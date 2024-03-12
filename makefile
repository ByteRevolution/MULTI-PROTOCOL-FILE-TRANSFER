CC = gcc
CFLAGS = -Wall -Wextra -g

SRCDIR1 = ./server/src
SRCDIR2 = ./client/src
INCDIR = ./include
OBJDIR = obj
BINDIR = bin

SRCS1 = $(wildcard $(SRCDIR1)/*.c)
SRCS2 = $(wildcard $(SRCDIR2)/*.c)
OBJS1 = $(SRCS1:$(SRCDIR1)/%.c=$(OBJDIR)/server/%.o)
OBJS2 = $(SRCS2:$(SRCDIR2)/%.c=$(OBJDIR)/client/%.o)
DEPS = $(wildcard $(INCDIR)/*.h)

TARGET = $(BINDIR)/samba_conf

$(TARGET): $(OBJS1) $(OBJS2)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $^ -I$(INCDIR) 

$(OBJDIR)/server/%.o: $(SRCDIR1)/%.c $(DEPS)
	@mkdir -p $(OBJDIR)/server
	$(CC) $(CFLAGS) -c -o $@ $< -I$(INCDIR)

$(OBJDIR)/client/%.o: $(SRCDIR2)/%.c $(DEPS)
	@mkdir -p $(OBJDIR)/client
	$(CC) $(CFLAGS) -c -o $@ $< -I$(INCDIR)

.PHONY: clean
clean:
	rm -rf $(OBJDIR) $(BINDIR) path.txt
run :
	@sudo ./bin/samba_conf
