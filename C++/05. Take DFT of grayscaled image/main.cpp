#include<opencv2\opencv.hpp>

// Define functions for creating DFT of image
void recenterDFT(cv::Mat& source);
void takeDFT(cv::Mat& source, cv::Mat& output);
void showDFT(cv::Mat& source);


// Function for creating DFT of image
void takeDFT(cv::Mat& source, cv::Mat& output)
{
	cv::Mat origComplex[2] = { source, cv::Mat::zeros(source.size() ,CV_32F) };
	// Merge origComplex into one two chanel image
	cv::Mat dftImg; // image for complex
	merge(origComplex, 2, dftImg);
	// DFT process 
	dft(dftImg, output, cv::DFT_COMPLEX_OUTPUT);
}


// Function that shows dft
void showDFT(cv::Mat& source)
{
	// Array for split
	cv::Mat arrSplit[2] = { cv::Mat::zeros(source.size(), CV_32F),cv::Mat::zeros(source.size(), CV_32F)};
	// Split image
	split(source, arrSplit);
	// As we have two parts - real and imagine - het magnitude of these numbers
	cv::Mat dftMagnitude;
	magnitude(arrSplit[0], arrSplit[1], dftMagnitude);
	// For correct log function add 1
	dftMagnitude += cv::Scalar::all(1);
	// Get  logarithm
	log(dftMagnitude, dftMagnitude); // notice that we saved it into the same variable
	// Normalize image with MINMAX method - min value = 0, max value = 1 and save to the same variable
	normalize(dftMagnitude, dftMagnitude, 0, 1,CV_MINMAX); 
	// Recenter DFT
	recenterDFT(dftMagnitude);
	// Finally show image
	imshow("DFT", dftMagnitude);
	cv::waitKey();
}


// Function that recenter DFT
void recenterDFT(cv::Mat& source)
{
	//	Finde position of center
	int centerX = source.cols / 2;
	int centerY = source.rows / 2;
	// Create parts of source
	cv::Mat q1(source, cv::Rect(0, 0, centerX, centerY));
	cv::Mat q2(source, cv::Rect(centerX, 0, centerX, centerY));
	cv::Mat q3(source, cv::Rect(0, centerY, centerX, centerY));
	cv::Mat q4(source, cv::Rect(centerX, centerY, centerX, centerY)); // I can't figure out what to is it

	// Swap parts
	cv::Mat swapMap;
	q1.copyTo(swapMap);
	q4.copyTo(q1);
	swapMap.copyTo(q4);
	q2.copyTo(swapMap);
	q3.copyTo(q2);
	swapMap.copyTo(q3);
}


// Inver DFT - function get DFT image and output real image
void invertDFT(cv::Mat& source, cv::Mat& output)
{
	dft(source, output, cv::DFT_INVERSE | cv::DFT_REAL_OUTPUT | cv::DFT_SCALE);
}


int main()
{
	// Taking the DFT of a Grayscaled Image
	cv::Mat original = cv::imread("machine_learning_path.png", CV_LOAD_IMAGE_GRAYSCALE);
	cv::Mat origFloat; // Image for converting to CV_32F type
	
	// Converting 
	original.convertTo(origFloat, CV_32FC1, 1.0/255.0); // Convert image to image with values from 0 to 1
	
	// Take dft
	cv::Mat dftOriginal;
	takeDFT(origFloat, dftOriginal);
	showDFT(dftOriginal);  
	
	cv::Mat invertedDFT;
	invertDFT(dftOriginal, invertedDFT);
	
	imshow("InvertedDFT", invertedDFT);
	
	cv::waitKey(0);
	return 0;
}