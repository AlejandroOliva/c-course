#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"

// Singly Linked List Implementation

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

void insert_at_beginning(LinkedList *list, int data) {
    Node *new_node = create_node(data);
    if (new_node == NULL) return;
    
    new_node->next = list->head;
    list->head = new_node;
    list->size++;
}

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

void insert_at_position(LinkedList *list, int data, int position) {
    if (position < 0 || position > list->size) {
        printf("Invalid position!\n");
        return;
    }
    
    if (position == 0) {
        insert_at_beginning(list, data);
        return;
    }
    
    if (position == list->size) {
        insert_at_end(list, data);
        return;
    }
    
    Node *new_node = create_node(data);
    if (new_node == NULL) return;
    
    Node *current = list->head;
    for (int i = 0; i < position - 1; i++) {
        current = current->next;
    }
    
    new_node->next = current->next;
    current->next = new_node;
    list->size++;
}

int delete_by_value(LinkedList *list, int data) {
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

int delete_at_position(LinkedList *list, int position) {
    if (position < 0 || position >= list->size) {
        printf("Invalid position!\n");
        return 0;
    }
    
    if (position == 0) {
        Node *temp = list->head;
        list->head = list->head->next;
        free(temp);
        list->size--;
        return 1;
    }
    
    Node *current = list->head;
    for (int i = 0; i < position - 1; i++) {
        current = current->next;
    }
    
    Node *temp = current->next;
    current->next = current->next->next;
    free(temp);
    list->size--;
    return 1;
}

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

int get_at_position(LinkedList *list, int position) {
    if (position < 0 || position >= list->size) {
        printf("Invalid position!\n");
        return -1;
    }
    
    Node *current = list->head;
    for (int i = 0; i < position; i++) {
        current = current->next;
    }
    return current->data;
}

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

void reverse_list(LinkedList *list) {
    Node *prev = NULL;
    Node *current = list->head;
    Node *next = NULL;
    
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    
    list->head = prev;
}

void sort_list(LinkedList *list) {
    if (list->size <= 1) return;
    
    // Bubble sort implementation
    for (Node *i = list->head; i != NULL; i = i->next) {
        for (Node *j = i->next; j != NULL; j = j->next) {
            if (i->data > j->data) {
                int temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }
}

void free_list(LinkedList *list) {
    Node *current = list->head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}

// Doubly Linked List Implementation

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

void dll_insert_at_beginning(DoublyLinkedList *list, int data) {
    DNode *new_node = create_dnode(data);
    if (new_node == NULL) return;
    
    if (list->head == NULL) {
        list->head = list->tail = new_node;
    } else {
        new_node->next = list->head;
        list->head->prev = new_node;
        list->head = new_node;
    }
    list->size++;
}

void dll_insert_at_end(DoublyLinkedList *list, int data) {
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

int dll_delete_by_value(DoublyLinkedList *list, int data) {
    DNode *current = list->head;
    
    while (current != NULL) {
        if (current->data == data) {
            if (current == list->head) {
                list->head = current->next;
                if (list->head != NULL) {
                    list->head->prev = NULL;
                }
            } else if (current == list->tail) {
                list->tail = current->prev;
                list->tail->next = NULL;
            } else {
                current->prev->next = current->next;
                current->next->prev = current->prev;
            }
            
            free(current);
            list->size--;
            return 1;  // Found and deleted
        }
        current = current->next;
    }
    
    return 0;  // Not found
}

void dll_display_forward(DoublyLinkedList *list) {
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

void dll_display_backward(DoublyLinkedList *list) {
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

void dll_free_list(DoublyLinkedList *list) {
    DNode *current = list->head;
    while (current != NULL) {
        DNode *temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}

// Circular Linked List Implementation

CircularLinkedList* create_circular_linked_list() {
    CircularLinkedList *list = malloc(sizeof(CircularLinkedList));
    if (list == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    list->head = NULL;
    list->size = 0;
    return list;
}

void cll_insert_at_end(CircularLinkedList *list, int data) {
    Node *new_node = create_node(data);
    if (new_node == NULL) return;
    
    if (list->head == NULL) {
        list->head = new_node;
        new_node->next = new_node;  // Point to itself
    } else {
        Node *current = list->head;
        while (current->next != list->head) {
            current = current->next;
        }
        current->next = new_node;
        new_node->next = list->head;
    }
    list->size++;
}

void cll_display(CircularLinkedList *list) {
    if (list->head == NULL) {
        printf("List is empty\n");
        return;
    }
    
    Node *current = list->head;
    printf("Circular List: ");
    do {
        printf("%d -> ", current->data);
        current = current->next;
    } while (current != list->head);
    printf("(back to %d)\n", list->head->data);
}

void cll_free_list(CircularLinkedList *list) {
    if (list->head == NULL) {
        free(list);
        return;
    }
    
    Node *current = list->head->next;
    while (current != list->head) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    free(list->head);
    free(list);
}

