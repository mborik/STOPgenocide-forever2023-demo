;;-----------------------------------------------------------------------------
; Every part is defined with this effect descriptor:
;
;     db  fx_demopart.pg   ; current fx 128k page
;                          ; (set bit.7 to LDIR given length, not decompress)
;     dw  fx_demopart      ; place where fx data lives
;     dw  fx_demopart.sync ; number of halts from start of demo to sync with
;     ... or ...
;     dw  fx_demopart.length

LDIR = #80

		db	fx_intro.pg
		dw	fx_intro
		dw	fx_intro.sync

		db	fx_micka.pg
		dw	fx_micka
		dw	fx_micka.sync

		db	fx_grinder.pg
		dw	fx_grinder
		dw	fx_grinder.sync

		db	fx_kitty_bank.pg | LDIR
		dw	fx_kitty_bank
		dw	fx_kitty_bank.length

		db	fx_plasma1.pg
		dw	fx_plasma1
		dw	fx_plasma1.sync

		db	fx_kitty.pg
		dw	fx_kitty
		dw	fx_kitty.sync

		db	fx_plasma2.pg
		dw	fx_plasma2
		dw	fx_plasma2.sync

		db	fx_simon_bank.pg | LDIR
		dw	fx_simon_bank
		dw	fx_simon_bank.length

		db	fx_lucyshow.pg
		dw	fx_lucyshow
		dw	fx_lucyshow.sync

		db	fx_lucy.pg
		dw	fx_lucy
		dw	fx_lucy.sync

		db	fx_simon.pg
		dw	fx_simon
		dw	fx_simon.sync

		db	fx_recyclefall.pg
		dw	fx_recyclefall
		dw	fx_recyclefall.sync

		db	fx_recytwist.pg | LDIR
		dw	fx_recytwist
		dw	fx_recytwist.length

		db	fx_recyplazmy.pg
		dw	fx_recyplazmy
		dw	fx_recyplazmy.sync
