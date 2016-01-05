
#include "../Graphical/Model.h"
#include <iostream>
#include <vector>

void readOBJ(const char*, std::vector<float>*, std::vector<float>*, std::vector<float>*, std::vector<unsigned int>*, std::vector<unsigned int>*, std::vector<unsigned int>*);
void saveModel(const char*, std::vector<float>*, std::vector<float>*, std::vector<float>*);

int main(int argc,char *argv[])
{
	std::cout << "/*****************************************************************/" << std::endl;
	std::cout << "/*                                                               */" << std::endl;
	std::cout << "/*    1----1----1       ------       1----     1-----    1       */" << std::endl;
	std::cout << "/*    1    1    1      -      -      1    -    1         1       */" << std::endl;
	std::cout << "/*    1    1    1     -        -     1     1   1-----    1       */" << std::endl;
	std::cout << "/*    1    1    1      -      -      1    -    1         1       */" << std::endl;
	std::cout << "/*    1    1    1       ------       1----     1-----    1-----  */" << std::endl;
	std::cout << "/*                                                               */" << std::endl;
	std::cout << "/*                                                               */" << std::endl;
	std::cout << "/*                                 Model Conver Start            */" << std::endl;
	std::cout << "/*                                                               */" << std::endl;
	std::cout << "/*                                                               */" << std::endl;
	std::cout << "/*                                       ----Made By GM2000      */" << std::endl;
	std::cout << "/*                                                               */" << std::endl;
	std::cout << "/*   Warning!Please make sure your model just use one texture    */" << std::endl;
	std::cout << "/*****************************************************************/" << std::endl;

	bool HasInputTexture = false;

	char HasIndex = false;

	std::vector<std::string> Texture;

	//定义文件名
	char *FileName = new char[256];

	//判断是否直接使用程序打开
	if (argc == 1)
	{
		//输入文件名
		std::cout << "Please input the file name:" << std::endl;
		std::cin.getline(FileName, 256);
	}
	//是
	else
	{
		FileName = argv[1];
	}

	//储存顶点数据以及图形索引
	std::cout << "Do you want to make a model that have point index?<0>" << std::endl;
	std::cin.getline(&HasIndex, 1);

	//定义变量
	std::cout << "No error" << std::endl;

	std::vector<float> VerticesData;
	std::vector<float> NormalsData;
	std::vector<float> TextureData;

	std::vector<unsigned int> VerticesIndex;
	std::vector<unsigned int> NormalsIndex;
	std::vector<unsigned int> TextureIndex;

	std::vector<float> VerticesTotal;
	std::vector<float> NormalsTotal;
	std::vector<float> TextureTotal;

	//开始加载
	readOBJ(FileName, &VerticesData, &NormalsData, &TextureData, &VerticesIndex, &NormalsIndex, &TextureIndex);

	std::cout << "Waiting for loading model,it mabey will take a long time" << std::endl;

	std::cout << "Load complete!start to Conver" << std::endl;

	//转换格式
	VerticesTotal.resize(VerticesIndex.size() * 3);
	NormalsTotal.resize(VerticesIndex.size() * 3);
	TextureTotal.resize(VerticesIndex.size() * 3);

	if (!HasIndex)
	{
		for (unsigned int i = 0; i < VerticesIndex.size(); i++)
		{
			VerticesTotal[i * 3] = VerticesData[(unsigned int)VerticesIndex[i] * 3 - 3];
			VerticesTotal[i * 3 + 1] = VerticesData[(unsigned int)VerticesIndex[i] * 3 - 2];
			VerticesTotal[i * 3 + 2] = VerticesData[(unsigned int)VerticesIndex[i] * 3 - 1];

			TextureTotal[i * 3] = TextureData[(unsigned int)TextureIndex[i] * 3 - 3];
			TextureTotal[i * 3 + 1] = TextureData[(unsigned int)TextureIndex[i] * 3 - 2];
			TextureTotal[i * 3 + 2] = TextureData[(unsigned int)TextureIndex[i] * 3 - 1];

			NormalsTotal[i * 3] = NormalsData[(unsigned int)NormalsIndex[i] * 3 - 3];
			NormalsTotal[i * 3 + 1] = NormalsData[(unsigned int)NormalsIndex[i] * 3 - 2];
			NormalsTotal[i * 3 + 2] = NormalsData[(unsigned int)NormalsIndex[i] * 3 - 1];
		}
	}
	//获取输入路径
	std::cout << "Conver Complete!Now saving file to " << FileName << ".GMesh" << std::endl;

	std::string FileType = ".GMesh";
	std::string SaveFileName(FileName + FileType);
	saveModel(SaveFileName.c_str(), &VerticesTotal, &TextureTotal, &NormalsTotal);

	std::cout << "Complete!Now checking!" << std::endl;

	//检验
	
	model Model;
	Model.loadModel(SaveFileName.c_str());


	std::cout << "Checking no error,All done!" << std::endl;

	
	std::cout << "/*****************************************************************/" << std::endl;
	std::cout << "/*                                                               */" << std::endl;
	std::cout << "/*    1----1----1       ------       1----     1-----    1       */" << std::endl;
	std::cout << "/*    1    1    1      -      -      1    -    1         1       */" << std::endl;
	std::cout << "/*    1    1    1     -        -     1     1   1-----    1       */" << std::endl;
	std::cout << "/*    1    1    1      -      -      1    -    1         1       */" << std::endl;
	std::cout << "/*    1    1    1       ------       1----     1-----    1-----  */" << std::endl;
	std::cout << "/*                                                               */" << std::endl;
	std::cout << "/*                                                               */" << std::endl;
	std::cout << "/*                                 Model Conver Done             */" << std::endl;
	std::cout << "/*                                                               */" << std::endl;
	std::cout << "/*                                                               */" << std::endl;
	std::cout << "/*                                       ----Made By GM2000      */" << std::endl;
	std::cout << "/*                                                               */" << std::endl;
	std::cout << "/*   Warning!Please make sure your model just use one texture    */" << std::endl;
	std::cout << "/*****************************************************************/" << std::endl;

	while (true);
}