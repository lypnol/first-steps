CC = g++
CFLAGS = -g -Wall -std=c++11
SRCS = main.cpp
INCLUDES = -I/usr/local/include/SDL
LIBS = -lSDL -lSDL_Image -lSDL_TTF -lSDLmain 
FRAMEWORKS = -framework OpenGL -framework SDL -framework Cocoa
PROG = escape

$(PROG):$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(LIBS) $(SRCS) $(FRAMEWORKS) $(INCLUDES)
