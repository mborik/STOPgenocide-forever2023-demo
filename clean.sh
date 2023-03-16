#!/bin/bash

# demo cleaner (c) 2019-2023 mborik/SinDiKat
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
	hellokitty
	plasma1
	plasma2
	simon
	lucy
	lucyshow
	recyshow
	recytwist
	recyplazmy
	vodocat
	music
)

for D in "${subdirs[@]}"; do
	pushd "${D}"
	rm -f final.bin *.lst *.sna *.tap
	find . -name "*.pak" -type f -delete
	popd
done
