#include "PropertyPanel.h"
#include "imgui.h"
#include "ResourceManager.h"
#include <TextureLoader.h>
#include <Transform.h>
#include <Sprite.h>
#include <iostream>
PropertyPanel PropertyPanel::instance;
PropertyPanel::PropertyPanel()
{
}

void PropertyPanel::display(int screenWidth, int screenHeight)
{
	if (hierarchyPanel == nullptr)
	{
		hierarchyPanel = &HierarchyPanel::instance;
		return;
	}
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 1.1f);
	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoScrollbar;
	window_flags |= ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoResize;
	window_flags |= ImGuiWindowFlags_NoCollapse;
	bool *p_open = NULL;
	ImGui::SetNextWindowPos(ImVec2(0, screenHeight - 180), ImGuiSetCond_Always);
	ImGui::SetNextWindowSize(ImVec2(screenWidth - hierarchyPanel->xLimiter, 180), ImGuiSetCond_Always);
	ImGui::Begin("Property Panel", p_open, window_flags);

	GameObject* obj = hierarchyPanel->getActiveGameObj();
	if (obj != nullptr)
	{
		std::string text = "Name : " + obj->getName();
		ImGui::Text(text.c_str());
		ImGui::Text("Transform");
		text = "Position : " + std::to_string(obj->getComponent<Transform>()->getPosition().x) + ", ";
		text += std::to_string(obj->getComponent<Transform>()->getPosition().y);
		ImGui::Text(text.c_str());
		ImGui::Text("Has Sprite");
		std::string filePath;
		if (obj->hasComponent<Sprite>())
		{
			filePath = "File Path : ";
			for (int i = 0; i < ResourceManager::instance.getTextureVector()->size(); i++)
			{
				filePath += std::get<0>(ResourceManager::instance.getTextureVector()->at(i)) + " size : ";
				filePath += std::to_string(std::get<1>(ResourceManager::instance.getTextureVector()->at(i)).fileSize/1000.0f) + " KB";
			}
		}
		ImGui::Text(filePath.c_str());
	}

	/*ImGuiIO& io = ImGui::GetIO();

	ImTextureID my_tex_id = (void *)textures[0].textureId; //io.Fonts->TexID;
	float my_tex_w, my_tex_h;
	float ratio;
	const float MAX_SIZE = 145.0f;
	if (textures[0].width > textures[0].height)
		ratio = MAX_SIZE / textures[0].width;
	else
		float ratio = MAX_SIZE / textures[0].height;
	my_tex_w = ratio * textures[0].width;
	my_tex_h = ratio * textures[0].height;

	ImGui::Text("%dx%d", textures[0].width, textures[0].height);

	ImVec2 pos = ImGui::GetCursorScreenPos();
	ImGui::Image(my_tex_id, ImVec2(my_tex_w, my_tex_h), ImVec2(1, 1), ImVec2(0, 0), ImColor(255, 255, 255, 255), ImColor(255, 255, 255, 128));
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		float focus_sz = 32.0f;
		float focus_x = io.MousePos.x - pos.x - focus_sz * 0.5f; if (focus_x < 0.0f) focus_x = 0.0f; else if (focus_x > my_tex_w - focus_sz) focus_x = my_tex_w - focus_sz;
		float focus_y = io.MousePos.y - pos.y - focus_sz * 0.5f; if (focus_y < 0.0f) focus_y = 0.0f; else if (focus_y > my_tex_h - focus_sz) focus_y = my_tex_h - focus_sz;
		ImGui::Text("Min: (%.2f, %.2f)", focus_x/ratio, focus_y/ratio);
		ImGui::Text("Max: (%.2f, %.2f)", (focus_x + focus_sz)/ratio, (focus_y + focus_sz)/ratio);
		ImVec2 uv0 = ImVec2((focus_x) / my_tex_w, (focus_y) / my_tex_h);
		ImVec2 uv1 = ImVec2((focus_x + focus_sz) / my_tex_w, (focus_y + focus_sz) / my_tex_h);
		ImGui::Image(my_tex_id, ImVec2(128, 128), uv1, uv0, ImColor(255, 255, 255, 255), ImColor(255, 255, 255, 128));
		ImGui::EndTooltip();
	}
	ImGui::SameLine(180.0f);*/


	ImGui::End();
	ImGui::PopStyleVar();
	ImGui::PopStyleVar();
}

void PropertyPanel::addTexture(const Texture & texture)
{
	textures.push_back(texture);
}

PropertyPanel::~PropertyPanel()
{
}
