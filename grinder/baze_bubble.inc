; ASM data file from a ZX-Paintbrush picture
; line based output of pixel data in effecient zig-zag format
; A->B->C->D
; D->C->B->A
; ...
; 0 = end marker

		db	#07, #FF, #E7, #FF
		db	#FF, #DB, #FF, #07
		db	#0F, #FF, #DB, #FF
		db	#FF, #E7, #FF, #0F
		db	#0F, #FF, #FF, #FF
		db	#FF, #F1, #FF, #9F
		db	#9F, #FF, #EE, #FF
		db	#FF, #EE, #FF, #DF
		db	#FF, #FF, #EE, #FF
		db	#FF, #F1, #FF, #FF
		db	#FF, #FF, #FF, #FF
		db	#0F, #00, #00, #F0
		db	#CF, #FF, #FF, #F3
		db	#FD, #FF, #FF, #BF
		db	#BF, #FF, #FF, #FD
		db	#FE, #FF, #F7, #7F
		db	#7F, #FB, #FF, #FE
		db	#DE, #2A, #33, #7F
		db	#7E, #AA, #AA, #FE
		db	#DE, #2A, #2B, #7F
		db	#7E, #72, #69, #DE
		db	#DE, #FF, #FF, #7F
		db	#7F, #FF, #EF, #DE
		db	#FE, #FF, #FF, #7D
		db	#7E, #FF, #FF, #FE
		db	#9E, #D5, #DD, #7C
		db	#7A, #AB, #D5, #3E
		db	#5E, #D5, #AB, #7A
		db	#7C, #D9, #C3, #BE
		db	#FE, #FF, #FB, #7F
		db	#7F, #FF, #FF, #FE
		db	#FE, #FF, #FF, #7F
		db	#78, #F9, #C7, #9E
		db	#3E, #DF, #75, #7B
		db	#7B, #79, #F7, #5E
		db	#BE, #C7, #F3, #78
		db	#7B, #FF, #FF, #FE
		db	#FE, #FF, #FF, #7B
		db	#7F, #FF, #FF, #FE
		db	#FE, #FF, #FF, #7F
		db	#7E, #6B, #AC, #DE
		db	#7E, #AB, #AB, #7D
		db	#7D, #AB, #AB, #5E
		db	#DE, #9C, #67, #7E
		db	#7F, #EF, #FF, #DE
		db	#DE, #FF, #EF, #7F
		db	#BF, #FF, #FF, #FD
		db	#FD, #FF, #FF, #BF
		db	#CF, #FF, #FF, #F3
		db	#0F, #00, #00, #F0
		db	#00
