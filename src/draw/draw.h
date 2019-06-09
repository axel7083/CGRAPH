#ifndef DRAW_H_
#define DRAW_H_

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void run();
void stop();
void calculate();
void drawEdges();
void rotate2d(float* x, float* y, float rad);
void setVertex(int nb_points,float x,float y,float z);
void setSides(int nb_edges,int nb_points);
void printIntXY(int var, int x, int y, int dec);
int selectColor(float height);
void computeMinMax(int nb_pt);
void display(void);
float precision(void);
void print_string_centered(const char *str,int y);

void show(int nb_points); 
#endif