
/*
 * board/amlogic/txl_skt_v1/firmware/scp_task/pwr_ctrl.c
 *
 * Copyright (C) 2015 Amlogic, Inc. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#include <gpio.h>
#include "pwm_ctrl.h"
#ifdef CONFIG_CEC_WAKEUP
#include <cec_tx_reg.h>
#endif

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

static void set_vddee_voltage(unsigned int target_voltage)
{
	unsigned int to, pwm_size = 0;
	static int (*pwm_voltage_ee)[2];

	/* BOOT_9 = H use PWM_CFG0(0.67v-0.97v), =L use PWM_CFG1(0.69v-0.89v) */
	/*set BOOT_9 input mode*/
	writel((readl(PREG_PAD_GPIO0_EN_N) | 0x200), PREG_PAD_GPIO0_EN_N);
	if (((readl(PREG_PAD_GPIO0_EN_N) & 0x200 ) == 0x200) &&
			((readl(PREG_PAD_GPIO0_I) & 0x200 ) == 0x0)) {
		uart_puts("use vddee new table!");
		uart_puts("\n");
		pwm_voltage_ee = pwm_voltage_table_ee_new;
		pwm_size = ARRAY_SIZE(pwm_voltage_table_ee_new);
	} else {
		uart_puts("use vddee table!");
		uart_puts("\n");
		pwm_voltage_ee = pwm_voltage_table_ee;
		pwm_size = ARRAY_SIZE(pwm_voltage_table_ee);
	}

	for (to = 0; to < pwm_size; to++) {
		if (pwm_voltage_ee[to][1] >= target_voltage) {
			break;
		}
	}

	if (to >= pwm_size) {
		to = pwm_size - 1;
	}

	writel(*(*(pwm_voltage_ee + to)), AO_PWM_PWM_B);
}

static void power_off_at_24M(unsigned int suspend_from)
{
	/* set gpioH_8 low to power off sd vdd */
	writel(readl(PREG_PAD_GPIO3_EN_N) & (~(1 << 8)), PREG_PAD_GPIO3_EN_N);
	writel(readl(PERIPHS_PIN_MUX_C) & (~(0xf)), PERIPHS_PIN_MUX_C);
	
	/*set gpioH_6 output/low to power off vcc 5v*/
	writel(readl(PREG_PAD_GPIO3_O) & (~(1 << 6)), PREG_PAD_GPIO3_O);
	writel(readl(PREG_PAD_GPIO3_EN_N) & (~(1 << 6)), PREG_PAD_GPIO3_EN_N);
	writel(readl(PERIPHS_PIN_MUX_B) & (~(0xf << 24)), PERIPHS_PIN_MUX_B);

	/*set test_n output/low to power off vcck*/
	writel(readl(AO_GPIO_O) & (~(1 << 31)), AO_GPIO_O);
	writel(readl(AO_GPIO_O_EN_N) & (~(1 << 31)), AO_GPIO_O_EN_N);
	writel(readl(AO_RTI_PIN_MUX_REG1) & (~(0xf << 28)), AO_RTI_PIN_MUX_REG1);

	/*step down ee voltage*/
	set_vddee_voltage(CONFIG_VDDEE_SLEEP_VOLTAGE);
}

static void power_on_at_24M(unsigned int suspend_from)
{
	/*step up ee voltage*/
	set_vddee_voltage(CONFIG_VDDEE_INIT_VOLTAGE);

	/* set gpioH_8 output/external pull high to power on sd vdd */
	writel(readl(PREG_PAD_GPIO3_EN_N) | (1 << 8), PREG_PAD_GPIO3_EN_N);
	writel(readl(PERIPHS_PIN_MUX_C) & (~(0xf)), PERIPHS_PIN_MUX_C);

	/*set test_n output/high to power on vcck*/
	writel(readl(AO_GPIO_O) | (1 << 31), AO_GPIO_O);
	writel(readl(AO_GPIO_O_EN_N) & (~(1 << 31)), AO_GPIO_O_EN_N);
	writel(readl(AO_RTI_PIN_MUX_REG1) & (~(0xf << 28)), AO_RTI_PIN_MUX_REG1);
	_udelay(100);

	/*set gpioH_6 output/high to power on vcc 5v*/
	writel(readl(PREG_PAD_GPIO3_O) | (1 << 6), PREG_PAD_GPIO3_O);
	writel(readl(PREG_PAD_GPIO3_EN_N) & (~(1 << 6)), PREG_PAD_GPIO3_EN_N);
	writel(readl(PERIPHS_PIN_MUX_B) & (~(0xf << 24)), PERIPHS_PIN_MUX_B);

	_udelay(10000);
}

void get_wakeup_source(void *response, unsigned int suspend_from)
{
	struct wakeup_info *p = (struct wakeup_info *)response;
	unsigned val;
	unsigned i = 0;

	p->gpio_info_count = i;
	p->status = RESPONSE_OK;
	val = (POWER_KEY_WAKEUP_SRC | AUTO_WAKEUP_SRC | REMOTE_WAKEUP_SRC);

	p->sources = val;
}
extern void __switch_idle_task(void);

static unsigned int detect_key(unsigned int suspend_from)
{
	int exit_reason = 0;
	unsigned char adc_key_cnt = 0;
	unsigned *irq = (unsigned *)WAKEUP_SRC_IRQ_ADDR_BASE;
	uart_puts("enter detect key\n");
	init_remote();
#ifdef CONFIG_CEC_WAKEUP
		if (hdmi_cec_func_config & 0x1) {
			remote_cec_hw_reset();
			cec_node_init();
		}
#endif

	do {
		#ifdef CONFIG_CEC_WAKEUP
		if (irq[IRQ_AO_CECB] == IRQ_AO_CEC2_NUM) {
			irq[IRQ_AO_CECB] = 0xFFFFFFFF;
			if (cec_power_on_check())
				exit_reason = CEC_WAKEUP;
		}
		#endif
		if (irq[IRQ_AO_TIMERA] == IRQ_AO_TIMERA_NUM) {
			irq[IRQ_AO_TIMERA] = 0xFFFFFFFF;
			saradc_enable();
			if (check_adc_key_resume()) {
				adc_key_cnt++;
				/*using variable 'adc_key_cnt' to eliminate the dithering of the key*/
				if (2 == adc_key_cnt)
					exit_reason = POWER_KEY_WAKEUP;
			} else {
				adc_key_cnt = 0;
			}
			saradc_disable();
		}
		
		if (irq[IRQ_AO_IR_DEC] == IRQ_AO_IR_DEC_NUM) {
			irq[IRQ_AO_IR_DEC] = 0xFFFFFFFF;
			if (remote_detect_key())
				exit_reason = REMOTE_WAKEUP;
		}

		if (irq[IRQ_VRTC] == IRQ_VRTC_NUM) {
			irq[IRQ_VRTC] = 0xFFFFFFFF;
			exit_reason = RTC_WAKEUP;
		}

		if (!(readl(PREG_PAD_GPIO2_I) & (0x01 << 18))
				&& (readl(PREG_PAD_GPIO2_O) & (0x01 << 17))
				&& !(readl(PREG_PAD_GPIO2_EN_N) & (0x01 << 17))) {
			_udelay(200*1000);
			if (!(readl(PREG_PAD_GPIO2_I) & (0x01 << 18)))
				exit_reason = BT_WAKEUP;
		}

		if (irq[IRQ_ETH_PTM] == IRQ_ETH_PMT_NUM) {
			irq[IRQ_ETH_PTM]= 0xFFFFFFFF;
			exit_reason = ETH_PMT_WAKEUP;
		}

		if (exit_reason)
			break;
		else
			__switch_idle_task();
	} while (1);

	return exit_reason;
}

static void pwr_op_init(struct pwr_op *pwr_op)
{
	pwr_op->power_off_at_24M = power_off_at_24M;
	pwr_op->power_on_at_24M = power_on_at_24M;
	pwr_op->detect_key = detect_key;
	pwr_op->get_wakeup_source = get_wakeup_source;
}
