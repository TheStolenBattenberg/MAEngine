typedef unsigned int uint;

enum VariantTypes {
	VariantTypeNull,
	VariantTypeInteger,
	VariantTypeUnsignedInteger,
	VariantTypeFloat,
	VariantTypeDouble,
	VariantTypePointer
};

class Variant {
public:
	Variant();
	Variant(int val);
	Variant(uint val);
	Variant(float val);
	Variant(double val);
	Variant(void* val);

	VariantTypes getType();

	void setNull();

	void set(int val);
	void set(uint val);
	void set(float val);
	void set(double val);
	void set(void* val);

	int    getInteger();
	uint   getUnsignedInteger();
	float  getFloat();
	double getDouble();
	void*  getPointer();

private:
	VariantTypes type;

	union {
		int    Integer;
		uint   UnsignedInteger;
		float  Float;
		double Double;
		void*  Pointer;
	} value;
};