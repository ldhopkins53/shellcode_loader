all:
	clang-format -i *.c
	gcc -g -F DWARF loader.c -o loader.bin
	nasm test.asm -o test.bin
clean:
	rm -vf *.bin
