# Example 3: Data Structure Library

A comprehensive library of data structures and algorithms implemented in C.

## Features

- **Linked Lists**: Singly, doubly, and circular linked lists
- **Stacks and Queues**: Array and linked list implementations
- **Trees**: Binary trees, BST, AVL trees
- **Hash Tables**: Open addressing and chaining
- **Graphs**: Adjacency list and matrix representations
- **Sorting Algorithms**: Bubble, selection, insertion, quick, merge, heap sort
- **Searching Algorithms**: Linear, binary, interpolation search
- **Advanced Data Structures**: Tries, Skip Lists, Bloom Filters

## Files

- `linked_list.c/h` - Linked list implementations
- `stack_queue.c/h` - Stack and queue implementations
- `tree.c/h` - Tree data structures
- `hash_table.c/h` - Hash table implementations
- `graph.c/h` - Graph data structures
- `sorting.c/h` - Sorting algorithms
- `searching.c/h` - Searching algorithms
- `advanced.c/h` - Advanced data structures
- `test_suite.c` - Comprehensive test suite
- `Makefile` - Build configuration
- `README.md` - This file

## Building

```bash
make
```

## Usage

### Running Tests
```bash
./test_suite
```

### Using the Library
```c
#include "linked_list.h"
#include "stack_queue.h"
#include "tree.h"

int main() {
    // Create a linked list
    LinkedList *list = create_linked_list();
    insert_at_end(list, 10);
    insert_at_end(list, 20);
    insert_at_end(list, 30);
    
    // Create a stack
    Stack *stack = create_stack();
    push(stack, 100);
    push(stack, 200);
    
    // Create a binary search tree
    BSTNode *root = NULL;
    root = insert_bst(root, 50);
    root = insert_bst(root, 30);
    root = insert_bst(root, 70);
    
    return 0;
}
```

## Data Structures Overview

### Linked Lists
- **Singly Linked List**: Linear data structure with forward traversal
- **Doubly Linked List**: Bidirectional traversal with previous/next pointers
- **Circular Linked List**: Last node points to first node

### Stacks and Queues
- **Stack**: LIFO (Last In, First Out) data structure
- **Queue**: FIFO (First In, First Out) data structure
- **Priority Queue**: Elements with associated priorities

### Trees
- **Binary Tree**: Each node has at most two children
- **Binary Search Tree**: Ordered binary tree for efficient searching
- **AVL Tree**: Self-balancing binary search tree
- **Heap**: Complete binary tree with heap property

### Hash Tables
- **Open Addressing**: Linear probing, quadratic probing
- **Chaining**: Separate chaining with linked lists
- **Dynamic Resizing**: Automatic resizing based on load factor

### Graphs
- **Adjacency List**: List of neighbors for each vertex
- **Adjacency Matrix**: 2D array representation
- **Graph Algorithms**: BFS, DFS, shortest path, minimum spanning tree

### Sorting Algorithms
- **Comparison Sorts**: Bubble, selection, insertion, quick, merge
- **Non-Comparison Sorts**: Counting, radix, bucket
- **Stable vs Unstable**: Maintains relative order of equal elements

### Searching Algorithms
- **Linear Search**: O(n) time complexity
- **Binary Search**: O(log n) time complexity
- **Interpolation Search**: O(log log n) average case

### Advanced Data Structures
- **Trie**: Tree-like structure for string storage
- **Skip List**: Probabilistic data structure for fast search
- **Bloom Filter**: Space-efficient probabilistic data structure

## Performance Characteristics

| Data Structure | Access | Search | Insertion | Deletion | Space |
|---------------|--------|--------|-----------|----------|-------|
| Array | O(1) | O(n) | O(n) | O(n) | O(n) |
| Linked List | O(n) | O(n) | O(1) | O(1) | O(n) |
| Stack | O(n) | O(n) | O(1) | O(1) | O(n) |
| Queue | O(n) | O(n) | O(1) | O(1) | O(n) |
| BST | O(log n) | O(log n) | O(log n) | O(log n) | O(n) |
| Hash Table | N/A | O(1) | O(1) | O(1) | O(n) |

## Algorithm Complexity

| Algorithm | Time Complexity | Space Complexity |
|-----------|----------------|------------------|
| Bubble Sort | O(n²) | O(1) |
| Selection Sort | O(n²) | O(1) |
| Insertion Sort | O(n²) | O(1) |
| Quick Sort | O(n log n) | O(log n) |
| Merge Sort | O(n log n) | O(n) |
| Heap Sort | O(n log n) | O(1) |
| Linear Search | O(n) | O(1) |
| Binary Search | O(log n) | O(1) |

## Testing

The library includes comprehensive tests for all data structures and algorithms:

```bash
# Run all tests
./test_suite

# Run specific test categories
./test_suite --linked-list
./test_suite --tree
./test_suite --sorting
```

## Memory Management

All data structures include proper memory management:
- Automatic cleanup functions
- Memory leak detection
- Bounds checking
- Error handling

## Thread Safety

The library is designed for single-threaded use. For multi-threaded applications, additional synchronization mechanisms need to be implemented.

## Portability

The code is written in standard C99 and should compile on:
- Linux/Unix systems
- macOS
- Windows (with appropriate compiler)
- Embedded systems

## Contributing

When adding new data structures or algorithms:
1. Follow the existing code style
2. Include comprehensive tests
3. Document time and space complexity
4. Add to the test suite
5. Update this README

## License

This library is provided as educational material. Feel free to use, modify, and distribute.

