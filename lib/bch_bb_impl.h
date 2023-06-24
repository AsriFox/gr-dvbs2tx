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
    u32 m_poly_n_8[4];
    u32 m_poly_n_10[5];
    u32 m_poly_n_12[6];
    u32 m_poly_s_12[6];
    u32 m_poly_m_12[6];
    void get_kbch_nbch(dvb_framesize_t, dvb_code_rate_t, u32*, u32*, u32*);
    i32 poly_mult(const i32*, i32, const i32*, i32, i32*);
    void poly_pack(const i32*, u32*, i32);
    void poly_reverse(i32*, i32*, i32);
    inline void reg_4_shift(u32*);
    inline void reg_5_shift(u32*);
    inline void reg_6_shift(u32*);
    void bch_poly_build_tables(void);

public:
    bch_bb_impl();
    ~bch_bb_impl();

    void forecast(int noutput_items, gr_vector_int& ninput_items_required) override;

    int general_work(int noutput_items,
                     gr_vector_int& ninput_items,
                     gr_vector_const_void_star& input_items,
                     gr_vector_void_star& output_items) override;
};

} // namespace dvbs2tx
} // namespace gr

#endif /* INCLUDED_DVBS2TX_BCH_BB_IMPL_H */
