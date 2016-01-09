#include <iostream>
#include "OutputStream.h"
#include "../lang/String.h"

namespace java
{
	namespace io
	{
		namespace OutputStream
		{
			static Class* staticClassPtr = nullptr;

			Class* initialize(ClassMap* classMap)
			{
				if (staticClassPtr != nullptr)
				{
					return staticClassPtr;
				}

				Class * objectClass = classMap->getClass("java/lang/Object");
				Class * aClass = new Class(0);
				aClass->parentClass = objectClass;
				aClass->classLoader = NULL;
				aClass->fullyQualifiedName = "java/io/OutputStream";
				
				return aClass;
			};
		}
	}
}
