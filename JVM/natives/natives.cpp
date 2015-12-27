#include "natives.h"
#include "JavaObject.h"
#include "../runtime/ClassMap.h"
#include "System.h"
#include "PrintStream.h"

using namespace Java::Lang;

void InitializeNatives(ClassMap* classMap)
{
	classMap->addClass(Java::Lang::Object::initialize());
	classMap->addClass(PrintStr::initialize(classMap));
	classMap->addClass(Java::Lang::System::initialize(classMap));

}
