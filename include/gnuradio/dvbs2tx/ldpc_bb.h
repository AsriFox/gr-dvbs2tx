/* -*- c++ -*- */
/*
 * Copyright 2014,2016 Ron Economos.
 * Copyright 2023 Oleg Nikitin.
 *
 * This file is part of gr-dvbs2tx.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DVBS2TX_LDPC_BB_H
#define INCLUDED_DVBS2TX_LDPC_BB_H

#include <gnuradio/block.h>
#include <gnuradio/dvbs2tx/api.h>
#include <gnuradio/dvbs2tx/dvbs2_config.h>

namespace gr {
namespace dvbs2tx {

/*!
 * \brief Encodes a LDPC (Low-Density Parity-Check) FEC.
 * \ingroup dvbs2tx
 *
 * Input: Variable length FEC baseband frames with appended BCH (BCHFEC).
 * Output: Normal, medium or short FEC baseband frames with appended LPDC
 * (LDPCFEC).
 */
class DVBS2TX_API ldpc_bb : virtual public gr::block
{
public:
    typedef std::shared_ptr<ldpc_bb> sptr;

    /*!
     * \brief Create a baseband frame LDPC encoder.
     */
    static sptr make();
};

} // namespace dvbs2tx
} // namespace gr

#endif /* INCLUDED_DVBS2TX_LDPC_BB_H */
