/**
 * @file tree.h
 * @brief Definicje struktur i funkcji do obsługi drzewa składniowego wyrażeń arytmetycznych
 * 
 * Ten plik zawiera definicje struktur reprezentujących węzły drzewa AST (Abstract Syntax Tree)
 * oraz deklaracje funkcji do tworzenia, wyświetlania i zwalniania drzewa.
 */

#ifndef TREE_H
#define TREE_H

// Typ wyliczeniowy określający rodzaj węzła w drzewie
typedef enum {
    TYPE_NUM,     // Węzeł przechowujący liczbę całkowitą
    TYPE_OP,      // Węzeł przechowujący operator binarny
    TYPE_UNARY    // Węzeł przechowujący operator jednoargumentowy (rozszerzenie)
} NodeType;

// Struktura reprezentująca węzeł drzewa składniowego
typedef struct Node {
    NodeType type;  // Typ węzła
    
    union {
        // Dane dla węzła liczbowego
        int number;
        
        // Dane dla węzła operatora binarnego
        struct {
            char op;                // Operator: '+', '-', '*', '/', '^'
            struct Node *left;      // Lewy operand
            struct Node *right;     // Prawy operand
        } op_details;
        
        // Dane dla węzła operatora jednoargumentowego (rozszerzenie)
        struct {
            char op;                // Operator: '-' (negacja)
            struct Node *operand;   // Operand
        } unary_details;
    };
} Node;

// Prototypy funkcji

/**
 * @brief Tworzy nowy węzeł przechowujący liczbę
 * @param value Wartość liczbowa
 * @return Wskaźnik na utworzony węzeł lub NULL w przypadku błędu
 */
Node* create_number_node(int value);

/**
 * @brief Tworzy nowy węzeł operatora binarnego
 * @param op Znak operatora
 * @param left Wskaźnik na lewe poddrzewo
 * @param right Wskaźnik na prawe poddrzewo
 * @return Wskaźnik na utworzony węzeł lub NULL w przypadku błędu
 */
Node* create_operator_node(char op, Node* left, Node* right);

/**
 * @brief Tworzy nowy węzeł operatora jednoargumentowego
 * @param op Znak operatora
 * @param operand Wskaźnik na operand
 * @return Wskaźnik na utworzony węzeł lub NULL w przypadku błędu
 */
Node* create_unary_node(char op, Node* operand);

/**
 * @brief Wyświetla drzewo w prostej formie ASCII (funkcja pomocnicza)
 * @param node Wskaźnik na korzeń drzewa
 * @param level Poziom zagnieżdżenia (używany do wcięć)
 * @note Ta funkcja jest zachowana jako alternatywna metoda wyświetlania
 */
void print_tree(Node* node, int level);

/**
 * @brief Wyświetla drzewo w formie ASCII-art z liniami łączącymi
 * @param node Wskaźnik na korzeń drzewa
 * @param prefix Przedrostek do wyświetlenia
 * @param is_tail Czy węzeł jest ostatnim dzieckiem
 * @note To jest główna funkcja używana do wyświetlania drzewa w programie
 */
void print_tree_pretty(Node* node, const char* prefix, int is_tail);

/**
 * @brief Oblicza wartość wyrażenia reprezentowanego przez drzewo
 * @param node Wskaźnik na korzeń drzewa
 * @return Wartość wyrażenia
 */
int evaluate_tree(Node* node);

/**
 * @brief Zwalnia pamięć zajmowaną przez drzewo
 * @param node Wskaźnik na korzeń drzewa
 */
void free_tree(Node* node);

#endif // TREE_H