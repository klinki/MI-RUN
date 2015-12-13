#include "natives.h"
#include "JavaObject.h"
#include "../runtime/ClassMap.h"
using namespace Java::Lang;

void InitializeNatives(ClassMap* classMap)
{
	classMap->addClass(Java::Lang::Object::initialize());


}
