#include<opencv2\opencv.hpp>


int main()
{
	cv::Mat image = cv::imread("dog.jpg");
	
	// Define ROI(region of interest)
	cv::Rect fg_r(cv::Point(150, 0), cv::Point(720, 524));
	
	cv::Mat result;
	cv::Mat bgModel, fgModel;
	grabCut(image, result, fg_r, bgModel, fgModel, 5, cv::GC_INIT_WITH_RECT);

	// Get the pixels marked as likely foreground
	cv::compare(result, cv::GC_PR_FGD, result, cv::CMP_EQ);
	
	// Generate output image
	cv::Mat foreground(image.size(), CV_8UC3, cv::Scalar(255, 255, 255));
	
	image.copyTo(foreground, result); // bg pixels not copied
	imshow("Dog image", image);
	imshow("Foreground", foreground);
	
	cv::waitKey(0);   
	return 0;
}