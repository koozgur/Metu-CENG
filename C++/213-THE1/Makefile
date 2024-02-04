CC=g++
CFLAGS=-ansi -Wall -pedantic-errors -O0

all: linkedlist browser

browser: Tab.h Node.h LinkedList.h Window.h Browser.h Window.cpp Browser.cpp main_browser.cpp
	$(CC) $(CFLAGS) main_browser.cpp Browser.cpp Window.cpp -o browser

linkedlist: Node.h LinkedList.h
	$(CC) $(CFLAGS) main_linkedlist.cpp -o linkedlist

clean:
	rm linkedlist
	rm browser