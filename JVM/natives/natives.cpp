#include "natives.h"
#include "../runtime/ClassMap.h"
#include "../runtime/Runtime.h"
#include "java/lang/Object.h"
#include "java/lang/System.h"
#include "java/io/PrintStream.h"


using namespace Java::Lang;

void initializeNatives(ClassMap* classMap)
{
	classMap->addClass(Java::Lang::Object::initialize());
	classMap->addClass(java::io::PrintStr::initialize(classMap));
	classMap->addClass(Java::Lang::System::initialize(classMap));
}

void initializeNatives(Runtime* runtime)
{
	initializeNatives(runtime->classTable);
}
