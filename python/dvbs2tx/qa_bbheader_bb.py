#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# Copyright 2023 AsriFox.
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

from gnuradio import gr, gr_unittest
from gnuradio import analog, blocks, dtv
try:
    from gnuradio.dvbs2tx import bbheader_bb
except ImportError:
    import os
    import sys
    dirname, filename = os.path.split(os.path.abspath(__file__))
    sys.path.append(os.path.join(dirname, "bindings"))
    from gnuradio.dvbs2tx import bbheader_bb
from time import sleep

class qa_bbheader_bb(gr_unittest.TestCase):

    def setUp(self):
        self.tb = gr.top_block()
        self.src = analog.random_uniform_source_b(0, 255, 0)
        self.snk = blocks.tag_debug(gr.sizeof_char, 'bbheader', 'modcod')

    def tearDown(self):
        self.tb.disconnect_all()
        self.tb = None
        self.src = None
        self.snk = None

    def test_instance(self):
        instance = bbheader_bb(
            dtv.FECFRAME_NORMAL, 
            dtv.C1_4, 
            dtv.MOD_QPSK,
            True, 
            0, 
            dtv.RO_0_35)

    def test_print_tags(self):
        instance = bbheader_bb(
            dtv.FECFRAME_SHORT,
            dtv.C8_9,
            dtv.MOD_16APSK,
            False,
            0,
            dtv.RO_0_20)
        self.tb.disconnect_all()
        self.tb.connect(self.src, instance, self.snk)
        self.tb.run()
        sleep(3)
        self.tb.stop()
        self.tb.wait()
        

if __name__ == '__main__':
    gr_unittest.run(qa_bbheader_bb)
