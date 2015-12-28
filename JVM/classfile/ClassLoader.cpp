#include "ClassLoader.h"
#include "../runtime/Runtime.h"

using namespace std;

ClassLoader::ClassLoader(Runtime * runtime)
{
	this->runtime = runtime;
	this->classMap = runtime->classTable;
	this->constantPool = new ConstantPool(1000);
	data = new char[1024];
}

Class* ClassLoader::load(const char * filename)
{
	if (myfile.is_open())
	{
		myfile.close();
	}

	myfile = ifstream(filename, ios::in | ios::binary);

	if (!myfile.is_open())
	{
		printf("cloud not open %s", filename);
		throw FileNotFoundException();
	}

	printf("loading class\n");
	if (reader(4))//read CAFEBABE
	{
		printf("ERROR IN READ FILE");
		//return 0;
	}


	loadMinVersion();
	loadMajVersion();
	loadConstPool();
	unsigned short access_flags = loadFlags();
	FLAG f = access_flags;
	Class *thisClass = new Class(f);
	thisClass->constantPool = this->constantPool;
	thisClass->constantPool->resolveStringRef();
	thisClass->constantPool->print();
	loadThisClass(thisClass);
	loadSuperClass(thisClass);
	loadInterfaces(thisClass);
	loadFields(thisClass);
	loadMethods(thisClass);
	loadAttributes(thisClass);

	myfile.close();
	this->resolvePool(thisClass);

	classMap->addClass(thisClass);
	printf("loading finnished\n");
	return thisClass;
}
int ClassLoader::loadMinVersion()
{
	if (reader(2))
	{
		printf("ERROR IN READ FILE");
		return -1;
	}

	int minor_version = (int)((unsigned char)data[0] * 256 + (unsigned char)data[1]);
	//printf("min_ver:%d\n", minor_version);
	return 0;
}
int ClassLoader::loadMajVersion()
{
	if (reader(2))
	{
		printf("ERROR IN READ FILE");
		return -1;
	}

	int major_version = (int)((unsigned char)data[0] * 256 + (unsigned char)data[1]);
	//printf("maj_ver:%d\n", major_version);
	return 0;
}
int ClassLoader::loadConstPool()
{
	if (reader(2))
	{
		printf("ERROR IN READ FILE");
		return -1;
	}
	int constant_pool_count = (int)((unsigned char)data[0] * 256 + (unsigned char)data[1]);
	//printf("constant_pool_count:%d\n", constant_pool_count);
	constantPool = new ConstantPool(constant_pool_count);

	for (int k = 1; k < constant_pool_count; k++)
	{
		//printf("tag:");
		if (reader(1))
		{
			printf("ERROR IN READ FILE");
			return -1;
		}

		int cpType = (int)((unsigned char)data[0]);
		//printf("entry:%d type:%d\n", k, cpType);
		switch (cpType)
		{

		case ConstantPoolTag::CONSTANT_Utf8://utf8
			if (reader(2))
			{
				printf("ERROR IN READ FILE");
				return -1;
			}
			else
			{


				int utflength = (int)((unsigned char)data[0] * 256 + (unsigned char)data[1]);

				if (reader(utflength))
				{
					printf("ERROR IN READ FILE");
					return -1;
				}



				//data[utflength] = '\0';


				constantPool->add(k, cpType, utflength, data);
			}
			break;
		case ConstantPoolTag::CONSTANT_Integer://integer
			if (reader(4))
			{
				printf("ERROR IN READ FILE");
				return -1;
			}

			constantPool->add(k, cpType, 4, data);
			break;
		case ConstantPoolTag::CONSTANT_Float://float

			if (reader(4))
			{
				printf("ERROR IN READ FILE");
				return -1;
			}

			constantPool->add(k, cpType, 4, data);
			break;
		case ConstantPoolTag::CONSTANT_Long://long

			if (reader(8))
			{
				printf("ERROR IN READ FILE");
				return -1;
			}

			constantPool->add(k++, cpType, 8, data);
			break;
		case ConstantPoolTag::CONSTANT_Double://double

			if (reader(8))
			{
				printf("ERROR IN READ FILE");
				return -1;
			}

			constantPool->add(k++, cpType, 8, data);
			break;
		case ConstantPoolTag::CONSTANT_Class://class

			if (reader(2))
			{
				printf("ERROR IN READ FILE");
				return -1;
			}

			constantPool->add(k, cpType, 2, data);
			break;
		case ConstantPoolTag::CONSTANT_String://string

			if (reader(2))
			{
				printf("ERROR IN READ FILE");
				return -1;
			}

			constantPool->add(k, cpType, 2, data);
			break;
		case ConstantPoolTag::CONSTANT_Fieldref://fieldref

			if (reader(4))
			{
				printf("ERROR IN READ FILE");
				return -1;
			}

			constantPool->add(k, cpType, 4, data);
			break;
		case ConstantPoolTag::CONSTANT_Methodref://methodref

			if (reader(4))
			{
				printf("ERROR IN READ FILE");
				return -1;
			}

			constantPool->add(k, cpType, 4, data);
			break;
		case ConstantPoolTag::CONSTANT_InterfaceMethodref://interfacemethodref

			if (reader(4))
			{
				printf("ERROR IN READ FILE");
				return -1;
			}

			constantPool->add(k, cpType, 4, data);
			break;
		case ConstantPoolTag::CONSTANT_NameAndType://nameandtype

			if (reader(4))
			{
				printf("ERROR IN READ FILE");
				return -1;
			}

			constantPool->add(k, cpType, 4, data);
			break;
		case ConstantPoolTag::CONSTANT_MethodHandle://_MethodHandle

			if (reader(3))
			{
				printf("ERROR IN READ FILE");
				return -1;
			}

			constantPool->add(k, cpType, 3, data);
			break;
		case ConstantPoolTag::CONSTANT_MethodType://_MethodType

			if (reader(2))
			{
				printf("ERROR IN READ FILE");
				return -1;
			}

			constantPool->add(k, cpType, 2, data);
			break;
		case ConstantPoolTag::CONSTANT_InvokeDynamic://InvokeDynamic

			if (reader(4))
			{
				printf("ERROR IN READ FILE");
				return -1;
			}

			constantPool->add(k, cpType, 4, data);
			break;

		default:
			printf("ERROR WRONG CPTYPE %d\n", cpType);

		}

	}


	return 0;
}
unsigned short ClassLoader::loadFlags()
{
	if (reader(2))
	{
		printf("ERROR IN READ FILE");
		return -1;
	}
	unsigned short access_flags = (unsigned short)((unsigned char)data[0] * 256 + (unsigned char)data[1]);
	//printf("access flags:%X\n", access_flags);
	return access_flags;
}
int ClassLoader::loadThisClass(Class * thisClass)
{

	if (reader(2))
	{
		printf("ERROR IN READ FILE");
		return -1;
	}
	int thisClassIndex = (int)((unsigned char)data[0] * 256 + (unsigned char)data[1]);
	thisClass->constantPool->setClassPtr(thisClassIndex, thisClass);
	printf("this class:%d\n", thisClassIndex);
	int nameptr = thisClass->constantPool->get(thisClassIndex)->classInfo.name_index;
	thisClass->fullyQualifiedName = Utf8String(thisClass->constantPool->get(nameptr)->utf8Info.bytes, thisClass->constantPool->get(nameptr)->utf8Info.length);

	return 0;
}
int ClassLoader::loadSuperClass(Class * thisClass)
{
	if (reader(2))
	{
		printf("ERROR IN READ FILE");
		return -1;
	}
	int superClassIndex = (int)((unsigned char)data[0] * 256 + (unsigned char)data[1]);


	return 0;
}
int ClassLoader::loadInterfaces(Class * thisClass) // TODO write interefaces, where? //references to const pool
{
	if (reader(2))
	{
		printf("ERROR IN READ FILE");
		return -1;
	}
	int interfaces_count = (int)((unsigned char)data[0] * 256 + (unsigned char)data[1]);

	//printf("interface count:%d\n", interfaces_count);
	for (int i = 0; i < interfaces_count; i++)
	{
		if (reader(2))
		{
			printf("ERROR IN READ FILE");
			return -1;
		}

	}

	return 0;
}
int ClassLoader::loadFields(Class * thisClass)
{
	//fields[fields_count]
	//{
	//u2 access_flags;
	//u2 name_index;
	//u2 descriptor_index;
	//u2 attributes_count;
	//attributes[attributes_count]
	//{
	//u2 attribute_name_index;
	//u4 attribute_length;
	//info[attribute_length]
	//{
	//[attribute data, see Table 9]
	//}
	//}
	//}

	if (reader(2))
	{
		printf("ERROR IN READ FILE");
		return -1;
	}
	size_t fields_count = (int)((unsigned char)data[0] * 256 + (unsigned char)data[1]);

	//printf("fields count:%d\n", fields_count);


	for (int i = 0; i < fields_count; i++)
	{
		unsigned short access_flags;
		int name_index;
		int descriptor_index;
		int attributes_count;
		if (reader(8))
		{
			printf("ERROR IN READ FILE");
			return -1;
		}
		access_flags = (unsigned short)((unsigned char)data[0] * 256 + (unsigned char)data[1]);
		name_index = (int)((unsigned char)data[2] * 256 + (unsigned char)data[3]);
		descriptor_index = (int)((unsigned char)data[4] * 256 + (unsigned char)data[5]);
		attributes_count = (int)((unsigned char)data[6] * 256 + (unsigned char)data[7]);


		//printf("access_flags:%d\n", access_flags);
		//printf("name_index:%d\n", name_index);
		//printf("descriptor_index:%d\n", descriptor_index);
		//printf("attributes count:%d\n", attributes_count);

		//create new field object
		Utf8String name(thisClass->constantPool->get(name_index)->utf8Info.bytes, (int)thisClass->constantPool->get(name_index)->utf8Info.length);
		Utf8String descriptor(thisClass->constantPool->get(descriptor_index)->utf8Info.bytes, (int)thisClass->constantPool->get(descriptor_index)->utf8Info.length);

		Field * field = new Field(access_flags, name, descriptor);
		thisClass->addField(field);

		// read attributes and do nothing
		for (int j = 0; j < attributes_count; j++)
		{
			int attribute_name_index;
			int attribute_length;
			if (reader(6))
			{
				printf("ERROR IN READ FILE");
				return -1;
			}

			attribute_name_index = (int)((unsigned char)data[0] * 256 + (unsigned char)data[1]);
			attribute_length = (int)((unsigned char)data[2] * 256 * 256 * 256 + (unsigned char)data[3] * 256 * 256 + (unsigned char)data[4] * 256 + (unsigned char)data[5]);


			//printf("attribute_name_index:%d\n", attribute_name_index);
			//printf("attribute lenght:%d\n", attribute_length);
			if (reader(attribute_length))
			{
				printf("ERROR IN READ FILE");
				return -1;
			}

		}
	}



	return 0;
}
int ClassLoader::loadMethods(Class * thisClass) {
	if (reader(2))
	{
		printf("ERROR IN READ FILE");
		return -1;
	}
	int methods_count = (int)((unsigned char)data[0] * 256 + (unsigned char)data[1]);
	printf("method count %d\n", methods_count);

	for (int i = 0; i < methods_count; i++)
	{
		int access_flags;
		int name_index;
		int descriptor_index;
		int attributes_count;
		if (reader(8))
		{
			printf("ERROR IN READ FILE");
			return -1;
		}
		access_flags = (int)((unsigned char)data[0] * 256 + (unsigned char)data[1]);
		name_index = (int)((unsigned char)data[2] * 256 + (unsigned char)data[3]);
		descriptor_index = (int)((unsigned char)data[4] * 256 + (unsigned char)data[5]);
		attributes_count = (int)((unsigned char)data[6] * 256 + (unsigned char)data[7]);


		// create new method onject
		Method * m = new Method(access_flags);
		m->name = Utf8String(thisClass->constantPool->get(name_index)->utf8Info.bytes, (int)thisClass->constantPool->get(name_index)->utf8Info.length);
		m->descriptor = Utf8String(thisClass->constantPool->get(descriptor_index)->utf8Info.bytes, (int)thisClass->constantPool->get(descriptor_index)->utf8Info.length);


		printf("method %d flags: %d\n", i, access_flags);
		printf("method %d name: %d\n", i, name_index);
		printf("method %d descriptor: %d\n", i, descriptor_index);
		printf("method %d att count: %d\n", i, attributes_count);
		for (int j = 0; j < attributes_count; j++)
		{
			int attribute_name_index;
			int attribute_length;
			if (reader(6))
			{
				printf("ERROR IN READ FILE");
				return -1;
			}

			attribute_name_index = (int)((unsigned char)data[0] * 256 + (unsigned char)data[1]);
			attribute_length = (int)((unsigned char)data[2] * 256 * 256 * 256 + (unsigned char)data[3] * 256 * 256 + (unsigned char)data[4] * 256 + (unsigned char)data[5]);
			printf("method %d name index: %d\n", j, attribute_name_index);
			printf("method %d att length: %d\n", j, attribute_length);

			if (reader(attribute_length))
			{
				printf("ERROR IN READ FILE");
				return -1;
			}

			unsigned char* n = thisClass->constantPool->get(attribute_name_index)->utf8Info.bytes;
			int n_length = (int)thisClass->constantPool->get(attribute_name_index)->utf8Info.length;
			printf("name %s %d\n", n, n_length);

			if (n_length == 4 && n[0] == 'C'&&n[1] == 'o'&&n[2] == 'd'&&n[3] == 'e') // zmenit na porovnani utf8
			{
				printf("method %d CODE:\n", j);
				int max_stack = (int)((unsigned char)data[0] * 256 + (unsigned char)data[1]);
				m->operandStackSize = max_stack;
				int max_variables = (int)((unsigned char)data[2] * 256 + (unsigned char)data[3]);
				m->localVariablesArraySize = max_variables;
				int code_length = (int)((unsigned char)data[4] * 256 * 256 * 256 + (unsigned char)data[5] * 256 * 256 + (unsigned char)data[6] * 256 + (unsigned char)data[7]);
				m->byteCodeLength = code_length;
				//unsigned char * code = new unsigned char[code_length];


				printf("method %d max stack: %d\n", j, max_stack);
				printf("method %d max var: %d\n", j, max_variables);
				printf("method %d code length: %d\n", j, code_length);

				m->byteCode = new Instruction[code_length];

				for (int i1 = 0; i1 < code_length; i1++)
				{
					m->byteCode[i1] = (unsigned char)(unsigned char)data[i1 + 8];

				}

				int exception_table_length = (int)((unsigned char)data[code_length + 8] * 256 + (unsigned char)data[code_length + 9]);
				printf("method %d exc table length: %d\n", j, exception_table_length);

				for (int i1 = 0; i1 < exception_table_length; i1++)
				{
					int start_pc = (int)((unsigned char)data[code_length + 10 + i1 * 8] * 256 + (unsigned char)data[code_length + 11 + i1 * 8]);
					int end_pc = (int)((unsigned char)data[code_length + 12 + i1 * 8] * 256 + (unsigned char)data[code_length + 13 + i1 * 8]);
					int handler_pc = (int)((unsigned char)data[code_length + 14 + i1 * 8] * 256 + (unsigned char)data[code_length + 15 + i1 * 8]);
					int catch_type = (int)((unsigned char)data[code_length + 16 + i1 * 8] * 256 + (unsigned char)data[code_length + 17 + i1 * 8]);

					printf("method %d ecx %d start pc: %d\n", j, i1, start_pc);
					printf("method %d ecx %d end pc: %d\n", j, i1, end_pc);
					printf("method %d ecx %d handler pc: %d\n", j, i1, handler_pc);
					printf("method %d ecx %d catch type: %d\n", j, i1, catch_type);

					int n_i = thisClass->constantPool->get(catch_type)->classInfo.name_index;

					Utf8String exc_name = Utf8String(thisClass->constantPool->get(n_i)->utf8Info.bytes, thisClass->constantPool->get(n_i)->utf8Info.length);
					m->exceptionTable.addException(exc_name, start_pc, end_pc, handler_pc, catch_type);
				}

				int code_attributes_count = (int)((unsigned char)data[code_length + 10 + exception_table_length * 8] * 256 + (unsigned char)data[code_length + 11 + exception_table_length * 8]);
				printf("method %d code att count: %d\n", j, code_attributes_count);

			}
			else if (n_length == 11 && n[0] == 'E' &&n[1] == 'x' &&n[2] == 'c' &&n[3] == 'e' &&n[4] == 'p' &&n[5] == 't' &&n[6] == 'i' &&n[7] == 'o' &&n[8] == 'n' &&n[9] == 's')// Exceptions
			{
				printf("method %d EXCEPTIONS:\n", j);

				int number_of_exceptions = (int)((unsigned char)data[0] * 256 + (unsigned char)data[1]);
				for (int k = 0; k < number_of_exceptions; k++)
				{
					int exception_index = (int)((unsigned char)data[2 + k * 2] * 256 + (unsigned char)data[3 + k * 2]);
					//add exception to exception table?
				}
			}
			//else if (n_length == 16 && n[0] == 'M' &&n[1] == 'e' &&n[2] == 't' &&n[3] == 'h' &&n[4] == 'o' &&n[5] == 'd' &&n[6] == 'P' &&n[7] == 'a' &&n[8] == 'r' &&n[9] == 'a'&&n[10] == 'm'&&n[11] == 'e'&&n[12] == 't'&&n[13] == 'e'&&n[14] == 'r'&&n[15] == 's')// MethodParameters
			else
			{
				printf("method %d OTHER : %s \n", j, n);

				//u2 attribute_name_index;
				//u4 attribute_length;
				//u1 parameters_count;
				//{   u2 name_index;
				//u2 access_flags;
				//} parameters[parameters_count];
			}
		}
		thisClass->methodArea.addMethod(m);
	}


	return 0;
}
int ClassLoader::loadAttributes(Class * thisClass)
{
	if (reader(2))
	{
		printf("ERROR IN READ FILE");
		return -1;
	}
	int attributes_count = (int)((unsigned char)data[0] * 256 + (unsigned char)data[1]);
	printf("attributes count:%d\n", attributes_count);

	//attributes[attributes_count]
	//attributes[attributes_count]
	//{
	//u2 attribute_name_index;
	//u4 attribute_length;
	//info[attribute_length]
	//{
	//[attribute data, see Table 16]
	//}
	//}
	for (int i = 0; i < attributes_count; i++)
	{
		int attribute_name_index;
		int attribute_length;
		if (reader(6))
		{
			printf("ERROR IN READ FILE");
			return -1;
		}

		attribute_name_index = (int)((unsigned char)data[0] * 256 + (unsigned char)data[1]);
		attribute_length = (int)((unsigned char)data[2] * 256 * 256 * 256 + (unsigned char)data[3] * 256 * 256 + (unsigned char)data[4] * 256 + (unsigned char)data[5]);

		printf("attribute_name_index:%d\n", attribute_name_index);
		printf("attribute lenght:%d\n", attribute_length);

		if (reader(attribute_length))
		{
			printf("ERROR IN READ FILE");
			return -1;
		}

	}

	return 0;
}

int ClassLoader::reader(int nob)
{
	if (myfile.is_open())
	{
		if (nob > 1024)
		{
			delete[] data;
			data = new char[nob];
		}
		myfile.read(data, nob);

		return 0;
	}
	else
	{
		throw FileNotFoundException();
		return -1;
	}

}
void ClassLoader::resolvePool(Class * thisClass)
{
	int constant_pool_size = thisClass->constantPool->GetSize();
	for (int i = 1; i < constant_pool_size; i++)
	{

		int item_tag = thisClass->constantPool->get(i)->tag;
		//printf("resolve pool %d %d\n",i,item_tag);
		switch (item_tag)
		{
		case  ConstantPoolTag::CONSTANT_Class: {

			if (thisClass->constantPool->get(i)->classInfo.classPtr == nullptr)
			{
				resolveClassPointer(thisClass, i);
			}

			break;}
		case  ConstantPoolTag::CONSTANT_Fieldref:
		{
			//classptr
			int class_index = thisClass->constantPool->get(i)->fieldInfo.class_index;
			if (thisClass->constantPool->get(class_index)->classInfo.classPtr == nullptr)
			{
				resolveClassPointer(thisClass, class_index);
			}

			Class * myClass = thisClass->constantPool->get(class_index)->classInfo.classPtr;
			thisClass->constantPool->setClassPtr(i, myClass);

			//field ptr
			//if (myClass != nullptr)
			//{
			int name_index = thisClass->constantPool->get(i)->fieldInfo.name_and_type_index;
			int descriptor_index = thisClass->constantPool->get(name_index)->nameAndTypeInfo.descriptor_index;
			name_index = thisClass->constantPool->get(name_index)->nameAndTypeInfo.name_index;
			Utf8String item_name = Utf8String(thisClass->constantPool->get(name_index)->utf8Info.bytes, thisClass->constantPool->get(name_index)->utf8Info.length);
			Utf8String item_descriptor = Utf8String(thisClass->constantPool->get(descriptor_index)->utf8Info.bytes, thisClass->constantPool->get(descriptor_index)->utf8Info.length);

			Field* field = myClass->getField(item_name, item_descriptor);
			thisClass->constantPool->setFieldPtr(i, field);
			//}
		}
		break;
		case  ConstantPoolTag::CONSTANT_Methodref: {
			//classptr
			int class_index = thisClass->constantPool->get(i)->methodInfo.class_index;
			if (thisClass->constantPool->get(class_index)->classInfo.classPtr == nullptr)
			{

				resolveClassPointer(thisClass, class_index);

			}
			Class * myClass = thisClass->constantPool->get(class_index)->classInfo.classPtr;
			thisClass->constantPool->setClassPtr(i, myClass);
			//merhod ptr


			int name_index = thisClass->constantPool->get(i)->methodInfo.name_and_type_index;
			int descriptor_index = thisClass->constantPool->get(name_index)->nameAndTypeInfo.descriptor_index;
			name_index = thisClass->constantPool->get(name_index)->nameAndTypeInfo.name_index;
			Utf8String item_name = Utf8String(thisClass->constantPool->get(name_index)->utf8Info.bytes, thisClass->constantPool->get(name_index)->utf8Info.length);
			Utf8String item_descriptor = Utf8String(thisClass->constantPool->get(descriptor_index)->utf8Info.bytes, thisClass->constantPool->get(descriptor_index)->utf8Info.length);

			if (thisClass->methodArea.getMethod(item_name, item_descriptor) != nullptr)
			{
				thisClass->constantPool->setMethodPtr(i, thisClass->methodArea.getMethod(item_name, item_descriptor));
			}
			else if (myClass != nullptr &&  myClass->methodArea.getMethod(item_name, item_descriptor) != nullptr)
			{
				thisClass->constantPool->setMethodPtr(i, myClass->methodArea.getMethod(item_name, item_descriptor));
			}


			break;}
		case  ConstantPoolTag::CONSTANT_InterfaceMethodref: {
			//classptr
			int class_index = thisClass->constantPool->get(i)->interfaceMethodInfo.class_index;
			if (thisClass->constantPool->get(class_index)->classInfo.classPtr == nullptr)
			{
				resolveClassPointer(thisClass, class_index);
			}
			Class * myClass = thisClass->constantPool->get(class_index)->classInfo.classPtr;
			thisClass->constantPool->setClassPtr(i, myClass);
			//method ptr
			//if (myClass != nullptr)
			//{
			int name_index = thisClass->constantPool->get(i)->interfaceMethodInfo.name_and_type_index;
			int descriptor_index = thisClass->constantPool->get(name_index)->nameAndTypeInfo.descriptor_index;
			name_index = thisClass->constantPool->get(name_index)->nameAndTypeInfo.name_index;
			Utf8String item_name = Utf8String(thisClass->constantPool->get(name_index)->utf8Info.bytes, thisClass->constantPool->get(name_index)->utf8Info.length);
			Utf8String item_descriptor = Utf8String(thisClass->constantPool->get(descriptor_index)->utf8Info.bytes, thisClass->constantPool->get(descriptor_index)->utf8Info.length);
			if (thisClass->methodArea.getMethod(item_name, item_descriptor) != nullptr)
			{
				thisClass->constantPool->setMethodPtr(i, thisClass->methodArea.getMethod(item_name, item_descriptor));
			}
			else if (myClass != nullptr &&  myClass->methodArea.getMethod(item_name, item_descriptor) != nullptr)
			{
				thisClass->constantPool->setMethodPtr(i, myClass->methodArea.getMethod(item_name, item_descriptor));
			}
			//}

			break;}
		case  ConstantPoolTag::CONSTANT_Double:
		case  ConstantPoolTag::CONSTANT_Long:
			i++;
			break;
		default:
			break;
		}
	}
	//printf("resolving finnished\n");
}
void ClassLoader::resolveClassPointer(Class * thisClass, int i)
{
	printf("resolve class pointer %d\n", i);
	int name_index = thisClass->constantPool->get(i)->classInfo.name_index;
	Utf8String item_name = Utf8String(thisClass->constantPool->get(name_index)->utf8Info.bytes, thisClass->constantPool->get(name_index)->utf8Info.length);

	Class* class_pointer = classMap->getClass(item_name);

	if (class_pointer == nullptr)
	{
		//reurzivne zavolej classloader pro tridu co nenasel

		unsigned char *a = thisClass->constantPool->get(name_index)->utf8Info.bytes;
		size_t alen = thisClass->constantPool->get(name_index)->utf8Info.length;
		char *r = new char[alen + 7];

		char ext[] = ".class";
		strcpy_s(r, alen + 7, (char*)a);
		strncpy_s(r + alen, alen + 7, ext, strlen(ext));

		this->load(r);

		class_pointer = classMap->getClass(item_name);

	}

	printf("set class ptr %d\n", i);
	thisClass->constantPool->setClassPtr(i, class_pointer);

}
ClassLoader::~ClassLoader()
{
	delete[] data;
}
