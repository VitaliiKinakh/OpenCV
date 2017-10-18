#pragma once
#include<opencv2\opencv.hpp>
#include<iostream>
class MorphoFeatures
{
private:
	// threshold
	int threshold;
	// elements for corver detection
	cv::Mat cross;
	cv::Mat diamond;
	cv::Mat square;
	cv::Mat x;
	// finction for applying binary threshold
	void applyThreshold(cv::Mat& result);
public:
	MorphoFeatures();
	MorphoFeatures(int t);
	~MorphoFeatures();
	void setThreshold(int t);
	// Functions to detect edges
	cv::Mat getEdges(const cv::Mat& image);
	// Function to detect corners
	cv::Mat getCorners(const cv::Mat& image);
	// Function to draw a circle near each corner 
	// binary is image with corners - image image to draw
	void drawOnImage(const cv::Mat& binary, cv::Mat& image);

};


