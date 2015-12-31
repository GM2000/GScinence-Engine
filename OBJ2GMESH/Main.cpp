
#include <iostream>
#include <fstream>
#include <vector>

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

	//文件流
	std::ifstream LoadOBJ;

	//定义文件名
	char *FileName = new char[256];

	//判断是否直接使用程序打开
	if (argc == 1)
	{
		//输入文件名
		std::cout << "Please input the file name:" << std::endl;
		std::cin.getline(FileName, 256);

		//加载
		LoadOBJ = std::ifstream(FileName);
	}
	//是
	else
	{
		//加载
		LoadOBJ = std::ifstream(argv[1]);
		FileName = argv[1];
	}

	//储存顶点数据以及图形索引
	std::cout << "Do you want to make a model that have point index?<0>" << std::endl;
	std::cin.getline(&HasIndex, 1);

	//成功加载？
	if (!LoadOBJ)
	{
		std::cout << "[ERROR]Unknow problem!Cannot open this file." << std::endl;
		while (true);
	}

	//定义变量
	std::cout << "No error" << std::endl;

	std::vector<float> VerticesData;
	std::vector<float> NormalsData;
	std::vector<float> TextureData;

	std::vector<float> VerticesIndex;
	std::vector<float> NormalsIndex;
	std::vector<float> TextureIndex;

	//读取每行第一个词
	char FirstWord[2];

	float GetData = 0;

	LoadOBJ.setf(LoadOBJ.fixed);
	LoadOBJ.precision(4);

	std::cout << "Waiting for loading model,it mabey will take a long time" << std::endl;
	//循环
	while (!LoadOBJ.eof())
	{
		//读取第一个词
		LoadOBJ >> FirstWord;

		//设置顶点
		if (FirstWord[0] == 'v' && FirstWord[1] == 0)
		{
#ifdef _DEBUG
			std::cout << "Find V	";
#endif

			for (int i = 0; i < 3; i++)
			{
				LoadOBJ >> GetData;
				VerticesData.push_back(GetData);
#ifdef _DEBUG
				std::cout << i << ":" << GetData << " ";
#endif
			}
#ifdef _DEBUG
			std::cout << std::endl;
#endif
			
		}
		//设置法线
		else if (FirstWord[0] == 'v' && FirstWord[1] == 'n')
		{
#ifdef _DEBUG
			std::cout << "Find VN	";
#endif

			for (int i = 0; i < 3; i++)
			{
				LoadOBJ >> GetData;
				NormalsData.push_back(GetData);
#ifdef _DEBUG
				std::cout << i << ":" << GetData << " ";
#endif
			}
#ifdef _DEBUG
			std::cout << std::endl;
#endif
		}
		//设置纹理
		else if (FirstWord[0] == 'v' && FirstWord[1] == 't')
		{
#ifdef _DEBUG
			std::cout << "Find VT	";
#endif

			for (int i = 0; i < 3; i++)
			{
				LoadOBJ >> GetData;
				TextureData.push_back(GetData);
#ifdef _DEBUG
				std::cout << i << ":" << GetData << " ";
#endif
			}
#ifdef _DEBUG
			std::cout << std::endl;
#endif
		}
		//设置索引
		else if (FirstWord[0] == 'f' && FirstWord[1] == 0)
		{
#ifdef _DEBUG
			std::cout << "Find F" << std::endl;
#endif
			//拆分字符串
			for (int i = 0; i < 3; i++)
			{
				char GetDatas[33];

				char cGetVI[11];
				char cGetNI[11];
				char cGetTI[11];

				LoadOBJ >> GetDatas;

				int NowFindData = 0;
				int Position = 0;

				for (int i = 0; i < 32; i++)
				{
					if (GetDatas[i] == '/')
					{
						NowFindData++;
						Position = 0;
					}
					else if (GetDatas[i] == 0)
					{
						break;
					}
					else
					{
						if (NowFindData == 0)
						{
							cGetVI[Position] = GetDatas[i];
							cGetVI[Position + 1] = 0;
						}
						else if (NowFindData == 1)
						{
							cGetTI[Position] = GetDatas[i];
							cGetTI[Position + 1] = 0;
						}
						else if (NowFindData == 2)
						{
							cGetNI[Position] = GetDatas[i];
							cGetNI[Position + 1] = 0;
						}
						Position++;
					}
				}

				unsigned int GetVI = atoi(cGetVI);
				unsigned int GetNI = atoi(cGetNI);
				unsigned int GetTI = atoi(cGetTI);

#ifdef _DEBUG
				std::cout << "VI" << i << ":" << GetVI << " ";
#endif
				VerticesIndex.push_back((float)GetVI);

#ifdef _DEBUG
				std::cout << "NI" << i << ":" << GetTI << " ";
#endif
				NormalsIndex.push_back((float)GetTI);

#ifdef _DEBUG
				std::cout << "TI" << i << ":" << GetNI << " ";
#endif
				TextureIndex.push_back((float)GetNI);
			}
#ifdef _DEBUG
			std::cout << std::endl;
#endif
		}
		//换行
		while (LoadOBJ.get() != 10 && !LoadOBJ.eof());
	}
	//关闭文件
	LoadOBJ.close();

	std::cout << "Load complete!start to Conver" << std::endl;

	//转换格式
	if (!HasIndex)
	{
		for (unsigned int i = 0; i < VerticesIndex.size(); i++)
		{
			VerticesIndex[i] = VerticesData[(unsigned int)VerticesIndex[i] - 1];
			TextureIndex[i] = TextureData[(unsigned int)TextureIndex[i] - 1];
			NormalsIndex[i] = NormalsData[(unsigned int)NormalsIndex[i] - 1];
		}
	}
	//获取输入路径
	std::cout << "Conver Complete!Now saving file to " << FileName << ".GMesh" << std::endl;

	std::string FileType = ".GMesh";
	std::string SaveFileName(FileName + FileType);

	std::ofstream SaveGMESH;
	SaveGMESH.open(SaveFileName, std::ios::binary);

	//设置精度
	SaveGMESH.setf(SaveGMESH.fixed);
	SaveGMESH.precision(4);
	//获取大小
	unsigned int PointSize = VerticesIndex.size();

	//写入顶点
	SaveGMESH << PointSize;
	SaveGMESH << std::endl;
	for (unsigned int i = 0; i < PointSize; i++)
	{
		SaveGMESH << VerticesIndex[i];
		SaveGMESH << " ";
	}
	SaveGMESH << std::endl;
	//写入纹理
	for (unsigned int i = 0; i < PointSize; i++)
	{
		SaveGMESH << TextureIndex[i];
		SaveGMESH << " ";
	}
	SaveGMESH << std::endl;
	//写入法线
	for (unsigned int i = 0; i < PointSize; i++)
	{
		SaveGMESH << NormalsIndex[i];
		SaveGMESH << " ";
	}
	SaveGMESH << std::endl;
	SaveGMESH.close();

	std::cout << "Complete!Now checking!" << std::endl;

	//检验
	std::ifstream SaveGMESHCheck;
	SaveGMESHCheck.open(SaveFileName, std::ios::binary);

	SaveGMESHCheck.setf(SaveGMESHCheck.fixed);
	SaveGMESHCheck.precision(4);

	SaveGMESHCheck >> PointSize;

	std::vector<float> TmpVerticesIndex(PointSize);
	std::vector<float> TmpNormalsIndex(PointSize);
	std::vector<float> TmpTextureIndex(PointSize);

	//读取顶点
	for (unsigned int i = 0; i < PointSize; i++)
	{
		SaveGMESHCheck >> TmpVerticesIndex[i];

		if (TmpVerticesIndex[i] != VerticesIndex[i])
		{
			std::cout << "Find a error!" << std::endl;
		}

	}
	//读取纹理
	for (unsigned int i = 0; i < PointSize; i++)
	{
		SaveGMESHCheck >> TmpTextureIndex[i];

		if (TmpTextureIndex[i] != TextureIndex[i])
		{
			std::cout << "Find a error!" << std::endl;
		}
	}
	//读取法线
	for (unsigned int i = 0; i < PointSize; i++)
	{
		SaveGMESHCheck >> TmpNormalsIndex[i];

		if (TmpNormalsIndex[i] != NormalsIndex[i])
		{
			std::cout << "Find a error!" << std::endl;
		}
	}
	//关闭文件
	SaveGMESHCheck.close();

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