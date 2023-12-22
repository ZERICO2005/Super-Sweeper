	
	assume adl=1
	
	section .text
	public  _fillRect
	public	_fillText
	public  _horiz
	public  _vert
	public  _plot
	public  _plotFast
	public	_addPointer
	public	_fillMemory
	; +9 high, +10 mid, +11, low
	
	_fillMemory:
		; +3 value, +4 base, +7 len
		; -1 color
		ld hl,-7	; 2*3 + 1*1 byte
		push ix		; adds 2*3 bytes
		ld ix, 0	; put 0 in ix
		add ix, sp	; add sp to ix
		add hl, sp	; add sp to hl
		ld sp, hl	; put hl in sp
		

		ld a,(ix+3) 	;Load Value
		ld de,(ix+4) 	;Load Base
		inc de
		ld bc,(ix+7)	;Load Length
		dec bc
		ld (hl),a		;Writes Value to Address
		ldir			; Where the magic happens
		
		ld sp, ix
		pop ix
		ret
	
	
	_fillRect:
		; +6 x1, +9 y1, +12 x2, +15 y2
		; -3 jump, -6 base, -7 color, -8 address
		ld hl,-8	; (4 * 3) + (2 * 3) byte
		push ix		; adds (2 * 3) bytes
		ld ix, 0	; put 0 in ix
		add ix, sp	; add sp to ix
		add hl, sp	; add sp to hl
		ld sp, hl	; put hl in sp
		
		ld hl,($D657F0)
		ld a,(hl) ;D052F4
		ld (ix-7),a
		
		ld hl,320		;320 - x2
		dec (ix+12)
		ld de,(ix+12)	;loads x2 into de
		sbc hl,de		;subtracts
		ld (ix-3),hl	;store jump

;		ld hl,0			;23 vs 20 clock cycles, so this is slower
;		ld de,(ix+10)	; multiply by 256 method A
;		ld e,0			;
;		ld deu,(ix+10)	; multiply by 256 method B
;		ld d,(ix+11)	;
;		add hl,de		; copys de to hl
;		ld f,0 			; divide hl by 4
;		rr h
;		rr l
;		ld f,0
;		rr h
;		rr l
;		add hl,de		; * 320
		
		;0xD40000 + x1 + (y1 * 320)
		ld hl,(ix+9) 	; loads y1
		add hl,hl 		; 2
		add hl,hl  		; 4
		add hl,hl 		; 8
		add hl,hl 		; 16
		add hl,hl  		; 32
		add hl,hl  		; 64
		push hl 		; store 64 in base temporarily
		add hl,hl		; 128
		add hl,hl 		; 256
		pop de			; loads 64 inside of base
		add hl,de 		; add de to hl (256 + 64)

		
		
		ld de,$D40000
		add hl,de 		; add VRAM
		ld de,(ix+6)	; load x1
		add hl,de 		; add x1
;		ld (ix-18),hl 	; store 320 in base

		inc (ix-3) 		;Jump related

		ld a,(ix+15)	; loads y2
		loopY0:
			ld (ix-8),a
			ld a,(ix-7)
;			ld hl
			ld (ix-6),hl 	;load hl into base
			ld de,(ix-6) 	;set de to base
			inc de
			ld bc,(ix+12)
			ld (hl),a;Writes color to screen
			ldir
			ld de,(ix-3)
			add hl,de
			ld a,(ix-8)
			dec a
		jr nz,loopY0
		
		ld sp, ix
		pop ix
		ret
		
	_horiz:
		; +6 x1, +9 y, +12 x2
		; -1 color
		ld hl,-1	; 0*3 + 1*1 byte
		push ix		; adds 2*3 bytes
		ld ix, 0	; put 0 in ix
		add ix, sp	; add sp to ix
		add hl, sp	; add sp to hl
		ld sp, hl	; put hl in sp
		
		ld hl,($D657F0) ; Loads color in a two step process
		ld a,(hl) ;D052F4
;		ld (ix-3),a 	; No need to store it this time
		
		;0xD40000 + x1 + x2 + (y * 320)
		ld hl,(ix+9) 	; loads y
		add hl,hl 		; 2
		add hl,hl  		; 4
		add hl,hl 		; 8
		add hl,hl 		; 16
		add hl,hl  		; 32
		add hl,hl  		; 64
		push hl 		; store 64 in base temporarily
		add hl,hl		; 128
		add hl,hl 		; 256
		pop de			; loads 64 inside of base
		add hl,de 		; add de to hl (256 + 64)
		ld de,$D40000
		add hl,de 		; add VRAM
		ld de,(ix+6)	; load x1
		add hl,de 		; add x1
;		ld (ix-6),hl 	; store 320 in base

		push hl ;load hl into base
		pop de 	;set de to base
		inc de
		ld bc,(ix+12)
		dec bc
		ld (hl),a;Writes color to screen
		ldir			; Where the magic happens
		
		ld sp, ix
		pop ix
		ret
		
		
		
	_vert:
		; +6 x, +9 y1, +12 y2
		push ix
		ld ix, 0
		add ix, sp
		
		ld hl,($D657F0)
		ld c,(hl) ;D052F4
		
		;0xD40000 + x1 + (y1 * 320)
		ld hl,(ix+9) 	; loads y1
		add hl,hl 		; 2
		add hl,hl  		; 4
		add hl,hl 		; 8
		add hl,hl 		; 16
		add hl,hl  		; 32
		add hl,hl  		; 64
		push hl 		; store 64 in base temporarily
		add hl,hl		; 128
		add hl,hl 		; 256
		pop de			; loads 64 inside of base
		add hl,de 		; add de to hl (256 + 64)
		ld de,$D40000
		add hl,de 		; add VRAM
		ld de,(ix+6)	; load x1
		add hl,de 		; add x1
		
		ld de,320
		
		ld a,(ix+12)	; loads y2
		
		loopY1:
		
			ld (hl),c	;Writes color to screen
			add hl,de
			dec a
			
		jr nz,loopY1
		
		pop ix
		ret
		
		
	_plot:
		; +6 x, +9 y
		push ix
		ld ix, 0
		add ix, sp
		
		ld hl,($D657F0)
		ld a,(hl)
		
		;0xD40000 + x1 + x2 + (y * 320)
		ld hl,(ix+9) 	; loads y
		add hl,hl 		; 2
		add hl,hl  		; 4
		add hl,hl 		; 8
		add hl,hl 		; 16
		add hl,hl  		; 32
		add hl,hl  		; 64
		push hl 		; store 64 in base temporarily
		add hl,hl		; 128
		add hl,hl 		; 256
		pop de			; loads 64 inside of base
		add hl,de 		; add de to hl (256 + 64)
		ld de,$D40000
		add hl,de 		; add VRAM
		ld de,(ix+6)	; load x
		add hl,de 		; add x
		
		ld (hl),a
		
		pop ix
		ret
		
	_plotFast:
		; +6 z
		push ix
		ld ix, 0
		add ix, sp
		
		ld hl,($D657F0) ; Loads color in a two step process
		ld a,(hl) 		;D052F4
		ld de,(ix+6)
		ld (de),a
		
		pop ix
		ret
		
	_addPointer:
		; +6 x, +9 y
		push ix
		ld ix, 0
		add ix, sp
		
		ld hl,(ix+6)	; Loads the Address of X
		ld hl,(hl)		; Loads the value at the Address of X
		ld de,(ix+9)	; Y to add
		add hl,de
		ex de,hl		; Swaps HL and DE
		ld hl,(ix+6)	; Loads the Address of X
		ld (hl),de
		
		pop ix
		ret
		
		
		
		
	_fillText:
		; +6 x1, +9 y1, +12 x2, +15 y2
		; -1 color, -4 jump, -7 base
		ld hl,-3	; 1*3 + 0*1 byte
		push ix		; adds 2*3 bytes
		ld ix, 0	; put 0 in ix
		add ix, sp	; add sp to ix
		add hl, sp	; add sp to hl
		ld sp, hl	; put hl in sp
		
		ld hl,($D657F0)
		ld d,(hl) ;Close to $D052F4
		
		ld hl,320		;320 - x2
		dec (ix+12)
		ld de,(ix+12)	;loads x2 into de
		sbc hl,de		;subtracts
		ld (ix-4),hl	;store jump
		
		;0xD40000 + x1 + (y1 * 320)
		ld hl,(ix+9) 	; loads y1
		add hl,hl 		; 2
		add hl,hl  		; 4
		add hl,hl 		; 8
		add hl,hl 		; 16
		add hl,hl  		; 32
		add hl,hl  		; 64
		push hl 		; store 64 in base temporarily
		add hl,hl		; 128
		add hl,hl 		; 256
		pop de			; loads 64 inside of base
		add hl,de 		; add de to hl (256 + 64)
		ld de,$D40000
		add hl,de 		; add VRAM
		ld de,(ix+6)	; load x1
		add hl,de 		; add x1
		ld (ix-7),hl
		
		ld de,320
		
		ld b,(ix+15)	; loads y2
		ld c,(ix+12)	; loads x2
		loopYF:
			loopXF:
			
				ld hl,(ix-7)
				ld a,(hl)
				dec a ;tests if a is 0
				jr nz,loopZF
				ld (ix-7),d	;Writes color to screen
				loopZF:
				
				inc (ix-7)
				dec b
			jr nz,loopXF
			
			
			push de
			ld de,(ix-4)
			add hl,de	; Adds jump for the next line
			pop de
			dec c
		jr nz,loopYF
		
		ld sp, ix
		pop ix
		ret
	
	
	