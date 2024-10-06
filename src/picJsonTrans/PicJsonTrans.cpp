#include "basicFunApi.h"
#include "PicJsonTrans.h"

#include "nlohmann-json/json.hpp"
#include "opencv/opencv.hpp"

#include "MyCvProcess.h"
#include <iostream>
#include <string>


namespace nsPicJsonTrans {

    void TestJson() {
        std::cout << "TestJson" << std::endl;
        std::cout << "" << std::endl;

        using json = nlohmann::json;
        json j;
        

        // �������  
        j["number"] = 123;

        // ����ַ���  
        j["string"] = "Hello, World!";

        // ���һ�����飬�����������Ԫ��  
        json arrayPart;
        arrayPart.push_back("element1");
        arrayPart.push_back(456);
        arrayPart.push_back(true);  // JSON��Ҳ���԰�������ֵ  
        j["array"] = arrayPart;

        // ����Լ�����Ӹ���ļ�ֵ�Ժ�����...  
        json jTop;
        json jTopArray;
        jTopArray.push_back(j);
        jTop["picList"] = jTopArray;

        // ���json������̨  
        std::cout << jTop.dump(4) << std::endl;  // 4�������������ڸ�ʽ�����
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



    // ������ɫͼ�񲢽����ش���vector  
    void StorePixelsInVector(const cv::Mat& img, std::vector<cv::Vec3b>& pixels) {
        // ȷ��img��һ����ͨ��ͼ��  
        if (img.channels() != 3) {
            std::cerr << "Error: Image must be color (3 channels)." << std::endl;
            return;
        }

        //cv::Mat img
        // ����ͼ���ÿһ������  
        for (int y = 0; y < img.rows; ++y) {
            for (int x = 0; x < img.cols; ++x) {
                // ��ȡ��ǰ���ص�ֵ��BGR��  
                cv::Vec3b pixel = img.at<cv::Vec3b>(y, x);
                // ������ֵ��ӵ�vector��  
                pixels.push_back(pixel);
            }
        }
    }


    // ����vector��ͼ�񳤿�ԭcv::Mat  
    cv::Mat RestoreMatFromVector(int rows, int cols, const std::vector<cv::Vec3b>& pixels) {
        // ����һ����ԭʼͼ����ͬ���ͺʹ�С��Mat  
        cv::Mat restoredImg(rows, cols, CV_8UC3);
        // ����vector�е�ÿһ�����أ������õ���Mat�Ķ�Ӧλ��  
        for (int y = 0; y < rows; ++y) {
            for (int x = 0; x < cols; ++x) {
                // ע�������ļ��㷽ʽ����Ϊvector�����Դ洢��  
                int index = y * cols + x;
                if (index < pixels.size()) {
                    restoredImg.at<cv::Vec3b>(y, x) = pixels[index];
                }
                // ���pixels��sizeС��rows*cols�������©��һЩ���أ����Ը�����Ҫ��Ӵ�����  
            }
        }
        return restoredImg;
    }

}
