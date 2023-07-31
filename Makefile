CC = gcc
CFLAGS = -Wall
LDFLAGS = -lncurses	

TARGET = cspeed 
SOURCE = cspeed.c
	
all: $(TARGET)
	
$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE) $(LDFLAGS)
	
clean:
	rm -f $(TARGET)

