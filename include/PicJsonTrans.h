#ifndef DLL_PICJSONTRANS_API_H
#define DLL_PICJSONTRANS_API_H
#include <iostream>
#include <string>
#include <vector>


#ifdef PICJSONTRANS_EXPORT
#define PICJSONTRANS_API __declspec(dllexport)
#else
#define PICJSONTRANS_API __declspec(dllimport)
#endif

namespace nsPicJsonTrans {
    PICJSONTRANS_API void FunTest();

}
#endif