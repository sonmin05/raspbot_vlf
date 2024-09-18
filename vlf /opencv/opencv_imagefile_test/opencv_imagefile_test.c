#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <stdio.h>

#define IMG_Width     320
#define IMG_Height    240

using namespace cv;
using namespace std; 

int main(void)
{
    int img_width, img_height;
    img_width = 320;
    img_height = 240;
    
    ///////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////OpenCV 변수 선언///////////////////////////////////////////
    
    Mat mat_image_org_color;
    Mat mat_image_org_gray;
    Mat mat_image_org_gary_result;
    Mat mat_image_binary;
    Mat image;
	
    Scalar GREEN(0,255,0);
    Scalar RED(0,0,255);
    Scalar BLUE(255,0,0);
    Scalar YELLOW(0,255,255);
    //////////////////////////////////////////////////////////////////////////////////////
    
    mat_image_org_color = imread("/home/pi/Team_aMAP/OpenCV_Code/opencv/opencv_imagefile_test/line_1.jpg");
    
    img_width = mat_image_org_color.size().width;
    img_height = mat_image_org_color.size().height;
    
    
    printf("Image size[%3d,%3d]\n", img_width,img_height);
    
    namedWindow("Display window", CV_WINDOW_NORMAL);
    resizeWindow("Display window", img_width,img_height);
    moveWindow("Display window", 10, 10);
    
    namedWindow("Gray Image window", CV_WINDOW_NORMAL);
    resizeWindow("Gray Image window", img_width,img_height);
    moveWindow("Gray Image window", 700, 10);
    
    namedWindow("Binary Image window", CV_WINDOW_NORMAL);
    resizeWindow("Binary Image window", img_width,img_height);
    moveWindow("Binary Image window", 10, 500);
	
    while(1)
    { 
      cvtColor( mat_image_org_color, mat_image_org_gray, CV_RGB2GRAY );               // color to gray conversion
      threshold(mat_image_org_gray, mat_image_binary, 200, 255, THRESH_BINARY);
       
      if (mat_image_org_color.empty())
      {
        cerr << "Empty Video \n";
        break;
      }
    
     imshow("Display window", mat_image_org_color);
     imshow("Gray Image window", mat_image_org_gray);
     imshow("Binary window", mat_image_binary);    
     if(waitKey(10) > 0)
        break;
    }
    
    destroyAllWindows();
    
   return 0;	
}
