#include "D3DImporter.h"
#include "D3DExporter.h"
#include "Importer.h"

#include "Utils.h"


GM3DImporter::GM3DImporter()
{
	D3DRegisterExporter(exp);
	D3DRegisterImporter(imp);
}

bool GM3DImporter::importModel(const std::string& file)
{
	if ((scene = imp.ReadFile(file, ppf)) == 0)
	{
		error = imp.GetErrorString();
		return 0;
	}

	return 1;
}

bool GM3DImporter::exportModel(const std::string& file)
{
	if (scene == 0)
	{
		error = "GM3DImporter: Scene not loaded";
		return 0;
	}

	if (exp.Export(scene, GetExtension(file.c_str()), file.c_str()) != AI_SUCCESS)
	{
		error = exp.GetErrorString();
		return 0;
	}

	return 1;
}

const char* GM3DImporter::getError()
{
	return error;
}

const aiScene* GM3DImporter::getScene()
{
	return scene;
}
