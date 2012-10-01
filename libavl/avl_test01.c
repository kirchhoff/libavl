#include <stdio.h>
#include <stdlib.h>

#include "syslog.h"
#include "avl.h"

int data_cmp(void *a, void *b)
{
    return (int) ((char *) a - (char *) b);
}

void data_print(void *d)
{
    printf("%p", d);
}

void data_delete(void *d)
{
    (void) d;
}

int main(int argc, char *argv[])
{
    tree *first = NULL;

    (void) argc;
    (void) argv;

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

    // Try to delete it
    delete_tree(first);

    // Try to delete a null tree
    delete_tree(NULL);


    return EXIT_SUCCESS;
}
