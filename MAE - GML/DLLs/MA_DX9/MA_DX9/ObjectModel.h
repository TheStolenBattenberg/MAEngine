/**
 * 
 * NOTE :-> This is probably a rather bad way to go about the Model Objects, it shouldn't be bad for speed but more for expandability.
 *          It might be a good idea to split the ObjectModel class into different ones, if we have more model types.
 *
 * Also note that the MD2 loader is based off an artical by Brian Jorgensen, on Gamedev.net Props to him for helping the world learn!
 *
 */

#include "MD2Type.h" //Features: Morph Target Animation.
#include "MSMType.h" ////Features: Internal Shader, Super small file size.

//#include "MS3DType.h" //Features: Bone Based Animation. !NOTE - Currently a little broken.

struct Vertex
{
	float x, y, z;
};

struct TexCoord
{
	float s, t;
};

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
	LPDIRECT3DINDEXBUFFER9 indBuf = 0;
	LPDIRECT3DVERTEXBUFFER9 texBuf = 0;
};
