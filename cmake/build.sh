#!/bin/sh
# ==========================================================================
#  Run cmake with a suitable (i.e. installed) generator!
# ==========================================================================
# The following generators are available on this platform:
#   Unix Makefiles              = Generates standard UNIX makefiles.
#   CodeBlocks - Unix Makefiles = Generates CodeBlocks project files.
#   Eclipse CDT4 - Unix Makefiles
#                               = Generates Eclipse CDT 4.0 project files.
#   KDevelop3                   = Generates KDevelop 3 project files.
#   KDevelop3 - Unix Makefiles  = Generates KDevelop 3 project files.

mkdir -p build-unix32-make-debug
cd build-unix32-make-debug
cmake -G "Unix Makefiles" -D CMAKE_BUILD_TYPE=Debug -D CMAKE_INSTALL_PREFIX=../runtime ../..
cd ..

mkdir -p build-unix32-make-release
cd build-unix32-make-release
cmake -G "Unix Makefiles" -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=../runtime ../..
cd ..
