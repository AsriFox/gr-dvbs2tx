/* -*- c++ -*- */
/*
 * Copyright 2014,2016 Ron Economos.
 * Copyright 2023 AsriFox.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DVBS2TX_BBSCRAMBLER_BB_IMPL_H
#define INCLUDED_DVBS2TX_BBSCRAMBLER_BB_IMPL_H

#include <gnuradio/dvbs2tx/bbscrambler_bb.h>

namespace gr {
namespace dvbs2tx {

class bbscrambler_bb_impl : public bbscrambler_bb
{
private:
    gr::thread::mutex d_mutex;
    int get_kbch(dvb_framesize_t frame_size, dvb_code_rate_t code_rate);
    unsigned char bb_randomise[FRAME_SIZE_NORMAL];
    void init_bb_randomiser();

protected:
    void parse_length_tags(const std::vector<std::vector<tag_t>>& tags,
                           gr_vector_int& n_input_items_reqd) override;
    int calculate_output_stream_length(const gr_vector_int& ninput_items) override;

public:
    bbscrambler_bb_impl();
    ~bbscrambler_bb_impl() override;

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_int& ninput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items) override;
};

} // namespace dvbs2tx
} // namespace gr

#endif /* INCLUDED_DVBS2TX_BBSCRAMBLER_BB_IMPL_H */
