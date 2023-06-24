/* -*- c++ -*- */
/*
 * Copyright 2014,2016,2017 Ron Economos.
 * Copyright 2023 Oleg Nikitin.
 *
 * This file is part of gr-dvbs2tx.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "bbscrambler_bb_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
namespace dvbs2tx {

using namespace gr::dtv;

bbscrambler_bb::sptr bbscrambler_bb::make()
{
    return gnuradio::get_initial_sptr(new bbscrambler_bb_impl());
}

/*
 * The private constructor
 */
bbscrambler_bb_impl::bbscrambler_bb_impl()
    : gr::sync_block("bbscrambler_bb",
                     gr::io_signature::make(1, 1, sizeof(u8)),
                     gr::io_signature::make(1, 1, sizeof(u8)))
{
    init_bb_randomiser();
    set_output_multiple(FRAME_SIZE_NORMAL);
}

/*
 * Our virtual destructor.
 */
bbscrambler_bb_impl::~bbscrambler_bb_impl() {}

void bbscrambler_bb_impl::get_kbch(dvb_framesize_t framesize,
                                   dvb_code_rate_t rate,
                                   unsigned int* kbch)
{
    if (framesize == FECFRAME_NORMAL) {
        switch (rate) {
        case C1_4:
            *kbch = 16008;
            break;
        case C1_3:
            *kbch = 21408;
            break;
        case C2_5:
            *kbch = 25728;
            break;
        case C1_2:
            *kbch = 32208;
            break;
        case C3_5:
            *kbch = 38688;
            break;
        case C2_3:
            *kbch = 43040;
            break;
        case C3_4:
            *kbch = 48408;
            break;
        case C4_5:
            *kbch = 51648;
            break;
        case C5_6:
            *kbch = 53840;
            break;
        case C8_9:
            *kbch = 57472;
            break;
        case C9_10:
            *kbch = 58192;
            break;
        case C2_9_VLSNR:
            *kbch = 14208;
            break;
        case C13_45:
            *kbch = 18528;
            break;
        case C9_20:
            *kbch = 28968;
            break;
        case C90_180:
            *kbch = 32208;
            break;
        case C96_180:
            *kbch = 34368;
            break;
        case C11_20:
            *kbch = 35448;
            break;
        case C100_180:
            *kbch = 35808;
            break;
        case C104_180:
            *kbch = 37248;
            break;
        case C26_45:
            *kbch = 37248;
            break;
        case C18_30:
            *kbch = 38688;
            break;
        case C28_45:
            *kbch = 40128;
            break;
        case C23_36:
            *kbch = 41208;
            break;
        case C116_180:
            *kbch = 41568;
            break;
        case C20_30:
            *kbch = 43008;
            break;
        case C124_180:
            *kbch = 44448;
            break;
        case C25_36:
            *kbch = 44808;
            break;
        case C128_180:
            *kbch = 45888;
            break;
        case C13_18:
            *kbch = 46608;
            break;
        case C132_180:
            *kbch = 47328;
            break;
        case C22_30:
            *kbch = 47328;
            break;
        case C135_180:
            *kbch = 48408;
            break;
        case C140_180:
            *kbch = 50208;
            break;
        case C7_9:
            *kbch = 50208;
            break;
        case C154_180:
            *kbch = 55248;
            break;
        default:
            *kbch = 0;
            break;
        }
    } else if (framesize == FECFRAME_SHORT) {
        switch (rate) {
        case C1_4:
            *kbch = 3072;
            break;
        case C1_3:
            *kbch = 5232;
            break;
        case C2_5:
            *kbch = 6312;
            break;
        case C1_2:
            *kbch = 7032;
            break;
        case C3_5:
            *kbch = 9552;
            break;
        case C2_3:
            *kbch = 10632;
            break;
        case C3_4:
            *kbch = 11712;
            break;
        case C4_5:
            *kbch = 12432;
            break;
        case C5_6:
            *kbch = 13152;
            break;
        case C8_9:
            *kbch = 14232;
            break;
        case C11_45:
            *kbch = 3792;
            break;
        case C4_15:
            *kbch = 4152;
            break;
        case C14_45:
            *kbch = 4872;
            break;
        case C7_15:
            *kbch = 7392;
            break;
        case C8_15:
            *kbch = 8472;
            break;
        case C26_45:
            *kbch = 9192;
            break;
        case C32_45:
            *kbch = 11352;
            break;
        case C1_5_VLSNR_SF2:
            *kbch = 2512;
            break;
        case C11_45_VLSNR_SF2:
            *kbch = 3792;
            break;
        case C1_5_VLSNR:
            *kbch = 3072;
            break;
        case C4_15_VLSNR:
            *kbch = 4152;
            break;
        case C1_3_VLSNR:
            *kbch = 5232;
            break;
        default:
            *kbch = 0;
            break;
        }
    } else {
        switch (rate) {
        case C1_5_MEDIUM:
            *kbch = 5660;
            break;
        case C11_45_MEDIUM:
            *kbch = 7740;
            break;
        case C1_3_MEDIUM:
            *kbch = 10620;
            break;
        default:
            *kbch = 0;
            break;
        }
    }
}

void bbscrambler_bb_impl::init_bb_randomiser(void)
{
    int sr = 0x4A80;
    for (int i = 0; i < FRAME_SIZE_NORMAL; i++) {
        int b = ((sr) ^ (sr >> 1)) & 1;
        bb_randomise[i] = b;
        sr >>= 1;
        if (b) {
            sr |= 0x4000;
        }
    }
}

int bbscrambler_bb_impl::work(int noutput_items,
                              gr_vector_const_void_star& input_items,
                              gr_vector_void_star& output_items)
{
    const u8* in = static_cast<const u8*>(input_items[0]);
    u8* out = static_cast<u8*>(output_items[0]);
    u32 kbch;
    usize produced = 0;

    std::vector<tag_t> tags;
    const uint64_t nread = this->nitems_read(0); // number of items read on port 0

    // Read all tags on the input buffer
    this->get_tags_in_range(
        tags, 0, nread, nread + noutput_items, pmt::string_to_symbol("modcod"));

    for (int i = 0; i < (int)tags.size(); i++) {
        get_kbch(dvb_framesize_t(((pmt::to_uint64(tags[i].value)) >> 1) & 0x7f),
                 dvb_code_rate_t(((pmt::to_uint64(tags[i].value)) >> 8) & 0xff),
                 &kbch);
        if (kbch + produced <= usize(noutput_items)) {
            for (usize j = 0; j < kbch; ++j) {
                out[produced + j] = in[produced + j] ^ bb_randomise[j];
            }
            produced += kbch;
        } else {
            break;
        }
    }

    // Tell runtime system how many output items we produced.
    return produced;
}

} // namespace dvbs2tx
} /* namespace gr */
