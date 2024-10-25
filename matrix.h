/* SAVU Paul-Cristian - 311CD */

/*
    verifies the score of the given matrix
*/
int matrix_score(Matrix **grid, int line, int col, int height, int factor, Tree node) {
    unsigned long long red = 0, green = 0, blue = 0;
    int i = 0, j = 0;
    int aux1 = 0, aux2 = 0;
    for (i = line; aux1 < height; i++) {
        for (j = col; aux2 < height; j++) {
            red = red + grid[i][j].red;
            green = green + grid[i][j].green;
            blue = blue + grid[i][j].blue;
            aux2++;
        }
        aux2 = 0;
        aux1++;
    }

    // average colour
    red = red / (height * height);
    green = green / (height * height);
    blue = blue / (height * height);

    // similarity score
    unsigned long long mean = 0;
    aux1 = aux2 = 0;
    for (i = line; aux1 < height; i++) {
        for (j = col; aux2 < height; j++) {
            mean = mean + (red - grid[i][j].red) * (red - grid[i][j].red) +
                   (green - grid[i][j].green) * (green - grid[i][j].green) +
                   (blue - grid[i][j].blue) * (blue - grid[i][j].blue);
            aux2++;
        }
        aux2 = 0;
        aux1++;
    }
    int divisor = height * height;
    mean = mean / (3 * divisor);
    if (mean <= factor) {
        node->R = red;
        node->G = green;
        node->B = blue;
        return 1;
    } else {
        return 0;
    }
}