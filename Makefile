# Makefile for hello.c
pidgin_notify: pidgin_notify.c
	gcc -Wall -fpic  -shared pidgin_notify.c -o pidgin_notify.so `pkg-config --libs --cflags glib-2.0 gtk+-2.0 purple` -lnotify
