#pragma once
#include <vector>
class FileExplorer
{
public:
	static FileExplorer instance;
	bool isDirty = true;
	bool shouldDisplay = false;
	std::string path = "F:\\";
	FileExplorer();
	void display();
	~FileExplorer();
private:
	std::vector<std::string> paths;
};