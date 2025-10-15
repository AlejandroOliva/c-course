# Module 4: Memory Management

Welcome to Module 4! This module covers one of the most critical aspects of C programming: memory management. Understanding how memory works in C is essential for writing efficient, safe, and robust programs. You'll learn about dynamic memory allocation, memory leaks, and best practices.

## 🎯 Learning Objectives

By the end of this module, you will be able to:
- Understand the difference between stack and heap memory
- Use dynamic memory allocation functions (malloc, calloc, realloc, free)
- Avoid memory leaks and dangling pointers
- Debug memory-related issues
- Apply best practices for memory management
- Use tools like Valgrind for memory debugging

## 📚 Topics Covered

1. [Memory Layout in C](#memory-layout-in-c)
2. [Dynamic Memory Allocation](#dynamic-memory-allocation)
3. [Memory Management Functions](#memory-management-functions)
4. [Common Memory Problems](#common-memory-problems)
5. [Memory Debugging Tools](#memory-debugging-tools)
6. [Best Practices](#best-practices)
7. [Exercises](#exercises)

---

## Memory Layout in C

Understanding how memory is organized in C programs is crucial for effective memory management.

### Memory Segments

A C program's memory is divided into several segments:

```c
#include <stdio.h>
#include <stdlib.h>

// Global variables (data segment)
int global_var = 100;
static int static_global = 200;

// Function declarations
void function_example(void);
void stack_example(void);
void heap_example(void);

int main() {
    // Local variables (stack)
    int local_var = 50;
    static int static_local = 75;  // Data segment
    
    printf("=== Memory Layout Example ===\n");
    printf("Global variable address: %p\n", &global_var);
    printf("Static global address: %p\n", &static_global);
    printf("Static local address: %p\n", &static_local);
    printf("Local variable address: %p\n", &local_var);
    printf("Function address: %p\n", &function_example);
    
    stack_example();
    heap_example();
    
    return 0;
}

void stack_example(void) {
    // Stack variables
    int stack_var = 10;
    char stack_array[100];
    
    printf("\nStack variables:\n");
    printf("stack_var address: %p\n", &stack_var);
    printf("stack_array address: %p\n", stack_array);
}

void heap_example(void) {
    // Heap allocation
    int *heap_ptr = malloc(sizeof(int));
    *heap_ptr = 42;
    
    printf("\nHeap allocation:\n");
    printf("heap_ptr value: %p\n", heap_ptr);
    printf("heap_ptr address: %p\n", &heap_ptr);
    printf("Dereferenced value: %d\n", *heap_ptr);
    
    free(heap_ptr);  // Important: free allocated memory
}
```

### Stack vs Heap Memory

| Aspect | Stack | Heap |
|--------|-------|------|
| **Size** | Limited (typically 1-8 MB) | Large (limited by system RAM) |
| **Speed** | Very fast | Slower (requires system calls) |
| **Management** | Automatic | Manual (malloc/free) |
| **Lifetime** | Function scope | Until explicitly freed |
| **Fragmentation** | No fragmentation | Can become fragmented |
| **Thread Safety** | Thread-local | Shared across threads |

## Dynamic Memory Allocation

Dynamic memory allocation allows programs to request memory at runtime.

### Basic Memory Allocation

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    // Allocate memory for a single integer
    int *ptr = malloc(sizeof(int));
    
    if (ptr == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    
    *ptr = 42;
    printf("Allocated integer: %d\n", *ptr);
    printf("Address: %p\n", ptr);
    
    // Free the allocated memory
    free(ptr);
    ptr = NULL;  // Good practice: set pointer to NULL after freeing
    
    return 0;
}
```

### Array Allocation

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int size;
    
    printf("Enter array size: ");
    scanf("%d", &size);
    
    // Allocate memory for an array
    int *arr = malloc(size * sizeof(int));
    
    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    
    // Initialize array
    for (int i = 0; i < size; i++) {
        arr[i] = i * i;  // Square of index
    }
    
    // Display array
    printf("Array contents:\n");
    for (int i = 0; i < size; i++) {
        printf("arr[%d] = %d\n", i, arr[i]);
    }
    
    // Free allocated memory
    free(arr);
    arr = NULL;
    
    return 0;
}
```

### 2D Array Allocation

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int rows, cols;
    
    printf("Enter number of rows: ");
    scanf("%d", &rows);
    printf("Enter number of columns: ");
    scanf("%d", &cols);
    
    // Method 1: Single malloc with pointer arithmetic
    int **matrix = malloc(rows * sizeof(int*));
    if (matrix == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    
    for (int i = 0; i < rows; i++) {
        matrix[i] = malloc(cols * sizeof(int));
        if (matrix[i] == NULL) {
            printf("Memory allocation failed for row %d!\n", i);
            // Free previously allocated memory
            for (int j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            return 1;
        }
    }
    
    // Initialize matrix
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = i * cols + j;
        }
    }
    
    // Display matrix
    printf("Matrix contents:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%3d ", matrix[i][j]);
        }
        printf("\n");
    }
    
    // Free memory
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
    
    return 0;
}
```

## Memory Management Functions

### malloc, calloc, realloc, and free

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // malloc: Allocates uninitialized memory
    int *ptr1 = malloc(5 * sizeof(int));
    if (ptr1 == NULL) {
        printf("malloc failed!\n");
        return 1;
    }
    
    // Initialize manually
    for (int i = 0; i < 5; i++) {
        ptr1[i] = i + 1;
    }
    
    printf("malloc array: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", ptr1[i]);
    }
    printf("\n");
    
    // calloc: Allocates and initializes memory to zero
    int *ptr2 = calloc(5, sizeof(int));
    if (ptr2 == NULL) {
        printf("calloc failed!\n");
        free(ptr1);
        return 1;
    }
    
    printf("calloc array (initialized to zero): ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", ptr2[i]);
    }
    printf("\n");
    
    // realloc: Resize allocated memory
    ptr1 = realloc(ptr1, 10 * sizeof(int));
    if (ptr1 == NULL) {
        printf("realloc failed!\n");
        free(ptr2);
        return 1;
    }
    
    // Initialize new elements
    for (int i = 5; i < 10; i++) {
        ptr1[i] = i + 1;
    }
    
    printf("realloc array (resized to 10): ");
    for (int i = 0; i < 10; i++) {
        printf("%d ", ptr1[i]);
    }
    printf("\n");
    
    // Free all allocated memory
    free(ptr1);
    free(ptr2);
    
    return 0;
}
```

### String Memory Management

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to create a copy of a string
char* string_copy(const char* source) {
    if (source == NULL) {
        return NULL;
    }
    
    size_t len = strlen(source);
    char* copy = malloc((len + 1) * sizeof(char));  // +1 for null terminator
    
    if (copy == NULL) {
        return NULL;
    }
    
    strcpy(copy, source);
    return copy;
}

// Function to concatenate two strings
char* string_concat(const char* str1, const char* str2) {
    if (str1 == NULL || str2 == NULL) {
        return NULL;
    }
    
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    char* result = malloc((len1 + len2 + 1) * sizeof(char));
    
    if (result == NULL) {
        return NULL;
    }
    
    strcpy(result, str1);
    strcat(result, str2);
    return result;
}

int main() {
    const char* original = "Hello, World!";
    
    // Create a copy
    char* copy = string_copy(original);
    if (copy != NULL) {
        printf("Original: %s\n", original);
        printf("Copy: %s\n", copy);
        printf("Address of original: %p\n", (void*)original);
        printf("Address of copy: %p\n", (void*)copy);
        
        // Modify copy
        strcpy(copy, "Modified copy!");
        printf("After modification:\n");
        printf("Original: %s\n", original);
        printf("Copy: %s\n", copy);
        
        free(copy);
    }
    
    // Concatenate strings
    char* combined = string_concat("Hello, ", "C Programming!");
    if (combined != NULL) {
        printf("Combined: %s\n", combined);
        free(combined);
    }
    
    return 0;
}
```

## Common Memory Problems

### Memory Leaks

Memory leaks occur when allocated memory is not freed:

```c
#include <stdio.h>
#include <stdlib.h>

// BAD: Memory leak example
void bad_function(void) {
    int *ptr = malloc(sizeof(int));
    *ptr = 42;
    printf("Value: %d\n", *ptr);
    // Forgot to call free(ptr) - MEMORY LEAK!
}

// GOOD: Proper memory management
void good_function(void) {
    int *ptr = malloc(sizeof(int));
    if (ptr == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    
    *ptr = 42;
    printf("Value: %d\n", *ptr);
    
    free(ptr);  // Properly free memory
    ptr = NULL; // Set pointer to NULL
}

// Memory leak in loop
void leaky_loop(void) {
    for (int i = 0; i < 1000; i++) {
        int *ptr = malloc(sizeof(int));
        *ptr = i;
        // Missing free(ptr) - 1000 memory leaks!
    }
}

// Fixed version
void fixed_loop(void) {
    for (int i = 0; i < 1000; i++) {
        int *ptr = malloc(sizeof(int));
        if (ptr != NULL) {
            *ptr = i;
            free(ptr);  // Free memory in each iteration
        }
    }
}

int main() {
    printf("Calling good function:\n");
    good_function();
    
    printf("\nCalling bad function (memory leak):\n");
    bad_function();
    
    return 0;
}
```

### Dangling Pointers

Dangling pointers point to freed memory:

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *ptr = malloc(sizeof(int));
    *ptr = 42;
    
    printf("Value before free: %d\n", *ptr);
    
    free(ptr);  // Memory is freed
    
    // DANGER: ptr is now a dangling pointer
    // printf("Value after free: %d\n", *ptr);  // Undefined behavior!
    
    // Solution: Set pointer to NULL after freeing
    ptr = NULL;
    
    // Now it's safe to check
    if (ptr != NULL) {
        printf("Value: %d\n", *ptr);
    } else {
        printf("Pointer is NULL (memory was freed)\n");
    }
    
    return 0;
}
```

### Double Free

Freeing the same memory twice:

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *ptr = malloc(sizeof(int));
    *ptr = 42;
    
    free(ptr);  // First free - OK
    
    // DANGER: Double free
    // free(ptr);  // Undefined behavior!
    
    // Solution: Set pointer to NULL after first free
    ptr = NULL;
    
    // Now second free is safe (free(NULL) is safe)
    free(ptr);  // This is safe
    
    return 0;
}
```

### Buffer Overflows

Accessing memory beyond allocated boundaries:

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    // Allocate memory for 5 integers
    int *arr = malloc(5 * sizeof(int));
    if (arr == NULL) {
        return 1;
    }
    
    // Initialize array
    for (int i = 0; i < 5; i++) {
        arr[i] = i + 1;
    }
    
    printf("Valid array elements:\n");
    for (int i = 0; i < 5; i++) {
        printf("arr[%d] = %d\n", i, arr[i]);
    }
    
    // DANGER: Buffer overflow
    // arr[5] = 100;  // Writing beyond allocated memory!
    // arr[10] = 200; // Even worse!
    
    // Safe approach: Check bounds
    int index = 5;
    if (index >= 0 && index < 5) {
        arr[index] = 100;
        printf("arr[%d] = %d\n", index, arr[index]);
    } else {
        printf("Index %d is out of bounds!\n", index);
    }
    
    free(arr);
    return 0;
}
```

## Memory Debugging Tools

### Using Valgrind

Valgrind is a powerful memory debugging tool:

```bash
# Install Valgrind (Ubuntu/Debian)
sudo apt install valgrind

# Compile with debugging information
gcc -g program.c -o program

# Run with Valgrind
valgrind --leak-check=full ./program

# More detailed output
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./program
```

### Example Valgrind Output

```c
// leak_example.c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *ptr = malloc(sizeof(int));
    *ptr = 42;
    printf("Value: %d\n", *ptr);
    // Intentionally not freeing memory to demonstrate leak
    
    return 0;
}
```

Compile and run with Valgrind:
```bash
gcc -g leak_example.c -o leak_example
valgrind --leak-check=full ./leak_example
```

### Using GDB for Memory Debugging

```c
// debug_example.c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *ptr = malloc(sizeof(int));
    *ptr = 42;
    
    printf("Before free: %d\n", *ptr);
    free(ptr);
    printf("After free: %d\n", *ptr);  // Bug: accessing freed memory
    
    return 0;
}
```

Debug with GDB:
```bash
gcc -g debug_example.c -o debug_example
gdb ./debug_example

# Inside GDB:
(gdb) break main
(gdb) run
(gdb) step
(gdb) print *ptr
(gdb) continue
```

## Best Practices

### 1. Always Check malloc Return Value

```c
int *ptr = malloc(sizeof(int));
if (ptr == NULL) {
    fprintf(stderr, "Memory allocation failed!\n");
    exit(EXIT_FAILURE);
}
```

### 2. Free Memory in the Right Order

```c
// For nested allocations, free in reverse order
int **matrix = malloc(rows * sizeof(int*));
for (int i = 0; i < rows; i++) {
    matrix[i] = malloc(cols * sizeof(int));
}

// Free in reverse order
for (int i = 0; i < rows; i++) {
    free(matrix[i]);
}
free(matrix);
```

### 3. Use Consistent Memory Management

```c
// Create a wrapper function for safe malloc
void* safe_malloc(size_t size) {
    void *ptr = malloc(size);
    if (ptr == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

// Use it consistently
int *arr = safe_malloc(10 * sizeof(int));
```

### 4. Initialize Memory

```c
// Use calloc for zero-initialized memory
int *arr = calloc(10, sizeof(int));

// Or manually initialize after malloc
int *arr = malloc(10 * sizeof(int));
memset(arr, 0, 10 * sizeof(int));
```

### 5. Set Pointers to NULL After Freeing

```c
free(ptr);
ptr = NULL;  // Prevents accidental access to freed memory
```

## Exercises

### Exercise 1: Dynamic Array Implementation
Create a dynamic array structure that can:
1. Grow and shrink as needed
2. Store integers
3. Have functions for adding, removing, and accessing elements
4. Handle memory allocation errors gracefully
5. Include bounds checking

### Exercise 2: String Builder
Implement a string builder that:
1. Dynamically grows as you append strings
2. Has functions for appending, inserting, and deleting
3. Manages memory efficiently
4. Provides a function to get the final string

### Exercise 3: Matrix Operations
Create a program that:
1. Dynamically allocates matrices of any size
2. Implements matrix addition, multiplication, and transpose
3. Handles memory allocation failures
4. Frees all memory properly

### Exercise 4: Memory Leak Detector
Write a simple program that:
1. Intentionally creates memory leaks
2. Uses Valgrind to detect them
3. Fixes the leaks and verifies with Valgrind

### Exercise 5: Linked List with Dynamic Memory
Implement a linked list that:
1. Uses dynamic memory allocation for nodes
2. Has functions for insertion, deletion, and traversal
3. Properly manages memory
4. Includes error handling

### Exercise 6: Memory Pool
Create a simple memory pool that:
1. Pre-allocates a large block of memory
2. Provides smaller chunks from the pool
3. Tracks allocated chunks
4. Allows freeing chunks back to the pool

## 🎯 Module Summary

In this module, you learned:
- ✅ How memory is organized in C programs
- ✅ Dynamic memory allocation with malloc, calloc, realloc
- ✅ Common memory problems and how to avoid them
- ✅ Memory debugging tools like Valgrind and GDB
- ✅ Best practices for memory management
- ✅ How to write memory-safe programs

## 🚀 What's Next?

You're ready to move on to **Module 5: File I/O and System Programming**, where you'll learn about:
- File operations and I/O
- Command line arguments
- Error handling
- Basic system calls
- Building command-line utilities

## 📚 Additional Reading

- [C Memory Management](https://en.cppreference.com/w/c/memory) - Standard memory functions
- [Valgrind Documentation](https://valgrind.org/docs/manual/manual.html) - Memory debugging tool
- [GDB Documentation](https://www.gnu.org/software/gdb/documentation/) - Debugger reference

---

**Outstanding work completing Module 4! 🎉**

*Next: [Module 5: File I/O and System Programming](../module-05-file-io/README.md)*

