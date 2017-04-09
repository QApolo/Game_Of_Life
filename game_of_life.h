#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#ifdef _WIN32
   #define CLEAR "cls"
#elif __WIN64
	#define CLEAR "cls"
#elif __APPLE__
    #define CLEAR "clear"
#elif __linux__
    #define CLEAR "clear"
#else
#   error "Unknown compiler"
#endif

#define SIZE 100
int const _probability = 25; //expressed as percentage
typedef char Cell;

//ascii value for living and dead cells
const Cell live = 32;
const Cell dead = 'x';

//prototypes for the functions
Cell **createMesh(void);
void initMesh(Cell);
int valid(int, int );
int count_neighbours(Cell, int, int, Cell);
void printMesh(Cell **);
void rutine(Cell **, int);
void start();