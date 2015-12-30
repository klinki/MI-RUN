#include "natives.h"
#include "../runtime/ClassMap.h"
#include "../runtime/Runtime.h"
#include "java/lang/Object.h"
#include "java/lang/System.h"
#include "java/lang/String.h"
#include "java/lang/StringBuilder.h"
#include "java/lang/Throwable.h"
#include "java/lang/Exception.h"
#include "java/io/PrintStream.h"

using namespace java::lang;

void initializeNatives(Runtime* runtime, ClassMap* classMap)
{
	classMap->addClass(java::lang::Object::initialize());
	classMap->addClass(java::io::PrintStr::initialize(classMap));
	classMap->addClass(java::lang::System::initialize(runtime));
	classMap->addClass(java::lang::StrBuilder::initialize(classMap));
	classMap->addClass(java::lang::String::initialize(classMap));
	classMap->addClass(java::lang::Throwable::initialize(classMap));
	
	classMap->addClass(java::lang::Exception::initialize(classMap, "java/lang/Exception", "java/lang/Throwable"));
	classMap->addClass(java::lang::Exception::initialize(classMap, "java/lang/CloneNotSupportedException"));
	classMap->addClass(java::lang::Exception::initialize(classMap, "java/lang/RuntimeException"));

	classMap->addClass(java::lang::Exception::initialize(classMap, "java/lang/NullPointerException", "java/lang/RuntimeException"));
	classMap->addClass(java::lang::Exception::initialize(classMap, "java/lang/ArrayIndexOutOfBoundsException", "java/lang/RuntimeException"));
	classMap->addClass(java::lang::Exception::initialize(classMap, "java/lang/ArithmeticException", "java/lang/RuntimeException"));
	classMap->addClass(java::lang::Exception::initialize(classMap, "java/lang/NegativeArraySizeException", "java/lang/RuntimeException"));
	classMap->addClass(java::lang::Exception::initialize(classMap, "java/lang/ArrayStoreException", "java/lang/RuntimeException"));
	classMap->addClass(java::lang::Exception::initialize(classMap, "java/lang/ClassCastException", "java/lang/RuntimeException"));

	classMap->addClass(java::lang::Exception::initialize(classMap, "java/lang/Error", "java/lang/Throwable"));
	classMap->addClass(java::lang::Exception::initialize(classMap, "java/lang/AbstractMethodError", "java/lang/Error"));
	classMap->addClass(java::lang::Exception::initialize(classMap, "java/lang/IncompatibleClassChangeError", "java/lang/Error"));
	classMap->addClass(java::lang::Exception::initialize(classMap, "java/lang/NoSuchMethodError", "java/lang/Error"));
	classMap->addClass(java::lang::Exception::initialize(classMap, "java/lang/IllegalAccessError", "java/lang/Error"));
	classMap->addClass(java::lang::Exception::initialize(classMap, "java/lang/UnsatisfiedLinkError", "java/lang/Error"));
}

void initializeNatives(Runtime* runtime)
{
	initializeNatives(runtime, runtime->classTable);
}
