;/*======================================================*/

;/*======================================================*/

			XDEF _clear
			
			XDEF _physBase
			
			XDEF _setScreen
			
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
			
_physBase:
			link a6,#0
			movem.l d1/a0,-(sp)			
			moveq.l #0,d1	
			
			
			jsr super
			
			move.l #$ff8200,a0
			movep.l 1(a0),d1
			
			jsr exSuper
			
		
			lsr.l #8,d1
			clr.b d1
			
			move.l d1,d0
			
			movem.l (sp)+,d1/a0
			unlk a6
			rts
;/*======================================================*/




;/*======================================================*/


_setScreen
				
			link a6,#0
			movem.l d1/a0,-(sp)
			movea.l	SCREEN(a6),a0
					
			
			clr.l 	d1
			
			move.l  a0,d1
			lsl.l #8,d1
			move.l  #$FF8200,a0	
							
			jsr super			
					
			movep.l d1,1(a0)
			
			jsr exSuper
			
			movem.l (sp)+,d1/a0
			unlk a6
			rts
;/*======================================================*/



;/*======================================================*/

super:                     		;go into super user mode
   			
			movem.l d0-d1/a0,-(sp)
			clr.l -(a7)
   			move.w #32,-(a7)  
   			trap #1    
   			addq.l #6,a7  
  			move.l d0,old_stack
   			movem.l  (sp)+,d0-d1/a0
			rts		
			

exSuper:							;leave super mode
			movem.l d0-d1/a0,-(sp)
			move.l old_stack,-(a7)
   			move.w #32,-(a7)
   			trap #1    
   			addq.l #6,a7
			movem.l  (sp)+,d0-d1/a0
   			rts
			

;/*======================================================*/

old_stack:  ds.l 0

           