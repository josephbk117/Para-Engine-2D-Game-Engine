#include <ParaEngine/TextureLoader.h>
#include <ParaEngine/Transform.h>
#include <ParaEngine/Sprite.h>
#include <iostream>

#include "PropertyPanel.h"
#include "imgui.h"
#include "ResourceManager.h"
PropertyPanel PropertyPanel::instance;
PropertyPanel::PropertyPanel()
{
}

void PropertyPanel::display(int screenWidth, int screenHeight)
{
	localScreenWidth = screenWidth;
	localScreenHeight = screenHeight;
	if (hierarchyPanel == nullptr)
	{
		hierarchyPanel = &HierarchyPanel::instance;
		return;
	}
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 1.1f);
	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoResize;
	window_flags |= ImGuiWindowFlags_NoCollapse;
	bool *p_open = NULL;
	ImGui::SetNextWindowPos(ImVec2(0, screenHeight - yLimiter), ImGuiSetCond_Always);
	ImGui::SetNextWindowSize(ImVec2(screenWidth - hierarchyPanel->xLimiter, yLimiter), ImGuiSetCond_Always);
	ImGui::Begin("Property Panel", p_open, window_flags);

	GameObject* obj = hierarchyPanel->getActiveGameObj();
	if (obj != nullptr)
	{
		std::string text = "NAME : " + obj->getName();
		float regionWidth = ImGui::GetContentRegionAvailWidth() * 0.5f;
		ImGui::Indent(regionWidth);
		ImGui::Text(text.c_str());
		ImGui::Unindent(regionWidth);
		ImGui::Separator();
		ImGui::Columns(obj->getAttachedComponents().size() + 1, "Components");
		ImGui::SetColumnWidth(0, (ImGui::GetColumnWidth(0) < 130) ? 130 : ImGui::GetColumnWidth(0));
		float xPos = 0.0f, yPos = 0.0f;
		xPos = obj->getComponent<Transform>()->getPosition().x;
		yPos = obj->getComponent<Transform>()->getPosition().y;
		float xScale = 0.0f, yScale = 0.0f;
		xScale = obj->getComponent<Transform>()->getScale().x;
		yScale = obj->getComponent<Transform>()->getScale().y;
		float rotation = glm::degrees(obj->getComponent<Transform>()->getRotation());

		regionWidth = ImGui::GetContentRegionAvailWidth() * 0.375f;
		ImGui::Indent(regionWidth);
		ImGui::Text("TRANSFORM");
		ImGui::Unindent(regionWidth);
		ImGui::Text("Position :");
		ImGui::PushItemWidth(ImGui::GetContentRegionAvailWidth() * 0.45f);
		if (ImGui::DragFloat("##Position X", &xPos, 0.001f, -9999999.0f, 9999999.0f, "X: %.3f"))
			obj->getComponent<Transform>()->setX(xPos);
		ImGui::SameLine();
		if (ImGui::DragFloat("##Position Y", &yPos, 0.001f, -9999999.0f, 9999999.0f, "Y: %.3f"))
			obj->getComponent<Transform>()->setY(yPos);
		ImGui::Text("Scale :");
		if (ImGui::DragFloat("##Scale X", &xScale, 0.001f, -9999999.0f, 9999999.0f, "X: %.3f"))
			obj->getComponent<Transform>()->setScale(glm::vec2(xScale, obj->getComponent<Transform>()->getScale().y));
		ImGui::SameLine();
		if (ImGui::DragFloat("##Scale Y", &yScale, 0.001f, -9999999.0f, 9999999.0f, "Y: %.3f"))
			obj->getComponent<Transform>()->setScale(glm::vec2(obj->getComponent<Transform>()->getScale().x, yScale));
		ImGui::Text("Rotation :");
		if (ImGui::DragFloat("##Rotation", &rotation, 0.1f, -9999999.0f, 9999999.0f, "Deg: %.3f"))
			obj->getComponent<Transform>()->setRotation(glm::radians(rotation));

		ImGui::PopItemWidth();

		if (obj->hasComponent<Sprite>())
		{
			ImGui::SetColumnWidth(1, (ImGui::GetColumnWidth(1) < 130) ? 130 : ImGui::GetColumnWidth(1));
			ImGui::NextColumn();

			std::string filePath;
			unsigned int index = -1;

			ImGuiIO& io = ImGui::GetIO();
			regionWidth = ImGui::GetContentRegionAvailWidth() * 0.375f;
			ImGui::Indent(regionWidth);
			ImGui::Text("SPRITE");
			ImGui::Unindent(regionWidth);
			ImTextureID my_tex_id = (void *)obj->getComponent<Sprite>()->getTextureID();
			float texWidth, texHeight;
			float ratio;
			const float MAX_SIZE = 100.0f;

			int currentImageIndex = -1;
			std::string comboImageBox = "";
			for (unsigned int i = 0; i < ResourceManager::instance.getImageVector()->size(); i++)
				comboImageBox += ResourceManager::instance.instance.getImageVector()->at(i).first + '\0';
			comboImageBox += '\0';
			ImGui::PushItemWidth(ImGui::GetContentRegionAvailWidth() * 0.45f);
			ImGui::Combo("Images", &currentImageIndex, comboImageBox.c_str());
			ImGui::PopItemWidth();
			if (currentImageIndex != -1)
				obj->getComponent<Sprite>()->setTextureID(*ResourceManager::instance.getImageVector()->at(currentImageIndex).second.data2);

			float width, height;
			for (unsigned int i = 0; i < ResourceManager::instance.getImageVector()->size(); i++)
			{
				if (*ResourceManager::instance.getImageVector()->at(i).second.data2 == obj->getComponent<Sprite>()->getTextureID())
				{
					width = ResourceManager::instance.getImageVector()->at(i).second.data1->x;
					height = ResourceManager::instance.getImageVector()->at(i).second.data1->y;
					index = i;
					break;
				}
			}

			if (width > height)
				ratio = MAX_SIZE / width;
			else
				ratio = MAX_SIZE / height;
			texWidth = ratio * width;
			texHeight = ratio * height;

			ImVec2 pos = ImGui::GetCursorScreenPos();
			ImGui::Image(my_tex_id, ImVec2(texWidth, texHeight), ImVec2(1, 1), ImVec2(0, 0), ImColor(255, 255, 255, 255), ImColor(255, 255, 255, 128));
			ImGui::SameLine();
			if (ImGui::IsItemHovered())
			{
				ImGui::BeginTooltip();
				float focusSize = 32.0f;
				float focus_x = io.MousePos.x - pos.x - focusSize * 0.5f; if (focus_x < 0.0f) focus_x = 0.0f; else if (focus_x > texWidth - focusSize) focus_x = texWidth - focusSize;
				float focus_y = io.MousePos.y - pos.y - focusSize * 0.5f; if (focus_y < 0.0f) focus_y = 0.0f; else if (focus_y > texHeight - focusSize) focus_y = texHeight - focusSize;
				ImGui::Text("Min: (%.2f, %.2f)", focus_x / ratio, focus_y / ratio);
				ImGui::Text("Max: (%.2f, %.2f)", (focus_x + focusSize) / ratio, (focus_y + focusSize) / ratio);
				ImVec2 uv0 = ImVec2(-(focus_x) / texWidth, ((focus_y) / texHeight));
				ImVec2 uv1 = ImVec2(-(focus_x + focusSize) / texWidth, ((focus_y + focusSize) / texHeight));
				uv0.y = 1.0f - uv0.y;
				uv1.y = 1.0f - uv1.y;
				ImGui::Image(my_tex_id, ImVec2(128, 128), uv0, uv1, ImColor(255, 255, 255, 255), ImColor(255, 255, 255, 128));
				ImGui::EndTooltip();
			}
			ImGui::Text("%dx%d", (int)width, (int)height);
			ImGui::SameLine();
			filePath = "File Path : ";
			filePath += std::get<0>(ResourceManager::instance.getImageVector()->at(index));
			ImGui::TextWrapped(filePath.c_str());
			float inKB = std::get<1>(ResourceManager::instance.getImageVector()->at(index)).fileSize / 1024.0f;
			float inMB = inKB / 1024.0f;
			//std::string fileSize = "File Size : " + std::to_string(inKB) + " KB (" + std::to_string(inMB) + "MB )";
			ImGui::Text("File size : %.2f KB ( %0.3f MB)", inKB, inMB);
		}
	}
	ImGui::End();
	ImGui::PopStyleVar();
	ImGui::PopStyleVar();
}

void PropertyPanel::addTexture(const Texture & texture)
{
	textures.push_back(texture);
}

void PropertyPanel::handleInputData()
{
	ImGuiIO& io = ImGui::GetIO();
	if (io.MouseClicked[0])
	{
		if (!isDragging)
		{
			if (io.MouseClickedPos[0].y > (localScreenHeight - yLimiter) - 8 && io.MouseClickedPos[0].y < (localScreenHeight - yLimiter) + 8)
				isDragging = true;
		}
		else
		{
			isDragging = false;
			ImGui::SetMouseCursor(ImGuiMouseCursor_Arrow);
		}
	}
	if (isDragging)
	{
		io.MouseDrawCursor = true;
		ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeNS);
		yLimiter = localScreenHeight - io.MousePos.y;
		yLimiter = glm::clamp(yLimiter, localScreenHeight / 6, localScreenHeight / 3);
	}
}

PropertyPanel::~PropertyPanel()
{
}
