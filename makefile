hackaton.exe: hackaton.o funHackatonC.o funHackatonGTK.o
	gcc hackaton.o funHackatonC.o funHackatonGTK.o -o hackaton.exe `pkg-config --libs gtk+-2.0`

funHackatonGTK.o: funHackatonGTK.c
	gcc -c funHackatonGTK.c `pkg-config --cflags gtk+-2.0`

funHackatonC.o: funHackatonC.c
	gcc -c funHackatonC.c `pkg-config --cflags gtk+-2.0`

hackaton.o: hackaton.c
	gcc -c hackaton.c `pkg-config --cflags gtk+-2.0`