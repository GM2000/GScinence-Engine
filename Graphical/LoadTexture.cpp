
#include <atlimage.h>
#include "LoadTexture.h"

unsigned int gsgLoadTexture(const wchar_t* FileName)
{
	BITMAP BitMap;
	GLuint TextureID = 0;
	CImage Image;

	//文件是否加载失败
	if (!SUCCEEDED(Image.Load(FileName)))
	{
		std::cerr << "[ERROR]:Unable to load image called '" << FileName << "'" << std::endl;
		return 0;
	}

	for (int i = 0; i < Image.GetWidth(); i++)
	{
		for (int j = 0; j < Image.GetHeight(); j++)
		{
			unsigned char* pucColor = reinterpret_cast<unsigned char *>(Image.GetPixelAddress(i, j));
			pucColor[0] = (pucColor[0] * pucColor[3] + 127) / 255;
			pucColor[1] = (pucColor[1] * pucColor[3] + 127) / 255;
			pucColor[2] = (pucColor[2] * pucColor[3] + 127) / 255;
		}
	}

	//获取图象数据
	if (!GetObject(HBITMAP(Image), sizeof(BitMap), &BitMap))
	{
		return 0;
	}

	glGenTextures(1, &TextureID);

	if (TextureID)
	{
		glBindTexture(GL_TEXTURE_2D, TextureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glPixelStoref(GL_PACK_ALIGNMENT, 1);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, BitMap.bmWidth, BitMap.bmHeight, 0, GL_BGR, GL_UNSIGNED_BYTE, BitMap.bmBits); //这里不是GL_RGB  
	}
	return TextureID;

}

