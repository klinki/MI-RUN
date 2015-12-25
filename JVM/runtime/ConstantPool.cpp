#include "ConstantPool.h"


ConstantPool::ConstantPool()
{
	constant_pool_count = 0;
}
ConstantPool::ConstantPool(int size)
{
	constant_pool_count = size;

	constantPool = new ConstantPoolItem[size];
	/*
	constPool = new unsigned char *[constant_pool_count];
	for (int i = 0; i < constant_pool_count; i++)
	{
		constPool[i] = new unsigned char[9];
	}
	//printf("%d\n", constant_pool_count);
	*/
}


ConstantPool::~ConstantPool()
{
	/*
	for (int i = 0; i < constant_pool_count; i++)
	{
		delete[] constPool[i];
	}
	delete[] constPool;
	*/
	delete[] constantPool;
}


int ConstantPool::GetSize()
{
	return constant_pool_count;
}
int ConstantPool::add(int pos, int type, int length, unsigned char * data)
{
	//printf("zapis %d\n",type);
	switch (type)
	{
	case ConstantPoolTag::CONSTANT_Class:{//class
		unsigned short index = (unsigned short)(data[0] * 256 + data[1]);
		ConstantPoolItem spi(ConstantPoolTag::CONSTANT_Class);
		spi.classInfo = CONSTANT_Class_info(index);
		constantPool[pos] = spi;
		break;
	}
	case ConstantPoolTag::CONSTANT_Fieldref: {//field ref
		unsigned short i1 = (unsigned short)(data[0] * 256 + data[1]);
		unsigned short i2 = (unsigned short)(data[2] * 256 + data[3]);
		ConstantPoolItem spi(ConstantPoolTag::CONSTANT_Fieldref);
		spi.fieldInfo = CONSTANT_Fieldref_info(i1, i2);
		constantPool[pos] = spi;
		break;}
	case ConstantPoolTag::CONSTANT_Methodref: {//method ref
		unsigned short i1 = (unsigned short)(data[0] * 256 + data[1]);
		unsigned short i2 = (unsigned short)(data[2] * 256 + data[3]);
		ConstantPoolItem spi(ConstantPoolTag::CONSTANT_Methodref);
		spi.methodInfo = CONSTANT_Methodref_info(i1, i2);
		constantPool[pos] = spi;
		break;}
	case ConstantPoolTag::CONSTANT_InterfaceMethodref: {//interface method ref
		unsigned short i1 = (unsigned short)(data[0] * 256 + data[1]);
		unsigned short i2 = (unsigned short)(data[2] * 256 + data[3]);
		ConstantPoolItem spi(ConstantPoolTag::CONSTANT_InterfaceMethodref);
		spi.interfaceMethodInfo = CONSTANT_InterfaceMethodref_info(i1, i2);
		constantPool[pos] = spi;
		break;}
	case ConstantPoolTag::CONSTANT_String: {//string
		unsigned short i1 = (unsigned short)(data[0] * 256 + data[1]);
		ConstantPoolItem spi(ConstantPoolTag::CONSTANT_String);
		spi.stringInfo = CONSTANT_String_info(i1);
		constantPool[pos] = spi;
		break;}
	case ConstantPoolTag::CONSTANT_Integer: {//integer
		int v = (int)(data[0] * 256 * 256 * 256 + data[1] * 256 * 256 + data[2] * 256 + data[3]);
		ConstantPoolItem spi(ConstantPoolTag::CONSTANT_Integer);
		spi.integerInfo = CONSTANT_Integer_info(v);
		constantPool[pos] = spi;
		break;}
	case ConstantPoolTag::CONSTANT_Float: {//float
		/*  TODO float value:  If bits is 0x7f800000, the float value will be positive infinity.

			If bits is 0xff800000, the float value will be negative infinity.

			If bits is in the range 0x7f800001 through 0x7fffffff or in the range 0xff800001 through 0xffffffff, the float value will be NaN.

			In all other cases, let s, e, and m be three values that might be computed from bits:

			int s = ((bits >> 31) == 0) ? 1 : -1;
			int e = ((bits >> 23) & 0xff);
			int m = (e == 0) ?
					  (bits & 0x7fffff) << 1 :
					  (bits & 0x7fffff) | 0x800000;


		Then the float value equals the result of the mathematical expression s � m � 2e-150*/
		float v = (float)(data[0] * 256 * 256 * 256 + data[1] * 256 * 256 + data[2] * 256 + data[3]);
		ConstantPoolItem spi(ConstantPoolTag::CONSTANT_Float);
		spi.floatInfo = CONSTANT_Float_info(v);
		constantPool[pos] = spi;
		break;}
	case  ConstantPoolTag::CONSTANT_Long: {//long // TODO value
		int v1 = (int)(data[0] * 256 * 256 * 256 + data[1] * 256 * 256 + data[2] * 256 + data[3]);
		int v2 = (int)(data[4] * 256 * 256 * 256 + data[5] * 256 * 256 + data[6] * 256 + data[7]);
		ConstantPoolItem spi(ConstantPoolTag::CONSTANT_Long);
		spi.longInfo = CONSTANT_Long_info(v1, v2);
		constantPool[pos] = spi;
		break;}
	case  ConstantPoolTag::CONSTANT_Double: {//double // TODO value
		int v1 = (int)(data[0] * 256 * 256 * 256 + data[1] * 256 * 256 + data[2] * 256 + data[3]);
		int v2 = (int)(data[4] * 256 * 256 * 256 + data[5] * 256 * 256 + data[6] * 256 + data[7]);
		ConstantPoolItem spi(ConstantPoolTag::CONSTANT_Double);
		spi.doubleInfo = CONSTANT_Double_info(v1, v2);
		constantPool[pos] =spi;
		break;}
	case  ConstantPoolTag::CONSTANT_NameAndType: {//nameandtype
		unsigned short i1 = (unsigned short)(data[0] * 256 + data[1]);
		unsigned short i2 = (unsigned short)(data[2] * 256 + data[3]);
		ConstantPoolItem spi(ConstantPoolTag::CONSTANT_NameAndType);
		spi.nameAndTypeInfo = CONSTANT_NameAndType_info(i1, i2);
		constantPool[pos] = spi;
		break;}
	case  ConstantPoolTag::CONSTANT_Utf8: {//utf8
		ConstantPoolItem spi(ConstantPoolTag::CONSTANT_Utf8);
		spi.utf8Info = CONSTANT_Utf8_info((unsigned short)length, data);
		constantPool[pos] = spi;
		break;}
	case  ConstantPoolTag::CONSTANT_MethodHandle: {//methodhandle
		unsigned short i1 = (unsigned short)(data[0]);
		ReferenceType rt;
		switch (i1)
		{
		case 1: rt = REF_getField;break;
		case 2:	rt = REF_getStatic;break;
		case 3:	rt = REF_putField;break;
		case 4:	rt = REF_putStatic;break;
		case 5:	rt = REF_invokeVirtual;break;
		case 6:	rt = REF_invokeStatic;break;
		case 7:	rt = REF_invokeSpecial;break;
		case 8:	rt = REF_newInvokeSpecial;break;
		case 9:	rt = REF_invokeInterface;break;
		default:
			printf("ERROR wrong method ref type\n");
			return -1;
		}
		unsigned short i2 = (unsigned short)(data[1] * 256 + data[2]);
		ConstantPoolItem spi(ConstantPoolTag::CONSTANT_MethodHandle);
		spi.methodHandleInfo = CONSTANT_MethodHandle_info(rt, i2);
		constantPool[pos] = spi;
		break;}
	case  ConstantPoolTag::CONSTANT_MethodType: {//methodtype
		unsigned short i1 = (unsigned short)(data[0] * 256 + data[1]);
		ConstantPoolItem spi(ConstantPoolTag::CONSTANT_MethodType);
		spi.methodTypeInfo = CONSTANT_MethodType_info(i1);
		constantPool[pos] = spi;
		break;}
	case  ConstantPoolTag::CONSTANT_InvokeDynamic: {//invokedynamic
		unsigned short i1 = (unsigned short)(data[0] * 256 + data[1]);
		unsigned short i2 = (unsigned short)(data[2] * 256 + data[3]);
		ConstantPoolItem spi(ConstantPoolTag::CONSTANT_InvokeDynamic);
		spi.invokeDynamicInfo = CONSTANT_InvokeDynamic_info(i1, i2);
		constantPool[pos] = spi;
		break;}
	default:
		printf("ERROR Constant pool unknown tag %d", type);
		return -1;
	}
	int i = pos;
	
	return 0;
}

ConstantPoolItem *ConstantPool::get(int index)
{
	return & constantPool[index];
}

void ConstantPool::print()
{
 for (int i = 1; i < constant_pool_count; i++)
	{
		printf("%d: t%d ", i, constantPool[i].tag);
		ConstantPoolItem * cpi;
		//cpi = this->get(i);
		
		switch (constantPool[i].tag)
		{
		case CONSTANT_Class: //class
			printf("class name_index:%d ", constantPool[i].classInfo.name_index);
			break;
		case CONSTANT_Fieldref: //field ref
			printf("field class_index:%d ", constantPool[i].fieldInfo.class_index);
			printf(" name_and_type_index:%d ", constantPool[i].fieldInfo.name_and_type_index);
			break;
		case CONSTANT_Methodref: //method ref
			printf("method class_index:%d ", constantPool[i].methodInfo.class_index);
			printf(" name_and_type_index:%d ", constantPool[i].methodInfo.name_and_type_index);
			break;
		case CONSTANT_InterfaceMethodref://interface method ref
			printf("interface class_index:%d ", constantPool[i].interfaceMethodInfo.class_index);
			printf(" name_and_type_index:%d ", constantPool[i].interfaceMethodInfo.name_and_type_index);
			break;
		case CONSTANT_String: //string
			printf("string string_index:%d ", constantPool[i].stringInfo.string_index);
			break;
		case CONSTANT_Integer: //integer
			printf("integer value:%d ", constantPool[i].integerInfo.value);
			break;
		case CONSTANT_Float: //float
			printf("float value:%f ", constantPool[i].floatInfo.value);
			break;
		case CONSTANT_Long: //long 
			printf("long high_bytes:%d ", constantPool[i].longInfo.high_bytes);
			printf(" low_bytes:%d ", constantPool[i].longInfo.low_bytes);
			i++;
			break;
		case CONSTANT_Double: //double 
			printf("double high_bytes:%d ", constantPool[i].doubleInfo.high_bytes);
			printf(" low_bytes:%d ", constantPool[i].doubleInfo.low_bytes);
			i++;
			break;
		case CONSTANT_NameAndType: //nameandtype
			printf("nameandtype name_index:%d ", constantPool[i].nameAndTypeInfo.name_index);
			printf(" descriptor_index:%d ", constantPool[i].nameAndTypeInfo.descriptor_index);
			
			break;
		case CONSTANT_Utf8://utf8
			for (int k = 0; k < constantPool[i].utf8Info.length;k++)
			{
				printf("%c", constantPool[i].utf8Info.bytes[k]);
			}
			
			break;
		case CONSTANT_MethodHandle: //methodhandle
			printf("methodHandleInfo reference_kind:%d ", constantPool[i].methodHandleInfo.reference_kind);
			printf(" reference_index:%d ", constantPool[i].methodHandleInfo.reference_index);
			break;
		case CONSTANT_MethodType: //methodtype
			printf("methodTypeInfo descriptor_index:%d ", constantPool[i].methodTypeInfo.descriptor_index);
			break;
		case CONSTANT_InvokeDynamic: //invokedynamic
			printf("invokeDynamicInfo bootstrap_method_attr_index:%d ", constantPool[i].invokeDynamicInfo.bootstrap_method_attr_index);
			printf("name_and_type_index:%d ", constantPool[i].invokeDynamicInfo.name_and_type_index);
			break;
		default:
			printf("ERROR Constant pool unknown tag \n");
		}
		printf("\n");
		
	}

	/*
	for (int i = 1; i < constant_pool_count; i++)
	{
		int type = (int)(constPool[i][0]);
		printf("%d: ", i);
		printf("t:%d ", type);
		int max;
		int k = 1;
		switch (type)
		{
		case 1:
			max = ((int)constPool[i][1]) * 256 + ((int)constPool[i][2]) + 2;
			k = 3;
			break;
		case 3:
			max = 4;
			break;
		case 4:
			max = 4;
			break;
		case 5:
			max = 8;
			break;
		case 6:
			max = 8;
			break;
		case 7:
			max = 2;
			break;
		case 8:
			max = 2;
			break;
		case 9:
			max = 4;
			break;
		case 10:
			max = 4;
			break;
		case 11:
			max = 4;
			break;
		case 12:
			max = 4;
		default:
			max = 0;
		}

		for (; k < max + 1; k++)
		{
			if (type != 1)
			{
				printf("%X", constPool[i][k]);
			}
			else
			{
				printf("%c", constPool[i][k]);
			}
		}
		printf("\n");
	}
	*/

}

void ConstantPool::resolveStringRef()
{
	for (int i = 1;	i < this->constant_pool_count; i++)
	{
		if (this->constantPool[i].tag == 8)
		{
			this->constantPool[i].stringInfo.value = new Utf8String(constantPool[this->constantPool[i].stringInfo.string_index].utf8Info.bytes, constantPool[this->constantPool[i].stringInfo.string_index].utf8Info.length);
		}
	}

}


void ConstantPool::setClassPtr(int index, Class * c)
{
	switch (constantPool[index].tag)
	{
	case ConstantPoolTag::CONSTANT_Class:
		constantPool[index].classInfo.classPtr = c;
		break;
	case ConstantPoolTag::CONSTANT_Fieldref:
		constantPool[index].fieldInfo.classPtr = c;
		break;
	case ConstantPoolTag::CONSTANT_Methodref:
		constantPool[index].methodInfo.classPtr = c;
		break;
	case ConstantPoolTag::CONSTANT_InterfaceMethodref:
		constantPool[index].interfaceMethodInfo.classPtr = c;
		break;

	default:
		break;
	}
}
void ConstantPool::setFieldPtr(int index, Field * f)
{
	if (constantPool[index].tag == 9)
	{
		constantPool[index].fieldInfo.fieldPtr = f;
	}
}

void ConstantPool::setMethodPtr(int index, Method * m)
{
	if (constantPool[index].tag == 10)
	{
		constantPool[index].methodInfo.methodPtr = m;
	}
	else if (constantPool[index].tag == 11)
	{
		constantPool[index].interfaceMethodInfo.methodPtr = m;
	}
}
