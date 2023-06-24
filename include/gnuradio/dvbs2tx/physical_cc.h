/* -*- c++ -*- */
/*
 * Copyright 2014,2016,2017 Ron Economos.
 * Copyright 2023 Oleg Nikitin.
 *
 * This file is part of gr-dvbs2tx.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DVBS2TX_PHYSICAL_CC_H
#define INCLUDED_DVBS2TX_PHYSICAL_CC_H

#include <gnuradio/block.h>
#include <gnuradio/dvbs2tx/api.h>
#include <gnuradio/dvbs2tx/dvbs2_config.h>

namespace gr {
namespace dvbs2tx {

/*!
 * \brief Signals DVB-S2 physical layer frames.
 * \ingroup dvbs2tx
 *
 * Input: QPSK, 8PSK, 16APSK or 32APSK modulated complex IQ values (XFECFRAME).
 * Output: DVB-S2 PLFRAME.
 */
class DVBS2TX_API physical_cc : virtual public gr::block
{
public:
    typedef std::shared_ptr<physical_cc> sptr;

    /*!
     * \brief Create a DVB-S2 physical layer framer.
     *
     * \param dummyframes Enable dummy frames.
     */
    static sptr make(bool dummyframes);
};

} // namespace dvbs2tx
} // namespace gr

#endif /* INCLUDED_DVBS2TX_PHYSICAL_CC_H */
