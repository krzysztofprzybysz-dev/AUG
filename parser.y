%{
#include <stdio.h>
#include "tree.h" // Dołączamy nasz własny plik nagłówkowy

// Deklaracje funkcji, których Yacc będzie szukał
int yylex(void);
void yyerror(char const *s);
%}

/* Definicja tokenu, którego spodziewamy się od Lexa */
%token EOL

%%

/* Prosta reguła gramatyczna: program to jedna linia */
program:
    line
    ;

/* Linia to po prostu token końca linii (wciśnięcie Enter) */
line:
    EOL {
        printf("SUKCES! Parser rozpoznał wciśnięcie klawisza Enter.\n");
    }
    ;

%%

// Główna funkcja programu
int main(void) {
    printf("Program startuje. Naciśnij Enter, aby zakończyć.\n");
    yyparse(); // Uruchom parser
    return 0;
}

// Funkcja do obsługi błędów parsowania
void yyerror(char const *s) {
    fprintf(stderr, "Błąd parsowania: %s\n", s);
}