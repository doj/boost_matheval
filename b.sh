#!/bin/sh
set -e
if [ "$1" = make ] ; then
    cd b
elif [ "$1" = clean ] ; then
    rm -rf b
    find . -name '*~' -delete
    exit 0
else
    rm -rf b
    mkdir b
    cd b
    cmake ..
fi
make -j4 check
make -j4 examples
