#include "types.h"
#include "osbind.h"
#include "system.h"
#include "sound.h"
#include "soundgen.h"
#define MUSIC_LIMIT 37



void write_psg(int reg, UINT8 val);
void set_tone(int channel, int tuning);
void set_volume(int channel, int volume);
void stop_sound();
void enable_channel(int channel, int tone_on, int noise_on);	
volatile char *PSG_reg_select = 0xFF8800;
volatile char *PSG_reg_write  = 0xFF8802;

void write_psg_2(int reg, UINT8 val);




void start_music()
{
	long i = getTime();
	psg_write(7,0x3E);
	psg_write(8,10);

}


void write_psg(volatile int reg,volatile UINT8 val)
{
	long oldssp;	
/*	volatile char *PSG_reg_select = 0xFF8800;
	volatile char *PSG_reg_write  = 0xFF8802;*/
	oldssp = Super(0);
	
	*PSG_reg_select = reg;		/* set channel A fine tune = 248 */
	*PSG_reg_write  = (volatile char) val;

	
	Super(oldssp);
}

/*
void write_psg_2(int reg, UINT8 val)
{
	long oldssp;
	int select_check;
	char write_check;
/*	volatile char *PSG_reg_select = 0xFF8800;
	volatile char *PSG_reg_write  = 0xFF8802;*/
/*	oldssp = Super(0);
	
	select_check = 0;
	write_check = 250;
	
	*PSG_reg_select = select_check;		/* set channel A fine tune = 248 */
/*	*PSG_reg_write  = write_check;

	select_check = 1;
	write_check = 0;
	*PSG_reg_select = select_check;		/* set channel A coarse tune = 0 */
/*	*PSG_reg_write  = write_check;

	select_check = 7;
	write_check = 0x3E;
	
	*PSG_reg_select = select_check;		/* enable channel A on mixer */
/*	*PSG_reg_write  = write_check;

	select_check = 8;
	write_check = 11;
	*PSG_reg_select = select_check;		/* set channel A volume = 11 */
/*	*PSG_reg_write  = write_check;
/* 	*psg_select = (volatile char) reg;
	*psg_write = val;
*/ 	
/*	
	Super(oldssp);
}
*/


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
	psg_write(0,A_VOLUME);
	psg_write(0,B_VOLUME);
	psg_write(0,C_VOLUME);

}


void enable_channel(int channel, int tone_on, int noise_on)
{
	psg_write(channel,tone_on);
	psg_write(channel+1,noise_on);
}


void music()
{
	static UINT8 i;
	char music[MUSIC_LIMIT] = {G_FLAT,A_FLAT,A,B,B_FLAT,B,B_FLAT,B,B,B_FLAT,B_FLAT,A,B,A,A_FLAT,A,A,A_FLAT,A_FLAT,A,A,A,A_FLAT,F,E,F,G_FLAT,F,G_FLAT,F,A_FLAT,A,B,A,A_FLAT,A};
	if(i > MUSIC_LIMIT-1)
	i = 0;
	psg_write(0,music[i]);
	i++;
}
















