#!/bin/bash

function PAK() {
	rm -f $2
	zx0 -f $1
	mv -f "$1.zx0" $2
}

pushd gfx

topack=(
	01.scr
	02.scr
	03.scr
	04.scr
	05.scr
	06.scr
	11.scr
	12.scr
	13.scr
)

for FN in "${topack[@]}"; do
	PAK ${FN} ${FN%.*}.pak
done

popd
