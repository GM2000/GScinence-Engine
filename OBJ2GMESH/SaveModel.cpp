
#include <fstream>
#include <vector>
#include <iterator>

void saveModel(const char* FileName, std::vector<float>* VerticesIndex, std::vector<float>* TextureIndex, std::vector<float>* NormalsIndex)
{
	FILE *SaveGMESH = fopen(FileName, "wb");

	//获取大小
	unsigned int PointSize = VerticesIndex->size();

	//模型文件头
	fwrite(&PointSize, sizeof(float), 1, SaveGMESH);

	//循环写入数据
	for (unsigned int i = 0; i < PointSize; i++)
	{
		fwrite(&VerticesIndex->at(i), sizeof(float), 1, SaveGMESH);
		fwrite(&NormalsIndex->at(i), sizeof(float), 1, SaveGMESH);
		fwrite(&TextureIndex->at(i), sizeof(float), 1, SaveGMESH);
	}

	fclose(SaveGMESH);
}