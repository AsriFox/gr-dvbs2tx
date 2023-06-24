/* -*- c++ -*- */
/*
 * Copyright 2014,2016,2017 Ron Economos.
 * Copyright 2023 Oleg Nikitin.
 *
 * This file is part of gr-dvbs2tx.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DVBS2TX_CONFIG_H
#define INCLUDED_DVBS2TX_CONFIG_H

#include <gnuradio/dtv/dvb_config.h>
#include <gnuradio/dtv/dvbs2_config.h>
#include <gnuradio/dvbs2tx/rusty_types.h>

// BCH Code
#define BCH_CODE_N8 0
#define BCH_CODE_N10 1
#define BCH_CODE_N12 2
#define BCH_CODE_S12 3
#define BCH_CODE_M12 4

#define VLSNR_OFF 0
#define VLSNR_SET1 1
#define VLSNR_SET2 2

namespace gr {
namespace dvbs2tx {

const usize BB_HEADER_LENGTH_BITS = 72;

enum dvb_bb_ts_gs_t : u8 {
    TS_GS_GENERIC_PACKETIZED = 0,
    TS_GS_GENERIC_CONTINUOUS = 1,
    TS_GS_RESERVED = 2,
    TS_GS_TRANSPORT = 3,
};

enum dvb_bb_sis_mis_t : u8 {
    SIS_MIS_SINGLE = 1,
    SIS_MIS_MULTIPLE = 0,
};

enum dvb_bb_ccm_acm_t : u8 {
    CCM = 1,
    ACM = 0,
};

const usize FRAME_SIZE_NORMAL = 64800;
const usize FRAME_SIZE_MEDIUM = 32400;
const usize FRAME_SIZE_SHORT = 16200;

const usize LDPC_ENCODE_TABLE_LENGTH = FRAME_SIZE_NORMAL * 10;

const usize NORMAL_PUNCTURING = 3240;
const usize MEDIUM_PUNCTURING = 1620;
const usize SHORT_PUNCTURING_SET1 = 810;
const usize SHORT_PUNCTURING_SET2 = 1224;

const usize EXTRA_PILOT_SYMBOLS_SET1 = (18 * 34) + (3 * 36);
const usize EXTRA_PILOT_SYMBOLS_SET2 = (9 * 32) + 36;

} // namespace dvbs2tx
} // namespace gr


#endif /* INCLUDED_DVBS2TX_CONFIG_H */
