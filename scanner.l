%{

#include "parser.tab.h"  // Definicje tokenów generowane przez Bison
#include "tree.h"        // Definicje struktur drzewa
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Licznik linii (przydatny przy debugowaniu)
int line_number = 1;
%}

/* Definicje pomocnicze */
DIGIT       [0-9]
NUMBER      {DIGIT}+
WHITESPACE  [ \t]

/* Opcje skanera */
%option noyywrap
%option nounput
%option noinput

%%
    /* === REGUŁY LEKSYKALNE === */

{NUMBER}    {
                /* Rozpoznanie liczby całkowitej */
                yylval.node = create_number_node(atoi(yytext));
                if (yylval.node == NULL) {
                    fprintf(stderr, "Błąd: Nie można utworzyć węzła dla liczby %s\n", yytext);
                    exit(1);
                }
                return NUMBER;
            }

{WHITESPACE}+ {
                /* Ignoruj białe znaki (spacje i tabulacje) */
            }

\n          {
                /* Koniec linii - zwiększ licznik linii */
                line_number++;
                return EOL;
            }

"+"         { return '+'; }
"-"         { return '-'; }
"*"         { return '*'; }
"/"         { return '/'; }
"^"         { return '^'; }  /* Operator potęgowania */
"("         { return '('; }
")"         { return ')'; }

.           {
                /* Nierozpoznany znak */
                fprintf(stderr, "❌ Błąd leksykalny w linii %d: Nieznany znak '%s' (ASCII: %d)\n", 
                        line_number, yytext, (unsigned char)yytext[0]);
            }

%%
