#include <stdio.h>
#include <stdlib.h>
#include "colors.h"

#define BUCKET_SIZE 7
#define EMPTY NULL
#define TRUE 1
#define FALSE -1
#define MAXLOAD 0.5

int load = 0;

int sz = 10;

struct keyval_t
{
    int key;
    int val;
};
typedef struct keyval_t keyval_t;

int bucket_size = 10;

keyval_t *create(int key, int val)
{
    keyval_t *ptr = (keyval_t *)malloc(sizeof(keyval_t));
    ptr->key = key;
    ptr->val = val;

    return ptr;
}

int hash(int key)
{
    return key % bucket_size;
}

int isSaturated(void)
{
    return (load >= bucket_size);
}

int insert(keyval_t *pair, keyval_t *bucket[])
{
    if (isSaturated() == TRUE)
    {
        red();
        printf("Bucket out of space.\n");
        reset();
    }

    int idx = hash(pair->key);

    while (bucket[idx] != NULL)
    {
        idx = (idx + 1) % bucket_size;
    }

    bucket[idx] = pair;
    load++;
    return TRUE;
}

keyval_t *lookup(int key, keyval_t *bucket[])
{
    int idx = hash(key);

    int iter = 0;

    while (bucket[idx]->key != key || iter < bucket_size)
    {
        idx = (idx + 1) % bucket_size;
        iter++;
    }

    if (bucket[idx]->key == key)
    {
        return bucket[idx];
    }

    red();
    printf("Key does not exist!\n");
    reset();

    return NULL;
}

void traverse(keyval_t *bucket[])
{
    printf("\n");
    keyval_t *ptr;
    for (int i = 0; i < bucket_size; i++)
    {
        ptr = bucket[i];

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

int delete (int key, keyval_t *bucket[])
{
    int idx = hash(key);

    int iter = 0;

    while (bucket[idx]->key != key || iter < bucket_size)
    {
        idx = (idx + 1) % bucket_size;
        iter++;
    }

    if (bucket[idx]->key == key)
    {
        free(bucket[idx]);
        bucket[idx] = NULL;
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
    keyval_t *bucket = (keyval_t *)malloc(sz * sizeof(keyval_t));

    // insert(create(0, 20));   // index: 0
    insert(create(50, 21), bucket);  // index: 1
    insert(create(23, 22), bucket);  // index: 2
    insert(create(3, 23), bucket);   // index: 3
    insert(create(4, 24), bucket);   // index: 4
    insert(create(5, 25), bucket);   // index: 5
    insert(create(37, 205), bucket); // index: 2 -> 6
    insert(create(69, 26), bucket);  // index: 6 -> 0
    delete (37, bucket);             // deleting idx 6
    insert(create(0, 20), bucket);   // index: 0 -> 6

    // insert(create(x, y)); // index: x % bucket_size -> Bucket Full

    traverse(bucket);

    return 0;
}