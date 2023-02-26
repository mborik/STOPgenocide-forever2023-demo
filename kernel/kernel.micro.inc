		define	ukernel 1

	ifndef PRESET.border
		define PRESET.border 0
	endif
	ifndef PRESET.paper
		define PRESET.paper 0
	endif

	module __microkernel__
		org	#4000

		block	#1800, 0
		block	#0300, PRESET.paper

		org	#8000

@microkernel:	di
		ld	sp,RUNZONE
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
		org	#8180

semafor:	db	0
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

		ld	a,(act128page)
		push	af
		and	#F8		; ponechame nastavenu vram
		or	MUSIC.page	; a prestrankujeme na banku s muzikou
		ld	bc,page128
		out	(c),a
		call	MUSIC.out
		pop	af
		ld	bc,page128
		out	(c),a

.imcall		ld	bc,#0101

		ld	hl,(FRAMES)
		inc	hl
		ld	(FRAMES),hl

		ld	hl,semafor	; kazde zacate prerusenie semafor inkrementuje
		inc	(hl)
		ld	a,(hl)		;; Ak je toto uz druhe (vnorene) prerusenie,
		cp	2		;; potom ihned koniec obsluhy tohto prerusenia
		jr	nc,.end		;; (ale semafor je inkrementnuty aby sme vedeli ze nastalo)

.underrun	ei
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
		ld	hl,semafor
		dec	(hl)
		jr	nz,.underrun

.end		pop	hl
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

attrhide:	ld	hl,22528
		ld	c,24
.atthd2:	ld	b,32
		push	bc
.atthd3:	ld	a,(hl)
		and	7
		jr	z,.atthd4
		dec	a
.atthd4:	push	af
		ld	a,(hl)
		and	56
		jr	z,.atthd5
		ld	c,8
		sub	c
		ld	c,a
		pop	af
		or	c
		jr	.atthd6
.atthd5:	ld	a,(hl)
		and	248
		ld	c,a
		pop	af
		or	c
.atthd6:	ld	(hl),a
		inc	hl
		djnz	.atthd3
		pop	bc
		dec	c
		jr	nz,.atthd2
		ret
	endmodule

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

		block	#1800, 0
		block	#0300, PRESET.paper

		ds	#0200 ; gap

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
