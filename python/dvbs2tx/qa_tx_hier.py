#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# Copyright 2023 AsriFox.
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

from time import sleep
from gnuradio import gr, gr_unittest
from gnuradio import blocks, analog, dtv
try:
    from gnuradio.dvbs2tx import tx_hier
except ImportError:
    import os
    import sys
    dirname, filename = os.path.split(os.path.abspath(__file__))
    sys.path.append(os.path.join(dirname, "bindings"))
    from gnuradio.dvbs2tx import tx_hier

class qa_tx_hier(gr_unittest.TestCase):

    def setUp(self):
        self.tb = gr.top_block()
        self.src = analog.random_uniform_source_b(0, 255, 0)
        self.snk = blocks.null_sink(gr.sizeof_gr_complex)

    def tearDown(self):
        self.tb = None
        self.src = None
        self.snk = None
        try:
            self.core = None
        except AttributeError:
            pass

    def test_instance(self):
        """
        Test the constructor of DVB-S2 Transmitter stack
        """
        instance = tx_hier(
            dtv.FECFRAME_NORMAL, 
            dtv.C1_4,
            dtv.MOD_QPSK,
            True,
            0,
            dtv.RO_0_35,
            False)

    def test_fast_frames(self):
        self.tb.disconnect_all()
        self.core = tx_hier(
            dtv.FECFRAME_SHORT, 
            dtv.C8_9, 
            dtv.MOD_16APSK, 
            False, 
            0, 
            dtv.RO_0_05, 
            False)
        self.tb.connect(self.src, self.core, self.snk)

        self.tb.run()
        sleep(10.0)
        self.tb.stop()
        self.tb.wait()


if __name__ == '__main__':
    gr_unittest.run(qa_tx_hier)
