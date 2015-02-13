
tst_rast.tos: testLib.o raster.o clrScrn.o
	cc68x -g testLib.o raster.o clrScrn.o -o tst_rast.tos

testLib.o: testLib.c raster.h
	cc68x -g -c -v testLib.c

raster.o: raster.c raster.h
	cc68x -g -c -v raster.c

clrScrn.o: clrScrn.s
	gen -g -D -L2 clrScrn.s
#raster2.o: raster2.c raster.h
#	cc68x -g -c -v raster2.c
