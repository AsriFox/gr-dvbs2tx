/* -*- c++ -*- */
/*
 * Copyright 2023 AsriFox.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "tx_hier_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
namespace dvbs2tx {

tx_hier::sptr tx_hier::make(dvb_framesize_t framesize,
                            dvb_code_rate_t rate,
                            dvb_constellation_t constellation,
                            bool pilots,
                            int goldcode,
                            dvbs2_rolloff_factor_t rolloff,
                            bool dummyframes)
{
    return gnuradio::make_block_sptr<tx_hier_impl>(
        framesize, rate, constellation, pilots, goldcode, rolloff, dummyframes);
}


/*
 * The private constructor
 */
tx_hier_impl::tx_hier_impl(dvb_framesize_t framesize,
                           dvb_code_rate_t rate,
                           dvb_constellation_t constellation,
                           bool pilots,
                           int goldcode,
                           dvbs2_rolloff_factor_t rolloff,
                           bool dummyframes)
    : gr::hier_block2("tx_hier",
                      gr::io_signature::make(1, 1, sizeof(u8)),
                      gr::io_signature::make(1, 1, sizeof(gr_complex))),
      bbheader(
          bbheader_bb::make(framesize, rate, constellation, pilots, goldcode, rolloff)),
      bbscrambler(bbscrambler_bb::make()),
      bch_encoder(bch_bb::make()),
      ldpc_encoder(ldpc_bb::make()),
      interleaver(interleaver_bb::make()),
      modulator(modulator_bc::make()),
      pl_framer(physical_cc::make(dummyframes))
{
    const pmt::pmt_t port_id = pmt::mp("cmd");
    message_port_register_in(port_id);
    msg_connect(self(), port_id, bbheader, port_id);

    connect(self(), 0, bbheader, 0);
    connect(bbheader, 0, bbscrambler, 0);
    connect(bbscrambler, 0, bch_encoder, 0);
    connect(bch_encoder, 0, ldpc_encoder, 0);
    connect(ldpc_encoder, 0, interleaver, 0);
    connect(interleaver, 0, modulator, 0);
    connect(modulator, 0, pl_framer, 0);
    connect(pl_framer, 0, self(), 0);
}

/*
 * Our virtual destructor.
 */
tx_hier_impl::~tx_hier_impl() {}


} /* namespace dvbs2tx */
} /* namespace gr */
