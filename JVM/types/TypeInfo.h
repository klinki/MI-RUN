#pragma once
#include "Access.h"
#include "ConstantPool.h"

typedef ConstantPoolAddress u2;
typedef unsigned int u4;
typedef unsigned char u1;
typedef field_info method_info;


struct field_info
{
	Access access_flags;
	ConstantPoolAddress name_index;
	ConstantPoolAddress descriptor_index;
	unsigned short attributes_count;
	attribute_info attributes[1]; // actual = attributes_count
};


struct attribute_info
{
	ConstantPoolAddress attribute_name_index;
	unsigned int attribute_length;
	unsigned char info[1]; // actual = attribute_length
};

struct ConstantValue_attribute
{
	ConstantPoolAddress attribute_name_index;
	unsigned int attribute_length;
	ConstantPoolAddress constantvalue_index;
};

struct Code_attribute
{
	ConstantPoolAddress attribute_name_index;
	unsigned int attribute_length;
	unsigned short max_stack;
	unsigned short max_locals;
	unsigned int code_length;
	unsigned char code[1]; // actual - code length
	unsigned char exception_table_length;
	ExceptionTableItem exception_table[1]; // actual - exception table length
	unsigned short attributes_count;
	attribute_info attributes[1]; // actual - attributes count
};

struct ExceptionTableItem
{
	unsigned short start_pc;
	unsigned short end_pc;
	unsigned short handler_pc;
	ConstantPoolAddress catch_type;
};

struct StackMapTable_attribute
{
	ConstantPoolAddress attribute_name_index;
	unsigned int   attribute_length;
	unsigned short number_of_entries;
	stack_map_frame entries[1]; // actual - number of entries
};

enum StackFrameType
{
	SAME = 0, // 0 - 63
	SAME_LOCALS_1_STACK_ITEM = 64, // 64 - 127
	__RESERVED__ = 128, // 128 - 246
	SAME_LOCALS_1_STACK_ITEM_EXTENDED = 247,
	CHOP = 248, // 248 - 250
	SAME_FRAME_EXTENDED = 251,
	APPEND = 252, // 252 - 254
	FULL_FRAME = 255
};

union stack_map_frame
{
	same_frame sameFrame;
	same_locals_1_stack_item_frame sameLocals;
	same_locals_1_stack_item_frame_extended sameLocalsExtended;
	chop_frame chopFrame;
	same_frame_extended sameFrameExtended;
	append_frame appendFrame;
	full_frame fullFrame;
};

struct same_frame
{
	StackFrameType frame_type = SAME; /* 0-63 */
};

struct same_locals_1_stack_item_frame 
{
	StackFrameType frame_type = SAME_LOCALS_1_STACK_ITEM; /* 64-127 */
	verification_type_info stack[1];
};

struct same_locals_1_stack_item_frame_extended 
{
	StackFrameType frame_type = SAME_LOCALS_1_STACK_ITEM_EXTENDED; /* 247 */
	unsigned short offset_delta;
	verification_type_info stack[1];
};

struct chop_frame 
{
	StackFrameType frame_type = CHOP; /* 248-250 */
	unsigned short offset_delta;
};

struct same_frame_extended 
{
	StackFrameType frame_type = SAME_FRAME_EXTENDED; /* 251 */
	unsigned short offset_delta;
};

struct append_frame 
{
	StackFrameType frame_type = APPEND; /* 252-254 */
	unsigned short offset_delta;
	verification_type_info locals[1]; // actual - frame_type - 251
};

struct full_frame 
{
	StackFrameType frame_type = FULL_FRAME; /* 255 */
	unsigned short offset_delta;
	unsigned short number_of_locals;
	verification_type_info locals[1]; // actual - number of locals
	unsigned short number_of_stack_items;
	verification_type_info stack[1]; // actual - number of stack items
};


union verification_type_info 
{
	Top_variable_info topVariableInfo;
	Integer_variable_info integerVariableInfo;
	Float_variable_info floatVariableInfo;
	Long_variable_info longVariableInfo;
	Double_variable_info doubleVariableInfo;
	Null_variable_info nullVariableInfo;
	UninitializedThis_variable_info uninitializedThisVariableInfo;
	Object_variable_info objectVariableInfo;
	Uninitialized_variable_info uninitializedVariableInfo;
};

enum VerificationItemType
{
	ITEM_Top = 0,
	ITEM_Integer = 1,
	ITEM_Float = 2,
	ITEM_Double = 3,
	ITEM_Long = 4,
	ITEM_Null = 5,
	ITEM_UninitializedThis = 6,
	ITEM_Object = 7,
	ITEM_Uninitialized = 8
};

struct Top_variable_info 
{
	VerificationItemType tag = ITEM_Top; /* 0 */
};

struct Integer_variable_info 
{
	VerificationItemType tag = ITEM_Integer; /* 1 */
};

struct Float_variable_info 
{
	VerificationItemType tag = ITEM_Float; /* 2 */
};

struct Double_variable_info 
{
	VerificationItemType tag = ITEM_Double; /* 3 */
};

struct Long_variable_info 
{
	VerificationItemType tag = ITEM_Long; /* 4 */
};

struct Null_variable_info 
{
	VerificationItemType tag = ITEM_Null; /* 5 */
};

struct UninitializedThis_variable_info 
{
	VerificationItemType tag = ITEM_UninitializedThis; /* 6 */
};

struct Object_variable_info 
{
	VerificationItemType tag = ITEM_Object; /* 7 */
	ConstantPoolAddress cpool_index;
};


struct Uninitialized_variable_info
{
	VerificationItemType tag = ITEM_Uninitialized; /* 8 */
	unsigned short offset;
};

struct Exceptions_attribute 
{
	ConstantPoolAddress attribute_name_index;
	unsigned int attribute_length;
	unsigned short number_of_exceptions;
	ConstantPoolAddress exception_index_table[1]; // actual number of exceptions
};

struct InnerClasses_attribute
{
	ConstantPoolAddress attribute_name_index;
	unsigned int attribute_length;
	unsigned short number_of_classes;
	InnerOuterClassInfo classes[1]; // actual number of classes
};

struct InnerOuterClassInfo
{
	ConstantPoolAddress inner_class_info_index;
	ConstantPoolAddress outer_class_info_index;
	ConstantPoolAddress inner_name_index;
	Access inner_class_access_flags;
};

struct EnclosingMethod_attribute
{
	ConstantPoolAddress attribute_name_index;
	unsigned int attribute_length;
	ConstantPoolAddress class_index;
	ConstantPoolAddress method_index;
};

struct Synthetic_attribute 
{
	ConstantPoolAddress attribute_name_index;
	unsigned int attribute_length;
};

struct Signature_attribute
{
	ConstantPoolAddress attribute_name_index;
	unsigned int attribute_length;
	ConstantPoolAddress signature_index;
};

struct SourceFile_attribute{
	ConstantPoolAddress attribute_name_index;
	unsigned int attribute_length;
	ConstantPoolAddress sourcefile_index;
};

struct SourceDebugExtension_attribute
{
	u2 attribute_name_index;
	u4 attribute_length;
	u1 debug_extension[1]; // actual attribute_length
};

struct LineNumberTable_attribute{
	u2 attribute_name_index;
	u4 attribute_length;
	u2 line_number_table_length;
	LineNumberItem line_number_table[1]; // actual line number table length
};

struct LineNumberItem
{
	u2 start_pc;
	u2 line_number;
};

struct LocalVariableTable_attribute
{
	u2 attribute_name_index;
	u4 attribute_length;
	u2 local_variable_table_length;
	LocalVariableInfo local_variable_table[1]; // actual local variable table length
};

struct LocalVariableInfo
{
	u2 start_pc;
	u2 length;
	u2 name_index;
	u2 descriptor_index;
	u2 index;
};


struct LocalVariableTypeTable_attribute
{
	u2 attribute_name_index;
	u4 attribute_length;
	u2 local_variable_type_table_length;
	LocalVariableInfo local_variable_type_table[1]; // actual local variable table length
};

struct Deprecated_attribute
{
	u2 attribute_name_index;
	u4 attribute_length;
};

struct RuntimeVisibleAnnotations_attribute
{
	u2         attribute_name_index;
	u4         attribute_length;
	u2         num_annotations;
	annotation annotations[1]; // actual ...
};

struct annotation
{
	u2 type_index;
	u2 num_element_value_pairs;
	AnnotationInfo element_value_pairs[1]; // actual ...
};

struct AnnotationInfo
{
	u2 element_name_index;
	element_value value;
};

struct element_value
{
	u1 tag;
	union {
		u2 const_value_index;
		ConstNameIndexPair enum_const_value;
		u2 class_info_index;
		annotation annotation_value;
		AnnotationElements array_value;
	} value;
};

struct ConstNameIndexPair
{
	u2 type_name_index;
	u2 const_name_index;
};

struct AnnotationElements
{
	u2            num_values;
	element_value values[1]; // actual ...
};

