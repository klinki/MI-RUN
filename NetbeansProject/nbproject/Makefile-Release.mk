#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/4ea214d7/ClassLoader.o \
	${OBJECTDIR}/_ext/ad04863/BakerGc.o \
	${OBJECTDIR}/_ext/882d2459/GarbageCollector.o \
	${OBJECTDIR}/_ext/882d2459/Heap.o \
	${OBJECTDIR}/_ext/fd398b1c/Marker.o \
	${OBJECTDIR}/_ext/882d2459/ObjectTable.o \
	${OBJECTDIR}/_ext/882d2459/TreadMillGc.o \
	${OBJECTDIR}/_ext/511da3b2/main.o \
	${OBJECTDIR}/_ext/7bec1df/helpers.o \
	${OBJECTDIR}/_ext/cee7f803/PrintStream.o \
	${OBJECTDIR}/_ext/b4cb398b/Exception.o \
	${OBJECTDIR}/_ext/b4cb398b/Object.o \
	${OBJECTDIR}/_ext/b4cb398b/String.o \
	${OBJECTDIR}/_ext/b4cb398b/StringBuilder.o \
	${OBJECTDIR}/_ext/b4cb398b/System.o \
	${OBJECTDIR}/_ext/b4cb398b/Throwable.o \
	${OBJECTDIR}/_ext/7bec1df/natives.o \
	${OBJECTDIR}/_ext/fd28de7b/Class.o \
	${OBJECTDIR}/_ext/fd28de7b/ClassMap.o \
	${OBJECTDIR}/_ext/fd28de7b/ConstantPool.o \
	${OBJECTDIR}/_ext/fd28de7b/ExceptionTable.o \
	${OBJECTDIR}/_ext/fd28de7b/ExecutionEngine.o \
	${OBJECTDIR}/_ext/fd28de7b/Method.o \
	${OBJECTDIR}/_ext/fd28de7b/MethodArea.o \
	${OBJECTDIR}/_ext/fd28de7b/MethodFrame.o \
	${OBJECTDIR}/_ext/fd28de7b/OperandStack.o \
	${OBJECTDIR}/_ext/fdfbb3dc/Descriptors.o \
	${OBJECTDIR}/_ext/fe076c14/ArgumentsParser.o \
	${OBJECTDIR}/_ext/fe076c14/Utf8String.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/netbeansproject

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/netbeansproject: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/netbeansproject ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/4ea214d7/ClassLoader.o: ../JVM/classfile/ClassLoader.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/4ea214d7
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/4ea214d7/ClassLoader.o ../JVM/classfile/ClassLoader.cpp

${OBJECTDIR}/_ext/ad04863/BakerGc.o: ../JVM/gc/Baker/BakerGc.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/ad04863
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/ad04863/BakerGc.o ../JVM/gc/Baker/BakerGc.cpp

${OBJECTDIR}/_ext/882d2459/GarbageCollector.o: ../JVM/gc/GarbageCollector.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/882d2459
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/882d2459/GarbageCollector.o ../JVM/gc/GarbageCollector.cpp

${OBJECTDIR}/_ext/882d2459/Heap.o: ../JVM/gc/Heap.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/882d2459
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/882d2459/Heap.o ../JVM/gc/Heap.cpp

${OBJECTDIR}/_ext/fd398b1c/Marker.o: ../JVM/gc/MS/Marker.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/fd398b1c
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/fd398b1c/Marker.o ../JVM/gc/MS/Marker.cpp

${OBJECTDIR}/_ext/882d2459/ObjectTable.o: ../JVM/gc/ObjectTable.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/882d2459
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/882d2459/ObjectTable.o ../JVM/gc/ObjectTable.cpp

${OBJECTDIR}/_ext/882d2459/TreadMillGc.o: ../JVM/gc/TreadMillGc.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/882d2459
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/882d2459/TreadMillGc.o ../JVM/gc/TreadMillGc.cpp

${OBJECTDIR}/_ext/511da3b2/main.o: ../JVM/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/511da3b2
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511da3b2/main.o ../JVM/main.cpp

${OBJECTDIR}/_ext/7bec1df/helpers.o: ../JVM/natives/helpers.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/7bec1df
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7bec1df/helpers.o ../JVM/natives/helpers.cpp

${OBJECTDIR}/_ext/cee7f803/PrintStream.o: ../JVM/natives/java/io/PrintStream.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/cee7f803
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/cee7f803/PrintStream.o ../JVM/natives/java/io/PrintStream.cpp

${OBJECTDIR}/_ext/b4cb398b/Exception.o: ../JVM/natives/java/lang/Exception.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/b4cb398b
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/b4cb398b/Exception.o ../JVM/natives/java/lang/Exception.cpp

${OBJECTDIR}/_ext/b4cb398b/Object.o: ../JVM/natives/java/lang/Object.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/b4cb398b
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/b4cb398b/Object.o ../JVM/natives/java/lang/Object.cpp

${OBJECTDIR}/_ext/b4cb398b/String.o: ../JVM/natives/java/lang/String.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/b4cb398b
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/b4cb398b/String.o ../JVM/natives/java/lang/String.cpp

${OBJECTDIR}/_ext/b4cb398b/StringBuilder.o: ../JVM/natives/java/lang/StringBuilder.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/b4cb398b
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/b4cb398b/StringBuilder.o ../JVM/natives/java/lang/StringBuilder.cpp

${OBJECTDIR}/_ext/b4cb398b/System.o: ../JVM/natives/java/lang/System.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/b4cb398b
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/b4cb398b/System.o ../JVM/natives/java/lang/System.cpp

${OBJECTDIR}/_ext/b4cb398b/Throwable.o: ../JVM/natives/java/lang/Throwable.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/b4cb398b
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/b4cb398b/Throwable.o ../JVM/natives/java/lang/Throwable.cpp

${OBJECTDIR}/_ext/7bec1df/natives.o: ../JVM/natives/natives.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/7bec1df
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7bec1df/natives.o ../JVM/natives/natives.cpp

${OBJECTDIR}/_ext/fd28de7b/Class.o: ../JVM/runtime/Class.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/fd28de7b
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/fd28de7b/Class.o ../JVM/runtime/Class.cpp

${OBJECTDIR}/_ext/fd28de7b/ClassMap.o: ../JVM/runtime/ClassMap.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/fd28de7b
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/fd28de7b/ClassMap.o ../JVM/runtime/ClassMap.cpp

${OBJECTDIR}/_ext/fd28de7b/ConstantPool.o: ../JVM/runtime/ConstantPool.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/fd28de7b
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/fd28de7b/ConstantPool.o ../JVM/runtime/ConstantPool.cpp

${OBJECTDIR}/_ext/fd28de7b/ExceptionTable.o: ../JVM/runtime/ExceptionTable.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/fd28de7b
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/fd28de7b/ExceptionTable.o ../JVM/runtime/ExceptionTable.cpp

${OBJECTDIR}/_ext/fd28de7b/ExecutionEngine.o: ../JVM/runtime/ExecutionEngine.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/fd28de7b
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/fd28de7b/ExecutionEngine.o ../JVM/runtime/ExecutionEngine.cpp

${OBJECTDIR}/_ext/fd28de7b/Method.o: ../JVM/runtime/Method.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/fd28de7b
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/fd28de7b/Method.o ../JVM/runtime/Method.cpp

${OBJECTDIR}/_ext/fd28de7b/MethodArea.o: ../JVM/runtime/MethodArea.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/fd28de7b
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/fd28de7b/MethodArea.o ../JVM/runtime/MethodArea.cpp

${OBJECTDIR}/_ext/fd28de7b/MethodFrame.o: ../JVM/runtime/MethodFrame.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/fd28de7b
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/fd28de7b/MethodFrame.o ../JVM/runtime/MethodFrame.cpp

${OBJECTDIR}/_ext/fd28de7b/OperandStack.o: ../JVM/runtime/OperandStack.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/fd28de7b
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/fd28de7b/OperandStack.o ../JVM/runtime/OperandStack.cpp

${OBJECTDIR}/_ext/fdfbb3dc/Descriptors.o: ../JVM/types/Descriptors.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/fdfbb3dc
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/fdfbb3dc/Descriptors.o ../JVM/types/Descriptors.cpp

${OBJECTDIR}/_ext/fe076c14/ArgumentsParser.o: ../JVM/utils/ArgumentsParser.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/fe076c14
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/fe076c14/ArgumentsParser.o ../JVM/utils/ArgumentsParser.cpp

${OBJECTDIR}/_ext/fe076c14/Utf8String.o: ../JVM/utils/Utf8String.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/fe076c14
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/fe076c14/Utf8String.o ../JVM/utils/Utf8String.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/netbeansproject

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
