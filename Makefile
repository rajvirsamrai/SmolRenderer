CC = g++
CFLAGS = -Wall -Werror

smol:
	$(CC) $(CFLAGS) -o smol main.cpp image.cpp

run: smol
	./smol.exe

clean:
	del *.exe
	del *.tga