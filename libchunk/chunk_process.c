#include "chunk.h"

#define NEIGHBOR_COUNT 18
#define PLACEHOLDER_BLOCK 4

int neighbor_check(
    char*** chunk, int width, int height, int depth,
    int x, int y, int z, char block) {
        int res = 0;
        int coords[NEIGHBOR_COUNT][3] = {
                            {x - 1, y, z}, {x + 1, y, z}, {x, y - 1, z}, {x, y + 1, z}, {x, y, z - 1}, {x, y, z + 1},
                            {x - 1, y - 1, z}, {x - 1, y + 1, z}, {x + 1, y - 1, z}, {x + 1, y + 1, z},
                            {x - 1, y, z - 1}, {x - 1, y, z + 1}, {x + 1, y, z - 1}, {x + 1, y, z + 1},
                            {x, y - 1, z - 1}, {x, y - 1, z + 1}, {x, y + 1, z - 1}, {x, y + 1, z + 1}
                            };

        for (int i = 0; i < NEIGHBOR_COUNT; i++) {
            if ((
                coords[i][0] >= 0 && coords[i][0] < width
                && coords[i][1] >= 0 && coords[i][1] < height
                && coords[i][2] >= 0 && coords[i][2] < depth)
                && chunk[coords[i][0]][coords[i][1]][coords[i][2]] == block) {
                res = 1;
                break;
            }
        }
        return res;
}

char*** chunk_shell(
    char*** chunk, int width, int height, int depth,
    char target_block, char shell_block) {
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                for (int k = 0; k < depth; k++) {
                    if (chunk[i][j][k] != target_block) {
                        if (neighbor_check(chunk, width, height, depth, i, j, k, target_block)) {
                            chunk_place_block(chunk, width, height, depth, i, j, k, PLACEHOLDER_BLOCK);
                        }
                    }
                }
            }
        }

        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                for (int k = 0; k < depth; k++) {
                    if (chunk[i][j][k] == PLACEHOLDER_BLOCK) {
                        chunk_place_block(chunk, width, height, depth, i, j, k, shell_block);
                    }
                }
            }
        }

        return chunk;
}

char*** chunk_fill_xz(
    char*** chunk, int width, int height, int depth,
    int x, int y, int z, char block) {
        if (x - 1 >= 0 && chunk[x - 1][y][z] == chunk[x][y][z]) {
            chunk_fill_xz(chunk, width, height, depth, x - 1, y, z, block);
        }
        if (x + 1 < width && chunk[x + 1][y][z] == chunk[x][y][z]) {
            chunk_fill_xz(chunk, width, height, depth, x + 1, y, z, block);
        }
        if (z - 1 >= 0 && chunk[x][y][z - 1] == chunk[x][y][z]) {
            chunk_fill_xz(chunk, width, height, depth, x, y, z - 1, block);
        }
        if (z + 1 < depth && chunk[x][y][z + 1] == chunk[x][y][z]) {
            chunk_fill_xz(chunk, width, height, depth, x, y, z + 1, block);
        }

        chunk_place_block(chunk, width, height, depth, x, y, z, block);
        return chunk;
}

char*** chunk_fill(
    char*** chunk, int width, int height, int depth,
    int x, int y, int z, char block) {
        if (x - 1 >= 0 && chunk[x - 1][y][z] == chunk[x][y][z]) {
            chunk_fill(chunk, width, height, depth, x - 1, y, z, block);
        }
        if (x + 1 < width && chunk[x + 1][y][z] == chunk[x][y][z]) {
            chunk_fill(chunk, width, height, depth, x + 1, y, z, block);
        }
        if (y - 1 >= 0 && chunk[x][y - 1][z] == chunk[x][y][z]) {
            chunk_fill(chunk, width, height, depth, x, y - 1, z, block);
        }
        if (y + 1 < height && chunk[x][y + 1][z] == chunk[x][y][z]) {
            chunk_fill(chunk, width, height, depth, x, y + 1, z, block);
        }
        if (z - 1 >= 0 && chunk[x][y][z - 1] == chunk[x][y][z]) {
            chunk_fill(chunk, width, height, depth, x, y, z - 1, block);
        }
        if (z + 1 < depth && chunk[x][y][z + 1] == chunk[x][y][z]) {
            chunk_fill(chunk, width, height, depth, x, y, z + 1, block);
        }

        chunk_place_block(chunk, width, height, depth, x, y, z, block);
        return chunk;
}
