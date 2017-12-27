all: 
	cc -o output fileopen.c -lm

run:
	@./output

clean:
	@rm output
