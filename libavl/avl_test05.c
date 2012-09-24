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

#define MAX_ELEMENT 10000

int main(int argc, char *argv[])
{
    tree *first = NULL;
    int data[MAX_ELEMENT];
    unsigned int result;
    unsigned int element_in_tree = 0;
    int i = 0;

    (void) argc;
    (void) argv;

    unsigned long rand_seed = (unsigned long) time(NULL);
    ILOG("Random seed: %lu", rand_seed);
    srand(rand_seed);

    for (i = 0; i < MAX_ELEMENT; i++) {
        data[i] = rand();
    }


    verif_tree(first);

    // Try to allocate a new tree.
    first = init_dictionnary(data_cmp, data_print, data_delete);
    if (first == NULL) {
        ELOG("Init dictionnary error");
        return EXIT_FAILURE;
    }

    // Add data
    verif_tree(first);
    for (i = 0; i < MAX_ELEMENT; i++) {
        if (!is_present(first, &(data[i]))) {
            element_in_tree++;
        }
        result = insert_elmt(first, &(data[i]), sizeof(int));
        if (result != element_in_tree) {
            ELOG("Wrong result of inserted element");
            return EXIT_FAILURE;
        }
        verif_tree(first);
    }

    // Delete data
    for (i = 0; i < MAX_ELEMENT; i++) {
        delete_node(first, &(data[i]));
        if (is_present(first, &(data[i]))) {
            ELOG("Data not deleted");
            return EXIT_FAILURE;
        }
        verif_tree(first);
    }


    // Try to delete it
    delete_tree(first);



    return EXIT_SUCCESS;
}
