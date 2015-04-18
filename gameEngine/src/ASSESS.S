TANK		equ	294
X_COORD		equ	0
Y_COORD		equ	2
X_PREV		equ	4
Y_PREV		equ	6
HITPOINT	equ	8
SPEED		equ	12
MOVING		equ	13
FIRING		equ	14                          	
X_POSMASK	equ	16
Y_POSMASK	equ	18             	
H_FACING	equ	20
V_FACING	equ	22
IS_VISIBLE	equ	24
BEHAVIOUR	equ	26
AVAILABLE	equ	28
SPRITE		equ	30
MISSILE		equ	34
BACKMASK	equ	38

;BEHAVIOURS
SHOOT		equ	0
DODGE_X		equ	1
DODGE_Y		equ	2
MOVE_X		equ	3
MOVE_Y		equ	4
DIE		equ	5
RESPAWN		equ	6
TURN_RIGHT		equ	7
TURN_UP		equ	8
TURN_DOWN	equ	9
TURN_LEFT	equ	10
DO_NOTHING	equ	11

	xref		_missiles_alive_x
	xref		_missiles_alive_y
	xref		_playAlinHorizontal
	xref		_playAlinVertical
	xref		_yMove
	xref		_xMove
	xref		_die_check
	xref		_missile_fired
	xref		_yfacing
	xref		_xfacing
	xref		_needTurnRight
	xref		_needTurnLeft
	xref		_needTurnDown
	xref		_needTurnUp
	xref		_getTime
	xdef		_tankBehav
	


;
; Method: Tank_Behaviour
; Purpose: To find out what is happening on the battlefield and respond accordingly
;
;
; Input arguments
; 		enemy		- The enemy that is looking at the situation
;		player		- What the tank wants to interact with
;		missile		- The missiles that the tank will try to dodge
;		num_missiles - The amount missiles
;	
;	
;	
;					Case 1	   : The player is firing and thus the tanks will have
;								 to figure out based on it's surroundings what to do
;					
;					Case 2 & 3 : There's a missile somewhere already and the tanks have to 
;								 figure out if it is a threat to them, and react accordingly
;							
;					Case 4 & 5 : If the tank is lined up with the player, then the tank
;								 will take a shot at the player if it has a chance to
;
;					Case 6 - 9 : If the tank isn't alligned with the player or needs to move toward the
;								 player but isn't facing the player then the tank will turn.
;					
;					Case 10 & 11: Depending on what is closer, the tank will move either in
;								 the x direction or y direction
;								
;					Case 12	   : If a missile and a tank is at the same location, then the 
;								 tank will be instructed to no longer be visible
;								
;					Case 13	   : The tank will fire if all else fails
;	
	
	
;Tank_Behaviour(Tank* enemy, Tank* player, Missile* missile, int num_missiles)
ENEMY_TANK	equ	8
PLAY_TANK	equ	12
MISSILES	equ	16
NUM_MISSILES	equ	20
;LOCAL
NEW_HEALTH	equ	-2



_tankBehav:	link a6,#0				; Case 1
		movem.l	d3-d5/a3-a5,-(sp)
		movea.l	PLAY_TANK(a6),a3
		tst.b	FIRING(a3)
		beq	check_x_miss
		pea	NUM_MISSILES(a6)
		move.l	MISSILES(a6),-(sp)
		move.l	ENEMY_TANK(a6),-(sp)
		jsr	_missile_fired
		add.l	#12,sp
		tst.b		d0
		beq		check_x_miss
		movea.l	ENEMY_TANK(a6),a3
		move.w	d0,BEHAVIOUR(a3)
		bra	end

check_x_miss:	move.w	NUM_MISSILES(a6),-(sp) ; Case 2
		move.l	MISSILES(a6),-(sp)
		move.l	ENEMY_TANK(a6),-(sp)
		jsr	_missiles_alive_x
		add.l	#10,sp
		tst.b	d0
		beq	check_y_miss
		movea.l ENEMY_TANK(a6),a3
		moveq.w	#DODGE_X,d3
		move.w	d3,BEHAVIOUR(a3)
		bra	end
		
check_y_miss:	move.w	NUM_MISSILES(a6),-(sp) ;Case 3
		move.l	MISSILES(a6),-(sp)
		move.l	ENEMY_TANK(a6),-(sp)
		jsr	_missiles_alive_y
		add.l	#10,sp
		tst.b	d0
		beq	play_alin_horizontal
		movea.l	ENEMY_TANK(a6),a3
		moveq.w	#DODGE_Y,d3
		move.w	d3,BEHAVIOUR(a3)
		bra	end

play_alin_horizontal:
		move.l	PLAY_TANK(a6),-(sp) ;Case 4
		move.l	ENEMY_TANK(a6),-(sp)
		jsr	_playAlinHorizontal
		addq.l	#8,sp
		tst.b	d0
		beq	play_alin_vertical
		movea.l	ENEMY_TANK(a6),a3
		moveq.w	#SHOOT,d3
		move.w	d3,BEHAVIOUR(a3)
		bra	end
		
play_alin_vertical:					;Case 5
		move.l	PLAY_TANK(a6),-(sp)
		move.l	ENEMY_TANK(a6),-(sp)
		jsr	_playAlinVertical
		addq.l	#8,sp
		tst.b	d0
		beq	need_turn_right
		movea.l	ENEMY_TANK(a6),a3
		moveq.w	#SHOOT,d3
		move.w	d3,BEHAVIOUR(a3)
		bra	end

need_turn_right:					;Case 6
		move.l	PLAY_TANK(a6),-(sp)
		move.l	ENEMY_TANK(a6),-(sp)
		jsr	_needTurnRight
		addq.l	#8,sp
		tst.b	d0
		beq	need_turn_left
		movea.l ENEMY_TANK(a6),a3
		moveq.w	#TURN_RIGHT,d3
		move.w	d3,BEHAVIOUR(a3)
		bra	end
		
need_turn_left:						;Case 7
		move.l	PLAY_TANK(a6),-(sp)
		move.l	ENEMY_TANK(a6),-(sp)
		jsr	_needTurnLeft
		addq.l	#8,sp
		tst.b	d0
		beq	need_turn_up
		movea.l ENEMY_TANK(a6),a3
		moveq.w	#TURN_LEFT,d3
		move.w	d3,BEHAVIOUR(a3)
		bra	end		

need_turn_up:						;Case 8
		move.l	PLAY_TANK(a6),-(sp)
		move.l	ENEMY_TANK(a6),-(sp)
		jsr	_needTurnUp
		addq.l	#8,sp
		tst.b	d0
		beq	y_move
		movea.l ENEMY_TANK(a6),a3
		moveq.w	#TURN_UP,d3
		move.w	d3,BEHAVIOUR(a3)
		bra	end

need_turn_down:						;Case 9
		move.l	PLAY_TANK(a6),-(sp)
		move.l	ENEMY_TANK(a6),-(sp)
		jsr	_needTurnDown
		addq.l	#8,sp
		tst.b	d0
		beq	y_move
		movea.l ENEMY_TANK(a6),a3
		moveq.w	#TURN_DOWN,d3
		move.w	d3,BEHAVIOUR(a3)
		bra	end		

		
y_move:		move.l	PLAY_TANK(a6),-(sp) ;Case 10
		move.l	ENEMY_TANK(a6),-(sp)
		jsr	_yMove
		addq.l	#8,sp
		tst.b	d0
		beq	x_move
		movea.l	ENEMY_TANK(a6),a3
		moveq.w	#MOVE_Y,d3
		move.w	d3,BEHAVIOUR(a3)
		move.l	PLAY_TANK(a6),-(sp)
		move.l	ENEMY_TANK(a6),-(sp)
		jsr	_yfacing
		addq.l	#8,sp
		bra	end

x_move:		move.l	PLAY_TANK(a6),-(sp) ;Case 11
		move.l	ENEMY_TANK(a6),-(sp)
		jsr	_xMove
		addq.l	#8,sp
		tst.b	d0
		beq	die
		movea.l	ENEMY_TANK(a6),a3
		moveq.w	#MOVE_X,d3
		move.w	d3,BEHAVIOUR(a3)
		move.l	PLAY_TANK(a6),-(sp)
		move.l	ENEMY_TANK(a6),-(sp)
		jsr	_xfacing
		addq.l	#8,sp
		bra	end

die:		move.w	NUM_MISSILES(a6),-(sp) ;Case 12
		move.l	MISSILES(a6),-(sp)
		move.l	ENEMY_TANK(a6),-(sp)
		jsr	_die_check
		add.l	#10,sp
		tst.b	d0
		beq	nothing
		jsr	_getTime
		lsr.l #8,d0
		movea.l	ENEMY_TANK(a6),a3
		sub.l	d0,HITPOINT(a3)
		tst.l	HITPOINT(a3)
		bgt	end
		moveq.w	#DIE,d3
		move.w	d3,BEHAVIOUR(a3)
		bra	end

nothing:	movea.l	ENEMY_TANK(a6),a3 ;Case 13
		moveq.w	#SHOOT,d3
		move.w	d3,BEHAVIOUR(a3)
		moveq.w	#1,d3
		move.w	d3,FIRING(a3)
	
	
end:		movem.l	(sp)+,d3-d5/a3-a5
		unlk	a6
		rts



















