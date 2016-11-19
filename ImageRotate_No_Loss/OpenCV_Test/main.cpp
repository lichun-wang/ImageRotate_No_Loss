#include <iostream>
#include <time.h>//ͼ����ʱ��
#include <cmath>//ͼ������ȼ���
#include <iomanip>  //ʹ��setw����ʹ�ø�Ԥ��������

#include "cv.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;





int main()
{

	Mat inputImg, tempImg;
	inputImg = imread("C:\\Users\\LeoSpring\\Desktop\\·��������\\images\\DJI_0214.JPG");			//��opencv��ȡͼ������
	imshow("inputImg", inputImg);

	CV_Assert(!inputImg.empty());

	float angle = 90;
	float radian = (float)(angle / 180.0 * CV_PI);

	//���ͼ��ʹ�������תҪ��
	int uniSize = (int)(max(inputImg.cols, inputImg.rows)* 1.414);
	int dx = (int)(uniSize - inputImg.cols) / 2;
	int dy = (int)(uniSize - inputImg.rows) / 2;

	copyMakeBorder(inputImg, tempImg, dy, dy, dx, dx, BORDER_CONSTANT);


	//���D����
	Point2f center((float)(tempImg.cols / 2), (float)(tempImg.rows / 2));
	Mat affine_matrix = getRotationMatrix2D(center, angle, 1.0);

	//���D
	warpAffine(tempImg, tempImg, affine_matrix, tempImg.size());


	//���D��ĈD���С
	float sinVal = fabs(sin(radian));
	float cosVal = fabs(cos(radian));


	Size targetSize((int)(inputImg.cols * cosVal + inputImg.rows * sinVal),
		(int)(inputImg.cols * sinVal + inputImg.rows * cosVal));

	//�������ܱ߿�
	int x = (tempImg.cols - targetSize.width) / 2;
	int y = (tempImg.rows - targetSize.height) / 2;

	Rect rect(x, y, targetSize.width, targetSize.height);
	tempImg = Mat(tempImg, rect);

	imwrite("aa.bmp", tempImg);

	cvWaitKey();
	return 0;
}