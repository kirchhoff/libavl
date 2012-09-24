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

int count_treat(void *n, void *param)
{
    struct _tree_data *data = (struct _tree_data *) n;

    if (param != NULL) {
        *((unsigned int *) param) += (unsigned) data->value;
    }

    return 1;
}

int main(int argc, char *argv[])
{
    tree *first = NULL;
    struct _tree_data data[MAX_ELEMENT];
    struct _tree_data tmp_elmnt;
    struct _tree_data node_min;
    struct _tree_data node_max;
    unsigned int result;
    unsigned int element_in_tree = 0;
    int i = 0;
    unsigned int r = 0;
    int return_value = 0;
    int count = 0;


    (void) argc;
    (void) argv;

    unsigned long rand_seed = (unsigned long) time(NULL);
    ILOG("Random seed: %lu", rand_seed);
    srand(rand_seed);

    node_min.key = rand();
    node_max.key = 0;
    while (node_max.key < node_min.key)
        node_max.key = rand();

    for (i = 0; i < MAX_ELEMENT; i++) {
        data[i].key = rand();
        data[i].value = 1;
        if (    (data[i].key < node_max.key)
            &&  (data[i].key > node_min.key)
           )
            count++;
    }

    // explore tree on a NULL tree
    return_value = explore_restrain_tree(first, count_treat, &r, &node_min, &node_max);
    if (r != 0 || return_value != 0) {
        ELOG("Wrong result on NULL tree");
        return EXIT_FAILURE;
    }

    // Try to allocate a new tree.
    first = init_dictionnary(data_cmp, data_print, data_delete);
    if (first == NULL) {
        ELOG("Init dictionnary error");
        return EXIT_FAILURE;
    }

    // explore tree on an empty tree
    return_value = explore_restrain_tree(first, count_treat, &r, &node_min, &node_max);
    if (r != 0 || return_value != 0) {
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

    return_value = explore_restrain_tree(first, count_treat, &r, &node_min, &node_max);
    if (r != (unsigned) return_value) {
        ELOG("Wrong return param");
        return EXIT_FAILURE;
    }
    if (return_value != count) {
        ELOG("Wrong number of detected element in tree");
        return EXIT_FAILURE;
    }

    // Try to delete it
    delete_tree(first);

    return EXIT_SUCCESS;
}
