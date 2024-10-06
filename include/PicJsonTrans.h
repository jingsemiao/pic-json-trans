#ifndef DLL_PICJSONTRANS_API_H
#define DLL_PICJSONTRANS_API_H
#include <iostream>
#include <string>
#include <vector>
#include "nlohmann-json/json.hpp"
#include "opencv/opencv.hpp"

//在PicJsonTrans工程中能够识别通过，但是main工程中的cmake因为没有包含会导致编译失败
//#include "picJsonTrans/MyCvProcess.h"


#ifdef PICJSONTRANS_EXPORT
#define PICJSONTRANS_API __declspec(dllexport)
#else
#define PICJSONTRANS_API __declspec(dllimport)
#endif

namespace nsPicJsonTrans {

    static const std::string strJsonSymbol_OnePic_PicName = "PicName";
    static const std::string strJsonSymbol_OnePic_Dir = "Dir";
    static const std::string strJsonSymbol_OnePic_Rows = "Rows";
    static const std::string strJsonSymbol_OnePic_Cols = "Cols";
    static const std::string strJsonSymbol_OnePic_Datas = "Datas";

    PICJSONTRANS_API void FunTest();
    PICJSONTRANS_API bool TransOneCvMatToJson(cv::Mat& matSrc,std::string strFileName ,nlohmann::json& jsonVar);


    PICJSONTRANS_API void StorePixelsInVector(const cv::Mat& img, std::vector<cv::Vec3b>& pixels);
    PICJSONTRANS_API cv::Mat RestoreMatFromVector(int rows, int cols, const std::vector<cv::Vec3b>& pixels);
}
#endif