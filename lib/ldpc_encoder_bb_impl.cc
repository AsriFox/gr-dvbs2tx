/* -*- c++ -*- */
/*
 * Copyright 2014,2016,2017,2020 Ron Economos.
 * Copyright 2023 AsriFox.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "ldpc_encoder_bb_impl.h"
#include "modcod_tag.hh"
#include <gnuradio/io_signature.h>

namespace gr {
namespace dvbs2tx {

ldpc_encoder_bb::sptr ldpc_encoder_bb::make()
{
    return gnuradio::make_block_sptr<ldpc_encoder_bb_impl>();
}


/*
 * The private constructor
 */
ldpc_encoder_bb_impl::ldpc_encoder_bb_impl()
    : gr::tagged_stream_block("ldpc_encoder_bb",
                              gr::io_signature::make(1, 1, sizeof(u8)),
                              gr::io_signature::make(1, 1, sizeof(u8)),
                              "modcod")
{
    set_min_output_buffer(FRAME_SIZE_NORMAL);
    set_tag_propagation_policy(TPP_ALL_TO_ALL);
}

/*
 * Our virtual destructor.
 */
ldpc_encoder_bb_impl::~ldpc_encoder_bb_impl() {}

void ldpc_encoder_bb_impl::parse_length_tags(const std::vector<std::vector<tag_t>>& tags,
                                             gr_vector_int& n_input_items_reqd)
{
    n_input_items_reqd[0] = 0;
    for (tag_t tag : tags[0]) {
        if (pmt::symbol_to_string(tag.key) == "modcod") {
            auto mt = from_pmt(tag.value);
            enc = ldpc_encoder::select(mt.framesize, mt.code_rate);
            n_input_items_reqd[0] = (enc != nullptr) ? enc->nbch : 0;
            break;
        }
    }
}

int ldpc_encoder_bb_impl::calculate_output_stream_length(
    const gr_vector_int& ninput_items)
{
    return (enc != nullptr) ? (ninput_items[0] / enc->nbch * enc->frame_size) : 0;
}


int ldpc_encoder_bb_impl::work(int noutput_items,
                               gr_vector_int& ninput_items,
                               gr_vector_const_void_star& input_items,
                               gr_vector_void_star& output_items)
{
    if (enc == nullptr || ninput_items[0] == 0 || noutput_items == 0) {
        return 0;
    }
    auto in = static_cast<const u8*>(input_items[0]);
    auto out = static_cast<u8*>(output_items[0]);

    // Pad the input data inside the shortening buffer
    if (enc->shortening != 0) {
        std::memset(&shortening_buffer[0], 0, sizeof(u8) * enc->shortening);
        std::memcpy(&shortening_buffer[enc->shortening], in, sizeof(u8) * enc->nbch);
        in = static_cast<const u8*>(shortening_buffer);
    }

    // Set up a puncturing buffer
    usize plen = enc->frame_size + enc->puncturing - enc->nbch;
    u8* parity_buffer =
        (enc->puncturing_period != 0) ? &puncturing_buffer[enc->nbch] : &out[enc->nbch];
    out += enc->nbch;

    enc->calculate_parity_bits(in, parity_buffer);

    enc->puncture_parity_bits(parity_buffer, out);

    // Do inner parity calculations
    for (usize j = 1; j < plen - enc->puncturing; j++) {
        out[j] ^= out[j - 1];
    }

    return enc->frame_size;
}

void ldpc_encoder::puncture_parity_bits(u8* parity_buffer, u8* parity_out) const
{
    usize plen = frame_size + puncturing - nbch;
    // Do the puncturing
    if (puncturing_period != 0) {
        for (usize j = 0, pj = 0; j < plen / puncturing_period && pj < puncturing;
             j++, pj++) {
            std::memcpy(&parity_out[j * (puncturing_period - 1)],
                        &parity_buffer[j * puncturing_period],
                        puncturing_period - 1);
            // for (usize k = 1; k < puncturing_period; k++) {
            //     out[j * (puncturing_period - 1) + k - 1] = in[j * puncturing_period +
            //     k];
            // }
        }
    }
}

void ldpc_encoder::calculate_parity_bits(const u8* data_buffer, u8* parity_buffer) const
{
    usize plen = frame_size + puncturing - nbch;
    // Do the parity checking
    std::memset(parity_buffer, 0, sizeof(u8) * plen);
    for (usize row = 0; row < table.size(); row++) {
        for (usize n = 0; n < 360; n++) {
            usize d = row * 360 + n;
            for (u16 t : table[row]) {
                usize p = (t + n * q) % plen;
                parity_buffer[p] ^= data_buffer[d];
            }
        }
    }
}

ldpc_encoder::uptr ldpc_encoder::select(dvb_framesize_t framesize, dvb_code_rate_t rate)
{
    using namespace gr::dtv;
    switch (framesize) {
    case FECFRAME_NORMAL:
        switch (rate) {
        case C1_4:
            return uptr(&ldpc_tab_1_4N);
        case C1_3:
            return uptr(&ldpc_tab_1_3N);
        case C2_5:
            return uptr(&ldpc_tab_2_5N);
        case C1_2:
            return uptr(&ldpc_tab_1_2N);
        case C3_5:
            return uptr(&ldpc_tab_3_5N);
        case C2_3:
            return uptr(&ldpc_tab_2_3N);
        case C3_4:
            return uptr(&ldpc_tab_3_4N);
        case C4_5:
            return uptr(&ldpc_tab_4_5N);
        case C5_6:
            return uptr(&ldpc_tab_5_6N);
        case C8_9:
            return uptr(&ldpc_tab_8_9N);
        case C9_10:
            return uptr(&ldpc_tab_9_10N);
        case C13_45:
            return uptr(&ldpc_tab_13_45N);
        case C9_20:
            return uptr(&ldpc_tab_9_20N);
        case C90_180:
            return uptr(&ldpc_tab_90_180N);
        case C96_180:
            return uptr(&ldpc_tab_96_180N);
        case C11_20:
            return uptr(&ldpc_tab_11_20N);
        case C100_180:
            return uptr(&ldpc_tab_100_180N);
        case C104_180:
            return uptr(&ldpc_tab_104_180N);
        case C26_45:
            return uptr(&ldpc_tab_26_45N);
        case C18_30:
            return uptr(&ldpc_tab_18_30N);
        case C28_45:
            return uptr(&ldpc_tab_28_45N);
        case C23_36:
            return uptr(&ldpc_tab_23_36N);
        case C116_180:
            return uptr(&ldpc_tab_116_180N);
        case C20_30:
            return uptr(&ldpc_tab_20_30N);
        case C124_180:
            return uptr(&ldpc_tab_124_180N);
        case C25_36:
            return uptr(&ldpc_tab_25_36N);
        case C128_180:
            return uptr(&ldpc_tab_128_180N);
        case C13_18:
            return uptr(&ldpc_tab_13_18N);
        case C132_180:
            return uptr(&ldpc_tab_132_180N);
        case C22_30:
            return uptr(&ldpc_tab_22_30N);
        case C135_180:
            return uptr(&ldpc_tab_135_180N);
        case C140_180:
            return uptr(&ldpc_tab_140_180N);
        case C7_9:
            return uptr(&ldpc_tab_7_9N);
        case C154_180:
            return uptr(&ldpc_tab_154_180N);
        case C2_9_VLSNR:
            return uptr(&ldpc_tab_VLSNR_2_9N);
        default:
            break;
        }
        break;
    case FECFRAME_SHORT:
        switch (rate) {
        case C1_4:
            return uptr(&ldpc_tab_1_4S);
        case C1_3:
            return uptr(&ldpc_tab_1_3S);
        case C2_5:
            return uptr(&ldpc_tab_2_5S);
        case C1_2:
            return uptr(&ldpc_tab_1_2S);
        case C3_5:
            return uptr(&ldpc_tab_3_5S);
        case C2_3:
            return uptr(&ldpc_tab_2_3S);
        case C3_4:
            return uptr(&ldpc_tab_3_4S);
        case C4_5:
            return uptr(&ldpc_tab_4_5S);
        case C5_6:
            return uptr(&ldpc_tab_5_6S);
        case C8_9:
            return uptr(&ldpc_tab_8_9S);
        case C11_45:
            return uptr(&ldpc_tab_11_45S);
        case C4_15:
            return uptr(&ldpc_tab_4_15S);
        case C14_45:
            return uptr(&ldpc_tab_14_45S);
        case C7_15:
            return uptr(&ldpc_tab_7_15S);
        case C8_15:
            return uptr(&ldpc_tab_8_15S);
        case C26_45:
            return uptr(&ldpc_tab_26_45S);
        case C32_45:
            return uptr(&ldpc_tab_32_45S);
        case C1_5_VLSNR_SF2:
            return uptr(&ldpc_tab_VLSNR_1_5SF2);
        case C11_45_VLSNR_SF2:
            return uptr(&ldpc_tab_VLSNR_11_45SF2);
        case C1_5_VLSNR:
            return uptr(&ldpc_tab_VLSNR_1_5S);
        case C4_15_VLSNR:
            return uptr(&ldpc_tab_VLSNR_4_15S);
        case C1_3_VLSNR:
            return uptr(&ldpc_tab_VLSNR_1_3S);
        default:
            break;
        }
        break;
    case FECFRAME_MEDIUM:
        switch (rate) {
        case C1_5_MEDIUM:
            return uptr(&ldpc_tab_VLSNR_1_5M);
        case C11_45_MEDIUM:
            return uptr(&ldpc_tab_VLSNR_11_45M);
        case C1_3_MEDIUM:
            return uptr(&ldpc_tab_VLSNR_1_3M);
        default:
            break;
        }
        break;
    }
    return nullptr;
}

} /* namespace dvbs2tx */
} /* namespace gr */
