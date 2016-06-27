#pragma once

class Releasable {
public:
	static void operator delete(void* ptr) {
		((Releasable*) ptr)->release();
	}

	virtual void release() = 0;
};
