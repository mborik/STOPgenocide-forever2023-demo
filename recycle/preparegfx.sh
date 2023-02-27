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
	dd if=${FN}.scr of=${FN}.part bs=4096 count=1 iflag=skip_bytes status=none
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
