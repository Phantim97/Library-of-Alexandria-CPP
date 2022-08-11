//Note requires opencv
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>

cv::Mat rgb_to_hsv(const cv::Mat& img)
{
	cv::Mat res = img.clone();
	cv::Mat channels[3];
	cv::Mat hsv_channels[3];

	cv::split(img, channels); //BGR channels
	cv::split(res, hsv_channels);

	float hue = 0;
	float saturation = 0;
	float value = 0;

	float b = 0.0;
	float g = 0.0;
	float r = 0.0;

	uchar idx = 0;
	uchar value_index = 0;

	float min_val = 0;

	uchar hue_idx1 = 0;
	uchar hue_idx2 = 0;

	for (int i = 0; i < res.rows; i++)
	{
		for (int j = 0; j < res.cols; j++)
		{
			//Felt motivated to do a branchless HSV calculation, was a fun optimization problem to do
			b = channels[0].at<uchar>(i, j) / 255.0;
			g = channels[1].at<uchar>(i, j) / 255.0;
			r = channels[2].at<uchar>(i, j) / 255.0;

			//Branchless max check
			idx = (r >= g && r >= b) + ((g <= r || g >= b) && (b <= r || b <= g));
			value = channels[idx].at<uchar>(i, j) / 255.0;
			value_index = idx;

			//Branchless min check
			idx = (r <= g && r <= b) + ((g >= r || g <= b) && (b >= r || b >= g));
			min_val = channels[idx].at<uchar>(i, j) / 255.0;

			//Branchless Saturation Calculation
			saturation = (value - min_val) * (value != 0); //Set to 0 if value == 0
			saturation /= (value + (value == 0)); //Since previous step makes it 0 all we need to do is divide by 1 if saturation = 0

			//Branchless Color channel selection for hue calculation
			hue_idx1 = (value_index == 0 || value_index == 2) + (value_index == 0);
			hue_idx2 = (value_index == 1 || value_index == 0) + (value_index == 1);

			hue = (240 - (120 * value_index)) + (60.0 * ((channels[hue_idx1].at<uchar>(i, j)/255.0) - (channels[hue_idx2].at<uchar>(i, j)/255.0))) / (value - min_val);

			//Store channels
			hsv_channels[0].at<uchar>(i, j) = ((hue + (360 * (hue < 0))) / 2.0);
			hsv_channels[1].at<uchar>(i, j) = saturation * 255;
			hsv_channels[2].at<uchar>(i, j) = value * 255;
		}
	}

	cv::merge(hsv_channels, 3, res);

	return res;
}
