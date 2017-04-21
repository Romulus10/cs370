typedef struct node {
    char *type;
    float value;
    struct node *next;
} Node;

void push(Node head, char *type, float value);
Node pop(Node head);
Node new_stack();
