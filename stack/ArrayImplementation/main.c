#include <stdbool.h>
#include <stdio.h>
#define MAX_SIZE 101

typedef struct {
        int top;
        int arr[MAX_SIZE];
} stack;

static bool isFull(stack *working_structure) { return working_structure->top == (MAX_SIZE - 1); }

static bool isEmpty(stack *working_structure) { return working_structure->top < 0; }

static void Push(int data, stack *working_structure) {
        if (isFull(working_structure)) {
                puts("Stack full; CRASH INCOMING");
                return;
        } else {
                working_structure->top++;
                working_structure->arr[working_structure->top] = data;
        }
}

static void Pop(stack *working_structure) {
        if (working_structure->top < 0) {
                puts("List is too short; No elements to pop");
                return;
        } else {
                printf("Popping element : %d\n", working_structure->arr[working_structure->top]);
                working_structure->top--;
        }
}
static int Top(stack *working_structure) {
        if (!isEmpty(working_structure)) {
                return working_structure->arr[working_structure->top];
        } else {
                puts("STACK EMPTY; NO TOP ELEMENT !");
                return -1;
        }
}

static void Print(stack *working_structure) {
        int i = 0;
        fputs("List : ", stdout);
        while (i <= working_structure->top) {
                printf("%d\t", working_structure->arr[i]);
                i++;
        }
        puts("");
}

int main(void) {
        stack main_struct = {.top = -1};

        Push(2, &main_struct);
        Print(&main_struct);

        Push(4, &main_struct);
        Print(&main_struct);

        printf("Top Element : %d\n", Top(&main_struct));
        Pop(&main_struct);

        Push(6, &main_struct);
        Print(&main_struct);

        Push(8, &main_struct);
        Print(&main_struct);

        printf("Top Element : %d\n", Top(&main_struct));
        Pop(&main_struct);

        Push(12, &main_struct);
        Print(&main_struct);
        return 0;
}
