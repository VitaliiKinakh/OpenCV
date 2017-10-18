#include<opencv2\opencv.hpp>
#include<iostream>


int main()
{
	// Cascade classifier
	cv::CascadeClassifier face;
	cv::CascadeClassifier eye;
	// Load cascades
	if (!face.load("haarcascade_frontalface_default.xml") || !eye.load("haarcascade_eye.xml"))
	{
		std::cerr << "ERROR CANT OPEN FILES" << std::endl;
		return -1;
	}
	// Load video from webcam
	cv::VideoCapture video(0);
	if (!video.isOpened())
	{
		std::cerr << "ERROR CANT OPEN VIDEO" << std::endl;
		return -1;
	}
	while (true)
	{
		cv::Mat frame; // image for each video frame
		std::vector<cv::Rect> faces; // vector for face rectangles
		video.read(frame);
		cv::Mat frame_gray;
		cv::cvtColor(frame, frame_gray, CV_BGR2GRAY);

		// Detect faces
		face.detectMultiScale(frame_gray, faces);
		
		// Draw each face and detect eyes inside face
		for (size_t i = 0; i < faces.size(); ++i)
		{
			cv::rectangle(frame, faces[i], cv::Scalar(0, 255, 0), 3);

			// Detect eye
			cv::Mat frameROI = frame(faces[i]);
			std::vector<cv::Rect> eyes;
			eye.detectMultiScale(frameROI, eyes);

			// Draw each eye
			for (size_t j = 0; j < eyes.size(); ++j)
			{

				cv::Point eye_center(faces[i].x + eyes[j].x + eyes[j].width / 2, faces[i].y + eyes[j].y + eyes[j].height / 2);
				int radius = cvRound((eyes[j].width + eyes[j].height)*0.25);
				cv::circle(frame, eye_center, radius, Scalar(255, 0, 0), 4, 8, 0);
			}
		}

		// Show frame
		cv::imshow("Face and eyes", frame);

		int key = waitKey(10);
		if (key == 27)
		{
			break;
		}

	}

	return 0;
}