;/*======================================================*/

;/*======================================================*/

			XDEF _clear
			
			XDEF _phys_Base
			
			XDEF _set_Screen
			
			XDEF _enterSuper
			
			XDEF _exitSuper


SCREEN:		equ	 8
PHYSBASE:   equ  16




_clear:		link	a6,#0
			movem.l d0-d1,-(sp)			
			movea.l	SCREEN(a6),a0
			
			
			moveq.l #00,d1					
			move.l	#$03FF,d0

clr:	    move.l	d1,(a0)
			addq.l  #4,a0
			move.l  d1,(a0)
			addq.l  #4,a0
			move.l d1,(a0)
			addq.l  #4,a0
			move.l  d1,(a0)
			addq.l  #4,a0
			move.l d1,(a0)
			addq.l  #4,a0
			move.l  d1,(a0)
			addq.l  #4,a0
			move.l d1,(a0)
			addq.l  #4,a0
			move.l  d1,(a0)		
			addq.l  #4,a0				
			dbra	d0,clr
					
			movem.l (sp)+,d0-d1
			unlk	a6
			rts
			
;/*======================================================*/

SR_SAVE		equ	-2			
_phys_Base:
			link a6,#-2
			movem.l d1/a0,-(sp)			
			moveq.l #0,d1
			
			
			jsr _enterSuper
			move.w	sr,SR_SAVE(a6)
		 	move.w	#$2700,sr  		;turn off the interupts
		
			move.l #$ff8200,a0
			movep.w 1(a0),d1
			move.w	SR_SAVE(a6),sr 			;best to turn them back on
			
			jsr _exitSuper			
		
			lsl.l #8,d1
			clr.b d1
			
			move.l d1,d0
			
			movem.l (sp)+,d1/a0
			unlk a6
			rts
;/*======================================================*/




;/*======================================================*/



_set_Screen
				
			link a6,#0
			movem.l d0/d3-d4/a3-4,-(sp)
			movea.l	SCREEN(a6),a4
			clr.l 	d3
			
			move.l  a4,d3
			lsr.l #8,d3

		
			
			
			clr.l	-(sp)
			move.w	#32,-(sp)
			trap	#1
			addq.l	#6,sp
			move.l	d0,old_stack
			movea.l  #$FFFF8200,a3	
			adda.l	#1,a3			
			movep.w d3,(a3)
			move.l	old_stack,-(sp)
			move.w	#32,-(sp)
			trap	#1
			addq.l	#6,sp
	
			
			movem.l (sp)+,d0/d3-4/a3-4
			unlk a6
			rts
;/*======================================================*/



;/*======================================================*/

_enterSuper:                     		;go into super user mode
   			link	a6,#0
			movem.l d0-d1/a0,-(sp)
			clr.l -(a7)
   			move.w #32,-(a7)  
   			trap #1    
   			adda.l #6,a7  
  			move.l d0,old_stack
   			movem.l  (sp)+,d0-d1/a0
			unlk	a6
			rts		
			

_exitSuper:	
			link	a6,#0;leave super mode
			movem.l d0-d1/a0,-(sp)
			move.l old_stack,-(a7)
   			move.w #32,-(a7)
   			trap #1    
   			addq.l #6,a7
			movem.l  (sp)+,d0-d1/a0
			unlk	a6
   			rts
			

;/*======================================================*/

old_stack:  dc.l 0

           