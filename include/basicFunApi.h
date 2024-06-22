#ifndef DLL_BF_BASICFUNAPI_H
#define DLL_BF_BASICFUNAPI_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#ifdef COMMONFUN_EXPORT
#define BASICFUN_API __declspec(dllexport)
#else
#define BASICFUN_API __declspec(dllimport)
#endif

namespace nsCommonFun {
	BASICFUN_API void printNumber(int a);


	//文件处理
	BASICFUN_API bool FileExist(const std::string& filePath);
	BASICFUN_API bool FileExist(const std::wstring& filePath);
	BASICFUN_API bool ReadFile(const std::string& filePath, std::string& text);

    //字符串处理
	BASICFUN_API std::string UnicodeToUTF8(const std::wstring& ws);
	BASICFUN_API std::wstring UTF8toUnicode(const std::string& s);

}
#endif



