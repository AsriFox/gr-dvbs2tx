/* -*- c++ -*- */
/*
 * Copyright 2014,2016 Ron Economos.
 * Copyright 2023 Oleg Nikitin.
 *
 * This file is part of gr-dvbs2tx.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DVBS2TX_BCH_BB_IMPL_H
#define INCLUDED_DVBS2TX_BCH_BB_IMPL_H

#include <gnuradio/dvbs2tx/bch_bb.h>

namespace gr {
namespace dvbs2tx {

class bch_bb_impl : public bch_bb
{
private:
    unsigned int m_poly_n_8[4];
    unsigned int m_poly_n_10[5];
    unsigned int m_poly_n_12[6];
    unsigned int m_poly_s_12[6];
    unsigned int m_poly_m_12[6];
    void get_kbch_nbch(dvbs2_framesize_t,
                       dvbs2_code_rate_t,
                       unsigned int*,
                       unsigned int*,
                       unsigned int*);
    int poly_mult(const int*, int, const int*, int, int*);
    void poly_pack(const int*, unsigned int*, int);
    void poly_reverse(int*, int*, int);
    inline void reg_4_shift(unsigned int*);
    inline void reg_5_shift(unsigned int*);
    inline void reg_6_shift(unsigned int*);
    void bch_poly_build_tables(void);

public:
    bch_bb_impl();
    ~bch_bb_impl();

    void forecast(int noutput_items, gr_vector_int& ninput_items_required);

    int general_work(int noutput_items,
                     gr_vector_int& ninput_items,
                     gr_vector_const_void_star& input_items,
                     gr_vector_void_star& output_items);
};

} // namespace dvbs2tx
} // namespace gr

#endif /* INCLUDED_DVBS2TX_BCH_BB_IMPL_H */
