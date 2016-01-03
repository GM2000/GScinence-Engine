
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

	//写入顶点
	for (unsigned int i = 0; i < PointSize; i++)
	{
		SaveGMESH << (VerticesIndex->at(i));
		SaveGMESH << " ";
	}
	SaveGMESH << std::endl;

	//写入纹理
	for (unsigned int i = 0; i < PointSize; i++)
	{
		SaveGMESH << TextureIndex->at(i);
		SaveGMESH << " ";
	}
	SaveGMESH << std::endl;

	//写入法线
	for (unsigned int i = 0; i < PointSize; i++)
	{
		SaveGMESH << NormalsIndex->at(i);
		SaveGMESH << " ";
	}
	SaveGMESH << std::endl;
	SaveGMESH.close();
}