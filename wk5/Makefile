# Name: Nicholas Fotinakes
# Date: 2022-04-05
# Title: Lab5 Makefile
# Description: This is the makefile for Lab 5

all: threadHello_step1 threadHello_step1_fixed matrix_multiplication

threadHello_step1: threadHello_step1.c
	gcc threadHello_step1.c -o threadHello_step1 -Wall -Werror -pthread

threadHello_step1_fixed: threadHello_step1_fixed.c
	gcc threadHello_step1_fixed.c -o threadHello_step1_fixed -Wall -Werror -pthread

matrix_multiplication: matrix_multiplication.c
	gcc matrix_multiplication.c -o matrix_multiplication -std=c99 -Wall -Werror -pthread

clean:
	rm -f threadHello_step1 threadHello_step1_fixed matrix_multiplication
