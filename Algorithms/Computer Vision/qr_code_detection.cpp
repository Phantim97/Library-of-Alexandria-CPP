#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>

void qr_example()
{
	const std::string img_path = "/images/qr_image.png"; //Supply the image here

	const cv::Mat img = cv::imread(img_path);

	cv::Mat bbox;
	cv::Mat rectified_image;

	cv::QRCodeDetector qr_decoder = cv::QRCodeDetector();

	const std::string opencv_data = qr_decoder.detectAndDecode(img, bbox, rectified_image);

	if (opencv_data.length() > 0)
	{
		std::cout << "QR Code Detected\n";
	}
	else
	{
		std::cout << "QR Code NOT Detected\n";
	}

	const int n = bbox.rows;

	for (int i = 0; i < n; i++)
	{
		cv::line(rectified_image,
		         cv::Point(bbox.at<uchar>(i, 0), bbox.at<uchar>(i, 1)),
		         cv::Point(bbox.at<uchar>(((i + 1) % n), 0), bbox.at<uchar>((i + 1) % n, 1)),
		         cv::Scalar(0, 0, 255), 3);
	}

	std::cout << "QR Code Detected!\n";

	constexpr double font_scale = 1.5;
	constexpr int font_face = cv::FONT_HERSHEY_SIMPLEX;
	const cv::Scalar font_color = cv::Scalar(255, 10, 10);
	constexpr int font_thickness = 2;

	const cv::Point text_location(bbox.at<uchar>(0, 0));

	cv::putText(rectified_image, opencv_data, text_location, font_face, font_scale, font_color, font_thickness, cv::LINE_AA);

	const std::string result_image_path = "./QRCode-Output.png";

	cv::imwrite(result_image_path, rectified_image);
}