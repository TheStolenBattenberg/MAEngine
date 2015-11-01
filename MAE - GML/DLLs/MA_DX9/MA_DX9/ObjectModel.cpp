/**
*
* NOTE :-> See note inside ObjectModel.h.
* 
*/
#include "dllbackend.h"

int MD2Model::MD2Load(char* file_md2)
{
	try {
		std::ifstream f_MD2;
		f_MD2.open(file_md2, std::ios::in | std::ios::binary); 
		
		if (!f_MD2.is_open())
		{ 
			throw Exception("Failed to open MD2 file."); 
		}

		try {
			MD2FetchHeader(f_MD2);
			MD2ValidateHeader();

		}
		catch (Exception& e)
		{
			MessageBoxA(NULL, e.exception, "MD2 Error!", MB_ICONERROR);
		}
	}
	catch (Exception& e)
	{
		MessageBoxA(NULL, e.exception, "MD2 Error!", MB_ICONERROR);
	}
	return 0;
}

void MD2Model::MD2FetchHeader(std::ifstream& f_MD2)
{

}

void MD2Model::MD2ValidateHeader()
{

}