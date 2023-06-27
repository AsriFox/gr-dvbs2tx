/* -*- c++ -*- */
/*
 * Copyright 2014,2016 Ron Economos.
 * Copyright 2023 AsriFox.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "bbscrambler_bb_impl.h"
#include "modcod_tag.hh"
#include <gnuradio/io_signature.h>
#include <pmt/pmt.h>

namespace gr {
namespace dvbs2tx {

using namespace gr::dtv;

bbscrambler_bb::sptr bbscrambler_bb::make()
{
    return gnuradio::make_block_sptr<bbscrambler_bb_impl>();
}

/*
 * The private constructor
 */
bbscrambler_bb_impl::bbscrambler_bb_impl()
    : gr::tagged_stream_block("bbscrambler_bb",
                              gr::io_signature::make(1, 1, sizeof(u8)),
                              gr::io_signature::make(1, 1, sizeof(u8)),
                              "modcod")
{
    init_bb_randomiser();
    set_tag_propagation_policy(TPP_ALL_TO_ALL);
}

/*
 * Our virtual destructor.
 */
bbscrambler_bb_impl::~bbscrambler_bb_impl() {}

void bbscrambler_bb_impl::init_bb_randomiser(void)
{
    int sr = 0x4A80;
    for (usize i = 0; i < FRAME_SIZE_NORMAL; i++) {
        int b = ((sr) ^ (sr >> 1)) & 1;
        bb_randomise[i] = b;
        sr >>= 1;
        if (b) {
            sr |= 0x4000;
        }
    }
}

int bbscrambler_bb_impl::get_kbch(dvb_framesize_t framesize, dvb_code_rate_t rate)
{
    if (framesize == FECFRAME_NORMAL) {
        switch (rate) {
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
    } else if (framesize == FECFRAME_SHORT) {
        switch (rate) {
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
        switch (rate) {
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

void bbscrambler_bb_impl::parse_length_tags(const std::vector<std::vector<tag_t>>& tags,
                                            gr_vector_int& n_input_items_reqd)
{
    n_input_items_reqd[0] = 0;
    for (tag_t tag : tags[0]) {
        if (pmt::symbol_to_string(tag.key) == "modcod") {
            auto mt = from_pmt(tag.value);
            n_input_items_reqd[0] = get_kbch(mt.framesize, mt.code_rate);
            break;
        }
    }
}

int bbscrambler_bb_impl::calculate_output_stream_length(const gr_vector_int& ninput_items)
{
    return ninput_items[0];
}

int bbscrambler_bb_impl::work(int noutput_items,
                              gr_vector_int& ninput_items,
                              gr_vector_const_void_star& input_items,
                              gr_vector_void_star& output_items)
{
    auto in = static_cast<const u8*>(input_items[0]);
    auto out = static_cast<u8*>(output_items[0]);

    for (usize j = 0; j < usize(ninput_items[0]); j++) {
        out[j] = in[j] ^ bb_randomise[j];
    }

    return noutput_items;
}

} /* namespace dvbs2tx */
} /* namespace gr */
