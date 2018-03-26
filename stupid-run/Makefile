CC = gcc
CFLAGS = -g -Wall -std=c11
SRCS = main.c
INCLUDES = -I/usr/local/include/SDL
LIBS = -lSDL -lSDL_Image -lSDL_TTF -lSDLmain 
FRAMEWORKS = -framework SDL -framework Cocoa
PROG = stupidrun

$(PROG):$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(LIBS) $(SRCS) $(FRAMEWORKS) $(INCLUDES)
