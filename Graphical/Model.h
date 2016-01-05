#pragma once

#include <vector>

class model
{
	std::vector<float> VerticesData;
	std::vector<float> NormalsData;
	std::vector<float> TextureData;

	unsigned ModelSize = 0;

public:
	struct pointData
	{
		float VerticesData;
		float NormalsData;
		float TextureData;

		pointData(float, float, float);
	};

	const void* getVerticesData();
	const void* getNormalsData();
	const void* getTextureData();

	bool loadModel(const char*);

	void clear();

	void addPoint(float, float, float);

	unsigned int size();

	pointData operator [](int);
};