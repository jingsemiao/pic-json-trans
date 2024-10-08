#include "basicFunApi.h"
#include "PicJsonTrans.h"

#include "nlohmann-json/json.hpp"
#include "opencv/opencv.hpp"

#include "MyCvProcess.h"
#include <iostream>
#include <string>


namespace nsPicJsonTrans {

    nlohmann::json TestOnePicJson(int hang,int lie,std::string strText)
    {
        using json = nlohmann::json;
        json j;

        if (hang <= 0) {
            hang = 1;
        }

        // 添加数字  
        j["number"] = hang;

        // 添加字符串  
        j["Text"] = strText;

        // 添加一个数组，并在其中添加元素  
        
        json ToparrayPart;
        for (int row = 0; row < hang; row++) {
            json AraryHang;
            AraryHang.clear();
            for (int col = 0; col < lie; col++) {
                json arraryLie;
                arraryLie.clear();

                json ArrayThrid_BGR;
                ArrayThrid_BGR.clear();

                ArrayThrid_BGR.push_back(hang + 10 * row + col + 1);
                ArrayThrid_BGR.push_back(hang + 10 * row + col + 2);
                ArrayThrid_BGR.push_back(hang + 10 * row + col + 3);
                arraryLie["BGR"] = ArrayThrid_BGR;
                //arraryLie.push_back(ArrayThrid_BGR);

                AraryHang.push_back(arraryLie);
            }


            ToparrayPart.push_back(AraryHang);
        }


        
        //arrayPart.push_back("element1");
        //ToparrayPart.push_back(number+100);
        //ToparrayPart.push_back(number + 101);
        //ToparrayPart.push_back(number + 102);
        //ToparrayPart.push_back(ArarySecond);



        //arrayPart.push_back(true);  // JSON中也可以包含布尔值  
        j["array"] = ToparrayPart;
        return j;
    }

    void TestJson() {
        std::cout << "TestJson" << std::endl;
        std::cout << "" << std::endl;

        using json = nlohmann::json;
        json j;
        

        // 添加数字  
        j["number"] = 123;

        // 添加字符串  
        j["string"] = "Hello, World!";

        // 添加一个数组，并在其中添加元素  
        json arrayPart;
        //arrayPart.push_back("element1");
        arrayPart.push_back(456);
        arrayPart.push_back(789);
        arrayPart.push_back(123);
        //arrayPart.push_back(true);  // JSON中也可以包含布尔值  
        j["array"] = arrayPart;

        // 你可以继续添加更多的键值对和数组...  
        json jTop;
        json jTopArray;
        json pic1 = TestOnePicJson(1,2,"hello");
        json pic2 = TestOnePicJson(2, 3,"test");
        jTopArray.push_back(pic1);
        jTopArray.push_back(pic2);
        jTop["picList"] = jTopArray;

        // 输出json到控制台  
        std::cout << jTop.dump(4) << std::endl;  // 4是缩进级别，用于格式化输出
        int kkkl = 412;
    }

    void TestCv()
    {
        cv::Mat mat1;
        if (mat1.empty()) {

        }
        int kkk = 456;
    }

    void FunTest() {
        std::cout << "Is nsPicJsonTrans" << std::endl;
        TestJson();
        TestCv();
        int kkk = 456;
    }

    bool TransOneCvMatToJson(cv::Mat& matSrc, std::string strFileName,nlohmann::json& jsonVar)
    {
        if (matSrc.empty() == true || matSrc.rows <= 0 || matSrc.cols <= 0) {
            return false;
        }
        jsonVar.clear();
        
        return true;
    }



    // 遍历彩色图像并将像素存入vector  
    void StorePixelsInVector(const cv::Mat& img, std::vector<cv::Vec3b>& pixels) {
        // 确保img是一个三通道图像  
        if (img.channels() != 3) {
            std::cerr << "Error: Image must be color (3 channels)." << std::endl;
            return;
        }

        //cv::Mat img
        // 遍历图像的每一个像素  
        for (int y = 0; y < img.rows; ++y) {
            for (int x = 0; x < img.cols; ++x) {
                // 获取当前像素的值（BGR）  
                cv::Vec3b pixel = img.at<cv::Vec3b>(y, x);
                // 将像素值添加到vector中  
                pixels.push_back(pixel);
            }
        }
    }


    // 根据vector和图像长宽复原cv::Mat  
    cv::Mat RestoreMatFromVector(int rows, int cols, const std::vector<cv::Vec3b>& pixels) {
        // 创建一个与原始图像相同类型和大小的Mat  
        cv::Mat restoredImg(rows, cols, CV_8UC3);
        // 遍历vector中的每一个像素，并设置到新Mat的对应位置  
        for (int y = 0; y < rows; ++y) {
            for (int x = 0; x < cols; ++x) {
                // 注意索引的计算方式，因为vector是线性存储的  
                int index = y * cols + x;
                if (index < pixels.size()) {
                    restoredImg.at<cv::Vec3b>(y, x) = pixels[index];
                }
                // 如果pixels的size小于rows*cols，这里会漏掉一些像素，可以根据需要添加错误处理  
            }
        }
        return restoredImg;
    }

}
