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
     * \param framesize FEC frame size (normal, medium or short).
     * \param rate FEC code rate.
     * \param constellation DVB-S2 constellation.
     * \param pilots pilot symbols (on/off).
     * \param goldcode physical layer scrambler Gold code (0 to 262141 inclusive).
     * \param rolloff DVB-S2 root-raised-cosine filter roll-off.
     */
    static sptr make(dvb_framesize_t framesize,
                     dvb_code_rate_t rate,
                     dvb_constellation_t constellation,
                     bool pilots,
                     int goldcode,
                     dvbs2_rolloff_factor_t rolloff);

    virtual void set_modcod(int modcod) = 0;
};

} // namespace dvbs2tx
} // namespace gr

#endif /* INCLUDED_DVBS2TX_BBHEADER_BB_H */
