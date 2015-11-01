/**
 * 
 * NOTE :-> This is probably a rather bad way to go about the Model Objects, it shouldn't be bad for speed but more for expandability.
 *          It might be a good idea to split the ObjectModel class into different ones, if we have more model types.
 *
 * Also note that the MD2 loader is based off an artical by Brian Jorgensen, on Gamedev.net Props to him for helping the world learn!
 *
 */
class MD2Model : public Object {
	public:
		int MD2Load(char* file_name);
		void MD2FetchHeader(std::ifstream& f_MD2);
		void MD2ValidateHeader();
};