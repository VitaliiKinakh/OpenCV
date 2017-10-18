#include<opencv2\opencv.hpp>
#include"MorphoFeatures.h"


int main()
{
	// Detect corners and edges on image
	cv::Mat image = cv::imread("opencv-corner-detection-sample.jpg", 0);
	
	// Define object for detecting corners
	MorphoFeatures morpho;
	morpho.setThreshold(40);
	
	// Get the edges
	cv::Mat edges;
	edges = morpho.getEdges(image);
	imshow("Edges", edges);
	
	cv::Mat corners;
	corners = morpho.getCorners(image);
	
	// Display the corner on the image
	imshow("Corners on Image", corners);
	
	// Draw corners
	morpho.drawOnImage(corners, image);
	imshow("Detected corners", image);
	
	cv::waitKey(0);
	return 0;
}