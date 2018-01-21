#pragma once
class PropertyPanel
{
public:
	static PropertyPanel instance;
	PropertyPanel();
	PropertyPanel(const PropertyPanel&) = delete;
	void display(int screenWidth, int screenHeight);
	~PropertyPanel();
};

