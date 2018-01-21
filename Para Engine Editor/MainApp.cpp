#include <GL\glew.h>
#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"
#include <GLFW\glfw3.h>
#include <iostream>
#include "HierarchyPanel.h"
#include "PropertyPanel.h"
#include <Game.h>
#include <TextureLoader.h>
int main(int, char**)
{
	if (!glfwInit())
		return 1;
	GLFWwindow* window = glfwCreateWindow(1040, 640, "Para Engine v0.01-alpha", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	glfwInit();
	GLenum err = glewInit();
	if (GLEW_OK != err)
		std::cout << "Error: %s\n" << glewGetErrorString(err);
	else
		std::cout << " Glew initialsed" << std::endl;

	// Setup ImGui binding
	ImGui_ImplGlfwGL3_Init(window, true);

	// Setup style
	//ImGui::StyleColorsClassic();
	ImGui::StyleColorsDark();
	TextureManager::loadTextureFromFile("sdsd", "sdsd", false);
	// Load Fonts
	// - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them. 
	// - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple. 
	// - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
	// - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
	// - Read 'extra_fonts/README.txt' for more instructions and details.
	// - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
	ImGuiIO& io = ImGui::GetIO();
	ImFont* font = io.Fonts->AddFontFromFileTTF("F:\\Visual Studio 2017\\Projects\\Para Engine Editor\\Debug\\arial.ttf", 14.0f);
	IM_ASSERT(font != NULL);

	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);


	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
		// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
		// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
		// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
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
				if (ImGui::MenuItem("Open Project", "CTRL+O")) { std::cout << "open project called\n"; }
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
				if (ImGui::BeginMenu("Game Object"))
				{
					if (ImGui::MenuItem("Create New"))
						showPopUp = true;
					ImGui::MenuItem("Add Component");
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
			ImGui::SetNextWindowSize(ImVec2(300, 80));
			if (ImGui::BeginPopupModal("Add An Object", NULL, window_flags))
			{
				static char bufpass[40] = "";
				ImGui::InputText("New Object", bufpass, 40, NULL);
				if (ImGui::Button("Add Object"))
				{
					HierarchyPanel::instance.addGameObject(bufpass);
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
		
		HierarchyPanel::instance.handleInputData();
		// Rendering

		glViewport(0, 0, display_w, display_h);
		glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui::Render();
		glfwSwapBuffers(window);
	}

	// Cleanup
	ImGui_ImplGlfwGL3_Shutdown();
	glfwTerminate();

	return 0;
}
