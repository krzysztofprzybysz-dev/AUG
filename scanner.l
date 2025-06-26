%{
    #include "y.tab.h" // Plik nagłówkowy generowany przez Bisona
%}

%%
[ \t]       ; /* Ignoruj spacje i tabulacje */
\n          { return EOL; } /* Rozpoznaj koniec linii i zwróć token EOL */
.           { printf("Nieznany znak: %s\n", yytext); }
%%

int yywrap(void) {
    return 1;
}