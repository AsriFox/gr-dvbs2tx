/* -*- c++ -*- */
/*
 * Copyright 2014,2016 Ron Economos.
 * Copyright 2023 Oleg Nikitin.
 *
 * This file is part of gr-dvbs2tx.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DVBS2TX_INTERLEAVER_BB_IMPL_H
#define INCLUDED_DVBS2TX_INTERLEAVER_BB_IMPL_H

#include <gnuradio/dvbs2tx/interleaver_bb.h>

namespace gr {
namespace dvbs2tx {

class interleaver_bb_impl : public interleaver_bb
{
private:
    int rowaddr0;
    int rowaddr1;
    int rowaddr2;
    int rowaddr3;
    int rowaddr4;
    void
    get_rows(dvbs2_framesize_t, dvbs2_code_rate_t, dvbs2_constellation_t, int*, int*);

public:
    interleaver_bb_impl();
    ~interleaver_bb_impl();

    void forecast(int noutput_items, gr_vector_int& ninput_items_required);

    int general_work(int noutput_items,
                     gr_vector_int& ninput_items,
                     gr_vector_const_void_star& input_items,
                     gr_vector_void_star& output_items);
};

} // namespace dvbs2tx
} // namespace gr

#endif /* INCLUDED_DVBS2TX_INTERLEAVER_BB_IMPL_H */
