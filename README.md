Pretty Printer Wyrażeń Arytmetycznych
📋 Opis projektu
Pretty Printer to program napisany przy użyciu narzędzi Lex (Flex) i Yacc (Bison), który analizuje wyrażenia arytmetyczne i wyświetla je w formie drzewa składniowego ASCII-art. Program dodatkowo oblicza wartość wprowadzonego wyrażenia.
Główne funkcjonalności:

✅ Parsowanie wyrażeń arytmetycznych
✅ Budowanie drzewa składniowego (AST - Abstract Syntax Tree)
✅ Wyświetlanie drzewa w formie ASCII-art z liniami łączącymi
✅ Obliczanie wartości wyrażenia
✅ Obsługa błędów składniowych

Obsługiwane operacje:

Dodawanie (+)
Odejmowanie (-)
Mnożenie (*)
Dzielenie (/)
Potęgowanie (^)
Negacja (jednoargumentowy -)
Nawiasy () do zmiany kolejności działań

🛠️ Wymagania systemowe

System operacyjny: Linux/Unix/macOS
Kompilator: GCC
Flex: >= 2.5
Bison: >= 3.0
Make: do automatycznej kompilacji

Instalacja zależności (Ubuntu/Debian):
bashsudo apt-get update
sudo apt-get install build-essential flex bison
🚀 Kompilacja i uruchomienie
Metoda 1: Używając Makefile (zalecana)
bash# Kompilacja
make

# Uruchomienie
make run

# Uruchomienie testów
make test

# Czyszczenie
make clean
Metoda 2: Ręczna kompilacja
bash# Generowanie skanera
flex scanner.l

# Generowanie parsera
bison -d parser.y

# Kompilacja
gcc -o pretty_printer parser.tab.c lex.yy.c tree.c

# Uruchomienie
./pretty_printer
📖 Instrukcja użycia

Uruchom program poleceniem ./pretty_printer
Wprowadź wyrażenie arytmetyczne i naciśnij Enter
Program wyświetli:

Drzewo składniowe w formie ASCII-art z liniami łączącymi
Obliczony wynik wyrażenia


Wpisz pustą linię, aby zakończyć program

Przykłady wyrażeń:
2+3*4
(2+3)*4
10/2-3
2^3+1
-5+10
(10-4)/(3-1)
📁 Struktura projektu
.
├── scanner.l       # Analizator leksykalny (Flex)
├── parser.y        # Parser (Bison)
├── tree.h          # Definicje struktur drzewa AST
├── tree.c          # Implementacja funkcji drzewa
├── Makefile        # Plik automatyzacji kompilacji
├── README.md       # Dokumentacja projektu
└── examples/       # Przykładowe wyrażenia (opcjonalnie)
🏗️ Architektura programu
1. Analizator leksykalny (scanner.l)

Rozpoznaje tokeny: liczby, operatory, nawiasy
Przekazuje tokeny do parsera
Obsługuje błędy leksykalne

2. Parser (parser.y)

Implementuje gramatykę wyrażeń arytmetycznych
Buduje drzewo składniowe (AST)
Zarządza pierwszeństwem operatorów

3. Drzewo składniowe (tree.h/tree.c)

Struktury danych reprezentujące węzły drzewa
Funkcje tworzenia węzłów
Funkcja wyświetlania drzewa w formie ASCII-art
Funkcja obliczania wartości wyrażenia

🎯 Rozszerzenia względem podstawowej wersji

Operator potęgowania (^) - prawostronna łączność
Operator negacji (-) - jednoargumentowy
Eleganckie wyświetlanie drzewa - ASCII-art z liniami łączącymi
Obliczanie wartości wyrażenia
Lepsza obsługa błędów z recovery
Czytelny interfejs użytkownika z emoji
Dokumentacja kodu i komentarze

🐛 Obsługa błędów
Program obsługuje następujące błędy:

Błędy składniowe (np. brakujące nawiasy)
Dzielenie przez zero
Nierozpoznane znaki
Błędy alokacji pamięci

📊 Przykład działania
╔═══════════════════════════════════════════════════════════════╗
║           Pretty Printer Wyrażeń Arytmetycznych               ║
╚═══════════════════════════════════════════════════════════════╝

> (5+3)*2

===== ANALIZA WYRAŻENIA =====

📊 Drzewo składniowe:
└── [*]
    ├── [+]
    │   ├── 5
    │   └── 3
    └── 2

🧮 Obliczony wynik: 16

=============================
👨‍💻 Autor
[Twoje imię i nazwisko]
📄 Licencja
Ten projekt został stworzony w celach edukacyjnych.