#define DLLEXPORT extern "C" __declspec (dllexport)

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#define MS_MAX_NAME             32
#define MS_MAX_PATH             256

#include <string.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <Windows.h>

#pragma pack(1)
#ifndef byte
typedef unsigned char byte;
#endif

#ifndef word
typedef unsigned short word;
#endif

typedef float   msVec4[4];
typedef float   msVec3[3];
typedef float   msVec2[2];

typedef enum {
	eSelected = 1, eSelected2 = 2, eHidden = 4, eDirty = 8,
	eAveraged = 16, eUnused = 32
} msFlag;

typedef struct msVertex
{
	byte        nFlags;
	msVec3      Vertex;
	float       u, v;
	char        nBoneIndex;
} msVertex;

typedef struct
{
	word        nFlags;
	word        nVertexIndices[3];
	word        nNormalIndices[3];
	msVec3      Normal;
	byte        nSmoothingGroup;
} msTriangle;

typedef struct msMesh
{
	byte        nFlags;
	char        szName[MS_MAX_NAME];
	char        nMaterialIndex;

	word        nNumVertices;
	word        nNumAllocedVertices;
	msVertex*   pVertices;

	word        nNumNormals;
	word        nNumAllocedNormals;
	msVec3*     pNormals;

	word        nNumTriangles;
	word        nNumAllocedTriangles;
	msTriangle* pTriangles;
} msMesh;

typedef struct msMaterial
{
	int         nFlags;
	char        szName[MS_MAX_NAME];
	msVec4      Ambient;
	msVec4      Diffuse;
	msVec4      Specular;
	msVec4      Emissive;
	float       fShininess;
	float       fTransparency;
	char        szDiffuseTexture[MS_MAX_PATH];
	char        szAlphaTexture[MS_MAX_PATH];
	int         nName;
} msMaterial;

typedef struct msPositionKey
{
	float       fTime;
	msVec3      Position;
} msPositionKey;

typedef struct msRotationKey
{
	float   fTime;
	msVec3  Rotation;
} msRotationKey;

typedef struct msBone
{
	int             nFlags;
	char            szName[MS_MAX_NAME];
	char            szParentName[MS_MAX_NAME];
	msVec3          Position;
	msVec3          Rotation;

	int             nNumPositionKeys;
	int             nNumAllocedPositionKeys;
	msPositionKey*  pPositionKeys;

	int             nNumRotationKeys;
	int             nNumAllocedRotationKeys;
	msRotationKey*  pRotationKeys;
} msBone;

/* msModel */
typedef struct msModel
{
	int         nNumMeshes;
	int         nNumAllocedMeshes;
	msMesh*     pMeshes;

	int         nNumMaterials;
	int         nNumAllocedMaterials;
	msMaterial* pMaterials;

	int         nNumBones;
	int         nNumAllocedBones;
	msBone*     pBones;

	int         nFrame;
	int         nTotalFrames;

	msVec3      Position;
	msVec3      Rotation;
} msModel;
#pragma pack()
// ----------------------------------------------------------------------------

class cMsPlugIn
{
public:
	enum
	{
		eTypeImport = 1,
		eTypeExport = 2,
		eTypeTool = 3,
		eTypeEdit = 4,
		eTypeVertex = 5,
		eTypeFace = 6,
		eTypeAnimate = 7
	};

public:
	cMsPlugIn() {};
	virtual ~cMsPlugIn() {};

public:
	virtual int             GetType() = 0;
	virtual const char *    GetTitle() = 0;
	virtual int             Execute(msModel* pModel) = 0;
};

class MyPlugin : public cMsPlugIn
{
public:
	MyPlugin()
	{
		strcpy(szTitle, "MA - Engine MSM...");
	}

	virtual ~MyPlugin() { }

	int GetType()
	{
		return cMsPlugIn::eTypeExport;
	}

	const char *GetTitle()
	{
		return szTitle;
	}

	int Execute(msModel *);

private:
	char szTitle[64];
};

int MyPlugin::Execute(msModel * pModel)
{
	if (!pModel)
	{
		return -1;
	}

	OPENFILENAME ofn;
	char szFileName[MAX_PATH] = "";
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = "MAE Static Model (*.msm)\0*.msm\0";
	ofn.lpstrFile = szFileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = "msm";
	GetSaveFileName(&ofn);

	//Flags.
	int MSM_VERSION = 0x00000001;


	byte nHasShader = 0;

	int nNumMeshes = pModel->nNumMeshes;
	std::ofstream f_MSM(ofn.lpstrFile, std::ios::out | std::ios::binary);;
	{
		f_MSM.write("M", sizeof(char));
		f_MSM.write("S", sizeof(char));
		f_MSM.write("M", sizeof(char));
		f_MSM.write("f", sizeof(char));
		f_MSM.write(reinterpret_cast<const char *>(&MSM_VERSION), sizeof(int));
		f_MSM.write(reinterpret_cast<const char*>(&nNumMeshes), sizeof(int));

		for (int group = 0; group < nNumMeshes; group++)
		{
			f_MSM.write(reinterpret_cast<const char *>(&pModel->pMeshes[group].nNumVertices), sizeof(word));
			f_MSM.write(reinterpret_cast<const char *>(&pModel->pMeshes[group].nNumTriangles), sizeof(word));
			f_MSM.write(reinterpret_cast<const char *>(&nHasShader), sizeof(byte));

			//Vertices
			for (int vertex = 0; vertex < pModel->pMeshes[group].nNumVertices; vertex++)
			{
				msVertex * pVertices = pModel->pMeshes[group].pVertices;
				f_MSM.write(reinterpret_cast<const char *>(&pVertices->Vertex[0]), sizeof(float));
				f_MSM.write(reinterpret_cast<const char *>(&pVertices->Vertex[1]), sizeof(float));
				f_MSM.write(reinterpret_cast<const char *>(&pVertices->Vertex[2]), sizeof(float));
			}

			//Faces
			for (int face = 0; face < pModel->pMeshes[group].nNumTriangles; face++)
			{
				msTriangle * pFaces = pModel->pMeshes[group].pTriangles;
				f_MSM.write(reinterpret_cast<const char *>(&pFaces->nVertexIndices[0]), sizeof(word));
				//Norm 1
				//Texcoord 1

				f_MSM.write(reinterpret_cast<const char *>(&pFaces->nVertexIndices[1]), sizeof(word));
				//Norm 2
				//Texcoord 2

				f_MSM.write(reinterpret_cast<const char *>(&pFaces->nVertexIndices[2]), sizeof(word));
				//Norm 3
				//Texcoord 3
			}
		}
	}
	f_MSM.close();

	delete[] pModel;
	return 0;
}


DLLEXPORT MyPlugin *CreatePlugIn()
{

	return new MyPlugin;
}