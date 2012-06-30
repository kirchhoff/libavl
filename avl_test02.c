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

    srand(time(NULL));
    // Try to allocate a new tree.
    first = init_dictionnary(data_cmp, data_print, data_delete);
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


    // Try to delete it
    delete_tree(first);



    return EXIT_SUCCESS;
}
