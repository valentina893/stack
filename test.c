#include <stdio.h>

#define STACK_T int
#define STACK_PREFIX stack_
#define STACK_NAME istack
#include "stack.h"

int test_clear() {
    int passed = 1;
    istack s = stack_init(10);
    for (int i = 0; i < 10; i++) stack_push(&s, i);
    stack_clear(&s);
    if (stack_size(&s) != 0) {
        passed = 0;
        printf("incorrect size after clearing\n");
    }
    return passed;
}

int test_init() {

    int passed = 1;

    istack s = stack_init(10);

    if (stack_size(&s) != 0) {
        passed = 0;
        printf("incorrect size\n");
    }

    if (stack_ptr(&s) == NULL) {
        passed = 0;
        printf("array ptr is null\n");
    }

    stack_delete(&s);

    return passed;
}

int test_destroy() {
    int passed = 1;
    istack s = stack_init(10);
    stack_delete(&s);
    if (stack_ptr(&s) != NULL) {
        passed = 0;
        printf("stack array ptr not null after destroying\n");
    }
    return passed;
}

int test_push() {
    int passed = 1;
   
    istack s = stack_init(10);
    int sz = 0;

    // test attributes after 1 push
    stack_push(&s, 21);
    if (stack_size(&s) != 1) {
        passed = 0;
        printf("incorrect size after 1 push\n");
    }
    if (stack_pop(&s) != 21) {
        passed = 0;
        printf("incorrect element popped from stack\n");
    }

    // test attributes after 10 pushes
    for (; sz < 10; sz++) {
        stack_push(&s, sz+1);
    }
    if (stack_size(&s) != sz) {
        passed = 0;
        printf("incorrect size after 10 pushes, expected 10, got %llu\n", stack_size(&s));
    }
    for (; sz > 0; sz--) {
        int pop = stack_pop(&s);
        if (pop != sz) {
            passed = 0;
            printf("incorrect element popped from stack, expected %d, got %d\n", sz, pop);
        }
    }

    // test attributes after 300 pushes
    for (; sz < 300; sz++) {
        stack_push(&s, sz+1);
    }
    if (stack_size(&s) != sz) {
        passed = 0;
        printf("incorrect size after 300 pushes, expected 300, got %llu\n", stack_size(&s));
    }
    for (; sz > 0; sz--) {
        int pop = stack_pop(&s);
        if (pop != sz) {
            passed = 0;
            printf("incorrect element popped from stack, expected %d, got %d\n", sz, pop);
        }
    }

    stack_delete(&s);

    return passed;
}

int test_peek() {
    int passed = 1;
    istack s = stack_init(10);

    if (stack_peek(&s) != 0) {
        passed = 0;
        printf("top value is incorrect after init\n");
    }

    stack_push(&s, 100);

    if (stack_peek(&s) != 100) {
        passed = 0;
        printf("top value is incorrect after pushing\n");
    }

    return passed;
}

int test_size() {
    int passed = 1;
    istack s = stack_init(10);

    if (stack_size(&s) != 0) {
        passed = 0;
        printf("size not 0 when initialized\n");
    }

    int exp = 10;
    for (int i = 0; i < exp; i++) {
        stack_push(&s, i);
    }

    if (stack_size(&s) != exp) {
        passed = 0;
        printf("size not correct after pushing\n");
    }

    stack_pop(&s);
    if (stack_size(&s) != exp - 1) {
        passed = 0;
        printf("size not correct after popping\n");
    }

    return passed;
}

int test_pop() {
    int passed = 1;

    istack s = stack_init(10);

    // test attributes after pop from empty stack
    int pop = stack_pop(&s);
    if (pop != 0) {
        passed = 0;
        printf("incorrect element popped from empty stack\n");
    }
    if (stack_size(&s) != 0) {
        passed = 0;
        printf("incorrect size after popping from empty stack\n");
    }

    stack_push(&s, 1);

    return passed;
}

int main() {
    int passed = 0;
    printf("testing clear()\n");
    passed += test_clear();
    printf("testing init()\n");
    passed += test_init();
    printf("testing delete()\n");
    passed += test_destroy();
    printf("testing push()\n");
    passed += test_push();
    printf("testing peek()\n");
    passed += test_peek();
    printf("testing size()\n");
    passed += test_size();
    printf("testing pop()\n");
    passed += test_pop();
    printf("%d tests passed\n", passed);
    return 0;
}