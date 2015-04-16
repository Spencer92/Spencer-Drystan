
	xdef	_psg_write
	

GEMDOS		equ	1
PSG_SELECT	equ	$FF8800
PSG_WRITE	equ	$FF8802



;WRITE_PSG(int reg,uint8 val)
;LOCAL
SELECT		equ	-2
WRITE		equ	-4
;
REG		equ	8
VAL		equ	10


_psg_write:	
		link	a6,#-8
		movem.l d0-d3/a0-a2,-(sp)
		bsr	super
		lea		PSG_SELECT,a0
		lea		PSG_WRITE,a1
		move.w	REG(a6),d0
		move.b	d0,(a0)
		move.w	VAL(a6),d0
		move.b	d0,(a1)
		bsr	unsuper
		movem.l	(sp)+,d0-d3/a0-a2
		unlk	a6
		rts
	




super:		link	a6,#0
		movem.l d0-d3/a0-a2,-(sp)
		clr.l	-(sp)
		move.w	#32,-(sp)
		trap	#GEMDOS
		addq.l	#6,sp
		move.l	d0,oldssp
		movem.l (sp)+,d0-d3/a0-a2
		unlk	a6
		rts
		
unsuper:
		link	a6,#0
		movem.l	d0-d3/a0-a2,-(sp)
		move.l	oldssp,-(sp)
		move.w	#32,-(sp)
		trap	#GEMDOS
		addq.l	#6,sp
		movem.l	(sp)+,d0-d3/a0-a2
		unlk	a6
		rts
		
	
		even	
oldssp:		dc.l	0























