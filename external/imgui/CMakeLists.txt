#
# GlobeEngine projects: "globeEngineCore"
#
#project(imgui)
message(STATUS "\n---- Configuring imgui ----")
# -- Inputs --
file(GLOB_RECURSE src_files  *.c *.cpp *.cxx *.h *.hpp *.hxx)

# -- Outputs --
#set(LIBRARY_OUTPUT_PATH "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")  # It shouldn't be necessary
message("project name ${PROJECT_NAME}")
add_library(imgui STATIC ${src_files})
#set_target_properties(imgui PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/external/imgui")
#set(imgui_LIBRARY debug ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/external/imgui/Debug/libimgui.a optimized ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/external/imgui/Release/libimgui.a PARENT_SCOPE)
set(imgui_LIBRARY imgui PARENT_SCOPE)
message("output directory ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
message("PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR}")
set(imgui_INCLUDE_DIRS ${EXTERNAL_DIR}/imgui PARENT_SCOPE)
#include_directories(${PROJECT_SOURCE_DIR}/)


#if(MSVC)
#	install(TARGETS ${PROJECT_NAME} ARCHIVE DESTINATION ${LIB_DIRNAME} COMPONENT ${PROJECT_NAME})
#endif()