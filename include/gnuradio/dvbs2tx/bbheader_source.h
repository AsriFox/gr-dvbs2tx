/* -*- c++ -*- */
/*
 * Copyright 2017 Ron Economos.
 * Copyright 2023 Oleg Nikitin.
 *
 * This file is part of gr-dvbs2tx.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DVBS2TX_BBHEADER_SOURCE_H
#define INCLUDED_DVBS2TX_BBHEADER_SOURCE_H

#include <gnuradio/dvbs2tx/api.h>
#include <gnuradio/dvbs2tx/dvbs2_config.h>
#include <gnuradio/sync_block.h>

namespace gr {
namespace dvbs2tx {

/*!
 * \brief Formats IP packets into FEC baseband frames and adds a 10-byte
 * header.
 * \ingroup dvbs2tx
 *
 * \details
 * Input: IP packets (through PCAP).
 * Output: Variable length FEC baseband frames (BBFRAME). The output frame
 *         length is based on the FEC rate.
 */
class DVBS2TX_API bbheader_source : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<bbheader_source> sptr;

    /*!
     * \brief Create a GSE baseband header formatter.
     *
     * \param nstreams number of streams (1-4).
     * \param framesize1 FEC frame size (normal, medium or short).
     * \param rate1 FEC code rate.
     * \param constellation1 DVB-S2 constellation.
     * \param pilots1 pilot symbols (on/off).
     * \param goldcode1 physical layer scrambler Gold code (0 to 262141
     * inclusive). \param mac_address1 MAC address of IP interface. \param
     * framesize2 FEC frame size (normal, medium or short). \param rate2 FEC code
     * rate. \param constellation2 DVB-S2 constellation. \param pilots2 pilot
     * symbols (on/off). \param goldcode2 physical layer scrambler Gold code (0 to
     * 262141 inclusive). \param mac_address2 MAC address of IP interface. \param
     * framesize3 FEC frame size (normal, medium or short). \param rate3 FEC code
     * rate. \param constellation3 DVB-S2 constellation. \param pilots3 pilot
     * symbols (on/off). \param goldcode3 physical layer scrambler Gold code (0 to
     * 262141 inclusive). \param mac_address3 MAC address of IP interface. \param
     * framesize4 FEC frame size (normal, medium or short). \param rate4 FEC code
     * rate. \param constellation4 DVB-S2 constellation. \param pilots4 pilot
     * symbols (on/off). \param goldcode4 physical layer scrambler Gold code (0 to
     * 262141 inclusive). \param mac_address4 MAC address of IP interface. \param
     * rolloff DVB-S2 root-raised-cosine filter roll-off. \param ping_reply ping
     * reply mode (on/off). \param ipaddr_spoof IP address spoofing (on/off).
     * \param dst_address destination address for IP spoofing.
     */
    static sptr make(int nstreams,
                     dvbs2_framesize_t framesize1,
                     dvbs2_code_rate_t rate1,
                     dvbs2_constellation_t constellation1,
                     dvbs2_pilots_t pilots1,
                     int goldcode1,
                     char* mac_address1,
                     dvbs2_framesize_t framesize2,
                     dvbs2_code_rate_t rate2,
                     dvbs2_constellation_t constellation2,
                     dvbs2_pilots_t pilots2,
                     int goldcode2,
                     char* mac_address2,
                     dvbs2_framesize_t framesize3,
                     dvbs2_code_rate_t rate3,
                     dvbs2_constellation_t constellation3,
                     dvbs2_pilots_t pilots3,
                     int goldcode3,
                     char* mac_address3,
                     dvbs2_framesize_t framesize4,
                     dvbs2_code_rate_t rate4,
                     dvbs2_constellation_t constellation4,
                     dvbs2_pilots_t pilots4,
                     int goldcode4,
                     char* mac_address4,
                     dvbs2_rolloff_factor_t rolloff,
                     dvbs2_ping_reply_t ping_reply,
                     dvbs2_ipaddr_spoof_t ipaddr_spoof,
                     char* dst_address);
};

} // namespace dvbs2tx
} // namespace gr

#endif /* INCLUDED_DVBS2TX_BBHEADER_SOURCE_H */
