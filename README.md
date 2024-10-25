# Image Compression Program

This program processes `.PPM` image files and performs specific compression tasks based on command-line arguments.

## Table of Contents
1. [Task 1: Compression with Matrix Score Check](#task-1-compression-with-matrix-score-check)
2. [Task 2: Compression Tree Formation and Binary Output](#task-2-compression-tree-formation-and-binary-output)
3. [Memory Management](#memory-management)

---

### Task 1: Compression with Matrix Score Check (`-c1`)

In Task 1, the program reads data from a `.PPM` file and stores it in a `Matrix` variable, which contains fields for red, green, and blue values. Each node in the quadtree has three fields: `line`, `column`, and `size`, allowing easy mapping between a node's position in the tree and its corresponding pixel area.

The function `matrix_score` checks if the mean value for a given submatrix is less than or equal to the compression factor. The process proceeds as follows:

1. **Initial Matrix Score Check**: If the score of the entire matrix is greater than the compression factor, the matrix is not divided further, and the required data is written to the output file.

2. **Recursive Division**: If the matrix can be divided, the process continues recursively until the right child of the root has its `done` field set to 1. A node's `done` field is set to 1 if all its descendants (submatrices) have been divided until their score is less than or equal to the compression factor. In other words, a node is marked as done if all its descendants have `done` set to 1.

3. **Division Process**: In each loop iteration, the children of a node are processed from left to right. If any child can still be divided, the algorithm traverses that child’s subtree and then moves to the next child. This is possible due to pointers to parent nodes. When `qtree->right->done` equals 1, the image is fully divided, and the quadtree is complete.

#### Output Functions
- **`maxheight`**: Calculates the number of levels in the quadtree.
- **`countLeaves`**: Returns the number of leaves, equivalent to the number of matrix regions with a mean value <= compression factor.
- **`highestLeafLevel`**: Finds the closest leaf to the root and stores its level in the `level` variable. By knowing the leaf's level and the image size, the size of the largest image region with a mean value <= compression factor can be determined through successive division by 2.

### Task 2: Compression Tree Formation and Binary Output (`-c2`)

In Task 2, the compression tree is formed following the steps from Task 1. The resulting tree structure is then written to a file in binary format.

1. **Binary Output**: The image size is first written to the file. The `level_traversal` function then performs a level-order traversal of the tree. Using the `check` variable, leaf nodes are assigned a `type` value of 1, while internal nodes are assigned a `type` value of 0. `level_traversal` writes this data to the output file.

---

### Memory Management

After completing both tasks, all allocated memory is freed, including the pixel matrix and the quadtree. The `freeTree` function handles the deallocation.

--- 

This program effectively compresses images by constructing a quadtree based on pixel similarity, resulting in a hierarchical structure that can be stored efficiently and used for further analysis or compression.

