//It's bad to have these includes here, need to remove them still.
#include <d3d9.h>
#include <d3dx9.h>

class Object
{
	public:
		D3DXMATRIX* GetTransformation();

	private:
		D3DXMATRIX Translation;
		D3DXMATRIX Rotation;
		D3DXMATRIX Scale;
		D3DXMATRIX Transformation;
};