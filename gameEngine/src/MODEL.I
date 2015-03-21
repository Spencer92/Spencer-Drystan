# 1 "model.c" 1
# 1 "./model.h" 1
# 8 "./model.h"
typedef unsigned int UINT16;
typedef unsigned char UINT8;
typedef unsigned long UINT32;
# 1 "model.c" 2
# 1 "./behavior.h" 1
# 1 "C:/c68/include/types.h" 1
# 1 "C:/c68/include/compiler.h" 1
# 5 "C:/c68/include/types.h" 2
# 14 "C:/c68/include/types.h"
typedef unsigned long  size_t;




typedef long  time_t;


typedef unsigned short	dev_t;
typedef unsigned short 		gid_t;
typedef unsigned long	ino_t;
typedef unsigned short	mode_t;
typedef short		nlink_t;
typedef long		off_t;
typedef int 		pid_t;
typedef unsigned short 		uid_t;


typedef unsigned char	u_char;
typedef unsigned short	u_short;
typedef unsigned int 	u_int;
typedef unsigned long	u_long;
typedef void *		caddr_t;
# 43 "C:/c68/include/types.h"
typedef unsigned long  fd_set;
# 52 "C:/c68/include/types.h"
 int truncate	(const char *_filename, off_t length) ;
 int ftruncate	(int fd, off_t length) ;
# 1 "C:/c68/include/utime.h" 1
# 8 "C:/c68/include/utime.h"
struct utimbuf {
	time_t	actime;
	time_t	modtime;
};

 int utime (const char *path, const struct utimbuf *times) ;
# 55 "C:/c68/include/types.h" 2
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




typedef char* String;

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
	String x_find;
	UINT16 x_coordinate;
	String y_find;
	UINT16 y_coordinate;
	String end_coords;
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
	UINT8  is_visible;
	BEHAVIOUR current_behaviour;
	UINT8 missile_available;
}Tank;

typedef struct Missile
{
	UINT16 x_coordinate;
	UINT16 y_coordinate;
	UINT8 max_speed;
	UINT8 *sprite;
	UINT8  is_visible;
	MISSILE_BEHAVIOUR current_behaviour;
	H_DIRECTION horizontal_movement;
	V_DIRECTION vertical_movement;
}Missile;

typedef struct Stationary_Object
{
	UINT16 x_coordinate;
	UINT16 y_coordinate;
	UINT32 *sprite;

}Stationary_Object;



void turn(Tank *tank);
void dodge_y(Tank *tank, Stationary_Object *object, int *direction, int num_objects);
void dodge_x(Tank *tank, Stationary_Object *object, int *direction, int num_objects);
void move_y(Tank *tank, Stationary_Object *object, int offset, int num_objects);
void move_x(Tank *tank, Stationary_Object *object, int offset, int num_objects);
void shoot(Tank *tank, Missile *missile);
void die(Tank *tank);
void respawn(Tank *tank);
UINT8  flip(int position);
UINT8  die_check(Tank *enemy, Missile *missile, int num_missiles);


BEHAVIOUR foo(Tank * enemy, Missile * missile, int num_missles);
BEHAVIOUR missile_fired(Tank *tank, Missile *missile, int* num_missiles);
BEHAVIOUR move_check_x(Tank *enemy, Tank *player, int *direction);
BEHAVIOUR move_check_y(Tank *enemy, Tank *player, int *direction);
BEHAVIOUR shoot_check(Tank *enemy, Tank *player, Missile *missile);
BEHAVIOUR turn_check(Tank *enemy, Tank *player);
BEHAVIOUR respawn_check(Tank *enemy);
BEHAVIOUR dodge_x_check(Tank *enemy, Missile *missile);
BEHAVIOUR dodge_y_check(Tank *enemy, Missile *missile);
BEHAVIOUR move_check_player(Tank *enemy, Tank *player, char input);




MISSILE_BEHAVIOUR move_up_check(Missile *missile);
MISSILE_BEHAVIOUR move_down_check(Missile *missile);
MISSILE_BEHAVIOUR move_right_check(Missile *missile);
MISSILE_BEHAVIOUR move_left_check(Missile *missile);
MISSILE_BEHAVIOUR explode_check(Missile *missile, Tank *tank);
UINT8  missile_exist_check(Tank *tank, Missile *missile, int offset);
void move_up(Missile *missile, int offset);
void move_down(Missile *missile, int offset);
void move_right(Missile *missile, int offset);
void move_left(Missile *missile, int offset);
void offscreen(Missile *missile);
void explode(Missile *missile, Tank *tank);




UINT8  missiles_alive_y(Tank *enemy, Missile* missile, int num_missiles);
UINT8  missiles_alive_x(Tank *enemy, Missile* missile, int num_missiles);
void player_action_check(Tank *player, Tank *enemy, int num_enemies, char input, Missile* missile, int num_missiles);
void player_action(Tank* player, Missile* missile, char input);
UINT8  tanks_at(Tank* player, Tank* enemy, int num_tanks);
UINT8  DSconis();
char DSnecin();
void DSconws(String output);
void missile_check(Tank *tank, Missile *missile, int num_missiles, int num_tanks);
void DSconout(char output);
long getTime();
int thing();
void assess_situation(Tank enemy[], Tank *player, Stationary_Object *object, Missile* missile, int num_enemies, int num_missiles);
void tank_respond(Tank *enemy, Missile *missile, int num_missiles, int num_tanks, Stationary_Object *object, int num_objects);
# 2 "model.c" 2
# 1 "./missile.h" 1
# 3 "model.c" 2
# 1 "C:/c68/include/stdlib.h" 1
# 23 "C:/c68/include/stdlib.h"
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
# 1 "./system.h" 1




long getTime();
# 6 "model.c" 2
# 1 "./keyboard.h" 1


UINT8  DSconis();
char DSnecin();
void DSconws(String output);
void DSconout(char output);
# 7 "model.c" 2
# 141 "model.c"
void model(Tank* player, Tank* enemy, Missile *missile, Stationary_Object *object,
			int num_enemies, int num_missiles, int num_objects, char input, UINT8  input_valid)
{
	static int time_now;
	time_now = getTime();
	if(input_valid)
	{

		player_action_check(player,
		enemy,
		num_enemies,
		input,
		missile,
		num_missiles);
		if(getTime() >= time_now+10)
		{
			player_action(player,missile,input);
			time_now = getTime();
		}
	}
	assess_situation(enemy, player, object, missile, num_enemies, num_missiles);
	if(getTime() >= time_now+10)
	{
		tank_respond(enemy, missile, num_missiles, num_enemies, object, num_objects);
		time_now = getTime();
	}

}
# 175 "model.c"
int thing()
{
	register int whatever = 3;
	return whatever;
}
# 211 "model.c"
void player_action_check(Tank *player, Tank *enemy, int num_enemies, char input, Missile* missile, int num_missiles)
{
	if((input == 'd' || input == 'a') && !tanks_at(player, enemy, num_enemies))
	{
		player->current_behaviour = MOVE_X;
	}
	else if((input == 'w' || input == 's') && !tanks_at(player,enemy, num_enemies))
	{
		player->current_behaviour = MOVE_Y;
	}
	else if(input == ' ')
	{
		player->current_behaviour = SHOOT;
		player->is_firing = 1;
	}
	else if(die_check(player, missile, num_missiles))
	{
		player->current_behaviour = DIE;
	}
	else
	{
		player->current_behaviour == DO_NOTHING;
	}
}
# 261 "model.c"
void player_action(Tank* player, Missile* missile, char input)
{
	if(player->current_behaviour == MOVE_X && input == 'd')
	{
		player->x_coordinate++;
	}
	else if(player->current_behaviour == MOVE_X && input == 'a')
	{
		player->x_coordinate--;
	}
	else if(player->current_behaviour == MOVE_Y && input == 'w')
	{
		player->y_coordinate--;
	}
	else if(player->current_behaviour == MOVE_Y && input == 'd')
	{
		player->y_coordinate++;
	}
	else if(player->current_behaviour == SHOOT)
	{
		missile_check(player, missile, player->missile_available, 1);
		player->is_firing = 0;
	}
}
# 303 "model.c"
UINT8  tanks_at(Tank* player, Tank* enemy, int num_tanks)
{
	int index;
	UINT8  something_there = 0;
	for(index = 0; index < num_tanks && !something_there; index++)
	{
		if(!((player->x_coordinate + 16 < enemy[index].x_coordinate - 16 ||
			player->x_coordinate - 16 > enemy[index].x_coordinate + 16) &&
			(player->y_coordinate - 16 < enemy[index].y_coordinate + 16 ||
			player->y_coordinate + 16 > enemy[index].y_coordinate - 16)))
			{
				something_there = 1;
			}
	}
	return something_there;
}
# 354 "model.c"
void tank_respond(Tank *enemy, Missile *missile, int num_missiles, int num_tanks, Stationary_Object *object, int num_objects)
{
	int index;
	for(index = 0; index < num_tanks; index++)
	{
		if(enemy[index].is_visible && !enemy[index].current_behaviour == DO_NOTHING)
		{
			if(enemy[index].current_behaviour == SHOOT)
			{
				missile_check(&enemy[index], missile, enemy[index].missile_available, 1);
				enemy[index].is_firing = 0;
				DSconws("shooting\r\n\0");
			}
			else if(enemy[index].current_behaviour == DODGE_X)
			{
				dodge_x(&enemy[index], object, &(enemy[index].h_facing), num_objects);
				DSconws("Dodging x\r\n\0");
			}
			else if(enemy[index].current_behaviour == DODGE_Y)
			{
				dodge_y(&enemy[index], object,
										&(enemy[index].v_facing), num_objects);
				DSconws("Dodging y\r\n\0");
			}
			else if(enemy[index].current_behaviour == MOVE_X)
			{
				move_x(&enemy[index], object,
										&enemy[index].h_facing, num_objects);
				DSconws("Moving x\r\n\0");
			}
			else if(enemy[index].current_behaviour == MOVE_Y)
			{
				move_y(&enemy[index], object, &enemy[index].v_facing, num_objects);
				DSconws("Moving y\r\n\0");
			}
			else if(enemy[index].current_behaviour == DIE)
			{
				enemy[index].is_visible == 0;
				DSconws("Dying\r\n\0");
			}
			else if(enemy[index].current_behaviour == TURN)
			{
				turn(&enemy[index]);
				DSconws("Turning\r\n\0");
			}
		}

	}
}
# 434 "model.c"
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
			if(tank[index_tanks].is_firing && !missile[index_missile].is_visible)
			{
				if(tank[index_tanks].v_facing == UP)
				{
					missile[index_missile].y_coordinate = tank[index_tanks].y_coordinate-16;
					missile[index_missile].x_coordinate = tank[index_tanks].x_coordinate;
					missile[index_missile].current_behaviour = MOVE_UP;
					missile[index_missile].is_visible = 1;
					finished_firing = 1;
				}
				else if(tank[index_tanks].h_facing == LEFT)
				{
					missile[index_missile].x_coordinate = tank[index_tanks].x_coordinate-16;
					missile[index_missile].y_coordinate = tank[index_tanks].y_coordinate;
					missile[index_missile].current_behaviour = MOVE_LEFT;
					missile[index_missile].is_visible = 1;
					finished_firing = 1;
				}
				else if(tank[index_tanks].v_facing = DOWN)
				{
					missile[index_missile].x_coordinate = tank[index_tanks].x_coordinate;
					missile[index_missile].y_coordinate = tank[index_tanks].y_coordinate+16;
					missile[index_missile].current_behaviour = MOVE_DOWN;
					missile[index_missile].is_visible = 1;
					finished_firing = 1;
				}
				else if(tank[index_tanks].h_facing = RIGHT)
				{
					missile[index_missile].x_coordinate = tank[index_tanks].x_coordinate+16;
					missile[index_missile].y_coordinate = tank[index_tanks].y_coordinate;
					missile[index_missile].current_behaviour = MOVE_RIGHT;
					missile[index_missile].is_visible = 1;
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
# 533 "model.c"
void assess_situation(Tank enemy[], Tank *player, Stationary_Object *object, Missile* missile, int num_enemies, int num_missiles)
{
	int index;
	DSconws("Im in assess_situation \r\n\0");
	for(index = 0; index < num_enemies; index++)
	{
		if(player->is_firing)
		{
			enemy[index].current_behaviour =
			missile_fired(&enemy[index],
			missile,
			&num_missiles);
			DSconws("Player is fireing\r\n\0");
		}
		else if(missiles_alive_x(&enemy[index],
									missile,
									num_missiles))
		{
			enemy[index].current_behaviour = DODGE_X;
			DSconws("Dodge x\r\n\0");
		}
		else if(missiles_alive_y(&enemy[index],
									missile,
									num_missiles))
		{
			enemy[index].current_behaviour = DODGE_Y;
			DSconws("Dodge y\r\n\0");
		}
		else if((enemy[index].x_coordinate >= player->x_coordinate-8
		&&enemy[index].x_coordinate <= player->x_coordinate+8)
		||
		(enemy[index].y_coordinate >= player->y_coordinate-8
		&& enemy[index].y_coordinate <= player->y_coordinate+8))
		{
			enemy[index].current_behaviour = SHOOT;
			DSconws("Shoot \r\n\0");
		}
		else if(((enemy[index].x_coordinate >= player->x_coordinate-16
		&& enemy[index].x_coordinate <= player->x_coordinate+16)
		&& enemy[index].v_facing == HORIZONTAL) ||
		((enemy[index].y_coordinate >= player->y_coordinate-16
		&&enemy[index].y_coordinate <= player->y_coordinate+16) && enemy[index].h_facing == VERTICAL))
		{
			enemy[index].current_behaviour = TURN;
			DSconws("Turn \r\n\0");
		}
		else if(((enemy[index].y_coordinate - player->y_coordinate) < ((enemy[index].x_coordinate - player->x_coordinate) + 16)
		&& (enemy[index].y_coordinate - player->y_coordinate > 16))
		||
		((enemy[index].y_coordinate - player->y_coordinate) > ((enemy[index].x_coordinate - player->x_coordinate)+16)
		&& (enemy[index].y_coordinate - player->y_coordinate < -16)))
		{
			enemy[index].current_behaviour = MOVE_Y;
			DSconws("Move y\r\n\0");
		}
		else if(((enemy[index].x_coordinate - player->x_coordinate) < ((enemy[index].y_coordinate - player->y_coordinate)-16)
		&& (enemy[index].x_coordinate - player->x_coordinate > 16))
		||
		((enemy[index].x_coordinate - player->x_coordinate) > ((enemy[index].y_coordinate - player->y_coordinate)+16)
		&& (enemy[index].x_coordinate - player->x_coordinate < -16)))
		{
			enemy[index].current_behaviour = MOVE_X;
			DSconws("move x\r\n\0");
		}
		else if(die_check(&enemy[index], missile, num_missiles))
		{
			enemy[index].current_behaviour = DIE;
			DSconws("Die \r\n\0");
		}
		else
		{
			enemy[index].current_behaviour = DO_NOTHING;
			DSconws("Nuttun\r\n\0");
		}
	}
}
# 633 "model.c"
UINT8  missiles_alive_x(Tank *enemy, Missile* missile, int num_missiles)
{
	int index;
	for(index = 0; index < num_missiles && enemy->current_behaviour != DODGE_X; index++)
	{
		enemy->current_behaviour = dodge_x_check(enemy, &missile[index]);
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
# 671 "model.c"
UINT8  missiles_alive_y( Tank *enemy, Missile* missile,int num_missiles)
{
	int index;
	for(index = 0; index < num_missiles && enemy->current_behaviour != DODGE_Y; index++)
	{
		enemy->current_behaviour = dodge_y_check(enemy, &missile[index]);
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
