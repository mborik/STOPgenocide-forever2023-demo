#!/bin/bash

# demo builder (c) 2019-2023 mborik/SinDiKat
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Utils required in PATH to successful build:
# latest `sjasmplus` from https://github.com/z00m128/sjasmplus
# `zx0` from https://github.com/einar-saukas/ZX0

ASM="sjasmplus"
OUTPUT="stopgeno.tap"

function ASM() {
	FULLPATH=$(realpath $1)
	shift
	sjasmplus --nologo --fullpath --color=off --msg=war $FULLPATH $@
}
function PAK() {
	rm -f $2
	zx0 -f $1
	mv -f "$1.zx0" $2
}

cd build
rm -f ${OUTPUT}

# Every part is compiled using this cmds pattern:
#
#> cd ../demopart
#> ASM demopart.a80 -DisFX --lst=demopart.lst
#> PACK final.bin final.pak

cd ..
rm -f output bank*
ASM pg1fx.a80 --lst=kernel/pg1fx.lst --exp=kernel/pg1fx.inc
PAK bank1 bank1.pak
ASM pg3fx.a80 --lst=kernel/pg3fx.lst --exp=kernel/pg3fx.inc
PAK bank3 bank3.pak
ASM pg4fx.a80 --lst=kernel/pg4fx.lst --exp=kernel/pg4fx.inc
PAK bank4 bank4.pak
ASM pg6fx.a80 --lst=kernel/pg6fx.lst --exp=kernel/pg6fx.inc
PAK bank6 bank6.pak
ASM pg7fx.a80 --lst=kernel/pg7fx.lst --exp=kernel/pg7fx.inc
PAK bank7 bank7.pak

cd kernel
PAK loading.scr loading.pak
ASM kernel.a80 -DOUTPUT="../build/${OUTPUT}" --lst=kernel.lst --exp=constants.inc
