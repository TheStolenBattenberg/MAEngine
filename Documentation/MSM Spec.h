/**
 * 
 * MSM File type. (Static Model)
 *
 */

//Header
typedef struct {
	char id[4];				//MSMf
	int version;			//Should be "1", increment with versions.
} MSM_Header;

//Number of Vertices
u_16 VertexCount;

//Vertices
typedef struct {
	float vertex[3];
} MSM_Vertex;

//Number of Normals
u_16 NormalCount;

//Normals
typedef struct {
	float normal[3];
} MSM_Normal;

//Number of Faces.
u_16 FaceCount;

//Faces
typedef struct {
	u_8 Group;
	u_16 VertexIndex[3];
	u_16 NormalIndex[3];
	u_16 TextureCoordU[3];
	u_16 TextureCoordV[3];
} MSM_Face;

//Number of Materials
u_8 MaterialCount;

//Materials
typedef struct {
	u_8 MaterialType;
	
	//When Material Type is 0:
	u_8 VertexColour[4];
	
	//When Material Type is 1:
	u_8 MaterialNameLength;
	char MaterialName[MaterialNameLength];
	
	//When Material Type is 2:
	u_8 MaterialArchiveNameLength;
	char MaterialArchiveName[MaterialArchiveNameLength];
} MSM_Material;

//If the model has a shader. This shouldn't go over 1, it's only called ShaderCount to keep the same style.
u_8 ShaderCount;

typedef struct {
	u_8 ShaderType;
	
	//When Shader Type is 0:
	u_8 VShaderLength;
	char VShader[VShaderLength];
	u_8 PShaderLength;
	char PShader[PShaderLength];
	
	//When Shader Type is 1:
	u_8 VShaderNameLength;
	char VShaderName[VShaderNameLength];
	u_8 PShaderNameLength;
	char PShaderName[PShaderNameLength];
	
	//When Shader Type is 2:
	u_8 FXShaderNameLength;
	char FXShaderName;
} MSM_Shader;
