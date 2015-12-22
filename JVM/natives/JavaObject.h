#pragma once
#include "JavaString.h"
#include "../runtime/Class.h"
#include "../exceptions/RuntimeExceptions.h"
#include "../runtime/MethodFrame.h"
#include "../types/Descriptors.h"

namespace Java
{
	namespace Lang
	{
		namespace Object
		{
			Class* initialize();

			void clone();

			void equals(::Object *, MethodFrame *);
			void hashCode(::Object *, MethodFrame *);

			void finalize(::Object *, MethodFrame *);
			
			void getClass(::Object *, MethodFrame *);

			
			void notify(::Object *, MethodFrame *);
			void notifyAll(::Object *, MethodFrame *);
			
			void toString(::Object *, MethodFrame *);

			void waitEmpty(::Object* object, MethodFrame * frame);
			void waitTimeout(::Object* object, MethodFrame * frame);
			void waitTimeoutNanos(::Object* object, MethodFrame * frame);
		}
	}
}
