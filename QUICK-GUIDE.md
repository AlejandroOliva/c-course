# ⚡ C Programming Quick Reference Guide

A comprehensive cheat sheet for C programming syntax, functions, and commands.

## 🔧 Compilation Commands

```bash
# Basic compilation
gcc program.c -o program

# Compile with debugging info
gcc -g program.c -o program

# Compile with all warnings
gcc -Wall -Wextra program.c -o program

# Compile with optimizations
gcc -O2 program.c -o program

# Compile multiple files
gcc file1.c file2.c -o program

# Create object file
gcc -c program.c -o program.o

# Link object files
gcc file1.o file2.o -o program

# Compile with math library
gcc program.c -o program -lm

# Compile with specific standard
gcc -std=c99 program.c -o program
```

## 📝 Basic Syntax

### Program Structure
```c
#include <stdio.h>  // Standard I/O library
#include <stdlib.h> // Standard library

int main() {
    // Your code here
    return 0;  // Successful execution
}
```

### Data Types
```c
// Integer types
int age = 25;           // 4 bytes, -2^31 to 2^31-1
short small = 100;      // 2 bytes
long big = 1000000L;    // 8 bytes
long long huge = 1000000000LL;

// Character
char letter = 'A';      // 1 byte

// Floating point
float price = 19.99f;   // 4 bytes
double precise = 3.14159; // 8 bytes

// Boolean (C99+)
bool flag = true;       // Need #include <stdbool.h>

// Unsigned versions
unsigned int count = 100;
unsigned char byte = 255;
```

### Constants and Literals
```c
// Integer literals
int decimal = 42;
int octal = 052;        // Leading 0
int hex = 0x2A;         // Leading 0x
int binary = 0b101010;  // C23+ or GCC extension

// Floating point literals
float f1 = 3.14f;
double d1 = 3.14;
double scientific = 1.23e-4;

// Character literals
char ch1 = 'A';
char escape = '\n';     // Newline
char tab = '\t';        // Tab
char backslash = '\\';  // Backslash
```

### Variables and Scope
```c
// Global variables
int global_var = 10;

int main() {
    // Local variables
    int local_var = 20;
    
    // Block scope
    {
        int block_var = 30;
    }
    // block_var not accessible here
    
    return 0;
}
```

## 🔄 Control Flow

### Conditional Statements
```c
// if-else
if (age >= 18) {
    printf("Adult\n");
} else if (age >= 13) {
    printf("Teenager\n");
} else {
    printf("Child\n");
}

// Ternary operator
int max = (a > b) ? a : b;

// switch statement
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
    default:
        printf("Failed\n");
        break;
}
```

### Loops
```c
// for loop
for (int i = 0; i < 10; i++) {
    printf("%d\n", i);
}

// while loop
int i = 0;
while (i < 10) {
    printf("%d\n", i);
    i++;
}

// do-while loop
int i = 0;
do {
    printf("%d\n", i);
    i++;
} while (i < 10);

// break and continue
for (int i = 0; i < 10; i++) {
    if (i == 3) continue;  // Skip iteration
    if (i == 7) break;     // Exit loop
    printf("%d\n", i);
}
```

## 🎯 Functions

### Function Declaration and Definition
```c
// Function declaration (prototype)
int add(int a, int b);
void print_hello(void);

// Function definition
int add(int a, int b) {
    return a + b;
}

void print_hello(void) {
    printf("Hello, World!\n");
}

// Function call
int result = add(5, 3);
print_hello();
```

### Function Parameters
```c
// Pass by value
void modify_value(int x) {
    x = 100;  // Doesn't affect original
}

// Pass by reference (pointer)
void modify_pointer(int *x) {
    *x = 100;  // Modifies original
}

// Array parameter
void print_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
}
```

## 📊 Arrays and Strings

### Arrays
```c
// Array declaration and initialization
int numbers[5] = {1, 2, 3, 4, 5};
int matrix[3][4];  // 2D array

// Array access
numbers[0] = 10;
int value = numbers[2];

// Array size
int size = sizeof(numbers) / sizeof(numbers[0]);
```

### Strings
```c
// String declaration
char name[50] = "John Doe";
char *greeting = "Hello";

// String functions
#include <string.h>

strlen(name);           // Length
strcpy(dest, src);      // Copy
strcat(dest, src);      // Concatenate
strcmp(str1, str2);     // Compare

// String input/output
printf("Name: %s\n", name);
scanf("%s", name);      // No spaces
fgets(name, 50, stdin); // With spaces
```

## 🎯 Pointers

### Pointer Basics
```c
int x = 42;
int *ptr = &x;        // Pointer to x

printf("Value: %d\n", x);      // 42
printf("Address: %p\n", &x);   // Memory address
printf("Pointer value: %d\n", *ptr);  // 42

// Pointer arithmetic
int arr[] = {1, 2, 3, 4, 5};
int *p = arr;
printf("%d\n", *p);      // 1
printf("%d\n", *(p+1));  // 2
```

### Dynamic Memory
```c
#include <stdlib.h>

// Allocate memory
int *numbers = malloc(5 * sizeof(int));
int *array = calloc(5, sizeof(int));  // Initialized to 0

// Reallocate memory
numbers = realloc(numbers, 10 * sizeof(int));

// Free memory
free(numbers);
numbers = NULL;  // Good practice
```

## 🏗️ Structures

### Structure Definition and Usage
```c
// Structure definition
struct Person {
    char name[50];
    int age;
    float height;
};

// Typedef for convenience
typedef struct {
    int x, y;
} Point;

// Structure usage
struct Person john;
john.age = 25;
strcpy(john.name, "John");

// Structure pointer
struct Person *ptr = &john;
ptr->age = 26;  // Equivalent to (*ptr).age
```

### Union
```c
union Data {
    int i;
    float f;
    char str[20];
};

union Data data;
data.i = 10;
printf("%d\n", data.i);
```

## 📁 File I/O

### File Operations
```c
#include <stdio.h>

// Open file
FILE *file = fopen("data.txt", "r");
if (file == NULL) {
    perror("Error opening file");
    return 1;
}

// Read from file
char buffer[100];
fgets(buffer, 100, file);

// Write to file
fprintf(file, "Hello, World!\n");
fputc('A', file);

// Close file
fclose(file);
```

### File Modes
```c
"r"   // Read
"w"   // Write (overwrite)
"a"   // Append
"r+"  // Read and write
"w+"  // Write and read (overwrite)
"a+"  // Append and read
```

## 🛠️ Common Library Functions

### stdio.h
```c
printf("Hello %s, age %d\n", name, age);
scanf("%d", &number);
fprintf(stderr, "Error message\n");
sprintf(buffer, "Formatted string");
```

### stdlib.h
```c
int random = rand();           // Random number
int number = atoi("123");      // String to int
double value = atof("3.14");   // String to double
exit(0);                       // Exit program
```

### string.h
```c
strlen(str);                   // String length
strcpy(dest, src);            // Copy string
strncpy(dest, src, n);        // Copy n characters
strcat(dest, src);            // Concatenate
strncat(dest, src, n);        // Concatenate n characters
strcmp(str1, str2);           // Compare strings
strncmp(str1, str2, n);       // Compare n characters
strchr(str, ch);              // Find character
strstr(str, substr);          // Find substring
```

### ctype.h
```c
isalpha(ch);                  // Is alphabetic
isdigit(ch);                  // Is digit
isalnum(ch);                  // Is alphanumeric
islower(ch);                  // Is lowercase
isupper(ch);                  // Is uppercase
tolower(ch);                  // To lowercase
toupper(ch);                  // To uppercase
```

## 🐛 Debugging

### GDB Commands
```bash
gdb ./program

# Inside GDB:
(gdb) break main              # Set breakpoint
(gdb) run                     # Start program
(gdb) step                    # Step into function
(gdb) next                    # Step over function
(gdb) print variable          # Print variable value
(gdb) backtrace               # Show call stack
(gdb) quit                    # Exit GDB
```

### Debugging Tips
```c
// Use printf for debugging
printf("Debug: value = %d\n", value);

// Use assert for assumptions
#include <assert.h>
assert(ptr != NULL);

// Check return values
if (fopen("file.txt", "r") == NULL) {
    perror("fopen failed");
    exit(1);
}
```

## 📋 Format Specifiers

```c
// printf/scanf format specifiers
%d, %i     // int
%u          // unsigned int
%o          // octal
%x, %X      // hexadecimal
%c          // char
%s          // string
%f          // float/double
%e, %E      // scientific notation
%g, %G      // shortest representation
%p          // pointer address
%ld         // long
%lld        // long long
%lu         // unsigned long
%zu         // size_t
```

## ⚠️ Common Mistakes

```c
// Wrong
int x;
printf("%d\n", x);  // Uninitialized variable

// Correct
int x = 0;
printf("%d\n", x);

// Wrong
int arr[5];
arr[5] = 10;  // Out of bounds

// Correct
int arr[5];
arr[4] = 10;  // Valid index (0-4)

// Wrong
char *str = "Hello";
str[0] = 'h';  // Modifying string literal

// Correct
char str[] = "Hello";
str[0] = 'h';  // Modifying array
```

## 🔍 Memory Management Best Practices

```c
// Always check malloc return
int *ptr = malloc(sizeof(int));
if (ptr == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(1);
}

// Free memory and set pointer to NULL
free(ptr);
ptr = NULL;

// Use calloc for initialized memory
int *arr = calloc(10, sizeof(int));

// Check realloc return
int *new_ptr = realloc(ptr, 20 * sizeof(int));
if (new_ptr == NULL) {
    free(ptr);  // Clean up original
    exit(1);
}
ptr = new_ptr;
```

---

*Keep this guide handy while learning C! 📚*

