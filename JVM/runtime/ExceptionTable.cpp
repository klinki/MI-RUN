#include "ExceptionTable.h"

void ExceptionTable::setException(int index, int s_pc, int e_pc, int h_pc, int c_type)
{
	if (index < size)
	{
		start_pc[index] = s_pc;
		end_pc[index] = e_pc;
		handler_pc[index] = h_pc;
		catch_type[index] = c_type;
	}
	

}


ExceptionTable::ExceptionTable(int s)
{
	size = s;
}

ExceptionTable::ExceptionTable()
{
	size = 0;
}


ExceptionTable::~ExceptionTable()
{
}
