# Example 1: Calculator CLI

A command-line calculator with advanced features including expression parsing, history, and scientific operations.

## Features

- Basic arithmetic operations (+, -, *, /)
- Scientific functions (sin, cos, tan, log, sqrt, pow)
- Expression parsing with parentheses
- Calculation history
- Memory functions (M+, M-, MR, MC)
- Error handling and validation

## Files

- `calculator.c` - Main calculator implementation
- `expression_parser.c` - Expression parsing logic
- `scientific.c` - Scientific functions
- `history.c` - Calculation history management
- `Makefile` - Build configuration
- `README.md` - This file

## Building

```bash
make
```

## Usage

```bash
./calculator
```

### Commands

- `help` - Show help information
- `history` - Show calculation history
- `clear` - Clear screen
- `quit` - Exit calculator
- `memory` - Show memory value
- `memory_clear` - Clear memory

### Examples

```
> 2 + 3 * 4
14

> sqrt(16) + pow(2, 3)
12

> (10 + 5) / 3
5

> memory = 100
> memory + 50
> memory
150
```

## Implementation Details

### Expression Parser
Uses recursive descent parsing to handle operator precedence and parentheses.

### Scientific Functions
Implements mathematical functions using the math library.

### History Management
Stores calculation history in a linked list structure.

### Memory Functions
Provides calculator-style memory operations.

