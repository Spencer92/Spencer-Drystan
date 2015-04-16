# 1 "soundgen.c" 1
# 1 "./types.h" 1
# 7 "./types.h"
typedef char* String;

typedef unsigned char UINT8;
typedef unsigned int  UINT16;
typedef unsigned long UINT32;
# 1 "soundgen.c" 2
# 1 "C:/c68/include/osbind.h" 1
# 1 "C:/c68/include/compiler.h" 1
# 9 "C:/c68/include/osbind.h" 2
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
# 2 "soundgen.c" 2
# 1 "./system.h" 1




long getTime();
# 3 "soundgen.c" 2
# 1 "./sound.h" 1
# 1 "./types.h" 1
# 3 "./sound.h" 2
# 27 "./sound.h"
extern void psg_write(int reg,UINT8 val);
# 4 "soundgen.c" 2





void write_psg(int reg, UINT8 val);
void set_tone(int channel, int tuning);
void set_volume(int channel, int volume);
void stop_sound();
void enable_channel(int channel, int tone_on, int noise_on);
volatile char *PSG_reg_select = 0xFF8800;
volatile char *PSG_reg_write  = 0xFF8802;

void write_psg_2(int reg, UINT8 val);
void start_music();



int main()
{




	long i = getTime();

	psg_write(0,500);
	psg_write(7,0x3E);
	psg_write(8,10);

	while(!(short)_trap_1_w((short)0x0B) )
	{
		if(getTime() >= i+8)
		{
			start_music();
			i = getTime();
		}
	}
# 97 "soundgen.c"
	while(!(short)_trap_1_w((short)0x0B) )
		;
# 107 "soundgen.c"
	psg_write(8,0);
	return 0;
}


void write_psg(volatile int reg,volatile UINT8 val)
{
	long oldssp;


	oldssp = _trap_1_wl((short)0x20,(long)(0)) ;

	*PSG_reg_select = reg;
	*PSG_reg_write  = (volatile char) val;


	_trap_1_wl((short)0x20,(long)(oldssp)) ;
}
# 166 "soundgen.c"
UINT8 read_psg(int reg)
{

}

void set_tone(int channel, int tuning)
{

	psg_write(tuning,channel);

}


void set_volume(int channel, int volume)
{

	psg_write(channel,volume);
}


void stop_sound()
{
	psg_write(0,0x8 );
	psg_write(0,0x9 );
	psg_write(0,0xFB );

}


void enable_channel(int channel, int tone_on, int noise_on)
{
	psg_write(channel,tone_on);
	psg_write(channel+1,noise_on);
}


void start_music()
{
	static UINT8 i;
	char music[37 ] = {319 ,284 ,268 ,478 ,253 ,478 ,253 ,478 ,478 ,253 ,253 ,268 ,478 ,268 ,284 ,268 ,268 ,284 ,284 ,268 ,268 ,268 ,284 ,338 ,358 ,338 ,319 ,338 ,319 ,338 ,284 ,268 ,478 ,268 ,284 ,268 };
	if(i > 37 -1)
	i = 0;

	psg_write(0,music[i]);
	i++;
}
