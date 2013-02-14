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

#include "syslog.h"
#include "avl.h"

int data_cmp(void *a, void *b)
{
    int aa = *((int *) a);
    int bb = *((int *) b);

    return aa - bb;
}

void data_print(void *d)
{
    printf("%p|%d", d, *((int *) d));
}

void data_delete(void *d)
{
    free(d);
}

int main(int argc, char *argv[])
{
    tree *first = NULL;
    int data;
    unsigned int result;

    (void) argc;
    (void) argv;

    unsigned long rand_seed = (unsigned long) time(NULL);
    ILOG("Random seed: %lu", rand_seed);
    srand(rand_seed);
    // Try to allocate a new tree.
    first = init_dictionnary(data_cmp, data_print, data_delete, NULL);
    if (first == NULL) {
        ELOG("Init dictionnary error");
        return EXIT_FAILURE;
    }
    if (sizeof(*first) != sizeof(tree)) {
        ELOG("Wrong returned size");
        return EXIT_FAILURE;
    }

    data = rand();

    // Insert one element
    result = insert_elmt(first, &data, sizeof(int));
    if (result != 1) {
        ELOG("Wrong result of insert element");
        return EXIT_FAILURE;
    }

    // Check if element is in tree
    if (!is_present(first, &data)) {
        ELOG("Data not found in tree");
        return EXIT_FAILURE;
    }

    // Insert element already installed
    result = insert_elmt(first, &data, sizeof(int));

    // Check if random element is present
    data++;
    if (is_present(first, &data)) {
        ELOG("Unknown Data found");
        return EXIT_FAILURE;
    }


    // Try to delete it
    delete_tree(first);



    return EXIT_SUCCESS;
}
