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
TURN		equ	7
DO_NOTHING	equ	8

	xref		_missiles_alive_x
	xref		_missiles_alive_y
	xref		_playAlin
	xref		_needTurn
	xref		_yMove
	xref		_xMove
	xref		_die_check
	xref		_missile_fired
	xref		_yfacing
	xref		_xfacing
	xdef		_tankBehav



;Tank_Behaviour(Tank* enemy, Tank* player, Missile* missile, int num_missiles)
ENEMY_TANK	equ	8
PLAY_TANK	equ	12
MISSILES	equ	16
NUM_MISSILES	equ	20




_tankBehav:	link a6,#0
		movem.l	d3-d5/a3-a5,-(sp)
		movea.l	PLAY_TANK(a6),a3
		tst.b	FIRING(a3)
		beq	check_x_miss
		pea	NUM_MISSILES(a6)
		move.l	MISSILES(a6),-(sp)
		move.l	ENEMY_TANK(a6),-(sp)
		jsr	_missile_fired
		add.l	#12,sp
		movea.l	ENEMY_TANK(a6),a3
		move.w	d0,BEHAVIOUR(a3)
		bra	end

check_x_miss:	move.w	NUM_MISSILES(a6),-(sp)
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
		
check_y_miss:	move.w	NUM_MISSILES(a6),-(sp)
		move.l	MISSILES(a6),-(sp)
		move.l	ENEMY_TANK(a6),-(sp)
		jsr	_missiles_alive_y
		add.l	#10,sp
		tst.b	d0
		beq	play_alin
		movea.l	ENEMY_TANK(a6),a3
		moveq.w	#DODGE_Y,d3
		move.w	d3,BEHAVIOUR(a3)
		bra	end

play_alin:	move.l	PLAY_TANK(a6),-(sp)
		move.l	ENEMY_TANK(a6),-(sp)
		jsr	_playAlin
		addq.l	#8,sp
		tst.b	d0
		beq	need_turn
		movea.l	ENEMY_TANK(a6),a3
		moveq.w	#SHOOT,d3
		move.w	d3,BEHAVIOUR(a3)
		bra	end

need_turn:	move.l	PLAY_TANK(a6),-(sp)
		move.l	ENEMY_TANK(a6),-(sp)
		jsr	_needTurn
		addq.l	#8,sp
		tst.b	d0
		beq	y_move
		movea.l ENEMY_TANK(a6),a3
		moveq.w	#TURN,d3
		move.w	d3,BEHAVIOUR(a3)
		bra	end

y_move:		move.l	PLAY_TANK(a6),-(sp)
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

x_move:		move.l	PLAY_TANK(a6),-(sp)
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

die:		move.w	NUM_MISSILES(a6),-(sp)
		move.l	MISSILES(a6),-(sp)
		move.l	ENEMY_TANK(a6),-(sp)
		jsr	_die_check
		add.l	#10,sp
		tst.b	d0
		beq	nothing
		movea.l	ENEMY_TANK(a6),a3
		moveq.w	#DIE,d3
		move.w	d3,BEHAVIOUR(a3)
		bra	end

nothing:	movea.l	ENEMY_TANK(a6),a3
		moveq.w	#SHOOT,d3
		move.w	d3,BEHAVIOUR(a3)
		moveq.w	#1,d3
		move.w	d3,FIRING(a3)
	
	
end:		movem.l	(sp)+,d3-d5/a3-a5
		unlk	a6
		rts



















