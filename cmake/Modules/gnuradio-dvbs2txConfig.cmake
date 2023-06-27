find_package(PkgConfig)

PKG_CHECK_MODULES(PC_GR_DVBS2TX gnuradio-dvbs2tx)

FIND_PATH(
    GR_DVBS2TX_INCLUDE_DIRS
    NAMES gnuradio/dvbs2tx/api.h
    HINTS $ENV{DVBS2TX_DIR}/include
        ${PC_DVBS2TX_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    GR_DVBS2TX_LIBRARIES
    NAMES gnuradio-dvbs2tx
    HINTS $ENV{DVBS2TX_DIR}/lib
        ${PC_DVBS2TX_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
          )

include("${CMAKE_CURRENT_LIST_DIR}/gnuradio-dvbs2txTarget.cmake")

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GR_DVBS2TX DEFAULT_MSG GR_DVBS2TX_LIBRARIES GR_DVBS2TX_INCLUDE_DIRS)
MARK_AS_ADVANCED(GR_DVBS2TX_LIBRARIES GR_DVBS2TX_INCLUDE_DIRS)
