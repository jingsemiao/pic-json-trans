#include "basicFunApi.h"

namespace nsCommonFun {

    StDirFileInfo::StDirFileInfo()
    {
    }

    StDirFileInfo::StDirFileInfo(StDirFileInfo* parent)
    {
        if (parent) {
            parent->vecSonDir.push_back(this);
        }
    }

    StDirFileInfo::~StDirFileInfo()
    {
        // 删除所有子节点
        std::cout << "\n\n" << std::endl;
        std::cout << "~StDirFileInfo() dirPath = " << dirPath  << "   ,relPath =  " << dirRelPath << std::endl;
        for (std::string strFile : vecDirFile) {
            std::cout << "FileName = " << strFile << std::endl;
        }

        for (StDirFileInfo* child : vecSonDir) {
            delete child;
        }
        vecSonDir.clear();
    }

	void printNumber(int a) {
		std::cout << "number == " << a << std::endl;
	}


    bool DirectoryPathExists(const std::filesystem::path& path) {
        return std::filesystem::exists(path) && std::filesystem::is_directory(path);
    }

    bool FileExist(const std::string& filePath) {
        std::fstream inFile(filePath);
        return inFile.is_open();
    }

    bool FileExist(const std::wstring& filePath) {
        std::fstream inFile(filePath);
        return inFile.is_open();
    }


    bool ReadFile(const std::string& filePath,std::string& text) {
        std::ifstream reFile(filePath);
        if (!reFile.is_open()) {
            return false;
        }
        int kkk = 456;
        return true;
    }

    StDirFileInfo* TraverseDirectory(const std::filesystem::path& topPath,const std::filesystem::path curPath, StDirFileInfo* parentInfo)
    {
        if (DirectoryPathExists(curPath) == false) {
            return nullptr;
        }
        StDirFileInfo* ptrRes = new StDirFileInfo();
        if (parentInfo) {
            parentInfo->vecSonDir.push_back(ptrRes);
        }

        ptrRes->dirPath = curPath.string();
        std::string relative_path = std::filesystem::relative(curPath, topPath).string();
        ptrRes->dirRelPath = relative_path;

        std::vector<std::filesystem::path> vecSonDir;
        for (const auto& entry : std::filesystem::directory_iterator(curPath)) {
            if (std::filesystem::is_directory(entry.status())) {
                vecSonDir.push_back(entry.path());
            }
            else if (std::filesystem::is_regular_file(entry.status())) {
                // 获取纯文件名
                std::string filename = entry.path().filename().string();
                ptrRes->vecDirFile.push_back(filename);
            }
        }

        for (std::filesystem::path sonPath : vecSonDir) {
            TraverseDirectory(topPath, sonPath, ptrRes);
        }

        return ptrRes;
    }

    StDirFileInfo* GetDirFileRecursively(const std::string& filePath)
    {
        if (DirectoryPathExists(filePath) == false) {
            return nullptr;
        }
        StDirFileInfo* ptrRes = TraverseDirectory(filePath, filePath,nullptr);
        return ptrRes;
    }

    std::wstring UTF8toUnicode(const std::string& s)
    {
        std::wstring ws;
        wchar_t wc;
        for (int i = 0; i < s.length(); )
        {
            char c = s[i];
            if ((c & 0x80) == 0)
            {
                wc = c;
                ++i;
            }
            else if ((c & 0xE0) == 0xC0)
            {
                wc = (s[i] & 0x1F) << 6;
                wc |= (s[i + 1] & 0x3F);
                i += 2;
            }
            else if ((c & 0xF0) == 0xE0)
            {
                wc = (s[i] & 0xF) << 12;
                wc |= (s[i + 1] & 0x3F) << 6;
                wc |= (s[i + 2] & 0x3F);
                i += 3;
            }
            else if ((c & 0xF8) == 0xF0)
            {
                wc = (s[i] & 0x7) << 18;
                wc |= (s[i + 1] & 0x3F) << 12;
                wc |= (s[i + 2] & 0x3F) << 6;
                wc |= (s[i + 3] & 0x3F);
                i += 4;
            }
            else if ((c & 0xFC) == 0xF8)
            {
                wc = (s[i] & 0x3) << 24;
                wc |= (s[i] & 0x3F) << 18;
                wc |= (s[i] & 0x3F) << 12;
                wc |= (s[i] & 0x3F) << 6;
                wc |= (s[i] & 0x3F);
                i += 5;
            }
            else if ((c & 0xFE) == 0xFC)
            {
                wc = (s[i] & 0x1) << 30;
                wc |= (s[i] & 0x3F) << 24;
                wc |= (s[i] & 0x3F) << 18;
                wc |= (s[i] & 0x3F) << 12;
                wc |= (s[i] & 0x3F) << 6;
                wc |= (s[i] & 0x3F);
                i += 6;
            }
            ws += wc;
        }
        return ws;
    }

    std::string UnicodeToUTF8(const std::wstring& ws)
    {
        std::string s;
        for (int i = 0; i < ws.size(); ++i)
        {
            wchar_t wc = ws[i];
            if (0 <= wc && wc <= 0x7f)
            {
                s += (char)wc;
            }
            else if (0x80 <= wc && wc <= 0x7ff)
            {
                s += (0xc0 | (wc >> 6));
                s += (0x80 | (wc & 0x3f));
            }
            else if (0x800 <= wc && wc <= 0xffff)
            {
                s += (0xe0 | (wc >> 12));
                s += (0x80 | ((wc >> 6) & 0x3f));
                s += (0x80 | (wc & 0x3f));
            }
            else if (0x10000 <= wc && wc <= 0x1fffff)
            {
                s += (0xf0 | (wc >> 18));
                s += (0x80 | ((wc >> 12) & 0x3f));
                s += (0x80 | ((wc >> 6) & 0x3f));
                s += (0x80 | (wc & 0x3f));
            }
            else if (0x200000 <= wc && wc <= 0x3ffffff)
            {
                s += (0xf8 | (wc >> 24));
                s += (0x80 | ((wc >> 18) & 0x3f));
                s += (0x80 | ((wc >> 12) & 0x3f));
                s += (0x80 | ((wc >> 6) & 0x3f));
                s += (0x80 | (wc & 0x3f));
            }
            else if (0x4000000 <= wc && wc <= 0x7fffffff)
            {
                s += (0xfc | (wc >> 30));
                s += (0x80 | ((wc >> 24) & 0x3f));
                s += (0x80 | ((wc >> 18) & 0x3f));
                s += (0x80 | ((wc >> 12) & 0x3f));
                s += (0x80 | ((wc >> 6) & 0x3f));
                s += (0x80 | (wc & 0x3f));
            }
        }
        return s;
    }


}


