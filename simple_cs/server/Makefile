target:=server
srcs=$(wildcard ./*.c)
objs=$(srcs:.c=.o)
cc=gcc

$(target):$(objs)
	$(cc) -o $@ $^


%.o:%.c
	$(cc) -c -o $@ $<

clean:
	rm *.o $(target)
