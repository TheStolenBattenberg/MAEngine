/**
*
* NOTE :-> This MD2Type Class is taken from an example by Brian Jorgensen, on Gamedev.net.
*
*/

/**
 * Types.
 */
#ifndef byte
	typedef unsigned char byte;
#endif

namespace MD2Type {
	struct Header {
		int magic_number;
		int version;

		int skinwidth;
		int skinheight;
		int framesize;

		int num_skin;
		int num_xyz;
		int num_st;
		int num_tris;
		int num_glcmds;
		int num_frames;

		int ofs_skins;
		int ofs_st;
		int ofs_tris;
		int ofs_frames;
		int ofs_glcmds;
		int ofs_end;
	};

	struct Vertex
	{
		byte vertex[3];
		byte unused_normal_index;
	};

	struct Frame
	{
		float scale[3];
		float translate[3];
		char name[16];
		Vertex verticies[1];
	};

	struct Triangle
	{
		short vertex_indicies[3];
		short texture_indicies[3];
	};
	typedef short index_buffer[3];

	struct Texcoord
	{
		short s, t;
	};

	typedef char skin_name[64];

};