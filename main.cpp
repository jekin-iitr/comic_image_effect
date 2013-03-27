#include<cv.hpp>
#include<highgui.h>
#include<iostream>
using namespace cv;
using namespace std;
int main()
{
	Mat image = imread("britney.jpg");
	imshow("input",image);

	Mat gray;
	cvtColor(image,gray,CV_RGB2GRAY);

	const int MEDIAN_BLUR_FILTER_SIZE = 7;
	medianBlur(gray, gray, MEDIAN_BLUR_FILTER_SIZE);

	Mat edge;
	const int LAPLACIAN_FILTER_SIZE = 5;
	Laplacian(gray, edge, gray.depth(), LAPLACIAN_FILTER_SIZE);

	Mat mask;
	const int EDGE_THRESHOLD = 80;
	threshold(edge, mask, EDGE_THRESHOLD, 255, THRESH_BINARY_INV);

	Size size = image.size();
	Size smallSize;
	smallSize.width = size.width/2;
	smallSize.height = size.height/2;
	Mat smallImage = Mat(smallSize, CV_8UC3 );
	resize(image, smallImage, smallSize, 0, 0, INTER_LINEAR);

	Mat temp = Mat(smallSize, CV_8UC3);
	for(int i=0; i<7; i++)
	{
		int ksize = 9;
		double sigmaColor = 9;
		double sigmaSpace = 7;
		bilateralFilter(smallImage, temp, ksize, sigmaColor, sigmaSpace);
		bilateralFilter(temp,smallImage , ksize, sigmaColor, sigmaSpace);
	}

	Mat bigImg;
	resize(smallImage, bigImg, size, 0, 0, INTER_LINEAR );
	
	Mat dst = Mat(size, CV_8UC3);
	dst.setTo(0);
	bigImg.copyTo(dst, mask);

	imshow("output",dst);
	waitKey(0);
	return 0;
}
	