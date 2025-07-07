# 🌳 Pretty Printer for Arithmetic Expressions

A compiler construction project that parses arithmetic expressions and displays them as ASCII-art syntax trees. Built with Lex (Flex) and Yacc (Bison), featuring expression evaluation and elegant tree visualization.

![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Lex/Yacc](https://img.shields.io/badge/Lex/Yacc-FF6B6B?style=for-the-badge&logo=gnu&logoColor=white)
![Compiler Design](https://img.shields.io/badge/Compiler%20Design-4285F4?style=for-the-badge&logo=googlescholar&logoColor=white)
![AST](https://img.shields.io/badge/AST-00C853?style=for-the-badge&logo=tree&logoColor=white)

## 📋 Overview

This project implements a complete arithmetic expression parser that builds Abstract Syntax Trees (AST) and displays them in a visually appealing ASCII-art format. It serves as an educational tool for understanding compiler construction principles, particularly lexical analysis, parsing, and syntax tree generation.

### 🌟 Key Features

- **Lexical Analysis** - Token recognition using Flex
- **Syntax Parsing** - Grammar implementation with Bison
- **AST Construction** - Dynamic tree building during parsing
- **ASCII-art Visualization** - Beautiful tree display with connecting lines
- **Expression Evaluation** - Calculate results while traversing the tree
- **Error Recovery** - Graceful handling of syntax errors
- **Extended Operators** - Support for exponentiation and unary negation

## 🏗️ Architecture

### Core Components

- **`scanner.l`** - Lexical analyzer (Flex)
  - Token recognition and classification
  - Whitespace and newline handling
  - Error reporting for invalid characters

- **`parser.y`** - Syntax analyzer (Bison)
  - Grammar rules definition
  - Operator precedence and associativity
  - AST construction during parsing

- **`tree.h/tree.c`** - AST implementation
  - Node structures for different expression types
  - Tree manipulation functions
  - Visualization and evaluation algorithms

### Supported Operations

| Operator | Description | Precedence | Associativity |
|----------|-------------|------------|---------------|
| `+` | Addition | 1 | Left |
| `-` | Subtraction | 1 | Left |
| `*` | Multiplication | 2 | Left |
| `/` | Division | 2 | Left |
| `^` | Exponentiation | 3 | Right |
| `-` | Unary negation | 4 | Right |
| `()` | Parentheses | - | - |

## 🚀 Getting Started

### Prerequisites

- GCC compiler
- Flex >= 2.5
- Bison >= 3.0
- Make utility
- Linux/Unix/macOS environment

### Installation

1. Clone the repository:

```bash
git clone https://github.com/yourusername/pretty-printer-expressions.git
cd pretty-printer-expressions
```

2. Install dependencies (Ubuntu/Debian):

```bash
sudo apt-get update
sudo apt-get install build-essential flex bison
```

3. Build the project:

```bash
make
```

### Running the Program

```bash
# Method 1: Using make
make run

# Method 2: Direct execution
./pretty_printer
```

## 📝 Usage Examples

### Interactive Mode

```
╔═══════════════════════════════════════════════════════════════╗
║           Pretty Printer Wyrażeń Arytmetycznych               ║
╚═══════════════════════════════════════════════════════════════╝

> 2+3*4

===== ANALIZA WYRAŻENIA =====

📊 Drzewo składniowe:
└── [+]
    ├── 2
    └── [*]
        ├── 3
        └── 4

🧮 Obliczony wynik: 14

=============================
```

### More Examples

#### Parentheses change precedence:
```
> (2+3)*4

📊 Drzewo składniowe:
└── [*]
    ├── [+]
    │   ├── 2
    │   └── 3
    └── 4

🧮 Obliczony wynik: 20
```

#### Exponentiation (right-associative):
```
> 2^3^2

📊 Drzewo składniowe:
└── [^]
    ├── 2
    └── [^]
        ├── 3
        └── 2

🧮 Obliczony wynik: 512
```

#### Unary negation:
```
> -5+10

📊 Drzewo składniowe:
└── [+]
    ├── [-]
    │   └── 5
    └── 10

🧮 Obliczony wynik: 5
```

## 🔧 Technical Implementation

### Grammar Definition

```yacc
expr:
      NUMBER              
    | expr '+' expr       
    | expr '-' expr       
    | expr '*' expr       
    | expr '/' expr       
    | expr '^' expr       
    | '-' expr %prec UNARY
    | '(' expr ')'        
    ;
```

### AST Node Structure

```c
typedef struct Node {
    NodeType type;
    union {
        int number;
        struct {
            char op;
            struct Node *left;
            struct Node *right;
        } op_details;
        struct {
            char op;
            struct Node *operand;
        } unary_details;
    };
} Node;
```

### Tree Visualization Algorithm

The tree is displayed using a recursive algorithm that:
1. Prints the current node with appropriate prefix
2. Uses "├──" for non-tail children and "└──" for tail children
3. Adjusts the prefix for subtrees to create vertical lines
4. Maintains proper alignment across all levels

## 🧪 Testing

Run the built-in test suite:

```bash
make test
```

This executes predefined test cases:
- Basic arithmetic: `2+3*4`
- Parentheses: `(2+3)*4`
- Exponentiation: `2^3+1`
- Negation: `-5+10`

## 📊 Performance Characteristics

- **Time Complexity**: O(n) for parsing, where n is the number of tokens
- **Space Complexity**: O(h) for the AST, where h is the height of the expression tree
- **Memory Management**: Automatic cleanup after each expression evaluation

## 🛠️ Build System

The project includes a comprehensive Makefile with the following targets:

| Command | Description |
|---------|-------------|
| `make` | Build the project |
| `make run` | Build and run |
| `make test` | Run test cases |
| `make clean` | Remove build artifacts |
| `make help` | Show available commands |

## 🐛 Error Handling

The parser includes robust error handling:

- **Lexical Errors**: Unknown characters are reported with line numbers
- **Syntax Errors**: Invalid expressions trigger error recovery
- **Runtime Errors**: Division by zero is detected during evaluation
- **Memory Errors**: Allocation failures are handled gracefully

## 📚 Educational Value

This project demonstrates key compiler construction concepts:

1. **Lexical Analysis** - Pattern matching and tokenization
2. **Syntax Analysis** - Context-free grammar implementation
3. **Semantic Analysis** - Type checking (implicit in evaluation)
4. **AST Generation** - Tree data structure construction
5. **Tree Traversal** - Recursive algorithms for display and evaluation
Student ID: s24825  
Course: Compiler Construction / Formal Languages and Translation Techniques

---

<p align="center">Built with 🧠 and lots of ☕</p>
