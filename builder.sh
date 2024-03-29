#!/bin/bash

# demo builder (c) 2019-2023 mborik/SinDiKat
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Utils required in PATH to successful build:
# latest `sjasmplus` from https://github.com/z00m128/sjasmplus
# `zx0` from https://github.com/einar-saukas/ZX0

ASM="sjasmplus"
OUTPUT="STOPgenocide.tap"

function ASM() {
	FULLPATH=$(realpath $1)
	shift
	sjasmplus --nologo --fullpath --color=off --msg=war $FULLPATH $@
}
function PAK() {
	rm -f $2
	zx0 -f $1 &> /dev/null
	mv -f "$1.zx0" $2
}

cd build
rm -f ${OUTPUT}

# Every part is compiled using this cmds pattern:
#
#> cd ../demopart
#> ASM demopart.a80 -DisFX --lst=demopart.lst
#> PAK final.bin final.pak

cd ../intro
ASM intro.a80 -DisFX --lst=intro.lst
PAK final.bin final.pak

cd ../priskocmicka
. preparegfx.sh &> /dev/null
ASM priskocmicka.a80 -DisFX --lst=priskocmicka.lst
PAK final.bin final.pak

cd ../grinder
ASM grinder.a80 -DisFX --lst=grinder.lst
PAK final.bin final.pak

cd ../plasma1
ASM plasma1.a80 -DisFX --lst=plasma1.lst
PAK final.bin final.pak

cd ../hellokitty
PAK pattern.bin pattern.pak
ASM bank.a80 -DisFX --lst=bank.lst
ASM hellokitty.a80 -DisFX --lst=hellokitty.lst
PAK final.bin final.pak

cd ../lucyshow
ASM lucyshow.a80 -DisFX --lst=lucyshow.lst
PAK final.bin final.pak

cd ../lucy
ASM lucy.a80 -DisFX --lst=lucy.lst
PAK final.bin final.pak

cd ../simon
ASM anim.a80 --exp=anim.inc
PAK anim.bin anim.pak
ASM bank.a80 -DisFX --lst=bank.lst
ASM simon.a80 -DisFX --lst=simon.lst
PAK final.bin final.pak

cd ../plasma2
ASM plasma2.a80 -DisFX --lst=plasma2.lst
PAK final.bin final.pak

cd ../recyshow
. preparegfx.sh &> /dev/null
ASM recyshow.a80 -DisFX --lst=recyshow.lst
PAK final.bin final.pak

cd ../recytwist
ASM recytwist.a80 -DisFX --lst=recytwist.lst
PAK final.bin final.pak
ASM bank.a80 -DisFX --lst=bank.lst

cd ../recyplazmy
ASM recyplazmy.a80 -DisFX --lst=recyplazmy.lst
PAK final.bin final.pak

cd ../vodocat
ASM vodocat.a80 -DisFX --lst=vodocat.lst
PAK final.bin final.pak
ASM bank.a80 -DisFX --lst=bank.lst

# banks composition
cd ..
rm -f bank*
ASM pg0fx.a80 --lst=kernel/pg0fx.lst --exp=kernel/pg0fx.inc
ASM pg1fx.a80 --lst=kernel/pg1fx.lst --exp=kernel/pg1fx.inc
PAK bank1 bank1.pak
ASM pg3fx.a80 --lst=kernel/pg3fx.lst --exp=kernel/pg3fx.inc
### PAK bank3 bank3.pak
ASM pg4fx.a80 --lst=kernel/pg4fx.lst --exp=kernel/pg4fx.inc
### PAK bank4 bank4.pak
ASM pg6fx.a80 --lst=kernel/pg6fx.lst --exp=kernel/pg6fx.inc
### PAK bank6 bank6.pak
ASM pg7fx.a80 --lst=kernel/pg7fx.lst --exp=kernel/pg7fx.inc
PAK bank7 bank7.pak

cd kernel
PAK loading.scr loading.pak
ASM kernel.a80 --lst=kernel.lst --exp=constants.inc
PAK final.bin final.pak
ASM loader.a80 -DOUTPUT="\"../build/${OUTPUT}\"" --lst=loader.lst
