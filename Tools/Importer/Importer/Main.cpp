#include "importer.h"
#include <iostream>

int main(int argc, char** argv)
{
	if (argc < 3)
	{
		std::cout << "Usage: importer in out" << std::endl;
		return 1;
	}

	GM3DImporter imp;

	if (!imp.importModel(argv[1]))
	{
		std::cout << imp.getError() << std::endl;
		return 1;
	}

	if (!imp.exportModel(argv[2]))
	{
		std::cout << imp.getError() << std::endl;
		return 1;
	}

	return 0;
}
