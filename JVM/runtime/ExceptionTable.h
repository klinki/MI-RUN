#pragma once
class ExceptionTable
{
private:

	int size;
	int *start_pc;
	int *end_pc;
	int *handler_pc;
	int *catch_type;


public:
	ExceptionTable();
	ExceptionTable(int s);
	void setException(int index, int s_pc, int e_pc, int h_pc, int c_type);
	
	~ExceptionTable();
};

