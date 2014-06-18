/* Extremely optimized ASCII maze solver
 * Finds all valid paths from start to finish
 * /r/dailyprogrammer challenge 165
 * http://redd.it/278ptv
 * TODO: Show only the shortest path?
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Note: These should not be used for boolean comparisons! */
#define true  1
#define false 0

/* There's a special place in hell for people who abuse enums like this in
 * production code. */
enum {
    WALL       = '#',
    START      = 'S',
    END        = 'E',
    EMPTY      = ' ',
    SOLVE_PATH = '*'
};

FILE *filePointer(int argc, char* argv[]);

typedef struct {
    size_t height;
    size_t width;
    char *state;
} Maze;

static void print(FILE* out, Maze m);
static Maze init(FILE *fp);
char *get(Maze m, size_t x, size_t y);
void solve(FILE *fp);

int main(int argc, char* argv[])
{
    FILE *fp = filePointer(argc, argv);
    if (fp == NULL) return EXIT_FAILURE;
    solve(fp);
    fclose(fp);
    return EXIT_SUCCESS;
}

int equal_cstrings(char *s1, char *s2)
{
    return strcmp(s1, s2) == 0;
}

FILE *filePointer(int argc, char* argv[])
{
    if (argc == 1 || (argc == 2 && equal_cstrings(argv[1], "-")))
        return stdin;

    else if (argc == 2)
        return fopen(argv[1], "r");

    else
        return NULL;
}

void print(FILE* out, Maze m)
{
    size_t i, j;
    const char pathColorCode[]  = "\x1B[31m";
    const char wallColorCode[]  = "\x1B[36m";
    const char otherColorCode[] = "\x1B[33m";
    const char resetCode[]      = "\x1B[0m";
    const int addColor = 0;
    char next;

    for (j = 0; j < m.height; ++j) {
        for (i = 0; i < m.width; ++i) {
            next = *get(m, i, j);
            if (addColor) {
                if (next == SOLVE_PATH)
                    fprintf(out, "%s", pathColorCode);

                else if (next == WALL)
                    fprintf(out, "%s", wallColorCode);

                else
                    fprintf(out, "%s", otherColorCode);
            }
            fprintf(out, "%c", next);
        }
        fprintf(out, "\n");
    }

    if (addColor) fprintf(out, resetCode);
}

int deadEnd(Maze m, size_t x, size_t y)
{
    size_t i, numDeadNeighbors = 0;
    char *elem = get(m, x, y);

    if (elem != NULL && *elem == SOLVE_PATH) {
        char *neighbors[] = {
            get(m, x - 1, y),
            get(m, x + 1, y),
            get(m, x, y - 1),
            get(m, x, y + 1)
        };

        for (i = 0; i < 4; ++i)
            if (neighbors[i] == NULL
                    || *neighbors[i] == WALL
                    || *neighbors[i] == EMPTY)
                numDeadNeighbors++;

        return numDeadNeighbors >= 3;
    } else {
        return 0;
    }
}

void solve(FILE *fp)
{
    Maze m = init(fp);
    size_t i, j, width = m.width, height = m.height, done = false;
    print(stdout, m);
    while (!done) {
        done = true;
        for (j = 0; j < height; ++j) {
            for (i = 0; i < width; ++i) {
                if (deadEnd(m, i, j)) {
                    *get(m, i, j) = EMPTY;
                    done = false;
                }
            }
        }
    }
    printf("\n");
    print(stdout, m);
}

static Maze init(FILE *fp)
{
    Maze m;
    size_t i;
    char c;

    fscanf(fp, "%zd %zd\n", &m.width, &m.height);
    m.state = (char*)malloc(m.width * m.height);

    for (i = 0, c = fgetc(fp); c != EOF; c = fgetc(fp)) {
        if (c == WALL || c == START || c == END)
            m.state[i++] = c;
        else if (c == EMPTY)
            m.state[i++] = SOLVE_PATH;
    }
    return m;
}

char *get(Maze m, size_t x, size_t y)
{
    if (x > m.width || y > m.height)
        return NULL;
    else
        return &m.state[x + y * m.width];
}

