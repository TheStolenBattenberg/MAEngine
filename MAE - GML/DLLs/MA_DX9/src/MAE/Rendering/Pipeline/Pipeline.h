#pragma once

#include <MAE/Core/RefCounted.h>
#include <MAE/Core/Error.h>

class Pipeline: RefCounted {
public:
	enum PipelineMode: int {
		PipelineForward  = 0,
		PipelineDeffered = 1,
		PipelineCustom   = 2
	};

	virtual uint release() = 0;

	virtual ErrorCode setMode(PipelineMode mode) = 0;
};
