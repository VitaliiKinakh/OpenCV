#include<opencv2\opencv.hpp>


int main()
{
	// Take video from webcam
	cv::Mat frame; // Variable for each frame in video
	cv::VideoCapture vid(0); // 0 - means first webcam
	if (!vid.isOpened())
	{
		return -1;
	}
	else {
		while (vid.read(frame))
		{
			imshow("Video", frame);
			int key = cv::waitKey(1);
			if (key == 27) // Press Esc to exit 
			{
				break;
			}
		}
	}
	return 0;
}