#include<opencv2\opencv.hpp>
#include<iostream>


int main()
{
	// Detect cars on video using haar cascade
	//Load video
	cv::VideoCapture video("cars1.avi");
	cv::CascadeClassifier carClassifier;
	if (!carClassifier.load("haar_cascade_cars.xml"))
	{
		std::cerr << "CANNOT LOAD HAAR CASCADE" << std::endl;
		return -1;
	}
	cv::Mat frame; // frame for each frame in video

	while (true)
	{
		video.read(frame);
		if (frame.empty())
		{
			std::cout << "END" << std::endl;
			break;
		}

		// Detect cars
		std::vector<cv::Rect> carsVector;
		carClassifier.detectMultiScale(frame, carsVector);

		// Draw cars on frame
		for (size_t i = 0; i < carsVector.size(); ++i)
		{
			cv::rectangle(frame, carsVector[i], Scalar(0, 255, 0), 3);
		}

		imshow("Video", frame);
		int key = cv::waitKey(10);
		if (key == 27)
		{
			std::cout << "STOP" << std::endl;
			break;
		}
	}

	return 0;
}