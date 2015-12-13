#include "System.h"
#include "../runtime/Field.h"

namespace Java
{
	namespace Lang
	{
		namespace System
		{
			Class* initialize()
			{
				Class* system = new Class(NULL);

				system->staticVariables = new LocalVariablesArray(3);
				return system;
			}
		}
	}
}
