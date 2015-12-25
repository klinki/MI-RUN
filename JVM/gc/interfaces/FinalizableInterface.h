#pragma once
class Method;

class FinalizableInterface
{
public:
	virtual ~FinalizableInterface() {}
	virtual bool requiresFinalization() = 0;
	virtual Method* getFinalizationMethod()
	{
		return nullptr;
	}
};
