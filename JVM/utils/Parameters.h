#pragma once
struct Parameters
{
	bool PrintExecutedInstructions = false;
	size_t EdenSpaceSize = 5 * 1024 * 1024; // 5 MB
	size_t PermSpaceSize = 50 * 1024 * 1024; // 50 MB


	size_t MinEdenSpaceSize = 100 * 1024;
	size_t MinPermSpaceSize = 1 * 1024 * 1024;
};
