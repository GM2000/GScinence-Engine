
#include <iostream>
#include <fstream>
#include <vector>

void readOBJ(const char* FileName, std::vector<float>* VerticesData,std::vector<float>* NormalsData,std::vector<float>* TextureData, std::vector<float>* VerticesIndex,std::vector<float>* NormalsIndex,std::vector<float>* TextureIndex)
{
	//��ȡÿ�е�һ����
	char FirstWord[256];

	//��ȡ������
	float GetData = 0;

	//�ļ���
	std::ifstream LoadOBJ(FileName);

	//�ɹ����أ�
	if (!LoadOBJ)
	{
		std::cout << "[ERROR]Unknow problem!Cannot open this file." << std::endl;
		while (true);
	}

	//���þ���
	LoadOBJ.setf(LoadOBJ.fixed);
	LoadOBJ.precision(4);

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
				VerticesData->push_back(GetData);
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
				NormalsData->push_back(GetData);
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
				TextureData->push_back(GetData);
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
				VerticesIndex->push_back((float)GetVI);

#ifdef _DEBUG
				std::cout << "NI" << i << ":" << GetTI << " ";
#endif
				NormalsIndex->push_back((float)GetTI);

#ifdef _DEBUG
				std::cout << "TI" << i << ":" << GetNI << " ";
#endif
				TextureIndex->push_back((float)GetNI);
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
}