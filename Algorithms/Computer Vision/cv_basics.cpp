#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>

//Getting started examples
void split_channels_example()
{
	const std::string path = "images/img1.jpg";

	const cv::Mat img = cv::imread(path);

	cv::namedWindow("Base", cv::WINDOW_KEEPRATIO);
	cv::namedWindow("Channel 1", cv::WINDOW_KEEPRATIO);
	cv::namedWindow("Channel 2", cv::WINDOW_KEEPRATIO);
	cv::namedWindow("Channel 3", cv::WINDOW_KEEPRATIO);

	std::cout << "Size: " << img.size() << '\n';
	std::cout << "Channels: " << img.channels() << '\n';

	cv::Mat img_channels[3] = {};
	cv::split(img, img_channels);

	//Note: cv::imshow will only work with a cv::waitkey associated
	cv::imshow("Base", img);
	cv::imshow("Channel 1", img_channels[0]);
	cv::imshow("Channel 2", img_channels[1]);
	cv::imshow("Channel 3", img_channels[2]);

	while (true)
	{
		if (cv::waitKey(10) >= 0)
		{
			break;
		}
	}
}

void modify_pixels()
{
	const std::string path = "images/img1.jpg";

	cv::Mat img = cv::imread(path);
	//cv::Mat img2 = img; //I think cv::Mats are not copy constructible as doing this gives ref

	cv::namedWindow("Base", cv::WINDOW_KEEPRATIO);
	cv::imshow("Base", img);

	cv::namedWindow("Modified", cv::WINDOW_KEEPRATIO);

	img(cv::Range(0, img.rows / 4), cv::Range(0, img.cols / 4)).setTo(cv::Scalar(255, 255, 0));

	cv::imshow("Modified", img);

	while (true)
	{
		if (cv::waitKey(10) >= 0)
		{
			break;
		}
	}
}

void alpha_mask()
{
	const std::string path = "images/img1.png";

	const cv::Mat imgPNG = cv::imread(path, -1); //Read the image as is

	constexpr size
	std::cout << "Channels: " << imgPNG.channels() << '\n';

	cv::namedWindow("Base", cv::WINDOW_KEEPRATIO);

	cv::namedWindow("Modified", cv::WINDOW_KEEPRATIO);

	//Alpha Mask
	cv::Mat imgBGR;
	cv::Mat imgPNGChannels[4];
	cv::split(imgPNG, imgPNGChannels);

	cv::merge(imgPNGChannels, 3, imgBGR);

	cv::Mat imgMask = imgPNGChannels[3];

	//==========
	cv::imshow("Base", imgBGR);
	cv::imshow("Modified", imgMask);

	while (true)
	{
		if (cv::waitKey(10) >= 0)
		{
			break;
		}
	}
}

//Basic Image Operators

void image_copying()
{
	cv::Mat img = cv::imread("images/img1.jpg");

	cv::Mat img2 = img.clone(); //without clone, we are passing the ref
}

void blank_image()
{
	//200 x 100
	cv::Mat empty_matrix = cv::Mat(100, 200, CV_8UC3, cv::Scalar(0, 0, 0));

	cv::imwrite("images/empty.png", empty_matrix);
}

void image_cropping()
{
	const cv::Mat image = cv::imread("images/img1.jpg");
	cv::Mat crop = image(cv::Range(40,200), cv::Range(170, 320));
}

void region_copying()
{
	cv::Mat image = cv::imread("images/img1.jpg");
	cv::Mat copiedImage = image.clone();

	cv::Mat copyRoi = image(cv::Range(40, 200), cv::Range(180, 320));

	const int roiHeight = copyRoi.size().height;
	const int roiWidth = copyRoi.size().width;

	copyRoi.copyTo(copiedImage(cv::Range(40, 40 + roiHeight), cv::Range(10, 10 + roiWidth)));
	copyRoi.copyTo(copiedImage(cv::Range(40, 40 + roiHeight), cv::Range(330, 330 + roiWidth)));

	cv::imwrite("images/copied_image.png", copiedImage);
}

void resizing_image()
{
	constexpr int resizeDownWidth = 300;
	constexpr int resizeDownHeight = 200;
	cv::Mat image = cv::imread("images/img1.jpg");
	cv::Mat resizedDown;

	cv::resize(image, resizedDown, cv::Size(resizeDownWidth, resizeDownHeight),
	           0.0, 0.0);

	// Mess up with the aspect ratio
	constexpr int resizeUpWidth = 600;
	constexpr int resizeUpHeight = 900;
	cv::Mat resizedUp;
	resize(image, resizedUp, cv::Size(resizeUpWidth, resizeUpHeight), 0.0,
	       0.0,cv::INTER_LINEAR);

	cv::imwrite("images/resized_up.png", resizedUp);
	cv::imwrite("images/resized_down.png", resizedDown);

	//Scaling factor
	constexpr double width_scale = 1.5;
	constexpr double height_scale = 1.5;

	constexpr double scale_down = 0.6;

	cv::Mat scaledUp;
	cv::Mat scaledDown;

	cv::resize(image, scaledDown, cv::Size(),
	           scale_down, scale_down, cv::InterpolationFlags::INTER_LINEAR);

	cv::resize(image, scaledDown, cv::Size(),
	           width_scale, height_scale, cv::InterpolationFlags::INTER_LINEAR);

	cv::imwrite("images/scaled_down.png", scaledDown);
	cv::imwrite("images/scaled_up.png", scaledUp);
}

void image_mask()
{
	cv::Mat image = cv::imread( "images/img1.jpg", cv::IMREAD_COLOR);
	cv::Mat mask1 = cv::Mat::zeros(image.size(), image.type());

	cv::imwrite("images/mask1.jpg", mask1);

	mask1(cv::Range(50, 200),
	      cv::Range(170, 320)).setTo(255);

	cv::imwrite("images/mask_revised.jpg", mask1);

	//Filter high pass filter for green pixels above 50
	cv::Mat mask2;

	//remember in range here captures green pixels (BGR) greater than 50 green and less 
	cv::inRange(image, cv::Scalar(0, 50, 0),
	            cv::Scalar(150, 255, 100), mask2); //B: 150, G: 255, R: 100 upper bound

	cv::imwrite("images/mask2.jpg", mask2);
}

//Mathematical Operations
void contrast_enhancement()
{
	constexpr double enhancement_percentage = 30.0;

	cv::Mat image = cv::imread("images/img.jpg");
	cv::Mat contrastHigh = image;

	contrastHigh.convertTo(contrastHigh, CV_64F);
	contrastHigh = contrastHigh * (1 + enhancement_percentage / 100.0);
	cv::imwrite("images/highContrast.jpg", contrastHigh);
}

void brightness_enhancement()
{
	cv::Mat image = cv::imread("images/img1.jpg");

	constexpr double brightness_offset = 50;
	constexpr size_t num_channels = 3;

	cv::Mat bright_high = image;
	cv::Mat bright_high_channels[3];
	cv::split(bright_high, bright_high_channels);

#pragma omp parallel for
	for (int i = 0; i < 3; i++)
	{
		cv::add(bright_high_channels[i], brightness_offset, bright_high_channels[i]);
	}

	cv::merge(bright_high_channels, num_channels, bright_high);
	cv::imwrite("images/brighter.jpg", bright_high);

	double minVal = 0.0;
	double maxVal = 0.0;
	std::cout << "Original Image Datatype : " << type2str(image.type()) << '\n';
	std::cout << "Brightness Image Datatype : " << type2str(bright_high.type()) << '\n';

	cv::minMaxLoc(image, &minVal, &maxVal);
	std::cout << "Original Image Highest Pixel Intensity : " << maxVal << '\n';
	cv::minMaxLoc(bright_high, &minVal, &maxVal);
	std::cout << "Brightness Image Highest Pixel Intensity : " << maxVal << '\n';
}

void image_type_conversion()
{
	cv::Mat image = cv::imread("images/img1.jpg");

	constexpr double scaling_factor = 1 / 255.0;
	constexpr double shift = 0; //How much to shift values by

	image.convertTo(image, CV_32FC3, scaling_factor, shift);

	//To convert back we do the reciprocal of the scaling factor
	image.convertTo(image, CV_8UC3, 1.0 / scaling_factor, shift);
}

void typing_examples()
{
	cv::Mat image = cv::imread("images/img1.jpg");

	//This part clips pixel values
	uint8_t data[] = { 100,110,120,130 };
	cv::Mat a(2, 2, CV_8UC1, data);
	constexpr uint8_t scalar = 130;

	std::cout << a << '\n';
	std::cout << a + scalar << '\n';
	std::cout << a - scalar;

	//Solution 1: Using an OpenCV function
	cv::Mat addition;
	cv::add(a, cv::Scalar(scalar), addition);
	std::cout << addition << '\n';

	//Soltuion 2a: Convert to int
	const int data_int[] = { 100, 110, 120, 130 };
	cv::Mat b(2, 2, CV_32SC1, data_int);
	b = b + scalar;
	std::cout << b << '\n';

	b.convertTo(b, CV_8UC1);
	std::cout << b << '\n';

	//Solution 2b: Convert to normalized float32/float64
	cv::Mat a_float32;
	a.convertTo(a_float32, CV_32F, 1.0 / 255.0, 0); //Normalize range between 0 and 1
	a_float32 = a_float32 + 130.0 / 255.0;
	std::cout << a_float32;

	//Good to scale values back between 0-255 after arithmetic operations
	cv::Mat c;
	a_float32.convertTo(c, CV_32F, 255.0, 0.0);
	std::cout << c;

	//Clipped output
	cv::Mat b_uint8 = 25;
	c.convertTo(b_uint8, CV_8UC1);
	std::cout << b_uint8;
}

void brightness_and_contrast()
{
	cv::Mat image = cv::imread("images/img.jpg");

	double alpha = 1.0; /*< Simple contrast control */
	int beta = 0;       /*< Simple brightness control */

	std::cout << " Basic Linear Transforms\n";
	std::cout << "-------------------------\n";
	std::cout << "* Enter the alpha value [1.0-3.0]: ";
	std::cin >> alpha;
	std::cout << "* Enter the beta value [0-100]: ";
	std::cin >> beta;

	cv::Mat new_image = cv::Mat::zeros( image.size(), image.type());

	for (int y = 0; y < image.rows; y++)
	{
		for (int x = 0; x < image.cols; x++)
		{
			for (int c = 0; c < image.channels(); c++)
			{
				new_image.at<cv::Vec3b>(y, x)[c] = cv::saturate_cast<uchar>(alpha * image.at<cv::Vec3b>(y, x)[c] + beta);
			}
		}
	}

	imshow("Original Image", image);
	imshow("New Image", new_image);

	while (true)
	{
		if (cv::waitKey(10) >= 0)
		{
			break;
		}
	}
}

void gamma_correction()
{
	cv::Mat image = cv::imread("images/img2.jpg");

	double gamma = 0.0;
	std::cout << "Enter Gamma: ";
	std::cin >> gamma;
	cv::Mat look_up_table(1, 256, CV_8U);
	uchar* p = look_up_table.ptr();

	for (int i = 0; i < 256; i++)
	{
		p[i] = cv::saturate_cast<uchar>(cv::pow(i / 255.0, gamma) * 255.0);
	}

	cv::Mat res = image.clone();

	//Look up table is used to improve performance of the computation as only 256 values
	//Need to be calculated once
	cv::LUT(image, look_up_table, res);
}

//Annotating Images
void line_draw()
{
	cv::Mat image_line = cv::imread("images/img1.jpg");

	cv::line(image_line, cv::Point(200, 80), cv::Point(280, 80), cv::Scalar(255, 0, 0), cv::LINE_AA);
	cv::imwrite("images/img_line.jpg", image_line);
}

void circle_draw()
{
	cv::Mat image_circle = cv::imread("images/img1.jpg");
	cv::circle(image_circle, cv::Point(250, 150), 100, cv::Scalar(255, 0, 0), cv::LINE_AA);
	cv::imwrite("images/img_circle.jpg", image_circle);
}

void filled_circle()
{
	cv::Mat image_filled_circle = cv::imread("images/img1.jpg");

	//-1 thickness fills in the circle
	cv::circle(image_filled_circle, cv::Point(250, 150), 100, cv::Scalar(255, 0, 0), -1, cv::LINE_AA);

	cv::imwrite("images/img_filled_circle.jpg", image_filled_circle);
}

void ellipse_draw()
{
	cv::Mat image_ellipse = cv::imread("images/img1.jpg");

	cv::ellipse(image_ellipse, cv::Point(250, 125), cv::Point(100, 50),
	            0, 0, 360, cv::Scalar(255, 0, 0),3, cv::LINE_AA);

	cv::ellipse(image_ellipse, cv::Point(250, 125), cv::Point(100, 50),
	            90, 0, 360, cv::Scalar(0, 0, 255), 3, cv::LINE_AA);

	cv::imwrite("images/img_ellipse.jpg", image_ellipse);
}

void ellipse_draw2()
{
	cv::Mat image_ellipse2 = cv::imread("images/img1.jpg");

	// Incomplete/Open ellipse
	cv::ellipse(image_ellipse2, cv::Point(250, 125), cv::Point(100, 50), 0, 180, 360,
	            cv::Scalar(255, 0, 0), 3, cv::LINE_AA);

	// Filled ellipse
	ellipse(image_ellipse2, cv::Point(250, 125), cv::Point(100, 50), 0, 0, 180,
	        cv::Scalar(0, 0, 255), -2, cv::LINE_AA); //-2 = half filled

	cv::imwrite("images/img_ellipse2.jpg", image_ellipse2);
}

void rectangle_draw()
{
	cv::Mat image_rectangle = cv::imread("images/img1.jpg");

	cv::rectangle(image_rectangle, cv::Point(170, 50), cv::Point(300, 200),
	              cv::Scalar(255, 0, 255), 5, cv::LINE_8);

	cv::imwrite("images/img_ellipse2.jpg", image_rectangle);
}

void text_write()
{
	cv::Mat image_text = cv::imread("images/img1.jpg");
	cv::Mat image_font_scale = image_text.clone(); //font scaling example
	cv::Mat image_get_size_text = image_text.clone(); //get size example

	//cv::putText parameters
	const std::string text = "Some Text";
	constexpr double font_scale = 1.5;
	constexpr int font_face = cv::FONT_HERSHEY_SIMPLEX;
	const cv::Scalar font_color(255, 10, 10);
	constexpr int font_thickness = 2;

	cv::putText(image_text, text, cv::Point(20, 350), font_face, font_scale, font_color, font_thickness, cv::LINE_AA);

	cv::imwrite("images/img_text.jpg", image_text);

	//Font scaling
	constexpr int pixel_height = 20;

	const double font_scale2 = cv::getFontScaleFromHeight(font_face, pixel_height, font_thickness);

	std::cout << "font scale = " << font_scale2 << '\n';

	cv::putText(image_font_scale, "Sample Text", cv::Point(20, 350), font_face, font_scale, font_color, font_thickness,
	            cv::LINE_AA);

	cv::imwrite("images/img_text_scaled.jpg", image_font_scale);

	//Height and width from text
	const int image_hieght = image_get_size_text.rows;
	const int image_width = image_get_size_text.cols;

	//get the text box height and width as a baseline
	int baseline = 0;
	const cv::Size text_size = cv::getTextSize("Sample Text", font_face, font_scale, font_thickness, &baseline);

	const int text_width = text_size.width;
	const int text_height = text_size.height;

	std::cout << "Text width: " << text_width << " Text Height: " << text_height << " baseline=" << baseline << '\n';

	//get coordinates of text box bottom left corner
	//x coordinate will be such that the text is centered
	const int x_coordinate = (image_width - text_width) / 2;

	//y coordinate will be such that box is 10 pixels above the bottom
	const int y_coordinate = (image_hieght - baseline - 10);

	std::cout << "TextBox bottom left: (" << x_coordinate << ", " << y_coordinate << ")\n";

	//Draw baseline for reference
	constexpr int line_thickness = 3;
	const cv::Point line_left(x_coordinate, y_coordinate);
	cv::Point line_right(x_coordinate + text_width, y_coordinate);
	const cv::Scalar line_color = cv::Scalar(255, 0, 0);

	cv::line(image_get_size_text, line_left, line_right, line_color, line_thickness, cv::LINE_AA);

	cv::putText(image_get_size_text, "Sample Text", cv::Point(x_coordinate, y_coordinate), font_face, font_scale2,
	            font_color, font_thickness, cv::LINE_AA);

	cv::imwrite("images/img_text3.jpg", image_get_size_text);
}

//Callbacks
cv::Mat source;
cv::Point circ_center;
cv::Point circ_circumference;

void draw_circle(const int action, const int x, const int y, const int flags, void* userdata)
{
	if (action == cv::EVENT_LBUTTONDOWN)
	{
		circ_center = cv::Point(x, y);

		//Mark the center
		cv::circle(source, circ_center, 1, cv::Scalar(255, 255, 0), 2, cv::LINE_AA);
	}
	else if (action == cv::EVENT_LBUTTONUP)
	{
		circ_circumference = cv::Point(x, y);

		const float radius = sqrt(cv::pow(circ_center.x - circ_circumference.x, 2) + cv::pow(circ_center.y - circ_circumference.y, 2));

		cv::circle(source, circ_center, radius, cv::Scalar(0,255,0), 2, cv::LINE_AA);

		cv::imshow("Window", source);
	}
}

void callback_example()
{
	source = cv::imread("images/img.jpg");

	//Dummy image to be used while drawing
	const cv::Mat dummy = source.clone();

	cv::namedWindow("Window", cv::WINDOW_KEEPRATIO);

	cv::setMouseCallback("Window", draw_circle);

	int k = 0;
	while (k != 27)
	{
		cv::imshow("Window", source);
		cv::putText(source, "Choose center point to drag a circle, press esc to exit, c to clear",
		            cv::Point(10, 300), cv::FONT_HERSHEY_SIMPLEX, 2, cv::Scalar(255, 255, 255), 3);

		k = cv::waitKey(20) & 0xFF;

		if (k == 99) // clear the image
		{
			dummy.copyTo(source);
		}
	}
}
