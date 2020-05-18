#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED
#include "matrix.h"

void convolution(Matrix &output,  Matrix &image,  Matrix &filter, int padding, double scaleFactor);
double convSum (Matrix &image,  Matrix &filter, int padding, int centerRow ,int centerCol, int offset);
void calculateIntensity(Matrix &output, Matrix &edgeX, Matrix &edgeY);
void calculateEdgeDir(Matrix &output, Matrix &edgeX, Matrix &edgeY, double threshold);
void nonMaxSupression(Matrix &output, Matrix &edgeIntensity, Matrix &edgeDir);
int maxTrio(int before, int center, int after);


#endif // UTILS_H_INCLUDED
