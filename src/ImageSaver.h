#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <freeimage/include/FreeImage.h>

namespace cgCourse {
	class ImageSaver
	{
	public:
		static void saveImageAsPPM(std::string fileName, int width, int height, float* data);
		static void saveImageAsPNG(std::string fileName, int width, int height, float* data);
	private:
		ImageSaver() {}
	};
}

