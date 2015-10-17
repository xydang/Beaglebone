INCLUDE=-I ./include/ -I ./json-c/

LIBJSON=./json-c/arraylist.c ./json-c/json_object.c ./json-c/json_c_version.c ./json-c/json_object_iterator.c ./json-c/json_tokener.c ./json-c/json_util.c ./json-c/libjson.c ./json-c/linkhash.c ./json-c/printbuf.c ./json-c/random_seed.c ./json-c/debug.c

PARA=-O2 -Wno-deprecated-declarations -Wno-unused-result

LIBS= -lpthread

all:iot

iot:
	gcc -g -o iot  main.c serial.c gpio.c tcp.c reply.c mpl3115.c msg.c $(LIBJSON) $(INCLUDE) $(LIBS) $(PARA)
clean:
	rm -rfv iot

