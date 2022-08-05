#include <stdio.h>
#include <stdlib.h>
#include "colors.h"

#define BUCKET_SIZE 7
#define EMPTY NULL
#define TRUE 1
#define FALSE -1

int load = 0;

struct keyval_t
{
    int key;
    int val;
};
typedef struct keyval_t keyval_t;

keyval_t *Bucket[BUCKET_SIZE] = {EMPTY};

keyval_t *create(int key, int val)
{
    keyval_t *ptr = (keyval_t *)malloc(sizeof(keyval_t));
    ptr->key = key;
    ptr->val = val;

    return ptr;
}

int hash(int key)
{
    return key % BUCKET_SIZE;
}

int isFull(void)
{
    return (load >= BUCKET_SIZE);
}

int insert(keyval_t *pair)
{
    if (isFull() == TRUE)
    {
        red();
        printf("Bucket out of space.\n");
        reset();
        return FALSE;
    }

    int idx = hash(pair->key);

    while (Bucket[idx] != NULL)
    {
        idx = (idx + 1) % BUCKET_SIZE;
    }

    Bucket[idx] = pair;
    load++;
    return TRUE;
}

keyval_t *lookup(int key)
{
    int idx = hash(key);

    int iter = 0;

    while (Bucket[idx]->key != key || iter < BUCKET_SIZE)
    {
        idx = (idx + 1) % BUCKET_SIZE;
        iter++;
    }

    if (Bucket[idx]->key == key)
    {
        return Bucket[idx];
    }

    red();
    printf("Key does not exist!\n");
    reset();

    return NULL;
}

void traverse(void)
{
    printf("\n");
    keyval_t *ptr;
    for (int i = 0; i < BUCKET_SIZE; i++)
    {
        ptr = Bucket[i];

        printf("Bucket[%d]:: ", i);

        if (NULL == ptr)
        {
            printf("NULL\n", i);
            continue;
        }
        printf("%d,", ptr->key);
        printf("%d", ptr->val);
        printf("\n");
    }
    printf("\n");
}

int delete (int key)
{
    int idx = hash(key);

    int iter = 0;

    while (Bucket[idx]->key != key || iter < BUCKET_SIZE)
    {
        idx = (idx + 1) % BUCKET_SIZE;
        iter++;
    }

    if (Bucket[idx]->key == key)
    {
        free(Bucket[idx]);
        Bucket[idx] = NULL;
        load--;
        return TRUE;
    }

    red();
    printf("Key does not exist!\n");
    reset();

    return FALSE;
}

int main(void)
{

    // insert(create(0, 20));   // index: 0
    insert(create(50, 21));  // index: 1
    insert(create(23, 22));  // index: 2
    insert(create(3, 23));   // index: 3
    insert(create(4, 24));   // index: 4
    insert(create(5, 25));   // index: 5
    insert(create(37, 205)); // index: 2 -> 6
    insert(create(69, 26));  // index: 6 -> 0
    delete (37);             // deleting idx 6
    insert(create(0, 20));   // index: 0 -> 6

    // insert(create(x, y)); // index: x % bucket_size -> Bucket Full

    traverse();

    return 0;
}