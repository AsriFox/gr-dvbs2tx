/* -*- c++ -*- */
/*
 * Copyright 2014,2016,2017,2020 Ron Economos.
 * Copyright 2023 AsriFox.
 *
 * This file is part of gr-dvbs2tx.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DVBS2TX_MODCOD_TAG_H
#define INCLUDED_DVBS2TX_MODCOD_TAG_H

#include <gnuradio/dvbs2tx/dvbs2_config.h>
#include <gnuradio/tags.h>

namespace gr {
namespace dvbs2tx {

struct ModcodTag {
    bool dummy;
    dvb_framesize_t framesize;
    dvb_code_rate_t code_rate;
    dvb_constellation_t constellation;
    bool pilots;
    u32 root_code;
};

inline ModcodTag from_pmt(pmt::pmt_t value)
{
    auto tagmodcod = pmt::to_uint64(value);
    return ModcodTag{
        bool(tagmodcod & 0x1),
        dvb_framesize_t((tagmodcod >> 1) & 0x7f),
        dvb_code_rate_t((tagmodcod >> 8) & 0xff),
        dvb_constellation_t((tagmodcod >> 16) & 0xff),
        bool((tagmodcod >> 24) & 0x1),
        u32((tagmodcod >> 32) & 0xffffffff),
    };
}

inline pmt::pmt_t to_pmt(ModcodTag mt)
{
    auto tagmodcod = (uint64_t(mt.root_code) << 32) | (uint64_t(mt.pilots) << 24) |
                     (uint64_t(mt.constellation) << 16) | (uint64_t(mt.code_rate) << 8) |
                     (uint64_t(mt.framesize) << 1) | uint64_t(mt.dummy);
    return pmt::from_uint64(tagmodcod);
}

} // namespace dvbs2tx
} // namespace gr

#endif /* INCLUDED_DVBS2TX_MODCOD_H */