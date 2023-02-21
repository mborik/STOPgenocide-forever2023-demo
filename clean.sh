#!/bin/bash

# demo builder (c) 2019-2023 mborik/SinDiKat
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

rm -f bank*

pushd build
rm -f *.tap
popd

subdirs=(
	kernel
	intro
	priskocmicka
	grinder
	music
)

for D in "${subdirs[@]}"; do
	pushd "${D}"
	rm -f final.bin *.lst *.pak *.sna *.tap
	popd
done
