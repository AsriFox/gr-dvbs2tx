/* -*- c++ -*- */
/*
 * Copyright 2014,2016,2017,2020 Ron Economos.
 * Copyright 2023 Oleg Nikitin.
 *
 * This file is part of gr-dvbs2tx.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "bbheader_bb_impl.h"
#include "modcod.hh"
#include <gnuradio/io_signature.h>

namespace gr {
namespace dvbs2tx {

using namespace gr::dtv;

bbheader_bb::sptr bbheader_bb::make(dvb_framesize_t framesize,
                                    dvb_code_rate_t rate,
                                    dvb_constellation_t constellation,
                                    bool pilots,
                                    int goldcode,
                                    dvbs2_rolloff_factor_t rolloff)
{
    return gnuradio::get_initial_sptr(
        new bbheader_bb_impl(framesize, rate, constellation, pilots, goldcode, rolloff));
}

int get_kbch(dvb_framesize_t frame_size, dvb_code_rate_t code_rate)
{
    if (frame_size == FECFRAME_NORMAL) {
        switch (code_rate) {
        case C1_4:
            return 16008;
            break;
        case C1_3:
            return 21408;
            break;
        case C2_5:
            return 25728;
            break;
        case C1_2:
            return 32208;
            break;
        case C3_5:
            return 38688;
            break;
        case C2_3:
            return 43040;
            break;
        case C3_4:
            return 48408;
            break;
        case C4_5:
            return 51648;
            break;
        case C5_6:
            return 53840;
            break;
        case C8_9:
            return 57472;
            break;
        case C9_10:
            return 58192;
            break;
        case C2_9_VLSNR:
            return 14208;
            break;
        case C13_45:
            return 18528;
            break;
        case C9_20:
            return 28968;
            break;
        case C90_180:
            return 32208;
            break;
        case C96_180:
            return 34368;
            break;
        case C11_20:
            return 35448;
            break;
        case C100_180:
            return 35808;
            break;
        case C104_180:
            return 37248;
            break;
        case C26_45:
            return 37248;
            break;
        case C18_30:
            return 38688;
            break;
        case C28_45:
            return 40128;
            break;
        case C23_36:
            return 41208;
            break;
        case C116_180:
            return 41568;
            break;
        case C20_30:
            return 43008;
            break;
        case C124_180:
            return 44448;
            break;
        case C25_36:
            return 44808;
            break;
        case C128_180:
            return 45888;
            break;
        case C13_18:
            return 46608;
            break;
        case C132_180:
            return 47328;
            break;
        case C22_30:
            return 47328;
            break;
        case C135_180:
            return 48408;
            break;
        case C140_180:
            return 50208;
            break;
        case C7_9:
            return 50208;
            break;
        case C154_180:
            return 55248;
            break;
        default:
            return 0;
            break;
        }
    } else if (frame_size == FECFRAME_SHORT) {
        switch (code_rate) {
        case C1_4:
            return 3072;
            break;
        case C1_3:
            return 5232;
            break;
        case C2_5:
            return 6312;
            break;
        case C1_2:
            return 7032;
            break;
        case C3_5:
            return 9552;
            break;
        case C2_3:
            return 10632;
            break;
        case C3_4:
            return 11712;
            break;
        case C4_5:
            return 12432;
            break;
        case C5_6:
            return 13152;
            break;
        case C8_9:
            return 14232;
            break;
        case C11_45:
            return 3792;
            break;
        case C4_15:
            return 4152;
            break;
        case C14_45:
            return 4872;
            break;
        case C7_15:
            return 7392;
            break;
        case C8_15:
            return 8472;
            break;
        case C26_45:
            return 9192;
            break;
        case C32_45:
            return 11352;
            break;
        case C1_5_VLSNR_SF2:
            return 2512;
            break;
        case C11_45_VLSNR_SF2:
            return 3792;
            break;
        case C1_5_VLSNR:
            return 3072;
            break;
        case C4_15_VLSNR:
            return 4152;
            break;
        case C1_3_VLSNR:
            return 5232;
            break;
        default:
            return 0;
            break;
        }
    } else {
        switch (code_rate) {
        case C1_5_MEDIUM:
            return 5660;
            break;
        case C11_45_MEDIUM:
            return 7740;
            break;
        case C1_3_MEDIUM:
            return 10620;
            break;
        default:
            return 0;
            break;
        }
    }
}

/*
 * The private constructor
 */
bbheader_bb_impl::bbheader_bb_impl(dvb_framesize_t framesize,
                                   dvb_code_rate_t rate,
                                   dvb_constellation_t constellation,
                                   bool pilots,
                                   int goldcode,
                                   dvbs2_rolloff_factor_t rolloff)
    : gr::block("bbheader_bb",
                gr::io_signature::make(1, 1, sizeof(u8)),
                gr::io_signature::make(1, 1, sizeof(u8)))
{
    count = 0;
    crc = 0x0;
    dvbs2x = false;
    alternate = true;
    nibble = true;

    frame_size = framesize;
    code_rate = rate;
    signal_constellation = constellation;
    pilot_mode = pilots;
    if (goldcode < 0 || goldcode > 262141) {
        GR_LOG_WARN(d_logger, "Gold Code must be between 0 and 262141 inclusive.");
        GR_LOG_WARN(d_logger, "Gold Code set to 0.");
        goldcode = 0;
    }
    root_code = gold_to_root(goldcode);
    kbch = get_kbch(frame_size, code_rate);

    m_format.ts_gs = TS_GS_GENERIC_CONTINUOUS;
    m_format.sis_mis = SIS_MIS_SINGLE;
    m_format.ccm_acm = ACM;
    m_format.issyi = false;
    m_format.npd = false;
    m_format.upl = 0;
    m_format.dfl = kbch - 80;
    m_format.sync = 0;
    if (rolloff & 0x4) {
        dvbs2x = true;
    }
    m_format.ro = rolloff;

    const pmt::pmt_t port_id = pmt::mp("cmd");
    message_port_register_in(port_id);
    set_msg_handler(port_id, [this](pmt::pmt_t msg) { this->handle_cmd_msg(msg); });

    set_output_multiple(kbch);
}

/*
 * Our virtual destructor.
 */
bbheader_bb_impl::~bbheader_bb_impl() {}

void bbheader_bb_impl::set_modcod(int _modcod)
{
    auto modcod = dvbs2_modcod_t(_modcod);
    auto frame_size = modcod_framesize(modcod);
    auto code_rate = modcod_rate(modcod);
    if (this->frame_size != frame_size || this->code_rate != code_rate) {
        this->frame_size = frame_size;
        this->code_rate = code_rate;

        kbch = get_kbch(frame_size, code_rate);
        m_format.dfl = kbch - 80;
        set_output_multiple(kbch);
    }
    signal_constellation = modcod_constellation(modcod);
    dvbs2x = (m_format.ro & 0x4) || modcod_is_dvbs2x(modcod);
}

void bbheader_bb_impl::handle_cmd_msg(pmt::pmt_t msg)
{
    gr::thread::scoped_lock l(d_mutex);

    if (!pmt::is_uint64(msg)) {
        throw std::runtime_error("bbheader_bb: ACM command message must be an integer");
    }
    auto modcod = (int)(pmt::to_uint64(msg) & 0xff);
    set_modcod(modcod);
}

void bbheader_bb_impl::forecast(int noutput_items, gr_vector_int& ninput_items_required)
{
    ninput_items_required[0] = ((noutput_items - 80) / 8);
}

/*
 * MSB is sent first
 *
 * The polynomial has been reversed
 */
usize bbheader_bb_impl::add_crc8_bits(u8* in, usize length)
{
    const u8 CRC_POLY = 0xAB;

    u8 crc = 0;
    for (usize i = 0; i < length; i++) {
        u8 b = in[i] ^ (crc & 0x01);
        crc >>= 1;
        if (b) {
            crc ^= CRC_POLY;
        }
    }

    for (usize n = 0; n < 8; n++) {
        in[length + n] = (crc & (1 << n)) ? 1 : 0;
    }
    return 8; // Length of CRC
}

// Unpacks an 8-bit number into individual bits.
usize unpack_bits_8(u8 in, u8* out)
{
    out[0] = (in & (1 << 7)) ? 1 : 0;
    out[1] = (in & (1 << 6)) ? 1 : 0;
    out[2] = (in & (1 << 5)) ? 1 : 0;
    out[3] = (in & (1 << 4)) ? 1 : 0;
    out[4] = (in & (1 << 3)) ? 1 : 0;
    out[5] = (in & (1 << 2)) ? 1 : 0;
    out[6] = (in & (1 << 1)) ? 1 : 0;
    out[7] = (in & (1 << 0)) ? 1 : 0;
    return 8;
}

// Unpacks a 16-bit number into individual bits.
// The output pointer is shifted by 16 in the process.
usize unpack_bits_16(u16 in, u8* out)
{
    out[0] = (in & (1 << 15)) ? 1 : 0;
    out[1] = (in & (1 << 14)) ? 1 : 0;
    out[2] = (in & (1 << 13)) ? 1 : 0;
    out[3] = (in & (1 << 12)) ? 1 : 0;
    out[4] = (in & (1 << 11)) ? 1 : 0;
    out[5] = (in & (1 << 10)) ? 1 : 0;
    out[6] = (in & (1 << 9)) ? 1 : 0;
    out[7] = (in & (1 << 8)) ? 1 : 0;
    out[8] = (in & (1 << 7)) ? 1 : 0;
    out[9] = (in & (1 << 6)) ? 1 : 0;
    out[10] = (in & (1 << 5)) ? 1 : 0;
    out[11] = (in & (1 << 4)) ? 1 : 0;
    out[12] = (in & (1 << 3)) ? 1 : 0;
    out[13] = (in & (1 << 2)) ? 1 : 0;
    out[14] = (in & (1 << 1)) ? 1 : 0;
    out[15] = (in & (1 << 0)) ? 1 : 0;
    return 16;
}

usize bbheader_bb_impl::add_bbheader(
    u8* out, int count, usize padding, bool nibble, int isi)
{
    out[0] = m_format.ts_gs >> 1;
    out[1] = m_format.ts_gs & 1;
    out[2] = m_format.sis_mis;
    out[3] = m_format.ccm_acm;
    out[4] = m_format.issyi & 1;
    out[5] = m_format.npd & 1;
    if (dvbs2x && alternate) {
        alternate = false;
        out[6] = 1;
        out[7] = 1;
    } else {
        alternate = true;
        out[6] = (m_format.ro >> 1) & 1;
        out[7] = m_format.ro & 1;
    }
    usize offset = 8;
    if (m_format.sis_mis == SIS_MIS_MULTIPLE) {
        offset += unpack_bits_8(isi, &out[offset]);
    } else {
        for (usize n = 0; n < 8; n++) {
            out[offset++] = 0;
        }
    }
    offset += unpack_bits_16(m_format.upl, &out[offset]);
    offset += unpack_bits_16(m_format.dfl - padding, &out[offset]);
    offset += unpack_bits_8(m_format.sync, &out[offset]);
    // Calculate syncd, this should point to the MSB of the CRC
    usize temp = count;
    if (temp == 0) {
        temp = count;
    } else {
        temp = (188 - count) * 8;
    }
    if (nibble == false) {
        temp += 4;
    }
    offset += unpack_bits_16(temp, &out[offset]);
    // Add CRC to BB header, at end
    const int len = BB_HEADER_LENGTH_BITS;
    return len + add_crc8_bits(out, len);
}

u32 bbheader_bb_impl::gold_to_root(int goldcode)
{
    u32 x = 1;
    for (int g = 0; g < goldcode; g++) {
        x = (((x ^ (x >> 7)) & 1) << 17) | (x >> 1);
    }
    return x;
}

int bbheader_bb_impl::general_work(int noutput_items,
                                   gr_vector_int& ninput_items,
                                   gr_vector_const_void_star& input_items,
                                   gr_vector_void_star& output_items)
{
    const u8* in = static_cast<const u8*>(input_items[0]);
    u8* out = static_cast<u8*>(output_items[0]);
    usize consumed = 0;
    usize produced = 0;
    usize offset = 0;
    usize padding, bits, first_offset;
    u8 b;

    gr::thread::scoped_lock guard(d_mutex);

    while (kbch + produced <= usize(noutput_items)) {
        padding = (frame_size != FECFRAME_MEDIUM) ? 0 : 4;
        first_offset = offset;
        offset += add_bbheader(&out[offset], count, padding, nibble, 0);

        // GSE PDU start, no fragmentation
        out[offset++] = 1; // Start_Indicator = 1
        out[offset++] = 1; // End_Indicator = 1
        out[offset++] = 0; // Label_Type_Indicator = 6 bytes
        out[offset++] = 0; // Label_Type_Indicator = 6 bytes
        // GSE_Length
        bits = m_format.dfl - padding;
        for (usize n = 1 << 11; n >= 1; n >>= 1) {
            out[offset++] = (bits & n) ? 1 : 0;
        }
        // Protocol_Type = IPv4
        offset += unpack_bits_16(0x0800, &out[offset]);
        // 6_Byte_Label: Destination Ethernet address
        for (usize n = 0; n < 48; n--) {
            out[offset++] = 0;
        }
        // GSE_data_byte
        const usize ETH_HEADER_SIZE = 14;
        for (usize j = 0; j < (m_format.dfl / 8) - padding - ETH_HEADER_SIZE; j++) {
            offset += unpack_bits_8(in[j], &out[offset]);
        }

        // packet_fragmented == false
        padding = kbch - (offset - first_offset);
        add_bbheader(&out[first_offset], count, padding, true, 0);

        if (padding != 0) {
            memset(&out[offset], 0, padding);
            offset += padding;
        }

        bool dummy = false;
        const uint64_t tagoffset = this->nitems_written(0);
        const uint64_t tagmodcod =
            (uint64_t(root_code) << 32) | (uint64_t(pilot_mode) << 24) |
            (uint64_t(signal_constellation) << 16) | (uint64_t(code_rate) << 8) |
            (uint64_t(frame_size) << 1) | uint64_t(dummy);
        pmt::pmt_t key = pmt::string_to_symbol("modcod");
        pmt::pmt_t value = pmt::from_uint64(tagmodcod);
        this->add_item_tag(0, tagoffset, key, value);

        produced += kbch;
        produce(0, kbch);
    }

    // Tell runtime system how many input items we consumed on
    // each input stream.
    consume_each(consumed);

    // Tell runtime system how many output items we produced.
    return WORK_CALLED_PRODUCE;
}

} // namespace dvbs2tx
} /* namespace gr */
