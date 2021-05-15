/**
 * SD, 2020
 * 
 * Lab #8, Binary Tree
 * 
 * Bonus
 */

#include "binary_tree.h"

int main(void)
{
	b_tree_t *tree = b_tree_create(sizeof(int));
    for (unsigned int i = 1; i <= 3; i++) {
    	b_tree_insert(tree, &i);
    }
	b_node_t *node, *up = NULL;
	node = tree->root;
	while (node != NULL) {
    	if (node->left != NULL) {
        b_node_t *left = node->left;
        node->left = up;
        up = node;
        node = left;
    } else if (node->right != NULL) {
        b_node_t *right = node->right;
        node->left = up;
        node->right = NULL;
        up = node;
        node = right;
    } else {
        if (up == NULL) {
            free(node);
            node = NULL;
        }
        while (up != NULL) {
            free(node);
            if (up->right != NULL) {
                node = up->right;
                up->right = NULL;
                break;
            } else {
                node = up;
                up = up->left;
            }
        }
    }
}
	return 0;
}
