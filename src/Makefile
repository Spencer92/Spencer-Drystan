# Atari (GCC/VBCC) Makefile 
#Drystan Mazur 2 Feb 2015


PATH := ${PATH}:/opt/vbcc/bin
VBCC := /opt/vbcc
CC = vc
ASM = vasm
ASMFLAGS = -m68000 -Felf 

LD = vlink

CFLAGS = +tos -g -vv
CDFLAGS = +tos -c -vv

RM = rm
LFLAGS = -I/home/drystan/workspace2015/game-stage2/src/
#The above directory name depends where your header file is residing

TARGET = test.tos

OBJS = testLib.o raster.o

all:$(TARGET)

$(TARGET): $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)


raster.o: raster.c
	$(CC) $(CDFLAGS) $(LFLAGS) raster.c



testLib.o: testLib.c
	$(CC) $(CDFLAGS) $(LFLAGS) testLib.c

.s.o:
	$(ASM) $(ASMFLAGS) $< -o $@


clean:
	$(RM) *.o *.tos
