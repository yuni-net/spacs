#include "image_loader.h"
#include <cstdlib>
#include <opencv/cv.h>
#include <opencv/highgui.h>

namespace spa
{
	bool image_loader::load(const char * path, GLuint & id, uint & width, uint & height)
	{
#if 0
		TImageInfo * pImageInfo = nullptr;
		pImageInfo = GetImageInfo(path);

		if (pImageInfo == nullptr)
		{
			return false;
		}
#endif

		// loading
		cv::Mat image = cv::imread(path);
		cv::cvtColor(image, image, CV_BGR2RGB);
		cv::flip(image, image, 0);


		width = static_cast<uint>(image.size().width);
		height = static_cast<uint>(image.size().height);
		if (height < 0)
		{
			height = 0 - height;	// 符号反転
		}

		// テクスチャの作成
		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
			width,
			height,
			0, GL_RGB, GL_UNSIGNED_BYTE,
			reinterpret_cast<void *>(image.data));

#if 0
		free(pImageInfo->pbyPixels);
		free(pImageInfo);
#endif

		return true;
	}





	bool image_loader::load(const char * path, GLuint & id, uint & width, uint & height, unsigned char r, unsigned char g, unsigned b)
	{
#if 0
		TImageInfo * pImageInfo = nullptr;
		pImageInfo = GetImageInfo(path);

		if (pImageInfo == nullptr)
		{
			return false;
		}
#endif

		// loading
		cv::Mat image = cv::imread(path);
		cv::cvtColor(image, image, CV_BGR2RGB);
		cv::flip(image, image, 0);

		width = static_cast<uint>(image.size().width);
		height = static_cast<uint>(image.size().height);
		if (height < 0)
		{
			height = 0 - height;	// 符号反転
		}

		int pixel_num = width*height;
		unsigned char * pixels = (unsigned char *)malloc(pixel_num * 4 );
		for (int index = 0; index*3 + 2 < pixel_num * 3; ++index)
		{
			int oldindex = index * 3;
			int newindex = index * 4;

			pixels[newindex] = image.data[oldindex];
			pixels[newindex+1] = image.data[oldindex+1];
			pixels[newindex+2] = image.data[oldindex+2];

			if (image.data[oldindex] == r &&
				image.data[oldindex + 1] == g &&
				image.data[oldindex + 2] == b)
			{
				pixels[newindex + 3] = 100;
			}
			else
			{
				pixels[newindex + 3] = 255;
			}

		}

		// テクスチャの作成
		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
			width,
			height,
			0, GL_RGBA, GL_UNSIGNED_BYTE,
			reinterpret_cast<void *>(pixels));


		free(pixels);
#if 0
		free(pImageInfo->pbyPixels);
		free(pImageInfo);
#endif

		return true;
	}
}