#include <iostream>

int main(int argc, char* argv[])
{
	std::cout << "Emulator started!" << std::endl;

	std::cout << "argc = " << argc << std::endl;
	for (auto i = 0; i < argc; i++)
	{
		std::cout << "argv[" << i << "] = " << argv[i] << std::endl;
	}

	return 0;
}
