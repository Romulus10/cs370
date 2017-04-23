#include <stdlib.h>

#include "stack.h"

void push(Node head, float value) {
    Node tmp = head;
    head = (Node) { value, tmp };
}

Node pop(Node head) {
    Node tmp = head;
    head = head.next;
    return tmp;
}

Node new_stack() {
    Node x;
    return x;
}
