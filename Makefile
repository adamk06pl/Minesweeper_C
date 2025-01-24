# Nazwa pliku wynikowego
TARGET = program

# Kompilator
CC = gcc

# Flagi kompilacji
CFLAGS = -Wall -Wextra

# Źródłowy plik C
SRC = main.c

# Reguła domyślna: kompilacja programu
all: $(TARGET)

# Reguła kompilacji
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Reguła czyszczenia plików tymczasowych
clean:
	rm -f $(TARGET)
