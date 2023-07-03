all: dirs run

clean:
	rm -rf bin

run:
	gcc and.c -o bin/and && ./bin/and

dirs:
	mkdir -p bin

