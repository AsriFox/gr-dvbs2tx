/* -*- c++ -*- */
/*
 * Copyright 2014,2016,2017,2020 Ron Economos.
 * Copyright 2023 Oleg Nikitin.
 *
 * This file is part of gr-dvbs2tx.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DVBS2TX_BBHEADER_BB_IMPL_H
#define INCLUDED_DVBS2TX_BBHEADER_BB_IMPL_H

#include <gnuradio/dvbs2tx/bbheader_bb.h>

#define NUM_STREAMS 4

typedef struct {
    int ts_gs;
    int sis_mis;
    int ccm_acm;
    int issyi;
    int npd;
    int ro;
    int isi;
    int upl;
    int dfl;
    int sync;
    int syncd;
} BBHeader;

typedef struct {
    BBHeader bb_header;
} FrameFormat;

namespace gr {
namespace dvbs2tx {

class bbheader_bb_impl : public bbheader_bb
{
private:
    int num_streams;
    int stream;
    unsigned int kbch[NUM_STREAMS];
    unsigned int count[NUM_STREAMS];
    unsigned char crc[NUM_STREAMS];
    unsigned int frame_size[NUM_STREAMS];
    unsigned int code_rate[NUM_STREAMS];
    unsigned int signal_constellation[NUM_STREAMS];
    unsigned int pilot_mode[NUM_STREAMS];
    unsigned int root_code[NUM_STREAMS];
    unsigned char bsave[NUM_STREAMS];
    bool dvbs2x[NUM_STREAMS];
    bool alternate[NUM_STREAMS];
    bool nibble[NUM_STREAMS];
    FrameFormat m_format[1][NUM_STREAMS];
    unsigned char crc_tab[256];
    void add_bbheader(unsigned char*, int, bool, int);
    int gold_to_root(int);
    void build_crc8_table(void);
    int add_crc8_bits(unsigned char*, int);

public:
    bbheader_bb_impl(int nstreams,
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
    ~bbheader_bb_impl();

    void forecast(int noutput_items, gr_vector_int& ninput_items_required);

    int general_work(int noutput_items,
                     gr_vector_int& ninput_items,
                     gr_vector_const_void_star& input_items,
                     gr_vector_void_star& output_items);
};

} // namespace dvbs2tx
} // namespace gr

#endif /* INCLUDED_DVBS2TX_BBHEADER_BB_IMPL_H */
