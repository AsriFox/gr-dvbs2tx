# Copyright 2020 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

GR_PYTHON_CHECK_MODULE_RAW(
    "pygccxml"
    "import pygccxml"
    PYGCCXML_FOUND
    )

include(GrPybind)

########################################################################
# Python Bindings
########################################################################

list(APPEND dvbs2tx_python_files
    bbheader_bb_python.cc
    bbheader_source_python.cc
    bbscrambler_bb_python.cc
    bch_bb_python.cc
    interleaver_bb_python.cc
    ldpc_bb_python.cc
    modulator_bc_python.cc
    physical_cc_python.cc
    dvbs2_config_python.cc 
    python_bindings.cc)

GR_PYBIND_MAKE_OOT(dvbs2tx 
   ../../..
   gr::dvbs2tx
   "${dvbs2tx_python_files}")

install(TARGETS dvbs2tx_python DESTINATION ${GR_PYTHON_DIR}/gnuradio/dvbs2tx COMPONENT pythonapi)
