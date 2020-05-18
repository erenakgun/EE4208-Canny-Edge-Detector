#Program needs:
--> image (binary format) file location
--> standart deviation value for the Gaussian filter.

#Outputs:
--> Result of the canny edge detection algorithm into 			Result.raw
--> Result of edge detection without non-maximum supression into	sobelIntensity.raw
--> Result of Sobel x filter into					sobelX.raw
--> Result of Sobel y filter into					sobelY.raw
--> Result of the Gaussian blurring into 				blurred.raw

#Files and code architecture
src file includes necessarry .cpp extension files. include file includes all headers.
Matrix class is a container for 2D images.
sobelFilter and GaussianFilter classes inherits Matrix class and implements special constructors.
IO file includes image input and output functions taking Matrix and path as an input
Utils file includes necessary functions for:
-> convolution
-> intensity calculation
-> edge direction detection
-> non maximum supression
and other functions used in above functions

### EXAMPLE INPUT
input1: images\\cana.raw
input2: 1.5
