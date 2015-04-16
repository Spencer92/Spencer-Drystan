#include "types.h"
#include "osbind.h"
#include "system.h"

#define A_TONE 0
#define B_TONE 1
#define C_TONE 2
#define A_CHANNEL 0x3F
#define B_CHANNEL 0x7D
#define C_CHANNEL 0xFB
#define A_VOLUME 0x8
#define B_VOLUME 0x9
#define C_VOLUME 0xA
void write_psg(int reg, UINT8 val);
void set_tone(int channel, int tuning);
void set_volume(int channel, int volume);
void stop_sound();
void enable_channel(int channel, int tone_on, int noise_on);

int main()
{


	enable_channel(0,248,0);
	write_psg(7,A_CHANNEL);
	set_volume(11,A_VOLUME);
	while(!Cconis())
		;
		
	stop_sound();
	
	return 0;
}


void write_psg(int reg, UINT8 val)
{
	volatile char* psg_select = 0xFF8800;
	volatile char* psg_write = 0xFF8802;
	long oldssp;
	
	oldssp = Super(0);
	
	
	*psg_select = (volatile char) reg;
	*psg_write = val;
	
	
	Super(oldssp);
}


UINT8 read_psg(int reg)
{
	
}

void set_tone(int channel, int tuning)
{

	write_psg(tuning,channel);

}


void set_volume(int channel, int volume)
{
	
	write_psg((volume%15),channel);
}


void stop_sound()
{
	write_psg(A_VOLUME,0);
	write_psg(B_VOLUME,0);
	write_psg(C_VOLUME,0);

}


void enable_channel(int channel, int tone_on, int noise_on)
{
	write_psg(channel,tone_on);
	write_psg(channel+1,noise_on);
}


















