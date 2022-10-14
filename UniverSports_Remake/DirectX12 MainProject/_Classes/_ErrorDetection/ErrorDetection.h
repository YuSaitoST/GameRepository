/**
 * @file ErrorDetection.h
 * @brief 例外をテキストファイルに出力する
 * @author 齋藤優宇
 * @date 2021/07/15
 */

#pragma once

 //------------------------------------------------------------------------------
 //	インクルードファイル
 //------------------------------------------------------------------------------
#include <fstream>
#include <chrono>

namespace YUSTK {
	inline void CreateTxt(std::wstring projectTitle, std::exception exception, int scene, std::string remarks = "none") {
		std::chrono::system_clock::time_point _now = std::chrono::system_clock::now();
		std::time_t _end_time = std::chrono::system_clock::to_time_t(_now);

		std::ofstream _outputfile(projectTitle + L"error_code.txt");
		_outputfile
			<< "\n"
			<< "--------------------------------------------------------------------" << "\n"
			<< "- Date and Time of Occurrence : " << std::ctime(&_end_time) << "\n"
			<< "- Exception	: " << exception.what() << "\n"
			<< "- Scene		: " << scene
			<< "- Remarks	: " << remarks << "\n"
			<< "--------------------------------------------------------------------" << "\n";
		_outputfile.close();
	}
}