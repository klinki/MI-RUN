#include "classloader.h"

using namespace std;

ClassLoader::ClassLoader()
{
}
bool ClassLoader::load(char * filename)
{	
	char * reader;
	unsigned char * data;
	int marker = 0;// says where we are 0- magic
	int constant_pool_count =1;
	int interfaces_count=0;
	int fields_count =0;
	int methods_count =0;
	int attributes_count =0;
	bool br = false;
	unsigned int access_flags;
	int nob = 4; //number of bytes to read
	ifstream myfile (filename, ios::in | ios::binary);
	
	while (!br)
	{
		if (myfile.is_open())
		{
			
			data = new unsigned char [nob];
			reader = new char[nob];
			myfile.read(reader,nob);
			for (int i = 0; i < nob; i++)
			{
				data[i] = (unsigned char)reader[i];
				printf("%X",data[i]);
			}
			printf("\n");	
		
			switch (marker)
			{
				case 0: //magic
					nob =2;
					marker++;				
					
					break;
				case 1:  //minor_version
					nob =2;
					marker++;
					break;
				case 2:  //major_version
					nob =2;
					marker++;
					break;
				case 3:  // constant_pool_count
					
					constant_pool_count = (int)(data[0]*256 + data[1]);
					printf("constant_pool_count:%d\n",constant_pool_count);
					nob =0;
					marker++;
					break;
				case 4: // constant_pool[constant_pool_count - 1]
					
					for (int k = 1; k < constant_pool_count; k++)
					{
						delete []data;
						delete []reader;
						if (myfile.is_open())
						{
							char r[1];
							myfile.read(r,1);
							int cpType=(int)((unsigned char)r[0]);
							int nob_cp;
							printf("entry:%d type:%d\n",k,cpType);
							
							switch (cpType)
							{
								
								case 1://utf8
									if (myfile.is_open())
									{
										char r1[2];
										myfile.read(r1,2);
										nob_cp=(int)(r1[0]*256 + r1[1]);
									}
									//TODO read rest
									break;
								case 2:
									//is not in table of types
									printf("ERROR WRONG CPTYPE 2\n");
									nob_cp=2;
									break;
								case 3://integer
									nob_cp=4;
									break;
								case 4://float
									nob_cp=4;
									break;
								case 5://long
									nob_cp=8;
									break;
								case 6://double
									nob_cp=8;
									break;
								case 7://class
									nob_cp=2;
									break;
								case 8://string
									nob_cp=2;
									break;
								case 9://fieldref
									nob_cp=4;
									break;
								case 10://methodref
									nob_cp=4;
									break;
								case 11://interfacemethodref
									nob_cp=4;
									break;
								case 12://nameandtype
									nob_cp=4;
									break;
								
								default:
									printf("ERROR WRONG CPTYPE %d\n",cpType);
									nob_cp=2;
							}
							if (myfile.is_open())
							{
								data = new unsigned char [nob_cp];
								reader = new char[nob_cp];
								myfile.read(reader,nob_cp);
								for (int i = 0; i < nob_cp; i++)
								{
									data[i] = (unsigned char)reader[i];
									printf("%c",data[i]);
								}
								printf("\n");
							}
						}
						
					}
					marker++;
					nob=2;
					break;
				case 5:  // access_flags
					
					access_flags = (unsigned int)(data[0]*256 + data[1]);
					printf("access flags:%X\n",access_flags);
					nob =2;
					marker++;
					break;
				case 6:  //this_class - reference to const_table (should be type 7)
					//TODO safe
					nob =2;
					marker++;
					break;
				case 7://super_class - reference to const_table (should be type 7)
					//TODO safe
					nob =2;
					marker++;
					break;
				case 8://interfaces_count
					interfaces_count = (int)(data[0]*256 + data[1]);
					printf("interface count:%d\n",interfaces_count);
					nob =0;
					marker++;
					break;
				case 9://interfaces[interfaces_count] - references to const pool
					
					for (int k = 0; k < interfaces_count; k++)
					{
						delete []data;
						delete []reader;
						if (myfile.is_open())
						{
							data = new unsigned char [2];
							reader = new char[2];
							myfile.read(reader,2);
							for (int i = 0; i < 2; i++)
							{
								data[i] = (unsigned char)reader[i];
								printf("%X",data[i]);
							}
							printf("\n");
							
						}
						
					}
					marker++;
					nob=2;
					break;
				case 10://fields_count
					fields_count = (int)(data[0]*256 + data[1]);
					printf("fields count:%d\n",fields_count);
					nob =0;
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
						delete []data;
						delete []reader;
						if (myfile.is_open())
						{
							data = new unsigned char [2];
							reader = new char[2];
							myfile.read(reader,2);
							for (int i = 0; i < 2; i++)
							{
								data[i] = (unsigned char)reader[i];
								printf("%X",data[i]);
							}
							printf("\n");
							
						}
						
					}
					marker++;
					nob=2;
					break;
				case 12:// methods_count
					methods_count = (int)(data[0]*256 + data[1]);
					printf("methods count:%d\n",methods_count);
					nob =0;
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
						delete []data;
						delete []reader;
						if (myfile.is_open())
						{
							data = new unsigned char [8];
							reader = new char[8];
							myfile.read(reader,8);
							for (int i = 0; i < 8; i++)
							{
								data[i] = (unsigned char)reader[i];
								printf("%X",data[i]);
							}
							printf("\n");
							access_flags = (int)(data[0]*256 + data[1]);
							name_index = (int)(data[2]*256 + data[3]);
							descriptor_index = (int)(data[4]*256 + data[5]);
							attributes_count = (int)(data[6]*256 + data[7]);
							printf("access_flags:%d\n",access_flags);
							printf("name_index:%d\n",name_index);
							printf("descriptor_index:%d\n",descriptor_index);
							printf("attributes count:%d\n",attributes_count);
							for (int j = 0; j < attributes_count; j++) // loading atributes
							{
								int attribute_name_index;
								int attribute_length;
								delete []data;
								delete []reader;
								data = new unsigned char [6];
								reader = new char[6];
								myfile.read(reader,6);
								for (int i = 0; i < 6; i++)
								{
									data[i] = (unsigned char)reader[i];
									printf("%X",data[i]);
								}
								printf("\n");
								attribute_name_index = (int)(data[0]*256 + data[1]);
								attribute_length = (int)(data[2]*256*256*256 + data[3]*256*256 + data[4]*256 + data[5]);
								printf("attribute_name_index:%d\n",attribute_name_index);
								printf("attribute lenght:%d\n",attribute_length);
								delete []data;
								delete []reader;
								data = new unsigned char [attribute_length];
								reader = new char[attribute_length];	
								myfile.read(reader,attribute_length);
								for (int i = 0; i < attribute_length; i++)
								{
									data[i] = (unsigned char)reader[i];
									printf("%X",data[i]);
								}
								printf("\n");
								
							}
						}
						
					}
					marker++;
					nob=2;
					break;
				case 14:// attributes_count
					attributes_count = (int)(data[0]*256 + data[1]);
					printf("attributes count:%d\n",attributes_count);
					nob =0;
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
						delete []data;
						delete []reader;
						if (myfile.is_open())
						{
							data = new unsigned char [6];
							reader = new char[6];
							myfile.read(reader,6);
							for (int i = 0; i < 6; i++)
							{
								data[i] = (unsigned char)reader[i];
								printf("%X",data[i]);
							}
							printf("\n");
							attribute_name_index = (int)(data[0]*256 + data[1]);
							attribute_length = (int)(data[2]*256*256*256 + data[3]*256*256 + data[4]*256 + data[5]);
							printf("attribute_name_index:%d\n",attribute_name_index);
							printf("attribute lenght:%d\n",attribute_length);
							
							delete []data;
							delete []reader;
							data = new unsigned char [attribute_length];
							reader = new char[attribute_length];	
							myfile.read(reader,attribute_length);
							for (int i = 0; i < attribute_length; i++)
							{
								data[i] = (unsigned char)reader[i];
								printf("%X",data[i]);
							}
							printf("\n");
								
							
						}
						
					}
					br=true;
				default:
					br=true;
			}
			delete []data;
			delete []reader;		
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
}


ClassLoader::~ClassLoader()
{
}

