#pragma once
#include <string>
#include <imgui.h>
class UserPreferences
{
public:
	UserPreferences();
	~UserPreferences();
private:
	ImVec4 viewportBgColour;
	ImFont* font;
	std::string defaultDrive;
};

