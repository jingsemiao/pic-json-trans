#include "basicFunApi.h"
#include "PicJsonTrans.h"

#include "opencv/opencv.hpp"
#include "nlohmann-json/json.hpp"
#include <windows.h>

#include <iostream>
#include <filesystem>

// 遍历彩色图像并将像素存入vector  
void storePixelsInVector(const cv::Mat& img, std::vector<cv::Vec3b>& pixels) {
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
cv::Mat restoreMatFromVector(int rows, int cols, const std::vector<cv::Vec3b>& pixels) {
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

void TestMat(std::string strFilePath,std::string strResNamePrefix)
{
	bool bFileExist = nsCommonFun::FileExist(strFilePath);
	std::cout << "FileExist = " << bFileExist << " , path = " << strFilePath << std::endl;
	cv::Mat mat1 = cv::imread(strFilePath, cv::IMREAD_COLOR);
	int nType = mat1.type();
	int depth = mat1.depth();
	int channels = mat1.channels();
	std::cout << "nType = " << nType << " ,depth = " << depth
		<< "channels = " << channels << std::endl;
	std::string strRes = strResNamePrefix + "_res.jpg";
	cv::imwrite(strRes,mat1);

	std::vector<cv::Vec3b> pixels2;
	// 遍历图像的每一行和每一列  
	for (int y = 0; y < mat1.rows; y++) {
		for (int x = 0; x < mat1.cols; x++) {
			// 访问当前像素的BGR值  
			cv::Vec3b pixel = mat1.at<cv::Vec3b>(y, x);
			uchar a1 = pixel[0];
			uchar a2 = pixel[1];
			uchar a3 = pixel[2];
			//printf("%d %d %d \n",a1,a2,a3);

			// 将像素值添加到vector中  
			pixels2.push_back(pixel);
		}
	}
	int xas = 456;


	// 存储像素  
	std::vector<cv::Vec3b> pixels;
	nsPicJsonTrans::StorePixelsInVector(mat1, pixels);
	// 复原图像  
	cv::Mat restoredImg = nsPicJsonTrans::RestoreMatFromVector(mat1.rows, mat1.cols, pixels);
	std::string strResCopy = strResNamePrefix + "_resCopy.jpg";
	cv::imwrite(strResCopy, restoredImg);
}


void recursiveDirectoryTraversal(const std::filesystem::path& path) {
	try {
		for (const auto& entry : std::filesystem::recursive_directory_iterator(path)) {
			if (std::filesystem::is_directory(entry.status())) {
				std::cout << "Directory: " << entry.path() << std::endl;
			}
			else if (std::filesystem::is_regular_file(entry.status())) {
				// 获取纯文件名
				
				std::string filename = entry.path().filename().string();
				// 获取相对路径
				std::string relative_path = std::filesystem::relative(entry.path(), path).string();
				std::cout << "relative_path: " << relative_path << ",FileName : " << filename << std::endl;
			}
			else {
				std::cout << "Other: " << entry.path() << std::endl;
			}
		}
	}
	catch (const std::filesystem::filesystem_error& e) {
		std::cerr << "Filesystem error: " << e.what() << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "Exception: " << e.what() << std::endl;
	}
}

int main() { 

	

	char buffer[MAX_PATH];
	if (GetModuleFileNameA(NULL, buffer, MAX_PATH) != 0) {
		std::string strbuffer(buffer);
		std::cout << "当前文件路径: " << strbuffer << std::endl;
	}
	else {
		std::cout << "无法获取文件路径" << std::endl;
	}
	

	std::string strPathTest = "C:\\test";
	nsCommonFun::StDirFileInfo* ptrInfo = nsCommonFun::GetDirFileRecursively(strPathTest);
	delete ptrInfo;

	recursiveDirectoryTraversal(strPathTest);

	// cv::cvtColor(input, output, cv::COLOR_BGR2GRAY);

	// windows中的中文字符默认是Gbk,若文件字符也是默认gbk，那么直接输入中文是能够识别到的
	// 直接到opencv中也能够识别到
	nsCommonFun::printNumber(100);
	nsPicJsonTrans::FunTest();
	//"C:\\test\\MTXX_20191108172152.jpg" strResNamePrefix
	TestMat("C:\\test\\MTXX_20191108172152.jpg", "MTXX_20191108172152");
	TestMat("C:\\test\\中文\\测试.jpg","测试");
	int kkk = 456;
}

