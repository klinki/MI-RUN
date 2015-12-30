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
			Class* initialize(Runtime * runtime)
			{
				ClassMap * map = runtime->classTable;
				Class* system = new Class(NULL);
				system->fullyQualifiedName = "java/lang/System";
				system->parentClass = map->getClass("java/lang/Object");
				system->staticVariablesValues = new LocalVariablesArray(3);

				byte* fieldMemory = runtime->heap->allocateOnSystemMemory(Field::getMemorySize());
				Field* field = new(fieldMemory) Field((int)FieldAccessFlags::STATIC | (int)FieldAccessFlags::PUBLIC, Utf8String("out"), Utf8String("Ljava/io/PrintStream;"));
				system->addField(field);

				byte* errFieldMemory = runtime->heap->allocateOnSystemMemory(Field::getMemorySize());
				Field* errField = new(errFieldMemory) Field((int)FieldAccessFlags::STATIC | (int)FieldAccessFlags::PUBLIC, Utf8String("err"), Utf8String("Ljava/io/PrintStream;"));
				system->addField(errField);

				java::io::PrintStream * out = new java::io::PrintStream(&std::cout);
				size_t outIndex = runtime->objectTable->insert(out);

				java::io::PrintStream * err = new java::io::PrintStream(&std::cerr);
				size_t errIndex = runtime->objectTable->insert(err);

				system->staticVariablesValues->set(field->fieldIndex, (word)makeReferenceAddress(outIndex));
				system->staticVariablesValues->set(errField->fieldIndex, (word)makeReferenceAddress(errIndex));

				return system;
			};
		}
	}
}
