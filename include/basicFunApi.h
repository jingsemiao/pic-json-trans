#ifndef DLL_BF_BASICFUNAPI_H
#define DLL_BF_BASICFUNAPI_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>

#ifdef COMMONFUN_EXPORT
#define BASICFUN_API __declspec(dllexport)
#else
#define BASICFUN_API __declspec(dllimport)
#endif

namespace nsCommonFun {

	struct BASICFUN_API StDirFileInfo
	{
		StDirFileInfo();
		StDirFileInfo(StDirFileInfo* parent);
		~StDirFileInfo();
		std::string dirPath;
		std::string dirRelPath;
		std::vector<std::string> vecDirFile;
		std::vector<StDirFileInfo*> vecSonDir;
	};




	BASICFUN_API void printNumber(int a);


	//文件处理
	BASICFUN_API bool FileExist(const std::string& filePath);
	BASICFUN_API bool FileExist(const std::wstring& filePath);
	BASICFUN_API bool DirectoryPathExists(const std::filesystem::path& path);
	BASICFUN_API bool ReadFile(const std::string& filePath, std::string& text);
	BASICFUN_API StDirFileInfo* GetDirFileRecursively(const std::string& filePath);

    //字符串处理
	BASICFUN_API std::string UnicodeToUTF8(const std::wstring& ws);
	BASICFUN_API std::wstring UTF8toUnicode(const std::string& s);

}
#endif



