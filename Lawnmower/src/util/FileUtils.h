#pragma once
#include <sstream>
#include <iostream>

	char* readFile(const char* filePath)
	{
		FILE* file;
		std::stringstream ss;
		file = fopen(filePath, "r");
		if (file == NULL) { std::cout << filePath << " is not a valid file path!\n"; return nullptr; }

		fseek(file, 0, SEEK_END);
		long length = ftell(file);

		char* result = new char[length];
		memset(result, 0, length);

		fseek(file, 0, SEEK_SET);
		fread(result, 1, length, file);
		fclose(file);

		return result;
	}