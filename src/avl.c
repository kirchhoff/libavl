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
 * \file avl.c
 * \author Adrien Oliva
 * \date May, 24th, 2011
 * \brief Generic AVL-tree library.
 * \version 0.9.1
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
 * Library needs implementation of two function
 * \arg \c \b avl_data_cmp: this function is used to compared data stored in tree.
 * \arg \c \b avl_data_print: this function is used only for debug to print tree.
 * \arg \c \b avl_data_delete: this function is used to delete data stored in tree.
 *
 * To create a new tree, first use \c \b init_dictionnary function. It return
 * a pointer to a tree structure.
 *
 * To add element in tree, use \c \b insert_elmt with a pointer to data to add.
 *
 * To get data stored in the tree, use \c \b get_data with a pointer to data to
 * look for with only key data fill in the structure.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "avl.h"


/** \fn int is_present_recur(node n, void *d);
 * \brief Recursive function to check if a given data is present in tree.
 *
 * \return 1 if data is present, 0 if not.
 * \param n Node of subtree to analyze.
 * \param d Pointer to data.
 *
 * \warning If you use this function you probably make a mistake.
 */
int is_present_recur(node n, void *d)
{
    int cmp = 0;

    // Prevent analyze of a Null node
    if (n == NULL)
        return 0;

    // Compare data
    cmp = avl_data_cmp(n->data, d);

    if (cmp == 0)
        // Node found, return true
        return 1;
    else if (cmp > 0)
        // Current node is higher than data to look for,
        // need to go to left subtree.
        return is_present_recur(n->left, d);
    else
        // Current node is smaller than data to look for,
        // need to go to right subtree.
        return is_present_recur(n->right, d);
}

/** Use for debug only. Print recursive level of inserted element */
int level_insert = 0;

/** \fn int height_tree(node tree);
 * \brief Give the height of tree.
 *
 * \return Height of tree
 * \param tree Root of tree to analyze
 *
 * If there is no son, height of node is 1. Else, the height is maximum
 * height of subtrees plus 1.
 *
 * \warning If you use this function you probably make a mistake.
 */
int height_tree(node tree)
{
    if (tree == NULL)
        return 0;

    return tree->height;
}

/** \fn void adjust_tree_height(node tree);
 * \brief Update height field of tree.
 *
 * \param tree Calculate new height of tree pointed by \c tree.
 *
 * For the height calculation rules, see \c height_tree function.
 *
 * \warning If you use this function you probably make a mistake.
 */
void adjust_tree_height(node tree)
{
    int h1;
    int h2;

    h1 = height_tree(tree->left);
    h2 = height_tree(tree->right);

    if (h1 > h2)
        tree->height = h1 + 1;
    else
        tree->height = h2 + 1;
}

/** \fn node rotate_tree_right(node tree);
 * \brief Proceed right rotation to tree pointed by \c tree.
 *
 * \return New root of right rotated tree.
 * \param tree Pointer to root of tree.
 *
 * \warning If you use this function you probably make a mistake.
 */
node rotate_tree_right(node tree)
{
    node temp = tree->left;
    tree->left = temp->right;
    adjust_tree_height(tree);
    temp->right = tree;
    adjust_tree_height(temp);
    return temp;
}

/** \fn node rotate_tree_left(node tree);
 * \brief Proceed left rotation to tree pointed by \c tree.
 *
 * \return New root of left rotated tree.
 * \param tree Pointer to root of tree.
 *
 * \warning If you use this function you probably make a mistake.
 */
node rotate_tree_left(node tree)
{
    node temp = tree->right;
    tree->right = temp->left;
    adjust_tree_height(tree);
    temp->left = tree;
    adjust_tree_height(temp);
    return temp;
}


/** \fn node equi_left(node tree);
 * \brief Balance left tree.
 *
 * \return New root of left-balanced tree.
 * \param tree Pointer to root of tree.
 *
 * This function make rotation and update height if necessary.
 *
 * \warning If you use this function you probably make a mistake.
 */
node equi_left(node tree)
{

    node son = tree->left;

    DLOG("height tree: tree(%d) | left (%d) | right (%d) | son (%d)",
            height_tree(tree),
            height_tree(tree->left),
            height_tree(tree->right),
            height_tree(son));
    if (height_tree(son) > height_tree(tree->right) + 1) {
        if (height_tree(son->right) > height_tree(son->left)) {
            DLOG("Need rotate left");
            tree->left = rotate_tree_left(tree->left);
        }
        DLOG("Need rotate right");
        tree = rotate_tree_right(tree);
    } else {
        DLOG("No rotate");
        adjust_tree_height(tree);
    }
    return tree;
}

/** \fn node equi_right(node tree);
 * \brief Balance right tree.
 *
 * \return New root of right-balanced tree.
 * \param tree Pointer to root of tree.
 *
 * This function make rotation and update height if necessary.
 *
 * \warning If you use this function you probably make a mistake.
 */
node equi_right(node tree)
{
    node son = tree->right;

    if (height_tree(son) > height_tree(tree->left) + 1) {
        if (height_tree(son->left) > height_tree(son->right))
            tree->right = rotate_tree_right(tree->right);
        tree = rotate_tree_left(tree);
    } else {
        adjust_tree_height(tree);
    }
    return tree;
}


/** \fn int delete_node_min_recur(node *n);
 * \brief Recursive deletion of minimum element.
 *
 * \return True if element is deleted, false if not.
 * \param n Root of tree where minimum element must be deleted.
 * 
 * \warning If you use this function you probably make a mistake.
 */
int delete_node_min_recur(node *n)
{
    node aux = NULL;
    int result;

    if (*n == NULL)
        return 0;

    if ((*n)->left == NULL) {
        // No node in left subtree, this means that the current node
        // is the minimum node stored in tree.
        aux = *n;
        *n = aux->right;
        avl_data_delete(aux->data);
        free(aux);
        return 1;
    } else {
        // not the minimum, go deep
        result = delete_node_min_recur(&((*n)->left));
        // balance resulting tree
        *n = equi_right(*n);
    }

    return result;
}

/** \fn node delete_node_recur(node *root, void *data);
 * \brief Recursive deletion of the a node.
 *
 * \param root Pointer of pointer to subtree.
 * \param data Data to delete. Only field used in \c avl_data_cmp
 * must be filled.
 * \return True if node is deleted, false else.
 * 
 * \warning If you use this function you probably make a mistake.
 */
int delete_node_recur(node *root, void *data)
{
    int cmp = 0;
    int result = 0;
    node aux = NULL;

    if (*root == NULL) {
        WLOG("Node does not exist");
        return 0;
    }

    cmp = avl_data_cmp(data, (*root)->data);
    if (cmp == 0) {
        // Current node is the node to delete.
        if ((*root)->right == NULL) {
            // simple deletion because there is no right subtree.
            // attach the left subtree instead of the deleted node
            aux = *root;
            *root = (*root)->left;

            // release memory used in node.
            avl_data_delete(aux->data);
            free(aux);
        } else {
            // There is a right subtree.
            // swap minimun element of right subtree and
            // the deleted data, efectively delete data
            // and re balance right subtree.
            void *d;
            node temp = (*root)->right;

            // look for the minimum element of right subtree.
            while (temp->left != NULL)
                temp = temp->left;

            // swap data
            d = (*root)->data;
            (*root)->data = temp->data;
            temp->data = d;

            // delete minimum node.
            delete_node_min_recur(&((*root)->right));
            // rebalance subtree.
            *root = equi_left(*root);
        }
        return 1;
    } else if (cmp > 0) {
        // current node is smaller than node to delete
        // go down into right subtree.
        result = delete_node_recur(&((*root)->right), data);
        // rebalance subtree.
        *root = equi_left(*root);
    } else {
        // current node is higher than node to delete
        // go down into left subtree.
        result = delete_node_recur(&((*root)->left), data);
        // rebalance subtree.
        *root = equi_right(*root);
    }

    return result;
}

/** \fn int insert_elmt_recur(node *tree, node add_node);
 * \brief Recursive function too add element in tree.
 *
 * \return Number of element inserted.
 * \param tree Root of tree where element must be inserted.
 * \param add_node Element to be added in tree.
 *
 * \warning If you use this function you probably make a mistake.
 */
int insert_elmt_recur(node *tree, node add_node) 
{
    int present = 0; // 1 means that data already present
    int cmp;

    // Here is the end of a tree. It must create new node here
    DLOG("Insert %p at level %d", add_node, level_insert);
    if (*tree == NULL) {
        (*tree) = add_node;
        (*tree)->height = 1;
        (*tree)->left = NULL;
        (*tree)->right = NULL;

        return 0;
    }

    cmp = avl_data_cmp((*tree)->data, add_node->data);

    // Check if current node is the node you want to add
    if (cmp == 0)
        // node already exist
        return 1;

    if (cmp > 0) {
        // Current node is higher that node you want to add
        // Insert it on left subtree.
        DLOG("Down into left level %d", ++level_insert);
        present = insert_elmt_recur(&(*tree)->left, add_node);
        DLOG("Out of level %d", level_insert--);

        if (!present) {
            // node was really inserted, need to re-balance tree
            *tree = equi_left(*tree);
            return 0;
        } else
            // node not inserted in subtree
            return 1;
    } else {
        // Current node is smaller that node you want to add
        // Insert it on right subtree.
        DLOG("Down into right level %d", ++level_insert);
        present = insert_elmt_recur(&(*tree)->right, add_node);
        DLOG("Out of level %d", level_insert--);

        if (!present) {
            // node was really inserted, need to re-balance tree
            *tree = equi_right(*tree);
            return 0;
        } else
            // node not inserted in subtree
            return 1;
    }

}

/** \fn void verif_avl(node tree, int tree_min, int tree_max,
 *                      void *data_min, void *data_max);
 * \brief Recursive deffensive function to check if tree is an AVL tree.
 *
 * \param tree Pointer to root of tree.
 * \param tree_min Boolean must be true if \c tree is the minimum node.
 * \param tree_max Boolean must be true if \c tree is the maximum node.
 * \param data_min Pointer to the minimum element of sub-tree.
 * \param data_max Pointer to the maximum element of sub-tree.
 *
 * \warning If you use this function you probably make a mistake.
 */
void verif_avl(node tree,
        int tree_min,
        int tree_max,
        void *data_min,
        void *data_max)
{
    unsigned hg;
    unsigned hd;

    // Check order of data.
    if (tree_min && avl_data_cmp(tree->data, data_min) < 0) {
        DLOG("Tree->data (%d) < data_min (%d)",
                *((int *) tree->data),
                *((int *) data_min));
        exit(-1);
    }
    if (tree_max && avl_data_cmp(tree->data, data_max) > 0) {
        DLOG("Tree->data (%d) > data_min (%d)",
                *((int *) tree->data),
                *((int *) data_max));
        exit(-2);
    }

    // Check avl left subtree.
    if (tree->left != NULL) {
        verif_avl(tree->left,
                tree_min,
                1,
                data_min,
                tree->data);
        hg = tree->left->height;
    } else {
        hg = 0;
    }

    // Check avl right subtree.
    if (tree->right != NULL) {
        verif_avl(tree->right,
                1,
                tree_max,
                tree->data,
                data_max);
        hd = tree->right->height;
    } else {
        hd = 0;
    }


    // Check height consistency of each subtree
    if (hg <= hd) {
        if (!(hd + 1 == tree->height && hg + 2 >= tree->height)) {
            DLOG("(hg<hd) Error in tree height: hd %u | hg %u | tree->height %u",
                    hd, hg, tree->height);
            exit(-3);
        }
    } else {
        if (!(hg + 1 == tree->height && hd + 2 >= tree->height)) {
            DLOG("(hg>hd) Error in tree height: hd %u | hg %u | tree->height %u",
                    hd, hg, tree->height);
            exit(-4);
        }
    }
}

/** \fn void delete_tree_recur(node n);
 * \brief Recursively delete all node in tree.
 *
 * \param n Root node of tree to delete.
 *
 * \warning If you use this function you probably make a mistake.
 */
void delete_tree_recur(node n)
{
    if (n->left != NULL)
        delete_tree_recur(n->left);
    if (n->right != NULL)
        delete_tree_recur(n->right);

    avl_data_delete(n->data);
    free(n);
}

/** \fn void print_tree_recur(node t);
 * \brief Recursive function to print tree. Use for debug.
 *
 * \param t Pointer to root of tree.
 *
 * \warning If you use this function you probably make a mistake.
 */
void print_tree_recur(node t)
{
    if (t == NULL)
        return;

    // recursively print left subtree.
    print_tree_recur(t->left);
    {
        // print current node with debug information.
        unsigned i = 0;
        for (i = 0; i < t->height; i++)
            printf("            ");
        printf("[%d|%p]", t->height, t);
        avl_data_print(t->data);
        printf("\n");
    }
    // recursively print right subtree.
    print_tree_recur(t->right);
}

/** \fn void explore_tree_recur(node t, void (*treatement)(void *, void *),
 *                              void *param);
 * \brief Recursive exploration of tree.
 *
 * \param t Pointer to subtree.
 * \param treatement Function apply to each node of tree.
 * \param param Pointer to data to pass to \c treatement function.
 *
 * \warning If you use this function you probably make a mistake.
 */
void explore_tree_recur(node t, void (*treatement)(void *, void *), void *param)
{
    if (t == NULL)
        return;

    // recursively treat left subtree.
    explore_tree_recur(t->left, treatement, param);
    // treat current node.
    treatement(t->data, param);
    // recursively treat right subtree.
    explore_tree_recur(t->right, treatement, param);
}

/** \fn int explore_restrain_tree_recur(node t, int (*check)(void *, void *),
 *                                      void *param, void *data_min,
 *                                      void *data_max);
 * \brief Recursive and restrain exploration of tree.
 *
 * \return Accumulation of return value of \c check function.
 * \param t Pointer to root of tree.
 * \param check Function apply to each node of tree between \c data_min and
 * \c data_max.
 * \param param Pointer to data to pass to \c check function
 * \param data_min All treated node are greater than \c data_min
 * \param data_max All treated node are smaller than \c data_max
 *
 * \warning If you use this function you probably make a mistake.
 */
int explore_restrain_tree_recur(node t, int (*check)(void *, void *),
        void *param,
        void *data_min, void *data_max)
{
    if (t == NULL)
        return 0;

    if (avl_data_cmp(t->data, data_max) > 0)
        // current data is not in the asked range.
        return explore_restrain_tree_recur(t->left, check, param,
                                            data_min, data_max);
    else if (avl_data_cmp(t->data, data_min) < 0)
        // current data is not in the asked range.
        return explore_restrain_tree_recur(t->right, check, param,
                                            data_min, data_max);
    else {
        // current data is in the range.
        int accu = 0;
        // treat recursively left subtree.
        accu += explore_restrain_tree_recur(t->left, check, param,
                                            data_min, data_max);
        // treat current node.
        accu += check(t->data, param);
        // treat recursively right subtree.
        accu += explore_restrain_tree_recur(t->right, check, param,
                                            data_min, data_max);
        return accu;
    }
}


/** \fn int get_data_recur(node n, void *data, size_t data_size)
 * \brief Recursively get of a single data.
 *
 * \param n Root of tree to analyze.
 * \param data Pointer to the asked data. At the begining of the function,
 * only field used in \c avl_data_cmp must be filled, at the end (and if
 * data exist in tree), all filled will be filled.
 * \param data_size Size of the data structure (need to copy data).
 * \return 1 if data was found, 0 if not.
 *
 * \warning If you use this function, you probably make a mistake.
 */
int get_data_recur(node n, void *data, size_t data_size)
{
    int cmp = avl_data_cmp(n->data, data);

    if (n == NULL)
        return 0;

    if (cmp == 0) {
        // Current node is the good node, copy it.
        memcpy(data, n->data, data_size);
        return 1;
    } else if (cmp > 0) {
        // Need to go deep in the left subtree.
        return get_data_recur(n->left, data, data_size);
    } else {
        // Need to go deep in the right subtree.
        return get_data_recur(n->right, data, data_size);
    }

}

/* ************************************************************************* *\
|*                      EXTERNAL FUNCTION                                    *|
\* ************************************************************************* */

/** \fn tree *init_dictionnary();
 * \brief Initialize dictionnary.
 *
 * \return Pointer to new tree.
 *
 * This function return an initilized tree.
 */
tree *init_dictionnary()
{
    DLOG("Create new tree");

    // New tree allocation
    tree *t = malloc(sizeof(tree));

    // Initialized field
    t->count = 0;
    t->root = NULL;

    return t;
}

/** \fn int insert_elmt(tree *t, void *data, size_t data_size);
 * \brief Insert new element in tree.
 *
 * \return Number of element inserted in tree.
 * \param t Pointer to tree.
 * \param data Pointer to data to add.
 */
int insert_elmt(tree *t, void *data, size_t datasize)
{
    node too_add = NULL;
    int present = 0;

    // check if data is already present
    if (is_present(t, data))
        return t->count;

    // Allocate memory for the new data and copy data.
    too_add = malloc(sizeof(struct _node));
    too_add->data = malloc(datasize);
    memcpy(too_add->data, data, datasize);
    too_add->height = 0;
    too_add->left = too_add->right = NULL;

    // recursively insert data in tree.
    present = insert_elmt_recur(&(t->root), too_add);

    // increment counter of element if so.
    if (!present)
        return ++t->count;
    else
        return t->count;
}


/** \fn void verif_tree(tree *t);
 * \brief Deffensive check if tree is a real AVL tree.
 *
 * \param t Pointer to tree.
 *
 * If tree is not an AVL tree, this function end on an assert.
 */
void verif_tree(tree *t)
{
    if (t == NULL)
        return;
    if (t->root == NULL)
        return;

    // recursively check of avl tree.
    verif_avl(t->root, 0, 0, t->root->data, t->root->data);
}

/** \fn void delete_tree(tree *t);
 * \brief Deallocate all memory used by tree.
 *
 * \param t Pointer to tree to delete.
 */
void delete_tree(tree *t)
{
    if (t == NULL || t->root == NULL)
        return;

    delete_tree_recur(t->root);
    free(t);
}

/** \fn void print_tree(tree *t);
 * \brief Use for debug only. Print all element in tree with function
 * \c avl_data_print.
 *
 * \param t Pointer to tree.
 */
void print_tree(tree *t)
{
    if (t == NULL)
        return;
    if (t->root == NULL)
        return;

    // recursively print the tree.
    print_tree_recur(t->root);
}

/** \fn void explore_tree(tree *t, void (*treatement)(void *, void *),
 *                              void *param);
 * \brief Execute function \c treatement on every node in tree.
 *
 * \param t Pointer to tree.
 * \param treatement Function to apply to each node.
 * \param param Pointer to extra data to pass to \c treatement function.
 */
void explore_tree(tree *t, void (*treatement)(void *, void *), void *param)
{
    if (t == NULL)
        return;
    if (t->root == NULL)
        return;

    // recursively explore the whole tree.
    explore_tree_recur(t->root, treatement, param);
}

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
 */
int explore_restrain_tree(tree *t, int (*check)(void *, void *), void *param,
        void *data_min, void *data_max)
{
    if (t == NULL)
        return 0;
    if (t->root == NULL)
        return 0;

    // recursively explore part of tree.
    return explore_restrain_tree_recur(t->root, check, param, data_min, data_max);
}

/** \fn int is_present(tree *t, void *d);
 * \brief Function to check if a given data is present in tree.
 *
 * \return 1 if data is present, 0 if not.
 * \param t Pointer to tree.
 * \param d Pointer to data. Only field used in \c avl_data_cmp need
 * to be filled in \c d.
 */
int is_present(tree *t, void *d)
{
    if (t == NULL)
        return 0;

    // Return result of a recursive exploration
    return is_present_recur(t->root, d);
}

/** \fn void delete_node_min(tree *t);
 * \brief Delete minimum element of a tree.
 *
 * \param t Tree where minimum element will be deleted.
 */
void delete_node_min(tree *t)
{
    if (t == NULL || t->root == NULL)
        return;

    // go recursively in tree to delete minimum node
    if (delete_node_min_recur(&(t->root)))
        t->count--;
}

/** \fn void delete_node(tree *t, void *data);
 * \brief Delete node n of tree.
 *
 * \param t Pointer to tree.
 * \param data Data to delete.
 */
void delete_node(tree *t, void *data)
{
    if (t == NULL)
        return;
    if (t->root == NULL)
        return;
    // explore tree recursively to delete node
    if (delete_node_recur(&(t->root), data))
        t->count--;
}

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
int get_data(tree *t, void *data, size_t data_size)
{
    if (t == NULL)
        return 0;
    if (t->root == NULL)
        return 0;

    return get_data_recur(t->root, data, data_size);
}

