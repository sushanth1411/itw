#include<stdio.h>
#include<stdlib.h>

#define MIN_DEGREE 3

struct BTreeNode {
    int *keys;
    struct BTreeNode **children;
    int n;
    int leaf;
};
  
struct BTreeNode *createNode(int leaf) {
    struct BTreeNode *node = (struct BTreeNode *)malloc(sizeof(struct BTreeNode));
    node->keys = (int *)malloc((2 * MIN_DEGREE - 1) * sizeof(int));
    node->children = (struct BTreeNode **)malloc((2 * MIN_DEGREE) * sizeof(struct BTreeNode *));
    node->n = 0;
    node->leaf = leaf;
    return node;
}

void insertNonFull(struct BTreeNode *root, int key) {
    int i = root->n - 1;
    if (root->leaf) {
        while (i >= 0 && key < root->keys[i]) {
            root->keys[i + 1] = root->keys[i];
            i--;
        }
        root->keys[i + 1] = key;
        root->n++;
    } else {
        while (i >= 0 && key < root->keys[i]) {
            i--;
        }
        if ((root->children[i + 1])->n == (2 * MIN_DEGREE - 1)) {
            splitChild(root, i + 1, root->children[i + 1]);
            if (key > root->keys[i + 1]) {
                i++;
            }
        }
        insertNonFull(root->children[i + 1], key);
    }
}

void splitChild(struct BTreeNode *parent, int index, struct BTreeNode *child) {
    struct BTreeNode *newChild = createNode(child->leaf);
    parent->children[index + 1] = newChild;
    parent->n++;
    int j;
    for (j = parent->n - 1; j > index; j--) {
        parent->keys[j] = parent->keys[j - 1];
    }
    parent->keys[index] = child->keys[MIN_DEGREE - 1];
    for (j = MIN_DEGREE; j < 2 * MIN_DEGREE - 1; j++) {
        newChild->keys[j - MIN_DEGREE] = child->keys[j];
    }
    if (!child->leaf) {
        for (j = MIN_DEGREE; j < 2 * MIN_DEGREE; j++) {
            newChild->children[j - MIN_DEGREE] = child->children[j];
        }
    }
    child->n = MIN_DEGREE - 1;
    newChild->n = MIN_DEGREE;
}

void inorder(struct BTreeNode *root) {
    int i;
    for (i = 0; i < root->n; i++) {
        if (!root->leaf) {
            inorder(root->children[i]);
        }
        printf("%d ", root->keys[i]);
    }
    if (!root->leaf) {
        inorder(root->children[i]);
    }
}

int main() {
    struct BTreeNode *root = createNode(1);
    insertNonFull(root, 89);
    insertNonFull(root, 78);
    insertNonFull(root, 8);
    insertNonFull(root, 19);
    insertNonFull(root, 20);
    insertNonFull(root, 33);
    insertNonFull(root, 56);
    insertNonFull(root, 44);
    printf("Inorder traversal: ");
    inorder(root);
    printf("\n");
    return 0;
}
