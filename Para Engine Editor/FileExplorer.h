#pragma once
#include <vector>
class FileExplorer
{
public:
	static FileExplorer instance;
	bool isDirty = true;
	std::string path = "C:\\";
	FileExplorer();
	void display();
	void displayDialog(std::string* pathOutput);
	~FileExplorer();
private:
	bool shouldDisplay = false;
	std::vector<std::string> paths;
	std::string* outputPath = nullptr;
};