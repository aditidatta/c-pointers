#
# 'make depend' uses makedepend to automatically generate dependencies 
#               (dependencies are added to end of Makefile)
# 'make'        build executable file 'prog4'
# 'make clean'  removes all .o and executable files
#

# define the C compiler to use
CC = gcc-7

# define any compile-time flags
CFLAGS = -Wall -g

# define the C source files
SRCS = List.c Alloc.c prog4.c

# define the C object files 
OBJS = $(SRCS:.c=.o)

# define the executable file 
MAIN = prog4

#
#.PHONY: clean

all: $(SRCS) $(MAIN) \
    @echo prog4 has been compiled

$(MAIN): $(OBJS) \
    $(CC) $(CFLAGS) $(OBJS) -o $@

.c.o: \
    $(CC) $(CFLAGS) -c $<  -o $@

clean: \
    $(RM) *.o *~ $(MAIN)

# --- end

