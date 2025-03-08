#!/bin/bash

set -e

if [ -z "$1" ]; then
    echo "Usage: $0 <path to .c file>"
    exit 1
fi

make
./compiler "$1"
gcc -m32 assembly.s -o out
./out
echo "Return value: $?"