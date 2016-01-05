
#include "Model.h"
#include <vector>
#include <fstream>

bool model::loadModel(const char* FileName)
{
	FILE *LoadModel = fopen(FileName, "rb");

	fread(&ModelSize, sizeof(unsigned int), 1, LoadModel);

	VerticesData.resize(ModelSize);
	TextureData.resize(ModelSize);
	NormalsData.resize(ModelSize);

	//ѭ����ȡ�ļ�
	for (unsigned int i = 0; i < ModelSize; i++)
	{
		//��ȡ����
		fread(&VerticesData[i], sizeof(unsigned int), 1, LoadModel);

		//��ȡ����
		fread(&NormalsData[i], sizeof(unsigned int), 1, LoadModel);

		//��ȡ����
		fread(&TextureData[i], sizeof(unsigned int), 1, LoadModel);
	}

	//�ر��ļ�
	fclose(LoadModel);

	return true;
}
void model::clear()
{
	if (ModelSize != 0)
	{
		VerticesData.clear();
		NormalsData.clear();
		TextureData.clear();
	}
}

void model::addPoint(float VerticesPos, float NormalsPos, float TeturePos)
{
	ModelSize++;

	VerticesData.push_back(VerticesPos);
	NormalsData.push_back(NormalsPos);
	TextureData.push_back(TeturePos);
}

model::pointData model::operator [](int i)
{
	return pointData(VerticesData[i], NormalsData[i], TextureData[i]);
}

model::pointData::pointData(float VerticesData, float NormalsData, float TextureData)
{
	pointData::VerticesData = VerticesData;
	pointData::NormalsData = NormalsData;
	pointData::TextureData = TextureData;
}

const void* model::getVerticesData()
{
	return &VerticesData[0];
}

const void* model::getNormalsData()
{
	return &NormalsData[0];
}

const void* model::getTextureData()
{
	return &TextureData[0];
}

unsigned int model::size()
{
	return ModelSize;
}