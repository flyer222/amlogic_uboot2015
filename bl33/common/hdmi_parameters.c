/*
* Copyright (C) 2017 Amlogic, Inc. All rights reserved.
* *
This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
* *
This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
* more details.
* *
You should have received a copy of the GNU General Public License along
* with this program; if not, write to the Free Software Foundation, Inc.,
* 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
* *
Description:
*/

#include <common.h>
#include <linux/stddef.h>
#include <amlogic/hdmi.h>

struct modeline_table {
	/* resolutions */
	unsigned int horpixels;
	unsigned int verpixels;
	/* clock and frequency */
	unsigned int pixel_clock;
	unsigned int hor_freq;
	unsigned int ver_freq;
	/* htimings */
	unsigned int hdisp;
	unsigned int hsyncstart;
	unsigned int hsyncend;
	unsigned int htotal;
	/* vtiminigs */
	unsigned int vdisp;
	unsigned int vsyncstart;
	unsigned int vsyncend;
	unsigned int vtotal;
	/* polarity and scan mode */
	unsigned int hsync_polarity; /* 1:+hsync, 0:-hsync */
	unsigned int vsync_polarity; /* 1:+vsync, 0:-vsync */
	unsigned int progress_mode; /* 1:progress, 0:interlaced */
};

static struct hdmi_format_para fmt_para_1920x1080p60_16x9 = {
	.vic = HDMI_1920x1080p60_16x9,
	.name = "1920x1080p60hz",
	.sname = "1080p60hz",
	.pixel_repetition_factor = 0,
	.progress_mode = 1,
	.scrambler_en = 0,
	.tmds_clk_div40 = 0,
	.tmds_clk = 148500,
	.timing = {
		.pixel_freq = 148500,
		.h_freq = 67500,
		.v_freq = 60000,
		.vsync_polarity = 1,
		.hsync_polarity = 1,
		.h_active = 1920,
		.h_total = 2200,
		.h_blank = 280,
		.h_front = 88,
		.h_sync = 44,
		.h_back = 148,
		.v_active = 1080,
		.v_total = 1125,
		.v_blank = 45,
		.v_front = 4,
		.v_sync = 5,
		.v_back = 36,
		.v_sync_ln = 1,
	},
};

static struct hdmi_format_para fmt_para_1920x1080p30_16x9 = {
	.vic = HDMI_1920x1080p30_16x9,
	.name = "1920x1080p30hz",
	.sname = "1080p30hz",
	.pixel_repetition_factor = 0,
	.progress_mode = 1,
	.scrambler_en = 0,
	.tmds_clk_div40 = 0,
	.tmds_clk = 74250,
	.timing = {
		.pixel_freq = 74250,
		.h_freq = 67500,
		.v_freq = 30000,
		.vsync_polarity = 1,
		.hsync_polarity = 1,
		.h_active = 1920,
		.h_total = 2200,
		.h_blank = 280,
		.h_front = 88,
		.h_sync = 44,
		.h_back = 148,
		.v_active = 1080,
		.v_total = 1125,
		.v_blank = 45,
		.v_front = 4,
		.v_sync = 5,
		.v_back = 36,
		.v_sync_ln = 1,
	},
};

static struct hdmi_format_para fmt_para_1920x1080p50_16x9 = {
	.vic = HDMI_1920x1080p50_16x9,
	.name = "1920x1080p50hz",
	.sname = "1080p50hz",
	.pixel_repetition_factor = 0,
	.progress_mode = 1,
	.scrambler_en = 0,
	.tmds_clk_div40 = 0,
	.tmds_clk = 148500,
	.timing = {
		.pixel_freq = 148500,
		.h_freq = 56250,
		.v_freq = 50000,
		.vsync_polarity = 1,
		.hsync_polarity = 1,
		.h_active = 1920,
		.h_total = 2640,
		.h_blank = 720,
		.h_front = 528,
		.h_sync = 44,
		.h_back = 148,
		.v_active = 1080,
		.v_total = 1125,
		.v_blank = 45,
		.v_front = 4,
		.v_sync = 5,
		.v_back = 36,
		.v_sync_ln = 1,
	},
};

static struct hdmi_format_para fmt_para_1920x1080p100_16x9 = {
	.vic = HDMI_1920x1080p100_16x9,
	.name = "1920x1080p100hz",
	.sname = "1080p100hz",
	.pixel_repetition_factor = 0,
	.progress_mode = 1,
	.scrambler_en = 0,
	.tmds_clk_div40 = 0,
	.tmds_clk = 297000,
	.timing = {
		.pixel_freq = 297000,
		.h_freq = 112500,
		.v_freq = 100000,
		.vsync_polarity = 1,
		.hsync_polarity = 1,
		.h_active = 1920,
		.h_total = 2640,
		.h_blank = 720,
		.h_front = 528,
		.h_sync = 44,
		.h_back = 148,
		.v_active = 1080,
		.v_total = 1125,
		.v_blank = 45,
		.v_front = 4,
		.v_sync = 5,
		.v_back = 36,
		.v_sync_ln = 1,
	},
};

static struct hdmi_format_para fmt_para_1920x1080p120_16x9 = {
	.vic = HDMI_1920x1080p120_16x9,
	.name = "1920x1080p120hz",
	.sname = "1080p120hz",
	.pixel_repetition_factor = 0,
	.progress_mode = 1,
	.scrambler_en = 0,
	.tmds_clk_div40 = 0,
	.tmds_clk = 297000,
	.timing = {
		.pixel_freq = 297000,
		.h_freq = 135000,
		.v_freq = 120000,
		.vsync_polarity = 1,
		.hsync_polarity = 1,
		.h_active = 1920,
		.h_total = 2200,
		.h_blank = 280,
		.h_front = 88,
		.h_sync = 44,
		.h_back = 148,
		.v_active = 1080,
		.v_total = 1125,
		.v_blank = 45,
		.v_front = 4,
		.v_sync = 5,
		.v_back = 36,
		.v_sync_ln = 1,
	},
};

static struct hdmi_format_para fmt_para_1920x1080p25_16x9 = {
	.vic = HDMI_1920x1080p25_16x9,
	.name = "1920x1080p25hz",
	.sname = "1080p25hz",
	.pixel_repetition_factor = 0,
	.progress_mode = 1,
	.scrambler_en = 0,
	.tmds_clk_div40 = 0,
	.tmds_clk = 148500,
	.timing = {
		.pixel_freq = 148500,
		.h_freq = 56250,
		.v_freq = 50000,
		.vsync_polarity = 1,
		.hsync_polarity = 1,
		.h_active = 1920,
		.h_total = 2640,
		.h_blank = 720,
		.h_front = 528,
		.h_sync = 44,
		.h_back = 148,
		.v_active = 1080,
		.v_total = 1125,
		.v_blank = 45,
		.v_front = 4,
		.v_sync = 5,
		.v_back = 36,
		.v_sync_ln = 1,
	},
};

static struct hdmi_format_para fmt_para_1920x1080p24_16x9 = {
	.vic = HDMI_1920x1080p24_16x9,
	.name = "1920x1080p24hz",
	.sname = "1080p24hz",
	.pixel_repetition_factor = 0,
	.progress_mode = 1,
	.scrambler_en = 0,
	.tmds_clk_div40 = 0,
	.tmds_clk = 74250,
	.timing = {
		.pixel_freq = 74250,
		.h_freq = 27000,
		.v_freq = 24000,
		.vsync_polarity = 1,
		.hsync_polarity = 1,
		.h_active = 1920,
		.h_total = 2750,
		.h_blank = 830,
		.h_front = 638,
		.h_sync = 44,
		.h_back = 148,
		.v_active = 1080,
		.v_total = 1125,
		.v_blank = 45,
		.v_front = 4,
		.v_sync = 5,
		.v_back = 36,
		.v_sync_ln = 1,
	},
};

static struct hdmi_format_para fmt_para_3840x2160p30_16x9 = {
	.vic = HDMI_3840x2160p30_16x9,
	.name = "3840x2160p30hz",
	.sname = "2160p30hz",
	.pixel_repetition_factor = 0,
	.progress_mode = 1,
	.scrambler_en = 0,
	.tmds_clk_div40 = 0,
	.tmds_clk = 297000,
	.timing = {
		.pixel_freq = 297000,
		.h_freq = 67500,
		.v_freq = 30000,
		.vsync_polarity = 1,
		.hsync_polarity = 1,
		.h_active = 3840,
		.h_total = 4400,
		.h_blank = 560,
		.h_front = 176,
		.h_sync = 88,
		.h_back = 296,
		.v_active = 2160,
		.v_total = 2250,
		.v_blank = 90,
		.v_front = 8,
		.v_sync = 10,
		.v_back = 72,
		.v_sync_ln = 1,
	},
};

static struct hdmi_format_para fmt_para_3840x2160p60_16x9 = {
	.vic = HDMI_3840x2160p60_16x9,
	.name = "3840x2160p60hz",
	.sname = "2160p60hz",
	.pixel_repetition_factor = 0,
	.progress_mode = 1,
	.scrambler_en = 1,
	.tmds_clk_div40 = 1,
	.tmds_clk = 594000,
	.timing = {
		.pixel_freq = 594000,
		.h_freq = 135000,
		.v_freq = 60000,
		.vsync_polarity = 1,
		.hsync_polarity = 1,
		.h_active = 3840,
		.h_total = 4400,
		.h_blank = 560,
		.h_front = 176,
		.h_sync = 88,
		.h_back = 296,
		.v_active = 2160,
		.v_total = 2250,
		.v_blank = 90,
		.v_front = 8,
		.v_sync = 10,
		.v_back = 72,
		.v_sync_ln = 1,
	},
};

static struct hdmi_format_para fmt_para_3840x2160p60_y420_16x9 = {
	.vic = HDMI_3840x2160p60_16x9_Y420,
	.name = "3840x2160p60hz420",
	.sname = "2160p60hz420",
	.pixel_repetition_factor = 0,
	.progress_mode = 1,
	.scrambler_en = 1,
	.tmds_clk_div40 = 1,
	.tmds_clk = 297000,
	.timing = {
		.pixel_freq = 594000,
		.h_freq = 135000,
		.v_freq = 60000,
		.vsync_polarity = 1,
		.hsync_polarity = 1,
		.h_active = 3840 / 2,
		.h_total = 4400 / 2,
		.h_blank = 560 / 2,
		.h_front = 176 / 2,
		.h_sync = 88 / 2,
		.h_back = 296 / 2,
		.v_active = 2160,
		.v_total = 2250,
		.v_blank = 90,
		.v_front = 8,
		.v_sync = 10,
		.v_back = 72,
		.v_sync_ln = 1,
	},
};

static struct hdmi_format_para fmt_para_3840x2160p50_16x9 = {
	.vic = HDMI_3840x2160p50_16x9,
	.name = "3840x2160p50hz",
	.sname = "2160p50hz",
	.pixel_repetition_factor = 0,
	.progress_mode = 1,
	.scrambler_en = 1,
	.tmds_clk_div40 = 1,
	.tmds_clk = 594000,
	.timing = {
		.pixel_freq = 594000,
		.h_freq = 112500,
		.v_freq = 50000,
		.vsync_polarity = 1,
		.hsync_polarity = 1,
		.h_active = 3840,
		.h_total = 5280,
		.h_blank = 1440,
		.h_front = 1056,
		.h_sync = 88,
		.h_back = 296,
		.v_active = 2160,
		.v_total = 2250,
		.v_blank = 90,
		.v_front = 8,
		.v_sync = 10,
		.v_back = 72,
		.v_sync_ln = 1,
	},
};

static struct hdmi_format_para fmt_para_3840x2160p50_y420_16x9 = {
	.vic = HDMI_3840x2160p50_16x9_Y420,
	.name = "3840x2160p50hz420",
	.sname = "2160p50hz420",
	.pixel_repetition_factor = 0,
	.progress_mode = 1,
	.scrambler_en = 1,
	.tmds_clk_div40 = 1,
	.tmds_clk = 297000,
	.timing = {
		.pixel_freq = 594000,
		.h_freq = 112500,
		.v_freq = 50000,
		.vsync_polarity = 1,
		.hsync_polarity = 1,
		.h_active = 3840 / 2,
		.h_total = 5280 / 2,
		.h_blank = 1440 / 2,
		.h_front = 1056 / 2,
		.h_sync = 88 / 2,
		.h_back = 296 / 2,
		.v_active = 2160,
		.v_total = 2250,
		.v_blank = 90,
		.v_front = 8,
		.v_sync = 10,
		.v_back = 72,
		.v_sync_ln = 1,
	},
};

static struct hdmi_format_para fmt_para_3840x2160p25_16x9 = {
	.vic = HDMI_3840x2160p25_16x9,
	.name = "3840x2160p25hz",
	.sname = "2160p25hz",
	.pixel_repetition_factor = 0,
	.progress_mode = 1,
	.scrambler_en = 0,
	.tmds_clk_div40 = 0,
	.tmds_clk = 297000,
	.timing = {
		.pixel_freq = 297000,
		.h_freq = 56250,
		.v_freq = 25000,
		.vsync_polarity = 1,
		.hsync_polarity = 1,
		.h_active = 3840,
		.h_total = 5280,
		.h_blank = 1440,
		.h_front = 1056,
		.h_sync = 88,
		.h_back = 296,
		.v_active = 2160,
		.v_total = 2250,
		.v_blank = 90,
		.v_front = 8,
		.v_sync = 10,
		.v_back = 72,
		.v_sync_ln = 1,
	},
};

static struct hdmi_format_para fmt_para_3840x2160p24_16x9 = {
	.vic = HDMI_3840x2160p24_16x9,
	.name = "3840x2160p24hz",
	.sname = "2160p24hz",
	.pixel_repetition_factor = 0,
	.progress_mode = 1,
	.scrambler_en = 0,
	.tmds_clk_div40 = 0,
	.tmds_clk = 297000,
	.timing = {
		.pixel_freq = 297000,
		.h_freq = 54000,
		.v_freq = 24000,
		.vsync_polarity = 1,
		.hsync_polarity = 1,
		.h_active = 3840,
		.h_total = 5500,
		.h_blank = 1660,
		.h_front = 1276,
		.h_sync = 88,
		.h_back = 296,
		.v_active = 2160,
		.v_total = 2250,
		.v_blank = 90,
		.v_front = 8,
		.v_sync = 10,
		.v_back = 72,
		.v_sync_ln = 1,
	},
};

static struct hdmi_format_para fmt_para_4096x2160p24_256x135 = {
	.vic = HDMI_4096x2160p24_256x135,
	.name = "4096x2160p24hz",
	.sname = "smpte24hz",
	.pixel_repetition_factor = 0,
	.progress_mode = 1,
	.scrambler_en = 0,
	.tmds_clk_div40 = 0,
	.tmds_clk = 297000,
	.timing = {
		.pixel_freq = 297000,
		.h_freq = 54000,
		.v_freq = 24000,
		.vsync_polarity = 1,
		.hsync_polarity = 1,
		.h_active = 4096,
		.h_total = 5500,
		.h_blank = 1404,
		.h_front = 1020,
		.h_sync = 88,
		.h_back = 296,
		.v_active = 2160,
		.v_total = 2250,
		.v_blank = 90,
		.v_front = 8,
		.v_sync = 10,
		.v_back = 72,
		.v_sync_ln = 1,
	},
};

static struct hdmi_format_para fmt_para_4096x2160p25_256x135 = {
	.vic = HDMI_4096x2160p25_256x135,
	.name = "4096x2160p25hz",
	.sname = "smpte25hz",
	.pixel_repetition_factor = 0,
	.progress_mode = 1,
	.scrambler_en = 0,
	.tmds_clk_div40 = 0,
	.tmds_clk = 297000,
	.timing = {
		.pixel_freq = 297000,
		.h_freq = 56250,
		.v_freq = 25000,
		.vsync_polarity = 1,
		.hsync_polarity = 1,
		.h_active = 4096,
		.h_total = 5280,
		.h_blank = 1184,
		.h_front = 968,
		.h_sync = 88,
		.h_back = 128,
		.v_active = 2160,
		.v_total = 2250,
		.v_blank = 90,
		.v_front = 8,
		.v_sync = 10,
		.v_back = 72,
		.v_sync_ln = 1,
	},
};

static struct hdmi_format_para fmt_para_4096x2160p30_256x135 = {
	.vic = HDMI_4096x2160p30_256x135,
	.name = "4096x2160p30hz",
	.sname = "smpte30hz",
	.pixel_repetition_factor = 0,
	.progress_mode = 1,
	.scrambler_en = 0,
	.tmds_clk_div40 = 0,
	.tmds_clk = 297000,
	.timing = {
		.pixel_freq = 297000,
		.h_freq = 67500,
		.v_freq = 30000,
		.vsync_polarity = 1,
		.hsync_polarity = 1,
		.h_active = 4096,
		.h_total = 4400,
		.h_blank = 304,
		.h_front = 88,
		.h_sync = 88,
		.h_back = 128,
		.v_active = 2160,
		.v_total = 2250,
		.v_blank = 90,
		.v_front = 8,
		.v_sync = 10,
		.v_back = 72,
		.v_sync_ln = 1,
	},
};

static struct hdmi_format_para fmt_para_4096x2160p50_256x135 = {
	.vic = HDMI_4096x2160p50_256x135,
	.name = "4096x2160p50hz",
	.sname = "smpte50hz",
	.pixel_repetition_factor = 0,
	.progress_mode = 1,
	.scrambler_en = 1,
	.tmds_clk_div40 = 1,
	.tmds_clk = 594000,
	.timing = {
		.pixel_freq = 594000,
		.h_freq = 112500,
		.v_freq = 50000,
		.vsync_polarity = 1,
		.hsync_polarity = 1,
		.h_active = 4096,
		.h_total = 5280,
		.h_blank = 1184,
		.h_front = 968,
		.h_sync = 88,
		.h_back = 128,
		.v_active = 2160,
		.v_total = 2250,
		.v_blank = 90,
		.v_front = 8,
		.v_sync = 10,
		.v_back = 72,
		.v_sync_ln = 1,
	},
};

static struct hdmi_format_para fmt_para_4096x2160p50_y420_256x135 = {
	.vic = HDMI_4096x2160p50_256x135_Y420,
	.name = "4096x2160p50hz420",
	.sname = "smpte50hz420",
	.pixel_repetition_factor = 0,
	.progress_mode = 1,
	.scrambler_en = 1,
	.tmds_clk_div40 = 1,
	.tmds_clk = 297000,
	.timing = {
		.pixel_freq = 594000,
		.h_freq = 112500,
		.v_freq = 50000,
		.vsync_polarity = 1,
		.hsync_polarity = 1,
		.h_active = 4096 / 2,
		.h_total = 5280 / 2,
		.h_blank = 1184 / 2,
		.h_front = 968 / 2,
		.h_sync = 88 / 2,
		.h_back = 128 / 2,
		.v_active = 2160,
		.v_total = 2250,
		.v_blank = 90,
		.v_front = 8,
		.v_sync = 10,
		.v_back = 72,
		.v_sync_ln = 1,
	},
};

static struct hdmi_format_para fmt_para_4096x2160p60_256x135 = {
	.vic = HDMI_4096x2160p60_256x135,
	.name = "4096x2160p60hz",
	.sname = "smpte60hz",
	.pixel_repetition_factor = 0,
	.progress_mode = 1,
	.scrambler_en = 1,
	.tmds_clk_div40 = 1,
	.tmds_clk = 594000,
	.timing = {
		.pixel_freq = 594000,
		.h_freq = 135000,
		.v_freq = 60000,
		.vsync_polarity = 1,
		.hsync_polarity = 1,
		.h_active = 4096,
		.h_total = 4400,
		.h_blank = 304,
		.h_front = 88,
		.h_sync = 88,
		.h_back = 128,
		.v_active = 2160,
		.v_total = 2250,
		.v_blank = 90,
		.v_front = 8,
		.v_sync = 10,
		.v_back = 72,
		.v_sync_ln = 1,
	},
};

static struct hdmi_format_para fmt_para_4096x2160p60_y420_256x135 = {
	.vic = HDMI_4096x2160p60_256x135_Y420,
	.name = "4096x2160p60hz420",
	.sname = "smpte60hz420",
	.pixel_repetition_factor = 0,
	.progress_mode = 1,
	.scrambler_en = 1,
	.tmds_clk_div40 = 1,
	.tmds_clk = 297000,
	.timing = {
		.pixel_freq = 594000,
		.h_freq = 135000,
		.v_freq = 60000,
		.vsync_polarity = 1,
		.hsync_polarity = 1,
		.h_active = 4096 / 2,
		.h_total = 4400 / 2,
		.h_blank = 304 / 2,
		.h_front = 88 / 2,
		.h_sync = 88 / 2,
		.h_back = 128 / 2,
		.v_active = 2160,
		.v_total = 2250,
		.v_blank = 90,
		.v_front = 8,
		.v_sync = 10,
		.v_back = 72,
		.v_sync_ln = 1,
	},
};

static struct hdmi_format_para fmt_para_1920x1080i60_16x9 = {
	.vic = HDMI_1920x1080i60_16x9,
	.name = "1920x1080i60hz",
	.sname = "1080i60hz",
	.pixel_repetition_factor = 0,
	.progress_mode = 0,
	.scrambler_en = 0,
	.tmds_clk_div40 = 0,
	.tmds_clk = 74250,
	.timing = {
		.pixel_freq = 74250,
		.h_freq = 33750,
		.v_freq = 60000,
		.vsync_polarity = 1,
		.hsync_polarity = 1,
		.h_active = 1920,
		.h_total = 2200,
		.h_blank = 280,
		.h_front = 88,
		.h_sync = 44,
		.h_back = 148,
		.v_active = 1080/2,
		.v_total = 1125,
		.v_blank = 45/2,
		.v_front = 2,
		.v_sync = 5,
		.v_back = 15,
		.v_sync_ln = 1,
	},
};

static struct hdmi_format_para fmt_para_1920x1080i50_16x9 = {
	.vic = HDMI_1920x1080i50_16x9,
	.name = "1920x1080i50hz",
	.sname = "1080i50hz",
	.pixel_repetition_factor = 0,
	.progress_mode = 0,
	.scrambler_en = 0,
	.tmds_clk_div40 = 0,
	.tmds_clk = 74250,
	.timing = {
		.pixel_freq = 74250,
		.h_freq = 28125,
		.v_freq = 50000,
		.vsync_polarity = 1,
		.hsync_polarity = 1,
		.h_active = 1920,
		.h_total = 2640,
		.h_blank = 720,
		.h_front = 528,
		.h_sync = 44,
		.h_back = 148,
		.v_active = 1080/2,
		.v_total = 1125,
		.v_blank = 45/2,
		.v_front = 2,
		.v_sync = 5,
		.v_back = 15,
		.v_sync_ln = 1,
	},
};

static struct hdmi_format_para fmt_para_1920x1080i100_16x9 = {
	.vic = HDMI_1920x1080i100_16x9,
	.name = "1920x1080i100hz",
	.sname = "1080i100hz",
	.pixel_repetition_factor = 0,
	.progress_mode = 0,
	.scrambler_en = 0,
	.tmds_clk_div40 = 0,
	.tmds_clk = 148500,
	.timing = {
		.pixel_freq = 148500,
		.h_freq = 56250,
		.v_freq = 100000,
		.vsync_polarity = 1,
		.hsync_polarity = 1,
		.h_active = 1920,
		.h_total = 2640,
		.h_blank = 720,
		.h_front = 528,
		.h_sync = 44,
		.h_back = 148,
		.v_active = 1080/2,
		.v_total = 1125,
		.v_blank = 45/2,
		.v_front = 2,
		.v_sync = 5,
		.v_back = 15,
		.v_sync_ln = 1,
	},
};

static struct hdmi_format_para fmt_para_1920x1080i120_16x9 = {
	.vic = HDMI_1920x1080i120_16x9,
	.name = "1920x1080i120hz",
	.sname = "1080i120hz",
	.pixel_repetition_factor = 0,
	.progress_mode = 0,
	.scrambler_en = 0,
	.tmds_clk_div40 = 0,
	.tmds_clk = 148500,
	.timing = {
		.pixel_freq = 148500,
		.h_freq = 67500,
		.v_freq = 120000,
		.vsync_polarity = 1,
		.hsync_polarity = 1,
		.h_active = 1920,
		.h_total = 2200,
		.h_blank = 280,
		.h_front = 88,
		.h_sync = 44,
		.h_back = 148,
		.v_active = 1080/2,
		.v_total = 1125,
		.v_blank = 45/2,
		.v_front = 2,
		.v_sync = 5,
		.v_back = 15,
		.v_sync_ln = 1,
	},
};

static struct hdmi_format_para fmt_para_1280x720p60_16x9 = {
	.vic = HDMI_1280x720p60_16x9,
	.name = "1280x720p60hz",
	.sname = "720p60hz",
	.pixel_repetition_factor = 0,
	.progress_mode = 1,
	.scrambler_en = 0,
	.tmds_clk_div40 = 0,
	.tmds_clk = 74250,
	.timing = {
		.pixel_freq = 74250,
		.h_freq = 45000,
		.v_freq = 60000,
		.vsync_polarity = 1,
		.hsync_polarity = 1,
		.h_active = 1280,
		.h_total = 1650,
		.h_blank = 370,
		.h_front = 110,
		.h_sync = 40,
		.h_back = 220,
		.v_active = 720,
		.v_total = 750,
		.v_blank = 30,
		.v_front = 5,
		.v_sync = 5,
		.v_back = 20,
		.v_sync_ln = 1,
	},
};

static struct hdmi_format_para fmt_para_1280x720p50_16x9 = {
	.vic = HDMI_1280x720p50_16x9,
	.name = "1280x720p50hz",
	.sname = "720p50hz",
	.pixel_repetition_factor = 0,
	.progress_mode = 1,
	.scrambler_en = 0,
	.tmds_clk_div40 = 0,
	.tmds_clk = 74250,
	.timing = {
		.pixel_freq = 74250,
		.h_freq = 37500,
		.v_freq = 50000,
		.vsync_polarity = 1,
		.hsync_polarity = 1,
		.h_active = 1280,
		.h_total = 1980,
		.h_blank = 700,
		.h_front = 440,
		.h_sync = 40,
		.h_back = 220,
		.v_active = 720,
		.v_total = 750,
		.v_blank = 30,
		.v_front = 5,
		.v_sync = 5,
		.v_back = 20,
		.v_sync_ln = 1,
	},
};

static struct hdmi_format_para fmt_para_1280x720p100_16x9 = {
	.vic = HDMI_1280x720p100_16x9,
	.name = "1280x720p100hz",
	.sname = "720p100hz",
	.pixel_repetition_factor = 0,
	.progress_mode = 1,
	.scrambler_en = 0,
	.tmds_clk_div40 = 0,
	.tmds_clk = 148500,
	.timing = {
		.pixel_freq = 148500,
		.h_freq = 75000,
		.v_freq = 100000,
		.vsync_polarity = 1,
		.hsync_polarity = 1,
		.h_active = 1280,
		.h_total = 1980,
		.h_blank = 700,
		.h_front = 440,
		.h_sync = 40,
		.h_back = 220,
		.v_active = 720,
		.v_total = 750,
		.v_blank = 30,
		.v_front = 5,
		.v_sync = 5,
		.v_back = 20,
		.v_sync_ln = 1,
	},
};

static struct hdmi_format_para fmt_para_1280x720p120_16x9 = {
	.vic = HDMI_1280x720p120_16x9,
	.name = "1280x720p120hz",
	.sname = "720p120hz",
	.pixel_repetition_factor = 0,
	.progress_mode = 1,
	.scrambler_en = 0,
	.tmds_clk_div40 = 0,
	.tmds_clk = 148500,
	.timing = {
		.pixel_freq = 148500,
		.h_freq = 90000,
		.v_freq = 120000,
		.vsync_polarity = 1,
		.hsync_polarity = 1,
		.h_active = 1280,
		.h_total = 1650,
		.h_blank = 370,
		.h_front = 110,
		.h_sync = 40,
		.h_back = 220,
		.v_active = 720,
		.v_total = 750,
		.v_blank = 30,
		.v_front = 5,
		.v_sync = 5,
		.v_back = 20,
		.v_sync_ln = 1,
	},
};

static struct hdmi_format_para fmt_para_720x480p60_16x9 = {
	.vic = HDMI_720x480p60_16x9,
	.name = "720x480p60hz",
	.sname = "480p60hz",
	.pixel_repetition_factor = 0,
	.progress_mode = 1,
	.scrambler_en = 0,
	.tmds_clk_div40 = 0,
	.tmds_clk = 27000,
	.timing = {
		.pixel_freq = 27000,
		.h_freq = 31469,
		.v_freq = 59940,
		.vsync_polarity = 0,
		.hsync_polarity = 0,
		.h_active = 720,
		.h_total = 858,
		.h_blank = 138,
		.h_front = 16,
		.h_sync = 62,
		.h_back = 60,
		.v_active = 480,
		.v_total = 525,
		.v_blank = 45,
		.v_front = 9,
		.v_sync = 6,
		.v_back = 30,
		.v_sync_ln = 7,
	},
};

static struct hdmi_format_para fmt_para_720x480p120_16x9 = {
	.vic = HDMI_720x480p120_16x9,
	.name = "720x480p120hz",
	.sname = "480p120hz",
	.pixel_repetition_factor = 0,
	.progress_mode = 1,
	.scrambler_en = 0,
	.tmds_clk_div40 = 0,
	.tmds_clk = 54000,
	.timing = {
		.pixel_freq = 54000,
		.h_freq = 62937,
		.v_freq = 119880,
		.vsync_polarity = 0,
		.hsync_polarity = 0,
		.h_active = 720,
		.h_total = 858,
		.h_blank = 138,
		.h_front = 16,
		.h_sync = 62,
		.h_back = 60,
		.v_active = 480,
		.v_total = 525,
		.v_blank = 45,
		.v_front = 9,
		.v_sync = 6,
		.v_back = 30,
		.v_sync_ln = 7,
	},
};

static struct hdmi_format_para fmt_para_720x480i60_16x9 = {
	.vic = HDMI_720x480i60_16x9,
	.name = "720x480i60hz",
	.sname = "480i60hz",
	.pixel_repetition_factor = 1,
	.progress_mode = 0,
	.scrambler_en = 0,
	.tmds_clk_div40 = 0,
	.tmds_clk = 27000,
	.timing = {
		.pixel_freq = 27000,
		.h_freq = 15734,
		.v_freq = 59940,
		.vsync_polarity = 0,
		.hsync_polarity = 0,
		.h_active = 1440,
		.h_total = 1716,
		.h_blank = 276,
		.h_front = 38,
		.h_sync = 124,
		.h_back = 114,
		.v_active = 480/2,
		.v_total = 525,
		.v_blank = 45/2,
		.v_front = 4,
		.v_sync = 3,
		.v_back = 15,
		.v_sync_ln = 4,
	},
};

static struct hdmi_format_para fmt_para_720x576p50_16x9 = {
	.vic = HDMI_720x576p50_16x9,
	.name = "720x576p50hz",
	.sname = "576p50hz",
	.pixel_repetition_factor = 0,
	.progress_mode = 1,
	.scrambler_en = 0,
	.tmds_clk_div40 = 0,
	.tmds_clk = 27000,
	.timing = {
		.pixel_freq = 27000,
		.h_freq = 31250,
		.v_freq = 50000,
		.vsync_polarity = 0,
		.hsync_polarity = 0,
		.h_active = 720,
		.h_total = 864,
		.h_blank = 144,
		.h_front = 12,
		.h_sync = 64,
		.h_back = 68,
		.v_active = 576,
		.v_total = 625,
		.v_blank = 49,
		.v_front = 5,
		.v_sync = 5,
		.v_back = 39,
		.v_sync_ln = 1,
	},
};

static struct hdmi_format_para fmt_para_720x576p100_16x9 = {
	.vic = HDMI_720x576p100_16x9,
	.name = "720x576p100hz",
	.sname = "576p100hz",
	.pixel_repetition_factor = 0,
	.progress_mode = 1,
	.scrambler_en = 0,
	.tmds_clk_div40 = 0,
	.tmds_clk = 54000,
	.timing = {
		.pixel_freq = 54000,
		.h_freq = 62500,
		.v_freq = 100000,
		.vsync_polarity = 0,
		.hsync_polarity = 0,
		.h_active = 720,
		.h_total = 864,
		.h_blank = 144,
		.h_front = 12,
		.h_sync = 64,
		.h_back = 68,
		.v_active = 576,
		.v_total = 625,
		.v_blank = 49,
		.v_front = 5,
		.v_sync = 5,
		.v_back = 39,
		.v_sync_ln = 1,
	},
};

static struct hdmi_format_para fmt_para_720x576i50_16x9 = {
	.vic = HDMI_720x576i50_16x9,
	.name = "720x576i50hz",
	.sname = "576i50hz",
	.pixel_repetition_factor = 1,
	.progress_mode = 0,
	.scrambler_en = 0,
	.tmds_clk_div40 = 0,
	.tmds_clk = 27000,
	.timing = {
		.pixel_freq = 27000,
		.h_freq = 15625,
		.v_freq = 50000,
		.vsync_polarity = 0,
		.hsync_polarity = 0,
		.h_active = 1440,
		.h_total = 1728,
		.h_blank = 288,
		.h_front = 24,
		.h_sync = 126,
		.h_back = 138,
		.v_active = 576/2,
		.v_total = 625,
		.v_blank = 49/2,
		.v_front = 2,
		.v_sync = 3,
		.v_back = 19,
		.v_sync_ln = 1,
	},
};

static struct hdmi_format_para fmt_para_non_hdmi_fmt = {
	.vic = HDMI_unkown,
	.name = "invalid",
	.sname = "invalid",
};

static struct hdmi_format_para fmt_para_vesa_480x320p60_4x3 = {
	.vic = HDMIV_480x320p60hz,
	.name = "480x320p60hz",
	.sname = "480x320p60hz",
	.pixel_repetition_factor = 0,
	.progress_mode = 1,
	.scrambler_en = 0,
	.tmds_clk_div40 = 0,
	.tmds_clk = 25200,
	.timing = {
		.pixel_freq = 25200,
		.h_freq = 31500,
		.v_freq = 60000,
		.vsync_polarity = 0, /* -VSync */
		.hsync_polarity = 0, /* -HSync */
		.h_active = 480,
		.h_total = 800,
		.h_blank = 320,
		.h_front = 120,
		.h_sync = 100,
		.h_back = 100,
		.v_active = 320,
		.v_total = 525,
		.v_blank = 205,
		.v_front = 8,
		.v_sync = 8,
		.v_back = 189,
		.v_sync_ln = 1,
	},
};

static struct hdmi_format_para fmt_para_vesa_640x480p60_4x3 = {
	.vic = HDMIV_640x480p60hz,
	.name = "640x480p60hz",
	.sname = "640x480p60hz",
	.pixel_repetition_factor = 0,
	.progress_mode = 1,
	.scrambler_en = 0,
	.tmds_clk_div40 = 0,
	.tmds_clk = 25175,
	.timing = {
		.pixel_freq = 25175,
		.h_freq = 26218,
		.v_freq = 59940,
		.vsync_polarity = 0,
		.hsync_polarity = 0,
		.h_active = 640,
		.h_total = 800,
		.h_blank = 160,
		.h_front = 16,
		.h_sync = 96,
		.h_back = 48,
		.v_active = 480,
		.v_total = 525,
		.v_blank = 45,
		.v_front = 10,
		.v_sync = 2,
		.v_back = 33,
		.v_sync_ln = 1,
	},
};

static struct hdmi_format_para fmt_para_vesa_800x480p60_4x3 = {
	.vic = HDMIV_800x480p60hz,
	.name = "800x480p60hz",
	.sname = "800x480p60hz",
	.pixel_repetition_factor = 0,
	.progress_mode = 1,
	.scrambler_en = 0,
	.tmds_clk_div40 = 0,
	.tmds_clk = 29230,
	.timing = {
		.pixel_freq = 29230,
		.h_freq = 30000,
		.v_freq = 60000,
		.vsync_polarity = 1,
		.hsync_polarity = 1,
		.h_active = 800,
		.h_total = 928,
		.h_blank = 128,
		.h_front = 40,
		.h_sync = 48,
		.h_back = 40,
		.v_active = 480,
		.v_total = 525,
		.v_blank = 45,
		.v_front = 13,
		.v_sync = 3,
		.v_back = 29,
		.v_sync_ln = 1,
	},
};

static struct hdmi_format_para fmt_para_vesa_800x600p60_4x3 = {
	.vic = HDMIV_800x600p60hz,
	.name = "800x600p60hz",
	.sname = "800x600p60hz",
	.pixel_repetition_factor = 0,
	.progress_mode = 1,
	.scrambler_en = 0,
	.tmds_clk_div40 = 0,
	.tmds_clk = 40000,
	.timing = {
		.pixel_freq = 40000,
		.h_freq = 37879,
		.v_freq = 60317,
		.vsync_polarity = 1,
		.hsync_polarity = 1,
		.h_active = 800,
		.h_total = 1056,
		.h_blank = 256,
		.h_front = 40,
		.h_sync = 128,
		.h_back = 88,
		.v_active = 600,
		.v_total = 628,
		.v_blank = 28,
		.v_front = 1,
		.v_sync = 4,
		.v_back = 23,
		.v_sync_ln = 1,
	},
};

static struct hdmi_format_para fmt_para_vesa_852x480p60_213x120 = {
	.vic = HDMIV_852x480p60hz,
	.name = "852x480p60hz",
	.sname = "852x480p60hz",
	.pixel_repetition_factor = 0,
	.progress_mode = 1,
	.scrambler_en = 0,
	.tmds_clk_div40 = 0,
	.tmds_clk = 30240,
	.timing = {
		.pixel_freq = 30240,
		.h_freq = 31900,
		.v_freq = 59960,
		.vsync_polarity = 1,
		.hsync_polarity = 1,
		.h_active = 852,
		.h_total = 948,
		.h_blank = 96,
		.h_front = 40,
		.h_sync = 16,
		.h_back = 40,
		.v_active = 480,
		.v_total = 532,
		.v_blank = 52,
		.v_front = 10,
		.v_sync = 2,
		.v_back = 40,
		.v_sync_ln = 1,
	},
};

static struct hdmi_format_para fmt_para_vesa_854x480p60_427x240 = {
	.vic = HDMIV_854x480p60hz,
	.name = "854x480p60hz",
	.sname = "854x480p60hz",
	.pixel_repetition_factor = 0,
	.progress_mode = 1,
	.scrambler_en = 0,
	.tmds_clk_div40 = 0,
	.tmds_clk = 30240,
	.timing = {
		.pixel_freq = 30240,
		.h_freq = 31830,
		.v_freq = 59950,
		.vsync_polarity = 1,
		.hsync_polarity = 1,
		.h_active = 854,
		.h_total = 950,
		.h_blank = 96,
		.h_front = 40,
		.h_sync = 16,
		.h_back = 40,
		.v_active = 480,
		.v_total = 531,
		.v_blank = 51,
		.v_front = 10,
		.v_sync = 2,
		.v_back = 39,
		.v_sync_ln = 1,
	},
};

static struct hdmi_format_para fmt_para_vesa_1024x600p60_17x10 = {
	.vic = HDMIV_1024x600p60hz,
	.name = "1024x600p60hz",
	.sname = "1024x600p60hz",
	.pixel_repetition_factor = 0,
	.progress_mode = 1,
	.scrambler_en = 0,
	.tmds_clk_div40 = 0,
	.tmds_clk = 44580,
	.timing = {
		.pixel_freq = 44580,
		.h_freq = 37320,
		.v_freq = 60000,
		.vsync_polarity = 1,
		.hsync_polarity = 1,
		.h_active = 1024,
		.h_total = 1152,
		.h_blank = 128,
		.h_front = 40,
		.h_sync = 48,
		.h_back = 40,
		.v_active = 600,
		.v_total = 645,
		.v_blank = 45,
		.v_front = 13,
		.v_sync = 3,
		.v_back = 29,
		.v_sync_ln = 1,
	},
};

static struct hdmi_format_para fmt_para_vesa_1024x768p60_4x3 = {
	.vic = HDMIV_1024x768p60hz,
	.name = "1024x768p60hz",
	.sname = "1024x768p60hz",
	.pixel_repetition_factor = 0,
	.progress_mode = 1,
	.scrambler_en = 0,
	.tmds_clk_div40 = 0,
	.tmds_clk = 650000,
	.timing = {
		.pixel_freq = 650000,
		.h_freq = 48360,
		.v_freq = 60004,
		.vsync_polarity = 1,
		.hsync_polarity = 1,
		.h_active = 1024,
		.h_total = 1344,
		.h_blank = 320,
		.h_front = 24,
		.h_sync = 136,
		.h_back = 160,
		.v_active = 768,
		.v_total = 806,
		.v_blank = 38,
		.v_front = 3,
		.v_sync = 6,
		.v_back = 29,
		.v_sync_ln = 1,
	},
};

static struct hdmi_format_para fmt_para_vesa_1152x864p75_4x3 = {
	.vic = HDMIV_1152x864p75hz,
	.name = "1152x864p75hz",
	.sname = "1152x864p75hz",
	.pixel_repetition_factor = 0,
	.progress_mode = 1,
	.scrambler_en = 0,
	.tmds_clk_div40 = 0,
	.tmds_clk = 108000,
	.timing = {
		.pixel_freq = 108000,
		.h_freq = 67500,
		.v_freq = 75000,
		.vsync_polarity = 1,
		.hsync_polarity = 1,
		.h_active = 1152,
		.h_total = 1600,
		.h_blank = 448,
		.h_front = 64,
		.h_sync = 128,
		.h_back = 256,
		.v_active = 864,
		.v_total = 900,
		.v_blank = 36,
		.v_front = 1,
		.v_sync = 3,
		.v_back = 32,
	},
};

static struct hdmi_format_para fmt_para_vesa_1280x480p60_8x3 = {
	.vic = HDMIV_1280x480p60hz,
	.name = "1280x480p60hz",
	.sname = "1280x480p60hz",
	.pixel_repetition_factor = 0,
	.progress_mode = 1,
	.scrambler_en = 0,
	.tmds_clk_div40 = 0,
	.tmds_clk = 43200,
	.timing = {
		.pixel_freq = 43200,
		.h_freq = 30000,
		.v_freq = 60000,
		.vsync_polarity = 1,
		.hsync_polarity = 1,
		.h_active = 1280,
		.h_total = 1440,
		.h_blank = 160,
		.h_front = 48,
		.h_sync = 32,
		.h_back = 80,
		.v_active = 480,
		.v_total = 500,
		.v_blank = 20,
		.v_front = 3,
		.v_sync = 7,
		.v_back = 10,
		.v_sync_ln = 1,
	},
};

static struct hdmi_format_para fmt_para_vesa_1280x600p60_32x15 = {
#if 0 /* TODO */
	.vic = HDMIV_1280x600p60hz,
	.name = "1280x600p60hz",
	.pixel_repetition_factor = 0,
	.progress_mode = 1,
	.scrambler_en = 0,
	.tmds_clk_div40 = 0,
	.tmds_clk = ,
	.timing = {
		.pixel_freq = ,
		.h_freq = ,
		.v_freq = 60000,
		.vsync_polarity = 1,
		.hsync_polarity = 1,
		.h_active = 1280,
		.h_total = ,
		.h_blank = ,
		.h_front = ,
		.h_sync = ,
		.h_back = ,
		.v_active = 600,
		.v_total = ,
		.v_blank = ,
		.v_front = ,
		.v_sync = ,
		.v_back = ,
		.v_sync_ln = 1,
	},
#endif
};

static struct hdmi_format_para fmt_para_vesa_1280x768p60_5x3 = {
	.vic = HDMIV_1280x768p60hz,
	.name = "1280x768p60hz",
	.sname = "1280x768p60hz",
	.pixel_repetition_factor = 0,
	.progress_mode = 1,
	.scrambler_en = 0,
	.tmds_clk_div40 = 0,
	.tmds_clk = 79500,
	.timing = {
		.pixel_freq = 79500,
		.h_freq = 47776,
		.v_freq = 59870,
		.vsync_polarity = 1,
		.hsync_polarity = 1,
		.h_active = 1280,
		.h_total = 1664,
		.h_blank = 384,
		.h_front = 64,
		.h_sync = 128,
		.h_back = 192,
		.v_active = 768,
		.v_total = 798,
		.v_blank = 30,
		.v_front = 3,
		.v_sync = 7,
		.v_back = 20,
	},
};

static struct hdmi_format_para fmt_para_vesa_1280x800p60_8x5 = {
	.vic = HDMIV_1280x800p60hz,
	.name = "1280x800p60hz",
	.sname = "1280x800p60hz",
	.pixel_repetition_factor = 0,
	.progress_mode = 1,
	.scrambler_en = 0,
	.tmds_clk_div40 = 0,
	.tmds_clk = 83500,
	.timing = {
		.pixel_freq = 83500,
		.h_freq = 49380,
		.v_freq = 59910,
		.vsync_polarity = 1,
		.hsync_polarity = 1,
		.h_active = 1280,
		.h_total = 1440,
		.h_blank = 160,
		.h_front = 48,
		.h_sync = 32,
		.h_back = 80,
		.v_active = 800,
		.v_total = 823,
		.v_blank = 23,
		.v_front = 3,
		.v_sync = 6,
		.v_back = 14,
		.v_sync_ln = 1,
	},
};

static struct hdmi_format_para fmt_para_vesa_1280x960p60_4x3 = {
	.vic = HDMIV_1280x960p60hz,
	.name = "1280x960p60hz",
	.sname = "1280x960p60hz",
	.pixel_repetition_factor = 0,
	.progress_mode = 1,
	.scrambler_en = 0,
	.tmds_clk_div40 = 0,
	.tmds_clk = 108000,
	.timing = {
		.pixel_freq = 108000,
		.h_freq = 60000,
		.v_freq = 60000,
		.vsync_polarity = 1,
		.hsync_polarity = 1,
		.h_active = 1280,
		.h_total = 1440,
		.h_blank = 520,
		.h_front = 96,
		.h_sync = 112,
		.h_back = 312,
		.v_active = 960,
		.v_total = 1000,
		.v_blank = 40,
		.v_front = 1,
		.v_sync = 3,
		.v_back = 36,
	},
};

static struct hdmi_format_para fmt_para_vesa_1280x1024p60_5x4 = {
	.vic = HDMIV_1280x1024p60hz,
	.name = "1280x1024p60hz",
	.sname = "1280x1024p60hz",
	.pixel_repetition_factor = 0,
	.progress_mode = 1,
	.scrambler_en = 0,
	.tmds_clk_div40 = 0,
	.tmds_clk = 108000,
	.timing = {
		.pixel_freq = 108000,
		.h_freq = 64080,
		.v_freq = 60020,
		.vsync_polarity = 1,
		.hsync_polarity = 1,
		.h_active = 1280,
		.h_total = 1688,
		.h_blank = 408,
		.h_front = 48,
		.h_sync = 112,
		.h_back = 248,
		.v_active = 1024,
		.v_total = 1066,
		.v_blank = 42,
		.v_front = 1,
		.v_sync = 3,
		.v_back = 38,
		.v_sync_ln = 1,
	},
};

static struct hdmi_format_para fmt_para_vesa_1360x768p60_16x9 = {
	.vic = HDMIV_1360x768p60hz,
	.name = "1360x768p60hz",
	.sname = "1360x768p60hz",
	.pixel_repetition_factor = 0,
	.progress_mode = 1,
	.scrambler_en = 0,
	.tmds_clk_div40 = 0,
	.tmds_clk = 855000,
	.timing = {
		.pixel_freq = 855000,
		.h_freq = 47700,
		.v_freq = 60015,
		.vsync_polarity = 1,
		.hsync_polarity = 1,
		.h_active = 1360,
		.h_total = 1792,
		.h_blank = 432,
		.h_front = 64,
		.h_sync = 112,
		.h_back = 256,
		.v_active = 768,
		.v_total = 795,
		.v_blank = 27,
		.v_front = 3,
		.v_sync = 6,
		.v_back = 18,
		.v_sync_ln = 1,
	},
};

static struct hdmi_format_para fmt_para_vesa_1366x768p60_16x9 = {
	.vic = HDMIV_1366x768p60hz,
	.name = "1366x768p60hz",
	.sname = "1366x768p60hz",
	.pixel_repetition_factor = 0,
	.progress_mode = 1,
	.scrambler_en = 0,
	.tmds_clk_div40 = 0,
	.tmds_clk = 85500,
	.timing = {
		.pixel_freq = 85500,
		.h_freq = 47880,
		.v_freq = 59790,
		.vsync_polarity = 1,
		.hsync_polarity = 1,
		.h_active = 1366,
		.h_total = 1792,
		.h_blank = 426,
		.h_front = 70,
		.h_sync = 143,
		.h_back = 213,
		.v_active = 768,
		.v_total = 798,
		.v_blank = 30,
		.v_front = 3,
		.v_sync = 3,
		.v_back = 24,
		.v_sync_ln = 1,
	},
};

static struct hdmi_format_para fmt_para_vesa_1400x1050p60_4x3 = {
	.vic = HDMIV_1400x1050p60hz,
	.name = "1400x1050p60hz",
	.sname = "1400x1050p60hz",
	.pixel_repetition_factor = 0,
	.progress_mode = 1,
	.scrambler_en = 0,
	.tmds_clk_div40 = 0,
	.tmds_clk = 121750,
	.timing = {
		.pixel_freq = 121750,
		.h_freq = 65317,
		.v_freq = 59978,
		.vsync_polarity = 1,
		.hsync_polarity = 1,
		.h_active = 1400,
		.h_total = 1864,
		.h_blank = 464,
		.h_front = 88,
		.h_sync = 144,
		.h_back = 232,
		.v_active = 1050,
		.v_total = 1089,
		.v_blank = 39,
		.v_front = 3,
		.v_sync = 4,
		.v_back = 32,
		.v_sync_ln = 1,
	},
};

static struct hdmi_format_para fmt_para_vesa_1440x900p60_8x5 = {
	.vic = HDMIV_1440x900p60hz,
	.name = "1440x900p60hz",
	.sname = "1440x900p60hz",
	.pixel_repetition_factor = 0,
	.progress_mode = 1,
	.scrambler_en = 0,
	.tmds_clk_div40 = 0,
	.tmds_clk = 106500,
	.timing = {
		.pixel_freq = 106500,
		.h_freq = 56040,
		.v_freq = 59887,
		.vsync_polarity = 1,
		.hsync_polarity = 1,
		.h_active = 1440,
		.h_total = 1904,
		.h_blank = 464,
		.h_front = 80,
		.h_sync = 152,
		.h_back = 232,
		.v_active = 900,
		.v_total = 934,
		.v_blank = 34,
		.v_front = 3,
		.v_sync = 6,
		.v_back = 25,
		.v_sync_ln = 1,
	},
};

static struct hdmi_format_para fmt_para_vesa_1440x2560p60_9x16 = {
	.vic = HDMIV_1440x2560p60hz,
	.name = "1440x2560p60hz",
	.sname = "1440x2560p60hz",
	.pixel_repetition_factor = 0,
	.progress_mode = 1,
	.scrambler_en = 0,
	.tmds_clk_div40 = 0,
	.tmds_clk = 244850,
	.timing = {
		.pixel_freq = 244850,
		.h_freq = 155760,
		.v_freq = 59999,
		.vsync_polarity = 1,
		.hsync_polarity = 1,
		.h_active = 1440,
		.h_total = 1572,
		.h_blank = 132,
		.h_front = 64,
		.h_sync = 4,
		.h_back = 64,
		.v_active = 2560,
		.v_total = 2596,
		.v_blank = 36,
		.v_front = 16,
		.v_sync = 4,
		.v_back = 16,
		.v_sync_ln = 1,
	},
};

static struct hdmi_format_para fmt_para_vesa_1440x2560p70_9x16 = {
	.vic = HDMIV_1440x2560p70hz,
	.name = "1440x2560p70hz",
	.sname = "1440x2560p70hz",
	.pixel_repetition_factor = 0,
	.progress_mode = 1,
	.scrambler_en = 0,
	.tmds_clk_div40 = 0,
	.tmds_clk = 280000,
	.timing = {
		.pixel_freq = 280000,
		.h_freq = 180320,
		.v_freq = 70100,
		.vsync_polarity = 1,
		.hsync_polarity = 1,
		.h_active = 1440,
		.h_total = 1550,
		.h_blank = 110,
		.h_front = 68,
		.h_sync = 16,
		.h_back = 26,
		.v_active = 2560,
		.v_total = 2576,
		.v_blank = 16,
		.v_front = 6,
		.v_sync = 6,
		.v_back = 4,
		.v_sync_ln = 1,
	},
};

static struct hdmi_format_para fmt_para_vesa_1600x900p60_16x9 = {
	.vic = HDMIV_1600x900p60hz,
	.name = "1600x900p60hz",
	.sname = "1600x900p60hz",
	.pixel_repetition_factor = 0,
	.progress_mode = 1,
	.scrambler_en = 0,
	.tmds_clk_div40 = 0,
	.tmds_clk = 108000,
	.timing = {
		.pixel_freq = 108000,
		.h_freq = 60000,
		.v_freq = 60000,
		.vsync_polarity = 1,
		.hsync_polarity = 1,
		.h_active = 1600,
		.h_total = 1800,
		.h_blank = 200,
		.h_front = 24,
		.h_sync = 80,
		.h_back = 96,
		.v_active = 900,
		.v_total = 1000,
		.v_blank = 100,
		.v_front = 1,
		.v_sync = 3,
		.v_back = 96,
		.v_sync_ln = 1,
	},
};

static struct hdmi_format_para fmt_para_vesa_1600x1200p60_4x3 = {
	.vic = HDMIV_1600x1200p60hz,
	.name = "1600x1200p60hz",
	.sname = "1600x1200p60hz",
	.pixel_repetition_factor = 0,
	.progress_mode = 1,
	.scrambler_en = 0,
	.tmds_clk_div40 = 0,
	.tmds_clk = 162000,
	.timing = {
		.pixel_freq = 162000,
		.h_freq = 75000,
		.v_freq = 60000,
		.vsync_polarity = 1,
		.hsync_polarity = 1,
		.h_active = 1600,
		.h_total = 2160,
		.h_blank = 560,
		.h_front = 64,
		.h_sync = 192,
		.h_back = 304,
		.v_active = 1200,
		.v_total = 1250,
		.v_blank = 50,
		.v_front = 1,
		.v_sync = 3,
		.v_back = 46,
		.v_sync_ln = 1,
	},
};

static struct hdmi_format_para fmt_para_vesa_1680x1050p60_8x5 = {
	.vic = HDMIV_1680x1050p60hz,
	.name = "1680x1050p60hz",
	.sname = "1680x1050p60hz",
	.pixel_repetition_factor = 0,
	.progress_mode = 1,
	.scrambler_en = 0,
	.tmds_clk_div40 = 0,
	.tmds_clk = 1190000,
	.timing = {
		.pixel_freq = 1190000,
		.h_freq = 64673,
		.v_freq = 59883,
		.vsync_polarity = 1,
		.hsync_polarity = 1,
		.h_active = 1680,
		.h_total = 1840,
		.h_blank = 160,
		.h_front = 48,
		.h_sync = 32,
		.h_back = 80,
		.v_active = 1050,
		.v_total = 1080,
		.v_blank = 30,
		.v_front = 3,
		.v_sync = 6,
		.v_back = 32,
		.v_sync_ln = 1,
	},
};

static struct hdmi_format_para fmt_para_vesa_1920x1200p60_8x5 = {
	.vic = HDMIV_1920x1200p60hz,
	.name = "1920x1200p60hz",
	.sname = "1920x1200p60hz",
	.pixel_repetition_factor = 0,
	.progress_mode = 1,
	.scrambler_en = 0,
	.tmds_clk_div40 = 0,
	.tmds_clk = 193250,
	.timing = {
		.pixel_freq = 193250,
		.h_freq = 74700,
		.v_freq = 59885,
		.vsync_polarity = 1,
		.hsync_polarity = 1,
		.h_active = 1920,
		.h_total = 2592,
		.h_blank = 672,
		.h_front = 136,
		.h_sync = 200,
		.h_back = 336,
		.v_active = 1200,
		.v_total = 1245,
		.v_blank = 45,
		.v_front = 3,
		.v_sync = 6,
		.v_back = 36,
		.v_sync_ln = 1,
	},
};
static struct hdmi_format_para fmt_para_vesa_2160x1200p90_9x5 = {
	.vic = HDMIV_2160x1200p90hz,
	.name = "2160x1200p90hz",
	.sname = "2160x1200p90hz",
	.pixel_repetition_factor = 0,
	.progress_mode = 1,
	.scrambler_en = 0,
	.tmds_clk_div40 = 0,
	.tmds_clk = 268550,
	.timing = {
		.pixel_freq = 268550,
		.h_freq = 109080,
		.v_freq = 90000,
		.vsync_polarity = 1,
		.hsync_polarity = 1,
		.h_active = 2160,
		.h_total = 2462,
		.h_blank = 302,
		.h_front = 190,
		.h_sync = 32,
		.h_back = 80,
		.v_active = 1200,
		.v_total = 1212,
		.v_blank = 12,
		.v_front = 6,
		.v_sync = 3,
		.v_back = 3,
		.v_sync_ln = 1,
	},
};

static struct hdmi_format_para fmt_para_vesa_2560x1080p60_64x27 = {
	.vic = HDMIV_2560x1080p60hz,
	.name = "2560x1080p60hz",
	.sname = "2560x1080p60hz",
	.pixel_repetition_factor = 0,
	.progress_mode = 1,
	.scrambler_en = 0,
	.tmds_clk_div40 = 0,
	.tmds_clk = 198000,
	.timing = {
		.pixel_freq = 198000,
		.h_freq = 66000,
		.v_freq = 60000,
		.vsync_polarity = 1,
		.hsync_polarity = 1,
	    .h_active = 2560,
		.h_total = 3000,
		.h_blank = 440,
		.h_front = 248,
		.h_sync = 44,
		.h_back = 148,
		.v_active = 1080,
		.v_total = 1100,
		.v_blank = 20,
		.v_front = 4,
		.v_sync = 5,
		.v_back = 11,
		.v_sync_ln = 1,
	},
};

static struct hdmi_format_para fmt_para_vesa_2560x1440p60_16x9 = {
        .vic = HDMIV_2560x1440p60hz,
        .name = "2560x1440p60hz",
        .sname = "2560x1440p60hz",
        .pixel_repetition_factor = 0,
        .progress_mode = 1,
        .scrambler_en = 0,
        .tmds_clk_div40 = 0,
        .tmds_clk =  241500,
        .timing = {
                .pixel_freq = 241500,
                .h_freq = 98700,
                .v_freq = 60000,
                .vsync_polarity = 1,
                .hsync_polarity = 1,
                .h_active = 2560,
                .h_total = 2720,
                .h_blank = 160,
                .h_front = 48,
                .h_sync = 32,
                .h_back = 80,
                .v_active = 1440,
                .v_total = 1481,
                .v_blank = 41,
                .v_front = 2,
                .v_sync = 5,
                .v_back = 34,
                .v_sync_ln = 1,
        },

};

static struct hdmi_format_para fmt_para_vesa_2560x1600p60_16x9 = {
	.vic = HDMIV_2560x1600p60hz,
	.name = "2560x1600p60hz",
	.sname = "2560x1600p60hz",
	.pixel_repetition_factor = 0,
	.progress_mode = 1,
	.scrambler_en = 0,
	.tmds_clk_div40 = 0,
	.tmds_clk = 297000,
	.timing = {
		.pixel_freq = 297000,
		.h_freq = 99664,
		.v_freq = 60000,
		.vsync_polarity = 0,
		.hsync_polarity = 0,
		.h_active = 2560,
		.h_total = 2980,
		.h_blank = 420,
		.h_front = 120,
		.h_sync = 32,
		.h_back = 268,
		.v_active = 1600,
		.v_total = 1652,
		.v_blank = 52,
		.v_front = 32,
		.v_sync = 10,
		.v_back = 10,
		.v_sync_ln = 1,
	},
};

static struct hdmi_format_para fmt_para_vesa_3440x1440p60_43x18 = {
	.vic = HDMIV_3440x1440p60hz,
	.name = "3440x1440p60hz",
	.sname = "3440x1440p60hz",
	.pixel_repetition_factor = 0,
	.progress_mode = 1,
	.scrambler_en = 0,
	.tmds_clk_div40 = 0,
	.tmds_clk = 319750,
	.timing = {
		.pixel_freq = 319750,
		.h_freq = 88819,
		.v_freq = 59973,
		.vsync_polarity = 1,
		.hsync_polarity = 1,
		.h_active = 3440,
		.h_total = 3600,
		.h_blank = 160,
		.h_front = 48,
		.h_sync = 32,
		.h_back = 80,
		.v_active = 1440,
		.v_total = 1481,
		.v_blank = 41,
		.v_front = 3,
		.v_sync = 10,
		.v_back = 28,
		.v_sync_ln = 1,
	},
};

static struct hdmi_format_para fmt_para_custombuilt = {
	.vic = HDMIV_CUSTOMBUILT,
	.name = "custombuilt",
	.sname = "custombuilt",
	.pixel_repetition_factor = 0,
	.scrambler_en = 0,
	.tmds_clk_div40 = 0,
	.timing = {
		.v_sync_ln = 1,
	},
};


static struct hdmi_format_para *all_fmt_paras[] = {
	&fmt_para_3840x2160p60_y420_16x9,
	&fmt_para_3840x2160p60_16x9,
	&fmt_para_3840x2160p50_y420_16x9,
	&fmt_para_3840x2160p50_16x9,
	&fmt_para_3840x2160p30_16x9,
	&fmt_para_3840x2160p25_16x9,
	&fmt_para_3840x2160p24_16x9,
	&fmt_para_4096x2160p24_256x135,
	&fmt_para_4096x2160p25_256x135,
	&fmt_para_4096x2160p30_256x135,
	&fmt_para_4096x2160p50_y420_256x135,
	&fmt_para_4096x2160p50_256x135,
	&fmt_para_4096x2160p60_y420_256x135,
	&fmt_para_4096x2160p60_256x135,
	&fmt_para_1920x1080p50_16x9,
	&fmt_para_1920x1080p60_16x9,
	&fmt_para_1920x1080p30_16x9,
	&fmt_para_1920x1080p25_16x9,
	&fmt_para_1920x1080p24_16x9,
	&fmt_para_1920x1080p100_16x9,
	&fmt_para_1920x1080p120_16x9,
	&fmt_para_1920x1080i60_16x9,
	&fmt_para_1920x1080i50_16x9,
	&fmt_para_1920x1080i100_16x9,
	&fmt_para_1920x1080i120_16x9,
	&fmt_para_1280x720p60_16x9,
	&fmt_para_1280x720p50_16x9,
	&fmt_para_1280x720p100_16x9,
	&fmt_para_1280x720p120_16x9,
	&fmt_para_720x480p60_16x9,
	&fmt_para_720x480p120_16x9,
	&fmt_para_720x480i60_16x9,
	&fmt_para_720x576p50_16x9,
	&fmt_para_720x576p100_16x9,
	&fmt_para_720x576i50_16x9,
	&fmt_para_vesa_480x320p60_4x3,
	&fmt_para_vesa_640x480p60_4x3,
	&fmt_para_vesa_800x480p60_4x3,
	&fmt_para_vesa_800x600p60_4x3,
	&fmt_para_vesa_852x480p60_213x120,
	&fmt_para_vesa_854x480p60_427x240,
	&fmt_para_vesa_1024x600p60_17x10,
	&fmt_para_vesa_1024x768p60_4x3,
	&fmt_para_vesa_1152x864p75_4x3,
	&fmt_para_vesa_1280x480p60_8x3,
	&fmt_para_vesa_1280x600p60_32x15,
	&fmt_para_vesa_1280x768p60_5x3,
	&fmt_para_vesa_1280x800p60_8x5,
	&fmt_para_vesa_1280x960p60_4x3,
	&fmt_para_vesa_1280x1024p60_5x4,
	&fmt_para_vesa_1360x768p60_16x9,
	&fmt_para_vesa_1366x768p60_16x9,
	&fmt_para_vesa_1400x1050p60_4x3,
	&fmt_para_vesa_1440x900p60_8x5,
	&fmt_para_vesa_1440x2560p60_9x16,
	&fmt_para_vesa_1440x2560p70_9x16,
	&fmt_para_vesa_1600x900p60_16x9,
	&fmt_para_vesa_1600x1200p60_4x3,
	&fmt_para_vesa_1680x1050p60_8x5,
	&fmt_para_vesa_1920x1200p60_8x5,
	&fmt_para_vesa_2160x1200p90_9x5,
	&fmt_para_vesa_2560x1080p60_64x27,
	&fmt_para_vesa_2560x1440p60_16x9,
	&fmt_para_vesa_2560x1600p60_16x9,
	&fmt_para_vesa_3440x1440p60_43x18,
	&fmt_para_custombuilt,
	&fmt_para_non_hdmi_fmt,
	NULL,
};

struct hdmi_format_para *hdmi_get_fmt_paras(enum hdmi_vic vic)
{
	int i;

	for (i = 0; all_fmt_paras[i] != NULL; i++) {
		if (vic == all_fmt_paras[i]->vic)
			return all_fmt_paras[i];
	}
	return NULL;
}

static struct parse_cd parse_cd_[] = {
	{HDMI_COLOR_DEPTH_24B, "8bit",},
	{HDMI_COLOR_DEPTH_30B, "10bit"},
	{HDMI_COLOR_DEPTH_36B, "12bit"},
	{HDMI_COLOR_DEPTH_48B, "16bit"},
};

static struct parse_cs parse_cs_[] = {
	{HDMI_COLOR_FORMAT_RGB, "rgb",},
	{HDMI_COLOR_FORMAT_444, "444",},
	{HDMI_COLOR_FORMAT_422, "422",},
	{HDMI_COLOR_FORMAT_420, "420",},
};

static struct parse_cr parse_cr_[] = {
	{HDMI_COLOR_RANGE_LIM, "limit",},
	{HDMI_COLOR_RANGE_FUL, "full",},
};

/* parse the string from "hdmitx output FORMAT" */
void hdmi_parse_attr(struct hdmi_format_para *para, char const *name)
{
	int i;

	/* parse color depth */
	for (i = 0; i < sizeof(parse_cd_) / sizeof(struct parse_cd); i++) {
		if (strstr(name, parse_cd_[i].name)) {
			para->cd = parse_cd_[i].cd;
			break;
		}
	}
	/* set default value */
	if (i == sizeof(parse_cd_) / sizeof(struct parse_cd))
		para->cd = HDMI_COLOR_DEPTH_24B;

	/* parse color space */
	for (i = 0; i < sizeof(parse_cs_) / sizeof(struct parse_cs); i++) {
		if (strstr(name, parse_cs_[i].name)) {
			para->cs = parse_cs_[i].cs;
			break;
		}
	}
	/* set default value */
	if (i == sizeof(parse_cs_) / sizeof(struct parse_cs))
		para->cs = HDMI_COLOR_FORMAT_444;

	/* parse color range */
	for (i = 0; i < sizeof(parse_cr_) / sizeof(struct parse_cr); i++) {
		if (strstr(name, parse_cr_[i].name)) {
			para->cr = parse_cr_[i].cr;
			break;
		}
	}
	/* set default value */
	if (i == sizeof(parse_cr_) / sizeof(struct parse_cr))
		para->cr = HDMI_COLOR_RANGE_FUL;
}

static void debug_hdmi_fmt_param(struct hdmi_format_para param)
{
	/* timing */
	pr_info("fmt_para.timing\n");
	pr_info("   - pixel_freq %d\n",
			param.timing.pixel_freq);
	pr_info("   - h_freq %d, v_freq %d\n",
			param.timing.h_freq, param.timing.v_freq);
	pr_info("   - hsync_polarity %d, vsync_polarity %d\n",
			param.timing.hsync_polarity,
			param.timing.vsync_polarity);
	pr_info("   - h_active %d, h_total %d\n",
			param.timing.h_active, param.timing.h_total);
	pr_info("   - h_blank %d, h_front %d, h_sync %d, h_back %d\n",
			param.timing.h_blank, param.timing.h_front,
			param.timing.h_sync, param.timing.h_back);
	pr_info("   - v_active %d, v_total %d\n",
			param.timing.v_active, param.timing.v_total);
	pr_info("   - v_blank %d, v_front %d, v_sync %d, v_back %d\n",
			param.timing.v_blank, param.timing.v_front,
			param.timing.v_sync, param.timing.v_back);
	pr_info("   - v_sync_ln %d\n", param.timing.v_sync_ln);
}

/*
 * assuming modeline information from command line is as following.
 * setenv modeline
 * "horpixels,verpixels,pixel_clock,hor_freq,ver_freq
 * ,hdisp,hsyncstart,hsyncend,htotal,vdisp,vsyncstart,vsyncend,vtotal
 * ,hsync_polarity,vsync_polarity,progress_mode"
 */
static void  hdmi_set_custombuild_timing(void)
{
	struct modeline_table tbl;
	unsigned int *buf;
	char *item = NULL;
	unsigned long temp = 0;
	int i = 0;
	const char *modeline=getenv("modeline");
	char *modeline_str = strdup(modeline);

	/* 1. parsing modeline information from command line */
	buf = (unsigned int *)&(tbl.horpixels);

	while (modeline_str != NULL) {
		item = strsep(&modeline_str, ",");
		temp = simple_strtoul(item, NULL, 10);
		*(buf + i) = temp;
		i++;
	}

	/* 2. build hdmi_format_para */
	fmt_para_custombuilt.progress_mode = tbl.progress_mode;
	fmt_para_custombuilt.tmds_clk = tbl.pixel_clock;

	/* timing */
	fmt_para_custombuilt.timing.pixel_freq = tbl.pixel_clock;
	fmt_para_custombuilt.timing.h_freq = tbl.hor_freq;
	fmt_para_custombuilt.timing.v_freq = (tbl.ver_freq * 1000);
	fmt_para_custombuilt.timing.hsync_polarity = tbl.hsync_polarity;
	fmt_para_custombuilt.timing.vsync_polarity = tbl.vsync_polarity;
	/* h_active = hdisp */
	fmt_para_custombuilt.timing.h_active = tbl.hdisp;
	/* h_total = htotal */
	fmt_para_custombuilt.timing.h_total =  tbl.htotal;
	/* h_blank = htotal - hdisp */
	fmt_para_custombuilt.timing.h_blank = tbl.htotal - tbl.hdisp;
	/* h_front = hsyncstart - hdisp */
	fmt_para_custombuilt.timing.h_front = tbl.hsyncstart - tbl.hdisp;
	/* h_sync = hsyncend - hsyncstart */
	fmt_para_custombuilt.timing.h_sync = tbl.hsyncend - tbl.hsyncstart;
	/* h_back = (h_blank - (h_front + h_sync))*/
	fmt_para_custombuilt.timing.h_back
		= fmt_para_custombuilt.timing.h_blank
		- fmt_para_custombuilt.timing.h_front
		- fmt_para_custombuilt.timing.h_sync;
	/* v_active = vdisp */
	fmt_para_custombuilt.timing.v_active = tbl.vdisp;
	/* v_total = vtotal */
	fmt_para_custombuilt.timing.v_total = tbl.vtotal;
	/* v_blank = vtotal - vdisp */
	fmt_para_custombuilt.timing.v_blank = tbl.vtotal - tbl.vdisp;
	/* v_front = vsyncstart - vdisp */
	fmt_para_custombuilt.timing.v_front = tbl.vsyncstart - tbl.vdisp;
	/* v_sync = vsyncend - vsyncstart */
	fmt_para_custombuilt.timing.v_sync = tbl.vsyncend - tbl.vsyncstart;
	/* v_back = (v_blank - (v_front + v_sync)) */
	fmt_para_custombuilt.timing.v_back
		= fmt_para_custombuilt.timing.v_blank
		- fmt_para_custombuilt.timing.v_front
		- fmt_para_custombuilt.timing.v_sync;
	fmt_para_custombuilt.timing.v_sync_ln = 1;

	/* check parameters */
	debug_hdmi_fmt_param(fmt_para_custombuilt);
}


/*
 * Paramter 'name' can be 1080p60hz, or 1920x1080p60hz
 * or 3840x2160p60hz, 2160p60hz
 * or 3840x2160p60hz420, 2160p60hz420 (Y420 mode)
 */
enum hdmi_vic hdmi_get_fmt_vic(char const *name)
{
	int i;
	char *lname;
	enum hdmi_vic vic = HDMI_unkown;
	struct hdmi_format_para *para = NULL;

	if (!name)
		return HDMI_unkown;
	for (i = 0; all_fmt_paras[i] != NULL; i++) {
		lname = all_fmt_paras[i]->name;
		if (lname && (strncmp(name, lname, strlen(lname)) == 0)) {
			vic = all_fmt_paras[i]->vic;
			break;
		}
		lname = all_fmt_paras[i]->sname;
		if (lname && (strncmp(name, lname, strlen(lname)) == 0)) {
			vic = all_fmt_paras[i]->vic;
			break;
		}
	}
	if ((vic != HDMI_unkown) && (all_fmt_paras[i] != NULL)) {
		para = all_fmt_paras[i];
		memset(&para->ext_name[0], 0, sizeof(para->ext_name));
		memcpy(&para->ext_name[0], name, strlen(name));
		hdmi_parse_attr(para, name);
	}

	if (vic == HDMIV_CUSTOMBUILT)
		hdmi_set_custombuild_timing();

	return vic;
}

struct hdmi_format_para *hdmi_match_dtd_paras(struct dtd *t)
{
	int i;

	if (!t)
		return NULL;
	for (i = 0; all_fmt_paras[i]; i++) {
		if ((abs(all_fmt_paras[i]->timing.pixel_freq / 10
		    - t->pixel_clock) <= (t->pixel_clock + 1000) / 1000) &&
		    (t->h_active == all_fmt_paras[i]->timing.h_active) &&
		    (t->h_blank == all_fmt_paras[i]->timing.h_blank) &&
		    (t->v_active == all_fmt_paras[i]->timing.v_active) &&
		    (t->v_blank == all_fmt_paras[i]->timing.v_blank) &&
		    (t->h_sync_offset == all_fmt_paras[i]->timing.h_front) &&
		    (t->h_sync == all_fmt_paras[i]->timing.h_sync) &&
		    (t->v_sync_offset == all_fmt_paras[i]->timing.v_front) &&
		    (t->v_sync == all_fmt_paras[i]->timing.v_sync)
		    )
			return all_fmt_paras[i];
	}

	return NULL;
}
