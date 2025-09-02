#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>
#include <stdio.h>

void RenderGUI()
{
     ImGui::Begin("Test Window");
     ImGui::Text("just do it ");
     ImGui::End();
}

int main()
{
     if (!glfwInit())
     {
          fprintf(stderr, "Failed to initialize GLFW\n");
          return -1;
     }

     // Setup OpenGL context for macOS (3.3 Core) so Dear ImGui can render since this library
     // communicates w GPU
     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

     glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
     // TODO: work w imgui and make a window the same size as I want the pet. Put
     //  like a button to move it around that always stays the same

#ifdef __APPLE__
     glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Required on Mac
#endif

     // Create window for  mac
     GLFWwindow *window = glfwCreateWindow(800, 200, "Dear ImGui Window", NULL, NULL);
     if (window == NULL)
     {
          fprintf(stderr, "Failed to create GLFW window\n");
          glfwTerminate();
          return -1;
     }
     glfwMakeContextCurrent(window);
     glfwSwapInterval(1); // Enable vsync (sync frame rate w monitor refresh rate)

     // Setup Dear ImGui context
     IMGUI_CHECKVERSION();
     ImGui::CreateContext();
     ImGuiIO &io = ImGui::GetIO();
     (void)io;

     // Setup platform/renderer backends
     ImGui_ImplGlfw_InitForOpenGL(window, true);
     ImGui_ImplOpenGL3_Init("#version 330");

     // Main loop
     while (!glfwWindowShouldClose(window))
     {
          glfwPollEvents();

          // Start ImGui frame - inside one
          ImGui_ImplOpenGL3_NewFrame();
          ImGui_ImplGlfw_NewFrame();
          ImGui::NewFrame();

          // Your UI here
          RenderGUI();

          // Rendering
          int display_w, display_h;
          glfwGetFramebufferSize(window, &display_w, &display_h);
          glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
          glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

          ImGui::Render();

          ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

          glfwSwapBuffers(window); // renders dear imgui window
     }

     // Cleanup
     /*ImGui_ImplOpenGL3_Shutdown();
     ImGui_ImplGlfw_Shutdown();
     ImGui::DestroyContext();
     glfwDestroyWindow(window);
     glfwTerminate();*/

     return 0;
}
