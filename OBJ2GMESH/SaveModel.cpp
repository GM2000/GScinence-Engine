
#include <fstream>
#include <vector>
#include <iterator>

void saveModel(const char* FileName, std::vector<float>* VerticesIndex, std::vector<float>* TextureIndex, std::vector<float>* NormalsIndex)
{
	FILE *SaveGMESH = fopen(FileName, "wb");

	//��ȡ��С
	unsigned int PointSize = VerticesIndex->size();

	//ģ���ļ�ͷ
	fwrite(&PointSize, sizeof(float), 1, SaveGMESH);

	//ѭ��д������
	for (unsigned int i = 0; i < PointSize; i++)
	{
		fwrite(&VerticesIndex->at(i), sizeof(float), 1, SaveGMESH);
		fwrite(&NormalsIndex->at(i), sizeof(float), 1, SaveGMESH);
		fwrite(&TextureIndex->at(i), sizeof(float), 1, SaveGMESH);
	}

	fclose(SaveGMESH);
}