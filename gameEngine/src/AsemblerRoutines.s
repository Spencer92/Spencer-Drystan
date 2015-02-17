;/*======================================================*/

;/*======================================================*/

			XDEF _clear


SCREEN:		equ	 8


_clear:		link	a6,#0
			movem.l d0-d1,-(sp)			
			movea.l	SCREEN(a6),a0
			
			
			moveq.l #00,d1					
			move.l	#$03FF,d0

clr:	    move.l	d1,(a0)
			addq.l  #4,a0
			move.l  d1,(a0)
			addq.l  #4,a0
			move.l	d1,(a0)
			addq.l  #4,a0
			move.l  d1,(a0)
			addq.l  #4,a0
			move.l	d1,(a0)
			addq.l  #4,a0
			move.l  d1,(a0)
			addq.l  #4,a0
			move.l	d1,(a0)
			addq.l  #4,a0
			move.l  d1,(a0)		
			addq.l  #4,a0				
			dbra	d0,clr
					
			movem.l (sp)+,d0-d1
			unlk	a6
			rts
