target:=client
cc=gcc
srcs=$(wildcard ./*.c)
objs=$(srcs:.c=.o)

$(target):$(objs)
	$(cc) -o $@ $^

$.o:%.c
	$(cc) -c -o $@ $<

clean:
	rm $(target) *.o
