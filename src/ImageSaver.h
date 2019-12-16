#pragma once

#include <iostream>
#include <fstream>
#include <string>

namespace cgCourse {
	class ImageSaver
	{
	public:
		static void saveImageAsPPM(std::string fileName, int width, int height, float* data);
	private:
		ImageSaver() {}
	};
}

