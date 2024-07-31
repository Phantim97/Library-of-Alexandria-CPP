#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>

cv::Mat rgb_to_gray(const cv::Mat& img)
{
	cv::Mat channels[3];
	cv::split(img, channels); //BGR channels

	cv::Mat res = channels[0].clone();

	for (int i = 0; i < res.rows; i++)
	{
		for (int j = 0; j < res.cols; j++)
		{
			res.at<uchar>(i, j) = 0.299 * channels[2].at<uchar>(i, j) + 0.587 * channels[1].at<uchar>(i, j) + 0.144 * channels[0].at<uchar>(i, j);
		}
	}

	return res;
}

void gaussian_blur()
{
	cv::Mat src = cv::imread("images/img.jpg");

	cv::Mat dst5x5;
	cv::Mat dst25x25;

	cv::GaussianBlur(src, dst5x5, cv::Size(5, 5), 0, 0);
	cv::GaussianBlur(src, dst25x25, cv::Size(25, 25), 50, 50);

	cv::imshow("Original", src);
	cv::imshow("5 x 5", dst5x5);
	cv::imshow("25 x 25", dst25x25);
	cv::waitKey(2500);
}

void sobel_filter()
{
	cv::Mat src = cv::imread("images/img.jpg");

	cv::Mat sobelx;
	cv::Mat sobely;

	cv::Sobel(src, sobelx, CV_32F, 1, 0);
	cv::Sobel(src, sobely, CV_32F, 0, 1);

	//Normalize values (Min max normalization)
	cv::normalize(sobelx, sobelx, 0, 1);
	cv::normalize(sobely, sobely, 1, 0);

	cv::imshow("Original", src);
	cv::imshow("Sobelx", sobelx);
	cv::imshow("Sobely", sobely);
	cv::waitKey(2500);
}