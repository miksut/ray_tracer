//
//  Gui.cpp
//  CGL
//
//  Created by Alireza Amiraghdam on 03.06.19.
//

#include "Gui.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <iostream>
#include "GLEmbreeTracer.h"

namespace cgCourse
{
  bool inputAccept;
  void connectVar(std::string _varName, void * _varAddress){
    std::map<std::string,void *>::iterator it = vars.find(_varName);
    if (it != vars.end())
      it->second = _varAddress;
    else
      vars.insert(std::pair<std::string,void *>(_varName,_varAddress));
  }


  void *getVar(std::string _varName){
    auto ret = vars.find(_varName);
    if (ret != vars.end()){
      return ret->second;
    }else{
      std::cout<<"WARNING: "<<_varName<<" is not connected to the GUI"<<std::endl;
      return nullptr;
    }
  }

  void initGui(GLFWwindow* _window){
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(_window, true);
    ImGui_ImplOpenGL3_Init("#version 150");

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Read 'misc/fonts/README.txt' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("/Users/amiraghdam/Downloads/imgui-master/misc/fonts/Roboto-Medium.ttf", 16.0f);
    io.Fonts->AddFontFromFileTTF((GLApp::getPathToExecutable() + "../../res/Cousine-Regular.ttf").c_str(), 15.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("/Users/amiraghdam/Downloads/imgui-master/misc/fonts/Roboto-Medium.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != NULL);
  }

  void updateGui(){
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    bool showd,show_demo_window,show_another_window;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    // Menu Bar
    if (ImGui::BeginMainMenuBar())
    {
      if (ImGui::BeginMenu("Menu"))
      {
        // ShowExampleMenuFile();
        ImGui::EndMenu();
      }

      if (ImGui::BeginMenu("Help"))
      {
        ImGui::MenuItem("Metrics", NULL, &showd);
        ImGui::MenuItem("Style Editor", NULL, &showd);
        ImGui::MenuItem("About Dear ImGui", NULL, &showd);
        ImGui::EndMenu();
      }
      ImGui::EndMainMenuBar();
    }


    // ImGui::ShowDemoWindow(&showd);
    {
      static int counter = 0;
      ImGui::SetNextWindowPos({0,20});
      if (ImGui::GetFrameCount() ==1)
        ImGui::SetNextWindowSize({300,1000});

      ImGui::Begin("Menu",NULL,ImGuiWindowFlags_NoMove);    // Create a window called "Menu" and append into it.

      ImGui::Separator();
      ImGui::Text("Camera Type:");
      ImGui::RadioButton("Arcball", (int *)getVar("cameraType"), 0); ImGui::SameLine();
      ImGui::RadioButton("Fly over", (int *)getVar("cameraType"), 1); ImGui::SameLine();
      ImGui::Separator();
      ImGui::Text("Shading Algorithm:");
      ImGui::RadioButton("Phong", (int *)getVar("shadingAlgorithm"), 0); ImGui::SameLine();
      ImGui::RadioButton("Blinn", (int *)getVar("shadingAlgorithm"), 1); ImGui::SameLine();
      ImGui::Separator();

      ImGui::Separator();
      ImGui::Text("Application average %.3f ms/frame", 1000.0f / ImGui::GetIO().Framerate);
      ImGui::Text("FPS: %.1f FPS", ImGui::GetIO().Framerate);

	  ImGui::Separator();

	  ImGui::AlignTextToFramePadding();
	  ImGui::Text("Load Scene: "); ImGui::SameLine();
	  static char sceneName[128] = "default.cgl";
	  ImGui::InputText("##test", sceneName, 128);

	  if (GLApp::current && ImGui::Button("Load", ImVec2(-1, 30)))
	  {
		  dynamic_cast<GLEmbreeTracer*>(GLApp::current)->loadScene(sceneName);
	  }

	  ImGui::Separator();

	  if (typeid(*GLApp::current) == typeid(GLEmbreeTracer)) {
		  if (ImGui::CollapsingHeader("Raytracing", ImGuiTreeNodeFlags_DefaultOpen)) {

			  ImGui::AlignTextToFramePadding();
			  ImGui::Text("Filename: "); ImGui::SameLine();

			  ImGui::InputText("##label", (char *)getVar("tracedFileName"), 128);

			  ImGui::AlignTextToFramePadding();
			  ImGui::Text("Format: "); ImGui::SameLine();

			  ImGui::RadioButton("PPM", (int *)getVar("imageFormat"), 0); ImGui::SameLine();
			  ImGui::RadioButton("PNG", (int *)getVar("imageFormat"), 1);

			  ImGui::AlignTextToFramePadding();
			  ImGui::SliderInt("Threads", (int*)getVar("threads"), 1, 16); 

              ImGui::Checkbox("Notification Sounds", (bool*) getVar("notificationSounds"));
			  ImGui::Separator();

			  ImGui::Dummy(ImVec2(0, 30.0));

			  ImGui::Text("Run a raytracer: ");
			  ImGui::Spacing();
              
              static bool aaCaster;
              ImGui::Checkbox("Antialiasing", &aaCaster);
              
              ImGui::Spacing();
              
              if (aaCaster){
                  // both AA GUIS store their own value but set the same one
                  static int samplesAACaster = 4;
                  ImGui::Text("AA Samples: ");
                  ImGui::RadioButton("4", &samplesAACaster, 4); ImGui::SameLine();
                  ImGui::RadioButton("9", &samplesAACaster, 9); ImGui::SameLine();
                  ImGui::RadioButton("16", &samplesAACaster, 16); ImGui::SameLine();
                  ImGui::RadioButton("25", &samplesAACaster, 25);
                  ImGui::Spacing();
                  
                  int* samplesAA = (int*) getVar("samplesAA");
                  *samplesAA = samplesAACaster;
              }
              
              
              if (GLApp::current && ImGui::Button("RayCaster", ImVec2(-1, 30)))
              {
                  dynamic_cast<GLEmbreeTracer*>(GLApp::current)->rayCaster(aaCaster);
              }
			  ImGui::Spacing();
			  ImGui::Separator();
			  ImGui::Spacing();
              
              static bool aaWhitted;
              ImGui::Checkbox("Antialiasing##2", &aaWhitted);
              ImGui::Spacing();
              
              if (aaWhitted){
                  // both AA GUIS store their own value but set the same one
                  static int samplesAAWhitted = 4;
                  ImGui::Text("AA Samples: ");
                  ImGui::RadioButton("4##2", &samplesAAWhitted, 4); ImGui::SameLine();
                  ImGui::RadioButton("9##2", &samplesAAWhitted, 9); ImGui::SameLine();
                  ImGui::RadioButton("16##2", &samplesAAWhitted, 16); ImGui::SameLine();
                  ImGui::RadioButton("25##2", &samplesAAWhitted, 25);
                  ImGui::Spacing();
                  
                  int* samplesAA = (int*) getVar("samplesAA");
                  *samplesAA = samplesAAWhitted;
              }
              

			  ImGui::AlignTextToFramePadding();
			  ImGui::Text("Light Samples: ");

			  ImGui::RadioButton("Low", (int*)getVar("sampleAmount"), 0); ImGui::SameLine();
			  ImGui::RadioButton("Medium", (int*)getVar("sampleAmount"), 1); ImGui::SameLine();
			  ImGui::RadioButton("High", (int*)getVar("sampleAmount"), 2);
			  
              ImGui::Spacing();
              
              static int recursions = 3;
              ImGui::SliderInt("Recursions", &recursions, 0, 10);
              
              ImGui::Spacing();
              
              if (GLApp::current && ImGui::Button("Whitted", ImVec2(-1, 30)))
              {
                  dynamic_cast<GLEmbreeTracer*>(GLApp::current)->whittedTracer(aaWhitted, recursions);
              }
			  ImGui::Spacing();
			  ImGui::Separator();
			  ImGui::Spacing();

		  }
	  }

      inputAccept = !ImGui::GetIO().WantCaptureMouse;
      InputManager::consumed = !inputAccept;
      ImGui::End();
    }


    ImGui::Render();

  }
  void renderGui(){
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  }


}
