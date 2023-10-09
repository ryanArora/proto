CC = gcc
CFLAGS = -Wall -Woverflow -Werror -Iinclude 
SRCDIR = src
BUILDDIR = build

SRCS := $(wildcard $(SRCDIR)/*.c)
OBJS := $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(SRCS))

all: client server

# Rule to build the client executable
client: $(BUILDDIR)/client.o $(BUILDDIR)/http.o | mkdir
	$(CC) $(CFLAGS) -o $@ $^

# Rule to build the server executable
server: $(BUILDDIR)/server.o | mkdir
	$(CC) $(CFLAGS) -o $@ $^

# Rule to build object files from source files
$(BUILDDIR)/%.o: $(SRCDIR)/%.c | mkdir
	$(CC) $(CFLAGS) -c -o $@ $<

mkdir:
	mkdir -p $(BUILDDIR)

clean:
	rm -rf $(BUILDDIR) client server

.PHONY: all clean
