#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>
#include <stdio.h>

void RenderGUI()
{
     ImGui::Begin("Test Window");
     ImGui::Text("omg ");
     ImGui::End();
}

int main()
{
     // Initialize GLFW
     if (!glfwInit())
     {
          fprintf(stderr, "Failed to initialize GLFW\n");
          return -1;
     }

     // Setup OpenGL context for macOS (3.3 Core)
     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
     glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Required on Mac
#endif

     // Create window
     GLFWwindow *window = glfwCreateWindow(800, 600, "Dear ImGui Window", NULL, NULL);
     if (window == NULL)
     {
          fprintf(stderr, "Failed to create GLFW window\n");
          glfwTerminate();
          return -1;
     }
     glfwMakeContextCurrent(window);
     glfwSwapInterval(1); // Enable vsync

     // Setup Dear ImGui context
     IMGUI_CHECKVERSION();
     ImGui::CreateContext();
     ImGuiIO &io = ImGui::GetIO();
     (void)io;

     // Setup Dear ImGui style
     ImGui::StyleColorsDark();

     // Setup platform/renderer backends
     ImGui_ImplGlfw_InitForOpenGL(window, true);
     ImGui_ImplOpenGL3_Init("#version 330");

     // Main loop
     while (!glfwWindowShouldClose(window))
     {
          glfwPollEvents();

          // Start ImGui frame
          ImGui_ImplOpenGL3_NewFrame();
          ImGui_ImplGlfw_NewFrame();
          ImGui::NewFrame();

          // Your UI here
          RenderGUI();

          // Rendering
          ImGui::Render();
          int display_w, display_h;
          glfwGetFramebufferSize(window, &display_w, &display_h);
          glViewport(0, 0, display_w, display_h);
          glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
          glClear(GL_COLOR_BUFFER_BIT);
          ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

          glfwSwapBuffers(window);
     }

     // Cleanup
     ImGui_ImplOpenGL3_Shutdown();
     ImGui_ImplGlfw_Shutdown();
     ImGui::DestroyContext();
     glfwDestroyWindow(window);
     glfwTerminate();

     return 0;
}
