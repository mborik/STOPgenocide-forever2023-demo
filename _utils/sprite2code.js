fs = require('fs');
path = require('path');

if (process.argv.length < 5)
	return console.error('few arguments, run "node sprite2code.js {file.sprite} {scradr(hex)} {w}"!');

const potentat = {};
const incPotentat = s => {
	if (potentat[s])
		potentat[s]++;
	else
		potentat[s] = 1;
}

const toHex = (num, width) => {
	let a = num.toString(16);
	return ('00000000' + a).substr(-Math.max(width || 2, a.length));
}

const downHL = (hl) => {
	let h = hl >>> 8,
		l = hl & 255;

	h++;
	if (!(h & 7)) {
		l += 32;
		if (l < 256)
			h -= 8;
	}

	return (h << 8) | (l & 255);
};

//-----------------------------------------------------------------------------

const src = fs.readFileSync(process.argv[2]);
const baseScrAdr = parseInt(process.argv[3], 16);
const w = parseInt(process.argv[4], 10);
const h = src.length / w;
const orMode = /^or$/i.test(process.argv[5]);

let dst = '';
let x, y, i, b, c, scradr = baseScrAdr;
let ptr, ptrSet, ptrInced, ptrLast = -1;

for (y = 0; y < h; y++) {
	ptr = scradr;
	ptrSet = false;
	ptrInced = 0;

	for (x = 0; x < w; x++, ptr++) {
		i = (y * w) + x;
		b = src[i];

		if (orMode && !b) {
			if (ptrSet)
				ptrInced++;
			continue;
		}

		if (!ptrSet) {
			if (orMode) {
				const delta = ptr - ptrLast;
				if (delta === 255) {
					dst += `\t	inc	h\n`;
					dst += `\t	dec	l\n`;
				}
				else if (delta === 256) {
					dst += `\t	inc	h\n`;
				}
				else if (delta === 257) {
					dst += `\t	inc	h\n`;
					dst += `\t	inc	l\n`;
				}
				else {
					dst += `\t	ld	hl,#${toHex(ptr, 4)}\n`;
				}

				ptrLast = ptr;
			}

			ptrSet = true;
		}
		else {
			if (orMode) {
				ptrLast = ptr;

				if (ptrInced > 2) {
					dst += `\t	ld	l,#${toHex(ptr & 0xff)}\n`;
					ptrInced = 0;
				}
				else while (ptrInced) {
					dst += `\t	inc	l\n`;
					ptrInced--;
				}
			}
			else {
				dst += `\t	inc	l\n`;
			}
		}

		if (orMode) {
			dst += `\t	ld	a,(hl)\n`;
			dst += `\t	or	#${toHex(b)}\n`;
			dst += `\t	ld	(hl),a\n`;

			ptrInced++;
		}
		else {
			dst += `\t	ld	(hl),#${toHex(b)}\n`;
		}

		incPotentat(toHex(b));
	}

	scradr = downHL(scradr);
}

const pots2sort = [];
for (s in potentat) {
	if (potentat[s] > 1)
		pots2sort.push({ id: s, count: potentat[s] });
}
pots2sort.sort((a, b) => b.count - a.count);

if (orMode) {
	const [ rB, rC, rD, rE ] = pots2sort.slice(0, 4).map(v => v.id);
	dst = (`
		ld	bc,#${rB}${rC}
		ld	de,#${rD}${rE}
` + dst
		.replace(new RegExp(`#${rB}`, 'ig'), 'b')
		.replace(new RegExp(`#${rC}`, 'ig'), 'c')
		.replace(new RegExp(`#${rD}`, 'ig'), 'd')
		.replace(new RegExp(`#${rE}`, 'ig'), 'e'))
		.slice(1);
}
else {
	const [ rA, rB, rC, rD, rE ] = pots2sort.slice(0, 5).map(v => v.id);
	dst = (`
		${rA > 0 ? `ld	a,${rA}` : 'xor	a'}
		ld	bc,#${rB}${rC}
		ld	de,#${rD}${rE}
` + dst
		.replace(new RegExp(`#${rA}`, 'ig'), 'a')
		.replace(new RegExp(`#${rB}`, 'ig'), 'b')
		.replace(new RegExp(`#${rC}`, 'ig'), 'c')
		.replace(new RegExp(`#${rD}`, 'ig'), 'd')
		.replace(new RegExp(`#${rE}`, 'ig'), 'e'))
		.slice(1);
}

fs.writeFileSync(path.parse(process.argv[2]).name + '.inc', dst, { flag: 'w' });
