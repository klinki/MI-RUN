#include <string>
#include <cstring>
#include "ClassLoader.h"
#include "../runtime/Runtime.h"
#include "../natives/java/lang/String.h"
#include "../exceptions/RuntimeExceptions.h"

using namespace std;
using namespace Errors;

ClassLoader::ClassLoader(Runtime * runtime)
{
	this->runtime = runtime;
	this->classMap = runtime->classTable;
	data = new char[1024];
}
ClassLoader::~ClassLoader()
{
    delete[] this->data;
    delete[] this->defaultNamespace;
}
        
void ClassLoader::init(const char * activeFile)
{
	std::string activeFileString(activeFile);
	int lastDelimiter = activeFileString.find_last_of('/');
	std::string directory = activeFileString.substr(0, lastDelimiter);
	this->currentDir = directory.c_str();
}

std::string ClassLoader::getNamespaceFromClass(const char* className)
{
	std::string currentClassName = std::string(className);
	int lastDelimiter = currentClassName.find_last_of('/');
	std::string directory = currentClassName.substr(0, lastDelimiter);
	std::string namesp = directory;

	if (this->defaultNamespace != NULL) {
	    delete[] this->defaultNamespace;
	}
	this->defaultNamespace = new char[directory.length() + 1];
	memcpy(this->defaultNamespace, directory.c_str(), directory.length() + 1);

	return namesp;
}

Class* ClassLoader::load(const char * filename)
{
	ifstream* file = new ifstream(filename, ios::in | ios::binary);

	this->myfile = file;

	if (!myfile->is_open())
	{
		string message = std::string("Could not open: ") + std::string(filename);
		throw NoClassDefFoundError(message.c_str());
	}

	DEBUG_PRINT("loading class\n");


	reader(4);//read CAFEBABE

	loadMinVersion();
	loadMajVersion();
	loadConstPool();
	unsigned short access_flags = loadFlags();
	FLAG f = access_flags;
	Class *thisClass = new Class(f);
	thisClass->constantPool = this->constantPool;
	//thisClass->constantPool->resolveStringRef();
	
	DEBUG_BLOCK(thisClass->constantPool->print());

	thisClass->constantPool->resolveStringRef();
	int nameptr = loadThisClass(thisClass);

	if (this->defaultNamespace == NULL)
	{
		this->getNamespaceFromClass(thisClass->fullyQualifiedName.toAsciiString());
		//this->rootNamespace = new NamespaceStructure(thisClass->fullyQualifiedName.toAsciiString());
		//this->rootNamespace->directory = this->currentDir;
	}

	classMap->addClass(thisClass);

	int super = loadSuperClass(thisClass);
	loadInterfaces(thisClass);
	loadFields(thisClass);
	loadMethods(thisClass);
	loadAttributes(thisClass);

	myfile->close();
	this->resolvePool(thisClass,nameptr);
	thisClass->setParent(thisClass->constantPool->get(super)->classInfo.classPtr);
	
	DEBUG_PRINT("loading finnished\n");

	file->close();
	delete file;

	return thisClass;
}
int ClassLoader::loadMinVersion()
{
	reader(2);

	int minor_version = (int)((unsigned char)data[0] * 256 + (unsigned char)data[1]);
	//DEBUG_PRINT("min_ver:%d\n", minor_version);
	return 0;
}
int ClassLoader::loadMajVersion()
{
	reader(2);

	int major_version = (int)((unsigned char)data[0] * 256 + (unsigned char)data[1]);
	//DEBUG_PRINT("maj_ver:%d\n", major_version);
	return 0;
}
int ClassLoader::loadConstPool()
{
	reader(2);
	int constant_pool_count = (int)((unsigned char)data[0] * 256 + (unsigned char)data[1]);
	//DEBUG_PRINT("constant_pool_count:%d\n", constant_pool_count);
	constantPool = new ConstantPool(constant_pool_count, this->runtime);

	for (int k = 1; k < constant_pool_count; k++)
	{
		//DEBUG_PRINT("tag:");
		reader(1);
	
		int cpType = (int)((unsigned char)data[0]);
		//DEBUG_PRINT("entry:%d type:%d\n", k, cpType);
		switch (cpType)
		{

		case ConstantPoolTag::CONSTANT_Utf8:
		{			
			reader(2);
			int utflength = (int)((unsigned char)data[0] * 256 + (unsigned char)data[1]);
			reader(utflength);
			constantPool->add(k, cpType, utflength, data);
		}
		break;
		case ConstantPoolTag::CONSTANT_Integer://integer
			reader(4);
			constantPool->add(k, cpType, 4, data);
			break;
		case ConstantPoolTag::CONSTANT_Float://float
			reader(4);
			constantPool->add(k, cpType, 4, data);
			break;
		case ConstantPoolTag::CONSTANT_Long://long
			reader(8);	
			constantPool->add(k++, cpType, 8, data);
			break;
		case ConstantPoolTag::CONSTANT_Double://double
			reader(8);
			constantPool->add(k++, cpType, 8, data);
			break;
		case ConstantPoolTag::CONSTANT_Class://class
			reader(2);
			constantPool->add(k, cpType, 2, data);
			break;
		case ConstantPoolTag::CONSTANT_String://string
			{
				reader(2);
				unsigned short tag = (unsigned short)((unsigned char)data[0] * 256 + (unsigned char)data[1]);
				ConstantPoolItem spi(ConstantPoolTag::CONSTANT_String);
				spi.stringInfo = CONSTANT_String_info(tag);
				constantPool->add(k, &spi);
			}
			break;
		case ConstantPoolTag::CONSTANT_Fieldref://fieldref
			reader(4);
			constantPool->add(k, cpType, 4, data);
			break;
		case ConstantPoolTag::CONSTANT_Methodref://methodref
			reader(4);
			constantPool->add(k, cpType, 4, data);
			break;
		case ConstantPoolTag::CONSTANT_InterfaceMethodref://interfacemethodref
			reader(4);
			constantPool->add(k, cpType, 4, data);
			break;
		case ConstantPoolTag::CONSTANT_NameAndType://nameandtype
			reader(4);
			constantPool->add(k, cpType, 4, data);
			break;
		case ConstantPoolTag::CONSTANT_MethodHandle://_MethodHandle
			reader(3);
			constantPool->add(k, cpType, 3, data);
			break;
		case ConstantPoolTag::CONSTANT_MethodType://_MethodType
			reader(2);
			constantPool->add(k, cpType, 2, data);
			break;
		case ConstantPoolTag::CONSTANT_InvokeDynamic://InvokeDynamic
			reader(4);
			constantPool->add(k, cpType, 4, data);
			break;
		default:
			DEBUG_PRINT("ERROR WRONG CPTYPE %d\n", cpType);
		}
	}


	return 0;
}

unsigned short ClassLoader::loadFlags()
{
	reader(2);
	unsigned short access_flags = (unsigned short)((unsigned char)data[0] * 256 + (unsigned char)data[1]);
	//DEBUG_PRINT("access flags:%X\n", access_flags);
	return access_flags;
}

int ClassLoader::loadThisClass(Class * thisClass)
{

	reader(2);
	int thisClassIndex = (int)((unsigned char)data[0] * 256 + (unsigned char)data[1]);
	thisClass->constantPool->setClassPtr(thisClassIndex, thisClass);

	DEBUG_PRINT("this class:%d\n", thisClassIndex);


	int nameptr = thisClass->constantPool->get(thisClassIndex)->classInfo.name_index;
	thisClass->fullyQualifiedName = Utf8String(thisClass->constantPool->get(nameptr)->utf8Info.bytes, thisClass->constantPool->get(nameptr)->utf8Info.length);

	return nameptr;
}

int ClassLoader::loadSuperClass(Class * thisClass)
{
	reader(2);
	int superClassIndex = (int)((unsigned char)data[0] * 256 + (unsigned char)data[1]);
	//DEBUG_PRINT("super: %d\n",superClassIndex);

	return superClassIndex;
}

int ClassLoader::loadInterfaces(Class * thisClass) // TODO write interefaces, where? //references to const pool
{
	reader(2);
	int interfaces_count = (int)((unsigned char)data[0] * 256 + (unsigned char)data[1]);

	//DEBUG_PRINT("interface count:%d\n", interfaces_count);
	for (int i = 0; i < interfaces_count; i++)
	{
		reader(2);
	}

	return 0;
}

int ClassLoader::loadFields(Class * thisClass)
{
	reader(2);
	size_t fields_count = (int)((unsigned char)data[0] * 256 + (unsigned char)data[1]);

	//DEBUG_PRINT("fields count:%d\n", fields_count);

	thisClass->staticVariablesValues = new LocalVariablesArray(fields_count);

	for (int i = 0; i < fields_count; i++)
	{
		unsigned short access_flags;
		int name_index;
		int descriptor_index;
		int attributes_count;
		reader(8);
			access_flags = (unsigned short)((unsigned char)data[0] * 256 + (unsigned char)data[1]);
		name_index = (int)((unsigned char)data[2] * 256 + (unsigned char)data[3]);
		descriptor_index = (int)((unsigned char)data[4] * 256 + (unsigned char)data[5]);
		attributes_count = (int)((unsigned char)data[6] * 256 + (unsigned char)data[7]);


		//DEBUG_PRINT("access_flags:%d\n", access_flags);
		//DEBUG_PRINT("name_index:%d\n", name_index);
		//DEBUG_PRINT("descriptor_index:%d\n", descriptor_index);
		//DEBUG_PRINT("attributes count:%d\n", attributes_count);

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
			reader(6);
		
			attribute_name_index = (int)((unsigned char)data[0] * 256 + (unsigned char)data[1]);
			attribute_length = (int)((unsigned char)data[2] * 256 * 256 * 256 + (unsigned char)data[3] * 256 * 256 + (unsigned char)data[4] * 256 + (unsigned char)data[5]);

			//DEBUG_PRINT("attribute_name_index:%d\n", attribute_name_index);
			//DEBUG_PRINT("attribute lenght:%d\n", attribute_length);
			reader(attribute_length);
		}
	}

	return 0;
}
int ClassLoader::loadMethods(Class * thisClass) {
	reader(2);
	int methods_count = (int)((unsigned char)data[0] * 256 + (unsigned char)data[1]);

	DEBUG_PRINT("method count %d\n", methods_count);


	for (int i = 0; i < methods_count; i++)
	{
		int access_flags;
		int name_index;
		int descriptor_index;
		int attributes_count;
		reader(8);
			access_flags = (int)((unsigned char)data[0] * 256 + (unsigned char)data[1]);
		name_index = (int)((unsigned char)data[2] * 256 + (unsigned char)data[3]);
		descriptor_index = (int)((unsigned char)data[4] * 256 + (unsigned char)data[5]);
		attributes_count = (int)((unsigned char)data[6] * 256 + (unsigned char)data[7]);


		// create new method onject
		Method * m = new Method(access_flags);
		m->name = Utf8String(thisClass->constantPool->get(name_index)->utf8Info.bytes, (int)thisClass->constantPool->get(name_index)->utf8Info.length);
		m->descriptor = Utf8String(thisClass->constantPool->get(descriptor_index)->utf8Info.bytes, (int)thisClass->constantPool->get(descriptor_index)->utf8Info.length);


		DEBUG_PRINT("method %d flags: %d\n", i, access_flags);
		DEBUG_PRINT("method %d name: %d\n", i, name_index);
		DEBUG_PRINT("method %d descriptor: %d\n", i, descriptor_index);
		DEBUG_PRINT("method %d att count: %d\n", i, attributes_count);


		for (int j = 0; j < attributes_count; j++)
		{
			int attribute_name_index;
			int attribute_length;
			reader(6);
		
			attribute_name_index = (int)((unsigned char)data[0] * 256 + (unsigned char)data[1]);
			attribute_length = (int)((unsigned char)data[2] * 256 * 256 * 256 + (unsigned char)data[3] * 256 * 256 + (unsigned char)data[4] * 256 + (unsigned char)data[5]);
		
			DEBUG_PRINT("method %d name index: %d\n", j, attribute_name_index);
			DEBUG_PRINT("method %d att length: %d\n", j, attribute_length);


			reader(attribute_length);
		
			unsigned char* n = thisClass->constantPool->get(attribute_name_index)->utf8Info.bytes;
			int n_length = (int)thisClass->constantPool->get(attribute_name_index)->utf8Info.length;

			DEBUG_PRINT("name %s %d\n", n, n_length);


			if (n_length == 4 && n[0] == 'C'&&n[1] == 'o'&&n[2] == 'd'&&n[3] == 'e') // zmenit na porovnani utf8
			{
				DEBUG_PRINT("method %d CODE:\n", j);


				int max_stack = (int)((unsigned char)data[0] * 256 + (unsigned char)data[1]);
				m->operandStackSize = max_stack;
				int max_variables = (int)((unsigned char)data[2] * 256 + (unsigned char)data[3]);
				m->localVariablesArraySize = max_variables;
				int code_length = (int)((unsigned char)data[4] * 256 * 256 * 256 + (unsigned char)data[5] * 256 * 256 + (unsigned char)data[6] * 256 + (unsigned char)data[7]);
				m->byteCodeLength = code_length;
				//unsigned char * code = new unsigned char[code_length];


				DEBUG_PRINT("method %d max stack: %d\n", j, max_stack);
				DEBUG_PRINT("method %d max var: %d\n", j, max_variables);
				DEBUG_PRINT("method %d code length: %d\n", j, code_length);


				m->byteCode = new Instruction[code_length];

				for (int i1 = 0; i1 < code_length; i1++)
				{
					m->byteCode[i1] = (unsigned char)(unsigned char)data[i1 + 8];

				}

				int exception_table_length = (int)((unsigned char)data[code_length + 8] * 256 + (unsigned char)data[code_length + 9]);

				DEBUG_PRINT("method %d exc table length: %d\n", j, exception_table_length);


				m->exceptionTable = new ExceptionTable(exception_table_length);

				for (int i1 = 0; i1 < exception_table_length; i1++)
				{
					int start_pc = (int)((unsigned char)data[code_length + 10 + i1 * 8] * 256 + (unsigned char)data[code_length + 11 + i1 * 8]);
					int end_pc = (int)((unsigned char)data[code_length + 12 + i1 * 8] * 256 + (unsigned char)data[code_length + 13 + i1 * 8]);
					int handler_pc = (int)((unsigned char)data[code_length + 14 + i1 * 8] * 256 + (unsigned char)data[code_length + 15 + i1 * 8]);
					int catch_type = (int)((unsigned char)data[code_length + 16 + i1 * 8] * 256 + (unsigned char)data[code_length + 17 + i1 * 8]);

					DEBUG_PRINT("method %d ecx %d start pc: %d\n", j, i1, start_pc);
					DEBUG_PRINT("method %d ecx %d end pc: %d\n", j, i1, end_pc);
					DEBUG_PRINT("method %d ecx %d handler pc: %d\n", j, i1, handler_pc);
					DEBUG_PRINT("method %d ecx %d catch type: %d\n", j, i1, catch_type);


					if (catch_type ==0)
					{
						Exception exc(start_pc, end_pc, handler_pc, catch_type, NULL);
						m->exceptionTable->addException(exc);
					}
					else
					{
						int n_i = thisClass->constantPool->get(catch_type)->classInfo.name_index;

						Utf8String exc_name = Utf8String(thisClass->constantPool->get(n_i)->utf8Info.bytes, thisClass->constantPool->get(n_i)->utf8Info.length);
						Exception exc(start_pc, end_pc, handler_pc, catch_type, this->runtime->classTable->getClass(exc_name));
						m->exceptionTable->addException(exc);
					}
					
				}

				int code_attributes_count = (int)((unsigned char)data[code_length + 10 + exception_table_length * 8] * 256 + (unsigned char)data[code_length + 11 + exception_table_length * 8]);
			
				DEBUG_PRINT("method %d code att count: %d\n", j, code_attributes_count);


			}
			else if (n_length == 11 && n[0] == 'E' &&n[1] == 'x' &&n[2] == 'c' &&n[3] == 'e' &&n[4] == 'p' &&n[5] == 't' &&n[6] == 'i' &&n[7] == 'o' &&n[8] == 'n' &&n[9] == 's')// Exceptions
			{
				DEBUG_PRINT("method %d EXCEPTIONS:\n", j);


				int number_of_exceptions = (int)((unsigned char)data[0] * 256 + (unsigned char)data[1]);
				for (int k = 0; k < number_of_exceptions; k++)
				{
					int exception_index = (int)((unsigned char)data[2 + k * 2] * 256 + (unsigned char)data[3 + k * 2]);
					//add exception to exception table?
				}
			}
			else
			{
				DEBUG_PRINT("method %d OTHER : %s \n", j, n);
			}
		}

		thisClass->addMethod(m);
	}


	return 0;
}
int ClassLoader::loadAttributes(Class * thisClass)
{
	reader(2);
	int attributes_count = (int)((unsigned char)data[0] * 256 + (unsigned char)data[1]);

	DEBUG_PRINT("attributes count:%d\n", attributes_count);


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
		reader(6);
	
		attribute_name_index = (int)((unsigned char)data[0] * 256 + (unsigned char)data[1]);
		attribute_length = (int)((unsigned char)data[2] * 256 * 256 * 256 + (unsigned char)data[3] * 256 * 256 + (unsigned char)data[4] * 256 + (unsigned char)data[5]);

		DEBUG_PRINT("attribute_name_index:%d\n", attribute_name_index);
		DEBUG_PRINT("attribute lenght:%d\n", attribute_length);


		reader(attribute_length);
	
	}

	return 0;
}

void ClassLoader::reader(int nob)
{
	if (myfile->is_open())
	{
		if (nob > 1024)
		{
			delete[] data;
			data = new char[nob];
		}
		myfile->read(data, nob);
	}
	else
	{
		throw NoClassDefFoundError("Error while reading from file");
	}
}
void ClassLoader::resolvePool(Class * thisClass, int nameptr)
{
	int constant_pool_size = thisClass->constantPool->GetSize();
	for (int i = 1; i < constant_pool_size; i++)
	{

		int item_tag = thisClass->constantPool->get(i)->tag;
		//DEBUG_PRINT("resolve pool %d %d\n",i,item_tag);
		switch (item_tag)
		{
		case  ConstantPoolTag::CONSTANT_Class: {

			if (thisClass->constantPool->get(i)->classInfo.classPtr == nullptr)
			{
				resolveClassPointer(thisClass, i, nameptr);
			}

			break;}
		case  ConstantPoolTag::CONSTANT_Fieldref:
		{
			//classptr
			int class_index = thisClass->constantPool->get(i)->fieldInfo.class_index;
			if (thisClass->constantPool->get(class_index)->classInfo.classPtr == nullptr)
			{
				resolveClassPointer(thisClass, class_index, nameptr);
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

				resolveClassPointer(thisClass, class_index , nameptr);

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
			else if (myClass != nullptr && myClass->methodArea.getMethod(item_name, item_descriptor) != nullptr)
			{
				thisClass->constantPool->setMethodPtr(i, myClass->methodArea.getMethod(item_name, item_descriptor));
			}


			break;}
		case  ConstantPoolTag::CONSTANT_InterfaceMethodref: {
			//classptr
			int class_index = thisClass->constantPool->get(i)->interfaceMethodInfo.class_index;
			if (thisClass->constantPool->get(class_index)->classInfo.classPtr == nullptr)
			{
				resolveClassPointer(thisClass, class_index,nameptr);
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
	//DEBUG_PRINT("resolving finnished\n");
}
void ClassLoader::resolveClassPointer(Class * thisClass, int i, int nameptr)
{
	DEBUG_PRINT("resolve class pointer %d\n", i);

	int name_index = thisClass->constantPool->get(i)->classInfo.name_index;
	Utf8String item_name = Utf8String(thisClass->constantPool->get(name_index)->utf8Info.bytes, thisClass->constantPool->get(name_index)->utf8Info.length);

	Class* class_pointer = classMap->getClass(item_name);

	if (class_pointer == nullptr)
	{
		//reurzivne zavolej classloader pro tridu co nenasel
		/*
		exc/All
		exc/prd
		exc/Ales

		prd/exc/All
		prd/exc/blb
		prd/rtr/pko
		sup/brk

		*/
		unsigned char *a = thisClass->constantPool->get(name_index)->utf8Info.bytes;
		//string a ((char*)thisClass->constantPool->get(name_index)->utf8Info.bytes);
		size_t alen = thisClass->constantPool->get(name_index)->utf8Info.length;
		size_t tclen = thisClass->constantPool->get(nameptr)->utf8Info.length;
		
		int counter = 0;
		int lastcol = 0;
		int morecol = 0;

		for (size_t i = 0; i < (alen > tclen ? alen : tclen); i++)
		{
			if (a[i] == thisClass->constantPool->get(nameptr)->utf8Info.bytes[i])
			{
				counter++;
				if (a[i] == '/')
				{
					lastcol = i;
				}
			}
			else
			{
				for (size_t j = i; j < alen; j++)
				{
					if (a[i] == '/')
					{
						morecol++;
					}
				}
				break;
			}
		}

		if (morecol > 0)
		{
			morecol = 0;
			for (size_t i = 0; i < tclen; i++)
			{
				if (thisClass->constantPool->get(nameptr)->utf8Info.bytes[i] == '/')
				{
					morecol++;
				}

			}

		}

		DEBUG_PRINT("%s ", a);
		DEBUG_PRINT("%d %d %d\n", counter, lastcol, morecol);
		
		if (!(lastcol==0 && counter== 0))
		{
			lastcol++;
		}
		
		char ext[] = ".class";
		//strcpy_s(r, alen + 7, (char*)a);
		//strncpy_s(r + alen, alen + 7, ext, strlen(ext));
		a = a + lastcol;
		alen = strlen((char*)a);

		DEBUG_PRINT("%s %d\n", a, alen);

		char * adr = new char[alen+ 7 + (morecol*3)];
		for (size_t i = 0; i < morecol; i++)
		{
			
			adr[i * 3] = '.';
			adr[i * 3 +1] = '.';
			adr[i * 3 +2] = '/';
			//char c[] = "../";
			//strncpy_s(r+(i*3),((i+1) * 3),c, strlen(c));
		}

		memcpy(adr + (morecol * 3), (char*)a, strlen((char*)a) + 1);
		memcpy(adr + alen  + (morecol * 3), ext, strlen(ext) + 1);

		// NamespaceStructure structure(thisClass->fullyQualifiedName.toAsciiString());

		this->load(adr);
		delete[] adr;

		class_pointer = classMap->getClass(item_name);

	}

	DEBUG_PRINT("set class ptr %d\n", i);

	thisClass->constantPool->setClassPtr(i, class_pointer);

}
