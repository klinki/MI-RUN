#pragma once
#include "../runtime/Class.h"

namespace Java
{
	namespace Lang
	{
		namespace String
		{
			Class* initialize();

			void String();
			void StringFromCharArray();
			void StringCopy();
			void length();
			void equals();
			void format();
			void hashCode();
			void toString();
			void clone();
		}
	}
}
