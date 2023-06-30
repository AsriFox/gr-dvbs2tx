/* -*- c++ -*- */
/*
 * Copyright 2014,2016 Ron Economos.
 * Copyright 2023 AsriFox.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DVBS2TX_LDPC_ENCODER_BB_IMPL_H
#define INCLUDED_DVBS2TX_LDPC_ENCODER_BB_IMPL_H

#include <gnuradio/dvbs2tx/ldpc_encoder_bb.h>
#include <vector>

namespace gr {
namespace dvbs2tx {

struct ldpc_encoder {
    usize nbch;
    usize q;
    usize frame_size;
    usize shortening;        // x_s
    usize puncturing_period; // p
    usize puncturing;        // x_p
    std::vector<std::vector<u16>> table;

    typedef std::unique_ptr<const ldpc_encoder> uptr;
    static uptr select(dvb_framesize_t, dvb_code_rate_t);

    void calculate_parity_bits(const u8* data_buffer, u8* parity_buffer) const;
    void puncture_parity_bits(u8* parity_buffer, u8* parity_out) const;

    const static ldpc_encoder ldpc_tab_1_4N;
    const static ldpc_encoder ldpc_tab_1_3N;
    const static ldpc_encoder ldpc_tab_2_5N;
    const static ldpc_encoder ldpc_tab_1_2N;
    const static ldpc_encoder ldpc_tab_3_5N;
    const static ldpc_encoder ldpc_tab_2_3N;
    const static ldpc_encoder ldpc_tab_3_4N;
    const static ldpc_encoder ldpc_tab_4_5N;
    const static ldpc_encoder ldpc_tab_5_6N;
    const static ldpc_encoder ldpc_tab_8_9N;
    const static ldpc_encoder ldpc_tab_9_10N;

    const static ldpc_encoder ldpc_tab_1_4S;
    const static ldpc_encoder ldpc_tab_1_3S;
    const static ldpc_encoder ldpc_tab_2_5S;
    const static ldpc_encoder ldpc_tab_1_2S;
    const static ldpc_encoder ldpc_tab_3_5S;
    const static ldpc_encoder ldpc_tab_2_3S;
    const static ldpc_encoder ldpc_tab_3_4S;
    const static ldpc_encoder ldpc_tab_4_5S;
    const static ldpc_encoder ldpc_tab_5_6S;
    const static ldpc_encoder ldpc_tab_8_9S;

    const static ldpc_encoder ldpc_tab_13_45N;
    const static ldpc_encoder ldpc_tab_9_20N;
    const static ldpc_encoder ldpc_tab_11_20N;
    const static ldpc_encoder ldpc_tab_26_45N;
    const static ldpc_encoder ldpc_tab_28_45N;
    const static ldpc_encoder ldpc_tab_23_36N;
    const static ldpc_encoder ldpc_tab_25_36N;
    const static ldpc_encoder ldpc_tab_13_18N;
    const static ldpc_encoder ldpc_tab_7_9N;
    const static ldpc_encoder ldpc_tab_90_180N;
    const static ldpc_encoder ldpc_tab_96_180N;
    const static ldpc_encoder ldpc_tab_100_180N;
    const static ldpc_encoder ldpc_tab_104_180N;
    const static ldpc_encoder ldpc_tab_116_180N;
    const static ldpc_encoder ldpc_tab_124_180N;
    const static ldpc_encoder ldpc_tab_128_180N;
    const static ldpc_encoder ldpc_tab_132_180N;
    const static ldpc_encoder ldpc_tab_135_180N;
    const static ldpc_encoder ldpc_tab_140_180N;
    const static ldpc_encoder ldpc_tab_154_180N;
    const static ldpc_encoder ldpc_tab_18_30N;
    const static ldpc_encoder ldpc_tab_20_30N;
    const static ldpc_encoder ldpc_tab_22_30N;

    const static ldpc_encoder ldpc_tab_11_45S;
    const static ldpc_encoder ldpc_tab_4_15S;
    const static ldpc_encoder ldpc_tab_14_45S;
    const static ldpc_encoder ldpc_tab_7_15S;
    const static ldpc_encoder ldpc_tab_8_15S;
    const static ldpc_encoder ldpc_tab_26_45S;
    const static ldpc_encoder ldpc_tab_32_45S;

    const static ldpc_encoder ldpc_tab_VLSNR_2_9N;
    const static ldpc_encoder ldpc_tab_VLSNR_1_5SF2;
    const static ldpc_encoder ldpc_tab_VLSNR_11_45SF2;
    const static ldpc_encoder ldpc_tab_VLSNR_1_5S;
    const static ldpc_encoder ldpc_tab_VLSNR_4_15S;
    const static ldpc_encoder ldpc_tab_VLSNR_1_3S;
    const static ldpc_encoder ldpc_tab_VLSNR_1_5M;
    const static ldpc_encoder ldpc_tab_VLSNR_11_45M;
    const static ldpc_encoder ldpc_tab_VLSNR_1_3M;
};

class ldpc_encoder_bb_impl : public ldpc_encoder_bb
{
private:
    u8 shortening_buffer[FRAME_SIZE_NORMAL];
    u8 puncturing_buffer[FRAME_SIZE_NORMAL];
    ldpc_encoder::uptr enc;

protected:
    void parse_length_tags(const std::vector<std::vector<tag_t>>& tags,
                           gr_vector_int& n_input_items_reqd) override;
    int calculate_output_stream_length(const gr_vector_int& ninput_items) override;

public:
    ldpc_encoder_bb_impl();
    ~ldpc_encoder_bb_impl() override;

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_int& ninput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items) override;
};

} // namespace dvbs2tx
} // namespace gr

#endif /* INCLUDED_DVBS2TX_LDPC_ENCODER_BB_IMPL_H */
