#ifndef LINKED_LIST_H
#define LINKED_LIST_H

// Singly Linked List
typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    int size;
} LinkedList;

// Doubly Linked List
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

// Circular Linked List
typedef struct {
    Node *head;
    int size;
} CircularLinkedList;

// Singly Linked List Functions
LinkedList* create_linked_list();
Node* create_node(int data);
void insert_at_beginning(LinkedList *list, int data);
void insert_at_end(LinkedList *list, int data);
void insert_at_position(LinkedList *list, int data, int position);
int delete_by_value(LinkedList *list, int data);
int delete_at_position(LinkedList *list, int position);
Node* search(LinkedList *list, int data);
int get_at_position(LinkedList *list, int position);
void display_list(LinkedList *list);
void reverse_list(LinkedList *list);
void sort_list(LinkedList *list);
void free_list(LinkedList *list);

// Doubly Linked List Functions
DoublyLinkedList* create_doubly_linked_list();
DNode* create_dnode(int data);
void dll_insert_at_beginning(DoublyLinkedList *list, int data);
void dll_insert_at_end(DoublyLinkedList *list, int data);
int dll_delete_by_value(DoublyLinkedList *list, int data);
void dll_display_forward(DoublyLinkedList *list);
void dll_display_backward(DoublyLinkedList *list);
void dll_free_list(DoublyLinkedList *list);

// Circular Linked List Functions
CircularLinkedList* create_circular_linked_list();
void cll_insert_at_end(CircularLinkedList *list, int data);
void cll_display(CircularLinkedList *list);
void cll_free_list(CircularLinkedList *list);

#endif // LINKED_LIST_H

