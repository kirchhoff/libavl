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

void data_copy(void *src, void *dst)
{
    *((int *) dst) = *((int *) src);
}

int main(int argc, char *argv[])
{
    tree *first = NULL;
    int data;
    int get_data_result = 0;
    unsigned int result;

    (void) argc;
    (void) argv;

    unsigned long rand_seed = (unsigned long) time(NULL);
    ILOG("Random seed: %lu", rand_seed);
    srand(rand_seed);
    // Try to allocate a new tree.
    first = init_dictionnary(data_cmp, data_print, data_delete, data_copy);
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

    // Check value of element
    get_data_result = data;
    if (!get_data(first, &get_data_result, sizeof(int))) {
        ELOG("Wrong get data result");
        return EXIT_FAILURE;
    }

    if (data != get_data_result) {
        ELOG("Wrong data stored");
        return EXIT_FAILURE;
    }

    // Insert the same element
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

    // Check value of element
    get_data_result = data;
    if (!get_data(first, &get_data_result, sizeof(int))) {
        ELOG("Wrong get data result");
        return EXIT_FAILURE;
    }

    if (data != get_data_result) {
        ELOG("Wrong data stored");
        return EXIT_FAILURE;
    }

    // Try to delete it
    delete_tree(first);



    return EXIT_SUCCESS;
}
