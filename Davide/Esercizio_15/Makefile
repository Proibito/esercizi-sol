CFLAGS = -std=c89 -pedantic

TARGET = test-list-module

OBJS = list-module.o test-list-module.o

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

all: $(TARGET)

clean:
	rm -f *.o $(TARGET) *~

run: $(TARGET)
	./$(TARGET)


