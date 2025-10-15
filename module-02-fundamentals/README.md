# Module 2: C Fundamentals

Welcome to Module 2! Now that you understand the basics of C and how to compile programs, it's time to dive into the fundamental building blocks of C programming: data types, variables, operators, control flow, and functions.

## 🎯 Learning Objectives

By the end of this module, you will be able to:
- Work with different data types and variables
- Use input and output functions effectively
- Apply operators and write expressions
- Implement control flow structures (if, switch, loops)
- Write and call functions
- Understand variable scope and storage classes

## 📚 Topics Covered

1. [Data Types and Variables](#data-types-and-variables)
2. [Input and Output](#input-and-output)
3. [Operators and Expressions](#operators-and-expressions)
4. [Control Flow](#control-flow)
5. [Functions](#functions)
6. [Variable Scope and Storage Classes](#variable-scope-and-storage-classes)
7. [Exercises](#exercises)

---

## Data Types and Variables

### Basic Data Types

C provides several built-in data types:

#### Integer Types
```c
int age = 25;           // 4 bytes, typically -2,147,483,648 to 2,147,483,647
short temperature = 32; // 2 bytes, -32,768 to 32,767
long population = 1000000L; // 8 bytes (on 64-bit systems)
long long huge_number = 9223372036854775807LL; // 8 bytes

// Unsigned versions (only positive numbers)
unsigned int count = 100;
unsigned char byte = 255;
```

#### Floating-Point Types
```c
float price = 19.99f;      // 4 bytes, ~7 decimal digits precision
double precise = 3.14159;  // 8 bytes, ~15 decimal digits precision
long double very_precise = 3.141592653589793238L; // 16 bytes (platform dependent)
```

#### Character Type
```c
char letter = 'A';        // 1 byte, ASCII value
char newline = '\n';      // Escape sequence
char tab = '\t';          // Tab character
char backslash = '\\';    // Backslash character
```

#### Boolean Type (C99+)
```c
#include <stdbool.h>
bool is_student = true;
bool is_working = false;
```

### Variable Declaration and Initialization

```c
// Declaration only
int age;
char name[50];

// Declaration with initialization
int height = 180;
float weight = 75.5f;
char grade = 'A';

// Multiple variables of same type
int x, y, z;
int a = 10, b = 20, c = 30;
```

### Constants

```c
// Using const keyword
const int MAX_SIZE = 100;
const float PI = 3.14159f;

// Using #define preprocessor directive
#define MAX_STUDENTS 50
#define COMPANY_NAME "TechCorp"

// Enumeration constants
enum Days { MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY };
enum Days today = MONDAY;
```

## Input and Output

### Printf Function

`printf` is used for formatted output:

```c
#include <stdio.h>

int main() {
    int age = 25;
    char name[] = "John";
    float height = 5.9f;
    
    // Basic formatting
    printf("Hello, World!\n");
    
    // String formatting
    printf("My name is %s\n", name);
    
    // Integer formatting
    printf("I am %d years old\n", age);
    
    // Float formatting
    printf("My height is %.1f feet\n", height);
    
    // Multiple values
    printf("Name: %s, Age: %d, Height: %.1f\n", name, age, height);
    
    return 0;
}
```

### Common Format Specifiers

| Specifier | Type | Example |
|-----------|------|---------|
| `%d` | int | `printf("%d", 42)` |
| `%f` | float/double | `printf("%.2f", 3.14)` |
| `%c` | char | `printf("%c", 'A')` |
| `%s` | string | `printf("%s", "Hello")` |
| `%x` | hexadecimal | `printf("%x", 255)` |
| `%o` | octal | `printf("%o", 64)` |
| `%p` | pointer | `printf("%p", &variable)` |

### Scanf Function

`scanf` is used for formatted input:

```c
#include <stdio.h>

int main() {
    int age;
    char name[50];
    float height;
    
    printf("Enter your name: ");
    scanf("%s", name);  // Note: stops at whitespace
    
    printf("Enter your age: ");
    scanf("%d", &age);  // Note: & is required for non-array variables
    
    printf("Enter your height: ");
    scanf("%f", &height);
    
    printf("Hello %s! You are %d years old and %.1f feet tall.\n", 
           name, age, height);
    
    return 0;
}
```

### Alternative Input Functions

```c
// fgets for reading entire lines (including spaces)
char line[100];
printf("Enter a line: ");
fgets(line, sizeof(line), stdin);

// getchar for single character input
char ch = getchar();

// putchar for single character output
putchar('A');
```

## Operators and Expressions

### Arithmetic Operators

```c
int a = 10, b = 3;

int sum = a + b;        // Addition: 13
int diff = a - b;       // Subtraction: 7
int product = a * b;    // Multiplication: 30
int quotient = a / b;   // Division: 3
int remainder = a % b;  // Modulus: 1

// Increment and decrement
int x = 5;
x++;        // Post-increment: x is now 6
++x;        // Pre-increment: x is now 7
x--;        // Post-decrement: x is now 6
--x;        // Pre-decrement: x is now 5
```

### Comparison Operators

```c
int a = 10, b = 5;

a == b;  // Equal to: false
a != b;  // Not equal to: true
a < b;   // Less than: false
a > b;   // Greater than: true
a <= b;  // Less than or equal: false
a >= b;  // Greater than or equal: true
```

### Logical Operators

```c
bool x = true, y = false;

x && y;  // Logical AND: false
x || y;  // Logical OR: true
!x;      // Logical NOT: false
```

### Assignment Operators

```c
int x = 10;

x += 5;   // Equivalent to x = x + 5
x -= 3;   // Equivalent to x = x - 3
x *= 2;   // Equivalent to x = x * 2
x /= 4;   // Equivalent to x = x / 4
x %= 3;   // Equivalent to x = x % 3
```

### Bitwise Operators

```c
int a = 12;  // Binary: 1100
int b = 10;  // Binary: 1010

a & b;   // Bitwise AND: 1000 (8)
a | b;   // Bitwise OR: 1110 (14)
a ^ b;   // Bitwise XOR: 0110 (6)
~a;      // Bitwise NOT: ...11110011
a << 2;  // Left shift: 110000 (48)
a >> 1;  // Right shift: 0110 (6)
```

### Operator Precedence

Operators have different precedence levels. Use parentheses to clarify:

```c
int result = 2 + 3 * 4;     // Result: 14 (multiplication first)
int result2 = (2 + 3) * 4;  // Result: 20 (addition first)
```

## Control Flow

### If-Else Statements

```c
int age = 20;

if (age >= 18) {
    printf("You are an adult.\n");
} else if (age >= 13) {
    printf("You are a teenager.\n");
} else {
    printf("You are a child.\n");
}

// Ternary operator
int max = (a > b) ? a : b;
```

### Switch Statements

```c
char grade = 'B';

switch (grade) {
    case 'A':
        printf("Excellent!\n");
        break;
    case 'B':
        printf("Good!\n");
        break;
    case 'C':
        printf("Average\n");
        break;
    case 'D':
        printf("Below average\n");
        break;
    case 'F':
        printf("Failed\n");
        break;
    default:
        printf("Invalid grade\n");
        break;
}
```

### For Loops

```c
// Basic for loop
for (int i = 0; i < 10; i++) {
    printf("%d ", i);
}
printf("\n");

// Loop with different increment
for (int i = 10; i > 0; i--) {
    printf("%d ", i);
}
printf("\n");

// Multiple variables
for (int i = 0, j = 10; i < j; i++, j--) {
    printf("i=%d, j=%d\n", i, j);
}
```

### While Loops

```c
int count = 0;
while (count < 5) {
    printf("Count: %d\n", count);
    count++;
}

// Input validation loop
int number;
printf("Enter a positive number: ");
scanf("%d", &number);
while (number <= 0) {
    printf("Invalid input. Enter a positive number: ");
    scanf("%d", &number);
}
```

### Do-While Loops

```c
int choice;
do {
    printf("Enter 1 to continue, 0 to exit: ");
    scanf("%d", &choice);
    if (choice == 1) {
        printf("Continuing...\n");
    }
} while (choice != 0);
```

### Break and Continue

```c
// Break example
for (int i = 0; i < 10; i++) {
    if (i == 5) {
        break;  // Exit the loop
    }
    printf("%d ", i);
}

// Continue example
for (int i = 0; i < 10; i++) {
    if (i % 2 == 0) {
        continue;  // Skip this iteration
    }
    printf("%d ", i);  // Only odd numbers
}
```

## Functions

### Function Declaration and Definition

```c
#include <stdio.h>

// Function declaration (prototype)
int add(int a, int b);
void print_hello(void);
int factorial(int n);

int main() {
    int result = add(5, 3);
    printf("Sum: %d\n", result);
    
    print_hello();
    
    int fact = factorial(5);
    printf("5! = %d\n", fact);
    
    return 0;
}

// Function definition
int add(int a, int b) {
    return a + b;
}

void print_hello(void) {
    printf("Hello, World!\n");
}

int factorial(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n - 1);
}
```

### Function Parameters

```c
// Pass by value (default)
void modify_value(int x) {
    x = 100;  // Doesn't affect the original variable
}

// Pass by reference (using pointers)
void modify_pointer(int *x) {
    *x = 100;  // Modifies the original variable
}

// Array parameter
void print_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// String parameter
void print_string(char str[]) {
    printf("String: %s\n", str);
}
```

### Function Return Types

```c
// Returns integer
int get_max(int a, int b) {
    return (a > b) ? a : b;
}

// Returns float
float calculate_average(float a, float b) {
    return (a + b) / 2.0f;
}

// Returns character
char get_grade(int score) {
    if (score >= 90) return 'A';
    if (score >= 80) return 'B';
    if (score >= 70) return 'C';
    return 'F';
}

// No return value
void display_menu(void) {
    printf("1. Add\n");
    printf("2. Subtract\n");
    printf("3. Multiply\n");
    printf("4. Divide\n");
}
```

## Variable Scope and Storage Classes

### Local vs Global Variables

```c
#include <stdio.h>

int global_var = 100;  // Global variable

void function1(void) {
    int local_var = 10;  // Local variable
    printf("Global: %d, Local: %d\n", global_var, local_var);
}

void function2(void) {
    int local_var = 20;  // Different local variable
    printf("Global: %d, Local: %d\n", global_var, local_var);
}

int main() {
    int local_var = 5;  // Local to main
    printf("Global: %d, Local: %d\n", global_var, local_var);
    
    function1();
    function2();
    
    return 0;
}
```

### Storage Classes

```c
// Automatic (default for local variables)
void function1(void) {
    auto int x = 10;  // Same as: int x = 10;
}

// Static (retains value between function calls)
void function2(void) {
    static int count = 0;
    count++;
    printf("Function called %d times\n", count);
}

// Register (hint to store in CPU register)
void function3(void) {
    register int i;
    for (i = 0; i < 1000; i++) {
        // Fast loop variable
    }
}

// External (declared elsewhere)
extern int external_var;  // Defined in another file
```

## Exercises

### Exercise 1: Calculator Program
Write a program that:
1. Asks the user for two numbers
2. Asks the user for an operation (+, -, *, /)
3. Performs the operation and displays the result
4. Handles division by zero

### Exercise 2: Grade Calculator
Write a program that:
1. Asks for student name and three test scores
2. Calculates the average
3. Determines the letter grade (A: 90+, B: 80+, C: 70+, F: <70)
4. Displays the results in a formatted way

### Exercise 3: Number Guessing Game
Write a program that:
1. Generates a random number between 1 and 100
2. Asks the user to guess the number
3. Provides hints (too high/too low)
4. Counts the number of guesses
5. Congratulates when correct

### Exercise 4: Fibonacci Sequence
Write a function that calculates the nth Fibonacci number and a program that:
1. Asks the user for a number n
2. Calculates and displays the first n Fibonacci numbers
3. Uses a function to calculate each number

### Exercise 5: Prime Number Checker
Write a program that:
1. Asks the user for a number
2. Checks if it's prime
3. Displays the result
4. Use a function for the prime check

### Exercise 6: Simple Menu System
Create a program with a menu that allows the user to:
1. Add two numbers
2. Subtract two numbers
3. Multiply two numbers
4. Divide two numbers
5. Exit

Use functions for each operation and a loop to keep the menu running.

## 🎯 Module Summary

In this module, you learned:
- ✅ Different data types and how to use them
- ✅ Input and output operations with printf and scanf
- ✅ Various operators and their precedence
- ✅ Control flow structures (if, switch, loops)
- ✅ How to write and call functions
- ✅ Variable scope and storage classes

## 🚀 What's Next?

You're ready to move on to **Module 3: Advanced C Concepts**, where you'll learn about:
- Arrays and strings
- Pointers and memory addresses
- Structures and unions
- Function pointers
- Preprocessor directives

## 📚 Additional Reading

- [C Data Types](https://en.cppreference.com/w/c/language/types) - Comprehensive data type reference
- [C Operators](https://en.cppreference.com/w/c/language/operator_precedence) - Operator precedence table
- [C Functions](https://en.cppreference.com/w/c/language/functions) - Function syntax and usage

---

**Great job completing Module 2! 🎉**

*Next: [Module 3: Advanced C Concepts](../module-03-advanced-concepts/README.md)*

