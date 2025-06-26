%{

#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

// Deklaracje funkcji
int yylex(void);
void yyerror(const char *s);

// Zmienna globalna przechowująca tryb wyświetlania
int display_mode = 0; // 0 - proste drzewo, 1 - ładne drzewo
%}

/* Definicja unii dla wartości semantycznych */
%union {
    struct Node* node;
}

/* Definicja tokenów */
%token <node> NUMBER
%token EOL

/* Definicja typów dla symboli nieterminalnych */
%type <node> expr

/* Definicja pierwszeństwa i łączności operatorów */
%left '+' '-'
%left '*' '/'
%right '^'        /* Potęgowanie - prawostronne */
%right UNARY      /* Negacja - najwyższy priorytet */

%%
/* === REGUŁY GRAMATYKI === */

program:
      /* program może być pusty */
    | program line
    ;

line:
      EOL                 /* pusta linia */
    | expr EOL            {
                            printf("\n===== ANALIZA WYRAŻENIA =====\n");
                            
                            // Wyświetl drzewo składniowe
                            printf("\n📊 Drzewo składniowe:\n");
                            print_tree_pretty($1, "", 1);
                            
                            // Oblicz i wyświetl wynik
                            printf("\n🧮 Obliczony wynik: %d\n", evaluate_tree($1));
                            
                            printf("\n=============================\n\n");
                            
                            // Zwolnij pamięć
                            free_tree($1);
                          }
    | error EOL           {
                            fprintf(stderr, "Pomijam błędne wyrażenie. Spróbuj ponownie.\n");
                            yyerrok;  // Zresetuj stan błędu
                          }
    ;

expr:
      NUMBER              { $$ = $1; }
    | expr '+' expr       { $$ = create_operator_node('+', $1, $3); }
    | expr '-' expr       { $$ = create_operator_node('-', $1, $3); }
    | expr '*' expr       { $$ = create_operator_node('*', $1, $3); }
    | expr '/' expr       {
                            // Możemy dodać sprawdzenie dzielenia przez zero już tutaj
                            $$ = create_operator_node('/', $1, $3);
                          }
    | expr '^' expr       { $$ = create_operator_node('^', $1, $3); }
    | '-' expr %prec UNARY { $$ = create_unary_node('-', $2); }
    | '(' expr ')'        { $$ = $2; }
    ;

%%
/* === KOD C === */

/**
 * @brief Funkcja główna programu
 */
int main(void) {
    printf("╔═══════════════════════════════════════════════════════════════╗\n");
    printf("║           Pretty Printer Wyrażeń Arytmetycznych               ║\n");
    printf("╠═══════════════════════════════════════════════════════════════╣\n");
    printf("║ Obsługiwane operacje:                                         ║\n");
    printf("║   • Dodawanie (+)        • Odejmowanie (-)                   ║\n");
    printf("║   • Mnożenie (*)         • Dzielenie (/)                     ║\n");
    printf("║   • Potęgowanie (^)      • Negacja (-)                       ║\n");
    printf("║   • Nawiasy ()                                                ║\n");
    printf("╠═══════════════════════════════════════════════════════════════╣\n");
    printf("║ Przykłady:                                                    ║\n");
    printf("║   • (5+3)*2              • -5+10                              ║\n");
    printf("║   • 2^3+1                • (10-4)/(3-1)                       ║\n");
    printf("╠═══════════════════════════════════════════════════════════════╣\n");
    printf("║ Wpisz wyrażenie i naciśnij Enter. Pusta linia kończy program.║\n");
    printf("╚═══════════════════════════════════════════════════════════════╝\n\n");
    
    yyparse();
    
    printf("\nDziękujemy za skorzystanie z programu!\n");
    return 0;
}

/**
 * @brief Funkcja obsługi błędów parsera
 * @param s Komunikat o błędzie
 */
void yyerror(const char *s) {
    fprintf(stderr, "❌ Błąd parsowania: %s\n", s);
}