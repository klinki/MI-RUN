#include "JavaString.h"
#include "../runtime/Object.h"

namespace Java
{
	namespace Lang
	{
		namespace String
		{
			Class* initialize()
			{
				return NULL;
			}

			void String(::Object * obj, MethodFrame * frm)
			{}

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
