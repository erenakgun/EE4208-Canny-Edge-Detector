#include "matrix.h"
#include "IO.h"
#include "GaussianFilter.h"
#include "sobelFilter.h"
#include "Utils.h"


#include <iostream>
#include <string>
#include <fstream>
#include <iterator>
#include <vector>
#include <bitset>


using namespace std;


int main()
{


    string path;
    cout<<"Enter image path: ";
    cin>>path;

    Matrix image;
    readImage(path,image);

    // Containers for intermediate results
    Matrix blurred(image.row,image.col);
    Matrix sobelXresult(image.row,image.col);
    Matrix sobelYresult(image.row,image.col);
    Matrix sobelIntensity(image.row,image.col);
    Matrix edgeDir(image.row,image.col);
    Matrix finalEdges(image.row,image.col);


    double sigma;
    cout<<"Enter standary deviation for Gaussian Filter: ";
    cin>>sigma;

    cout<<"Result will be saved to Result.raw file as binary: ";

    // Gaussian blurring
    GaussianFilter filter(sigma);
    path = "blurred.raw";
    convolution(blurred , image, filter, 0, filter.scaleFactor);
    writeImage(path.c_str(),blurred);

    // Sobel filters
    sobelFilter sobelY(0);
    path = "sobelY.raw";
    convolution(sobelYresult , blurred, sobelY, 1, filter.scaleFactor);
    writeImage(path.c_str(),sobelYresult);

    sobelFilter sobelX(1);
    path = "sobelX.raw";
    convolution(sobelXresult , blurred, sobelX, 1, filter.scaleFactor);
    writeImage(path.c_str(),sobelXresult);

    // Find edge intensities
    path = "sobelIntensity.raw";
    calculateIntensity(sobelIntensity, sobelXresult, sobelYresult);
    writeImage(path.c_str(),sobelIntensity);

    // Find edge directions
    calculateEdgeDir(edgeDir, sobelXresult, sobelYresult, 40);
    path = "edgeDir.raw";

    /* Can be used for visualizing edge directions
    edgeDir.scale(50);
    writeImage(path.c_str(),edgeDir);
    */

    //non-maximum supression
    nonMaxSupression(finalEdges, sobelIntensity, edgeDir);
    path = "Result.raw";
    writeImage(path.c_str(),finalEdges);

    return 0;
}
