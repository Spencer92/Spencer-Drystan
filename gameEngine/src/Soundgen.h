/*

Routines to generate sound 








*/
#ifndef SOUNDGEN_H
#define SOUNDGEN_H


#define A 0
#define B 1
#define C 2

#define A_TONE 0
#define B_TONE 1
#define C_TONE 2
#define A_CHANNEL 0x3F
#define B_CHANNEL 0x7D
#define C_CHANNEL 0xFB
#define A_VOLUME 0x8
#define B_VOLUME 0x9
#define C_VOLUME 0xA
#define B 478
#define C_SHARP 451
#define D_FLAT 426
#define D 402
#define E_FLAT 379
#define E 358
#define F 338
#define G_FLAT 319
#define G 301
#define A_FLAT 284
#define A 268
#define B_FLAT 253
void start_music();
void music();
void stop_sound();





#endif