/* -*- c++ -*- */
/*
 * Copyright 2023 AsriFox.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DVBS2TX_TX_HIER_IMPL_H
#define INCLUDED_DVBS2TX_TX_HIER_IMPL_H

#include <gnuradio/dvbs2tx/bbheader_bb.h>
#include <gnuradio/dvbs2tx/bbscrambler_bb.h>
#include <gnuradio/dvbs2tx/bch_bb.h>
#include <gnuradio/dvbs2tx/interleaver_bb.h>
#include <gnuradio/dvbs2tx/ldpc_bb.h>
#include <gnuradio/dvbs2tx/modulator_bc.h>
#include <gnuradio/dvbs2tx/physical_cc.h>
#include <gnuradio/dvbs2tx/tx_hier.h>

namespace gr {
namespace dvbs2tx {

class tx_hier_impl : public tx_hier
{
private:
    bbheader_bb::sptr bbheader;
    bbscrambler_bb::sptr bbscrambler;
    bch_bb::sptr bch_encoder;
    ldpc_bb::sptr ldpc_encoder;
    interleaver_bb::sptr interleaver;
    modulator_bc::sptr modulator;
    physical_cc::sptr pl_framer;

public:
    tx_hier_impl(dvb_framesize_t,
                 dvb_code_rate_t,
                 dvb_constellation_t,
                 bool pilots,
                 int goldcode,
                 dvbs2_rolloff_factor_t,
                 bool dummyframes);
    ~tx_hier_impl();
};

} // namespace dvbs2tx
} // namespace gr

#endif /* INCLUDED_DVBS2TX_TX_HIER_IMPL_H */
