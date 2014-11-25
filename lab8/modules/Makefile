obj-m += audio_test.o
audio_test-objs := xac97.o audio_buffer.o
all:
	make -C '/homes/ugrad/billlipeng/ECEN449/lab8/linux-2.6.35.7/' M=$(PWD) modules

clean:
	make -C '/homes/ugrad/billlipeng/ECEN449/lab8/linux-2.6.35.7/' M=$(PWD) clean
