all:
	clang-format -i *.c
	gcc -g -F DWARF loader.c -o loader.bin
	nasm breakpoint.asm -o breakpoint.bin
	./loader.bin ./breakpoint.bin
clean:
	rm -vf *.bin
