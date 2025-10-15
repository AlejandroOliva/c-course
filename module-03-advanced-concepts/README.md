# Module 3: Advanced C Concepts

Welcome to Module 3! This module covers some of the most powerful and important features of C programming: arrays, strings, pointers, structures, and function pointers. These concepts are crucial for understanding how C works at a deeper level.

## 🎯 Learning Objectives

By the end of this module, you will be able to:
- Work with arrays and multidimensional arrays
- Manipulate strings using both arrays and library functions
- Understand and use pointers effectively
- Create and work with structures and unions
- Use function pointers for advanced programming techniques
- Apply preprocessor directives effectively

## 📚 Topics Covered

1. [Arrays](#arrays)
2. [Strings](#strings)
3. [Pointers](#pointers)
4. [Structures and Unions](#structures-and-unions)
5. [Function Pointers](#function-pointers)
6. [Preprocessor Directives](#preprocessor-directives)
7. [Exercises](#exercises)

---

## Arrays

### One-Dimensional Arrays

Arrays are collections of elements of the same type:

```c
#include <stdio.h>

int main() {
    // Array declaration and initialization
    int numbers[5] = {1, 2, 3, 4, 5};
    int scores[3];  // Declaration without initialization
    
    // Accessing array elements
    scores[0] = 85;
    scores[1] = 92;
    scores[2] = 78;
    
    // Displaying array elements
    for (int i = 0; i < 5; i++) {
        printf("numbers[%d] = %d\n", i, numbers[i]);
    }
    
    // Array size calculation
    int size = sizeof(numbers) / sizeof(numbers[0]);
    printf("Array size: %d\n", size);
    
    return 0;
}
```

### Multidimensional Arrays

```c
#include <stdio.h>

int main() {
    // 2D array (matrix)
    int matrix[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    
    // Accessing 2D array elements
    printf("matrix[1][2] = %d\n", matrix[1][2]);  // Output: 7
    
    // Displaying 2D array
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%3d ", matrix[i][j]);
        }
        printf("\n");
    }
    
    // 3D array
    int cube[2][3][4];  // 2x3x4 array
    
    return 0;
}
```

### Array as Function Parameters

```c
#include <stdio.h>

// Function to print array
void print_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Function to find maximum element
int find_max(int arr[], int size) {
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

// Function to reverse array
void reverse_array(int arr[], int size) {
    int start = 0;
    int end = size - 1;
    
    while (start < end) {
        // Swap elements
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        
        start++;
        end--;
    }
}

int main() {
    int numbers[] = {10, 20, 30, 40, 50};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    
    printf("Original array: ");
    print_array(numbers, size);
    
    printf("Maximum element: %d\n", find_max(numbers, size));
    
    reverse_array(numbers, size);
    printf("Reversed array: ");
    print_array(numbers, size);
    
    return 0;
}
```

## Strings

### String as Character Arrays

In C, strings are arrays of characters terminated by a null character (`\0`):

```c
#include <stdio.h>

int main() {
    // String declaration methods
    char str1[] = "Hello, World!";  // Automatic size calculation
    char str2[20] = "Hello";        // Fixed size
    char str3[50];                  // Declaration only
    
    // String initialization
    str3[0] = 'H';
    str3[1] = 'i';
    str3[2] = '\0';  // Null terminator is crucial!
    
    printf("String 1: %s\n", str1);
    printf("String 2: %s\n", str2);
    printf("String 3: %s\n", str3);
    
    // String length (manual calculation)
    int len = 0;
    while (str1[len] != '\0') {
        len++;
    }
    printf("Length of str1: %d\n", len);
    
    return 0;
}
```

### String Library Functions

```c
#include <stdio.h>
#include <string.h>  // String functions library

int main() {
    char str1[50] = "Hello";
    char str2[50] = "World";
    char str3[50];
    
    // String length
    printf("Length of str1: %zu\n", strlen(str1));
    
    // String copy
    strcpy(str3, str1);
    printf("Copied string: %s\n", str3);
    
    // String concatenation
    strcat(str1, " ");
    strcat(str1, str2);
    printf("Concatenated: %s\n", str1);
    
    // String comparison
    if (strcmp(str1, "Hello World") == 0) {
        printf("Strings are equal\n");
    } else {
        printf("Strings are not equal\n");
    }
    
    // String copy with length limit
    char dest[10];
    strncpy(dest, "Hello World", 9);
    dest[9] = '\0';  // Ensure null termination
    printf("Limited copy: %s\n", dest);
    
    return 0;
}
```

### Common String Operations

```c
#include <stdio.h>
#include <string.h>
#include <ctype.h>  // Character functions

// Custom string functions
int string_length(char str[]) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

void string_reverse(char str[]) {
    int len = strlen(str);
    int start = 0;
    int end = len - 1;
    
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

int string_compare(char str1[], char str2[]) {
    int i = 0;
    while (str1[i] == str2[i]) {
        if (str1[i] == '\0') {
            return 0;  // Strings are equal
        }
        i++;
    }
    return str1[i] - str2[i];
}

int main() {
    char text[] = "Programming";
    
    printf("Original: %s\n", text);
    printf("Length: %d\n", string_length(text));
    
    string_reverse(text);
    printf("Reversed: %s\n", text);
    
    // Character manipulation
    char name[] = "john doe";
    for (int i = 0; name[i] != '\0'; i++) {
        if (i == 0 || name[i-1] == ' ') {
            name[i] = toupper(name[i]);  // Capitalize first letters
        }
    }
    printf("Capitalized: %s\n", name);
    
    return 0;
}
```

## Pointers

Pointers are variables that store memory addresses. They are one of C's most powerful features:

### Pointer Basics

```c
#include <stdio.h>

int main() {
    int num = 42;
    int *ptr;  // Pointer declaration
    
    ptr = &num;  // Assign address of num to ptr
    
    printf("Value of num: %d\n", num);
    printf("Address of num: %p\n", &num);
    printf("Value of ptr: %p\n", ptr);
    printf("Value pointed to by ptr: %d\n", *ptr);
    
    // Modifying value through pointer
    *ptr = 100;
    printf("New value of num: %d\n", num);
    
    return 0;
}
```

### Pointer Arithmetic

```c
#include <stdio.h>

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int *ptr = arr;  // Points to first element
    
    printf("Array elements using pointer arithmetic:\n");
    for (int i = 0; i < 5; i++) {
        printf("arr[%d] = %d (address: %p)\n", i, *(ptr + i), ptr + i);
    }
    
    // Different ways to access array elements
    printf("\nDifferent access methods:\n");
    printf("arr[2] = %d\n", arr[2]);
    printf("*(arr + 2) = %d\n", *(arr + 2));
    printf("ptr[2] = %d\n", ptr[2]);
    printf("*(ptr + 2) = %d\n", *(ptr + 2));
    
    return 0;
}
```

### Pointers and Functions

```c
#include <stdio.h>

// Function that modifies value through pointer
void modify_value(int *ptr) {
    *ptr = *ptr * 2;
}

// Function that returns pointer
int* find_max(int arr[], int size) {
    int *max_ptr = &arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > *max_ptr) {
            max_ptr = &arr[i];
        }
    }
    return max_ptr;
}

// Function with array parameter (arrays decay to pointers)
void print_array_with_pointer(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int num = 10;
    printf("Before modification: %d\n", num);
    modify_value(&num);
    printf("After modification: %d\n", num);
    
    int numbers[] = {5, 2, 8, 1, 9};
    int *max_ptr = find_max(numbers, 5);
    printf("Maximum element: %d at address %p\n", *max_ptr, max_ptr);
    
    print_array_with_pointer(numbers, 5);
    
    return 0;
}
```

### Pointers to Pointers

```c
#include <stdio.h>

int main() {
    int num = 42;
    int *ptr1 = &num;
    int **ptr2 = &ptr1;  // Pointer to pointer
    
    printf("num = %d\n", num);
    printf("*ptr1 = %d\n", *ptr1);
    printf("**ptr2 = %d\n", **ptr2);
    
    printf("Address of num: %p\n", &num);
    printf("Value of ptr1: %p\n", ptr1);
    printf("Address of ptr1: %p\n", &ptr1);
    printf("Value of ptr2: %p\n", ptr2);
    
    return 0;
}
```

## Structures and Unions

### Structures

Structures allow you to group related data together:

```c
#include <stdio.h>
#include <string.h>

// Structure definition
struct Student {
    char name[50];
    int age;
    float gpa;
    char grade;
};

// Structure with typedef
typedef struct {
    char title[100];
    char author[50];
    int pages;
    float price;
} Book;

// Function to print student information
void print_student(struct Student s) {
    printf("Name: %s\n", s.name);
    printf("Age: %d\n", s.age);
    printf("GPA: %.2f\n", s.gpa);
    printf("Grade: %c\n", s.grade);
}

// Function to print student using pointer
void print_student_ptr(struct Student *s) {
    printf("Name: %s\n", s->name);
    printf("Age: %d\n", s->age);
    printf("GPA: %.2f\n", s->gpa);
    printf("Grade: %c\n", s->grade);
}

int main() {
    // Structure initialization
    struct Student student1 = {"John Doe", 20, 3.8f, 'A'};
    
    // Structure assignment
    struct Student student2;
    strcpy(student2.name, "Jane Smith");
    student2.age = 19;
    student2.gpa = 3.9f;
    student2.grade = 'A';
    
    // Book using typedef
    Book book1 = {"The C Programming Language", "K&R", 272, 45.99f};
    
    printf("Student 1:\n");
    print_student(student1);
    
    printf("\nStudent 2:\n");
    print_student_ptr(&student2);
    
    printf("\nBook: %s by %s\n", book1.title, book1.author);
    
    return 0;
}
```

### Nested Structures

```c
#include <stdio.h>

struct Date {
    int day;
    int month;
    int year;
};

struct Person {
    char name[50];
    struct Date birth_date;
    struct Date hire_date;
    float salary;
};

void print_person(struct Person p) {
    printf("Name: %s\n", p.name);
    printf("Birth Date: %d/%d/%d\n", 
           p.birth_date.day, p.birth_date.month, p.birth_date.year);
    printf("Hire Date: %d/%d/%d\n", 
           p.hire_date.day, p.hire_date.month, p.hire_date.year);
    printf("Salary: $%.2f\n", p.salary);
}

int main() {
    struct Person employee = {
        "Alice Johnson",
        {15, 6, 1990},  // Birth date
        {1, 3, 2020},   // Hire date
        75000.00f
    };
    
    print_person(employee);
    
    return 0;
}
```

### Unions

Unions allow different data types to share the same memory space:

```c
#include <stdio.h>

union Data {
    int integer;
    float floating;
    char string[20];
};

int main() {
    union Data data;
    
    // Using as integer
    data.integer = 42;
    printf("Integer: %d\n", data.integer);
    
    // Using as float (overwrites integer)
    data.floating = 3.14f;
    printf("Float: %.2f\n", data.floating);
    printf("Integer after float: %d\n", data.integer);  // Garbage value
    
    // Using as string
    strcpy(data.string, "Hello");
    printf("String: %s\n", data.string);
    
    // Size of union
    printf("Size of union: %zu bytes\n", sizeof(union Data));
    
    return 0;
}
```

## Function Pointers

Function pointers allow you to store and call functions dynamically:

```c
#include <stdio.h>

// Function prototypes
int add(int a, int b);
int subtract(int a, int b);
int multiply(int a, int b);
int divide(int a, int b);

// Function that takes a function pointer
int calculate(int a, int b, int (*operation)(int, int)) {
    return operation(a, b);
}

int main() {
    int x = 10, y = 5;
    
    // Function pointer declaration
    int (*operation_ptr)(int, int);
    
    // Assign function to pointer
    operation_ptr = add;
    printf("Addition: %d\n", calculate(x, y, operation_ptr));
    
    operation_ptr = subtract;
    printf("Subtraction: %d\n", calculate(x, y, operation_ptr));
    
    operation_ptr = multiply;
    printf("Multiplication: %d\n", calculate(x, y, operation_ptr));
    
    operation_ptr = divide;
    printf("Division: %d\n", calculate(x, y, operation_ptr));
    
    // Array of function pointers
    int (*operations[])(int, int) = {add, subtract, multiply, divide};
    char* operation_names[] = {"Add", "Subtract", "Multiply", "Divide"};
    
    printf("\nUsing function pointer array:\n");
    for (int i = 0; i < 4; i++) {
        printf("%s: %d\n", operation_names[i], operations[i](x, y));
    }
    
    return 0;
}

// Function definitions
int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

int multiply(int a, int b) {
    return a * b;
}

int divide(int a, int b) {
    if (b != 0) {
        return a / b;
    }
    return 0;
}
```

### Callback Functions

```c
#include <stdio.h>

// Function pointer type for comparison
typedef int (*compare_func)(int a, int b);

// Comparison functions
int ascending(int a, int b) {
    return a - b;
}

int descending(int a, int b) {
    return b - a;
}

// Bubble sort with function pointer
void bubble_sort(int arr[], int size, compare_func compare) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (compare(arr[j], arr[j + 1]) > 0) {
                // Swap elements
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void print_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int numbers[] = {64, 34, 25, 12, 22, 11, 90};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    
    printf("Original array: ");
    print_array(numbers, size);
    
    bubble_sort(numbers, size, ascending);
    printf("Ascending order: ");
    print_array(numbers, size);
    
    bubble_sort(numbers, size, descending);
    printf("Descending order: ");
    print_array(numbers, size);
    
    return 0;
}
```

## Preprocessor Directives

The preprocessor processes your code before compilation:

### #define and Macros

```c
#include <stdio.h>

// Simple macro
#define PI 3.14159
#define MAX_SIZE 100

// Function-like macro
#define SQUARE(x) ((x) * (x))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

// Multi-line macro
#define PRINT_DEBUG(msg) \
    printf("Debug: %s at line %d in %s\n", msg, __LINE__, __FILE__)

// Conditional compilation
#define DEBUG_MODE 1

int main() {
    double radius = 5.0;
    double area = PI * SQUARE(radius);
    
    printf("Area of circle: %.2f\n", area);
    printf("Maximum of 10 and 20: %d\n", MAX(10, 20));
    
    #ifdef DEBUG_MODE
        PRINT_DEBUG("Program started");
        printf("Radius: %.2f\n", radius);
    #endif
    
    return 0;
}
```

### #include and Header Guards

```c
// math_utils.h
#ifndef MATH_UTILS_H
#define MATH_UTILS_H

// Function declarations
double power(double base, int exponent);
int factorial(int n);
int is_prime(int n);

#endif

// math_utils.c
#include "math_utils.h"

double power(double base, int exponent) {
    double result = 1.0;
    for (int i = 0; i < exponent; i++) {
        result *= base;
    }
    return result;
}

int factorial(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

int is_prime(int n) {
    if (n <= 1) return 0;
    if (n <= 3) return 1;
    if (n % 2 == 0 || n % 3 == 0) return 0;
    
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return 0;
        }
    }
    return 1;
}
```

### Conditional Compilation

```c
#include <stdio.h>

#define VERSION 2

int main() {
    #if VERSION == 1
        printf("Running version 1\n");
    #elif VERSION == 2
        printf("Running version 2\n");
    #else
        printf("Unknown version\n");
    #endif
    
    #ifdef WINDOWS
        printf("Compiled for Windows\n");
    #elif defined(LINUX)
        printf("Compiled for Linux\n");
    #elif defined(MACOS)
        printf("Compiled for macOS\n");
    #else
        printf("Unknown platform\n");
    #endif
    
    return 0;
}
```

## Exercises

### Exercise 1: Array Operations
Create a program that:
1. Declares an array of 10 integers
2. Fills it with user input
3. Finds the maximum, minimum, and average
4. Reverses the array
5. Sorts the array in ascending order

### Exercise 2: String Manipulation
Write a program that:
1. Takes a string as input
2. Counts vowels, consonants, and spaces
3. Converts to uppercase and lowercase
4. Checks if it's a palindrome
5. Replaces all spaces with underscores

### Exercise 3: Pointer Operations
Create a program that:
1. Uses pointers to swap two numbers
2. Implements a function that returns multiple values using pointers
3. Uses pointer arithmetic to traverse an array
4. Demonstrates pointer to pointer usage

### Exercise 4: Student Management System
Design a program using structures that:
1. Stores student information (name, ID, grades)
2. Calculates average grade for each student
3. Finds the student with highest average
4. Displays all student information

### Exercise 5: Calculator with Function Pointers
Implement a calculator that:
1. Uses function pointers for operations
2. Has an array of function pointers
3. Uses a menu system to select operations
4. Handles errors gracefully

### Exercise 6: Dynamic Array Implementation
Create a simple dynamic array structure that:
1. Can grow and shrink as needed
2. Has functions for adding, removing, and accessing elements
3. Manages memory allocation and deallocation
4. Includes bounds checking

## 🎯 Module Summary

In this module, you learned:
- ✅ How to work with arrays and multidimensional arrays
- ✅ String manipulation using arrays and library functions
- ✅ Pointer operations and pointer arithmetic
- ✅ Structure and union definitions and usage
- ✅ Function pointers and their applications
- ✅ Preprocessor directives and macros

## 🚀 What's Next?

You're ready to move on to **Module 4: Memory Management**, where you'll learn about:
- Dynamic memory allocation
- Memory leaks and how to avoid them
- Stack vs heap memory
- Debugging memory issues
- Best practices for memory management

## 📚 Additional Reading

- [C Arrays](https://en.cppreference.com/w/c/language/array) - Array syntax and usage
- [C Pointers](https://en.cppreference.com/w/c/language/pointer) - Pointer operations
- [C Structures](https://en.cppreference.com/w/c/language/struct) - Structure definitions
- [C Preprocessor](https://en.cppreference.com/w/c/preprocessor) - Preprocessor directives

---

**Excellent work completing Module 3! 🎉**

*Next: [Module 4: Memory Management](../module-04-memory-management/README.md)*

