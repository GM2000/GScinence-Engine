
#include <fstream>
#include <vector>
#include <iterator>

void saveModel(const char* FileName, std::vector<float>* VerticesIndex, std::vector<float>* TextureIndex, std::vector<float>* NormalsIndex)
{
	std::ofstream SaveGMESH;
	SaveGMESH.open(FileName, std::ios::binary);

	//���þ���
	SaveGMESH.setf(SaveGMESH.fixed);
	SaveGMESH.precision(4);

	//��ȡ��С
	unsigned int PointSize = VerticesIndex->size();

	//ģ���ļ�ͷ
	SaveGMESH << PointSize;
	SaveGMESH << std::endl;

	//ѭ��д������
	for (unsigned int i = 0; i < PointSize; i++)
	{
		SaveGMESH.write((char*)&VerticesIndex->at(i),sizeof(float));
		SaveGMESH.write((char*)&NormalsIndex->at(i), sizeof(float));
		SaveGMESH.write((char*)&TextureIndex->at(i), sizeof(float));
	}

	SaveGMESH.close();
}