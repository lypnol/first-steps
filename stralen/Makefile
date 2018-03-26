CC = gcc
CFLAGS = -g -Wall -std=c++11
SRCS = main.cpp
INCLUDES = -I/usr/local/include/SDL
LIBS = -lSDL -lSDL_Image -lSDL_TTF -lSDLmain 
FRAMEWORKS = -framework Cocoa
PROG = stralen

$(PROG):$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(LIBS) $(SRCS) $(FRAMEWORKS) $(INCLUDES)
