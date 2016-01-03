
#include "Model.h"
#include <vector>
#include <fstream>

bool model::loadModel(const char* FileName)
{
	std::ifstream LoadModel;
	LoadModel.open(FileName, std::ios::binary);

	LoadModel.setf(LoadModel.fixed);
	LoadModel.precision(4);

	LoadModel >> ModelSize;

	VerticesData.resize(ModelSize);
	TextureData.resize(ModelSize);
	NormalsData.resize(ModelSize);

	//读取顶点
	for (unsigned int i = 0; i < ModelSize; i++)
	{
		LoadModel >> VerticesData[i];
	}
	//读取纹理
	for (unsigned int i = 0; i < ModelSize; i++)
	{
		LoadModel >> TextureData[i];
	}
	//读取法线
	for (unsigned int i = 0; i < ModelSize; i++)
	{
		LoadModel >> NormalsData[i];
	}
	//关闭文件
	LoadModel.close();

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
unsigned int model::size()
{
	return ModelSize;
}