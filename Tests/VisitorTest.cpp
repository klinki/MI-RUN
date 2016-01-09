#include "stdafx.h"
#include "CppUnitTest.h"
#include "../JVM/runtime/MethodArea.h"
#include "../JVM/runtime/ExecutionEngine.h"
#include "../JVM/runtime/TypeDescriptors.h"
#include "../JVM/gc/interfaces/ObjectVisitorInterface.h"

class TestVisitor : public ObjectVisitorInterface
{
public:
	bool hasBeenCalled = false;

	virtual void visit(ObjectHeader* header)
	{
	}

	virtual void visit(word address)
	{
	}

	virtual void visit(Object* object)
	{
		this->hasBeenCalled = true;
	}

	virtual void visit(size_t address)
	{
		this->hasBeenCalled = true;
	}

	virtual void visit(MethodFrame* frame)
	{
	}
};

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(VisitorTest)
	{
	public:
		TEST_METHOD(testVisitSimpleArray)
		{
			Object * object = new Object();
			ArrayObject<int> * arrayObject = new ArrayObject<int>(10, 0, NULL, NULL);
			TestVisitor * visitor = new TestVisitor();
			arrayObject->accept(visitor);

			Assert::AreEqual(false, visitor->hasBeenCalled);
		}

		TEST_METHOD(testVisitArrayAsVisitableInterface)
		{
			ArrayObject<int> * arrayObject = new ArrayObject<int>(10, 0, NULL, NULL);
			VisitableInterface * visitable = (VisitableInterface*)arrayObject;
			TestVisitor * visitor = new TestVisitor();
			visitable->accept(visitor);

			Assert::AreEqual(false, visitor->hasBeenCalled);
		}

		TEST_METHOD(testVisitArrayOfObjects)
		{
			ArrayObject<Object*> * arrayObject = new ArrayObject<Object*>(10, 0, NULL, NULL);
			TestVisitor * visitor = new TestVisitor();
			arrayObject->accept(visitor);

			Assert::AreEqual(true, visitor->hasBeenCalled);
		}


		TEST_METHOD(testVisitArrayOfObjectsAsVisitableInterface)
		{
			ArrayObject<Object*> * arrayObject = new ArrayObject<Object*>(10, 0, NULL, NULL);
			VisitableInterface * visitable = (VisitableInterface*)arrayObject;
			TestVisitor * visitor = new TestVisitor();
			visitable->accept(visitor);

			Assert::AreEqual(true, visitor->hasBeenCalled);
		}

		TEST_METHOD(testVisitObject)
		{}
	};
}
