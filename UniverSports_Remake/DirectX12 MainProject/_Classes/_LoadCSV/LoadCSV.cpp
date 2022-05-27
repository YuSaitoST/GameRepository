#include "LoadCSV.h"
#include <stdio.h>
#include <cstdlib>
#include <cstdarg>
#include <vector>

/**
* @brief CSVファイルを開き、データを読み取る
* @param fileName ファイル名
* @param format データの読み取り形式
* @param ... データを保存したい変数
*/
void CSV::Schan(std::wstring fileName, const char* format, ...) {
	FILE* file;

	errno_t nonerror = _wfopen_s(&file, fileName.c_str(), L"r");
	if (nonerror != 0)
		std::abort();

	char dummyLine[512];
	fgets(dummyLine, 500, file);

	va_list args;
	va_start(args, format);

	vfscanf_s(file, format, args);

	va_end(args);

	fclose(file);
}