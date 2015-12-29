#include "Exception.h"
#include "Throwable.h"

using namespace java::lang::Throwable;

namespace java
{
	namespace lang
	{
		namespace Exception
		{
			Class* initialize(ClassMap * classMap, const char* name, const char* parent)
			{
				Class* newClass = java::lang::Throwable::initialize(classMap);
				newClass->parentClass = classMap->getClass(parent);
				newClass->fullyQualifiedName = Utf8String(name);
				return newClass;
			}
		}
	}
}
