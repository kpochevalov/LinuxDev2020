GENERATES = file* README lib* errlog.txt
TRASH = *.o *~ o.* empty_file
CFLAGS = -fPIC
LD_LIBRARY_PATH=`pwd`
PROG = prog prog-a prog-so
ARG1 = abc
ARG3 = a b c

all:	README $(PROG)

prog:	const.o fun.o prog.o

prog-a:	prog.o liboutput_static.a
	cc -L. $^ -loutput_static -o $@

prog-so:	prog.o liboutput.so
	cc -L. prog.o -loutput -o $@

test:	$(PROG)
	./prog >> file11
	./prog $(ARG1) >> file12
	./prog $(ARG3) >> file13
	./prog-a >> file21
	./prog-a $(ARG1) >> file22
	./prog-a $(ARG3) >> file23
	LD_LIBRARY_PATH=`pwd` ./prog-so >> file31
	LD_LIBRARY_PATH=`pwd` ./prog-so $(ARG1) >> file32
	LD_LIBRARY_PATH=`pwd` ./prog-so $(ARG3) >> file33
	touch empty_file errlog.txt
	cmp file11 file21 || (echo "Different ans {11,21} " >> errlog.txt)
	cmp file21 file31 || (echo "Different ans {21,31} " >> errlog.txt)
	cmp file12 file22 || (echo "Different ans {12,22} " >> errlog.txt)
	cmp file22 file32 || (echo "Different ans {22,32} " >> errlog.txt)
	cmp file13 file23 || (echo "Different ans {13,23} " >> errlog.txt)
	cmp file23 file33 || (echo "Different ans {23,33} " >> errlog.txt)
	cmp empty_file errlog.txt && echo "\033[32mCorrect\033[0m" || echo "\033[31m" ; cat errlog.txt ; echo "\033[0m"
	make distclean

README:	prog
	./$< 2> $@

fun.o:	outlib.h

liboutput_static.a:	fun.o const.o
	ar rcs $@ -o $^

liboutput.so:	fun.o const.o
	cc -shared $^ -o $@

clean:
	rm -f $(TRASH)

distclean:	clean
	rm -rf $(GENERATES) $(PROG)
