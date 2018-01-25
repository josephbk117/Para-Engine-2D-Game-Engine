#include "FileExplorer.h"
#include "imgui.h"
#include <vector>
#include <filesystem>
#include <iostream>
FileExplorer FileExplorer::instance;
FileExplorer::FileExplorer()
{
}

void FileExplorer::display()
{
	if (!shouldDisplay)
		return;
	if (isDirty)
	{
		for (auto & p : std::experimental::filesystem::directory_iterator(path))
		{
			auto pathC = p.path();
			paths.push_back(pathC.generic_string());
		}
		isDirty = false;
	}
	ImGui::OpenPopup("File Explorer");
	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoResize;
	window_flags |= ImGuiWindowFlags_NoCollapse;
	ImGui::SetNextWindowSize(ImVec2(470, 380));
	if (ImGui::BeginPopupModal("File Explorer", NULL, window_flags))
	{
		if (paths.size() > 0)
		{
			for (std::string strPath : paths)
			{
				ImGui::TextWrapped(strPath.c_str());
				if (ImGui::IsItemClicked(0))
				{
					path = strPath;
					paths.clear();
					isDirty = true;
				}
			}
		}
		if (ImGui::Button("Close"))
		{
			shouldDisplay = false;
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
}

FileExplorer::~FileExplorer()
{
}
