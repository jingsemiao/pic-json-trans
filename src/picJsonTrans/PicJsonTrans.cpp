#include "basicFunApi.h"
#include "PicJsonTrans.h"

#include "nlohmann-json/json.hpp"

#include <iostream>
#include <string>


namespace nsPicJsonTrans {

    void TestJson() {
        using json = nlohmann::json;
        json j;

        // 添加数字  
        j["number"] = 123;

        // 添加字符串  
        j["string"] = "Hello, World!";

        // 添加一个数组，并在其中添加元素  
        json arrayPart;
        arrayPart.push_back("element1");
        arrayPart.push_back(456);
        arrayPart.push_back(true);  // JSON中也可以包含布尔值  
        j["array"] = arrayPart;

        // 你可以继续添加更多的键值对和数组...  

        // 输出json到控制台  
        std::cout << j.dump(4) << std::endl;  // 4是缩进级别，用于格式化输出
    }

    void FunTest() {
        int kkk = 456;
        std::cout << "Is nsPicJsonTrans" << std::endl;
        TestJson();
    }

}
