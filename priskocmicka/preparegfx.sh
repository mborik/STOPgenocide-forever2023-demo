#!/bin/bash

function PAK() {
	rm -f $2
	zx0 -f $1
	mv -f "$1.zx0" $2
}

pushd gfx

justbottom=(
	05
	06
	07
	11
	12
	13
	14
	15
)

for FN in "${justbottom[@]}"; do
	tail -c +4097 ${FN}.scr > ${FN}.part
done

topack=(
	01.scr
	02.scr
	03.scr
	04.scr
	05.part
	06.part
	07.part
	08.scr
	09.scr
	11.part
	12.part
	13.part
	14.part
	15.part
	title.scr
)

for FN in "${topack[@]}"; do
	PAK ${FN} ${FN%.*}.pak

	if [ "${FN##*.}" = "part" ]; then
		rm ${FN}
	fi
done

popd
