#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "colors.h"

#define BUCKET_SIZE 7
#define TRUE 1
#define FALSE 0

struct keyval
{
    char *name;
    int data;
    struct keyval *next;
};
typedef struct keyval keyval;

int Load = 0;
float LoadFactorThreshold = 0.0000;

keyval *Bucket[BUCKET_SIZE] = {NULL};

int hash(char *ptr)
{
    int value;
    int sum = 0;
    for (size_t i = 0; i < strlen(ptr); i++)
    {
        value = 10 * (int)ptr[i] + i+1;
        sum += value;
    }
    return sum % BUCKET_SIZE;
}

keyval *create(char *name, int data)
{
    keyval *new = malloc(sizeof(keyval));
    int len = strlen(name);
    char *m_name = malloc(sizeof(char) * (len + 1)); // +1 for \0

    size_t i = 0;
    for (i = 0; i < len; i++)
    {
        m_name[i] = name[i];
    }

    m_name[i] = '\0';

    new->name = m_name;
    new->data = data;
    new->next = NULL;

    return new;
}

int CheckDuplicate(keyval *ptr, char *string)
{
    while (ptr != NULL)
    {
        if (strcmp(ptr->name, string) == 0)
        {
            return TRUE;
        }
        ptr = ptr->next;
    }
    return FALSE;
}

void Write(char *name, int data)
{
    // if ((float)(Load + 1) / BUCKET_SIZE > LoadFactorThreshold)
    // {
    //     /* Table explansion */
    // }

    int idx = hash(name);
    keyval *new = create(name, data);
    keyval *ptr = Bucket[idx];

    if (ptr != NULL)
    {
        if (CheckDuplicate(ptr, name) == TRUE)
        {
            free(new);
            red();
            printf("Entry <%s> already exists\n", name);
            reset();
            return;
        }
        new->next = ptr;
    }
    Bucket[idx] = new;
    // Load++;
}

void Remove(char *name)
{
    int idx = hash(name);
    keyval *ptr = Bucket[idx];

    if (ptr != NULL)
    {
        if (strcmp(ptr->name, name) == 0)
        {
            free(ptr);
            Bucket[idx] = NULL;
            return;
        }
        while (ptr->next != NULL)
        {
            if (strcmp(ptr->next->name, name) == 0)
            {
                keyval *next = ptr->next->next;
                free(ptr->next);
                ptr->next = next;
                return;
            }
            ptr = ptr->next;
        }
    }
    red();
    printf("Entry <%s> does not exist\n", name);
    reset();
}

void Read()
{
    keyval *ptr;
    printf("\n");
    for (size_t i = 0; i < BUCKET_SIZE; i++)
    {
        ptr = Bucket[i];
        if (ptr != NULL)
        {
            printf("Bucket[%d]: ", i);
            while (ptr != NULL)
            {
                printf("%s ", ptr->name);

                blue();
                printf("%d", ptr->data);

                reset();
                printf(" -> ", ptr->name, ptr->data);

                ptr = ptr->next;
            }
            printf("\b\b\b   \n\n");
            continue;
        }
        printf("Bucket[%d]: ", i);

        red();
        printf("NULL\n\n");

        reset();
    }
}

int main(void)
{

    Write("Rohit Sharma", 19);
    Write("Ajinkya Rahane", 18);
    Write("Joe Root", 121);
    Write("Cheteswar Pujara", 91);
    Write("KL Rahul", 8);
    Write("Virat Kohli", 55);
    Write("Sam Curran", 15);
    Write("Ajinkya Rahane", 18);
    Write("Sam Curran", 15);

    Remove("Rohit Sharma");

    Read();

    return 0;
}