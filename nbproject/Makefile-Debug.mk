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
CC=clang
CCC=clang++
CXX=clang++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=CLang-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/gog_object_generator.o \
	${OBJECTDIR}/gog_text.o \
	${OBJECTDIR}/main-cmd.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f2 \
	${TESTDIR}/TestFiles/f1

# Test Object Files
TESTOBJECTFILES= \
	${TESTDIR}/tests/generate.o \
	${TESTDIR}/tests/gog_text_test.o

# C Compiler Flags
CFLAGS=`pkg-config --cflags glib-2.0 gtk+-3.0 gobject-2.0` 

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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/gobjectgenerator

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/gobjectgenerator: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/gobjectgenerator ${OBJECTFILES} ${LDLIBSOPTIONS} `pkg-config --libs glib-2.0 gtk+-3.0 gobject-2.0`

${OBJECTDIR}/gog_object_generator.o: gog_object_generator.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I/usr/include/gtk-3.0 -I/usr/include/glib-2.0 -I/usr/include/gio-unix-2.0 -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/gog_object_generator.o gog_object_generator.c

${OBJECTDIR}/gog_text.o: gog_text.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I/usr/include/gtk-3.0 -I/usr/include/glib-2.0 -I/usr/include/gio-unix-2.0 -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/gog_text.o gog_text.c

${OBJECTDIR}/main-cmd.o: main-cmd.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I/usr/include/gtk-3.0 -I/usr/include/glib-2.0 -I/usr/include/gio-unix-2.0 -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main-cmd.o main-cmd.c

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-tests-subprojects .build-conf ${TESTFILES}
.build-tests-subprojects:

${TESTDIR}/TestFiles/f2: ${TESTDIR}/tests/generate.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c} -o ${TESTDIR}/TestFiles/f2 $^ ${LDLIBSOPTIONS} `pkg-config --libs glib-2.0 gobject-2.0`  

${TESTDIR}/TestFiles/f1: ${TESTDIR}/tests/gog_text_test.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.c} -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS} `pkg-config --libs glib-2.0 gobject-2.0`  


${TESTDIR}/tests/generate.o: tests/generate.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -g -I/usr/include/gtk-3.0 -I/usr/include/glib-2.0 -I/usr/include/gio-unix-2.0 -I. -std=c11 `pkg-config --cflags --libs glib-2.0` -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/generate.o tests/generate.c


${TESTDIR}/tests/gog_text_test.o: tests/gog_text_test.c 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.c) -g -I/usr/include/gtk-3.0 -I/usr/include/glib-2.0 -I/usr/include/gio-unix-2.0 -I. -std=c11 `pkg-config --cflags --libs glib-2.0` -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/gog_text_test.o tests/gog_text_test.c


${OBJECTDIR}/gog_object_generator_nomain.o: ${OBJECTDIR}/gog_object_generator.o gog_object_generator.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/gog_object_generator.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I/usr/include/gtk-3.0 -I/usr/include/glib-2.0 -I/usr/include/gio-unix-2.0 -std=c11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/gog_object_generator_nomain.o gog_object_generator.c;\
	else  \
	    ${CP} ${OBJECTDIR}/gog_object_generator.o ${OBJECTDIR}/gog_object_generator_nomain.o;\
	fi

${OBJECTDIR}/gog_text_nomain.o: ${OBJECTDIR}/gog_text.o gog_text.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/gog_text.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I/usr/include/gtk-3.0 -I/usr/include/glib-2.0 -I/usr/include/gio-unix-2.0 -std=c11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/gog_text_nomain.o gog_text.c;\
	else  \
	    ${CP} ${OBJECTDIR}/gog_text.o ${OBJECTDIR}/gog_text_nomain.o;\
	fi

${OBJECTDIR}/main-cmd_nomain.o: ${OBJECTDIR}/main-cmd.o main-cmd.c 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/main-cmd.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I/usr/include/gtk-3.0 -I/usr/include/glib-2.0 -I/usr/include/gio-unix-2.0 -std=c11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main-cmd_nomain.o main-cmd.c;\
	else  \
	    ${CP} ${OBJECTDIR}/main-cmd.o ${OBJECTDIR}/main-cmd_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f2 || true; \
	    ${TESTDIR}/TestFiles/f1 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
