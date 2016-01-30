#pragma once

#include "RefCounted.h"
#include "Error.h"

class Pipeline: RefCounted {
public:
	enum PipelineMode: int {
		PipelineForward  = 0,
		PipelineDeffered = 1,
		PipelineCustom   = 2
	};

	virtual uint release() = 0;

	virtual ErrorCode setMode(PipelineMode mode) = 0;
	virtual ErrorCode render(class Scene* scene) = 0;
};
