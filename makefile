CC = gcc
CFLAGS = -Wall -Wextra -g

SRCDIR1 = ./server/src
SRCDIR2 = ./client/src
INCDIR = ./include
OBJDIR = obj
BINDIR = bin

SRCS = $(wildcard $(SRCDIR1)/*.c)
SRCS += $(wildcard $(SRCDIR2)/*.c)
OBJS = $(SRCS:$(SRCDIR1)/%.c=$(OBJDIR)/%.o)
OBJS += $(SRCS:$(SRCDIR2)/%.c=$(OBJDIR)/%.o)
DEPS = $(wildcard $(INCDIR)/*.h)

TARGET = $(BINDIR)/samba_conf

$(TARGET): $(OBJS)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $^ -I$(INCDIR) 


$(OBJDIR)/%.o: $(SRCDIR1)/%.c $(SRCDIR2)/%.c $(DEPS)
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $< -I$(INCDIR) 	
.PHONY: clean reset remove move
clean:
	rm -rf $(OBJDIR) $(BINDIR)


print:
	$(info $(OBJS) $(SRCS))
