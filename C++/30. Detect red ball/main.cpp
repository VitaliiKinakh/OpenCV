#include<opencv2\opencv.hpp>
#include<iostream>


int main()
{
	/// Detect balls with opencv
	cv::Size size = cv::Size(640, 480);			// use a 640 x 480 size for all windows, also make sure your webcam is set to 640x480 !!

	cv::VideoCapture capWebcam(0);						// 0 means first webcam

	cv::Mat imgOriginal;			// pointer to an image structure, this will be the input image from webcam
	cv::Mat imgProcessed(size, CV_8U);			// pointer to an image structure, this will be the processed image
									
	std::vector<cv::Vec3f> circles; // vector for circles from HoughCircles

	if (!capWebcam.isOpened()) {			// if capture was not successful . . .
		std::cout << "Error can`t open camera" << std::endl; // error message to standard out
		getchar();								// getchar() to pause for user see message . . .
		return(-1);								// exit program
	}

	// declare 2 windows
	cv::namedWindow("Original", CV_WINDOW_FREERATIO);		// original image from webcam
	cv::namedWindow("Processed", CV_WINDOW_FREERATIO);		// the processed image we will use for detecting circles

	while (true) {								// for each frame . . .
		capWebcam.read(imgOriginal);	// get frame from webcam

		if (imgOriginal.empty()) {					// if frame was not captured successfully . . .
			std::cout << "Error: frame is empty" << std::endl;		// error message to std out
			getchar();
			break;
		}

		cv::Mat ranged; // image for inRange operation
		cv::inRange(imgOriginal, cv::Scalar(0,0, 175), cv::Scalar(100, 100, 255), ranged);

		// Gaussian blur
		cv::GaussianBlur(ranged, imgProcessed, cv::Size(3, 3), 0.5);

		// Detect circles
		cv::HoughCircles(imgProcessed, circles, cv::HOUGH_GRADIENT, 1,
			imgProcessed.rows / 16, // change this value to detect circles with different distances to each other
			100, 30, 1, 30);

		// Draw detected circles
		for (int i = 0; i < circles.size(); ++i) {

			cv::Vec3i c = circles[i];
			circle(imgOriginal, cv::Point(c[0], c[1]), c[2], cv::Scalar(255, 255, 255), 3, cv::LINE_AA); // circle
			circle(imgOriginal, cv::Point(c[0], c[1]), 2, cv::Scalar(0, 255, 0), 3, cv::LINE_AA); // center dot
		}	

		cv::imshow("Original", imgOriginal);			// original image with detectec ball overlay
		cv::imshow("Processed", imgProcessed);		// image after processing
		
		// Wait for esc pressed
		int key = cv::waitKey(10);
		if (key == 27)
		{
			break;
		}// if Esc key (ASCII 27) was pressed, jump out of while loop
	}	// end while

	cv::destroyAllWindows();

	return 0;
}