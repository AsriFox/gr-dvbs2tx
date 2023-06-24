/* -*- c++ -*- */
/*
 * Copyright 2014,2016 Ron Economos.
 * Copyright 2023 Oleg Nikitin.
 *
 * This file is part of gr-dvbs2tx.
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
    unsigned char bb_randomise[FRAME_SIZE_NORMAL];
    void get_kbch(dvbs2_framesize_t, dvbs2_code_rate_t, unsigned int*);
    void init_bb_randomiser(void);

public:
    bbscrambler_bb_impl();
    ~bbscrambler_bb_impl();

    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace dvbs2tx
} // namespace gr

#endif /* INCLUDED_DVBS2TX_BBSCRAMBLER_BB_IMPL_H */
