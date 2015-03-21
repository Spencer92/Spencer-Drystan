# 1 "gE.c" 1
# 1 "C:/c68/include/stdio.h" 1
# 1 "C:/c68/include/compiler.h" 1
# 11 "C:/c68/include/stdio.h" 2
# 20 "C:/c68/include/stdio.h"
typedef unsigned long  size_t;
# 69 "C:/c68/include/stdio.h"
typedef	struct
	{
	long		_cnt;
	unsigned char	*_ptr;
	unsigned char	*_base;
	unsigned int	_flag;
	int		_file;
	long		_bsiz;
	unsigned char	_ch;
	}
	FILE;


typedef unsigned long fpos_t;
# 92 "C:/c68/include/stdio.h"
extern	FILE	_iob[];
# 108 "C:/c68/include/stdio.h"
 char *	ctermid	(char *) ;




 int	remove	(const char *) ;
 int	rename	(const char *, const char *) ;
 char *	tmpnam	(char *) ;
 FILE *	tmpfile	(void) ;

 int	fclose	(FILE *) ;
 int	fflush	(FILE *) ;

 FILE *	fopen	(const char *, const char *) ;
 FILE *	freopen	(const char *, const char *, FILE *) ;

 void	setbuf	(FILE *, char *) ;
 int	setvbuf	(FILE *, char *, int, size_t) ;
# 132 "C:/c68/include/stdio.h"
 int  fscanf  (FILE *, const char *, ...) ;
 int  scanf   (const char *, ...) ;
 int  sscanf  (const char *, const char *, ...) ;


 int	fprintf	(FILE *, const char *, ...) ;
 int	printf	(const char *, ...) ;
 int	sprintf	(char *, const char *, ...) ;

 int 	vfprintf (FILE *, const char *, char * ) ;
 int 	vprintf	 (const char *, char * ) ;
 int 	vsprintf (char *, const char *, char * ) ;

 int	vscanf  (const char *, char * ) ;
 int	vfscanf (FILE *, const char *, char * ) ;
 int	vsscanf	(const char *, const char *, char * ) ;


 int	fgetc	(FILE *) ;
 char	*fgets	(char *, int, FILE *) ;
 char	*gets	(char *) ;
 int	fputc	(int c, FILE *) ;
 int	fputs	(const char *, FILE *) ;
 int	puts	(const char *) ;

 size_t	fread	(void *, size_t, size_t, FILE *) ;
 size_t	fwrite	(const void *, size_t, size_t, FILE *) ;

 int	fgetpos	(FILE *, fpos_t *) ;
 int	fsetpos	(FILE *, fpos_t *) ;

 int	fseek	(FILE *, long, int) ;
 long	ftell	(FILE *) ;
 void	rewind	(FILE *) ;

 void	perror	(const char *) ;


 FILE	*fdopen	(int, const char *) ;


 FILE *	fopenp	(const char *, const char *) ;
 int 	fungetc	(int, FILE *) ;
 int	pclose	(FILE *) ;
 FILE *	popen	(const char *, const char *) ;
 void	setlinebuf	(FILE *) ;

 void	_binmode	(int) ;
 long 	getl	(FILE *) ;
 long 	putl	(long, FILE *) ;
 short 	getw	(FILE *) ;
 short 	putw	(short, FILE *) ;
 void	_getbuf	(FILE *fp) ;
# 192 "C:/c68/include/stdio.h"
 int	_filbuf	(FILE *) ;
# 21 "gE.c" 2
# 1 "C:/c68/include/ctype.h" 1
# 16 "C:/c68/include/ctype.h"
extern	unsigned char	*_ctype;
# 88 "C:/c68/include/ctype.h"
 int	toupper	(int) ;
 int 	tolower	(int) ;
# 22 "gE.c" 2
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
# 23 "gE.c" 2
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
# 24 "gE.c" 2
# 1 "./types.h" 1



typedef unsigned char UINT8;
typedef unsigned int  UINT16;
typedef unsigned long UINT32;
# 28 "gE.c" 2
# 1 "./bitmaps.h" 1
# 1 "./types.h" 1
# 3 "./bitmaps.h" 2

extern 	UINT32 playerTankEast[];
extern 	UINT32 playerTankNorth[];
extern 	UINT32 playerTankSouth[];
extern 	UINT32 playerTankWest[];
extern 	UINT32 playerTankTwoEast[];
extern 	UINT32 playerTankTwoNorth[];
extern 	UINT32 playerTankTwoSouth[];
extern 	UINT32 playerTankTwoWest[];
extern 	UINT32 Rock401[];
extern 	UINT32 explosion[];
extern 	UINT32 lake[];
extern 	UINT32 tree2[];
extern 	UINT8 player_missile[];
extern 	UINT8 enemy_missile[];
# 29 "gE.c" 2
# 1 "./model.h" 1
# 33 "gE.c" 2
# 1 "./rE.h" 1
# 1 "./types.h" 1
# 8 "./rE.h" 2



void plotPixel(char *fbstart, int x, int y);

void plotHorzLine(char *fbstart, int xstart, int ystart, int xfin);

void plotVertLine(char *fbstart, int xstart, int ystart, int yfin);

void plotArbLine(char *fbstart, int xstart, int ystart, int xfin, int yfin);

void plotSprite(char *fbstart, UINT8 *spriteLocation, int xpostoPlot,
		int ypostoPlot, int size);

void copyBackground(char *fbstart, UINT8 *spriteLocation, int xpostoPlot,
		int ypostoPlot, int size);

void printvertical(unsigned char* base, unsigned int x_loc, unsigned int y_loc,
		unsigned int length);

void printArbitrary(unsigned char* base, unsigned int x_loc_start,
		unsigned int y_loc_start, unsigned int x_loc_end,
		unsigned int y_loc_end);

void plotLargeSprite(char *fbstart, UINT32 *spriteLocationint, int xpostoPlot,
		int ypostoPlot,int size);

typedef struct Screen {

	UINT32 *startOfSrcreen;

	UINT32 *displayArea;

} Screen;

void plotString(char *fbstart, char *theString, int size, int xpos,int ypos);



void copyBackground(char *fbstart, UINT32 *spriteLocation, int xpostoPlot,
		int ypostoPlot, int size);
# 34 "gE.c" 2
# 1 "./AsRou.h" 1



void clear(char* screen);
# 35 "gE.c" 2
# 1 "./bitmaps.h" 1
# 36 "gE.c" 2
# 50 "gE.c"
void gameReset();
void pauseAndchill(int duration);
void makeScreen(void* screenChunk1);

int main() {

	UINT8  playerInput = 0;
	char keypress = 0;

	UINT16 playerScore = 0;
	UINT8 i = 0;

	char *mainScreen;
	char *logMainscreen;
	char *gameScreen;
	char *backGamescreen;


	long readfile;
	int  handle;
	Missile missile[10 ];



	Tank demoArray[6];

	for(i = 0; i < 10 ; i++)
	{
		missile[i].is_visible = 0;
		missile[i].x_coordinate = -1;
		missile[i].y_coordinate = -1;
		missile[i].sprite = ((void *)0) ;
	}


	demoArray[0] = Tank
			playerTank = {20, 50, 50 , 5 , 1 , 0 , ((void *)0) , ((void *)0) , 1, 0, 1 , DO_NOTHING,2};
	demoArray[0].sprite = playerSprite;

	demoArray[1] = Tank
			enemyTank = {600, 10, 5 , 5 , 1 , 0 , ((void *)0) ,((void *)0) , -1, 0, 1 , D0_NOTHING,2};
	demoArray[2] = Tank
			enemyTank2 = {250, 30, 5 , 5 , 1 , 0 , ((void *)0) ,((void *)0) , -1, 0, 1 , DO_NOTHING,2};
	demoArray[3] = Tank
			enemyTank3 = {300, 50, 5 , 5 , 1 , 0 , ((void *)0) ,((void *)0) , -1, 0, 1 , DO_NOTHING, 2};
	demoArray[4] = Tank
			enemyTank4 = {400, 70, 5 , 5 , 1 , 0 , ((void *)0) ,((void *)0) , -1, 0, 1 , DO_NOTHING, 2};
	demoArray[5] = Tank
			enemyTank5 = {200, 100, 5 , 5 , 1 , 0 , ((void *)0) ,((void *)0) , -1, 0, 1 , DO_NOTHING, 2};

	demoArray[1].sprite = enemySprite;
	demoArray[2].sprite = enemySprite;
	demoArray[3].sprite = enemySprite;
	demoArray[4].sprite = enemySprite;
	demoArray[5].sprite = enemySprite;


	Stationary_Object landobjects[6] = { };


	mainScreen 		= ((void*)_trap_14_w((short)0x2) );
	logMainscreen 	= ((void*)_trap_14_w((short)0x3) );

	backdropScreen 	= (char*) (long)_trap_1_wl((short)0x48,(long)(0x8100L )) ;
	backdropScreen 	= (char*) ((UINT32) (gameScreen + 256) & 0x00FFFF00);

	gameScreen = (char*) (long)_trap_1_wl((short)0x48,(long)(0x8100L )) ;
	gameScreen = (char*) ((UINT32) (gameScreen + 256) & 0x00FFFF00);

	backGamescreen = (char*) (long)_trap_1_wl((short)0x48,(long)(0x8100L )) ;
	backGamescreen = (char*) ((UINT32) (gameScreen + 256) & 0x00FFFF00);


	clear(gameScreen);
	clear(backGamescreen);
# 131 "gE.c"
	readfile = (short)_trap_1_wlw((short)0x3D,(long)("tankscreen.pi1"),(short)(0)) ;

	handle = (readfile &= 0x0000FFFF);

	 _trap_1_wlww((short)0x42,(long)34,(short)(handle),(short)(0)) ;

	 _trap_1_wwll((short)0x3F,(short)(handle),(long)(FILE_SIZE),(long)(backdropScreen)) ;


	(short)_trap_14_www((short)0x15,(short)(0),(short)(0)) ;



	makeGamescreens(gameScreen,backGamescreen);



	 (void)_trap_14_w((short)0x25) ;

	 (void)_trap_14_wllw((short)0x5,(long)(-1L),(long)backdropScreen,(short)(-1L)) ;




	while (!(short)_trap_1_w((short)0x0B) ) {

		if (i == 0) {
			(short)_trap_1_wl((short)0x09,(long)("\r\n\0")) ;
			(short)_trap_1_wl((short)0x09,(long)("Press space to start or q to quit \r\n\0")) ;
			(short)_trap_1_wl((short)0x09,(long)("\r\n\0")) ;
		}

		if (!(i >= 1)) {
			i++;
		}

	}

	keypress = _trap_1_w((short)0x08) ;

	if (keypress != 'q') {


		for(i = 0; i < 6; i++)
		{
			plotLargeSprite(gameScreen, demoArray[i].sprite, demoArray[i].x_coordinate
			demoArray[i].y_coordinate, 32);
		}


		(void)_trap_14_w((short)0x25) ;
		(void)_trap_14_wllw((short)0x5,(long)(gameScreen),(long)gameScreen,(short)(-1L)) ;



		do {
# 194 "gE.c"
			if(DSconis())
			{
				playerInput = 1;
				if (keypress == 'p') {

				clear(mainScreen);
				(void)_trap_14_w((short)0x25) ;
				(void)_trap_14_wllw((short)0x5,(long)(logMainscreen),(long)mainScreen,(short)(-1L)) ;

				(short)_trap_1_wl((short)0x09,(long)("In pause game loop \r\n\0")) ;
				(short)_trap_1_wl((short)0x09,(long)("Please press any key to start \r\n\0")) ;

				while (!(short)_trap_1_w((short)0x0B) ) {
				}
				keypress = _trap_1_w((short)0x08) ;
				}
			}
			else
			{
				playerInput = 0;
			}
			model(&demoArray[0],demoArray,missile, object,
			num_enemies,num_missiles, num_objects,keypress,playerInput);

			for(i = 0; i < 6; i++)
			{
				plotLargeSprite(gameScreen, demoArray[i].sprite, demoArray[i].x_coordinate
				demoArray[i].y_coordinate, 32);
			}
			(void)_trap_14_w((short)0x25) ;
			(void)_trap_14_wllw((short)0x5,(long)(gameScreen),(long)gameScreen,(short)(-1L)) ;
			clear(backGamescreen);


			(void)_trap_14_w((short)0x25) ;
			(void)_trap_14_wllw((short)0x5,(long)(backGamescreen),(long)backGamescreen,(short)(-1L)) ;
		} while (keypress != 'q');

	}



	(short)_trap_1_wl((short)0x49,(long)(gameScreen)) ;
	(short)_trap_1_wl((short)0x49,(long)(backGamescreen)) ;

	return 0;

}

void pauseAndchill(int duration) {


	}

}

void gameReset(){



}


void makeGameScreens(void* screenChunk1 ,void* screenChunk2)
{
	long readfile;
	long *fastCopyptSrc = screenChunk1;
	long *fastCopyptDst = screenChunk2;
	int  handle;

	readfile = (short)_trap_1_wlw((short)0x3D,(long)("grass.pi1"),(short)(0)) ;

	handle = (readfile &= 0x0000FFFF);

	_trap_1_wlww((short)0x42,(long)34,(short)(handle),(short)(0)) ;

	_trap_1_wwll((short)0x3F,(short)(handle),(long)(FILE_SIZE),(long)(screenChunk1)) ;

	for(int i = 0 ;i < 0x8000 ;i++)
	{

		*(screenChunk2) = *(screenChunk1);

		screenChunk1++;
		screeenChunk2++;


	}



}
