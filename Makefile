run :
	clear
	gcc main.c -o run `pkg-config --cflags gtk+-3.0`  `pkg-config --libs gtk+-3.0` libbt.a
	./run
	rm run
