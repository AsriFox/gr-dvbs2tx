/* -*- c++ -*- */
/*
 * Copyright 2014,2016 Ron Economos.
 * Copyright 2023 Oleg Nikitin.
 *
 * This file is part of gr-dvbs2tx.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DVBS2TX_LDPC_BB_IMPL_H
#define INCLUDED_DVBS2TX_LDPC_BB_IMPL_H

#include <gnuradio/dvbs2tx/ldpc_bb.h>

namespace gr {
namespace dvbs2tx {

typedef struct {
    int table_length;
    int d[LDPC_ENCODE_TABLE_LENGTH];
    int p[LDPC_ENCODE_TABLE_LENGTH];
} ldpc_encode_table;

class ldpc_bb_impl : public ldpc_bb
{
private:
    unsigned char puncturing_buffer[FRAME_SIZE_NORMAL];
    unsigned char shortening_buffer[FRAME_SIZE_NORMAL];
    void get_nbch(
        dvb_framesize_t, dvb_code_rate_t, u32*, u32*, u32*, u32*, i32*, i32*, i32*, i32*);
    void ldpc_lookup_generate();
    ldpc_encode_table ldpc_encode[55];

    const static u16 ldpc_tab_1_4N[45][13];
    const static u16 ldpc_tab_1_3N[60][13];
    const static u16 ldpc_tab_2_5N[72][13];
    const static u16 ldpc_tab_1_2N[90][9];
    const static u16 ldpc_tab_3_5N[108][13];
    const static u16 ldpc_tab_2_3N[120][14];
    const static u16 ldpc_tab_3_4N[135][13];
    const static u16 ldpc_tab_4_5N[144][12];
    const static u16 ldpc_tab_5_6N[150][14];
    const static u16 ldpc_tab_8_9N[160][5];
    const static u16 ldpc_tab_9_10N[162][5];

    const static u16 ldpc_tab_1_4S[9][13];
    const static u16 ldpc_tab_1_3S[15][13];
    const static u16 ldpc_tab_2_5S[18][13];
    const static u16 ldpc_tab_1_2S[20][9];
    const static u16 ldpc_tab_3_5S[27][13];
    const static u16 ldpc_tab_2_3S[30][14];
    const static u16 ldpc_tab_3_4S[33][13];
    const static u16 ldpc_tab_4_5S[35][4];
    const static u16 ldpc_tab_5_6S[37][14];
    const static u16 ldpc_tab_8_9S[40][5];

    const static u16 ldpc_tab_2_9N[40][12];
    const static u16 ldpc_tab_13_45N[52][13];
    const static u16 ldpc_tab_9_20N[81][13];
    const static u16 ldpc_tab_11_20N[99][14];
    const static u16 ldpc_tab_26_45N[104][14];
    const static u16 ldpc_tab_28_45N[112][12];
    const static u16 ldpc_tab_23_36N[115][12];
    const static u16 ldpc_tab_25_36N[125][12];
    const static u16 ldpc_tab_13_18N[130][11];
    const static u16 ldpc_tab_7_9N[140][13];
    const static u16 ldpc_tab_90_180N[90][19];
    const static u16 ldpc_tab_96_180N[96][21];
    const static u16 ldpc_tab_100_180N[100][17];
    const static u16 ldpc_tab_104_180N[104][19];
    const static u16 ldpc_tab_116_180N[116][19];
    const static u16 ldpc_tab_124_180N[124][17];
    const static u16 ldpc_tab_128_180N[128][16];
    const static u16 ldpc_tab_132_180N[132][16];
    const static u16 ldpc_tab_135_180N[135][15];
    const static u16 ldpc_tab_140_180N[140][16];
    const static u16 ldpc_tab_154_180N[154][14];
    const static u16 ldpc_tab_18_30N[108][20];
    const static u16 ldpc_tab_20_30N[120][17];
    const static u16 ldpc_tab_22_30N[132][16];

    const static u16 ldpc_tab_11_45S[11][11];
    const static u16 ldpc_tab_4_15S[12][22];
    const static u16 ldpc_tab_14_45S[14][13];
    const static u16 ldpc_tab_7_15S[21][25];
    const static u16 ldpc_tab_8_15S[24][22];
    const static u16 ldpc_tab_26_45S[26][14];
    const static u16 ldpc_tab_32_45S[32][13];

    const static u16 ldpc_tab_1_5M[18][14];
    const static u16 ldpc_tab_11_45M[22][11];
    const static u16 ldpc_tab_1_3M[30][13];

public:
    ldpc_bb_impl();
    ~ldpc_bb_impl();

    void forecast(int noutput_items, gr_vector_int& ninput_items_required) override;

    int general_work(int noutput_items,
                     gr_vector_int& ninput_items,
                     gr_vector_const_void_star& input_items,
                     gr_vector_void_star& output_items) override;
};

} // namespace dvbs2tx
} // namespace gr

#endif /* INCLUDED_DVBS2TX_LDPC_BB_IMPL_H */
