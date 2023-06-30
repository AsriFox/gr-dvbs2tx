/* -*- c++ -*- */
/*
 * Copyright 2014,2016 Ron Economos.
 * Copyright 2023 AsriFox.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DVBS2TX_LDPC_ENCODER_BB_H
#define INCLUDED_DVBS2TX_LDPC_ENCODER_BB_H

#include <gnuradio/dvbs2tx/api.h>
#include <gnuradio/dvbs2tx/dvbs2_config.h>
#include <gnuradio/tagged_stream_block.h>

namespace gr {
namespace dvbs2tx {

/*!
 * \brief Encodes a LDPC (Low-Density Parity-Check) FEC.
 * \ingroup dvbs2tx
 *
 * Input: Variable length FEC baseband frames with appended BCH (BCHFEC).
 * Output: Normal, medium or short FEC baseband frames with appended LPDC (LDPCFEC).
 */
class DVBS2TX_API ldpc_encoder_bb : virtual public gr::tagged_stream_block
{
public:
    typedef std::shared_ptr<ldpc_encoder_bb> sptr;

    /*!
     * \brief Create a baseband frame LDPC encoder.
     */
    static sptr make();
};

} // namespace dvbs2tx
} // namespace gr

#endif /* INCLUDED_DVBS2TX_LDPC_ENCODER_BB_H */
