#include<opencv2\opencv.hpp>
#include<iostream>

// Variable for mouse callback
int event, x, y, frags;
cv::Mat frame;

void on_mouse_callback(int event, int x, int y, int frags, void* par)
{
	if (event == CV_EVENT_LBUTTONDOWN) {
		cv::Vec3b val;
		val = frame.at<cv::Vec3b>(y, x);
		std::cout << val << std::endl;
	}
}



int main()
{
	// Load video 
	cv::VideoCapture video("BATYARY.mp4");
	
	// Case if video is not loaded
	if (!video.isOpened())
	{
		std::cerr << "Error cant open video" << std::endl;
		return -1;
	}
	
	// Processing 
	while (true)
	{
		video.read(frame);
		
		// If video ends
		if (frame.empty())
		{
			std::cerr << "Video is empty" << std::endl;
			break;
		}
		
		cv::namedWindow("Image", CV_WINDOW_FREERATIO);
		
		// Get event from mouse
		cv::setMouseCallback("Image", on_mouse_callback);

		imshow("Image", frame);

		// Exit key
		int key = cv::waitKey(10);
		if (key == 27)
		{
			break;
		}
	}

	return 0;
}