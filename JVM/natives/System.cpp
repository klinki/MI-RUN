#include "System.h"
#include "../runtime/Field.h"
#include "../natives/PrintStream.h"
#include "../runtime//ClassMap.h"

namespace Java
{
	namespace Lang
	{
		namespace System
		{
			Class* initialize(ClassMap * map)
			{
				Class* system = new Class(NULL);
				system->fullyQualifiedName = "java/lang/System";
				system->parentClass = map->getClass("java/lang/Object");

				PrintStream * out = new PrintStream(&std::cout);

				system->staticVariables = new LocalVariablesArray(3);
				(*system->staticVariables)[0] = (word)out;

				return system;
			}
		}
	}
}
