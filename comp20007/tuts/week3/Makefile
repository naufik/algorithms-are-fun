# # # # # # #
# Sample Makefile for compiling a simple multi-module C program
#
# created for COMP20007 Design of Algorithms 2017
# by Matt Farrugia <matt.farrugia@unimelb.edu.au>
#

# Welcome to this sample Makefile. If you're new to make and makefiles, have a
# read through with the comments and follow their instructions.


# VARIABLES - change the values here to match your project setup

# specifying the C Compiler and Compiler Flags for make to use
CC     = gcc
CFLAGS = -Wall

# exe name and a list of object files that make up the program
EXE    = main-2
OBJ    = main-2.o list.o stack.o queue.o


# RULES - these tell make when and how to recompile parts of the project

# the first rule runs by default when you run 'make' ('make rule' for others)
# in our case, we probably want to build the whole project by default, so we
# make our first rule have the executable as its target
#  |
#  v
$(EXE): $(OBJ) # <-- the target is followed by a list of prerequisites
	$(CC) $(CFLAGS) -o $(EXE) $(OBJ)
# ^
# and a TAB character, then a shell command (or possibly multiple, 1 line each)
# (it's very important to use a TAB here because that's what make is expecting)

# the way it works is: if any of the prerequisites are missing or need to be
# recompiled, make will sort that out and then run the shell command to refresh
# this target too

# so our first rule says that the executable depends on all of the object files,
# and if any of the object files need to be updated (or created), we should do
# that and then link the executable using the command given


# okay here's another rule, this time to help make create object files
list.o: list.c list.h
	$(CC) $(CFLAGS) -c list.c

# this time the target is list.o. its prerequisites are list.c and list.h, and
# the command (its 'recepie') is the command for compiling (but not linking)
# a .c file

# list.c and list.h don't get their own rules, so make will just check if the
# files of those names have been updated since list.o was last modified, and
# re-run the command if they have been changed.


# actually, we don't need to provide all that detail! make knows how to compile
# .c files into .o files, and it also knows that .o files depend on their .c 
# files. so, it assumes these rules implicitly (unless we overwrite them as 
# above).

# so for the rest of the rules, we can just focus on the prerequisites!
# for example stack.o needs to be rebuilt if our list module changes, and
# also if stack.h changes (stack.c is an assumed prerequisite, but not stack.h)
stack.o: stack.h list.h

# note: we only depend on list.h, not also list.c. if something changes inside
# list.c, but list.h remains the same, then stack.o doesn't need to be rebuilt,
# because the way that list.o and stack.o are to be linked together will remain
# the same (as per list.h)

# likewise, queue.o depends on queue.h and the list module
queue.o: queue.h list.h

# so in the future we could save a lot of space and just write these rules:
# $(EXE): $(OBJ)
# 	$(CC) $(CFLAGS) -o $(EXE) $(OBJ)
# list.o: list.h
# stack.o: stack.h list.h
# queue.o: queue.h list.h



# finally, this last rule is a common convention, and a real nice-to-have
# it's a special target that doesn't represent a file (a 'phony' target) and
# just serves as an easy way to clean up the directory by removing all .o files
# and the executable, for a fresh start

# it can be accessed by specifying this target directly: 'make clean'
clean:
	rm -f $(OBJ) $(EXE)
