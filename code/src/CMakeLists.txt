set(EXECUTABLE_NAME helloTriangle)

find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(Vulkan REQUIRED)

add_executable(${EXECUTABLE_NAME}
	main.cpp
)

target_compile_features(${EXECUTABLE_NAME} PRIVATE cxx_std_17)

#add_subdirectory(physObj)

target_link_libraries(${EXECUTABLE_NAME}
	PRIVATE
	#	physObj
	glfw
	glm::glm
	Vulkan::Vulkan
)

target_include_directories(${EXECUTABLE_NAME}
	PRIVATE
	"${PROJECT_BINARY_DIR}"
	#	"${PROJECT_SOURCE_DIR}/physObj"
)
