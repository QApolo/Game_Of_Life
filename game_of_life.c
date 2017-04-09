#include "game_of_life.h"

Cell **createMesh()
{
	Cell **mesh = (Cell**)malloc(sizeof(Cell*)*SIZE);
	int i;
	for(i = 0; i < SIZE; i++)
		mesh[i] = (Cell*)malloc(sizeof(Cell)*SIZE);	
	return mesh;
}
void initMesh(Cell **mesh)
{
	int i,j;
	srand(time(NULL));

	int deads = _probability;
	int py,px;

	for(i = 0; i < SIZE; i++)
		for(j = 0; j < SIZE; j++)
			mesh[i][j] = live;
		
	for(i = 0; i < SIZE; i++)
	{
		for(j = 0; j < SIZE; j++)
		{
			py = rand()%SIZE;
			px = rand()%SIZE;

			if(mesh[py][px] != dead)
			{
				mesh[py][px] = dead;
				deads --;
			}

		}
	}	
}

int valid(int y, int x )
{
	if(y < 0 || y >=SIZE || x < 0 || x >= SIZE)return 0;
return 1;
}
int count_neighbours(Cell **mesh,int y, int x, Cell type)
{
	int cont = 0;
	int movs[8][2]=
			{
				{0,1},{1,0},
				{-1,0},{0,-1},
				{1,1},{1,-1},
				{-1,1},{-1,-1}
			};
	int i;
	int auxY,auxX;

	for(i = 0; i < 8; i++ )
	{
		auxY = movs[i][0] + y;
		auxX = movs[i][1] + x;

		if( valid(auxY,auxX) )
			if(mesh[auxY][auxX] == type) cont++;
	}
	return cont;
}

void printMesh(Cell **mesh)
{
	int i,j;
	for(i = 0; i < SIZE; i++)
	{
		for(j = 0; j < SIZE; j++)
			printf("%c ",mesh[i][j] );
		printf("\n");
	}
}
void rutine(Cell **mesh, int time)
{
	Cell **aux_mesh = createMesh();
	int i, j;

	while(time--)
	{
		printMesh(mesh);
		usleep(100000);
		system(CLEAR);
		
		for(i = 0; i < SIZE; i++)
		{
			for(j = 0; j < SIZE; j++)
			{
				if(mesh[i][j] == live)
				{
					int count = count_neighbours(mesh,i,j,live); //gets the number of living neighbours
					aux_mesh[i][j] = mesh[i][j];
					if((count == 2 || count == 3))
					{
						aux_mesh[i][j] = mesh[i][j];
					}
					else 
					{
						aux_mesh[i][j] = dead;
					}
				}
				else if(mesh[i][j] == dead)
				{
					int count = count_neighbours(mesh,i,j,live); 
					aux_mesh[i][j] = mesh[i][j];
					if(count == 3)
					{
						aux_mesh[i][j] = live;
					}
					else 
					{
						aux_mesh[i][j] = mesh[i][j];
					}	
				}
			}
		}

		for(i = 0; i < SIZE; i++)
			for(j = 0; j < SIZE; j++)
				mesh[i][j] = aux_mesh[i][j];
	}
}
void start()
{
	Cell **mesh = createMesh();
	initMesh(mesh);
	rutine(mesh,1000);
}