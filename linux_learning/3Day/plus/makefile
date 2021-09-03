target = app
CPPFLAGS = ./include
path = ./src

src = $(wildcard $(path)/*.c)
obj = $(patsubst %.c, %.o, $(src))

$(target):$(obj)
	gcc $^ -o $@

%.o:%.c
	echo $<
	gcc -c $< -I $(CPPFLAGS) -o $@ 

.PHONY:clean
clean:
	-rm $(path)/*.o
	-rm $(target)
