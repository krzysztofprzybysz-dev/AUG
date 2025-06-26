# Makefile dla Pretty Printer Wyrażeń Arytmetycznych
# Autor: [Twoje imię i nazwisko]
# Data: 2025

# Kompilator i flagi
CC = gcc
CFLAGS = -Wall -Wextra -g -std=c11 -D_GNU_SOURCE
LEX = flex
YACC = bison

# Nazwa programu wykonywalnego
TARGET = pretty_printer

# Pliki źródłowe
SOURCES = parser.tab.c lex.yy.c tree.c
OBJECTS = $(SOURCES:.c=.o)
HEADERS = tree.h parser.tab.h

# Główna reguła
all: $(TARGET)

# Kompilacja programu wykonywalnego
$(TARGET): parser.tab.h lex.yy.c $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS)
	@echo "✅ Kompilacja zakończona sukcesem!"
	@echo "📋 Uruchom program poleceniem: ./$(TARGET)"

# Generowanie parsera
parser.tab.c parser.tab.h: parser.y
	$(YACC) -d parser.y

# Generowanie skanera
lex.yy.c: scanner.l parser.tab.h
	$(LEX) scanner.l

# Kompilacja plików obiektowych
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Zależności
lex.yy.o: lex.yy.c parser.tab.h tree.h
parser.tab.o: parser.tab.c tree.h
tree.o: tree.c tree.h parser.tab.h

# Uruchomienie programu
run: $(TARGET)
	./$(TARGET)

# Testy
test: $(TARGET)
	@echo "🧪 Uruchamianie testów..."
	@echo "Test 1: 2+3*4"
	@echo "2+3*4" | ./$(TARGET)
	@echo "\nTest 2: (2+3)*4"
	@echo "(2+3)*4" | ./$(TARGET)
	@echo "\nTest 3: 2^3+1"
	@echo "2^3+1" | ./$(TARGET)
	@echo "\nTest 4: -5+10"
	@echo "-5+10" | ./$(TARGET)

# Czyszczenie
clean:
	rm -f $(TARGET) $(OBJECTS) lex.yy.c parser.tab.c parser.tab.h
	@echo "🧹 Wyczyszczono pliki tymczasowe"

# Pełne czyszczenie (włącznie z plikami generowanymi przez edytory)
distclean: clean
	rm -f *~ *.swp *.bak

# Pomoc
help:
	@echo "📖 Dostępne komendy:"
	@echo "  make        - kompiluje program"
	@echo "  make run    - kompiluje i uruchamia program"
	@echo "  make test   - uruchamia przykładowe testy"
	@echo "  make clean  - usuwa pliki tymczasowe"
	@echo "  make help   - wyświetla tę pomoc"

.PHONY: all run test clean distclean help