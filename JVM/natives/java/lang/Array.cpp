#include "Array.h"
#include "../../includes.h"

namespace java
{
	namespace lang
	{
		namespace Array
		{
			static Class* staticClassPtr = NULL;

			Class* initialize(ClassMap * classMap)
			{
				if (staticClassPtr != NULL)
				{
					return staticClassPtr;
				}

				Class * newClass = new Class(NULL);

				staticClassPtr = newClass;

				newClass->classLoader = NULL;
				newClass->parentClass = classMap->getClass("java/lang/Object");
				newClass->fullyQualifiedName = Utf8String("java/lang/Array");

				return newClass;
			}
		}
	}
}
