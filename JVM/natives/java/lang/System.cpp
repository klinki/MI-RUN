#include "System.h"
#include "../../../runtime/Field.h"
#include "../../../runtime/ClassMap.h"
#include "../io/PrintStream.h"

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

				system->staticVariablesValues = new LocalVariablesArray(3);
				(*system->staticVariablesValues)[0] = (word)out;

				Field* field = new Field((int)FieldAccessFlags::STATIC | (int)FieldAccessFlags::PUBLIC, Utf8String("out"), Utf8String("Ljava/io/PrintStream;"));
				field->fieldIndex = 0;

				system->fieldsMap.add(field);

				return system;
			}
		}
	}
}
