/* SAVU Paul-Cristian - 311CD */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arbore_cuaternar.h"
#include "matrix.h"

int main(int argc, char *argv[]) {
    FILE *fin, *fout;

    // opens the PPM file for reading for the first task
    if (strcmp(argv[1], "-c1") == 0) {
        fin = fopen(argv[3], "rb");
        fout = fopen(argv[4], "w");

        char ppm_type[2];
        fscanf(fin, "%s", ppm_type);

        int width = 0, height = 0;
        fscanf(fin, "%d", &width);
        fscanf(fin, "%d", &height);

        int max_value;
        fscanf(fin, "%d", &max_value);

        char aux;
        fread(&aux, sizeof(char), 1, fin);

        // alocates memory for the pixel matrix
        Matrix **grid;
        grid = (Matrix **)malloc(height * sizeof(Matrix *));

        int i = 0, j = 0;
        for (i = 0; i < height; i++) {
            grid[i] = (Matrix *)malloc(width * sizeof(Matrix));
        }

        // reads the pixel matrix
        for (i = 0; i < height; i++) {
            for (j = 0; j < width; j++) {
                fread(&grid[i][j].red, sizeof(char), 1, fin);
                fread(&grid[i][j].green, sizeof(char), 1, fin);
                fread(&grid[i][j].blue, sizeof(char), 1, fin);
            }
        }

        // creates the root of the tree
        Tree qtree = createRoot(height);
        Tree node = qtree, parent = qtree;

        int factor = atoi(argv[2]);
        int ok = 1;
 
        // checks mean <= factor for the entire image
        if (matrix_score(grid, qtree->line, qtree->column, qtree->size, factor, node) == 1) {
            ok = 0;
        }
        // if mean > factor for the entire image
        if (ok == 1) {
            // creates the first level
            if (matrix_score(grid, qtree->line, qtree->column, qtree->size, factor, node) == 0) {
                createLevel(qtree);
                node = parent->left;
            }
            while (qtree->right->done == 0) {
                if (node->right != NULL && node->right->done == 1) {
                    node->done = 1;
                    if (node == parent->left) {
                        node = parent->mid_left;
                    } else if (node == parent->mid_left) {
                        node = parent->mid_right;
                    } else if (node == parent->mid_right) {
                        node = parent->right;
                    } else if (node == parent->right) {
                        node = parent;
                        parent = node->parent;
                        continue;
                    }
                }
                if (matrix_score(grid, node->line, node->column, node->size, factor, node) == 0) {
                    createLevel(node);
                    parent = node;
                    node = parent->left;
                    continue;
                } else {
                    node->done = 1;
                    if (parent->mid_left->done == 0) {
                        node = parent->mid_left;
                        continue;
                    }
                    if (parent->mid_right->done == 0) {
                        node = parent->mid_right;
                        continue;
                    }
                    if (parent->right->done == 0) {
                        node = parent->right;
                        continue;
                    }
                    node = parent;
                    parent = node->parent;
                }
            }
        }
        updateHeight(qtree, 1);

        // writes the number of levels in the tree
        int depth = maxHeight(qtree);
        fprintf(fout, "%d\n", depth);

        // writes the number of zones which have mean <= factor
        int leaves = countLeaves(qtree);
        fprintf(fout, "%d\n", leaves);

        // writes the dimension of the biggest area which was not split
        int level = maxHeight(qtree) + 1;
        highestLeafLevel(qtree, &level);
        int dimension = width;
        while (level > 1) {
            dimension = dimension / 2;
            level--;
        }
        fprintf(fout, "%d\n", dimension);

        // closes the files and deallocates all memory
        fclose(fin);
        fclose(fout);
        freeTree(qtree);
        for (i = 0; i < height; i++) {
            free(grid[i]);
        }
        free(grid);
        return 0;
    }

    // task 2
    if (strcmp(argv[1], "-c2") == 0) {
        fin = fopen(argv[3], "rb");
        fout = fopen(argv[4], "wb");

        char ppm_type[2];
        fscanf(fin, "%s", ppm_type);

        int width = 0, height = 0;
        fscanf(fin, "%d", &width);
        fscanf(fin, "%d", &height);

        int max_value;
        fscanf(fin, "%d", &max_value);

        char test;
        fread(&test, sizeof(char), 1, fin);

        // alocates memory for the pixel matrix
        Matrix **grid;
        grid = (Matrix **)malloc(height * sizeof(Matrix *));

        int i = 0, j = 0;
        for (i = 0; i < height; i++) {
            grid[i] = (Matrix *)malloc(width * sizeof(Matrix));
        }

        // reads the pixel matrix
        for (i = 0; i < height; i++) {
            for (j = 0; j < width; j++) {
                fread(&grid[i][j].red, sizeof(char), 1, fin);
                fread(&grid[i][j].green, sizeof(char), 1, fin);
                fread(&grid[i][j].blue, sizeof(char), 1, fin);
            }
        }

        // creates the root of the tree
        Tree qtree = createRoot(height);
        Tree node = qtree, parent = qtree;

        int factor = atoi(argv[2]);
        int ok = 1;
 
        // checks mean <= factor for the entire image
        if (matrix_score(grid, qtree->line, qtree->column, qtree->size, factor, node) == 1) {
            ok = 0;
        }
        // if mean > factor for the entire image
        if (ok == 1) {
            // creates the first level
            if (matrix_score(grid, qtree->line, qtree->column, qtree->size, factor, node) == 0) {
                createLevel(qtree);
                node = parent->left;
            }
            while (qtree->right->done == 0) {
                if (node->right != NULL && node->right->done == 1) {
                    node->done = 1;
                    if (node == parent->left) {
                        node = parent->mid_left;
                    } else if (node == parent->mid_left) {
                        node = parent->mid_right;
                    } else if (node == parent->mid_right) {
                        node = parent->right;
                    } else if (node == parent->right) {
                        node = parent;
                        parent = node->parent;
                        continue;
                    }
                }
                if (matrix_score(grid, node->line, node->column, node->size, factor, node) == 0) {
                    createLevel(node);
                    parent = node;
                    node = parent->left;
                    continue;
                } else {
                    
                    node->done = 1;
                    if (parent->mid_left->done == 0) {
                        node = parent->mid_left;
                        continue;
                    }
                    if (parent->mid_right->done == 0) {
                        node = parent->mid_right;
                        continue;
                    }
                    if (parent->right->done == 0) {
                        node = parent->right;
                        continue;
                    }
                    node = parent;
                    parent = node->parent;
                }
            }
        }
        
        // prints the height to the file
        fwrite(&height, 1, sizeof(unsigned int), fout);

        updateHeight(qtree, 1);

        int index, check;
        
        for (int index = 1; index <= maxHeight(qtree); index++) {
            check = 0;
            level_traversal(qtree, index, check, fout);
        }

        // closes the files and deallocates all memory
        fclose(fin);
        fclose(fout);
        freeTree(qtree);
        for (i = 0; i < height; i++) {
            free(grid[i]);
        }
        free(grid);
        return 0;
    }

    // task 3 - incomplete
    if (strcmp(argv[1], "-d") == 0) {
        fin = fopen(argv[2], "rb");
        fout = fopen(argv[3], "w");

        unsigned int dimension = 0;
        fread(&dimension, sizeof(unsigned int), 1, fin);
        return 0;
    }
}