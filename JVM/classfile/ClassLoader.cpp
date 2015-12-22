#include "ClassLoader.h"

using namespace std;

ClassLoader::ClassLoader()
{
	
}

int ClassLoader::load(char * filename)
{
	constant_pool_count = 0;
	interfaces_count = 0;
	fields_count = 0;
	methods_count = 0;
	attributes_count = 0;
	access_flags = 0;
	myfile = ifstream (filename, ios::in | ios::binary);
	data = new unsigned char[0];
	//thisClass = Class();
	if (reader(4))//read CAFEBABE
	{
		printf("ERROR IN READ FILE");
		return -1;
	}

	
	loadMinVersion();
	loadMajVersion();
	loadConstPool();
	loadFlags();
	FLAG f = access_flags;
	thisClass = new Class(f);
	thisClass->constantPool = this->constantPool;
	thisClass->constantPool->print();
	loadThisClass();
	loadSuperClass();
	loadInterfaces();
	loadFields();
	loadMethods();
	loadAttributes();

	myfile.close();

	delete[] data;
	return 0;
}
int ClassLoader::loadMinVersion() 
{
	if (reader(2))
	{
		printf("ERROR IN READ FILE");
		return -1;
	}

	minor_version = (int)(data[0] * 256 + data[1]);
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

	major_version = (int)(data[0] * 256 + data[1]);
	printf("maj_ver:%d\n", major_version);
	return 0;
}
int ClassLoader::loadConstPool() 
{
	if (reader(2))
	{
		printf("ERROR IN READ FILE");
		return -1;
	}
	constant_pool_count = (int)(data[0] * 256 + data[1]);
	printf("constant_pool_count:%d\n", constant_pool_count);
	//CPool = new ConstantPool(constant_pool_count);
	constantPool = new ConstantPool(constant_pool_count);
	
	for (int k = 1; k < constant_pool_count; k++)
	{

		if (reader(1))
		{
			printf("ERROR IN READ FILE");
			return -1;
		}
		
		int cpType = (int)(data[0]);
		printf("entry:%d type:%d\n", k, cpType);
		switch (cpType)
		{

		case 1://utf8
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
				//utfdata[0] = data[0];
				//utfdata[1] = data[1];
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

				//CPool->add(k,(unsigned char)cpType,utflength+2,utfdata);
				constantPool->add(k, cpType, utflength, utfdata);
			}
			break;
		case 2:
			//is not in table of types
			printf("ERROR WRONG CPTYPE 2\n");
			
			break;
		case 3://integer
			if (reader(4))
			{
				printf("ERROR IN READ FILE");
				return -1;
			}
			//CPool->add(k, (unsigned char)cpType, 4, data);
			constantPool->add(k, cpType, 4, data);
			break;
		case 4://float
			
			if (reader(4))
			{
				printf("ERROR IN READ FILE");
				return -1;
			}
			//CPool->add(k, (unsigned char)cpType, 4, data);
			constantPool->add(k, cpType, 4, data);
			break;
		case 5://long
			
			if (reader(8))
			{
				printf("ERROR IN READ FILE");
				return -1;
			}
			//CPool->add(k, (unsigned char)cpType, 8, data);
			constantPool->add(k, cpType, 8, data);
			break;
		case 6://double
			
			if (reader(8))
			{
				printf("ERROR IN READ FILE");
				return -1;
			}
			//CPool->add(k, (unsigned char)cpType, 8, data);
			constantPool->add(k, cpType, 8, data);
			break;
		case 7://class
			
			if (reader(2))
			{
				printf("ERROR IN READ FILE");
				return -1;
			}
			//CPool->add(k, (unsigned char)cpType, 2, data);
			constantPool->add(k, cpType, 2, data);
			break;
		case 8://string
			
			if (reader(2))
			{
				printf("ERROR IN READ FILE");
				return -1;
			}
			//CPool->add(k, (unsigned char)cpType,2, data);
			constantPool->add(k, cpType, 2, data);
			break;
		case 9://fieldref
			
			if (reader(4))
			{
				printf("ERROR IN READ FILE");
				return -1;
			}
			//CPool->add(k, (unsigned char)cpType, 4, data);
			constantPool->add(k, cpType, 4, data);
			break;
		case 10://methodref
			
			if (reader(4))
			{
				printf("ERROR IN READ FILE");
				return -1;
			}
			//CPool->add(k, (unsigned char)cpType, 4, data);
			constantPool->add(k, cpType, 4, data);
			break;
		case 11://interfacemethodref
			
			if (reader(4))
			{
				printf("ERROR IN READ FILE");
				return -1;
			}
			//CPool->add(k, (unsigned char)cpType, 4, data);
			constantPool->add(k, cpType, 4, data);
			break;
		case 12://nameandtype
			
			if (reader(4))
			{
				printf("ERROR IN READ FILE");
				return -1;
			}
			//CPool->add(k, (unsigned char)cpType, 4, data);
			constantPool->add(k, cpType, 4, data);
			break;
		case 15://_MethodHandle

			if (reader(3))
			{
				printf("ERROR IN READ FILE");
				return -1;
			}
			//CPool->add(k, (unsigned char)cpType, 3, data);
			constantPool->add(k, cpType, 3, data);
			break;
		case 16://_MethodType

			if (reader(2))
			{
				printf("ERROR IN READ FILE");
				return -1;
			}
			//CPool->add(k, (unsigned char)cpType,2, data);
			constantPool->add(k, cpType, 2, data);
			break;
		case 18://InvokeDynamic

			if (reader(4))
			{
				printf("ERROR IN READ FILE");
				return -1;
			}
			//CPool->add(k, (unsigned char)cpType, 4, data);
			constantPool->add(k, cpType, 4, data);
			break;

		default:
			printf("ERROR WRONG CPTYPE %d\n", cpType);
			
		}

	}
	//CPool->print();

	return 0; 
}
int ClassLoader::loadFlags()
{
	if (reader(2))
	{
		printf("ERROR IN READ FILE");
		return -1;
	}
	access_flags = (unsigned short)(data[0] * 256 + data[1]);
	printf("access flags:%X\n", access_flags);
	return 0;
}
int ClassLoader::loadThisClass() 
{

	if (reader(2))
	{
		printf("ERROR IN READ FILE");
		return -1;
	}
	thisClassIndex=(int)(data[0] * 256 + data[1]);
	thisClass->constantPool->setClassPtr(thisClassIndex,thisClass);
	
	/*
	int l;
	unsigned char * adr = CPool->getElem((int)(data[0] * 256 + data[1]),l);

	thisClassName = CPool->getElem((int)(adr[0] * 256 +adr[1]),l);
	char * nameAux = new char[l];
	printf("this: ");
	for (int i = 0; i < l; i++)
	{
		printf("%c", thisClassName[i]);
		nameAux[i] = thisClassName[i];
	}
	printf("\n");
	size_t lAux = l;

	Utf8String name = Utf8String(nameAux, lAux);
	thisClass->fullyQualifiedName = name;
	*/
	return 0; 
}
int ClassLoader::loadSuperClass()
{
	if (reader(2))
	{
		printf("ERROR IN READ FILE");
		return -1;
	}
	superClassIndex = (int)(data[0] * 256 + data[1]);

	/*
	unsigned char * adr = CPool->getElem((int)(data[0] * 256 + data[1]));
	int l;
	superClassName = CPool->getElem((int)(adr[0] * 256 + adr[1]), l);
	printf("super: ");
	for (int i = 0; i < l; i++)
	{
		printf("%c", superClassName[i]);
	}
	printf("\n");
	*/
	return 0;
}
int ClassLoader::loadInterfaces() // TODO write interefaces, where? //references to const pool
{
	if (reader(2))
	{
		printf("ERROR IN READ FILE");
		return -1;
	}
	interfaces_count = (int)(data[0] * 256 + data[1]);
	interfacesIndex = new int[interfaces_count];
	printf("interface count:%d\n", interfaces_count);
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
int ClassLoader::loadFields() 
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
	fields_count = (int)(data[0] * 256 + data[1]);
	thisClass->countFields = (unsigned int)(data[0] * 256 + data[1]);
	//thisClass->fields = new Field[thisClass->countFields];
	printf("fields count:%d\n", methods_count);
	//thisClass->staticFields = new Field[fields_count];
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
		//thisClass->fields[i].flags = (const unsigned short)(data[0] * 256 + data[1]);	
		name_index = (int)(data[2] * 256 + data[3]);
		descriptor_index = (int)(data[4] * 256 + data[5]);
		attributes_count = (int)(data[6] * 256 + data[7]);

		flags[i] = (unsigned short)(data[0] * 256 + data[1]);
		name_indexes[i] = (int)(data[2] * 256 + data[3]);
		descriptor_indexes[i] = (int)(data[4] * 256 + data[5]);
		att_counts[i] = (int)(data[6] * 256 + data[7]);

		printf("access_flags:%d\n", access_flags);
		printf("name_index:%d\n", name_index);
		printf("descriptor_index:%d\n", descriptor_index);
		printf("attributes count:%d\n", attributes_count);

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
			

			printf("attribute_name_index:%d\n", attribute_name_index);
			printf("attribute lenght:%d\n", attribute_length);
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
int ClassLoader::loadMethods() {
	if (reader(2))
	{
		printf("ERROR IN READ FILE");
		return -1;
	}
	methods_count = (int)(data[0] * 256 + data[1]);
	thisClass->countMethods = methods_count;
	printf("methods count:%d\n", methods_count);
	
	//methods[methods_count]
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

		printf("access_flags:%d\n", access_flags);
		printf("name_index:%d\n", name_index);
		printf("descriptor_index:%d\n", descriptor_index);
		printf("attributes count:%d\n", attributes_count);
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

			printf("attribute_name_index:%d\n", attribute_name_index);
			printf("attribute lenght:%d\n", attribute_length);
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
		Method * m = new Method();
		m->name = Utf8String(thisClass->constantPool->get(name_indexes[i])->utf8Info.bytes, (int)thisClass->constantPool->get(name_indexes[i])->utf8Info.length);
		m->descriptor = Utf8String(thisClass->constantPool->get(descriptor_indexes[i])->utf8Info.bytes, (int)thisClass->constantPool->get(descriptor_indexes[i])->utf8Info.length);


		for (int j = 0; j < att_counts[i]; j++)
		{
			Utf8String attName(thisClass->constantPool->get(att_name_indexes[i][j])->utf8Info.bytes, (int)thisClass->constantPool->get(att_name_indexes[i][j])->utf8Info.length);
			unsigned char* n= thisClass->constantPool->get(att_name_indexes[i][j])->utf8Info.bytes;
			
			
			if (n[0]=='C'&&n[1] == '0'&&n[2] == 'd'&&n[3] == 'e') // zmenit na porovnani utf8
			{
				int max_stack = (int)(att_data[i][j][0] *256 + att_data[i][j][1]);
				m->operandStackSize = max_stack;
				int max_variables = (int)(att_data[i][j][2] *256 + att_data[i][j][3]);
				m->localVariablesArraySize;
				int code_length = (int)(att_data[i][j][4] * 256 *256 * 256 + att_data[i][j][5] *256 *256 + att_data[i][j][6] * 256 + att_data[i][j][7]);
				m->byteCodeLength = code_length;
				//unsigned char * code = new unsigned char[code_length];
				m->byteCode = new Instruction[code_length];
				for (int i1 = 0; i1 < code_length; i1++)
				{
					m->byteCode[i1] = att_data[i][j][i1+8];

				}
			
				int exception_table_length = (int)(att_data[i][j][code_length+8] * 256 + att_data[i][j][code_length+9]);
				m->exceptionTable = ExceptionTable(exception_table_length);
				for (int i1 = 0; i1 < exception_table_length; i1++)
				{
					int start_pc = (int)(att_data[i][j][code_length + 10 + i1*8] * 256 + att_data[i][j][code_length + 11 + i1 * 8]);
					int end_pc = (int)(att_data[i][j][code_length + 12 + i1 * 8] * 256 + att_data[i][j][code_length + 13 + i1 * 8]);
					int handler_pc = (int)(att_data[i][j][code_length + 14 + i1 * 8] * 256 + att_data[i][j][code_length + 15 + i1 * 8]);
					int catch_type = (int)(att_data[i][j][code_length + 16 + i1 * 8] * 256 + att_data[i][j][code_length + 17 + i1 * 8]);
					m->exceptionTable.setException(i1,start_pc,end_pc, handler_pc, catch_type);
				}
				int code_attributes_count = (int)(att_data[i][j][code_length + 10 + exception_table_length * 8] * 256 + att_data[i][j][code_length + 11 + exception_table_length * 8]);
				int r = 0;
				for (int i1 = 0; i1 < code_attributes_count; i1++)
				{
					//Utf8String datAttName(thisClass->constantPool->get(att_data[i][j][code_length + 12 + (exception_table_length * 8) + r])->utf8Info.bytes, (int)thisClass->constantPool->get(att_data[i][j][code_length + 13 + (exception_table_length * 8) + r])->utf8Info.length);
					int datAttName = (int)(att_data[i][j][code_length + 12 +r + exception_table_length * 8] * 256 + att_data[i][j][code_length + 13 + r + exception_table_length * 8]);

					r += 4; //name + length
					//if (thisClass->constantPool->get(datAttName)->utf8Info.bytes == "StackMapTable")// zmenit na porovnani utf8
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
				}
			}
		}
		thisClass->methodArea.addMethod(m);
	}

	return 0; 
}
int ClassLoader::loadAttributes()
{
	if (reader(2))
	{
		printf("ERROR IN READ FILE");
		return -1;
	}
	attributes_count = (int)(data[0] * 256 + data[1]);
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
			printf("%X", data[i]);
		}
		printf("\n");
		delete[] sdata;
		return 0;
	}
	else
	{
		return -1;
	}

}

/*
bool ClassLoader::load(char * filename)
{
	char * reader;
	int marker = 0;// says where we are 0- magic
	interfaces_count = 0;
	fields_count = 0;
	methods_count = 0;
	attributes_count = 0;
	bool br = false;
	access_flags;
	int nob = 4; //number of bytes to read
	myfile = ifstream (filename, ios::in | ios::binary);

	while (!br)
	{
		if (myfile.is_open())
		{

			data = new unsigned char[nob];
			reader = new char[nob];
			myfile.read(reader, nob);
			for (int i = 0; i < nob; i++)
			{
				data[i] = (unsigned char)reader[i];
				printf("%X", data[i]);
			}
			printf("\n");

			switch (marker)
			{
			case 0: //magic
				nob = 2;
				marker++;

				break;
			case 1:  //minor_version
				nob = 2;
				marker++;
				break;
			case 2:  //major_version
				nob = 2;
				marker++;
				break;
			case 3:  // constant_pool_count

				constant_pool_count = (int)(data[0] * 256 + data[1]);
				printf("constant_pool_count:%d\n", constant_pool_count);
				constPool = new unsigned char *[constant_pool_count];
				for (int i = 0; i < constant_pool_count; i++)
				{
					constPool[i] = new unsigned char[9];
				}

				nob = 0;
				marker++;
				break;
			case 4: // constant_pool[constant_pool_count - 1]

				for (int k = 1; k < constant_pool_count; k++)
				{

					delete[]reader;
					if (myfile.is_open())
					{
						char r[1];
						myfile.read(r, 1);
						int cpType = (int)((unsigned char)r[0]);
						int nob_cp = 0;
						printf("entry:%d type:%d\n", k, cpType);


						constPool[k][0] = (unsigned char)r[0]; //write type to const pool
						switch (cpType)
						{

						case 1://utf8
							char r1[2];
							if (myfile.is_open())
							{

								myfile.read(r1, 2);
								nob_cp = (int)(r1[0] * 256 + r1[1]);
							}
							delete[] constPool[k];
							constPool[k] = new unsigned char[nob_cp + 3];
							constPool[k][0] = (unsigned char)r[0]; //write type to const pool again
							constPool[k][1] = (unsigned char)r1[0]; //write lenght of type 1
							constPool[k][2] = (unsigned char)r1[1]; //write lenght of type 1

							break;
						case 2:
							//is not in table of types
							printf("ERROR WRONG CPTYPE 2\n");
							nob_cp = 2;
							break;
						case 3://integer
							nob_cp = 4;
							break;
						case 4://float
							nob_cp = 4;
							break;
						case 5://long
							nob_cp = 8;
							break;
						case 6://double
							nob_cp = 8;
							break;
						case 7://class
							nob_cp = 2;
							break;
						case 8://string
							nob_cp = 2;
							break;
						case 9://fieldref
							nob_cp = 4;
							break;
						case 10://methodref
							nob_cp = 4;
							break;
						case 11://interfacemethodref
							nob_cp = 4;
							break;
						case 12://nameandtype
							nob_cp = 4;
							break;

						default:
							printf("ERROR WRONG CPTYPE %d\n", cpType);
							nob_cp = 2;
						}
						if (myfile.is_open())
						{


							reader = new char[nob_cp];
							myfile.read(reader, nob_cp);

							for (int i = 1; i < nob_cp + 1; i++)
							{
								int x;
								if (cpType == 1) { x = i + 2; }
								else { x = i; }
								printf("%c", (unsigned char)reader[i - 1]);
								constPool[k][x] = (unsigned char)reader[i - 1];
							}
							printf("\n");
						}
					}

				}
				marker++;
				nob = 2;
				printCPool();
				break;
			case 5:  // access_flags

				access_flags = (unsigned int)(data[0] * 256 + data[1]);
				printf("access flags:%X\n", access_flags);
				nob = 2;
				marker++;
				break;
			case 6:  //this_class - reference to const_table (should be type 7)
					 //TODO safe
				nob = 2;
				marker++;
				break;
			case 7://super_class - reference to const_table (should be type 7)
				   //TODO safe
				nob = 2;
				marker++;
				break;
			case 8://interfaces_count
				interfaces_count = (int)(data[0] * 256 + data[1]);
				printf("interface count:%d\n", interfaces_count);
				nob = 0;
				marker++;
				break;
			case 9://interfaces[interfaces_count] - references to const pool

				for (int k = 0; k < interfaces_count; k++)
				{
					delete[]data;
					delete[]reader;
					if (myfile.is_open())
					{
						data = new unsigned char[2];
						reader = new char[2];
						myfile.read(reader, 2);
						for (int i = 0; i < 2; i++)
						{
							data[i] = (unsigned char)reader[i];
							printf("%X", data[i]);
						}
						printf("\n");

					}

				}
				marker++;
				nob = 2;
				break;
			case 10://fields_count
				fields_count = (int)(data[0] * 256 + data[1]);
				printf("fields count:%d\n", fields_count);
				nob = 0;
				marker++;
				break;
			case 11:// fields[fields_count]
					// load this:
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
				for (int k = 0; k < fields_count; k++)
				{
					delete[]data;
					delete[]reader;
					if (myfile.is_open())
					{
						data = new unsigned char[2];
						reader = new char[2];
						myfile.read(reader, 2);
						for (int i = 0; i < 2; i++)
						{
							data[i] = (unsigned char)reader[i];
							printf("%X", data[i]);
						}
						printf("\n");

					}

				}
				marker++;
				nob = 2;
				break;
			case 12:// methods_count
				methods_count = (int)(data[0] * 256 + data[1]);
				printf("methods count:%d\n", methods_count);
				nob = 0;
				marker++;
				break;
			case 13://methods[methods_count]
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
				for (int k = 0; k < methods_count; k++) //loading methods
				{
					int access_flags;
					int name_index;
					int descriptor_index;
					int attributes_count;
					delete[]data;
					delete[]reader;
					if (myfile.is_open())
					{
						data = new unsigned char[8];
						reader = new char[8];
						myfile.read(reader, 8);
						for (int i = 0; i < 8; i++)
						{
							data[i] = (unsigned char)reader[i];
							printf("%X", data[i]);
						}
						printf("\n");
						access_flags = (int)(data[0] * 256 + data[1]);
						name_index = (int)(data[2] * 256 + data[3]);
						descriptor_index = (int)(data[4] * 256 + data[5]);
						attributes_count = (int)(data[6] * 256 + data[7]);
						printf("access_flags:%d\n", access_flags);
						printf("name_index:%d\n", name_index);
						printf("descriptor_index:%d\n", descriptor_index);
						printf("attributes count:%d\n", attributes_count);
						for (int j = 0; j < attributes_count; j++) // loading atributes
						{
							int attribute_name_index;
							int attribute_length;
							delete[]data;
							delete[]reader;
							data = new unsigned char[6];
							reader = new char[6];
							myfile.read(reader, 6);
							for (int i = 0; i < 6; i++)
							{
								data[i] = (unsigned char)reader[i];
								printf("%X", data[i]);
							}
							printf("\n");
							attribute_name_index = (int)(data[0] * 256 + data[1]);
							attribute_length = (int)(data[2] * 256 * 256 * 256 + data[3] * 256 * 256 + data[4] * 256 + data[5]);
							printf("attribute_name_index:%d\n", attribute_name_index);
							printf("attribute lenght:%d\n", attribute_length);
							delete[]data;
							delete[]reader;
							data = new unsigned char[attribute_length];
							reader = new char[attribute_length];
							myfile.read(reader, attribute_length);
							for (int i = 0; i < attribute_length; i++)
							{
								data[i] = (unsigned char)reader[i];
								printf("%X", data[i]);
							}
							printf("\n");

						}
					}

				}
				marker++;
				nob = 2;
				break;
			case 14:// attributes_count
				attributes_count = (int)(data[0] * 256 + data[1]);
				printf("attributes count:%d\n", attributes_count);
				nob = 0;
				marker++;
				break;
			case 15://attributes[attributes_count]
					//attributes[attributes_count]
					//{
					//u2 attribute_name_index;
					//u4 attribute_length;
					//info[attribute_length]
					//{
					//[attribute data, see Table 16]
					//}
					//}
				for (int k = 0; k < attributes_count; k++) //loading methods
				{
					int attribute_name_index;
					int attribute_length;
					delete[]data;
					delete[]reader;
					if (myfile.is_open())
					{
						data = new unsigned char[6];
						reader = new char[6];
						myfile.read(reader, 6);
						for (int i = 0; i < 6; i++)
						{
							data[i] = (unsigned char)reader[i];
							printf("%X", data[i]);
						}
						printf("\n");
						attribute_name_index = (int)(data[0] * 256 + data[1]);
						attribute_length = (int)(data[2] * 256 * 256 * 256 + data[3] * 256 * 256 + data[4] * 256 + data[5]);
						printf("attribute_name_index:%d\n", attribute_name_index);
						printf("attribute lenght:%d\n", attribute_length);

						delete[]data;
						delete[]reader;
						data = new unsigned char[attribute_length];
						reader = new char[attribute_length];
						myfile.read(reader, attribute_length);
						for (int i = 0; i < attribute_length; i++)
						{
							data[i] = (unsigned char)reader[i];
							printf("%X", data[i]);
						}
						printf("\n");


					}

				}
				br = true;
			default:
				br = true;
			}
			delete[]data;
			delete[]reader;
		}

	}

	myfile.close();



	//u4             magic;
	//u2             minor_version;
	//u2             major_version;
	//u2             constant_pool_count;
	//cp_info        constant_pool[constant_pool_count - 1];
	//u2             access_flags;
	//u2             this_class;
	//u2             super_class;
	//u2             interfaces_count;
	//u2             interfaces[interfaces_count];
	//u2             fields_count;
	//field_info     fields[fields_count];
	//u2             methods_count;
	//method_info    methods[methods_count];
	//u2             attributes_count;
	//attribute_info attributes[attributes_count];
	return true;
}*/


ClassLoader::~ClassLoader()
{
	
}

