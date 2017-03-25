// Author  : Lewis Ward (i7212443)
// Program : Shader Binary Tool
// Date    : 25/03/2017
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#define MAX_ARGC 4
#define string std::string

int main(int argc, char** argv)
{
	std::cout << "Author: Lewis Ward (i7212443)\nConsole tool to convert text files into binary files, primary use for shaders\n";
	
	if (argc != MAX_ARGC)
	{
		std::cout << "enter 2 (space) shader filename (space) then the output filename you want the binary file to be called";
		return false;
	}

	// load the args - filenames
	string filename(argv[2]);
	string binaryFilename(argv[3]);
	std::cout << "filename " << filename.c_str() << "\nbinaryFilename " << binaryFilename << std::endl;

	// open the ASCII file
	FILE* file = fopen(filename.c_str(), "r");
	if (file == NULL)
	{
		std::cout << "Cannot open: " << filename << std::endl;
		fclose(file);
		return false;
	}

	// read in the data from the ASCII file
	std::vector<string> lines;
	while (1)
	{
		char line[256];

		if (fgets(line, 256, file) != NULL)
			puts(line);
		else
			break;

		lines.push_back(string(line));
	}
	fclose(file);
	
	// write out the read data from the ASCII file to a binary file
	FILE* binaryFile = fopen(binaryFilename.c_str(), "wb");
	if (binaryFile == NULL)
	{
		std::cout << "Cannot open: " << binaryFile << std::endl;
		return false;
	}
	for (int i = 0; i < lines.size(); i++)
	{
		fwrite(lines[i].c_str(), sizeof(char), lines[i].size(), binaryFile);
	}
	fclose(binaryFile);

	return 0;
}
