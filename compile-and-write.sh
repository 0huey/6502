#!/bin/bash

if [[ $# -ne 1 ]]; then
	echo "provide .asm file"
	exit 1
fi

outfile=$(echo $1 | sed 's/asm$/bin/')

set -x

vasm6502_oldstyle -quiet -wdc02 -dotdir -Fbin -o $outfile $1

set +x

if [[ $? -ne 0 ]]; then
	exit 1;
fi

set -x

hexdump -C $outfile

minipro -p AT28C256 -w $outfile
