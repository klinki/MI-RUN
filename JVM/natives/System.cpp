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

				Field* field = new Field((int)FieldAccessFlags::STATIC | (int)FieldAccessFlags::PUBLIC, Utf8String("out"), Utf8String("Ljava/io/PrintStream;"));
				field->value[0] = (word)out;

				system->staticVariablesMap.add(field);

				return system;
			}
		}
	}
}
