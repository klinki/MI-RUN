#pragma once
typedef const unsigned short FLAG;

static FLAG ACC_PUBLIC			= 0x0001;
static FLAG ACC_PRIVATE			= 0x0002;
static FLAG ACC_PROTECTED		= 0x0004;
static FLAG ACC_STATIC			= 0x0008;
static FLAG ACC_FINAL			= 0x0010;
static FLAG ACC_SUPER			= 0x0020;
static FLAG ACC_SYNCHRONIZED	= 0x0020; // too bad, duplicate
static FLAG ACC_VOLATILE		= 0x0040;
static FLAG ACC_BRIDGE			= 0x0040;
static FLAG ACC_TRANSIENT		= 0x0080;
static FLAG ACC_VARARGS			= 0x0080;
static FLAG ACC_NATIVE			= 0x0100;
static FLAG ACC_INTERFACE		= 0x0200;
static FLAG ACC_ABSTRACT		= 0x0400;
static FLAG ACC_STRICT			= 0x0800;
static FLAG ACC_SYNTHETIC		= 0x1000;
static FLAG ACC_ANNOTATION		= 0x2000;
static FLAG ACC_ENUM			= 0x4000;

enum class AccessFlags
{
	PUBLIC = ACC_PUBLIC,
	PRIVATE = ACC_PRIVATE,
	PROTECTED = ACC_PROTECTED,
	STATIC = ACC_STATIC,
	FINAL = ACC_FINAL,
	SUPER = ACC_SUPER,
	VOLATILE = ACC_VOLATILE,
	TRANSIENT = ACC_TRANSIENT,
	INTERFACE = ACC_INTERFACE,
	ABSTRACT = ACC_ABSTRACT,
	SYNTHETIC = ACC_SYNTHETIC,
	ANNOTATION = ACC_ANNOTATION,
	ENUM = ACC_ENUM
};

enum class FieldAccessFlags
{
	PUBLIC = ACC_PUBLIC,
	PRIVATE = ACC_PRIVATE,
	PROTECTED = ACC_PROTECTED,
	STATIC = ACC_STATIC,
	FINAL = ACC_FINAL,
	VOLATILE = ACC_VOLATILE,
	TRANSIENT = ACC_TRANSIENT,
	SYNTHETIC = ACC_SYNTHETIC,
	ENUM = ACC_ENUM
};

enum class MethodAccessFlags
{
	PUBLIC = ACC_PUBLIC,
	PRIVATE = ACC_PRIVATE,
	PROTECTED = ACC_PROTECTED,
	STATIC = ACC_STATIC,
	FINAL = ACC_FINAL,
	SYNCHRONIZED = ACC_SYNCHRONIZED,
	BRIDGE = ACC_BRIDGE,
	VARGARGS = ACC_VARARGS,
	NATIVE = ACC_NATIVE,
	ABSTRACT = ACC_ABSTRACT,
	STRICT = 0x0800,
	SYNTHETIC = ACC_SYNTHETIC
};

enum class ClassAccessFlags
{
	PUBLIC = ACC_PUBLIC,
	FINAL = ACC_FINAL,
	SUPER = ACC_SUPER,
	INTERFACE = ACC_INTERFACE,
	ABSTRACT = ACC_ABSTRACT,
	SYNTHETIC = ACC_SYNTHETIC,
	ANNOTATION = ACC_ANNOTATION,
	ENUM = ACC_ENUM
};

enum class NestedClassAccessFlags
{
	PUBLIC = ACC_PUBLIC,
	PRIVATE = ACC_PRIVATE,
	PROTECTED = ACC_PROTECTED,
	STATIC = ACC_STATIC,
	FINAL = ACC_FINAL,
	INTERFACE = ACC_INTERFACE,
	ABSTRACT = ACC_ABSTRACT,
	SYNTHETIC = ACC_SYNTHETIC,
	ANNOTATION = ACC_ANNOTATION,
	ENUM = ACC_ENUM
};
