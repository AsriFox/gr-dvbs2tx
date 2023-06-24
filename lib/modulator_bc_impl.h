/* -*- c++ -*- */
/*
 * Copyright 2014,2016 Ron Economos.
 * Copyright 2023 Oleg Nikitin.
 *
 * This file is part of gr-dvbs2tx.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DVBS2TX_MODULATOR_BC_IMPL_H
#define INCLUDED_DVBS2TX_MODULATOR_BC_IMPL_H

#include <gnuradio/dvbs2tx/modulator_bc.h>

namespace gr {
namespace dvbs2tx {

class modulator_bc_impl : public modulator_bc
{
private:
    gr_complex m_bpsk[2][2];
    gr_complex m_qpsk[4];
    gr_complex m_8psk[8];
    gr_complex m_8apsk[8][2];
    gr_complex m_16apsk[16][12];
    gr_complex m_8_8apsk[16][3];
    gr_complex m_32apsk[32][5];
    gr_complex m_4_12_16apsk[32][3];
    gr_complex m_4_8_4_16apsk[32][3];
    void
    get_items(dvbs2_framesize_t, dvbs2_code_rate_t, dvbs2_constellation_t, int*, int*);

public:
    modulator_bc_impl();
    ~modulator_bc_impl();

    void forecast(int noutput_items, gr_vector_int& ninput_items_required);

    int general_work(int noutput_items,
                     gr_vector_int& ninput_items,
                     gr_vector_const_void_star& input_items,
                     gr_vector_void_star& output_items);
};

} // namespace dvbs2tx
} // namespace gr

#endif /* INCLUDED_DVBS2TX_MODULATOR_BC_IMPL_H */
