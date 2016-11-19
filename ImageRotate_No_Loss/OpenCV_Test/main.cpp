#include <iostream>
#include <time.h>//图像处理时间
#include <cmath>//图像对象厚度计算
#include <iomanip>  //使用setw必须使用该预编译命令

#include "cv.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;





int main()
{

	Mat inputImg, tempImg;
	inputImg = imread("C:\\Users\\LeoSpring\\Desktop\\路标破损检测\\images\\DJI_0214.JPG");			//用opencv读取图像数据
	imshow("inputImg", inputImg);

	CV_Assert(!inputImg.empty());

	float angle = 90;
	float radian = (float)(angle / 180.0 * CV_PI);

	//填充图像使其符合旋转要求
	int uniSize = (int)(max(inputImg.cols, inputImg.rows)* 1.414);
	int dx = (int)(uniSize - inputImg.cols) / 2;
	int dy = (int)(uniSize - inputImg.rows) / 2;

	copyMakeBorder(inputImg, tempImg, dy, dy, dx, dx, BORDER_CONSTANT);


	//旋轉中心
	Point2f center((float)(tempImg.cols / 2), (float)(tempImg.rows / 2));
	Mat affine_matrix = getRotationMatrix2D(center, angle, 1.0);

	//旋轉
	warpAffine(tempImg, tempImg, affine_matrix, tempImg.size());


	//旋轉后的圖像大小
	float sinVal = fabs(sin(radian));
	float cosVal = fabs(cos(radian));


	Size targetSize((int)(inputImg.cols * cosVal + inputImg.rows * sinVal),
		(int)(inputImg.cols * sinVal + inputImg.rows * cosVal));

	//剪掉四周边框
	int x = (tempImg.cols - targetSize.width) / 2;
	int y = (tempImg.rows - targetSize.height) / 2;

	Rect rect(x, y, targetSize.width, targetSize.height);
	tempImg = Mat(tempImg, rect);

	imwrite("aa.bmp", tempImg);

	cvWaitKey();
	return 0;
}