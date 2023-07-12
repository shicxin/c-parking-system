CC="gcc"
all:a.exe

obj-y=hello.oright.omain.c

a.exe:obj-y
	$(CC)-o$@$^

hello.o:hello.c
	$(CC)-o$@-c$<

right.o:right.c
	$(CC)-o$@-c$<

clean:
	rm-f*.o
