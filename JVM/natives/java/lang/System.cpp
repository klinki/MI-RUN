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

				Field* field = new Field((int)FieldAccessFlags::STATIC | (int)FieldAccessFlags::PUBLIC, Utf8String("out"), Utf8String("Ljava/io/PrintStream;"));
				system->addField(field);

				Field* errField = new Field((int)FieldAccessFlags::STATIC | (int)FieldAccessFlags::PUBLIC, Utf8String("err"), Utf8String("Ljava/io/PrintStream;"));
				system->addField(errField);

                byte* printStrMemory = runtime->heap->allocateOnSystemMemory(sizeof(java::io::PrintStream));
				java::io::PrintStream * out = new(printStrMemory) java::io::PrintStream(&std::cout);
				size_t outIndex = runtime->objectTable->insert(out);

                byte* errStrMemory = runtime->heap->allocateOnSystemMemory(sizeof(java::io::PrintStream));
				java::io::PrintStream * err = new(errStrMemory) java::io::PrintStream(&std::cerr);
				size_t errIndex = runtime->objectTable->insert(err);

				system->staticVariablesValues->set(field->fieldIndex, (word)makeReferenceAddress(outIndex));
				system->staticVariablesValues->set(errField->fieldIndex, (word)makeReferenceAddress(errIndex));

				return system;
			};
		}
	}
}
