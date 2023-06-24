/* -*- c++ -*- */
/*
 * Copyright 2014,2016 Ron Economos.
 * Copyright 2023 Oleg Nikitin.
 *
 * This file is part of gr-dvbs2tx.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DVBS2TX_INTERLEAVER_BB_H
#define INCLUDED_DVBS2TX_INTERLEAVER_BB_H

#include <gnuradio/block.h>
#include <gnuradio/dvbs2tx/api.h>
#include <gnuradio/dvbs2tx/dvbs2_config.h>

namespace gr {
namespace dvbs2tx {

/*!
 * \brief Bit interleaves DVB-S2 FEC baseband frames.
 * \ingroup dvbs2tx
 *
 * Input: Normal or short FEC baseband frames with appended LPDC (LDPCFEC).
 * Output: Bit interleaved baseband frames.
 */
class DVBS2TX_API interleaver_bb : virtual public gr::block
{
public:
    typedef std::shared_ptr<interleaver_bb> sptr;

    /*!
     * \brief Create a DVB-S2 bit interleaver.
     */
    static sptr make();
};

} // namespace dvbs2tx
} // namespace gr

#endif /* INCLUDED_DVBS2TX_INTERLEAVER_BB_H */
