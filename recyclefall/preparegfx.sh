#!/bin/bash

function PAK() {
	rm -f $2
	zx0 -f $1
	mv -f "$1.zx0" $2
}

pushd gfx

justtop=(
	11
	12
)

for FN in "${justtop[@]}"; do
	head -c 4096 ${FN}.scr > ${FN}.part
done

topack=(
	01.scr
	02.scr
	03.scr
	04.scr
	11.part
	12.part
	13.scr
)

for FN in "${topack[@]}"; do
	PAK ${FN} ${FN%.*}.pak

	if [ "${FN##*.}" = "part" ]; then
		rm ${FN}
	fi
done

popd
