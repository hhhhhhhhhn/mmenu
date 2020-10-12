mmenu:
	cc -lncurses -o mmenu main.c
clean:
	rm mmenu
install: mmenu
	mv mmenu /usr/bin/mmenu
uninstall:
	rm /usr/bin/mmenu
debug:
	cc -lncurses -o mmenu main.c
	gdb -tui ./mmenu
