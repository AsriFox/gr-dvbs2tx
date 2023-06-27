/* -*- c++ -*- */
/*
 * Copyright 2014,2016 Ron Economos.
 * Copyright 2023 AsriFox.
 *
 * This file is part of gr-dvbs2tx.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DVBS2TX_BBSCRAMBLER_BB_H
#define INCLUDED_DVBS2TX_BBSCRAMBLER_BB_H

#include <gnuradio/dvbs2tx/api.h>
#include <gnuradio/dvbs2tx/dvbs2_config.h>
#include <gnuradio/tagged_stream_block.h>

namespace gr {
namespace dvbs2tx {

/*!
 * \brief Scrambles FEC baseband frames with a PRBS encoder.
 * \ingroup dvbs2tx
 *
 * \details
 * Input: Variable length FEC baseband frames (BBFRAME).
 * Output: Scrambled variable length FEC baseband frames (BBFRAME).
 */
class DVBS2TX_API bbscrambler_bb : virtual public gr::tagged_stream_block
{
public:
    typedef std::shared_ptr<bbscrambler_bb> sptr;

    /*!
     * \brief Create a baseband frame scrambler.
     */
    static sptr make();
};

} // namespace dvbs2tx
} // namespace gr

#endif /* INCLUDED_DVBS2TX_BBSCRAMBLER_BB_H */
