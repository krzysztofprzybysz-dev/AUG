/**
 * @file tree.c
 * @brief Implementacja funkcji do obsługi drzewa składniowego
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

// Zewnętrzna deklaracja funkcji yyerror z parser.y
extern void yyerror(const char *s);

/**
 * @brief Tworzy nowy węzeł przechowujący liczbę
 */
Node* create_number_node(int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        yyerror("Błąd: Nie udało się zaalokować pamięci dla węzła liczby");
        return NULL;
    }
    node->type = TYPE_NUM;
    node->number = value;
    return node;
}

/**
 * @brief Tworzy nowy węzeł operatora binarnego
 */
Node* create_operator_node(char op, Node* left, Node* right) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        yyerror("Błąd: Nie udało się zaalokować pamięci dla węzła operatora");
        return NULL;
    }
    node->type = TYPE_OP;
    node->op_details.op = op;
    node->op_details.left = left;
    node->op_details.right = right;
    return node;
}

/**
 * @brief Tworzy nowy węzeł operatora jednoargumentowego
 */
Node* create_unary_node(char op, Node* operand) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        yyerror("Błąd: Nie udało się zaalokować pamięci dla węzła operatora jednoargumentowego");
        return NULL;
    }
    node->type = TYPE_UNARY;
    node->unary_details.op = op;
    node->unary_details.operand = operand;
    return node;
}

/**
 * @brief Zwalnia pamięć zajmowaną przez drzewo (rekurencyjnie)
 */
void free_tree(Node* node) {
    if (node == NULL) {
        return;
    }
    
    switch (node->type) {
        case TYPE_OP:
            free_tree(node->op_details.left);
            free_tree(node->op_details.right);
            break;
        case TYPE_UNARY:
            free_tree(node->unary_details.operand);
            break;
        case TYPE_NUM:
            // Liczba nie ma potomków
            break;
    }
    
    free(node);
}

/**
 * @brief Wyświetla drzewo w prostej formie ASCII (funkcja pomocnicza - nieużywana w głównym programie)
 * 
 * Ta funkcja jest zachowana jako alternatywna metoda wyświetlania drzewa.
 * W głównym programie używamy print_tree_pretty() dla lepszej wizualizacji.
 */
void print_tree(Node* node, int level) {
    if (node == NULL) {
        return;
    }

    // Dla operatorów binarnych, najpierw wyświetl prawe poddrzewo
    if (node->type == TYPE_OP) {
        print_tree(node->op_details.right, level + 1);
    }

    // Wyświetl wcięcia
    for (int i = 0; i < level; i++) {
        printf("    ");
    }

    // Wyświetl wartość węzła
    switch (node->type) {
        case TYPE_NUM:
            printf("%d\n", node->number);
            break;
        case TYPE_OP:
            printf("%c\n", node->op_details.op);
            break;
        case TYPE_UNARY:
            printf("(%c)\n", node->unary_details.op);
            break;
    }

    // Dla operatorów, wyświetl lewe poddrzewo/operand
    if (node->type == TYPE_OP) {
        print_tree(node->op_details.left, level + 1);
    } else if (node->type == TYPE_UNARY) {
        print_tree(node->unary_details.operand, level + 1);
    }
}

/**
 * @brief Wyświetla drzewo w ładniejszej formie ASCII z liniami łączącymi
 */
void print_tree_pretty(Node* node, const char* prefix, int is_tail) {
    if (node == NULL) {
        return;
    }

    printf("%s", prefix);
    printf("%s", is_tail ? "└── " : "├── ");
    
    // Wyświetl wartość węzła
    switch (node->type) {
        case TYPE_NUM:
            printf("%d\n", node->number);
            break;
        case TYPE_OP:
            printf("[%c]\n", node->op_details.op);
            break;
        case TYPE_UNARY:
            printf("[%c]\n", node->unary_details.op);
            break;
    }

    // Przygotuj przedrostek dla potomków
    char new_prefix[256];
    snprintf(new_prefix, sizeof(new_prefix), "%s%s", prefix, is_tail ? "    " : "│   ");

    // Wyświetl potomków
    if (node->type == TYPE_OP) {
        print_tree_pretty(node->op_details.left, new_prefix, 0);
        print_tree_pretty(node->op_details.right, new_prefix, 1);
    } else if (node->type == TYPE_UNARY) {
        print_tree_pretty(node->unary_details.operand, new_prefix, 1);
    }
}

/**
 * @brief Oblicza wartość wyrażenia reprezentowanego przez drzewo
 */
int evaluate_tree(Node* node) {
    if (node == NULL) {
        yyerror("Błąd: Próba obliczenia wartości NULL");
        return 0;
    }

    switch (node->type) {
        case TYPE_NUM:
            return node->number;
            
        case TYPE_OP: {
            int left_val = evaluate_tree(node->op_details.left);
            int right_val = evaluate_tree(node->op_details.right);
            
            switch (node->op_details.op) {
                case '+': return left_val + right_val;
                case '-': return left_val - right_val;
                case '*': return left_val * right_val;
                case '/': 
                    if (right_val == 0) {
                        yyerror("Błąd: Dzielenie przez zero!");
                        return 0;
                    }
                    return left_val / right_val;
                case '^': {
                    // Prosty algorytm potęgowania dla liczb całkowitych
                    int result = 1;
                    for (int i = 0; i < right_val; i++) {
                        result *= left_val;
                    }
                    return result;
                }
                default:
                    yyerror("Błąd: Nieznany operator");
                    return 0;
            }
        }
        
        case TYPE_UNARY: {
            int operand_val = evaluate_tree(node->unary_details.operand);
            switch (node->unary_details.op) {
                case '-': return -operand_val;
                default:
                    yyerror("Błąd: Nieznany operator jednoargumentowy");
                    return 0;
            }
        }
        
        default:
            yyerror("Błąd: Nieznany typ węzła");
            return 0;
    }
}