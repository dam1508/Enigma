CFLAGS = g++ -Wall

go: main.o
	$(CFLAGS) main.o -o go

cmp: go
	./go

main.o: main.cpp
	$(CFLAGS) -c main.cpp

clean:
	rm *.o go
