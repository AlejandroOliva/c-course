# Module 6: Data Structures and Algorithms

Welcome to Module 6! This module covers fundamental data structures and algorithms that are essential for efficient programming. You'll learn how to implement, use, and analyze various data structures and algorithms commonly used in software development.

## 🎯 Learning Objectives

By the end of this module, you will be able to:
- Implement and use linked lists, stacks, and queues
- Work with trees and binary search trees
- Understand and implement sorting algorithms
- Implement searching algorithms
- Analyze algorithm complexity (Big O notation)
- Build reusable data structure libraries

## 📚 Topics Covered

1. [Linked Lists](#linked-lists)
2. [Stacks and Queues](#stacks-and-queues)
3. [Trees and Binary Search Trees](#trees-and-binary-search-trees)
4. [Sorting Algorithms](#sorting-algorithms)
5. [Searching Algorithms](#searching-algorithms)
6. [Algorithm Complexity](#algorithm-complexity)
7. [Exercises](#exercises)

---

## Linked Lists

Linked lists are dynamic data structures that can grow and shrink as needed.

### Singly Linked List

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    int size;
} LinkedList;

// Create a new node
Node* create_node(int data) {
    Node *new_node = malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

// Initialize linked list
LinkedList* create_linked_list() {
    LinkedList *list = malloc(sizeof(LinkedList));
    if (list == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    list->head = NULL;
    list->size = 0;
    return list;
}

// Insert at the beginning
void insert_at_beginning(LinkedList *list, int data) {
    Node *new_node = create_node(data);
    if (new_node == NULL) return;
    
    new_node->next = list->head;
    list->head = new_node;
    list->size++;
}

// Insert at the end
void insert_at_end(LinkedList *list, int data) {
    Node *new_node = create_node(data);
    if (new_node == NULL) return;
    
    if (list->head == NULL) {
        list->head = new_node;
    } else {
        Node *current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
    list->size++;
}

// Delete a node with given data
int delete_node(LinkedList *list, int data) {
    if (list->head == NULL) {
        return 0;  // Not found
    }
    
    if (list->head->data == data) {
        Node *temp = list->head;
        list->head = list->head->next;
        free(temp);
        list->size--;
        return 1;  // Found and deleted
    }
    
    Node *current = list->head;
    while (current->next != NULL && current->next->data != data) {
        current = current->next;
    }
    
    if (current->next != NULL) {
        Node *temp = current->next;
        current->next = current->next->next;
        free(temp);
        list->size--;
        return 1;  // Found and deleted
    }
    
    return 0;  // Not found
}

// Search for a value
Node* search(LinkedList *list, int data) {
    Node *current = list->head;
    while (current != NULL) {
        if (current->data == data) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Display the list
void display_list(LinkedList *list) {
    if (list->head == NULL) {
        printf("List is empty\n");
        return;
    }
    
    Node *current = list->head;
    printf("List: ");
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

// Free the entire list
void free_list(LinkedList *list) {
    Node *current = list->head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}

int main() {
    LinkedList *list = create_linked_list();
    
    insert_at_end(list, 10);
    insert_at_end(list, 20);
    insert_at_end(list, 30);
    insert_at_beginning(list, 5);
    
    printf("List size: %d\n", list->size);
    display_list(list);
    
    if (search(list, 20) != NULL) {
        printf("Found 20 in the list\n");
    }
    
    delete_node(list, 20);
    printf("After deleting 20:\n");
    display_list(list);
    
    free_list(list);
    return 0;
}
```

### Doubly Linked List

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct DNode {
    int data;
    struct DNode *prev;
    struct DNode *next;
} DNode;

typedef struct {
    DNode *head;
    DNode *tail;
    int size;
} DoublyLinkedList;

DNode* create_dnode(int data) {
    DNode *new_node = malloc(sizeof(DNode));
    if (new_node == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    new_node->data = data;
    new_node->prev = NULL;
    new_node->next = NULL;
    return new_node;
}

DoublyLinkedList* create_doubly_linked_list() {
    DoublyLinkedList *list = malloc(sizeof(DoublyLinkedList));
    if (list == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

void insert_at_end(DoublyLinkedList *list, int data) {
    DNode *new_node = create_dnode(data);
    if (new_node == NULL) return;
    
    if (list->head == NULL) {
        list->head = list->tail = new_node;
    } else {
        list->tail->next = new_node;
        new_node->prev = list->tail;
        list->tail = new_node;
    }
    list->size++;
}

void display_forward(DoublyLinkedList *list) {
    if (list->head == NULL) {
        printf("List is empty\n");
        return;
    }
    
    DNode *current = list->head;
    printf("Forward: ");
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

void display_backward(DoublyLinkedList *list) {
    if (list->tail == NULL) {
        printf("List is empty\n");
        return;
    }
    
    DNode *current = list->tail;
    printf("Backward: ");
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->prev;
    }
    printf("NULL\n");
}

int main() {
    DoublyLinkedList *list = create_doubly_linked_list();
    
    insert_at_end(list, 10);
    insert_at_end(list, 20);
    insert_at_end(list, 30);
    
    display_forward(list);
    display_backward(list);
    
    return 0;
}
```

## Stacks and Queues

### Stack Implementation

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct StackNode {
    int data;
    struct StackNode *next;
} StackNode;

typedef struct {
    StackNode *top;
    int size;
} Stack;

Stack* create_stack() {
    Stack *stack = malloc(sizeof(Stack));
    if (stack == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    stack->top = NULL;
    stack->size = 0;
    return stack;
}

int is_empty(Stack *stack) {
    return stack->top == NULL;
}

void push(Stack *stack, int data) {
    StackNode *new_node = malloc(sizeof(StackNode));
    if (new_node == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    new_node->data = data;
    new_node->next = stack->top;
    stack->top = new_node;
    stack->size++;
}

int pop(Stack *stack) {
    if (is_empty(stack)) {
        printf("Stack is empty!\n");
        return -1;  // Error value
    }
    
    StackNode *temp = stack->top;
    int data = temp->data;
    stack->top = stack->top->next;
    free(temp);
    stack->size--;
    return data;
}

int peek(Stack *stack) {
    if (is_empty(stack)) {
        printf("Stack is empty!\n");
        return -1;
    }
    return stack->top->data;
}

void display_stack(Stack *stack) {
    if (is_empty(stack)) {
        printf("Stack is empty\n");
        return;
    }
    
    StackNode *current = stack->top;
    printf("Stack (top to bottom): ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void free_stack(Stack *stack) {
    while (!is_empty(stack)) {
        pop(stack);
    }
    free(stack);
}

int main() {
    Stack *stack = create_stack();
    
    push(stack, 10);
    push(stack, 20);
    push(stack, 30);
    
    printf("Stack size: %d\n", stack->size);
    display_stack(stack);
    
    printf("Top element: %d\n", peek(stack));
    
    printf("Popped: %d\n", pop(stack));
    printf("Popped: %d\n", pop(stack));
    
    display_stack(stack);
    
    free_stack(stack);
    return 0;
}
```

### Queue Implementation

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct QueueNode {
    int data;
    struct QueueNode *next;
} QueueNode;

typedef struct {
    QueueNode *front;
    QueueNode *rear;
    int size;
} Queue;

Queue* create_queue() {
    Queue *queue = malloc(sizeof(Queue));
    if (queue == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
    return queue;
}

int is_empty(Queue *queue) {
    return queue->front == NULL;
}

void enqueue(Queue *queue, int data) {
    QueueNode *new_node = malloc(sizeof(QueueNode));
    if (new_node == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    new_node->data = data;
    new_node->next = NULL;
    
    if (is_empty(queue)) {
        queue->front = queue->rear = new_node;
    } else {
        queue->rear->next = new_node;
        queue->rear = new_node;
    }
    queue->size++;
}

int dequeue(Queue *queue) {
    if (is_empty(queue)) {
        printf("Queue is empty!\n");
        return -1;  // Error value
    }
    
    QueueNode *temp = queue->front;
    int data = temp->data;
    queue->front = queue->front->next;
    
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    
    free(temp);
    queue->size--;
    return data;
}

int front(Queue *queue) {
    if (is_empty(queue)) {
        printf("Queue is empty!\n");
        return -1;
    }
    return queue->front->data;
}

void display_queue(Queue *queue) {
    if (is_empty(queue)) {
        printf("Queue is empty\n");
        return;
    }
    
    QueueNode *current = queue->front;
    printf("Queue (front to rear): ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void free_queue(Queue *queue) {
    while (!is_empty(queue)) {
        dequeue(queue);
    }
    free(queue);
}

int main() {
    Queue *queue = create_queue();
    
    enqueue(queue, 10);
    enqueue(queue, 20);
    enqueue(queue, 30);
    
    printf("Queue size: %d\n", queue->size);
    display_queue(queue);
    
    printf("Front element: %d\n", front(queue));
    
    printf("Dequeued: %d\n", dequeue(queue));
    printf("Dequeued: %d\n", dequeue(queue));
    
    display_queue(queue);
    
    free_queue(queue);
    return 0;
}
```

## Trees and Binary Search Trees

### Binary Tree Implementation

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode* create_tree_node(int data) {
    TreeNode *new_node = malloc(sizeof(TreeNode));
    if (new_node == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

// Tree traversals
void inorder_traversal(TreeNode *root) {
    if (root != NULL) {
        inorder_traversal(root->left);
        printf("%d ", root->data);
        inorder_traversal(root->right);
    }
}

void preorder_traversal(TreeNode *root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder_traversal(root->left);
        preorder_traversal(root->right);
    }
}

void postorder_traversal(TreeNode *root) {
    if (root != NULL) {
        postorder_traversal(root->left);
        postorder_traversal(root->right);
        printf("%d ", root->data);
    }
}

int tree_height(TreeNode *root) {
    if (root == NULL) {
        return -1;  // Height of empty tree is -1
    }
    
    int left_height = tree_height(root->left);
    int right_height = tree_height(root->right);
    
    return 1 + (left_height > right_height ? left_height : right_height);
}

void free_tree(TreeNode *root) {
    if (root != NULL) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}

int main() {
    // Create a sample tree
    //       1
    //      / \
    //     2   3
    //    / \
    //   4   5
    
    TreeNode *root = create_tree_node(1);
    root->left = create_tree_node(2);
    root->right = create_tree_node(3);
    root->left->left = create_tree_node(4);
    root->left->right = create_tree_node(5);
    
    printf("Inorder traversal: ");
    inorder_traversal(root);
    printf("\n");
    
    printf("Preorder traversal: ");
    preorder_traversal(root);
    printf("\n");
    
    printf("Postorder traversal: ");
    postorder_traversal(root);
    printf("\n");
    
    printf("Tree height: %d\n", tree_height(root));
    
    free_tree(root);
    return 0;
}
```

### Binary Search Tree Implementation

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct BSTNode {
    int data;
    struct BSTNode *left;
    struct BSTNode *right;
} BSTNode;

BSTNode* create_bst_node(int data) {
    BSTNode *new_node = malloc(sizeof(BSTNode));
    if (new_node == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

BSTNode* insert(BSTNode *root, int data) {
    if (root == NULL) {
        return create_bst_node(data);
    }
    
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }
    // If data == root->data, do nothing (no duplicates)
    
    return root;
}

BSTNode* search(BSTNode *root, int data) {
    if (root == NULL || root->data == data) {
        return root;
    }
    
    if (data < root->data) {
        return search(root->left, data);
    } else {
        return search(root->right, data);
    }
}

BSTNode* find_min(BSTNode *root) {
    if (root == NULL) {
        return NULL;
    }
    
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

BSTNode* delete(BSTNode *root, int data) {
    if (root == NULL) {
        return root;
    }
    
    if (data < root->data) {
        root->left = delete(root->left, data);
    } else if (data > root->data) {
        root->right = delete(root->right, data);
    } else {
        // Node to be deleted found
        if (root->left == NULL) {
            BSTNode *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            BSTNode *temp = root->left;
            free(root);
            return temp;
        }
        
        // Node with two children
        BSTNode *temp = find_min(root->right);
        root->data = temp->data;
        root->right = delete(root->right, temp->data);
    }
    
    return root;
}

void inorder_traversal(BSTNode *root) {
    if (root != NULL) {
        inorder_traversal(root->left);
        printf("%d ", root->data);
        inorder_traversal(root->right);
    }
}

void free_bst(BSTNode *root) {
    if (root != NULL) {
        free_bst(root->left);
        free_bst(root->right);
        free(root);
    }
}

int main() {
    BSTNode *root = NULL;
    
    // Insert elements
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 60);
    root = insert(root, 80);
    
    printf("Inorder traversal (sorted): ");
    inorder_traversal(root);
    printf("\n");
    
    // Search for elements
    if (search(root, 40) != NULL) {
        printf("40 found in BST\n");
    } else {
        printf("40 not found in BST\n");
    }
    
    // Delete element
    root = delete(root, 30);
    printf("After deleting 30: ");
    inorder_traversal(root);
    printf("\n");
    
    free_bst(root);
    return 0;
}
```

## Sorting Algorithms

### Bubble Sort

```c
#include <stdio.h>

void bubble_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int swapped = 0;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap elements
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }
        // If no swapping occurred, array is sorted
        if (!swapped) {
            break;
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
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("Original array: ");
    print_array(arr, n);
    
    bubble_sort(arr, n);
    
    printf("Sorted array: ");
    print_array(arr, n);
    
    return 0;
}
```

### Quick Sort

```c
#include <stdio.h>

// Partition function for Quick Sort
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            // Swap arr[i] and arr[j]
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    
    // Swap arr[i+1] and arr[high]
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    
    return i + 1;
}

void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

void print_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("Original array: ");
    print_array(arr, n);
    
    quick_sort(arr, 0, n - 1);
    
    printf("Sorted array: ");
    print_array(arr, n);
    
    return 0;
}
```

### Merge Sort

```c
#include <stdio.h>
#include <stdlib.h>

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    // Create temporary arrays
    int *left_arr = malloc(n1 * sizeof(int));
    int *right_arr = malloc(n2 * sizeof(int));
    
    // Copy data to temporary arrays
    for (int i = 0; i < n1; i++) {
        left_arr[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        right_arr[j] = arr[mid + 1 + j];
    }
    
    // Merge the temporary arrays back
    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) {
        if (left_arr[i] <= right_arr[j]) {
            arr[k] = left_arr[i];
            i++;
        } else {
            arr[k] = right_arr[j];
            j++;
        }
        k++;
    }
    
    // Copy remaining elements
    while (i < n1) {
        arr[k] = left_arr[i];
        i++;
        k++;
    }
    
    while (j < n2) {
        arr[k] = right_arr[j];
        j++;
        k++;
    }
    
    free(left_arr);
    free(right_arr);
}

void merge_sort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);
        
        merge(arr, left, mid, right);
    }
}

void print_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("Original array: ");
    print_array(arr, n);
    
    merge_sort(arr, 0, n - 1);
    
    printf("Sorted array: ");
    print_array(arr, n);
    
    return 0;
}
```

## Searching Algorithms

### Linear Search

```c
#include <stdio.h>

int linear_search(int arr[], int n, int target) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == target) {
            return i;  // Return index if found
        }
    }
    return -1;  // Return -1 if not found
}

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 22;
    
    int result = linear_search(arr, n, target);
    
    if (result != -1) {
        printf("Element %d found at index %d\n", target, result);
    } else {
        printf("Element %d not found\n", target);
    }
    
    return 0;
}
```

### Binary Search

```c
#include <stdio.h>

int binary_search(int arr[], int left, int right, int target) {
    if (right >= left) {
        int mid = left + (right - left) / 2;
        
        // If element is present at the middle
        if (arr[mid] == target) {
            return mid;
        }
        
        // If element is smaller than mid, search left half
        if (arr[mid] > target) {
            return binary_search(arr, left, mid - 1, target);
        }
        
        // Else search right half
        return binary_search(arr, mid + 1, right, target);
    }
    
    // Element not found
    return -1;
}

int main() {
    int arr[] = {11, 12, 22, 25, 34, 64, 90};  // Must be sorted
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 25;
    
    int result = binary_search(arr, 0, n - 1, target);
    
    if (result != -1) {
        printf("Element %d found at index %d\n", target, result);
    } else {
        printf("Element %d not found\n", target);
    }
    
    return 0;
}
```

## Algorithm Complexity

### Big O Notation Examples

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// O(1) - Constant time
int get_first_element(int arr[], int n) {
    return arr[0];
}

// O(n) - Linear time
int linear_search_demo(int arr[], int n, int target) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == target) {
            return i;
        }
    }
    return -1;
}

// O(n²) - Quadratic time
void bubble_sort_demo(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// O(log n) - Logarithmic time (binary search)
int binary_search_demo(int arr[], int left, int right, int target) {
    if (right >= left) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            return mid;
        }
        
        if (arr[mid] > target) {
            return binary_search_demo(arr, left, mid - 1, target);
        }
        
        return binary_search_demo(arr, mid + 1, right, target);
    }
    
    return -1;
}

void measure_time(void (*func)(int*, int), int arr[], int n, const char* name) {
    clock_t start = clock();
    func(arr, n);
    clock_t end = clock();
    double time_spent = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("%s: %f seconds\n", name, time_spent);
}

int main() {
    const int size = 10000;
    int *arr = malloc(size * sizeof(int));
    
    // Initialize array with random values
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 1000;
    }
    
    printf("Algorithm Complexity Examples:\n");
    printf("Array size: %d\n\n", size);
    
    // O(1) operation
    clock_t start = clock();
    int first = get_first_element(arr, size);
    clock_t end = clock();
    printf("O(1) - Get first element: %f seconds\n", 
           ((double)(end - start)) / CLOCKS_PER_SEC);
    
    // O(n) operation
    start = clock();
    int found = linear_search_demo(arr, size, 500);
    end = clock();
    printf("O(n) - Linear search: %f seconds\n", 
           ((double)(end - start)) / CLOCKS_PER_SEC);
    
    // O(log n) operation (requires sorted array)
    // Sort array first for binary search
    qsort(arr, size, sizeof(int), (int(*)(const void*, const void*)) 
          ([](const int* a, const int* b) { return *a - *b; }));
    
    start = clock();
    int bin_found = binary_search_demo(arr, 0, size - 1, 500);
    end = clock();
    printf("O(log n) - Binary search: %f seconds\n", 
           ((double)(end - start)) / CLOCKS_PER_SEC);
    
    // O(n²) operation
    int *arr_copy = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        arr_copy[i] = rand() % 1000;
    }
    
    start = clock();
    bubble_sort_demo(arr_copy, size);
    end = clock();
    printf("O(n²) - Bubble sort: %f seconds\n", 
           ((double)(end - start)) / CLOCKS_PER_SEC);
    
    free(arr);
    free(arr_copy);
    
    return 0;
}
```

## Exercises

### Exercise 1: Dynamic Array with Linked List
Implement a dynamic array using a linked list that:
1. Supports random access (though not O(1))
2. Can grow and shrink dynamically
3. Implements common operations (insert, delete, search)
4. Provides bounds checking

### Exercise 2: Expression Evaluator
Build a program that:
1. Uses a stack to evaluate postfix expressions
2. Supports basic arithmetic operations (+, -, *, /)
3. Handles parentheses in infix expressions
4. Converts infix to postfix notation

### Exercise 3: Hash Table Implementation
Create a hash table that:
1. Uses chaining for collision resolution
2. Supports insertion, deletion, and lookup
3. Implements a good hash function
4. Handles resizing when load factor is high

### Exercise 4: Graph Representation
Implement a graph using:
1. Adjacency list representation
2. Functions for adding/removing vertices and edges
3. Breadth-first search (BFS)
4. Depth-first search (DFS)

### Exercise 5: Sorting Algorithm Comparison
Build a program that:
1. Implements multiple sorting algorithms
2. Measures their performance on different data sizes
3. Generates performance comparison reports
4. Tests on different data distributions (random, sorted, reverse sorted)

### Exercise 6: Priority Queue
Implement a priority queue using:
1. Binary heap data structure
2. Operations: insert, extract_max, peek
3. Heapify operations
4. Support for custom comparison functions

## 🎯 Module Summary

In this module, you learned:
- ✅ Linked list implementation and operations
- ✅ Stack and queue data structures
- ✅ Tree and binary search tree operations
- ✅ Sorting algorithms (bubble, quick, merge sort)
- ✅ Searching algorithms (linear, binary search)
- ✅ Algorithm complexity analysis (Big O notation)

## 🚀 What's Next?

You're ready to move on to **Module 7: Practical Exercises**, where you'll learn about:
- Advanced programming projects
- Real-world applications
- Code organization and modularity
- Testing and debugging strategies
- Performance optimization techniques

## 📚 Additional Reading

- [Introduction to Algorithms](https://mitpress.mit.edu/books/introduction-algorithms) - Cormen, Leiserson, Rivest, Stein
- [Data Structures and Algorithms in C](https://www.amazon.com/Data-Structures-Algorithms-Mark-Allen-Weiss/dp/0321375319) - Mark Allen Weiss
- [Algorithm Visualizations](https://visualgo.net/) - Interactive algorithm demonstrations

---

**Excellent work completing Module 6! 🎉**

*Next: [Module 7: Practical Exercises](../module-07-exercises/README.md)*

