#include <err.h>
#include <string.h>
#include "htab.h"


uint32_t hash(char *key)
{
    uint32_t hash = 0;
    for (int i = 0; i < strlen(key); i++)
    {
        hash += key[i];
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    return hash;
}


struct htab *htab_new()
{
    malloc(sizeof(struct htab));
    malloc(sizeof(struct pair) * 4);
    struct htab *ht = malloc(sizeof(struct htab));
    ht->size = 0;
    ht->capacity = 4;
    ht->data = malloc(sizeof(struct pair) * 4);
    for (int i = 0; i < 4; i++)
    {
        ht->data[i].key = NULL;
        ht->data[i].value = NULL;
        ht->data[i].next = NULL;
    }
    return ht;
}

void htab_clear(struct htab *ht)
{
    for (int i = 0; i < ht->capacity; i++)
    {
        if (ht->data[i].key != NULL)
        {
            free(ht->data[i].key);
            free(ht->data[i].value);
            struct pair *tmp = ht->data[i].next;
            while (tmp != NULL)
            {
                free(tmp->key);
                free(tmp->value);
                struct pair *tmp2 = tmp;
                tmp = tmp->next;
                free(tmp2);
            }
        }
    }
    ht->size = 0;
    ht->capacity = 4;
    ht->data = realloc(ht->data, sizeof(struct pair) * 4);
    for (int i = 0; i < 4; i++)
    {
        ht->data[i].key = NULL;
        ht->data[i].value = NULL;
        ht->data[i].next = NULL;
    }
}

void htab_free(struct htab *ht)
{
    htab_clear(ht);
    free(ht->data);
    free(ht);
}

struct pair *htab_get(struct htab *ht, char *key)
{
    uint32_t hash_value = hash(key);
    int index = hash_value % ht->capacity;
    if (ht->data[index].key == NULL)
    {
        return NULL;
    }
    else
    {
        struct pair *tmp = &ht->data[index];
        while (tmp != NULL)
        {
            if (strcmp(tmp->key, key) == 0)
            {
                return tmp;
            }
            tmp = tmp->next;
        }
        return NULL;
    }
}

int htab_insert(struct htab *ht, char *key, void *value)
{
    if (htab_get(ht, key) != NULL)
    {
        return 0;
    }
    else
    {
        if (ht->size == ht->capacity)
        {
            ht->capacity *= 2;
            ht->data = realloc(ht->data, sizeof(struct pair) * ht->capacity);
            for (int i = ht->size; i < ht->capacity; i++)
            {
                ht->data[i].key = NULL;
                ht->data[i].value = NULL;
                ht->data[i].next = NULL;
            }
        }
        uint32_t hash_value = hash(key);
        int index = hash_value % ht->capacity;
        if (ht->data[index].key == NULL)
        {
            ht->data[index].key = strdup(key);
            ht->data[index].value = value;
            ht->size++;
            return 1;
        }
        else
        {
            struct pair *tmp = &ht->data[index];
            while (tmp->next != NULL)
            {
                tmp = tmp->next;
            }
            tmp->next = malloc(sizeof(struct pair));
            tmp->next->key = strdup(key);
            tmp->next->value = value;
            tmp->next->next = NULL;
            ht->size++;
            return 1;
        }
    }
}

void htab_remove(struct htab *ht, char *key)
{

    uint32_t hash_value = hash(key);
    int index = hash_value % ht->capacity;
    if (ht->data[index].key == NULL)
    {
        return;
    }
    else
    {
        struct pair *tmp = &ht->data[index];
        if (strcmp(tmp->key, key) == 0)
        {
            free(tmp->key);
            free(tmp->value);
            if (tmp->next == NULL)
            {
                tmp->key = NULL;
                tmp->value = NULL;
                ht->size--;
                return;
            }
            else
            {
                struct pair *tmp2 = tmp->next;
                tmp->key = tmp2->key;
                tmp->value = tmp2->value;
                tmp->next = tmp2->next;
                free(tmp2);
                ht->size--;
                return;
            }
        }
        else
        {
            while (tmp->next != NULL)
            {
                if (strcmp(tmp->next->key, key) == 0)
                {
                    free(tmp->next->key);
                    free(tmp->next->value);
                    struct pair *tmp2 = tmp->next;
                    tmp->next = tmp2->next;
                    free(tmp2);
                    ht->size--;
                    return;
                }
                tmp = tmp->next;
            }
        }
    }
}