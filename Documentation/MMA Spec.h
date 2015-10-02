/**
 * 
 * MMA File type.
 *
 */
 
 /**
  * Description of texture batching, and MMAs.
  * MMA allows us to have batched texture material data, which lets us have less draw calls on multiple texture models, by  holding texture data inside a model.
  * 
  * To do this, we need to convert texture coordinates for the models, which is a gigantic pain.
  * 
  * The archives do come with a limitation, it can only have two sizes of texture, for example, 128 and 64, 256 and 128, 512 and 256.
  * 
  *
  *
  */
  
//Header
typedef struct {
	char id[4];				//MMAf
	int version;			//1
} MMA_Header;

//Number of Textures;
u_16 TextureCount;

//Texture
typedef struct {
	//Texture Header
	typedef struct {
		u_16 TextureWidth;
		u_16 TextureHeight;
	} MMA_TextureHeader;

	
	//Texture Data 4 * (TextureWidth*TextureHeight);
	typedef struct {
		u_8 R;
		u_8 G;
		u_8 B;
		u_8 A;
	} MMA_TextureData;
} MMA_Texture;