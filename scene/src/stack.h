typedef struct node {
    float value;
    struct node *next;
} Node;

void push(Node head, float value);
Node pop(Node head);
Node new_stack();
