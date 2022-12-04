# Name: Nicholas Fotinakes
# Date: 2022-04-12
# Title: Lab 6 Makefile
# Description: This is the makefile for Lab 6

all: threadSync alphabet

threadSync: threadSync.c
	gcc threadSync.c -o threadSync -Wall -Werror -pthread

alphabet: alphabet.c
	gcc alphabet.c -o alphabet -Wall -Werror -pthread

clean:
	rm -f threadSync alphabet
