#include "Mesh.h"

class Object
{
	public:
		D3DXMATRIX* GetTransformation();
		void SetTransformation(D3DXMATRIX trans);

	private:
		D3DXMATRIX Translation;
		D3DXMATRIX Rotation;
		D3DXMATRIX Scale;
		D3DXMATRIX Transformation;
};