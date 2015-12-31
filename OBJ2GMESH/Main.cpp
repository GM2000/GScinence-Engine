
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

	//�ļ���
	std::ifstream LoadOBJ;

	//�����ļ���
	char *FileName = new char[256];

	//�ж��Ƿ�ֱ��ʹ�ó����
	if (argc == 1)
	{
		//�����ļ���
		std::cout << "Please input the file name:" << std::endl;
		std::cin.getline(FileName, 256);

		//����
		LoadOBJ = std::ifstream(FileName);
	}
	//��
	else
	{
		//����
		LoadOBJ = std::ifstream(argv[1]);
		FileName = argv[1];
	}

	//���涥�������Լ�ͼ������
	std::cout << "Do you want to make a model that have point index?<0>" << std::endl;
	std::cin.getline(&HasIndex, 1);

	//�ɹ����أ�
	if (!LoadOBJ)
	{
		std::cout << "[ERROR]Unknow problem!Cannot open this file." << std::endl;
		while (true);
	}

	//�������
	std::cout << "No error" << std::endl;

	std::vector<float> VerticesData;
	std::vector<float> NormalsData;
	std::vector<float> TextureData;

	std::vector<float> VerticesIndex;
	std::vector<float> NormalsIndex;
	std::vector<float> TextureIndex;

	//��ȡÿ�е�һ����
	char FirstWord[2];

	float GetData = 0;

	LoadOBJ.setf(LoadOBJ.fixed);
	LoadOBJ.precision(4);

	std::cout << "Waiting for loading model,it mabey will take a long time" << std::endl;
	//ѭ��
	while (!LoadOBJ.eof())
	{
		//��ȡ��һ����
		LoadOBJ >> FirstWord;

		//���ö���
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
		//���÷���
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
		//��������
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
		//��������
		else if (FirstWord[0] == 'f' && FirstWord[1] == 0)
		{
#ifdef _DEBUG
			std::cout << "Find F" << std::endl;
#endif
			//����ַ���
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
		//����
		while (LoadOBJ.get() != 10 && !LoadOBJ.eof());
	}
	//�ر��ļ�
	LoadOBJ.close();

	std::cout << "Load complete!start to Conver" << std::endl;

	//ת����ʽ
	if (!HasIndex)
	{
		for (unsigned int i = 0; i < VerticesIndex.size(); i++)
		{
			VerticesIndex[i] = VerticesData[(unsigned int)VerticesIndex[i] - 1];
			TextureIndex[i] = TextureData[(unsigned int)TextureIndex[i] - 1];
			NormalsIndex[i] = NormalsData[(unsigned int)NormalsIndex[i] - 1];
		}
	}
	//��ȡ����·��
	std::cout << "Conver Complete!Now saving file to " << FileName << ".GMesh" << std::endl;

	std::string FileType = ".GMesh";
	std::string SaveFileName(FileName + FileType);

	std::ofstream SaveGMESH;
	SaveGMESH.open(SaveFileName, std::ios::binary);

	//���þ���
	SaveGMESH.setf(SaveGMESH.fixed);
	SaveGMESH.precision(4);
	//��ȡ��С
	unsigned int PointSize = VerticesIndex.size();

	//д�붥��
	SaveGMESH << PointSize;
	SaveGMESH << std::endl;
	for (unsigned int i = 0; i < PointSize; i++)
	{
		SaveGMESH << VerticesIndex[i];
		SaveGMESH << " ";
	}
	SaveGMESH << std::endl;
	//д������
	for (unsigned int i = 0; i < PointSize; i++)
	{
		SaveGMESH << TextureIndex[i];
		SaveGMESH << " ";
	}
	SaveGMESH << std::endl;
	//д�뷨��
	for (unsigned int i = 0; i < PointSize; i++)
	{
		SaveGMESH << NormalsIndex[i];
		SaveGMESH << " ";
	}
	SaveGMESH << std::endl;
	SaveGMESH.close();

	std::cout << "Complete!Now checking!" << std::endl;

	//����
	std::ifstream SaveGMESHCheck;
	SaveGMESHCheck.open(SaveFileName, std::ios::binary);

	SaveGMESHCheck.setf(SaveGMESHCheck.fixed);
	SaveGMESHCheck.precision(4);

	SaveGMESHCheck >> PointSize;

	std::vector<float> TmpVerticesIndex(PointSize);
	std::vector<float> TmpNormalsIndex(PointSize);
	std::vector<float> TmpTextureIndex(PointSize);

	//��ȡ����
	for (unsigned int i = 0; i < PointSize; i++)
	{
		SaveGMESHCheck >> TmpVerticesIndex[i];

		if (TmpVerticesIndex[i] != VerticesIndex[i])
		{
			std::cout << "Find a error!" << std::endl;
		}

	}
	//��ȡ����
	for (unsigned int i = 0; i < PointSize; i++)
	{
		SaveGMESHCheck >> TmpTextureIndex[i];

		if (TmpTextureIndex[i] != TextureIndex[i])
		{
			std::cout << "Find a error!" << std::endl;
		}
	}
	//��ȡ����
	for (unsigned int i = 0; i < PointSize; i++)
	{
		SaveGMESHCheck >> TmpNormalsIndex[i];

		if (TmpNormalsIndex[i] != NormalsIndex[i])
		{
			std::cout << "Find a error!" << std::endl;
		}
	}
	//�ر��ļ�
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