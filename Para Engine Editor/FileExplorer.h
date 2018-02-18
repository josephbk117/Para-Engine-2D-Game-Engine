#pragma once
#include <vector>

enum class FileType
{
	IMAGE, TEXT, CHAISCRIPT, AUDIO, NONE
};

class FileExplorer
{
public:
	static FileExplorer instance;
	bool isDirty = true;
	std::string path = "C:\\";
	FileExplorer();
	void display();
	void displayDialog(std::string* pathOutput, FileType filter = FileType::NONE);
	~FileExplorer();
private:
	bool shouldDisplay = false;
	std::vector<std::string> paths;
	std::string* outputPath = nullptr;
	FileType fileFilter = FileType::NONE;
};