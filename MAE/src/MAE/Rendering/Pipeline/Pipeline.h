#pragma once

#include <MAE/Core/Releasable.h>
#include <MAE/Core/Error.h>

class Pipeline: public Releasble {
public:
	enum PipelineMode: int {
		PipelineForward  = 0,
		PipelineDeffered = 1,
		PipelineCustom   = 2
	};

	virtual void release() = 0;

	virtual ErrorCode setMode(PipelineMode mode) = 0;
};
