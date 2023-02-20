#!/bin/bash

# demo builder (c) 2019-2023 mborik/SinDiKat
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

rm -f bank*

pushd build
rm -f stopgeno*
popd

subdirs=(
	kernel
	intro
	priskocmicka
	music
)

for D in "${subdirs[@]}"; do
	pushd "${D}"
	rm -f final.bin *.lst *.pak *.sna *.tap
	popd
done
