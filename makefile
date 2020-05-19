# Name: Dmitriy Khristoforov
# Project: lab 2

# This is a Makefile for my lab assignment. It allows me to easily and accurately rebuild
# the lab assignment.


# The CC and CFLAGS variables are defined to ensure I'm using the native compiler and
# that the correct command-line options are set
CC=gcc
CFLAGS=-g

# Here is my default target for the Makefile.  When I type make, this first target will
# be created. I.e., all the executables
all: spiritd mole
.PHONY: all

# On the following lines (which _must_ start with a tab), are the commands I need to type -- 
# each time my source file is modified.
spiritd: spiritd.c
	$(CC) $(CFLAGS) -c spiritd.c
	$(CC) $(CFLAGS) -o $@ spiritd.o

mole: mole.c
	$(CC) $(CFLAGS) -c mole.c
	$(CC) $(CFLAGS) -o $@ mole.o


# By convention, I always have a target called
# "clean" that I used to define all temporary
# or intermediates.
clean:
	rm -f spiritd mole spiritd.o mole.o *~

