#include "ImageSaver.h"

namespace cgCourse {
	
	void ImageSaver::saveImageAsPPM(std::string fileName, int width, int height, float* data) {
		std::ofstream myfile;

		myfile.open(fileName + ".ppm");

		myfile << "P3\n" << width << " " << height << "\n255\n";

		for (int j = height - 1; j >= 0; j--) {
			for (int i = 0; i < width; i++) {
				float r = data[3 * (j * width + i)];
				float g = data[3 * (j * width + i) + 1];
				float b = data[3 * (j * width + i) + 2];

				int ir = int(255.99 * r);
				int ig = int(255.99 * g);
				int ib = int(255.99 * b);
				myfile << ir << " " << ig << " " << ib << "\n";
			}
		}

		myfile.close();
	}
}