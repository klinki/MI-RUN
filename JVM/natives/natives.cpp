#include "natives.h"
#include "../runtime/ClassMap.h"
#include "java/lang/Object.h"
#include "java/lang/System.h"
#include "java/io/PrintStream.h"

using namespace Java::Lang;

void InitializeNatives(ClassMap* classMap)
{
	classMap->addClass(Java::Lang::Object::initialize());
	classMap->addClass(PrintStr::initialize(classMap));
	classMap->addClass(Java::Lang::System::initialize(classMap));

}
