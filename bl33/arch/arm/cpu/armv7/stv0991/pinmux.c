/*
 * (C) Copyright 2014
 * Vikas Manocha, ST Micoelectronics, vikas.manocha@st.com.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <asm/io.h>
#include <asm/arch/stv0991_creg.h>
#include <asm/arch/stv0991_periph.h>
#include <asm/arch/hardware.h>

static struct stv0991_creg *const stv0991_creg = \
			(struct stv0991_creg *)CREG_BASE_ADDR;

int stv0991_pinmux_config(int peripheral)
{
	switch (peripheral) {
	case UART_GPIOC_30_31:
		/* SSDA/SSCL pad muxing to UART Rx/Dx */
		writel((readl(&stv0991_creg->mux12) & GPIOC_31_MUX_MASK) |
				CFG_GPIOC_31_UART_RX,
				&stv0991_creg->mux12);
		writel((readl(&stv0991_creg->mux12) & GPIOC_30_MUX_MASK) |
				CFG_GPIOC_30_UART_TX,
				&stv0991_creg->mux12);
		/* SSDA/SSCL pad config to push pull*/
		writel((readl(&stv0991_creg->cfg_pad6) & GPIOC_31_MODE_MASK) |
				CFG_GPIOC_31_MODE_PP,
				&stv0991_creg->cfg_pad6);
		writel((readl(&stv0991_creg->cfg_pad6) & GPIOC_30_MODE_MASK) |
				CFG_GPIOC_30_MODE_HIGH,
				&stv0991_creg->cfg_pad6);
		break;
	case UART_GPIOB_16_17:
		/* ethernet rx_6/7 to UART Rx/Dx */
		writel((readl(&stv0991_creg->mux7) & GPIOB_17_MUX_MASK) |
				CFG_GPIOB_17_UART_RX,
				&stv0991_creg->mux7);
		writel((readl(&stv0991_creg->mux7) & GPIOB_16_MUX_MASK) |
				CFG_GPIOB_16_UART_TX,
				&stv0991_creg->mux7);
		break;
	case ETH_GPIOB_10_31_C_0_4:
		writel(readl(&stv0991_creg->mux6) & 0x000000FF,
				&stv0991_creg->mux6);
		writel(0x00000000, &stv0991_creg->mux7);
		writel(0x00000000, &stv0991_creg->mux8);
		writel(readl(&stv0991_creg->mux9) & 0xFFF00000,
				&stv0991_creg->mux9);
		/* Ethernet Voltage configuration to 1.8V*/
		writel((readl(&stv0991_creg->vdd_pad1) & VDD_ETH_PS_MASK) |
				ETH_VDD_CFG, &stv0991_creg->vdd_pad1);
		writel((readl(&stv0991_creg->vdd_pad1) & VDD_ETH_PS_MASK) |
				ETH_M_VDD_CFG, &stv0991_creg->vdd_pad1);

		break;
	default:
		break;
	}
	return 0;
}
