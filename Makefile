all: dirs run

clean:
	rm -rf bin

run:
	# gcc and.c -o bin/and && ./bin/and
	gcc first_order.c -o bin/first_order && ./bin/first_order

dirs:
	mkdir -p bin

