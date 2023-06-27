/* -*- c++ -*- */
/*
 * Copyright 2023 AsriFox.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <gnuradio/analog/random_uniform_source.h>
#include <gnuradio/attributes.h>
#include <gnuradio/blocks/head.h>
#include <gnuradio/blocks/tag_debug.h>
#include <gnuradio/dvbs2tx/bbheader_bb.h>
#include <gnuradio/dvbs2tx/bch_encoder_bb.h>
#include <gnuradio/dvbs2tx/dvbs2_config.h>
#include <gnuradio/top_block.h>
#include <boost/test/unit_test.hpp>

namespace gr {
namespace dvbs2tx {

using namespace gr::dtv;

BOOST_AUTO_TEST_CASE(test_bch_encoder_debug_tags)
{
    auto tb = gr::make_top_block("test_bbheader");
    auto src = gr::analog::random_uniform_source_b::make(0, 255, 0);
    auto head = gr::blocks::head::make(sizeof(u8), 64800);
    auto bbh = bbheader_bb::make(FECFRAME_SHORT, C8_9, MOD_16APSK, false, 0, RO_0_20);
    auto bbs = bch_encoder_bb::make();
    auto snk = gr::blocks::tag_debug::make(sizeof(u8), "bbheader", "modcod");
    tb->connect(src, 0, head, 0);
    tb->connect(head, 0, bbh, 0);
    tb->connect(bbh, 0, bbs, 0);
    tb->connect(bbs, 0, snk, 0);
    tb->run();
    tb->wait();
}

} /* namespace dvbs2tx */
} /* namespace gr */
