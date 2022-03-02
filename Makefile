CC := clang.exe
INCLUDE := -I ../foo
SDL_INCLUDE := ..
ZLIB_INCLUDE := ..
#INCLUDE := $(SDL_INCLUDE) $(ZLIB_INCLUDE)

# ciao ciao
all: foo2.exe

%.o: %.c test.h
	$(CC) -c $(INCLUDE) -o $@ $<

foo2.exe: ciao.o hello.o main.o
	$(CC) -o $@ $^

test: foo2.exe
	./foo2.exe

clean:
	del *.o

.PHONY: all test clean