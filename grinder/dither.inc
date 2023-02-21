; This can be either %11100000 (top of memory) or %11000000 (start of page).
T		equ	%11100000
D0		equ	%00000000
D1		equ	%00001000
D2		equ	%00010000
D3		equ	%00011000

		; Dithering matrix offset 0..3 (higher byte of sprite address).

		db	T|D0, T|D1, T|D2, T|D3, T|D0, T|D1, T|D2, T|D3, T|D0, T|D1, T|D2, T|D3, T|D0, T|D1, T|D2, T|D3
		db	T|D0, T|D1, T|D2, T|D3, T|D0, T|D1, T|D2, T|D3, T|D0, T|D1, T|D2, T|D3, T|D0, T|D1, T|D2, T|D3
		db	T|D0, T|D1, T|D2, T|D3, T|D0, T|D1, T|D2, T|D3, T|D0, T|D1, T|D2, T|D3, T|D0, T|D1, T|D2, T|D3
		db	T|D0, T|D1, T|D2, T|D3, T|D0, T|D1, T|D2, T|D3, T|D0, T|D1, T|D2, T|D3, T|D0, T|D1, T|D2, T|D3
		db	T|D0, T|D1, T|D2, T|D3, T|D0, T|D1, T|D2, T|D3, T|D0, T|D1, T|D2, T|D3, T|D0, T|D1, T|D2, T|D3
		db	T|D0, T|D1, T|D2, T|D3, T|D0, T|D1, T|D2, T|D3, T|D0, T|D1, T|D2, T|D3, T|D0, T|D1, T|D2, T|D3
		db	T|D0, T|D1, T|D2, T|D3, T|D0, T|D1, T|D2, T|D3, T|D0, T|D1, T|D2, T|D3, T|D0, T|D1, T|D2, T|D3
		db	T|D0, T|D1, T|D2, T|D3, T|D0, T|D1, T|D2, T|D3, T|D0, T|D1, T|D2, T|D3, T|D0, T|D1, T|D2, T|D3
		db	T|D0, T|D1, T|D2, T|D3, T|D0, T|D1, T|D2, T|D3, T|D0, T|D1, T|D2, T|D3, T|D0, T|D1, T|D2, T|D3
		db	T|D0, T|D1, T|D2, T|D3, T|D0, T|D1, T|D2, T|D3, T|D0, T|D1, T|D2, T|D3, T|D0, T|D1, T|D2, T|D3
		db	T|D0, T|D1, T|D2, T|D3, T|D0, T|D1, T|D2, T|D3, T|D0, T|D1, T|D2, T|D3, T|D0, T|D1, T|D2, T|D3
		db	T|D0, T|D1, T|D2, T|D3, T|D0, T|D1, T|D2, T|D3, T|D0, T|D1, T|D2, T|D3, T|D0, T|D1, T|D2, T|D3
		db	T|D0, T|D1, T|D2, T|D3, T|D0, T|D1, T|D2, T|D3, T|D0, T|D1, T|D2, T|D3, T|D0, T|D1, T|D2, T|D3
		db	T|D0, T|D1, T|D2, T|D3, T|D0, T|D1, T|D2, T|D3, T|D0, T|D1, T|D2, T|D3, T|D0, T|D1, T|D2, T|D3
		db	T|D0, T|D1, T|D2, T|D3, T|D0, T|D1, T|D2, T|D3, T|D0, T|D1, T|D2, T|D3, T|D0, T|D1, T|D2, T|D3
		db	T|D0, T|D1, T|D2, T|D3, T|D0, T|D1, T|D2, T|D3, T|D0, T|D1, T|D2, T|D3, T|D0, T|D1, T|D2, T|D3
