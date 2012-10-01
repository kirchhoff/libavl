#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

#define MAX_ELEMENT 10000

int main(int argc, char *argv[])
{
    tree *first = NULL;
    struct _tree_data data[MAX_ELEMENT];
    struct _tree_data look_for_data;
    unsigned int result;
    int bool_result;
    unsigned int element_in_tree = 0;
    int i = 0;

    (void) argc;
    (void) argv;

    unsigned long rand_seed = (unsigned long) time(NULL);
    ILOG("Random seed: %lu", rand_seed);
    srand(rand_seed);

    for (i = 0; i < MAX_ELEMENT; i++) {
        data[i].key = rand();
        data[i].value = rand();
    }


    verif_tree(first);

    // Get data on non existing tree
    for (i = MAX_ELEMENT - 1; i >= 0; i--) {
        look_for_data.key = data[i].key;
        bool_result = get_data(first, &(look_for_data), sizeof(struct _tree_data));
        if (bool_result) {
            ELOG("Data found");
            return EXIT_FAILURE;
        }
    }

    // Try to allocate a new tree.
    first = init_dictionnary(data_cmp, data_print, data_delete, NULL);
    if (first == NULL) {
        ELOG("Init dictionnary error");
        return EXIT_FAILURE;
    }

    // Get data on empty tree
    for (i = MAX_ELEMENT - 1; i >= 0; i--) {
        look_for_data.key = data[i].key;
        bool_result = get_data(first, &(look_for_data), sizeof(struct _tree_data));
        if (bool_result) {
            ELOG("Data found");
            return EXIT_FAILURE;
        }
    }

    // Add data
    verif_tree(first);
    for (i = 0; i < MAX_ELEMENT; i++) {
        look_for_data.key = data[i].key;
        if (!is_present(first, &(look_for_data))) {
            element_in_tree++;
        }
        result = insert_elmt(first, &(data[i]), sizeof(struct _tree_data));
        if (result != element_in_tree) {
            ELOG("Wrong result of inserted element");
            return EXIT_FAILURE;
        }
        verif_tree(first);
    }

    // Get data
    for (i = MAX_ELEMENT - 1; i >= 0; i--) {
        look_for_data.key = data[i].key;
        bool_result = get_data(first, &(look_for_data), sizeof(struct _tree_data));
        if (!bool_result) {
            ELOG("Data not found");
            return EXIT_FAILURE;
        }
        if (        look_for_data.key != data[i].key
                &&  look_for_data.value != data[i].value) {
            ELOG("Not the good data retrieve.");
            return EXIT_FAILURE;
        }
        verif_tree(first);
    }


    // Try to delete it
    delete_tree(first);



    return EXIT_SUCCESS;
}
