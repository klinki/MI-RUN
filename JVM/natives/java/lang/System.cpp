#include "System.h"
#include "../../Declarations.h"
#include "../../includes.h"
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
				system->staticVariablesValues = new LocalVariablesArray(3);

				Field* field = new Field((int)FieldAccessFlags::STATIC | (int)FieldAccessFlags::PUBLIC, Utf8String("out"), Utf8String("Ljava/io/PrintStream;"));
				system->addField(field);

				java::io::PrintStream * out = new java::io::PrintStream(&std::cout);
				system->staticVariablesValues->set(field->fieldIndex, (word)out);

				return system;
			}
		}
	}
}
