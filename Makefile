cli:
	gcc -std=c89 -o vpn_poll main.c lib.c /usr/lib/libcurl.dylib -Wall -pedantic-errors

