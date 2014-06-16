/* Conway's Game of Life
 * /r/dailyprogrammer challenge 165
 * http://redd.it/271xyp
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char CELL_ON  = '#';
const char CELL_OFF = '.';

typedef struct {
    size_t height;
    size_t width;
    char *board;
} GameBoard;

FILE *filePointer(int argc, char* argv[]);
void solve(FILE* fp);
GameBoard init(FILE *fp, size_t width, size_t height);
void iterate(GameBoard *b);
void iterateN(GameBoard *b, size_t n);
void print(FILE* out, GameBoard board);
char *get(GameBoard b, size_t x, size_t y);
int numOnNeighbors(GameBoard b, size_t x, size_t y);

int main(int argc, char* argv[])
{
    FILE *fp = filePointer(argc, argv);
    if (fp == NULL) return 1;
    solve(fp);
    fclose(fp);
    return EXIT_SUCCESS;
}

void solve(FILE* fp)
{
    GameBoard b;
    size_t numIterations, width, height;

    fscanf(fp, "%zd %zd %zd\n", &numIterations, &width, &height);
    b = init(fp, width, height);

    iterateN(&b, numIterations);
    print(stdout, b);

    free(b.board);
}

GameBoard init(FILE *fp, size_t width, size_t height)
{
    size_t i;
    char c;
    GameBoard b = { .width = width, .height = height };
    b.board = malloc(width * height);
    for (i = 0, c = fgetc(fp); c != EOF; c = fgetc(fp))
        if (c == CELL_ON || c == CELL_OFF)
            b.board[i++] = c;
    return b;
}

void iterate(GameBoard *b)
{
    GameBoard newBoard = { .height = b->height, .width = b->width };
    newBoard.board = calloc(b->width * b->height, sizeof(*newBoard.board));
    size_t i, j, n;
    for (j = 0; j < b->height; ++j) {
        for (i = 0; i < b->width; ++i) {
            n = numOnNeighbors(*b, i, j);
            if      (n == 3) *get(newBoard, i, j) = CELL_ON;
            else if (n == 2) *get(newBoard, i, j) = *get(*b, i, j);
            else             *get(newBoard, i, j) = CELL_OFF;
        }
    }
    free(b->board);
    b->board = newBoard.board;
}

void iterateN(GameBoard *b, size_t n)
{
    while (n --> 0) iterate(b);
}

void print(FILE* out, GameBoard b)
{
    size_t i, j;
    for (j = 0; j < b.height; ++j) {
        for (i = 0; i < b.width; ++i) {
            fprintf(out, "%c", *get(b, i, j));
        }
        fprintf(out, "\n");
    }
    fclose(out);
}

char *get(GameBoard b, size_t x, size_t y)
{
    return &b.board[((x + b.width)  % b.width) +         /* Mods for wrapping */
                    ((y + b.height) % b.height) * b.width];
}

FILE *filePointer(int argc, char* argv[])
{
    if (argc == 1 || (argc == 2 && !strncmp(argv[1], "-", 2)))
        return stdin;

    else if (argc == 2)
        return fopen(argv[1], "r");

    else
        return NULL;
}

int numOnNeighbors(GameBoard b, size_t x, size_t y)
{
    return
        (*get(b, x - 1, y - 1) == CELL_ON ? 1 : 0) +
        (*get(b, x    , y - 1) == CELL_ON ? 1 : 0) +
        (*get(b, x + 1, y - 1) == CELL_ON ? 1 : 0) +
        (*get(b, x - 1, y    ) == CELL_ON ? 1 : 0) +
        (*get(b, x + 1, y    ) == CELL_ON ? 1 : 0) +
        (*get(b, x - 1, y + 1) == CELL_ON ? 1 : 0) +
        (*get(b, x    , y + 1) == CELL_ON ? 1 : 0) +
        (*get(b, x + 1, y + 1) == CELL_ON ? 1 : 0);
}

