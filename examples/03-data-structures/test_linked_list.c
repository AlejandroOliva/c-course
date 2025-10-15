#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

int main() {
    printf("Testing Linked List Implementation\n");
    printf("==================================\n");
    
    // Test singly linked list
    printf("\n1. Testing Singly Linked List:\n");
    LinkedList *list = create_linked_list();
    
    insert_at_end(list, 10);
    insert_at_end(list, 20);
    insert_at_end(list, 30);
    insert_at_beginning(list, 5);
    
    printf("List after insertions: ");
    display_list(list);
    printf("List size: %d\n", list->size);
    
    // Test search
    Node *found = search(list, 20);
    if (found) {
        printf("Found 20 in the list\n");
    }
    
    // Test deletion
    delete_by_value(list, 20);
    printf("After deleting 20: ");
    display_list(list);
    
    // Test doubly linked list
    printf("\n2. Testing Doubly Linked List:\n");
    DoublyLinkedList *dlist = create_doubly_linked_list();
    
    dll_insert_at_end(dlist, 100);
    dll_insert_at_end(dlist, 200);
    dll_insert_at_end(dlist, 300);
    
    dll_display_forward(dlist);
    dll_display_backward(dlist);
    
    // Test circular linked list
    printf("\n3. Testing Circular Linked List:\n");
    CircularLinkedList *clist = create_circular_linked_list();
    
    cll_insert_at_end(clist, 1);
    cll_insert_at_end(clist, 2);
    cll_insert_at_end(clist, 3);
    
    cll_display(clist);
    
    // Clean up
    free_list(list);
    dll_free_list(dlist);
    cll_free_list(clist);
    
    printf("\nAll tests completed successfully!\n");
    return 0;
}

