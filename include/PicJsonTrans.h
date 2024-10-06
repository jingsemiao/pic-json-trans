#ifndef DLL_PICJSONTRANS_API_H
#define DLL_PICJSONTRANS_API_H
#include <iostream>
#include <string>
#include <vector>
//#include "MyCvProcess.h"
#include "nlohmann-json/json.hpp"
#include "opencv/opencv.hpp"


#ifdef PICJSONTRANS_EXPORT
#define PICJSONTRANS_API __declspec(dllexport)
#else
#define PICJSONTRANS_API __declspec(dllimport)
#endif

namespace nsPicJsonTrans {
    PICJSONTRANS_API void FunTest();
    PICJSONTRANS_API bool TransOneCvMatToJson(cv::Mat& matSrc,std::string strFileName ,nlohmann::json& jsonVar);


    PICJSONTRANS_API void StorePixelsInVector(const cv::Mat& img, std::vector<cv::Vec3b>& pixels);
    PICJSONTRANS_API cv::Mat RestoreMatFromVector(int rows, int cols, const std::vector<cv::Vec3b>& pixels);
}
#endif