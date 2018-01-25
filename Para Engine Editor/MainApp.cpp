#include <GL\glew.h>
#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"
#include <GLFW\glfw3.h>
#include <iostream>
#include "HierarchyPanel.h"
#include "PropertyPanel.h"
#include <Game.h>
#include <GameObject.h>
#include <Sprite.h>
#include <TextureLoader.h>
#include <Texture.h>
#include "ResourceManager.h"
#include "FileExplorer.h"
#include "EditorSceneViewManager.h"

void StyleColorsParaEngineDefault(ImGuiStyle* dst = (ImGuiStyle*)0);

int main(int, char**)
{
	if (!glfwInit())
		return 1;
	GLFWwindow* window = glfwCreateWindow(1040, 640, "Para Engine v0.04-alpha", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	glfwInit();
	GLenum err = glewInit();
	if (GLEW_OK != err)
		std::cout << "Error: %s\n" << glewGetErrorString(err);
	else
		std::cout << " Glew initialsed" << std::endl;
	ImGui_ImplGlfwGL3_Init(window, true);
	StyleColorsParaEngineDefault();
	// Load Fonts
	// - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them. 
	// - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple. 
	// - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
	// - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
	// - Read 'extra_fonts/README.txt' for more instructions and details.
	// - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
	ImGuiIO& io = ImGui::GetIO();
	ImFont* font = io.Fonts->AddFontFromFileTTF("Test Resources\\arial.ttf", 16.0f);
	IM_ASSERT(font != NULL);

	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	TextureManager::loadTextureFromFile("Test Resources\\lili.jpg", "bg", false);
	ResourceManager::instance.addResource(ResourceType::TEXTURE, "Test Resources\\lili.jpg");

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
		// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
		// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
		// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
		EditorSceneViewManager::instance.updateSceneView();

		glfwPollEvents();
		ImGui_ImplGlfwGL3_NewFrame();
		// 3. Show the ImGui demo window. Most of the sample code is in ImGui::ShowDemoWindow().
		if (show_demo_window)
		{
			ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver); // Normally user code doesn't need/want to call this because positions are saved in .ini file anyway. Here we just want to make the demo initial state a bit more friendly!
			ImGui::ShowDemoWindow(&show_demo_window);
		}
		//______________________
		bool showPopUp = false;
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Open Project", "CTRL+O")) {
					std::cout << "open project called\n"; FileExplorer::instance.shouldDisplay = true;
				}
				if (ImGui::MenuItem("Open Scene")) {}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Edit"))
			{
				if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
				if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
				ImGui::Separator();
				ImGui::MenuItem("Search");
				ImGui::MenuItem("Reload");
				if (ImGui::BeginMenu("Preferences"))
				{
					if (ImGui::BeginMenu("Theme"))
					{
						if (ImGui::MenuItem("Default")) { StyleColorsParaEngineDefault(); }
						if (ImGui::MenuItem("Dark")) { ImGui::StyleColorsDark(); }
						if (ImGui::MenuItem("Light")) { ImGui::StyleColorsLight(); }
						ImGui::EndMenu();
					}
					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("Game Object"))
				{
					if (ImGui::MenuItem("Create New"))
						showPopUp = true;
					if (ImGui::BeginMenu("Add Component", HierarchyPanel::instance.getActiveGameObj() != nullptr))
					{
						if (ImGui::MenuItem("Sprite"))
						{
							Sprite* sp = new Sprite();
							sp->init(1.0f, 1.0f);
							sp->setTextureID(TextureManager::getTextureIdFromReference("bg"));
							HierarchyPanel::instance.getActiveGameObj()->addComponent(sp);
						}
						ImGui::MenuItem("Camera");
						ImGui::MenuItem("Box Collider");
						ImGui::MenuItem("Text");
						ImGui::EndMenu();
					}
					if (ImGui::BeginMenu("Add Standard Shader"))
					{
						ImGui::MenuItem("Basic Sprite");
						ImGui::MenuItem("Basic Unlit");
						ImGui::MenuItem("Basic Colour");
						ImGui::EndMenu();
					}
					ImGui::EndMenu();
				}
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
			if (showPopUp)
				ImGui::OpenPopup("Add An Object");
			ImGuiWindowFlags window_flags = 0;
			window_flags |= ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoResize;
			window_flags |= ImGuiWindowFlags_NoCollapse;
			ImGui::SetNextWindowSize(ImVec2(320, 90));
			if (ImGui::BeginPopupModal("Add An Object", NULL, window_flags))
			{
				static char bufpass[40] = "";
				ImGui::InputText("New Object", bufpass, 40, NULL);
				if (ImGui::Button("Add Object"))
				{
					std::string objName(bufpass);
					while (true)
					{
						bool success = true;
						try { GameObject::createGameObject(objName); }
						catch (...)
						{
							if (isdigit(objName[objName.length() - 1]))
							{
								int count = 0;
								while (isdigit(objName[objName.length() - count - 1]))
									count++;
								int incrementValue = atoi(objName.substr(objName.length() - count, count).c_str());
								objName = objName.substr(0, objName.length() - count) + std::to_string(++incrementValue);
							}
							else
								objName += "0";
							success = false;
						}
						if (success)
							break;
					}
					bufpass[0] = '\0';
					ImGui::CloseCurrentPopup();
				}
				ImGui::SameLine();
				if (ImGui::Button("Close"))
					ImGui::CloseCurrentPopup();
				ImGui::EndPopup();
			}
		}
		HierarchyPanel::instance.display(display_w, display_h);
		PropertyPanel::instance.display(display_w, display_h);
		FileExplorer::instance.display();
		HierarchyPanel::instance.handleInputData();
		PropertyPanel::instance.handleInputData();
		// Rendering

		glViewport(0, 0, display_w, display_h);
		glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);

		ImGui::Render();
		glfwSwapBuffers(window);
	}
	ImGui_ImplGlfwGL3_Shutdown();
	glfwTerminate();

	return 0;
}
void StyleColorsParaEngineDefault(ImGuiStyle* dst)
{
	ImGuiStyle* style = dst ? dst : &ImGui::GetStyle();
	ImVec4* colors = style->Colors;

	colors[ImGuiCol_Text] = ImVec4(0.88f, 0.88f, 0.88f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
	//colors[ImGuiCol_TextHovered]          = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	//colors[ImGuiCol_TextActive]           = ImVec4(1.00f, 1.00f, 0.00f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.24f, 0.08f, 0.20f, 1.00f);
	colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.20f, 0.0f, 0.10f, 1.00f);
	colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.40f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.24f, 0.12f, 0.24f, 1.00f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.26f, 0.99f, 0.98f, 0.40f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.66f, 0.59f, 0.98f, 0.67f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.36f, 0.26f, 0.36f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.46f, 0.145f, 0.36f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 1.00f, 1.00f, 0.51f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.26f, 0.0f, 0.26f, 1.00f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.48f, 0.35f, 0.48f, 0.53f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.69f, 0.69f, 0.69f, 0.80f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.59f, 0.49f, 0.49f, 0.80f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.59f, 0.59f, 0.49f, 1.00f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.26f, 0.59f, 0.98f, 0.78f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.46f, 0.54f, 0.80f, 0.60f);
	colors[ImGuiCol_Button] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(0.26f, 0.59f, 0.98f, 0.31f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_Separator] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.14f, 0.44f, 0.80f, 0.78f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.14f, 0.44f, 0.80f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.30f, 0.30f, 0.70f, 0.46f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
	colors[ImGuiCol_CloseButton] = ImVec4(0.79f, 0.29f, 0.59f, 0.80f);
	colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.98f, 0.39f, 0.36f, 1.00f);
	colors[ImGuiCol_CloseButtonActive] = ImVec4(0.98f, 0.39f, 0.36f, 1.00f);
	colors[ImGuiCol_PlotLines] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.45f, 0.00f, 1.00f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
	colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.0f, 0.0f, 0.20f, 0.45f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
}