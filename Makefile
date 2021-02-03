CC = g++
CFLAGS = -Wall -Werror

smol:
	$(CC) $(CFLAGS) -o smol main.cpp image.cpp model.cpp

run: smol
	./smol.exe african_head.obj

clean:
	del *.exe
	del *.tga