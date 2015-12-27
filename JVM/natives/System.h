#pragma once
#include "../runtime/Class.h"

class ClassMap;

namespace Java
{
	namespace Lang
	{
		namespace System
		{
			Class* initialize(ClassMap* classMap);
		}
	}
}
