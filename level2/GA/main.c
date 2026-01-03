#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define POP_SIZE 100
#define ROW 7
#define COL 8
typedef struct {
    int gene[100];
    double fitness;
} Individual;

Individual pop[POP_SIZE];

char maze[ROW][COL+1];

void initPopulation();

double computeFitness(Individual ind);

void runGA(int maxGen);

int selectIndividual();

Individual crossover(Individual parent1, Individual parent2);

Individual mutate(Individual *ind);

int main() {
    FILE *fp=fopen("maze.txt","r");
    if (fp == NULL) {
        perror("error");
    }
    for(int i=0; i<ROW; i++) {
        fgets(maze[i],COL+2,fp);
    }
    fclose(fp);
    for(int i=0; i<ROW; i++) {
        printf("%s\n",maze[i]);
    }
    srand(time(NULL));
    return 0;
}

