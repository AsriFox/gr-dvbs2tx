/* -*- c++ -*- */
/*
 * Copyright 2023 AsriFox.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DVBS2TX_TX_HIER_H
#define INCLUDED_DVBS2TX_TX_HIER_H

#include <gnuradio/dvbs2tx/api.h>
#include <gnuradio/dvbs2tx/dvbs2_config.h>
#include <gnuradio/hier_block2.h>

namespace gr {
namespace dvbs2tx {

/*!
 * \brief DVB-S2 Transmitter stack
 * \ingroup dvbs2tx
 *
 * \details
 * Input: Information stream (bytes).
 * Output: DVB-S2 Physical Layer Frames (PLFRAME) (sequences of complex samples).
 */
class DVBS2TX_API tx_hier : virtual public gr::hier_block2
{
public:
    typedef std::shared_ptr<tx_hier> sptr;

    /*!
     * \brief Create a DVB-S2 Transmitter.
     *
     * \param framesize FEC frame size (normal, medium or short).
     * \param rate FEC code rate.
     * \param constellation DVB-S2 constellation.
     * \param pilots pilot symbols (on/off).
     * \param goldcode physical layer scrambler Gold code (0 to 262141 inclusive).
     * \param rolloff DVB-S2 root-raised-cosine filter roll-off.
     * \param dummyframes Enable dummy frames.
     */
    static sptr make(dvb_framesize_t framesize,
                     dvb_code_rate_t rate,
                     dvb_constellation_t constellation,
                     bool pilots,
                     int goldcode,
                     dvbs2_rolloff_factor_t rolloff,
                     bool dummyframes);
};

} // namespace dvbs2tx
} // namespace gr

#endif /* INCLUDED_DVBS2TX_TX_HIER_H */
