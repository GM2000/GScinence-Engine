
#include <iostream>
#include <fstream>
#include <vector>

int main(int argc,char *argv[])
{
	//�ļ���
	std::ifstream LoadOBJ;

	//�ж��Ƿ�ֱ��ʹ�ó����
	if (argc == 1)
	{
		//�����ļ���
		char FileName[256];
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
	}

	//�ɹ����أ�
	if (!LoadOBJ)
	{
		std::cout << "[ERROR]Unknow problem!Cannot open this file." << std::endl;
		while (true);
	}
	//ѭ����ȡ�ļ�
	while (LoadOBJ)
	{
		//�����ǻ��з������ѭ��
		char FirstChar = LoadOBJ.get();

		while (FirstChar == 10)
		{
			FirstChar = LoadOBJ.get();
		}
		//��ȡ��һ���ַ�
		std::cout << FirstChar << std::endl;
		//������һ��
		while ((LoadOBJ.get() != 10) && LoadOBJ);
	}
	std::cout << std::endl;
	while (true);
}