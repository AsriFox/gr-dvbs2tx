/* -*- c++ -*- */
/*
 * Copyright 2014,2016,2017,2020 Ron Economos.
 * Copyright 2023 AsriFox.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DVBS2TX_BBHEADER_BB_IMPL_H
#define INCLUDED_DVBS2TX_BBHEADER_BB_IMPL_H

#include <gnuradio/dvbs2tx/bbheader_bb.h>

namespace gr {
namespace dvbs2tx {

struct BBHeader {
    dvb_bb_ts_gs_t ts_gs;
    dvb_bb_sis_mis_t sis_mis;
    dvb_bb_ccm_acm_t ccm_acm;
    bool issyi;
    bool npd;
    dvbs2_rolloff_factor_t ro;
    u8 isi;
    u16 upl;
    u16 dfl;
    u8 sync;
    u16 syncd;
};

class bbheader_bb_impl : public bbheader_bb
{
private:
    usize kbch;
    usize count;
    u8 crc;
    dvb_framesize_t framesize;
    dvb_code_rate_t code_rate;
    dvb_constellation_t constellation;
    bool pilots;
    u32 root_code;
    bool dvbs2x;
    bool alternate;
    bool nibble;
    BBHeader m_format;
    gr::thread::mutex d_mutex;
    int get_kbch(dvb_framesize_t frame_size, dvb_code_rate_t code_rate);
    usize add_bbheader(u8* out, int count, usize padding, bool nibble, int isi);
    u32 gold_to_root(int);
    usize add_crc8_bits(u8* out, usize length);

public:
    bbheader_bb_impl(dvb_framesize_t framesize,
                     dvb_code_rate_t code_rate,
                     dvb_constellation_t constellation,
                     bool pilots,
                     int goldcode,
                     dvbs2_rolloff_factor_t rolloff);
    ~bbheader_bb_impl() override;

    void set_modcod(int modcod) override;

    void handle_cmd_msg(pmt::pmt_t msg);

    // Where all the action really happens
    void forecast(int noutput_items, gr_vector_int& ninput_items_required) override;

    int general_work(int noutput_items,
                     gr_vector_int& ninput_items,
                     gr_vector_const_void_star& input_items,
                     gr_vector_void_star& output_items) override;
};

} // namespace dvbs2tx
} // namespace gr

#endif /* INCLUDED_DVBS2TX_BBHEADER_BB_IMPL_H */
