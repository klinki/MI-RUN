#include "ConstantPool.h"


ConstantPool::ConstantPool()
{
	constant_pool_count = 0;
}
ConstantPool::ConstantPool(int size)
{
	constant_pool_count = size;
	constPool = new unsigned char *[constant_pool_count];
	for (int i = 0; i < constant_pool_count; i++)
	{
		constPool[i] = new unsigned char[9];
	}
	//printf("%d\n", constant_pool_count);
}


ConstantPool::~ConstantPool()
{
	for (int i = 0; i < constant_pool_count; i++)
	{
		delete[] constPool[i];
	}
	delete[] constPool;
}
int ConstantPool::GetSize()
{
	return constant_pool_count;
}
int ConstantPool::add(int pos, unsigned char type, int length, unsigned char * data)
{
	delete[] constPool[pos];
	constPool[pos] = new unsigned char[9];
	if ((int)type == 1)
	{
		delete[] constPool[pos];
		constPool[pos] = new unsigned char [length+1];
		
	}
	printf("%d\n", pos);
	
	constPool[pos][0] = type;
	for (int i = 0; i < length; i++)
	{
			
		constPool[pos][i+1] = data[i];
		printf("%c", data[i]);
	}
	printf("\n\n");
	return 0;
}
unsigned char * ConstantPool::getElem(int pos)
{
	int l;
	return getElem(pos, l);
}
unsigned char * ConstantPool::getElem(int pos, int & length)
{
	//printf("pos:%d\n",pos);
	
	if (pos == 0 || pos > constant_pool_count)
	{
		return 0;
	}
	//printf("type:%d\n", (int)constPool[pos][0]);
	switch ((int)constPool[pos][0])
	{
	case 1:
		length = ((int)constPool[pos][1]) * 256 + ((int)constPool[pos][2]);
		break;
	case 3:
		length = 4;
		break;
	case 4:
		length = 4;
		break;
	case 5:
		length = 8;
		break;
	case 6:
		length = 8;
		break;
	case 7:
		length = 2;
		break;
	case 8:
		length = 2;
		break;
	case 9:
		length = 4;
		break;
	case 10:
		length = 4;
		break;
	case 11:
		length = 4;
		break;
	case 12:
		length = 4;
	default:
		length = 0;
		return 0;
	}
	
	unsigned char * ret = new unsigned char[length];
	for (int i = 0; i < length; i++)
	{
		if (constPool[pos][0]==1)
		{
			ret[i] = constPool[pos][i + 3];
		}
		else
		{
			ret[i] = constPool[pos][i + 1];
			
		}	
	}

	return ret;
}

void ConstantPool::print()
{
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


}
