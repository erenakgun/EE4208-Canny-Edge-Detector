#include "matrix.h"
#include "IO.h"
#include <iostream>
#include <string>
#include <fstream>
#include <iterator>
#include <vector>
#include <bitset>
#include <stdio.h>

void readImage(std::string path,Matrix &image)
{
    /*
        This function accepts raw image path as parameter and returns matrix of that image

    */

    int row;
    int col;
    int intensity;

    std::ifstream input(path, std::ios::binary );

    if(!input)

    {
        std::cerr<< "While opening a file an error is encountered" << std::endl;

    }
    else
    {
        std::cout << "File is successfully opened" << std::endl;

        // copies all data into buffer
        std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(input), {});

        // read header
        readHeader(row,col,intensity,buffer);

        //Create dynamic array for pixel data
        double **data = new double*[row];
        for(int i=0;i<row;i++)
        {
            data[i] = new double[col];
        }

        //Read data from buffer into 2D dynamic array
        for (int i =0; i< row;i++)
        {
            for(int j =0 ;j<col;j++)
            {
                data[i][j] = static_cast<double> (buffer[i*col + j +5]);

            }
        }

        image.row=row;
        image.col=col;
        image.mat = data;
    }
}


void writeImage(const char* fileName,const Matrix &matrix){
    int matSize = matrix.row * matrix.col;
    char buffer[matSize-1];

    for (int i=0;i<matrix.row;i++){
    	for (int j=0;j<matrix.col;j++)
    	{
    		buffer[i*matrix.col+j]= static_cast<char>(matrix.mat[i][j]);
    	}
    }

    std::ofstream myFile (fileName, std::ios::out | std::ios::binary);
    myFile.write (buffer, matSize);
}

void readHeader(int &row, int &col, int &intensity, std::vector<unsigned char> buffer)
{
    /*
     * This function reads the header file from buffer
     * First 2 bytes are row in reverse order (most significant byte is the second)
     * Second 2 bytes are col in reverse order (most significant byte is the second)
     * Fifth byte is intensity
     */
    std::bitset<16> myRow{};
    std::bitset<16> myCol{};

    //Read row number
    std::bitset<16> bitsetLS{buffer[0]};
    std::bitset<16> bitsetMS{buffer[1]};
    bitsetMS<<=8;

    myCol = bitsetMS | bitsetLS;
    col = static_cast<int>(myCol.to_ulong());
    std::cout<<"Width: "<< col <<std::endl;


    //read column number
    std::bitset<16> bitsetLSC{buffer[2]};
    std::bitset<16> bitsetMSC{buffer[3]};
    bitsetMSC<<=8;

    myRow = bitsetMSC | bitsetLSC;
    row = static_cast<int>(myRow.to_ulong());
    std::cout<<"Height: "<< row <<std::endl;

    //read intensity size (we assume its always 8)
    intensity = static_cast<int>(buffer[4]);
    std::cout<<"Intensity: "<<intensity<<'\n'<<std::endl;


}




