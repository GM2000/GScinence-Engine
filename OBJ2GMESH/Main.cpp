
#include "../Graphical/Model.h"
#include <iostream>
#include <vector>

void readOBJ(const char*, std::vector<float>*, std::vector<float>*, std::vector<float>*, std::vector<float>*, std::vector<float>*, std::vector<float>*);
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

	std::vector<float> VerticesIndex;
	std::vector<float> NormalsIndex;
	std::vector<float> TextureIndex;

	//开始加载
	readOBJ(FileName, &VerticesData, &NormalsData, &TextureData, &VerticesIndex, &NormalsIndex, &TextureIndex);

	std::cout << "Waiting for loading model,it mabey will take a long time" << std::endl;

	std::cout << "Load complete!start to Conver" << std::endl;

	//转换格式
	if (!HasIndex)
	{
		for (unsigned int i = 0; i < VerticesIndex.size(); i++)
		{
			VerticesIndex[i * 3] = VerticesData[(unsigned int)VerticesIndex[i] * 3 - 3];
			TextureIndex[i] = TextureData[(unsigned int)TextureIndex[i] * 3 - 3];
			NormalsIndex[i] = NormalsData[(unsigned int)NormalsIndex[i] * 3 - 3];
		}
	}
	//获取输入路径
	std::cout << "Conver Complete!Now saving file to " << FileName << ".GMesh" << std::endl;

	std::string FileType = ".GMesh";
	std::string SaveFileName(FileName + FileType);
	saveModel(SaveFileName.c_str(), &VerticesIndex, &TextureIndex, &NormalsIndex);

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