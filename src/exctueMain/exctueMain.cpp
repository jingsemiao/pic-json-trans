#include "basicFunApi.h"
#include "PicJsonTrans.h"

#include "opencv/opencv.hpp"
#include "nlohmann-json/json.hpp"
#include <windows.h>

#include <iostream>
#include <filesystem>

// ������ɫͼ�񲢽����ش���vector  
void storePixelsInVector(const cv::Mat& img, std::vector<cv::Vec3b>& pixels) {
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
cv::Mat restoreMatFromVector(int rows, int cols, const std::vector<cv::Vec3b>& pixels) {
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
	// ����ͼ���ÿһ�к�ÿһ��  
	for (int y = 0; y < mat1.rows; y++) {
		for (int x = 0; x < mat1.cols; x++) {
			// ���ʵ�ǰ���ص�BGRֵ  
			cv::Vec3b pixel = mat1.at<cv::Vec3b>(y, x);
			uchar a1 = pixel[0];
			uchar a2 = pixel[1];
			uchar a3 = pixel[2];
			//printf("%d %d %d \n",a1,a2,a3);

			// ������ֵ��ӵ�vector��  
			pixels2.push_back(pixel);
		}
	}
	int xas = 456;


	// �洢����  
	std::vector<cv::Vec3b> pixels;
	nsPicJsonTrans::StorePixelsInVector(mat1, pixels);
	// ��ԭͼ��  
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
				// ��ȡ���ļ���
				
				std::string filename = entry.path().filename().string();
				// ��ȡ���·��
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


using json = nlohmann::json;

// ���� BGR �ṹ��
struct BGR {
	int b;
	int g;
	int r;
};

// ���� PicItem �ṹ��
struct PicItem {
	std::string Text;
	std::vector<std::vector<BGR>> array;
	int number;
};

// ����� JSON �� BGR �ṹ���ת��
void from_json(const json& j, BGR& bgr) {
	bgr.b = j.at("BGR").at(0);
	bgr.g = j.at("BGR").at(1);
	bgr.r = j.at("BGR").at(2);
}

// ����� JSON �� PicItem �ṹ���ת��
void from_json(const json& j, PicItem& p) {
	j.at("Text").get_to(p.Text);
	j.at("number").get_to(p.number);

	const json& jsonArray = j.at("array");
	for (const auto& row : jsonArray) {
		std::vector<BGR> rowVector;
		for (const auto& bgrObj : row) {
			BGR bgr;
			from_json(bgrObj, bgr);
			rowVector.push_back(bgr);
		}
		p.array.push_back(rowVector);
	}
}


void ReadTestJieXiJson()
{
	std::ifstream file("C:\\test\\jsonTest.json");
	if (!file.is_open()) {
		std::cerr << "Failed to open file." << std::endl;
		return;
	}

	// ���� JSON ����
	json j;
	file >> j;

	// ��� picList �Ƿ����
	if (j.contains("picList")) {
		const json& picList = j.at("picList");

		// �� picList ת��Ϊ vector<PicItem>
		std::vector<PicItem> picItems;
		for (const auto& item : picList) {
			PicItem picItem;
			from_json(item, picItem);
			picItems.push_back(picItem);
		}

		// ������
		for (const auto& picItem : picItems) {
			std::cout << "Text: " << picItem.Text << std::endl;
			std::cout << "Array: " << std::endl;
			for (const auto& row : picItem.array) {
				for (const auto& bgr : row) {
					std::cout << "BGR: [" << bgr.b << ", " << bgr.g << ", " << bgr.r << "] ";
				}
				std::cout << std::endl;
			}
			std::cout << "Number: " << picItem.number << std::endl;
			std::cout << "----------------------" << std::endl;
		}
	}
	else {
		std::cerr << "Key 'picList' does not exist in the JSON object." << std::endl;
	}

	std::cout << "TestJieXi Json End" << std::endl;
}

int main() { 
	ReadTestJieXiJson();
	

	char buffer[MAX_PATH];
	if (GetModuleFileNameA(NULL, buffer, MAX_PATH) != 0) {
		std::string strbuffer(buffer);
		std::cout << "��ǰ�ļ�·��: " << strbuffer << std::endl;
	}
	else {
		std::cout << "�޷���ȡ�ļ�·��" << std::endl;
	}
	

	std::string strPathTest = "C:\\test";
	nsCommonFun::StDirFileInfo* ptrInfo = nsCommonFun::GetDirFileRecursively(strPathTest);
	delete ptrInfo;

	recursiveDirectoryTraversal(strPathTest);

	// cv::cvtColor(input, output, cv::COLOR_BGR2GRAY);

	// windows�е������ַ�Ĭ����Gbk,���ļ��ַ�Ҳ��Ĭ��gbk����ôֱ�������������ܹ�ʶ�𵽵�
	// ֱ�ӵ�opencv��Ҳ�ܹ�ʶ��
	nsCommonFun::printNumber(100);
	nsPicJsonTrans::FunTest();
	//"C:\\test\\MTXX_20191108172152.jpg" strResNamePrefix
	TestMat("C:\\test\\MTXX_20191108172152.jpg", "MTXX_20191108172152");
	TestMat("C:\\test\\����\\����.jpg","����");
	int kkk = 456;
}

