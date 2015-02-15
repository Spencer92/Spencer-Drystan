# Atari (GCC/VBCC) Makefile 
#Drystan Mazur 2 Feb 2015
#Use hexdump -C <file.o>on linux to check for symbols being exported
#Uses auto depencies to compile all the files without having lots of lines
PATH := ${PATH}:/opt/vbcc/bin
VBCC := /opt/vbcc
#comment the above out for cc68x
CC = vc
#change to cc68x for  crappy compiler
ASM = vasmm68k_mot 
ASMFLAGS = -Faout  -m68000 -spaces -x -showopt 
#ASMFLAGS =  -g -D -L2
#ASM = gen
CFLAGS =  +tos -g 
CDFLAGS = +tos  -c  
#CFLAGS =  -g
#CDFLAGS = -g -c -v



RM = rm

SOURCES= AIsystem.c  CollsionDetect.c  font.c GameEngine.c Keyboard.c RenderEngine.c  TileControl.c
#change to whatever you called all of your srouce files
ASMSOURCES = AsemblerRoutines.s
#change to whatever your asslembler stuff is called

OBJS = $(SOURCES:.c=.o) $(ASMSOURCES:.s=.o)
#LEAVE AS IS !!!!!!!!!!

TARGET = test.tos
#change to what you want your target to be called

all:$(TARGET)


$(TARGET):  $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)


.c.o:
	$(CC) $(CDFLAGS) $(LFLAGS)  $< -o $@


.s.o:
	$(ASM) $(ASMFLAGS)  $< -o $@


clean:
	$(RM) *.o *.tos
