CC = g++
CFLAGS = -Wall -Werror -O3

smol:
	$(CC) $(CFLAGS) -o smol main.cpp image.cpp model.cpp

run: smol
	./smol.exe head.obj

clean:
	del *.exe
	del *.tga