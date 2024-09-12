CC=gcc

CFLAGS=-g -Wall -Iinclude 

HEADER_DIR = include
SOURCE_DIR = src

SOURCES=$(wildcard $(SOURCE_DIR)/*.c)      
OBJECTS=$(SOURCES:$(SOURCE_DIR)/%.c=$(SOURCE_DIR)/%.o) 

EXECUTABLE=program

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

$(SOURCE_DIR)/%.o: $(SOURCE_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(SOURCE_DIR)/*.o $(EXECUTABLE)

run: $(EXECUTABLE)
	# Chạy tệp thực thi
	./$(EXECUTABLE)
