#!/bin/bash

function PAK() {
	rm -f $2
	zx0 -f $1
	mv -f "$1.zx0" $2
}

pushd gfx

PAK 01.scr 01.pak

tail -c +6145 04.scr > 04.tmp
head -c 352 04.tmp > 04.attrs
rm -f 04.tmp
PAK 04.attrs 04.attrs.pak
rm -f 04.attrs

popd
