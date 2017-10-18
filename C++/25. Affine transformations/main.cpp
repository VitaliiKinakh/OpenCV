#include<opencv2\opencv.hpp>

using namespace std;

int main()
{
	/// Affine transofmation
	Mat src = imread("animal.jpg");
	// Images for transormation
	
	Mat dst, warp_dst, warp_mat, warp_rotate, rot_mat;
	
	// Set transframtion via points
	warp_dst = Mat::zeros(src.rows, src.cols, src.type());
	Point2f srcTri[3];
	Point2f dstTri[3];
	
	// Set input
	srcTri[0] = Point2f(0, 0);
	srcTri[1] = Point2f(src.cols - 1, 0);
	srcTri[2] = Point2f(0, src.rows - 1);
	
	// Set output
	dstTri[0] = Point2f(0.33 * src.cols, 0.85 * src.rows);
	dstTri[1] = Point2f(src.cols* 0.5, src.rows * 0.5);
	dstTri[2] = Point2f(0, src.rows * 0.66);
	
	// set Affine Transformation
	warp_mat = getAffineTransform(srcTri, dstTri);
	
	// Apply transformation
	warpAffine(src, warp_dst, warp_mat, warp_dst.size());
	imshow("Affine transormation", warp_dst);

	// Rotate
	Point center = Point(warp_dst.cols / 2, warp_dst.rows / 2);
	double angle = -50.0;
	double scale = 0.6;

	/// Get the rotation matrix with the specifications above
	rot_mat = getRotationMatrix2D(center, angle, scale);

	/// Rotate the warped image
	warpAffine(warp_dst, warp_rotate, rot_mat, warp_dst.size());
	imshow("Rotated", warp_rotate);
	waitKey(0);
	return 0;
}