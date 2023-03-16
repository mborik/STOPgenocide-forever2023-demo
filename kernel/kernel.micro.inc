		define	ukernel 1

	ifndef PRESET.border
		define PRESET.border 0
	endif
	ifndef PRESET.paper
		define PRESET.paper 0
	endif

	module __microkernel__
	ifndef PRESET.noclearscr
		org	#4000

		block	#1800, 0
		block	#0300, PRESET.paper
	endif

;;- COMMON FUNCTIONS ----------------------------------------------------------
		org	xchg.vram

	module commons
vram:		ld	a,#1D
		xor	#0A
		ld	(xchg.vram+1),a
bnk:		ld	(act128page),a
		ld	bc,page128
		out	(c),a
		ret

depack:		module zx0
		include "dzx0_fast.a80"
		endmodule

downhl		inc	h
		ld	a,h
		and	7
		ret	nz
		ld	a,32
		add	a,l
		ld	l,a
		ret	c
		ld	a,-8
		add	a,h
		ld	h,a
		ret

downde		inc	d
		ld	a,d
		and	7
		ret	nz
		ld	a,e
		add	a,32
		ld	e,a
		ret	c
		ld	a,d
		sub	8
		ld	d,a
		ret

upde		dec	d
		ld	a,d
		inc	a
		and	7
		ret	nz
		ld	a,e
		sub	32
		ld	e,a
		ret	c
		ld	a,d
		add	a,8
		ld	d,a
		ret

waitforit	ei
		halt
		ld	hl,(FRAMES)
		xor	a
		sbc	hl,bc
		jr	c,.waitforit
		ret
	endmodule

@microkernel:	di
		ld	sp,basesp
		ld	a,PRESET.border
		out	(254),a
		ld	(actborder),a
		ld	hl,-1
		ld	(FRAMES),hl
		ld	a,high vector
		ld	i,a
		im	2
		jp	baseloop

;;- INTERRUPT -----------------------------------------------------------------
		org	#8181

interrupt:	push	af		; zakladne osetrenie prerusenia
		ld	a,(actborder)	; s volanim hudobneho hradla
		out	(254),a
		push	bc
		push	de
		push	hl
		exx
		ex	af,af'
		push	ix
		push	iy
		push	af
		push	bc
		push	de
		push	hl

		ld	a,MUSIC.page	; a prestrankujeme na banku s muzikou
		ld	bc,page128
		out	(c),a
		call	MUSIC.out
		ld	a,(act128page)
		ld	bc,page128
		out	(c),a

.imcall		ld	bc,#0101

		ld	hl,(FRAMES)
		inc	hl
		ld	(FRAMES),hl

		ld	a,(act128page)
		push	af
		and	#F8		; ponechame nastavenu vram
		or	MUSIC.page	; a prestrankujeme na banku s muzikou
		ld	bc,page128
		out	(c),a
		call	MUSIC.play
		pop	af
		ld	bc,page128
		out	(c),a

		pop	hl
		pop	de
		pop	bc
		pop	af
		pop	iy
		pop	ix
		ex	af,af'
		exx
		pop	hl
		pop	de
		pop	bc
		pop	af
		ei
		ret

;;-----------------------------------------------------------------------------
		org	#8200

vector:		block	257,#81

; init music
baseloop:	ld	a,MUSIC.page | #10
		call	xchg.bnk
		call	MUSIC.init
	ifdef PRESET.waitfor
		ld	bc,PRESET.waitfor - 1
		ld	(FRAMES),bc
.muswaiter:	push	bc
		call	MUSIC.play
		pop	bc
		dec	bc
		ld	a,b
		or	c
		jr	nz,.muswaiter
	endif
		ld	a,#10
		call	xchg.bnk
		call	RUNZONE

		ld	a,2
		ld	(actborder),a
.deadend:	ei
		halt
		jr	.deadend


		slot 3
		page 7

		org	#C000

	ifndef PRESET.noclearscr
		block	#1800, 0
		block	#0300, PRESET.paper

		ds	#0200 ; gap
	else
		ds	#1D00
	endif

MUSIC.buffer	dw	0, 0, 0
		db	0, #3F ; mixer
		db	0, 0, 0
		dw	0
		db	-1
		dw	0

		align 256
		define OUT2BUFFER
		include "../music/sqt.a80"

	endmodule
