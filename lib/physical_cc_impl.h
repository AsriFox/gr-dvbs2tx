/* -*- c++ -*- */
/*
 * Copyright 2014,2016,2017,2020 Ron Economos.
 * Copyright 2023 Oleg Nikitin.
 *
 * This file is part of gr-dvbs2tx.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DVBS2TX_PHYSICAL_CC_IMPL_H
#define INCLUDED_DVBS2TX_PHYSICAL_CC_IMPL_H

#include <gnuradio/dvbs2tx/physical_cc.h>

namespace gr {
namespace dvbs2tx {

const usize VLSNR_HEADER_LENGTH = 900;

class physical_cc_impl : public physical_cc
{
private:
    bool dummy_frames;
    u8 b[VLSNR_HEADER_LENGTH];
    gr_complex m_bpsk[4][2];
    gr_complex m_pl[90];
    gr_complex m_pl_dummy[90];
    gr_complex m_vlsnr_header[VLSNR_HEADER_LENGTH];
    gr_complex m_zero;
    int m_cscram_x;
    int m_cscram_y;
    void b_64_8_code(u8, u8*);
    void pl_header_encode(u8, u8, u8*);
    inline int parity_chk(int, int);
    inline int symbol_scrambler();
    void get_slots(dvb_framesize_t,
                   dvb_code_rate_t,
                   dvb_constellation_t,
                   bool pilots,
                   int,
                   int&,
                   int&,
                   int&,
                   int&);

    const static u32 g[7];
    const static u8 ph_scram_tab[64];
    const static u8 ph_sync_seq[26];
    const static u8 ph_vlsnr_seq[16][VLSNR_HEADER_LENGTH - 4];

public:
    physical_cc_impl(bool dummyframes);
    ~physical_cc_impl();

    void forecast(int noutput_items, gr_vector_int& ninput_items_required) override;

    int general_work(int noutput_items,
                     gr_vector_int& ninput_items,
                     gr_vector_const_void_star& input_items,
                     gr_vector_void_star& output_items) override;
};

} // namespace dvbs2tx
} // namespace gr

#endif /* INCLUDED_DVBS2TX_PHYSICAL_CC_IMPL_H */
