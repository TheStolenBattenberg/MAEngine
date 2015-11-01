class Terrain : public Object {
	public:
		void Generate();
		void Render();
		void Release();

	private:
		IDirect3DVertexBuffer9 *VBuffer;
		IDirect3DIndexBuffer9 *IBuffer;
		LPDIRECT3DTEXTURE9 Texture;
};