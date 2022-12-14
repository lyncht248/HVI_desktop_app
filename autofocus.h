#ifndef AUTOFOCUS_H
#define AUTOFOCUS_H

#include <opencv2/highgui.hpp>

//Global Variables
//extern std::atomic<bool> bAutofocusing; //Flag that controls the autofocusing while() loop
//extern std::atomic<bool> bNewImage; //Flag that is 1 for when the buffer image is new, 0 when buffer image is old


// extern unsigned char* img_read_buf; // Video capture. Accessed by T1.
// extern unsigned char* img_transfer_buf; // Transfer. Accessed by T1 and T2.
// extern unsigned char* img_calc_buf; // Calculation. Accessed by T2.
//extern std::mutex mtx; 

class autofocus { //This object handles autofocusing
  public:

  void run(); 

  //thread for capturing video from the tilted camera
  static void capturevideo();

  //computes the location of best-focus, from 8 to 310
  int computebestfocus (cv::Mat image, int imgHeight, int imgWidth); 


  private:
  //computes the sharpness curve along the horizontal of the image using a sharpness algorithm
  std::vector<double> computesharpness(cv::Mat image, int imgHeight, int imgWidth, int kernel);
 
  //computes the sharpness score for a given portion of imagedata
  cv::Scalar robertscross(cv::Mat imagedata); 
  cv::Scalar tenengrad(cv::Mat imagedata);
  cv::Scalar vollath(cv::Mat imagedata);
  cv::Scalar canny(cv::Mat imagedata);

 
  //fits a normal curve to the given curve, which avoids local maxima
  std::vector<double> fitnormalcurve(std::vector<double> curve, int kernel);
  double normpdf(double x, double u, double s); //helper function

};

#endif // AUTOFOCUS_H