GCC = g++
CFLAGS = -O2 -std=c++14
SSEFLAGS = -msse2 -mssse3 -msse4.1 -msse4.2 -mavx -march=native
FILES = elastic.out cmheap.out cmsketch.out cusketch.out countheap.out countsketch.out \
		linearcounting.out mrac.out hashpipe.out sieving.out spacesaving.out univmon.out \
		css.out flowradar.out reversiblesketch.out

all: $(FILES) 

elastic.out: elastic.cpp BOBHash32.o
	$(GCC) $(CFLAGS) $(SSEFLAGS) -o elastic.out elastic.cpp BOBHash32.o

cmheap.out: cmheap.cpp BOBHash32.o
	$(GCC) $(CFLAGS) -o cmheap.out cmheap.cpp BOBHash32.o

countheap.out: countheap.cpp BOBHash32.o
	$(GCC) $(CFLAGS) -o countheap.out countheap.cpp BOBHash32.o

cmsketch.out: cmsketch.cpp BOBHash32.o
	$(GCC) $(CFLAGS) -o cmsketch.out cmsketch.cpp BOBHash32.o

cusketch.out: cusketch.cpp BOBHash32.o
	$(GCC) $(CFLAGS) -o cusketch.out cusketch.cpp BOBHash32.o

countsketch.out: countsketch.cpp BOBHash32.o
	$(GCC) $(CFLAGS) -o countsketch.out countsketch.cpp BOBHash32.o

hashpipe.out: hashpipe.cpp BOBHash32.o
	$(GCC) $(CFLAGS) -o hashpipe.out hashpipe.cpp BOBHash32.o

linearcounting.out: linearcounting.cpp BOBHash32.o 
	$(GCC) $(CFLAGS) -o linearcounting.out linearcounting.cpp BOBHash32.o

mrac.out: mrac.cpp BOBHash32.o
	$(GCC) $(CFLAGS) -o mrac.out mrac.cpp BOBHash32.o

sieving.out: BOBHash32.o
	$(GCC) $(CFLAGS) -o sieving.out sieving.cpp BOBHash32.o

spacesaving.out:
	$(GCC) $(CFLAGS) -o spacesaving.out spacesaving.cpp

univmon.out: BOBHash32.o
	$(GCC) $(CFLAGS) -o univmon.out univmon.cpp BOBHash32.o

css.out: BOBHash32.o
	$(GCC) $(CFLAGS) -o css.out css.cpp BOBHash32.o

flowradar.out: BOBHash32.o
	$(GCC) $(CFLAGS) -o flowradar.out flowradar.cpp	BOBHash32.o

reversiblesketch.out: common.o os_galoisField.o os_mangler.o BOBHash32.o
	$(GCC) $(CFLAGS) -o reversiblesketch.out reversiblesketch.cpp common.o os_galoisField.o os_mangler.o BOBHash32.o

common.o:
	$(GCC) $(CFLAGS) -c ../common/common.cc

os_galoisField.o:
	$(GCC) $(CFLAGS) -c ../common/os_galoisField.cc

os_mangler.o:
	$(GCC) $(CFLAGS) -c ../common/os_mangler.cc

# undefined reference to `BOBHash32:
BOBHash32.o:
	$(GCC) $(CFLAGS) -c ../common/BOBHash32.cpp

clean:
	rm $(all) -f *~ *.o *.out
