#include "MD2Type.h"
#include "MSMType.h"


/**
* Types
*/
struct Vertex
{
	float x, y, z;
};

struct Normal
{
	float x, y, z;
};

struct TexCoord
{
	float s, t;
};


/**
* MD2 Model
*/
class MD2Model : public Object {
public:
	~MD2Model();

	bool load(std::string model);
	void setTexture(LPDIRECT3DTEXTURE9 tex);

	LPDIRECT3DVERTEXBUFFER9 getVB(uint frame);
	LPDIRECT3DVERTEXBUFFER9 getTB();
	LPDIRECT3DINDEXBUFFER9  getIB();
	LPDIRECT3DTEXTURE9      getTex();

	uint getVertCount();
	uint getTriCount();
	uint getFrameCount();

private:
	uint vertCount = 0;
	uint triCount  = 0;

	LPDIRECT3DTEXTURE9 tex = 0;

	std::vector<LPDIRECT3DVERTEXBUFFER9> vertBufs;
	LPDIRECT3DVERTEXBUFFER9 texBuf = 0;
	LPDIRECT3DINDEXBUFFER9 indBuf = 0;
};

/**
 * MSM Model
 */
class MSMModel : public Object {
public:
	~MSMModel();

	bool load(std::string model);
	void setTexture(LPDIRECT3DTEXTURE9, uint mesh);

	LPDIRECT3DVERTEXBUFFER9 getMesh(uint mesh);
	LPDIRECT3DINDEXBUFFER9  getIB(uint mesh);
	LPDIRECT3DTEXTURE9      getTex(uint mesh);
	D3DMATERIAL9            getMat(uint mesh);

	uint getVertCount(uint mesh);
	uint getTriCount(uint mesh);
	uint getMeshCount();

private: //There has to be a better way to handle multiple mesh objects.
	ushort meshCount = 0;
	std::vector<ushort> vertCount;
	std::vector<ushort> triCount;
	std::vector<byte> hasShader;

	std::vector<LPDIRECT3DTEXTURE9> tex;
	std::vector<D3DMATERIAL9> mat;

	std::vector<LPDIRECT3DVERTEXBUFFER9> meshBuf;
	std::vector<LPDIRECT3DINDEXBUFFER9> indBuf;
};