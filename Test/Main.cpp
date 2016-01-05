
#include <GS\gsGraphical.h>
#include <iostream>
int main()
{
	if (gsgInit("娴嬭瘯"))
	{
		char cc[256];
		while (true)
		{
			std::cin.getline(cc, 256);
			std::cout << cc << std::endl;
		}
		return 0;
	}
	return 1;
}