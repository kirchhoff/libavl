/*
 *   Libavl is a library to manage AVL structure to store and organize
 *   everykind of data. You just need to implement function to compare,
 *   to desallocate and to print your structure.
 *
 *       DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE 
 *                   Version 2, December 2004 
 *
 *   Copyright (C) 2013 Adrien Oliva <adrien.oliva@yapbreak.fr>
 *
 *   Everyone is permitted to copy and distribute verbatim or modified 
 *   copies of this license document, and changing it is allowed as long 
 *   as the name is changed. 
 *
 *           DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE 
 *   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION 
 *
 *   0. You just DO WHAT THE FUCK YOU WANT TO.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "syslog.h"
#include "avl.h"

struct _tree_data {
    int key;
    int value;
};

int data_cmp(void *a, void *b)
{
    struct _tree_data aa = *((struct _tree_data *) a);
    struct _tree_data bb = *((struct _tree_data *) b);

    return aa.key - bb.key;
}

void data_print(void *d)
{
    printf("%p|%d-%d", d,
            ((struct _tree_data *) d)->key, ((struct _tree_data *) d)->value);
}

void data_delete(void *d)
{
    free(d);
}

void data_copy(void *src, void *dst)
{
    memcpy(dst, src, sizeof(struct _tree_data));
}

#define MAX_ELEMENT 10000

void count_treat(void *n, void *param)
{
    struct _tree_data *data = (struct _tree_data *) n;

    if (param != NULL) {
        *((unsigned int *) param) += (unsigned) data->value;
    }
}

int main(int argc, char *argv[])
{
    tree *first = NULL;
    struct _tree_data data[MAX_ELEMENT];
    struct _tree_data tmp_elmnt;
    unsigned int result;
    unsigned int element_in_tree = 0;
    int i = 0;
    unsigned int r = 0;

    (void) argc;
    (void) argv;

    unsigned long rand_seed = (unsigned long) time(NULL);
    ILOG("Random seed: %lu", rand_seed);
    srand(rand_seed);

    for (i = 0; i < MAX_ELEMENT; i++) {
        data[i].key = rand();
        data[i].value = 1;
    }

    // explore tree on a NULL tree
    explore_tree(first, count_treat, &r);
    if (r != 0) {
        ELOG("Wrong result on NULL tree");
        return EXIT_FAILURE;
    }

    // Try to allocate a new tree.
    first = init_dictionnary(data_cmp, data_print, data_delete, data_copy);
    if (first == NULL) {
        ELOG("Init dictionnary error");
        return EXIT_FAILURE;
    }

    // explore tree on an empty tree
    explore_tree(first, count_treat, &r);
    if (r != 0) {
        ELOG("Wrong result on empty tree");
        return EXIT_FAILURE;
    }

    // Add data
    verif_tree(first);
    for (i = 0; i < MAX_ELEMENT; i++) {
        tmp_elmnt.key = data[i].key;
        if (!is_present(first, &(tmp_elmnt))) {
            element_in_tree++;
        }
        result = insert_elmt(first, &(data[i]), sizeof(struct _tree_data));
        if (result != element_in_tree) {
            ELOG("Wrong result of inserted element");
            return EXIT_FAILURE;
        }
        verif_tree(first);
    }

    explore_tree(first, count_treat, &r);
    if (r != element_in_tree) {
        ELOG("Wrong result on empty tree: %d != %d", r, element_in_tree);
        return EXIT_FAILURE;
    }

    // Try to delete it
    delete_tree(first);



    return EXIT_SUCCESS;
}
