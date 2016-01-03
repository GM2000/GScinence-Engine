
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

	//д�붥��
	for (unsigned int i = 0; i < PointSize; i++)
	{
		SaveGMESH << (VerticesIndex->at(i));
		SaveGMESH << " ";
	}
	SaveGMESH << std::endl;

	//д������
	for (unsigned int i = 0; i < PointSize; i++)
	{
		SaveGMESH << TextureIndex->at(i);
		SaveGMESH << " ";
	}
	SaveGMESH << std::endl;

	//д�뷨��
	for (unsigned int i = 0; i < PointSize; i++)
	{
		SaveGMESH << NormalsIndex->at(i);
		SaveGMESH << " ";
	}
	SaveGMESH << std::endl;
	SaveGMESH.close();
}