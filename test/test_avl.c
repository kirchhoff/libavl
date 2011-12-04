/*   
 *   Libavl is a library to manage AVL structure to store and organize
 *   every kind of data. You just need to implement function to compare,
 *   to desallocate and print your structure.
 *   
 *   Copyright (C) 2011 Adrien Oliva
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * \file test_avl.c
 * \author Adrien Oliva
 * \date May, 24th, 2011
 * \brief Generic AVL-tree library: test file.
 * \version 0.9
 *
 * Test of the implementation of an AVL tree to store generic data.
 */
#include "avl.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <assert.h>

#define DEBUG

int main(int argc, char **argv)
{
    int number_of_inserted_element;
    int *element;
    int idx;
    int count;
    tree *t;


    // initialized random value generator.
    srand(time(NULL));

    // argument checking
    if (argc != 2) {
        fprintf(stderr, "Not enough argument\n");
        return 1;
    }

    number_of_inserted_element = atoi(argv[1]);
    element = (int *) malloc(sizeof(int) * number_of_inserted_element);


    // Create new dictionnary
    t = init_dictionnary();
    if (t == NULL) {
        fprintf(stderr, "Cant initialized tree\n");
        goto error1;
    }

    // Insert element
    printf("Insert element in tree\n");
    count = 0;
    for (idx = 0; idx < number_of_inserted_element; idx++) {
        do {
            element[idx] = rand();
            if (is_present(t, (void *) &(element[idx])) == 0) {
                count = insert_elmt(t, (void *) &(element[idx]), sizeof(int));
                verif_tree(t);
                if (idx + 1 == count)
                    printf("[%d] Insert %d in tree\n", idx, element[idx]);
                else {
                    fprintf(stderr, "Cannot insert %d in tree\n", element[idx]);
                    goto error2;
                }
            } else {
                count = insert_elmt(t, (void *) &(element[idx]), sizeof(int));
                verif_tree(t);
                if (idx == count)
                    printf("Non insert %d in tree cause %d was already present\n", element[idx], element[idx]);
                else {
                    fprintf(stderr, "Insert %d but %d already present\n", element[idx], element[idx]);
                    goto error2;
                }
            }
        } while (idx + 1 != count);
    }
    printf("Complete insertion\n");

    // Check presence
    printf("Check presence of each element...");
    for (idx = 0; idx < number_of_inserted_element; idx++) {
        if (!is_present(t, &(element[idx]))) {
            fprintf(stderr, "Element not present\n");
            goto error2;
        }
    }
    printf(" done\n");

    // Deletion
    printf("Delete all element...");
    for (idx = 0; idx < number_of_inserted_element; idx++) {
        delete_node_min(t);
        verif_tree(t);
    }
    printf(" done\n");

    printf("Check non presence of each element...");
    for (idx = 0; idx < number_of_inserted_element; idx++) {
        if (is_present(t, &(element[idx]))) {
            fprintf(stderr, "Element present\n");
            goto error2;
        }
    }
    printf(" done\n");

    // Test of element deletion one-by-one
    printf("Reinsert all element\n");
    for (idx = 0; idx < number_of_inserted_element; idx++)
        insert_elmt(t, (void *) &(element[idx]), sizeof(int));
    printf("All element inserted\n");

    print_tree(t);

    printf("Delete all node...");
    for (idx = 0; idx < number_of_inserted_element; idx++) {
        delete_node(t, &(element[idx]));
        verif_tree(t);
    }
    printf(" done\n");

    printf("Check non presence of each element...");
    for (idx = 0; idx < number_of_inserted_element; idx++) {
        if (is_present(t, &(element[idx]))) {
            fprintf(stderr, "Element present\n");
            goto error2;
        }
    }
    printf(" done\n");

    // Print tree test
    printf("Reinsert all element\n");
    for (idx = 0; idx < number_of_inserted_element; idx++)
        insert_elmt(t, (void *) &(element[idx]), sizeof(int));
    printf("All element inserted\n");

    printf("Print the whole tree...\n");
    print_tree(t); 

    delete_tree(t);
    free(element);
    return 0;

error2:
    delete_tree(t);
error1:
    free(element);

    return 2;
}

int avl_data_cmp(void *a, void *b)
{
    return *((int *) a) -
            *((int *) b);
}

void avl_data_print(void *d)
{
    printf("%d", *((int *) d));
}

void avl_data_delete(void *d)
{
    int *dd = (int *) d;

    free(dd);
}
