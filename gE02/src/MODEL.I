# 1 "model.c" 1
# 1 "./model.h" 1
# 1 "./types.h" 1



typedef unsigned char UINT8;
typedef unsigned int  UINT16;
typedef unsigned long UINT32;
# 6 "./model.h" 2
# 1 "./behavior.h" 1
# 1 "./types.h" 1
# 3 "./behavior.h" 2
# 1 "./missile.h" 1




typedef enum MISSILE_BEHAVIOUR
{
	MOVE_UP,
	MOVE_DOWN,
	MOVE_LEFT,
	MOVE_RIGHT,
	EXPLODE

}MISSILE_BEHAVIOUR;
# 4 "./behavior.h" 2
# 1 "./model.h" 1
# 5 "./behavior.h" 2





typedef enum H_DIRECTION
{
	RIGHT = 1,
	LEFT  = -1,
	VERTICAL = 0

}H_DIRECTION;

typedef enum V_DIRECTION
{
	UP = -1,
	HORIZONTAL = 0,
	DOWN = 1

}V_DIRECTION;

typedef enum BEHAVIOUR
{
	SHOOT,
	DODGE_X,
	DODGE_Y,
	MOVE_X,
	MOVE_Y,
	DIE,
	RESPAWN,
	TURN,
	DO_NOTHING

}BEHAVIOUR;




typedef struct Tank
{
	UINT16 x_coordinate;
	UINT16 y_coordinate;
	UINT32 hitpoints;
	UINT8  current_speed;
	UINT8  is_moving;
	UINT8  is_firing;
	UINT32 *sprite;
	UINT32 backMask[32];
	UINT16 x_posMask;
	UINT16 y_posMask;
	UINT8  *Missile;
	H_DIRECTION h_facing;
	V_DIRECTION v_facing;
	UINT8  is_visable;
	BEHAVIOUR current_behaviour;
	UINT8 missile_available;
}Tank;

typedef struct Missile
{
	UINT16 x_coordinate;
	UINT16 y_coordinate;
	UINT8 max_speed;
	UINT8 *sprite;
	UINT8  is_visable;
	MISSILE_BEHAVIOUR current_behaviour;
}Missile;

typedef struct Stationary_Object
{
	UINT16 x_coordinate;
	UINT16 y_coordinate;
	UINT32 *sprite;

}Stationary_Object;



void turn(Tank *tank);
void dodge_x(Tank *tank, Stationary_Object object, int direction);
void dodge_y(Tank *tank, Stationary_Object object, int direction);
void move_y(Tank *tank, Stationary_Object object, int offset);
void move_x(Tank *tank, Stationary_Object object, int offset);
void shoot(Tank *tank, Missile *missile);
void die(Tank *tank);
void respawn(Tank *tank);
UINT8  flip(int position);

BEHAVIOUR missile_fired(Tank *tank, Missile *missile, int num_missiles);
BEHAVIOUR move_check_x(Tank *enemy, Tank *player, int *direction);
BEHAVIOUR move_check_y(Tank *enemy, Tank *player, int *direction);
BEHAVIOUR die_check(Tank *enemy, Missile *missile, int num_missiles);
BEHAVIOUR shoot_check(Tank *enemy, Tank *player, Missile *missile);
BEHAVIOUR turn_check(Tank *enemy, Tank *player);
BEHAVIOUR respawn_check(Tank *enemy);
BEHAVIOUR dodge_x_check(Tank *enemy, Missile *missile);
BEHAVIOUR dodge_y_check(Tank *enemy, Missile *missile);
BEHAVIOUR move_check_player(Tank *enemy, Tank *player, char input);




MISSILE_BEHAVIOUR move_up_check(Missile *missile, Tank* tank);
MISSILE_BEHAVIOUR move_down_check(Missile *missile, Tank* tank);
MISSILE_BEHAVIOUR move_right_check(Missile *missile, Tank* tank);
MISSILE_BEHAVIOUR move_left_check(Missile *missile, Tank* tank);
MISSILE_BEHAVIOUR explode_check(Missile *missile, Tank *tank);
UINT8  missile_exist_check(Tank *tank, Missile *missile, int offset);
void move_up(Missile *missile, int offset);
void move_down(Missile *missile, int offset);
void move_right(Missile *missile, int offset);
void move_left(Missile *missile, int offset);
void offscreen(Missile *missile);
void explode(Missile *missile, Tank *tank);
# 7 "./model.h" 2
# 1 "model.c" 2
# 1 "./behavior.h" 1
# 2 "model.c" 2
# 1 "./missile.h" 1
# 3 "model.c" 2
# 1 "C:/c68/include/stdlib.h" 1
# 1 "C:/c68/include/compiler.h" 1
# 9 "C:/c68/include/stdlib.h" 2
# 18 "C:/c68/include/stdlib.h"
typedef unsigned long  size_t;




typedef char  wchar_t;
# 44 "C:/c68/include/stdlib.h"
typedef struct {
    int		quot;
    int		rem;
} div_t;

typedef struct {
    long	quot;
    long	rem;
} ldiv_t;

 double atof (const char *s) ;
 int atoi (const char *str) ;
 long atol (const char *str) ;
 long int strtol (const char *nptr, char **endptr, int base) ;
 unsigned long int strtoul (const char *nptr, char **endptr, int base) ;
 double strtod (const char *s, char **endptr) ;

 void srand (unsigned int seed) ;
 int rand (void) ;

 void *malloc (size_t n) ;
 void free (void *param) ;
 void *realloc (void *_r, size_t n) ;
 void *calloc (size_t n, size_t sz) ;





 void *alloca (size_t) ;
# 89 "C:/c68/include/stdlib.h"
 void  abort (void) ;


 int atexit (void (*)(void)) ;

 void  exit (int) ;

 char *getenv (const char *tag) ;
 int system (const char *s) ;

 void *bsearch (const void *key, const void *base, size_t num, size_t size, int (*cmp )(const void *, const void *)) ;
 void qsort (void *base, size_t total_elems, size_t size, int (*cmp )(const void *, const void *)) ;

 int abs (int x) ;
 long labs (long x) ;

 div_t div (int num, int denom) ;
 ldiv_t ldiv (long num, long denom) ;

 int mblen (const char *, size_t) ;
 size_t mbstowcs (wchar_t *, const char *, size_t) ;
 int mbtowc (wchar_t *, const char *, size_t) ;
 size_t wcstombs (char *, const wchar_t *, size_t) ;
 int wctomb (char *, wchar_t) ;

 wchar_t *wcscat (wchar_t *, const wchar_t *) ;
 int wcscmp (const wchar_t *, const wchar_t *) ;
 wchar_t *wcscpy (wchar_t *, const wchar_t *) ;
 size_t wcslen (const wchar_t *) ;
 wchar_t *wcsncat (wchar_t *, const wchar_t *, size_t) ;
 int wcsncmp (const wchar_t *, const wchar_t *, size_t) ;
 wchar_t *wcsncpy (wchar_t *, const wchar_t *, size_t) ;
# 4 "model.c" 2
# 1 "C:/c68/include/osbind.h" 1
# 1 "C:/c68/include/ostruct.h" 1
# 22 "C:/c68/include/ostruct.h"
typedef struct {
    long b_free;
    long b_total;
    long b_secsiz;
    long b_clsiz;
} _DISKINFO;


typedef struct {
  short time;
  short date;
} _DOSTIME;


typedef struct
{
        unsigned char maxlen;
        unsigned char actuallen;
        char    buffer[255];
} _CCONLINE;
# 48 "C:/c68/include/ostruct.h"
typedef struct _dta {
    char 	    dta_buf[21];
    char            dta_attribute;
    unsigned short  dta_time;
    unsigned short  dta_date;
    long            dta_size;
    char            dta_name[14];
} _DTA;
# 98 "C:/c68/include/ostruct.h"
typedef struct {
  short recsiz;
  short clsiz;
  short clsizb;
  short rdlen;
  short fsiz;
  short fatrec;
  short datrec;
  short numcl;
  short bflags;
} _BPB;




typedef struct _md {
    struct _md	*md_next;
    long	 md_start;
    long	 md_length;
    long	 md_owner;
} _MD;


typedef struct {
    _MD *mp_free;
    _MD *mp_used;
    _MD *mp_rover;
} _MPB;
# 141 "C:/c68/include/ostruct.h"
typedef struct {
    char    *ibuf;
    short   ibufsiz;
    volatile short   ibufhd;
    volatile short   ibuftl;
    short   ibuflow;
    short   ibufhi;
} _IOREC;


typedef struct {
	char	topmode;
	char	buttons;
	char	xparam;
	char	yparam;
	short	xmax;
	short	ymax;
	short	xstart;
	short	ystart;
} _PARAM;


typedef struct {
    void    (*midivec)	(void) ;
    void    (*vkbderr)	(void) ;
    void    (*vmiderr)	(void) ;
    void    (*statvec)	(void *) ;
    void    (*mousevec)	(void *) ;
    void    (*clockvec)	(void *) ;
    void    (*joyvec)	(void *) ;
    long    (*midisys)	(void) ;
    long    (*ikbdsys)	(void) ;
    char    kbstate;
} _KBDVECS;


typedef struct {
    void *unshift;
    void *shift;
    void *caps;
} _KEYTAB;


typedef struct
{
        void    *pb_scrptr;
        int     pb_offset;
        int     pb_width;
        int     pb_height;
        int     pb_left;
        int     pb_right;
        int     pb_screz;
        int     pb_prrez;
        void    *pb_colptr;
        int     pb_prtype;
        int     pb_prport;
        void    *pb_mask;
} _PBDEF;
# 17 "C:/c68/include/osbind.h" 2
# 33 "C:/c68/include/osbind.h"
 long _trap_1_w		(short) ;
 long _trap_1_ww	(short,short) ;
 long _trap_1_wl	(short,long) ;
 long _trap_1_wlw	(short,long,short) ;
 long _trap_1_wwll	(short,short,long,long) ;
 long _trap_1_wlww	(short,long,short,short) ;
 long _trap_1_www	(short,short,short) ;
 long _trap_1_wll	(short,long,long) ;
 long _trap_1_wwlll	(short,short,long,long,long) ;
 long _trap_1_wwwll	(short,short,short,long,long) ;
 long _trap_13_wl	(short,long) ;
 long _trap_13_w	(short) ;
 long _trap_13_ww	(short,short) ;
 long _trap_13_www	(short,short,short) ;
 long _trap_13_wwlwww	(short,short,long,short,short,short) ;
 long _trap_13_wwl	(short,short,long) ;
 long _trap_14_wwl	(short,short,long) ;
 long _trap_14_wwll	(short,short,long,long) ;
 long _trap_14_ww	(short,short) ;
 long _trap_14_w	(short) ;
 long _trap_14_wllw	(short,long,long,short) ;
 long _trap_14_wl	(short,long) ;
 long _trap_14_www	(short,short,short) ;
 long _trap_14_wllwwwww (short,long,long,short,short,short,short,short) ;
 long _trap_14_wllwwwwlw (short,long,long,short,short,short,short,long,short) ;
 long _trap_14_wllwwwwwlw (short,long,long,short,short,short,short,short,long,short) ;
 long _trap_14_wwwwwww	(short,short,short,short,short,short,short) ;
 long _trap_14_wlll	(short,long,long,long) ;
 long _trap_14_wllww	(short,long,long,short,short) ;
 long _trap_14_wwwwl	(short,short,short,short,long) ;
 long _trap_14_wwwl	(short,short,short,long) ;
 long _trap_14_wlwlw	(short,long,short,long,short) ;
# 103 "C:/c68/include/osbind.h"
 long _trap_1_ 	(short,...) ;
 long _trap_14_ 	(short,...) ;
 long _trap_13_ 	(short,...) ;
# 5 "model.c" 2

UINT8  missiles_alive_y(Missile* missile, Tank *enemy, int num_missiles);
UINT8  missiles_alive_x(Missile* missile, Tank *enemy, int num_missiles);




int main()
{
	Tank player;
	Tank enemy[3];
	Missile missile[10];
	int initial_offset = 100;
	int index;
	int number_of_enemies = 3;

	player.x_coordinate = 250;
	player.y_coordinate = 250;
	player.hitpoints = 100;
	player.current_speed = 0;
	player.is_moving = 0;
	player.is_firing = 0;
	player.sprite = ((void *)0) ;
	player.x_posMask = 0;
	player.y_posMask = 0;
	player.h_facing = VERTICAL;
	player.v_facing = DOWN;
	player.is_visable = 1;
	player.current_behaviour = DO_NOTHING;
	player.is_firing = 0;
	player.missile_available = 2;

	for(index = 0; index < number_of_enemies; index++)
	{
		enemy[index].x_coordinate = initial_offset;
		enemy[index].y_coordinate = 100;
		enemy[index].hitpoints = 100;
		enemy[index].current_speed = 0;
		enemy[index].is_moving = 0;
		enemy[index].is_firing = 0;
		enemy[index].sprite = ((void *)0) ;
		enemy[index].x_posMask = 0;
		enemy[index].y_posMask = 0;
		enemy[index].h_facing = VERTICAL;
		enemy[index].v_facing = DOWN;
		enemy[index].is_visable = 1;
		enemy[index].current_behaviour = DO_NOTHING;
		enemy[index].is_firing = 0;
		initial_offset += 32;
	}

	return 0;
}




void missile_check(Tank *tank, Missile *missile, int num_missiles, int num_tanks)
{
	int index_missile;
	int index_tanks;
	UINT8  finished_firing = 0;
	for(index_tanks = 0; index_tanks < num_tanks; index_tanks++)
	{
		finished_firing = 0;
		for(index_missile = 0; index_missile < num_missiles && !finished_firing; index_missile++)
		{
			if(tank[index_tanks].is_firing && !missile[index_missile].is_visable)
			{
				if(tank[index_tanks].v_facing == UP)
				{
					missile[index_missile].y_coordinate = tank[index_tanks].y_coordinate-16;
					missile[index_missile].x_coordinate = tank[index_tanks].x_coordinate;
					missile[index_missile].current_behaviour = MOVE_UP;
					finished_firing = 1;
				}
				else if(tank[index_tanks].h_facing == LEFT)
				{
					missile[index_missile].x_coordinate = tank[index_tanks].x_coordinate-16;
					missile[index_missile].y_coordinate = tank[index_tanks].y_coordinate;
					missile[index_missile].current_behaviour = MOVE_LEFT;
					finished_firing = 1;
				}
				else if(tank[index_tanks].v_facing = DOWN)
				{
					missile[index_missile].x_coordinate = tank[index_tanks].x_coordinate;
					missile[index_missile].y_coordinate = tank[index_tanks].y_coordinate+16;
					missile[index_missile].current_behaviour = MOVE_DOWN;
					finished_firing = 1;
				}
				else if(tank[index_tanks].h_facing = RIGHT)
				{
					missile[index_missile].x_coordinate = tank[index_tanks].x_coordinate+16;
					missile[index_missile].y_coordinate = tank[index_tanks].y_coordinate;
					missile[index_missile].current_behaviour = MOVE_RIGHT;
					finished_firing = 1;

				}
			}
			else if(!tank[index_tanks].is_firing)
			{
				finished_firing = 1;
			}
		}
	}

}





void assess_situation(Tank enemy[], Tank *player, Stationary_Object *object, Missile* missile, int num_enemies, int num_missiles)
{
	int index;
	UINT8  missile_alive_x;
	UINT8  missile_alive_y;
	BEHAVIOUR missile_fired;
	for(index = 0; index < num_enemies; index++)
	{
		if(player->is_firing)
		{
			enemy[index].current_behaviour = missile_fired(enemy[index], missile, num_missiles);
		}
		else if(missiles_alive_x(enemy[index],
									missile,
									num_missiles))
		{
			enemy[index].current_behaviour = DODGE_X;
		}
		else if(missiles_alive_y(enemy[index],
									missile,
									num_missiles))
		{
			enemy[index].current_behaviour = DODGE_Y;
		}
		else if((enemy[index].x_coordinate >= player->x_coordinate-8
		&&enemy[index].x_coordinate <= player->x_coordinate+8)
		||
		(enemy[index].y_coordinate >= player->y_coordinate-8
		&& enemy[index].y_coordinate <= player->y_coordinate+8))
		{
			enemy[index].current_behaviour = SHOOT;
		}
		else if(((enemy[index].x_coordinate >= player->x_coordinate-16
		&& enemy[index].x_coordinate <= player->x_coordinate+16)
		&& enemy[index].v_facing == HORIZONTAL) ||
		((enemy[index].y_coordinate >= player->y_coordinate-16
		&&enemy[index].y_coordinate <= player->y_coordinate+16) && enemy[index].h_facing == VERTICAL))
		{
			enemy[index].current_behaviour = TURN;
		}
		else if(((enemy[index].y_coordinate - player->y_coordinate) < ((enemy[index].x_coordinate - player->x_coordinate) + 16)
		&& (enemy[index].y_coordinate - player->y_coordinate > 16))
		||
		((enemy[index].y_coordinate - player->y_coordinate) > ((enemy[index].x_coordinate - player->x_coordinate)+16)
		&& (enemy[index].y_coordinate - player->y_coordinate < -16)))
		{
			enemy[index].current_behaviour = MOVE_Y;
		}
		else if(((enemy[index].x_coordinate - player->x_coordinate) < ((enemy[index].y_coordinate - player->y_coordinate)-16)
		&& (enemy[index].x_coordinate - player->x_coordinate > 16))
		||
		((enemy[index].x_coordinate - player->x_coordinate) > ((enemy[index].y_coordinate - player->y_coordinate)+16)
		&& (enemy[index].x_coordinate - player->x_coordinate < -16)))
		{
			enemy[index].current_behaviour = MOVE_X;
		}
		else if(die_check(enemy[index], missile, num_missiles))
		{
			enemy[index].current_behaviour = DIE;
		}
	}
}



UINT8  missiles_alive_x(Missile* missile, Tank *enemy, int num_missiles)
{
	int index;
	for(index = 0; index < num_missiles && enemy->current_behaviour != DODGE_X; index++)
	{
		enemy->current_behaviour = dodge_x_check(enemy, missile[index]);
	}
	if(enemy->current_behaviour == DODGE_X)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

UINT8  missiles_alive_y(Missile* missile, Tank *enemy, int num_missiles)
{
	int index;
	for(index = 0; index < num_missiles && enemy->current_behaviour != DODGE_Y; index++)
	{
		enemy->current_behaviour = dodge_y_check(enemy, missile[index]);
	}
	if(enemy->current_behaviour == DODGE_Y)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
