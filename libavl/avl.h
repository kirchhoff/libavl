/*
 *   Libavl is a library to manage AVL structure to store and organize
 *   everykind of data. You just need to implement function to compare,
 *   to desallocate and to print your structure.
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
 * \file avl.h
 * \author Adrien Oliva
 * \date May, 24th, 2011
 * \brief Generic AVL-tree library.
 * \version 1.0.0
 *
 * Implementation of an AVL tree to store generic data.
 * In computer science, an AVL tree is a self-balancing binary search tree,
 * and it was the first such data structure to be invented. In an AVL tree,
 * the heights of the two child subtrees of any node differ by at most one.
 * Lookup, insertion, and deletion all take \f$\mathcal{O}(\log n)\f$
 * time in both the average and worst cases, where \e n is the number of
 * nodes in the tree prior to the operation. Insertions and deletions may
 * require the tree to be rebalanced by one or more tree rotations.
 *
 * The AVL tree is named after its two Soviet inventors, G.M. Adelson-Velskii
 * and E.M. Landis, who published it in their 1962 paper "An algorithm for the
 * organization of information."
 *
 * The balance factor of a node is the height of its left subtree minus the
 * height of its right subtree (sometimes opposite) and a node with balance
 * factor 1, 0, or −1 is considered balanced. A node with any other balance
 * factor is considered unbalanced and requires rebalancing the tree. The
 * balance factor is either stored directly at each node or computed from the
 * heights of the subtrees.
 *
 * \section Usage Use of library
 *
 */
#ifndef __AVL_H__
#define __AVL_H__

#include "syslog.h"
#include <stddef.h>



/** \struct _node
 * \brief Node of a tree
 *
 * Structure that contain all data usefull to organize the tree
 */
struct _node {
        /** Size of subtree */
        unsigned height;
        /** Left son */
        struct _node *left;
        /** Right son */
        struct _node *right;
        /** Pointer to data stored in this node */
        void *data;
};

/**
 * \brief Pointer to the \c _node structure.
 */
typedef struct _node *node;

/**
 * \brief Tree structure wich contains all necessary element.
 */
typedef struct _tree {
        /** Number of element in tree */
        unsigned count;
        /** Pointer to the first node of tree */
        node root;
        /** \brief External function to compare data
         *
         * \param a Pointer to first element to compare
         * \param b Pointer to second element to compare
         *
         * \return 0 if a = b, positive if a > b and negative if a < b.
         *
         * \note \e You must implement this function. It is necessary for the library
         * to work and depends on your data you want to store.
         */
        int (* data_cmp) (void *, void *);
        /** \brief External function to print data.
         *
         * \param d Pointer to data to print.
         *
         * This function is usefull for debuging program.
         *
         * \note \e You must implement this function. It is necessary for the library
         * to work and depends on your data you want to store.
         */
        void (* data_print) (void *d);

        /** \brief External function to delete data.
         *
         * \param d Pointer to data to delete.
         *
         * This function is usefull for when you want to delete data from tree to prevent
         * memory leak.
         *
         * \note \e You must implement this function. It is necessary for the library
         * to work and depends on your data you want to store.
         */
        void (* data_delete) (void *d);
} tree;



/* ************************************************************************* *\
|*                      EXTERNAL FUNCTION                                    *|
\* ************************************************************************* */

/** \fn tree *init_dictionnary(int (*data_cmp)(void *, void *),
 *                             void (*data_print)(void *),
 *                             void (*data_delete)(void *));
 * \brief Initialize dictionnary.
 *
 * \return Pointer to new tree.
 *
 * \param data_cmp Function to compare data.
 * \param data_print Function to print data.
 * \param data_delete Function to delete data.
 *
 * This function return an initilized tree.
 *
 * \note By default, if you do not provide function usefull to the tree,
 * the LibAVL library uses its own function. As LibAVL does not know exactly
 * the structure and the definition of your data, result can not be as good
 * as expected. Details on these functions are given in the following.
 *
 * \section LibAVL internal data function
 *
 *    - Compare function: by default, the internal \c data_cmp function will
 *      return the difference between the two pointer given in arguments
 *
 *          return (int) ((ptrdiff_t) a - (ptrdiff_t) b);
 *
 *      The \c data_cmp function is really critical and guarantee efficiency of
 *      LibAVL.
 *    - Print function: by default, the internal \c data_print function will
 *      print the addresse contained in pointer in argument, in hexadecimal
 *
 *          printf("0x%08x\n", d);
 *
 *      Since \c data_print is mainly used as debug function to dump a complete
 *      tree, it is not the most important data function, but with the correct
 *      implementation, it could save lots of time and money when something
 *      went wrong.
 *    - Delete function: by default, the internal \c data_delete function will
 *      call \c free on the argument pointer. If your data is only a static
 *      structure or a simple type, this function is enough. But for bigger
 *      object like a string array, it is necessary to provide a new
 *      \c data_delete function to avoid memory leak.
 */
tree *init_dictionnary(int (*data_cmp)(void *, void *),
                       void (*data_print)(void *),
                       void (*data_delete)(void *));

/** \fn int insert_elmt(tree *t, void *data, size_t datasize);
 * \brief Insert new element in tree.
 *
 * \return Number of element inserted in tree.
 * \param t Pointer to tree.
 * \param data Pointer to data to add.
 * \param datasize Size of data to add.
 *
 * This function allocate a new memory space with the given size
 * and copy object pointed by \c data to the newly created space.
 */
unsigned int insert_elmt(tree *t, void *data, size_t datasize);

/** \fn void verif_tree(tree *t);
 * \brief Deffensive check if tree is a real AVL tree.
 *
 * \param t Pointer to tree.
 *
 * If tree is not an AVL tree, this function end on an assert.
 */
void verif_tree(tree *t);

/** \fn void delete_tree(tree *t);
 * \brief Deallocate all memory used by tree.
 *
 * \param t Pointer to tree to delete.
 */
void delete_tree(tree *t);

/** \fn void print_tree(tree *t);
 * \brief Use for debug only. Print all element in tree with function
 * \c data_print.
 *
 * \param t Pointer to tree.
 */
void print_tree(tree *t);

/** \fn void explore_tree(tree *t, void (*treatement)(void *, void *),
 *                              void *param);
 * \brief Execute function \c treatement on every node in tree.
 *
 * \param t Pointer to tree.
 * \param treatement Function to apply to each node.
 * \param param Pointer to extra data to pass to \c treatement function.
 *
 * This function goes thought the entire tree and, if \c n is the pointer
 * to the current node, call the function:
 *
 *      treatement(n, param);
 *
 */
void explore_tree(tree *t, void (*treatement)(void *, void *), void *param);

/** \fn explore_restrain_tree(tree *t, int (*check)(void *, void *),
 *                              void *param,
 *                              void *data_min, void *data_max);
 * \brief Execute function \c check on every node between \c data_min and
 * \c data_max.
 *
 * \return Accumulation of all return value of \c check function.
 * \param t Pointer to tree.
 * \param check Function apply on every node between \c data_min and
 * \c data_max
 * \param param Pointer to extra data to pass to \c check function.
 * \param data_min Pointer to the minimum element.
 * \param data_max Pointer to the maximum element.
 *
 * This function goes thought a part of tree bounded with \c data_min and
 * \c data_max, and if \c n is the pointer to the current node, it calls
 * the function:
 *
 *      accu += check(n, param);
 *
 * The value of \c accu is returned by \c explore_restrain_tree.
 */
int explore_restrain_tree(tree *t, int (*check)(void *, void *), void *param,
                                void *data_min, void *data_max);

/** \fn int is_present(tree *t, void *d);
 * \brief Function to check if a given data is present in tree.
 *
 * \return 1 if data is present, 0 if not.
 * \param t Pointer to tree.
 * \param d Pointer to data. Only field used in \c avl_data_cmp need
 * to be filled in \c d.
 */
int is_present(tree *t, void *d);

/** \fn void delete_node_min(tree *t);
 * \brief Delete minimum element of a tree.
 *
 * \param t Tree where minimum element will be deleted.
 */
void delete_node_min(tree *t);

/** \fn void delete_node(tree *t, void *data);
 * \brief Delete node n of tree.
 *
 * \param t Pointer to tree.
 * \param data Data to delete.
 */
void delete_node(tree *t, void *data);

/** \fn int get_data(tree *t, void *data, size_t data_size);
 * \brief Fill information pointed by data with the data stored in the tree.
 *
 * \return True if value pointed by data are relevant, false if not.
 *
 * \param t Pointer to tree.
 * \param data Data to retrieve. At the begining of the function, only
 * field used in \c avl_data_cmp must be filled.
 * \param data_size Size of data structure pointed by data.
 */
int get_data(tree *t, void *data, size_t data_size);

#endif
