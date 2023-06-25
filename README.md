# gr-dvbs2tx

## Overview
**gr-dvbs2tx** is a GNU Radio OOT module including transmitter blocks for software-defined radio and message passing simulation. This is a fork of drmpeg's [gr-dvbs2](https://github.com/drmpeg/gr-dvbs2) project. The receiver blocks are in [gr-dvbs2rx](https://github.com/AsriFox/gr-dvbs2rx).

> The goal of this project is to build a software-defined DVB-S2 transmitter, based on the EN 302 307 V1.3.1 Second Generation framing structure, channel coding and modulation systems for Broadcasting, Interactive Services, New Gathering and other broadband satellite applications standard:<br>
> http://www.etsi.org/deliver/etsi_en/302300_302399/302307/01.03.01_60/en_302307v010301p.pdf<br>
> The baseband framing, baseband scrambling, LDPC (low density parity check), BCH (Bose, Chaudhuri, Hocquenghem), bit interleaver and physical layer framing and scrambling blocks are from G4GUO's DATV-Express Digital Amateur Television project datvexpress_gui (https://github.com/G4GUO/datvexpress_gui/tree/master/DVB-S2) and converted to GnuRadio 3.7.x.

> Since the functionality of the CCM version of the DVB-S2 transmitter is already included in GNU Radio, this OOT implements a VCM/ACM (Variable/Adaptive Coding and Modulation) version of the DVB-S2 transmitter.

This implementation supports the following DVB-S2 System configurations:
<!-- 
1. QPSK 1/4, 1/3, 2/5
1. QPSK 1/2, 3/5, 2/3, 3/4, 4/5, 5/6, 8/9, 9/10
1. 8PSK 3/5, 2/3, 3/4, 5/6, 8/9, 9/10
1. 16APSK 2/3, 3/4, 4/5, 5/6, 8/9, 9/10
1. 32APSK 3/4, 4/5, 5/6, 8/9, 9/10
1. CCM (Constant Coding and Modulation)
1. FECFRAME normal 64,800 bits
1. FECFRAME short 16,200 bits
1. Single Transport Stream
1. Roll-off 0.35, 0.25 and 0.20
1. VCM (Variable Coding and Modulation)
1. ACM (Adaptive Coding and Modulation)
1. Multiple Transport Streams
1. Multiple Generic Streams
1. Single Generic Stream
1. Dummy Frame Insertion
-->

System configurations not supported are:
1. Input Stream Synchronizer
1. Null Packet Detection
1. Wide-band mode

This project is licensed under GPLv3 and was developed primarily for non-commercial research, experimentation, and education. Please feel free to contribute or get in touch to request features or report any problems.

## Installation
The only available installation method is compiling from source. You will need to clone this repository first:
```
git clone --recursive https://github.com/AsriFox/gr-dvbs2tx.git
cd gr-dvbs2tx/
```

Install dependencies on Ubuntu:
```
apt install cmake pkg-config doxygen gnuradio-dev \
    graphviz libsndfile1-dev libspdlog-dev \
    pybind11-dev python3-packaging
```

Install dependencies on Fedora:
```
dnf install cmake doxygen gnuradio-devel \
    fftw-devel gmp-devel graphviz \
    libsndfile-devel spdlog-devel \
    pybind11-devel python3-packaging \
```

Build:
```
mkdir build && cd build
cmake -DCMAKE_INSTALL_PREFIX=$(gnuradio-config-info --prefix) ..
cmake --build . -j$(nproc)
```

IDE support: **VSCode** (tasks, launch profiles and toolchain settings).<br>
Extensions used: 
- [CMake Tools](https://github.com/microsoft/vscode-cmake-tools)
- [CodeLLDB](https://github.com/vadimcn/codelldb)

Install (from *build/*):
```
sudo make install
sudo ldconfig
```

## Authors
- [Ron Economos](https://github.com/drmpeg)
- [Ahmet Inan](https://github.com/xdsopl)
- [Igor Freire](https://github.com/igorauad)
- [Oleg Nikitin](https://github.com/AsriFox)
