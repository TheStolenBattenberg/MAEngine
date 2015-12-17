#include "MPMExporter.h"

#include "ModelMPM.h"

#include <assimp\scene.h>
#include <DefaultIOSystem.h>
#include <BaseImporter.h>

void MPMRegisterExporter(Assimp::Exporter& exp)
{
	Assimp::Exporter::ExportFormatEntry entry("mpm", "MAE Packed Model", "mpm", [](const char* file, Assimp::IOSystem* iohandler, const aiScene* scene, const Assimp::ExportProperties* prop)
	{
		Assimp::IOStream* f = iohandler->Open(file, "wb");

		if (f == 0)
			throw new DeadlyExportError("Failed to open file");

		MPMModel::Header h;

		if (f->Write(&h, sizeof(h), 1) != 1)
			throw new DeadlyExportError("Failed to write to file");

		iohandler->Close(f);
	});

	exp.RegisterExporter(entry);
}
