GCC = g++
CFLAGS = -O2 -std=c++14
SSEFLAGS = -msse2 -mssse3 -msse4.1 -msse4.2 -mavx -march=native
FILES = elastic.out elastic_my.out cmsketch.out cusketch.out countsketch.out

DFLAGs = -DSTART_FILE_NO=1 -DEND_FILE_NO=10 -DTOT_MEM_IN_BYTES=614400

all: $(FILES) 

elastic.out: elastic.cpp BOBHash32.o
	$(GCC) $(CFLAGS) $(DFLAGs) $(SSEFLAGS) -o elastic.out elastic.cpp BOBHash32.o

elastic_my.out: elastic_my.cpp BOBHash32.o
	$(GCC) $(CFLAGS) $(DFLAGs) $(SSEFLAGS) -o elastic_my.out elastic_my.cpp BOBHash32.o

cmsketch.out: cmsketch.cpp BOBHash32.o
	$(GCC) $(CFLAGS) $(DFLAGs) -o cmsketch.out cmsketch.cpp BOBHash32.o

cusketch.out: cusketch.cpp BOBHash32.o
	$(GCC) $(CFLAGS) $(DFLAGs) -o cusketch.out cusketch.cpp BOBHash32.o

countsketch.out: countsketch.cpp BOBHash32.o
	$(GCC) $(CFLAGS) $(DFLAGs) -o countsketch.out countsketch.cpp BOBHash32.o

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
