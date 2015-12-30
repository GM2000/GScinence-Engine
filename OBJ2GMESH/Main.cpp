
#include <iostream>
#include <fstream>
#include <vector>

int main(int argc,char *argv[])
{
	//文件流
	std::ifstream LoadOBJ;

	//判断是否直接使用程序打开
	if (argc == 1)
	{
		//定义文件名
		char FileName[256];
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
	}

	//成功加载？
	if (!LoadOBJ)
	{
		std::cout << "[ERROR]Unknow problem!Cannot open this file." << std::endl;
		while (true);
	}
	//循环读取文件
	while (LoadOBJ)
	{
		//若还是换行符则继续循环
		char FirstChar = LoadOBJ.get();

		while (FirstChar == 10)
		{
			FirstChar = LoadOBJ.get();
		}
		//读取第一个字符
		std::cout << FirstChar << std::endl;
		//跳到下一行
		while ((LoadOBJ.get() != 10) && LoadOBJ);
	}
	std::cout << std::endl;
	while (true);
}