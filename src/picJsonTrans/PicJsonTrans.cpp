#include "basicFunApi.h"
#include "PicJsonTrans.h"

#include "nlohmann-json/json.hpp"
#include "opencv/opencv.hpp"

#include <iostream>
#include <string>


namespace nsPicJsonTrans {

    void TestJson() {
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

        // ���json������̨  
        std::cout << j.dump(4) << std::endl;  // 4�������������ڸ�ʽ�����
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

}
