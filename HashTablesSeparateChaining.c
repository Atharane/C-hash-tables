#include <stdio.h>
#include <stdlib.h>

#define BUCKET_SIZE 7
#define EMPTY NULL
#define TRUE 1;
#define FALSE -1;

struct keyval_t
{
    int key;
    int val;
    struct keyval_t *next;
};
typedef struct keyval_t keyval_t;

keyval_t *Bucket[BUCKET_SIZE] = {EMPTY};

keyval_t *create(int key, int val)
{
    keyval_t *ptr = (keyval_t *)malloc(sizeof(keyval_t));
    ptr->key = key;
    ptr->val = val;
    ptr->next = NULL;
    return ptr;
}

int hash(int key)
{
    return key % BUCKET_SIZE;
}

void insert(keyval_t *pair)
{
    int idx = hash(pair->key);
    keyval_t *ptr = Bucket[idx];

    if (ptr != EMPTY)
        pair->next = ptr;

    Bucket[idx] = pair;
}

keyval_t *lookup(int key)
{
    int idx = hash(key);

    if (Bucket[idx]->key != key)
    {
        printf("Key not found!");
        return NULL;
    }
    return Bucket[idx];
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
        while (ptr != NULL)
        {
            printf("%d,",ptr->key);
            printf("%d", ptr->val);
            printf(" -> ");
            ptr = ptr->next;
        }
        printf("\b\b\b  \n");
    }
    printf("\n");
}

int delete (int key)
{
}

int main(void)
{

    insert(create(0, 20));  // index: 0
    insert(create(50, 21)); // index: 1
    insert(create(23, 22)); // index: 2
    insert(create(3, 23));  // index: 3
    insert(create(4, 24));  // index: 4
    insert(create(5, 25));  // index: 5
    insert(create(40, 25)); // index: 5
    // insert(create(69, 26)); // index: 6

    traverse();

    return 0;
}