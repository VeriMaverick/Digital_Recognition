//Digital image processing three items: digital recognition
//Author:WangMingJie
//Date:2023/11/24
//Version:1.0

#include"iostream"
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>

using namespace cv;
using namespace std;

//模板轮廓提取函数
void FindContoursAndRectangles(Mat& src)
{
    Mat gray, edge, dst;
    cvtColor(src, gray, COLOR_BGR2GRAY);	                                                        //转换为灰度图像
    GaussianBlur(gray, gray, Size(3, 3), 0, 0);	                                                    //高斯滤波
    Canny(gray, edge, 50, 150, 3);	                                                                //边缘检测
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(edge, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));	    //查找轮廓
    dst = Mat::zeros(src.size(), CV_8UC3);
    vector<Rect> rects;
    for (int i = 0; i < contours.size(); i++)
    {
        Rect rect = boundingRect(contours[i]);	                                                    //获取轮廓的矩形块
        if (rect.width > 10 && rect.height > 10)	                                                //过滤掉过小的矩形块
        {
            rects.push_back(rect);
            drawContours(dst, contours, i, Scalar(255, 255, 255), 1, 1, hierarchy, 1, Point(0));    //绘制轮廓 drawContours (绘制轮廓的图像，轮廓，轮廓索引，颜色，厚度，线型，层次结构，最大层次，偏移量)
            rectangle(dst, rect, Scalar(0, 255, 0), 0);	                                            //绘制矩形块
        }
    }
    imshow("轮廓图像", dst);
    sort(rects.begin(), rects.end(), [](Rect a, Rect b) {return a.x < b.x; });	                    //按矩形块的x坐标排序
    for (int i = 0; i < rects.size(); i++)
    {
        Mat roi = src(rects[i]);	                                                                //获取矩形块对应的图像区域
        Mat gray_roi, binary_roi;
        cvtColor(roi, gray_roi, COLOR_BGR2GRAY);	                                                //转换为灰度图像
        threshold(gray_roi, binary_roi, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);	                //二值化
        vector<vector<Point>> contours_roi;
        vector<Vec4i> hierarchy_roi;
        findContours(binary_roi, contours_roi, hierarchy_roi, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));	//查找轮廓
        for (int j = 0; j < contours_roi.size(); j++)
        {
            Rect rect_roi = boundingRect(contours_roi[j]);	                                        //获取轮廓的矩形块
            if (rect_roi.width > 100 && rect_roi.height > 200)	                                    //过滤掉过小的矩形块
            {
                rectangle(roi, rect_roi, Scalar(255, 255, 255), 0);	                                //绘制矩形块
            }
        }
        imshow(to_string(i), roi);
        imwrite("template"+ to_string(i) + ".png", roi);
    }
}

int main()
{
    //读取模板
	Mat src = imread("template.png");
	imshow("模板图像", src);
	FindContoursAndRectangles(src);
    //读取模板
    Mat src0 = imread("template0.png");
    Mat src1 = imread("template1.png");
    Mat src2 = imread("template2.png");
    Mat src3 = imread("template3.png");
    Mat src4 = imread("template4.png");
    Mat src5 = imread("template5.png");
    Mat src6 = imread("template6.png");
    Mat src7 = imread("template7.png");
    Mat src8 = imread("template8.png");
    Mat src9 = imread("template9.png");

	waitKey(0);


	return 0;
}