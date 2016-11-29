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
	${OBJECTDIR}/main-cmd.o \
	${OBJECTDIR}/namespace_objectname.o


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
	$(COMPILE.c) -g -I/usr/include/gtk-3.0 -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/gog_object_generator.o gog_object_generator.c

${OBJECTDIR}/main-cmd.o: main-cmd.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I/usr/include/gtk-3.0 -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main-cmd.o main-cmd.c

${OBJECTDIR}/namespace_objectname.o: namespace_objectname.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I/usr/include/gtk-3.0 -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/namespace_objectname.o namespace_objectname.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/gobjectgenerator

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
