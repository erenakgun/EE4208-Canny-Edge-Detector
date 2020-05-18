#ifndef IO_H_INCLUDED
#define IO_H_INCLUDED

#include "matrix.h"
#include <string>
#include <vector>


void readImage(std::string path,Matrix &image);
void writeImage(const char* name, const Matrix &matrix);
void readHeader(int &row,int &col, int &intensity , std::vector<unsigned char> buffer);
void outputImage(const char* fileName,const Matrix &matrix);
#endif // IO_H_INCLUDED
