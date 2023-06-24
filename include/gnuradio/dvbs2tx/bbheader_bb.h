/* -*- c++ -*- */
/*
 * Copyright 2014,2016 Ron Economos.
 * Copyright 2023 Oleg Nikitin.
 *
 * This file is part of gr-dvbs2tx.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DVBS2TX_BBHEADER_BB_H
#define INCLUDED_DVBS2TX_BBHEADER_BB_H

#include <gnuradio/block.h>
#include <gnuradio/dvbs2tx/api.h>
#include <gnuradio/dvbs2tx/dvbs2_config.h>

namespace gr {
namespace dvbs2tx {

/*!
 * \brief Formats MPEG-2 Transport Stream packets into FEC baseband frames
 * and adds a 10-byte header.
 * \ingroup dvbs2tx
 *
 * \details
 * Input: 188-byte MPEG-2 Transport Stream packets.
 * Output: Variable length FEC baseband frames (BBFRAME). The output frame
 *         length is based on the FEC rate.
 */
class DVBS2TX_API bbheader_bb : virtual public gr::block
{
public:
    typedef std::shared_ptr<bbheader_bb> sptr;

    /*!
     * \brief Create a baseband header formatter.
     *
     * \param nstreams number of streams (1-4).
     * \param framesize1 FEC frame size (normal, medium or short).
     * \param rate1 FEC code rate.
     * \param constellation1 DVB-S2 constellation.
     * \param pilots1 pilot symbols (on/off).
     * \param goldcode1 physical layer scrambler Gold code (0 to 262141
     * inclusive). \param framesize2 FEC frame size (normal, medium or short).
     * \param rate2 FEC code rate.
     * \param constellation2 DVB-S2 constellation.
     * \param pilots2 pilot symbols (on/off).
     * \param goldcode2 physical layer scrambler Gold code (0 to 262141
     * inclusive). \param framesize3 FEC frame size (normal, medium or short).
     * \param rate3 FEC code rate.
     * \param constellation3 DVB-S2 constellation.
     * \param pilots3 pilot symbols (on/off).
     * \param goldcode3 physical layer scrambler Gold code (0 to 262141
     * inclusive). \param framesize4 FEC frame size (normal, medium or short).
     * \param rate4 FEC code rate.
     * \param constellation4 DVB-S2 constellation.
     * \param pilots4 pilot symbols (on/off).
     * \param goldcode4 physical layer scrambler Gold code (0 to 262141
     * inclusive). \param rolloff DVB-S2 root-raised-cosine filter roll-off.
     */
    static sptr make(int nstreams,
                     dvbs2_framesize_t framesize1,
                     dvbs2_code_rate_t rate1,
                     dvbs2_constellation_t constellation1,
                     dvbs2_pilots_t pilots1,
                     int goldcode1,
                     dvbs2_framesize_t framesize2,
                     dvbs2_code_rate_t rate2,
                     dvbs2_constellation_t constellation2,
                     dvbs2_pilots_t pilots2,
                     int goldcode2,
                     dvbs2_framesize_t framesize3,
                     dvbs2_code_rate_t rate3,
                     dvbs2_constellation_t constellation3,
                     dvbs2_pilots_t pilots3,
                     int goldcode3,
                     dvbs2_framesize_t framesize4,
                     dvbs2_code_rate_t rate4,
                     dvbs2_constellation_t constellation4,
                     dvbs2_pilots_t pilots4,
                     int goldcode4,
                     dvbs2_rolloff_factor_t rolloff);
};

} // namespace dvbs2tx
} // namespace gr

#endif /* INCLUDED_DVBS2TX_BBHEADER_BB_H */
