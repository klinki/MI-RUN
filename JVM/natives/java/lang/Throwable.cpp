#include "Throwable.h"


namespace java
{
	namespace lang
	{
		namespace Throwable
		{
			Throwable::Throwable(Class* classPtr) : Object(2, classPtr, (byte*)(&this->callStackIndex +1))
			{
			}

			Throwable::~Throwable()
			{
			}

			void Throwable::printStackTrace()
			{
				this->printStackTrace(std::cerr);
			}

			void Throwable::printStackTrace(std::ostream & os)
			{
				os << this->objectClass->fullyQualifiedName.toAsciiString() << " stack trace: " << std::endl;

				for (int i = 0; i < this->callStackIndex; i++)
				{
					os  << this->callStack[i]->classPtr->fullyQualifiedName.toAsciiString() 
						<< "." 
						<< this->callStack[i]->name.toAsciiString() 
						<< this->callStack[i]->descriptor.toAsciiString() 
						<< std::endl;
				}
			}

			void Throwable::addStackTrace(Method * method)
			{
				if (this->callStackIndex < this->callStackSize)
				{
					this->callStack[this->callStackIndex++] = method;
				}
			}

			Class* initialize(ClassMap* classMap)
			{
				Class * newClass = new Class(NULL);
				newClass->classLoader = NULL;
				newClass->parentClass = classMap->getClass("java/lang/Object");
				newClass->fullyQualifiedName = Utf8String("java/lang/Throwable");
				newClass->countNonStaticFields = 2;

				newClass->addField(new Field((int)FieldAccessFlags::PROTECTED, "message", "Ljava/lang/String;"));
				newClass->addField(new Field((int)FieldAccessFlags::PROTECTED, "throwable", "Ljava/lang/Throwable;"));

				newClass->addMethod(getNativeMethod("<init>", "()V", &init));
				newClass->addMethod(getNativeMethod("<init>", "(Ljava/lang/String;)V", &initWithMessage));
				newClass->addMethod(getNativeMethod("<init>", "(Ljava/lang/String;Ljava/lang/Throwable;)V", &initWithMessageAndThrowable));
				newClass->addMethod(getNativeMethod("printStackTrace", "()V", &printStackTrace));
				newClass->addMethod(getNativeMethod("getMessage", "()Ljava/lang/String;", &getMessage));
				newClass->addMethod(getNativeMethod("getCause", "()Ljava/lang/Throwable;", &getCause));

				return newClass;
			}

			Throwable* createInstance(::Object * object, ExecutionEngine * engine)
			{
				// pointer is not object, but ref. to class
				size_t index = engine->getCurrentMethodFrame()->operandStack->popReference();
				Class* classPtr = (Class*)engine->objectTable->get(index);

				byte* memory = engine->heap->allocate(Throwable::getMemorySize());
				Throwable* throwable = new(memory) Throwable(classPtr);

				engine->objectTable->updateAddress(index, throwable);

				return throwable;
			}

			NATIVE_METHOD_HEADER(init)
			{				
				createInstance(object, engine);
			}

			NATIVE_METHOD_HEADER(initWithMessage)
			{
				size_t stringIndex = engine->getCurrentMethodFrame()->operandStack->pop();
				Throwable* throwable = createInstance(object, engine);

				throwable->fields->set(0, stringIndex);
			}

			NATIVE_METHOD_HEADER(initWithMessageAndThrowable)
			{
				size_t throwableIndex = engine->getCurrentMethodFrame()->operandStack->pop();
				size_t stringIndex = engine->getCurrentMethodFrame()->operandStack->pop();

				Throwable* throwable = createInstance(object, engine);
				throwable->fields->set(0, stringIndex);
				throwable->fields->set(1, throwableIndex);
			}

			NATIVE_METHOD_HEADER(printStackTrace)
			{
				Throwable* throwable = (Throwable*)engine->objectTable->get(engine->getCurrentMethodFrame()->operandStack->popReference());
				throwable->printStackTrace();
			}

			NATIVE_METHOD_HEADER(getMessage)
			{
				Throwable* throwable = (Throwable*)engine->objectTable->get(engine->getCurrentMethodFrame()->operandStack->popReference());
				engine->getCurrentMethodFrame()->operandStack->push(throwable->fields->get(0));
			}

			NATIVE_METHOD_HEADER(getCause)
			{
				Throwable* throwable = (Throwable*)engine->objectTable->get(engine->getCurrentMethodFrame()->operandStack->popReference());
				engine->getCurrentMethodFrame()->operandStack->push(throwable->fields->get(1));
			}
		}
	}
}
