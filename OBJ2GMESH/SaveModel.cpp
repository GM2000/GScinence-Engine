
#include <fstream>
#include <vector>
#include <iterator>

void saveModel(const char* FileName, std::vector<float>* VerticesIndex, std::vector<float>* TextureIndex, std::vector<float>* NormalsIndex)
{
	std::ofstream SaveGMESH;
	SaveGMESH.open(FileName, std::ios::binary);

	//设置精度
	SaveGMESH.setf(SaveGMESH.fixed);
	SaveGMESH.precision(4);

	//获取大小
	unsigned int PointSize = VerticesIndex->size();

	//模型文件头
	SaveGMESH << PointSize;
	SaveGMESH << std::endl;

	//循环写入数据
	for (unsigned int i = 0; i < PointSize; i++)
	{
		SaveGMESH.write((char*)&VerticesIndex->at(i),sizeof(float));
		SaveGMESH.write((char*)&NormalsIndex->at(i), sizeof(float));
		SaveGMESH.write((char*)&TextureIndex->at(i), sizeof(float));
	}

	SaveGMESH.close();
}