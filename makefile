CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g

SRCDIR = .
SOURCES = main.c structures.c utils.c menu.c admin.c exam.c student.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = exam_system

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

main.o: main.c structures.h utils.h menu.h
structures.o: structures.c structures.h utils.h
utils.o: utils.c utils.h structures.h
menu.o: menu.c menu.h utils.h admin.h exam.h student.h structures.h
admin.o: admin.c admin.h utils.h exam.h menu.h structures.h
exam.o: exam.c exam.h utils.h admin.h menu.h structures.h
student.o: student.c student.h utils.h menu.h structures.h

clean:
	rm -f $(OBJECTS) $(TARGET)

install: $(TARGET)
	cp $(TARGET) /usr/local/bin/

uninstall:
	rm -f /usr/local/bin/$(TARGET)

