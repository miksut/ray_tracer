#include "ImageSaver.h"

namespace cgCourse {
	
	void ImageSaver::saveImageAsPPM(std::string fileName, int width, int height, float* data) {
		std::ofstream myfile;

		myfile.open(fileName + ".ppm");

		myfile << "P3\n" << width << " " << height << "\n255\n";

        for (int j = 0; j < height; j++) {
			for (int i = 0; i < width; i++) {
				float r = data[3 * (j * width + i)];
				float g = data[3 * (j * width + i) + 1];
				float b = data[3 * (j * width + i) + 2];
                
                // use 255.99 because of some weird overflow errors
				int ir = int(255.99 * r);
				int ig = int(255.99 * g);
				int ib = int(255.99 * b);
				myfile << ir << " " << ig << " " << ib << "\n";
			}
		}

		myfile.close();
	}

	void ImageSaver::saveImageAsPNG(std::string fileName, int width, int height, float* data) {
		FreeImage_Initialise();
        
		FIBITMAP* bitmap = FreeImage_Allocate(width, height, 24);
		RGBQUAD col;

		if (!bitmap) {
			exit(1);}

		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
                // use 255.99 because we used it at the other one as well
				col.rgbRed = data[3 * (y * width + x)] * 255.99;
				col.rgbGreen = data[3 * (y * width + x) + 1] * 255.99;
				col.rgbBlue = data[3 * (y * width + x) + 2] * 255.99;
				FreeImage_SetPixelColor(bitmap, x, height - y, &col);
			}
		}

		FreeImage_Save(FIF_PNG, bitmap, (fileName + ".png").c_str(), 0);
		FreeImage_DeInitialise();
	}
}
