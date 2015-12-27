#include "ClassLoader.h"

using namespace std;

ClassLoader::ClassLoader()
{
	
}
ClassLoader::ClassLoader(ClassMap * cm)
{
	this->classMap = cm;
	this->constantPool = new ConstantPool(1000);
}

Class* ClassLoader::load(char * filename)
{
	
	if (myfile.is_open())
	{
		myfile.close();
	}

	myfile = ifstream(filename, ios::in | ios::binary);
	
	if (!myfile.is_open())
	{
		throw;
	}
	data = new unsigned char[0];
	//thisClass = Class();
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
	//delete[] data;
	
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

	int minor_version = (int)(data[0] * 256 + data[1]);
	printf("min_ver:%d\n", minor_version);
	return 0; 
}
int ClassLoader::loadMajVersion()
{
	if (reader(2))
	{
		printf("ERROR IN READ FILE");
		return -1;
	}

	int major_version = (int)(data[0] * 256 + data[1]);
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
	int constant_pool_count = (int)(data[0] * 256 + data[1]);
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
		
		int cpType = (int)(data[0]);
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
				unsigned char * utfdata;
			
				int utflength = (int)(data[0] * 256 + data[1]);
				utfdata = new unsigned char[utflength + 1];
				if (reader(utflength))
				{
					printf("ERROR IN READ FILE");
					return -1;
				}

				for (int i = 0; i < utflength; i++)
				{
					utfdata[i] = data[i];
				}

				utfdata[utflength] = '\0';

				
				constantPool->add(k, cpType, utflength, utfdata);
			}
			break;
		case ConstantPoolTag::CONSTANT_Integer ://integer
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
	unsigned short access_flags = (unsigned short)(data[0] * 256 + data[1]);
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
	int thisClassIndex=(int)(data[0] * 256 + data[1]);
	thisClass->constantPool->setClassPtr(thisClassIndex,thisClass);
	printf("this class:%d\n",thisClassIndex);
	int nameptr = thisClass->constantPool->get(thisClassIndex)->classInfo.name_index;
	thisClass ->fullyQualifiedName= Utf8String(thisClass->constantPool->get(nameptr)->utf8Info.bytes,thisClass->constantPool->get(nameptr)->utf8Info.length);
	
	return 0; 
}
int ClassLoader::loadSuperClass(Class * thisClass)
{
	if (reader(2))
	{
		printf("ERROR IN READ FILE");
		return -1;
	}
	int superClassIndex = (int)(data[0] * 256 + data[1]);

	
	return 0;
}
int ClassLoader::loadInterfaces(Class * thisClass) // TODO write interefaces, where? //references to const pool
{
	if (reader(2))
	{
		printf("ERROR IN READ FILE");
		return -1;
	}
	int interfaces_count = (int)(data[0] * 256 + data[1]);
	int * interfacesIndex = new int[interfaces_count];
	//printf("interface count:%d\n", interfaces_count);
	for (int i = 0; i < interfaces_count; i++)
	{
		if (reader(2))
		{
			printf("ERROR IN READ FILE");
			return -1;
		}
		interfacesIndex[i] = (int)(data[0] * 256 + data[1]);
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

	if(reader(2))
	{
		printf("ERROR IN READ FILE");
		return -1;
	}
	int fields_count = (int)(data[0] * 256 + data[1]);
	thisClass->countFields = (unsigned int)(data[0] * 256 + data[1]);
	
	//printf("fields count:%d\n", fields_count);

	unsigned short* flags;
	flags = new unsigned short[fields_count];

	int * name_indexes;
	name_indexes = new int[fields_count];

	int * descriptor_indexes;
	descriptor_indexes = new int[fields_count];

	int * att_counts;
	att_counts = new int[fields_count];

	int ** att_name_indexes;
	att_name_indexes = new int*[fields_count];

	int ** att_lengts;
	att_lengts = new int*[fields_count];
	
	unsigned char *** att_data;
	att_data = new unsigned char **[fields_count];

	for (int i = 0; i < fields_count; i++)
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
		access_flags = (int)(data[0] * 256 + data[1]);
		name_index = (int)(data[2] * 256 + data[3]);
		descriptor_index = (int)(data[4] * 256 + data[5]);
		attributes_count = (int)(data[6] * 256 + data[7]);

		flags[i] = (unsigned short)(data[0] * 256 + data[1]);
		name_indexes[i] = (int)(data[2] * 256 + data[3]);
		descriptor_indexes[i] = (int)(data[4] * 256 + data[5]);
		att_counts[i] = (int)(data[6] * 256 + data[7]);

		//printf("access_flags:%d\n", access_flags);
		//printf("name_index:%d\n", name_index);
		//printf("descriptor_index:%d\n", descriptor_index);
		//printf("attributes count:%d\n", attributes_count);

		att_name_indexes[i] = new int[att_counts[i]];
		att_lengts[i] = new int[att_counts[i]];
		att_data[i]= new unsigned char*[att_counts[i]];

		for (int j = 0; j < attributes_count; j++)
		{
			int attribute_name_index;
			int attribute_length;
			if (reader(6))
			{
				printf("ERROR IN READ FILE");
				return -1;
			}

			attribute_name_index = (int)(data[0] * 256 + data[1]);
			attribute_length = (int)(data[2] * 256 * 256 * 256 + data[3] * 256 * 256 + data[4] * 256 + data[5]);

			att_name_indexes[i][j] =  (int)(data[0] * 256 + data[1]);
			att_lengts[i][j] = (int)(data[2] * 256 * 256 * 256 + data[3] * 256 * 256 + data[4] * 256 + data[5]);
			

			//printf("attribute_name_index:%d\n", attribute_name_index);
			//printf("attribute lenght:%d\n", attribute_length);
			if (reader(attribute_length))
			{
				printf("ERROR IN READ FILE");
				return -1;
			}
			att_data[i][j] = data;
		}
	}
	for (int i = 0; i < fields_count; i++)
	{
		thisClass->fields = new Field*[thisClass->countFields];
		Utf8String name(thisClass->constantPool->get(name_indexes[i])->utf8Info.bytes, (int)thisClass->constantPool->get(name_indexes[i])->utf8Info.length);
		Utf8String descriptor(thisClass->constantPool->get(descriptor_indexes[i])->utf8Info.bytes, (int)thisClass->constantPool->get(descriptor_indexes[i])->utf8Info.length);
		thisClass->fields[i] = new Field(flags[i], name, descriptor, att_counts[i]);

		for (int j = 0; j < att_counts[i]; j++)
		{
			if (att_lengts[i][j] == 2)
			{
				thisClass->fields[i]->setAttribute(j, att_data[i][j][0] * 256 + att_data[i][j][1]);
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
	int methods_count = (int)(data[0] * 256 + data[1]);
	thisClass->countMethods = methods_count;
	//printf("methods count:%d\n", methods_count);
	
	//methods[methods_count]
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
	//[attribute data, see Table 13]
	//}
	//}
	//}

	unsigned short* flags;
	flags = new unsigned short[methods_count];

	int * name_indexes;
	name_indexes = new int[methods_count];

	int * descriptor_indexes;
	descriptor_indexes = new int[methods_count];

	int * att_counts;
	att_counts = new int[methods_count];

	int ** att_name_indexes;
	att_name_indexes = new int*[methods_count];

	int ** att_lengts;
	att_lengts = new int*[methods_count];

	unsigned char *** att_data;
	att_data = new unsigned char **[methods_count];

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
		access_flags = (int)(data[0] * 256 + data[1]);
		name_index = (int)(data[2] * 256 + data[3]);
		descriptor_index = (int)(data[4] * 256 + data[5]);
		attributes_count = (int)(data[6] * 256 + data[7]);

		flags[i] = (unsigned short)(data[0] * 256 + data[1]);
		name_indexes[i] = (int)(data[2] * 256 + data[3]);
		descriptor_indexes[i] = (int)(data[4] * 256 + data[5]);
		att_counts[i] = (int)(data[6] * 256 + data[7]);

		att_name_indexes[i] = new int[att_counts[i]];
		att_lengts[i] = new int[att_counts[i]];
		att_data[i] = new unsigned char*[att_counts[i]];

		//printf("access_flags:%d\n", access_flags);
		//printf("name_index:%d\n", name_index);
		//printf("descriptor_index:%d\n", descriptor_index);
		//printf("attributes count:%d\n", attributes_count);
		for (int j = 0; j < attributes_count; j++)
		{
			int attribute_name_index;
			int attribute_length;
			if (reader(6))
			{
				printf("ERROR IN READ FILE");
				return -1;
			}

			attribute_name_index = (int)(data[0] * 256 + data[1]);
			attribute_length = (int)(data[2] * 256 * 256 * 256 + data[3] * 256 * 256 + data[4] * 256 + data[5]);

			att_name_indexes[i][j] = (int)(data[0] * 256 + data[1]);
			att_lengts[i][j] = (int)(data[2] * 256 * 256 * 256 + data[3] * 256 * 256 + data[4] * 256 + data[5]);
			att_data[i][j] = new unsigned char[att_lengts[i][j]];

			//printf("attribute_name_index:%d\n", attribute_name_index);
			//printf("attribute lenght:%d\n", attribute_length);
			if (reader(attribute_length))
			{
				printf("ERROR IN READ FILE");
				return -1;
			}
			for (int k = 0; k < att_lengts[i][j]; k++)
			{
				att_data[i][j][k] = data[k];
			}
			

		}
	}
	for (int i = 0; i < methods_count; i++)
	{
		Method * m = new Method(flags[i]);
		m->name = Utf8String(thisClass->constantPool->get(name_indexes[i])->utf8Info.bytes, (int)thisClass->constantPool->get(name_indexes[i])->utf8Info.length);
		m->descriptor = Utf8String(thisClass->constantPool->get(descriptor_indexes[i])->utf8Info.bytes, (int)thisClass->constantPool->get(descriptor_indexes[i])->utf8Info.length);

		printf("method %d flags: %d\n", i, flags[i]);
		printf("method %d name: %d\n", i, name_indexes[i]);
		printf("method %d descriptor: %d\n", i, descriptor_indexes[i]);
		printf("method %d att count: %d\n", i, att_counts[i]);

		for (int j = 0; j < att_counts[i]; j++)
		{
			unsigned char* n= thisClass->constantPool->get(att_name_indexes[i][j])->utf8Info.bytes;
			int n_length = (int)thisClass->constantPool->get(att_name_indexes[i][j])->utf8Info.length;
			
			
			if (n_length == 4 && n[0]=='C'&&n[1] == 'o'&&n[2] == 'd'&&n[3] == 'e'&& n[4]=='\0') // zmenit na porovnani utf8
			{
				printf("method %d CODE:\n", i);
				int max_stack = (int)(att_data[i][j][0] *256 + att_data[i][j][1]);
				m->operandStackSize = max_stack;
				int max_variables = (int)(att_data[i][j][2] *256 + att_data[i][j][3]);
				m->localVariablesArraySize;
				int code_length = (int)(att_data[i][j][4] * 256 *256 * 256 + att_data[i][j][5] *256 *256 + att_data[i][j][6] * 256 + att_data[i][j][7]);
				m->byteCodeLength = code_length;
				//unsigned char * code = new unsigned char[code_length];
				m->byteCode = new Instruction[code_length];

				printf("method %d max stack: %d\n", i, max_stack);
				printf("method %d max var: %d\n", i, max_variables);
				printf("method %d code length: %d\n", i, code_length);


				for (int i1 = 0; i1 < code_length; i1++)
				{
					m->byteCode[i1] = att_data[i][j][i1+8];

				}
			
				int exception_table_length = (int)(att_data[i][j][code_length+8] * 256 + att_data[i][j][code_length+9]);
				//printf("method %d exc table length: %d\n", i, exception_table_length);
				//m->exceptionTable = ExceptionTable(exception_table_length);
				for (int i1 = 0; i1 < exception_table_length; i1++)
				{
					int start_pc = (int)(att_data[i][j][code_length + 10 + i1*8] * 256 + att_data[i][j][code_length + 11 + i1 * 8]);
					int end_pc = (int)(att_data[i][j][code_length + 12 + i1 * 8] * 256 + att_data[i][j][code_length + 13 + i1 * 8]);
					int handler_pc = (int)(att_data[i][j][code_length + 14 + i1 * 8] * 256 + att_data[i][j][code_length + 15 + i1 * 8]);
					int catch_type = (int)(att_data[i][j][code_length + 16 + i1 * 8] * 256 + att_data[i][j][code_length + 17 + i1 * 8]);
					//m->exceptionTable.setException(i1,start_pc,end_pc, handler_pc, catch_type);
					int n_i = thisClass->constantPool->get(catch_type)->classInfo.name_index;
					
					Utf8String exc_name = Utf8String(thisClass->constantPool->get(n_i)->utf8Info.bytes, thisClass->constantPool->get(n_i)->utf8Info.length);
					m->exceptionTable.addException(exc_name, start_pc, end_pc, handler_pc, catch_type);
				}

				int code_attributes_count = (int)(att_data[i][j][code_length + 10 + exception_table_length * 8] * 256 + att_data[i][j][code_length + 11 + exception_table_length * 8]);
				//printf("method %d code att count: %d\n", i, code_attributes_count);
				int r = 0;
				/*
				for (int i1 = 0; i1 < code_attributes_count; i1++)
				{
					//Utf8String datAttName(thisClass->constantPool->get(att_data[i][j][code_length + 12 + (exception_table_length * 8) + r])->utf8Info.bytes, (int)thisClass->constantPool->get(att_data[i][j][code_length + 13 + (exception_table_length * 8) + r])->utf8Info.length);
					int datAttName = (int)(att_data[i][j][code_length + 12 +r + exception_table_length * 8] * 256 + att_data[i][j][code_length + 13 + r + exception_table_length * 8]);
					printf("method %d code att %d name: %d\n", i,i1, datAttName);
					r += 6; //name + length
					
					unsigned char* an = thisClass->constantPool->get(datAttName)->utf8Info.bytes;
					int an_length = (int)thisClass->constantPool->get(datAttName)->utf8Info.length;
					
					if (an_length == 15)//LineNumberTable
					{

					}
					else if (an_length == 13)// StackMapTable
					{
						int number_of_entries = (int)(att_data[i][j][code_length + 12+r + exception_table_length * 8] * 256 + att_data[i][j][code_length + 13+r + exception_table_length * 8]);
						r += 2;
						for (int i2 = 0; i2 < number_of_entries; i2++)
						{
							short tag = (short)(att_data[i][j][code_length + 12 + r + exception_table_length * 8]);
							switch (tag)
							{
							case 7:
							case 8:
								r += 2;
							default:
								break;
							}
						}
					}
					else if (an_length == 22)//LocalVariableTypeTable
					{

					}
					else if (an_length == 18)//LocalVariableTable
					{

					}
				}
				*/
			}
			else if (n_length == 11 &&n[0]=='E' &&n[1] == 'x' &&n[2] == 'c' &&n[3] == 'e' &&n[4] == 'p' &&n[5] == 't' &&n[6] == 'i' &&n[7] == 'o' &&n[8] == 'n' &&n[9] == 's')// Exceptions
			{
				printf("method %d EXCEPTIONS:\n", i);

				int number_of_exceptions = (int)(att_data[i][j][0] * 256 + att_data[i][j][1]);
				for (int k = 0; k < number_of_exceptions; k++)
				{
					int exception_index = (int)(att_data[i][j][2 + k*2] * 256 + att_data[i][j][3+ k*2]);
					//add exception to exception table?
				}
			}
			else if (n_length == 16 && n[0] == 'M' &&n[1] == 'e' &&n[2] == 't' &&n[3] == 'h' &&n[4] == 'o' &&n[5] == 'd' &&n[6] == 'P' &&n[7] == 'a' &&n[8] == 'r' &&n[9] == 'a'&&n[10] == 'm'&&n[11] == 'e'&&n[12] == 't'&&n[13] == 'e'&&n[14] == 'r'&&n[15] == 's')// MethodParameters
			{

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
	int attributes_count = (int)(data[0] * 256 + data[1]);
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

		attribute_name_index = (int)(data[0] * 256 + data[1]);
		attribute_length = (int)(data[2] * 256 * 256 * 256 + data[3] * 256 * 256 + data[4] * 256 + data[5]);

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
		delete[] data;
		char* sdata = new char[nob];
		data = new unsigned char[nob];
		myfile.read(sdata, nob);
		for (int i = 0; i < nob; i++)
		{
			data[i] = (unsigned char)sdata[i];
			//printf("%X", data[i]);
		}
		//printf("\n");
		delete[] sdata;
		return 0;
	}
	else
	{
		throw;
		return -1;
	}

}
void ClassLoader::resolvePool(Class * thisClass)
{
	int constant_pool_size = thisClass->constantPool->GetSize();
	for (int i = 1; i < constant_pool_size; i++)
	{
				
		int item_tag = thisClass->constantPool->get(i)->tag;
		printf("resolve pool %d %d\n",i,item_tag);
		switch (item_tag)
		{
		case  ConstantPoolTag::CONSTANT_Class : {
			
			if (thisClass->constantPool->get(i)->classInfo.classPtr == nullptr)
			{
				resolveClassPointer(thisClass,i);
			}
			
			break;}
		case  ConstantPoolTag::CONSTANT_Fieldref: {
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
				
				for (int j = 0; j < thisClass->countFields; j++)
				{
					if (thisClass->fields[i]->descriptor == item_descriptor && thisClass->fields[i]->name == item_name)
					{
						thisClass->constantPool->setFieldPtr(i, thisClass->fields[i]);
					}
				}
				if (thisClass->constantPool->get(i)->fieldInfo.fieldPtr==nullptr && myClass != nullptr )
				{
					for (int j = 0; j < myClass->countFields; j++)
					{
						if (myClass->fields[i]->descriptor == item_descriptor && myClass->fields[i]->name == item_name)
						{
							thisClass->constantPool->setFieldPtr(i, myClass->fields[i]);
						}
					}
				}
			//}
			

			break;}
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
void ClassLoader::resolveClassPointer(Class * thisClass,int i)
{
	printf("resolve class pointer %d\n",i);
	int name_index = thisClass->constantPool->get(i)->classInfo.name_index;
	Utf8String item_name = Utf8String(thisClass->constantPool->get(name_index)->utf8Info.bytes, thisClass->constantPool->get(name_index)->utf8Info.length);

	Class* class_pointer = classMap->getClass(item_name);

	if (class_pointer == nullptr)
	{
		//reurzivne zavolej classloader pro tridu co nenasel
		
		unsigned char *a =  thisClass->constantPool->get(name_index)->utf8Info.bytes;
		size_t alen = thisClass->constantPool->get(name_index)->utf8Info.length;
		char *r = new char[alen+6];

		for (size_t i = 0; i < alen; i++)
		{
			r[i] = (char)a[i];
			
		}
		r[alen] = '.';
		r[alen+1] = 'c';
		r[alen+2] = 'l';
		r[alen+3] = 'a';
		r[alen+4] = 's';
		r[alen+5] = 's';
		for (size_t i = alen +6; i < strlen(r); i++)
		{
			r[i] = ' ';
		}
		
		this->load(r);

		class_pointer = classMap->getClass(item_name);
		
	}
	
		printf("set class ptr %d\n",i);
		thisClass->constantPool->setClassPtr(i, class_pointer);
	
}
ClassLoader::~ClassLoader()
{
	
}

