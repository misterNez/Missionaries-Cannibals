CC = g++
PROG = miss_vs_cann
OBJS = miss_cann.o tree.o

all: $(PROG)

$(PROG): $(OBJS)
	$(CC) -o $@ $^
	
clean:
	rm -rf *.o $(PROG)
