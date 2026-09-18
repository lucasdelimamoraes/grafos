# Makefile - Pratica 01
 
CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
TARGET = main
OBJS = grafo_matriz.o grafo_lista.o main.o
 
all: $(TARGET)
 
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) -lm
 
grafo_matriz.o: grafo_matriz.c grafo_matriz.h
	$(CC) $(CFLAGS) -c grafo_matriz.c
 
grafo_lista.o: grafo_lista.c grafo_lista.h
	$(CC) $(CFLAGS) -c grafo_lista.c
 
main.o: main.c grafo_matriz.h grafo_lista.h
	$(CC) $(CFLAGS) -c main.c
 
clean:
	rm -f $(OBJS) $(TARGET) $(TARGET).exe
 
.PHONY: all clean