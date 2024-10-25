/* SAVU Paul-Cristian - 311CD */

typedef struct node {
    unsigned char R, G, B; // red, green, blue components
    unsigned char type; // 1 - leaf, 0 - internal node
    int done;
    int height;
    int isRoot;
    int line, column, size;
    struct node *parent;
    struct node* left;
    struct node* mid_left;
    struct node* mid_right;
    struct node* right;
} TreeNode, *Tree;

typedef struct matrix {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} Matrix;

// creates the root of the tree
Tree createRoot(int height) {
    Tree root = malloc(sizeof(TreeNode));
    root->done = 0;
    root->height = 0;
    root->isRoot = 1;
    root->line = 0;
    root->column = 0;
    root->size = height;
    root->parent = NULL;
    root->left = NULL;
    root->mid_left = NULL;
    root->mid_right = NULL;
    root->right = NULL;
    return root;
}

// creates nodes for the tree
Tree createTree(Tree parent) {
    Tree root = malloc(sizeof(TreeNode));
    root->done = 0;
    root->height = 0;
    root->isRoot = 0;
    root->line = 0;
    root->column = 0;
    root->size = (parent->size) / 2;
    root->parent = parent;
    root->left = NULL;
    root->mid_left = NULL;
    root->mid_right = NULL;
    root->right = NULL;
    return root;
}

// creates 4 children for root
void createLevel(Tree root) {
    root->left = createTree(root);
    root->mid_left = createTree(root);
    root->mid_right = createTree(root);
    root->right = createTree(root);

    // for root->left
    root->left->line = root->line;
    root->left->column = root->column;

    // for root->mid_left
    root->mid_left->line = root->line;
    root->mid_left->column = root->column + root->mid_left->size;

    // for root->mid_right
    root->mid_right->line = root->line + root->mid_right->size;
    root->mid_right->column = root->column + root->mid_right->size;

    // for root->right
    root->right->line = root->line + root->right->size;
    root->right->column = root->column;
}

// determines the maximum of 4 values
int maximum(int a, int b, int c, int d) {
    if (a >= b && a >= c && a >= d) {
        return a;
    }
    if (b >= a && b >= c && b >= d) {
        return b;
    }
    if (c >= a && c >= b && c >= d) {
        return c;
    }
    if (d >= a && d >= b && d >= c) {
        return d;
    }
}

// number of levels in the tree
int maxHeight(Tree root) {
    if (root == NULL) {
        return 0;
    } else {
        int l_height = maxHeight(root->left);
        int ml_height = maxHeight(root->mid_left);
        int mr_height = maxHeight(root->mid_right);
        int r_height = maxHeight(root->right);

        return maximum(l_height, ml_height, mr_height, r_height) + 1;
    }
}

// number of leaves in the tree
int countLeaves(Tree root) {
    if (root == NULL) {
        return 0;
    }
    if (root->left == NULL) {
        return 1;
    } else {
        return countLeaves(root->left) +
               countLeaves(root->mid_left) +
               countLeaves(root->mid_right) +
               countLeaves(root->right);
    }
}

// updates the height of every node in the tree
void updateHeight(Tree root, int height) {
    if (root == NULL) {
        return;
    } else {
        root->height = height;
        updateHeight(root->left, 1 + height);
        updateHeight(root->mid_left, 1 + height);
        updateHeight(root->mid_right, 1 + height);
        updateHeight(root->right, 1 + height);
    }
}

// gets the level of the leaf closest to the root
void highestLeafLevel(Tree root, int *level) {
    if (root != NULL) {
        if (root->left == NULL && root->height < *level) {
            *level = root->height;
        }
        highestLeafLevel(root->left, level);
        highestLeafLevel(root->mid_left, level);
        highestLeafLevel(root->mid_right, level);
        highestLeafLevel(root->right, level);
    }
}

// level traversal for the quaternary tree
void level_traversal(Tree root, int level, int check, FILE* fout) {
    if (root == NULL) {
        return;
    }
    if (level == maxHeight(root)) {
        check = 1;
    }
    if (level == 1) {
        if (check == 1) {
            root->type = 1;
            fwrite(&root->type, 1, sizeof(unsigned char), fout);
            fwrite(&root->R, 1, sizeof(unsigned char), fout);
            fwrite(&root->G, 1, sizeof(unsigned char), fout);
            fwrite(&root->B, 1, sizeof(unsigned char), fout);
        } else {
            root->type = 0;
            fwrite(&root->type, 1, sizeof(unsigned char), fout);
        }
        return;
    }
    level_traversal(root->left, level - 1, check, fout);
    level_traversal(root->mid_left, level - 1, check, fout);
    level_traversal(root->mid_right, level - 1, check, fout);
    level_traversal(root->right, level - 1, check, fout);
}

// deallocates the memory of the tree
void freeTree(Tree root) {
    if (root == NULL) {
        return;
    }
    freeTree(root->left);
    freeTree(root->mid_left);
    freeTree(root->mid_right);
    freeTree(root->right);
    free(root);
}