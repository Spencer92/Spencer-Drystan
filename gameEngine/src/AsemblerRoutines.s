;/*======================================================*/

;/*======================================================*/

			XDEF _clear


SCREEN:		equ	 8


_clear:		link	a6,#0
			movea.l	SCREEN(a6),a0
			move.l	#$1FFF,d1

clr:			clr.l	(a0)+
			dbra	d1,clr
			unlk	a6
			rts
