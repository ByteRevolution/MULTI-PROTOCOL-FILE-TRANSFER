CC = gcc
CFLAGS = -Wall -Wextra -g

SRCDIR = source
INCDIR = include
OBJDIR = build

SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
DEPS = $(wildcard $(INCDIR)/*.h)

TARGET = main

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $< -I$(INCDIR)
    
.PHONY: clean reset remove move
clean:
	rm -rf $(OBJDIR) main 
