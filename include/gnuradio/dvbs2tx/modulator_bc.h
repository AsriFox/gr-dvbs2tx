/* -*- c++ -*- */
/*
 * Copyright 2014,2016 Ron Economos.
 * Copyright 2023 Oleg Nikitin.
 *
 * This file is part of gr-dvbs2tx.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DVBS2TX_MODULATOR_BC_H
#define INCLUDED_DVBS2TX_MODULATOR_BC_H

#include <gnuradio/block.h>
#include <gnuradio/dvbs2tx/api.h>
#include <gnuradio/dvbs2tx/dvbs2_config.h>

namespace gr {
namespace dvbs2tx {

/*!
 * \brief Modulates DVB-S2 frames.
 * \ingroup dvbs2tx
 *
 * Input: Bit interleaved baseband frames.
 * Output: QPSK, 8PSK, 16APSK or 32APSK modulated complex IQ values (XFECFRAME).
 */
class DVBS2TX_API modulator_bc : virtual public gr::block
{
public:
    typedef std::shared_ptr<modulator_bc> sptr;

    /*!
     * \brief Create a DVB-S2 constellation modulator.
     */
    static sptr make();
};

} // namespace dvbs2tx
} // namespace gr

#endif /* INCLUDED_DVBS2TX_MODULATOR_BC_H */
