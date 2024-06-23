#include "basicFunApi.h"
#include "PicJsonTrans.h"

#include "nlohmann-json/json.hpp"

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

    void FunTest() {
        int kkk = 456;
        std::cout << "Is nsPicJsonTrans" << std::endl;
        TestJson();
    }

}
