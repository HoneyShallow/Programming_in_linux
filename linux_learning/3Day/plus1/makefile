app:a.o b.o
	gcc a.o -o a
	gcc b.o -o b

a.o:a.c
	gcc -c a.c -o a.o

b.o:b.c
	gcc -c b.c -o b.o


# src = $(wildcard ./*.c)
# temp = $(patsubst %.c, %.o, $(src))
#  obj = $(patsubst %.o, %, $(temp))

# %:%.o
#	gcc $< -o $@

# %.o:%.c
# gcc -c $< -o $@
