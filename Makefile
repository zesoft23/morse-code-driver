SRC := main.c
TARGET = morse
CFLAGS := -Wall -Werror
OBJS := $(SRC:.c=.o)

all: $(TARGET)

# if crosscompile is specified, prepend that to gcc
$(TARGET) : $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(TARGET) $(LDFLAGS)

clean:
	-rm -f *.o $(TARGET) *.elf *.map

