#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <vector>

class HelloTriangleApplication {
public:
  void run() {
    initWindow();
    initVulkan();
    mainLoop();
    cleanup();
  }

private:
  void initWindow() {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    mWindow =
        glfwCreateWindow(mWidth, mHeight, "Vulkan test", nullptr, nullptr);
  }

  bool checkExtensions(const uint32_t glfwExtensionCount,
                       const char **glfwExtensions) {
    uint32_t extensionCount{0u};
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
    std::vector<VkExtensionProperties> extensions(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount,
                                           extensions.data());

    uint32_t foundExtensions{0u};
    for (uint32_t i{0u}; i < glfwExtensionCount; ++i) {
      for (auto extension : extensions) {
        if (static_cast<std::string>(glfwExtensions[i]) ==
            static_cast<std::string>(extension.extensionName)) {
          ++foundExtensions;
          break;
        }
      }
    }

    return foundExtensions == glfwExtensionCount;
  }

  void createInstance() {
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Hello triangle";
    appInfo.applicationVersion = VK_MAKE_VERSION(0, 0, 1);
    appInfo.pEngineName = "No engine";
    appInfo.engineVersion = VK_MAKE_VERSION(0, 0, 1);
    appInfo.apiVersion = VK_API_VERSION_1_3;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    uint32_t glfwExtensionCount{0u};
    const char **glfwExtensions =
        glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    if (checkExtensions(glfwExtensionCount, glfwExtensions)) {
      std::string error{__PRETTY_FUNCTION__};
      error += " Vulkan extensions not found";
      throw std::runtime_error(error);
    }

    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;
    createInfo.enabledLayerCount = 0;

    if (VK_SUCCESS != vkCreateInstance(&createInfo, nullptr, &mInstance)) {
      std::string error{__PRETTY_FUNCTION__};
      error += " Failed to create instance";
      throw std::runtime_error(error);
    }
  }

  void initVulkan() { createInstance(); }

  void mainLoop() {
    while (!glfwWindowShouldClose(mWindow)) {
      glfwPollEvents();
    }
  }

  void cleanup() {
    vkDestroyInstance(mInstance, nullptr);
    glfwDestroyWindow(mWindow);
    glfwTerminate();
  }

  const uint16_t mWidth{800u};
  const uint16_t mHeight{600u};
  GLFWwindow *mWindow; // Change this to std::unique_ptr<GLFWWindow> later
  VkInstance mInstance;
};

int main() {
  HelloTriangleApplication app;

  try {
    app.run();
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    return -1;
  }

  return 0;
}