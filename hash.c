#include "sporth.h"

uint32_t sporth_hash(const char *str)
{
    uint32_t h = 5381;
    while(*str)
    {
        h = ((h << 5) + h) ^ str[0];
        h %= 0x7FFFFFFF;
        *str++;
    }

    return h % 256;
}

int sporth_search(sporth_htable *ht, const char *key, uint32_t *val)
{
    uint32_t pos = sporth_hash(key);
    sporth_list *list = &ht->list[pos];
    uint32_t i;
    sporth_entry *entry = list->root.next;;
    for(i = 0; i < list->count; i++) {
        if(!strcmp(entry->key, key)) {
            *val = entry->val;
            return SPORTH_OK;
        }
        entry = entry->next;
    }

    return SPORTH_NOTOK;
}

int sporth_htable_add(sporth_htable *ht, const char *key, uint32_t val)
{
    uint32_t pos = sporth_hash(key);

    sporth_list *list = &ht->list[pos];
    list->count++;
    sporth_entry *old = list->last;
    sporth_entry *new = malloc(sizeof(sporth_entry));
    new->val = val;
    new->key = malloc(sizeof(char) * (strlen(key) + 1));
    strcpy(new->key, key);
    old->next = new;
    list->last = new;

    return SPORTH_OK;
}

int sporth_htable_init(sporth_htable *ht)
{
    sporth_list *list;
    int i;

    for(i = 0; i < 256; i++) {
        list = &ht->list[i];
        list->last = &list->root;
        list->count = 0;
    }

    return SPORTH_OK;
}

int sporth_htable_destroy(sporth_htable *ht)
{
    sporth_list *list;
    sporth_entry *entry, *next;
    int i, j;

    for(i = 0; i < 256; i++) {
        list = &ht->list[i];
        entry = list->root.next;
        for(j = 0; j < list->count; j++) {
            next = entry->next;
            free(entry->key);
            free(entry);
            entry = next;
        }
    }

    return SPORTH_OK;
}
/*
int main()
{
    sporth_htable ht;
    uint32_t val = 0;
    sporth_htable_init(&ht);
    const char *key = "Helloworld";
    sporth_htable_add(&ht, "PaulBatchelor", 123456);
    sporth_htable_add(&ht, "Helloworld", 3321);

    if(sporth_search(&ht, key, &val) == SPORTH_OK) {
        printf("The val for %s is %d\n", key, val);
    } else {
        printf("Could not find a value for key %s\n", key);
    }

    sporth_htable_destroy(&ht);
    return 0;
}
*/