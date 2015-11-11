#include "../types/types.h"
namespace Instructions
{
	namespace Arithmetic
	{
		inline JavaInt add(JavaInt a, JavaInt b) { return JavaInt(a.intValue + b.intValue); };
		inline JavaLong add(JavaLong a, JavaLong b) { return JavaLong(a.intValue + b.intValue); };
		inline JavaFloat add(JavaFloat a, JavaFloat b) { return JavaFloat(a.intValue + b.intValue); };
		inline JavaDouble add(JavaDouble a, JavaDouble b) { return JavaDouble(a.intValue + b.intValue); };
	}
}
