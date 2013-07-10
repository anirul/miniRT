# a simple stupid Makefile
UNAME := $(shell uname)

ifeq ($(UNAME), Darwin)
CC = clang
CXX = clang++
CFLAGS = -O0 -g -I/opt/local/include -I/opt/local/include/SDL
LIBS = -L/opt/local/lib/ \
	-framework GLUT -framework Cocoa -framework OpenGL -framework OpenCL \
	-lSDL -lSDLmain
endif

ifeq ($(UNAME), Linux)
CC = gcc
CXX = g++
CFLAGS = -O0 -g -I/usr/include -I/usr/local/include
LIBS = -L/usr/lib64 -L/usr/local/lib \
	-lglut -lSDL -lSDLmain -lGLU -lOpenCL -lGL
endif

ALL = miniRT

all : $(ALL)

miniRT_cam.o : miniRT_cam.cpp miniRT_cam.h
	$(CXX) -o miniRT_cam.o -c miniRT_cam.cpp $(CFLAGS)
miniRT_index_buffer.o : miniRT_index_buffer.cpp miniRT_index_buffer.h
	$(CXX) -o miniRT_index_buffer.o -c miniRT_index_buffer.cpp $(CFLAGS)
miniRT_main.o : miniRT_main.cpp miniRT_main.h
	$(CXX) -o miniRT_main.o -c miniRT_main.cpp $(CFLAGS)
miniRT_math.o : miniRT_math.cpp miniRT_math.h
	$(CXX) -o miniRT_math.o -c miniRT_math.cpp $(CFLAGS)
miniRT_new.o : miniRT_new.cpp miniRT_new.h
	$(CXX) -o miniRT_new.o -c miniRT_new.cpp $(CFLAGS)
miniRT_render.o : miniRT_render.cpp miniRT_render.h
	$(CXX) -o miniRT_render.o -c miniRT_render.cpp $(CFLAGS)
miniRT_triangle.o : miniRT_triangle.cpp miniRT_triangle.h
	$(CXX) -o miniRT_triangle.o -c miniRT_triangle.cpp $(CFLAGS)
miniRT_vertex_buffer.o : miniRT_vertex_buffer.cpp miniRT_vertex_buffer.h
	$(CXX) -o miniRT_vertex_buffer.o -c miniRT_vertex_buffer.cpp $(CFLAGS)
miniRT_win.o : miniRT_win.cpp miniRT_win.h
	$(CXX) -o miniRT_win.o -c miniRT_win.cpp $(CFLAGS)

miniRT : miniRT_cam.o miniRT_index_buffer.o miniRT_main.o miniRT_math.o miniRT_new.o miniRT_render.o miniRT_triangle.o miniRT_vertex_buffer.o miniRT_win.o
	$(CXX) -o miniRT miniRT_cam.o miniRT_index_buffer.o miniRT_main.o miniRT_math.o miniRT_new.o miniRT_render.o miniRT_triangle.o miniRT_vertex_buffer.o miniRT_win.o $(LIBS)

clean :
	rm -f $(ALL) *.o

