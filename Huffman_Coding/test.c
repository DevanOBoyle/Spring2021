#include "code.h"
#include "inttypes.h"
#include "io.h"
#include "node.h"
#include "pq.h"
#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"

int main(void) {
    Node *n = node_create('a', 3);
    Node *w = node_create('b', 2);
    Node *j = node_join(n, w);
    PriorityQueue *q = pq_create(30);
    enqueue(q, n);
    enqueue(q, w);
    //pq_print(q);
    dequeue(q, &n);
    dequeue(q, &w);
    pq_delete(&q);
    //node_print(j);
    node_delete(&n);
    node_delete(&w);
    node_delete(&j);
    Code c = code_init();

    code_push_bit(&c, 1);
    code_push_bit(&c, 0);
    write_code(1, &c);
    flush_codes(1);
    //code_print(&c);
    uint8_t bit1 = 1;
    uint8_t bit2 = 1;
    code_pop_bit(&c, &bit1);
    code_pop_bit(&c, &bit2);
    return 0;
}
