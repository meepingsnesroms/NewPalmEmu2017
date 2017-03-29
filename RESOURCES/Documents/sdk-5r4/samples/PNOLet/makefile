## --------------------------------------------------------------------------
#  Palm OS Generic Makefile for Eclipse v1.0.0
#
# Fill in this file to specify your project and the source that you want
# to build, and the settings involved in the build. The makefile-engine.mk
# will then do the hard work of the makefile and dependency handling.
#
# After starting a new project, please remember the following steps...
#	1. Add all sources and resources in SOURCES and RESOURCES
#	2. Review the other settings as needed.
#
## --------------------------------------------------------------------------

SHELL = /bin/sh

## --------------------------------------------------------------------------
# Set up the artifact name.
# The PRC and/or static library name, the database name, and other file names 
# are based on the artifact name
## --------------------------------------------------------------------------

ARTIFACT_NAME =NativeCallTestApp

EMPTY =
SPACE =$(EMPTY) $(EMPTY)
ESCAPED_ARTIFACT_NAME = $(subst $(SPACE),\ ,$(ARTIFACT_NAME))
PRC_NAME = $(ESCAPED_ARTIFACT_NAME).prc
LIB_NAME = $(ESCAPED_ARTIFACT_NAME).a
SIM_LIB_NAME = $(ESCAPED_ARTIFACT_NAME).lib

## --------------------------------------------------------------------------
# 68K Sources and Resources
# List all the sources (.c/.cpp) and resources (.xrd) in your project
# Use project relative path names with forward slashes (src/code.cpp).
# Please do not use spaces in directory names.
# A note about XRD resource files:  If you have existing .rsrc or .rcp files, 
# refer to the documentation for the GenerateXRD tool to convert them into 
# XRD files for use with all Palm OS SDKs.
## --------------------------------------------------------------------------

# TODO: Update all sources and resources

SOURCES = ./Src/NativeCallTestApp.c
RESOURCES = ./Rsc/Starter.xrd

## --------------------------------------------------------------------------
# PNO Sources
# Warning: To understand this section, you need to understand how PNO
# functions are called from a 68K program.  Please refer to
# http://www.palmos.com/dev/support/docs/os5arm/PalmOS5ARMTOC.html
# To generate the correct PNO objects for your project, make needs more
# than just a list of sources.  It also needs to know the binary resources
# that will be loaded by your program calling the PNO, and what objects
# go into each resource.  To specify everything required, please do 
# the following:
# 	1. 	Fill in PNO_SOURCES with a list of all PNO source files.
#	2.	Fill in PNO_RESOURCES with a list of the binary resources your 
#		program is going to load specified by type and id.  The normal
#		convention for PNO resources uses a type of ARMC and starts with 
#		an id of 1000 (hex). To specify this resource, use ARMC1000.
#		There is currently a 64k limit on the size of each resource.
#	3.	Add a definition for each resource.  The definition consists of
#		the list of objects that should be put into that resource.
#		(These definitions allow you to combine multiple source files 
#		into one resource.)  The format of the definition should be:
#		resource = object(s)
#	4.	Add three pieces of information for each ARM resource:
#			PNO_ENTRY = the name of the method accessible in the resource
#			MAIN_OBJ = the object file containing the PNO entry method
#			RSRC_ID = the hex id of the resource
#	5.	Fill in your desired name for the Palm OS Simulator library
#		for running your application in the simulator.
# Here is an example setup with three source files and two resources.
# One resource contains multiple objects.
#	PNO_SOURCES = Compress.c Calculate.cpp CalcUtils.cpp
#	PNO_RESOURCES = ARMC1000 ARMC1001
#	ARMC1000 = Compress.o
#	ARMC1000_PNO_ENTRY = PNOMain
#	ARMC1000_MAIN_OBJ = Compress.o
#	ARMC1000_RSRC_ID = 0x1000
#	ARMC1001 = Calculate.o CalcUtils.o
#	ARMC1001_PNO_ENTRY = CalcFunction
#	ARMC1001_MAIN_OBJ = Calculate.o
#	ARMC1001_RSRC_ID = 0x1001
#	PNO_LIBRARY = $(ESCAPED_ARTIFACT_NAME).dll
## --------------------------------------------------------------------------

# TODO: List any PNO sources and binaries 
#

PNO_SOURCES = NativeCode/src/PNOLet-simple.c 
PNO_RESOURCES = ARMC1000 

ARMC1000 = PNOLet-simple.o
ARMC1000_PNO_ENTRY = PNOMain
ARMC1000_MAIN_OBJ = PNOLet-simple.o
ARMC1000_RSRC_ID = 0x1000

PNO_LIBRARY = $(ESCAPED_ARTIFACT_NAME).dll

## --------------------------------------------------------------------------
# Specify if this application has multiple sections
# If TRUE, then Sections.def file must be part of the project
## --------------------------------------------------------------------------

MULTIPLE_CODE_SECTIONS = FALSE

## --------------------------------------------------------------------------
# Review Database information
# Register Creator ID at: http://dev.palmos.com/creatorid/
## --------------------------------------------------------------------------

CREATOR_ID = apno
DB_TYPE = appl

# to enable reset on install, use -r
DATABASE_RESET = 
# to enable backup, use -b
DATABASE_BACKUP = -b
# to make the app hidden, use -h
DATABASE_HIDDEN = 
# to prevent copy, use -p
DATABASE_PROTECT = 

DATABASE_VERSION = 1 

LOCALE = enUS
DATABASE_NAME = $(ESCAPED_ARTIFACT_NAME)

## --------------------------------------------------------------------------
# Build Settings
# Review the following for your needs.
# The default settings build with debug information and no optimization.
## --------------------------------------------------------------------------

#
# Set Debug or Release configuration here
#
DEBUG_OR_RELEASE=Debug

#
# Set the target platform for the build; either Device or Simulator
# Use Device as a target for emulator builds.  
# This setting affects whether a DLL is produced or not for application
# projects.  A DLL is needed for simulator builds and contains the PNO 
# code in native platform format (e.g. x86 on Windows systems).  For static
# libraries, Device produces code in ARM format while Simulator targets
# produce code in the format of the native build platform (e.g. x86 for
# Windows systems).
#
TARGET_PLATFORM=Simulator

# Specify the level of optimization that you want
# NONE, SOME, FULL
OPTIMIZE_LEVEL = NONE

# Specify warning level
# NONE = supress all warnings
# ALL = enable all warnings
# <undefined> = default warnings
WARNING_LEVEL = 

# List additional libraries to link with
# (Full or project relative path)
ADDITIONAL_LINK_LIBRARIES =
ADDITIONAL_PNO_LINK_LIBRARIES =
ADDITIONAL_PNO_SIM_LINK_LIBRARIES =

# Additional paths to look for #include "header"
# (Source file directories are automatically included)
# Please note that both local and system include paths should 
# either use "cygwin" syntax or if in Windows syntax the should
# be quoted.  ie: ../MyLibrary/headers or "C:\Source\MyLibrary\headers"
LOCAL_INCLUDE_PATHS = -I./Rsc -I./NativeCode/src
LOCAL_PNO_INCLUDE_PATHS = -I./Rsc -I./NativeCode/src
LOCAL_PNO_SIM_INCLUDE_PATHS = -I./rsc -I./NativeCode

# Additional paths to look for #include <header>
# (Palm OS SDK directories are automatically included)
# Additionally, you must explicly specify the "-I" prior to each
# path included in this variable.  Spaces are used to separate
# each path from each other.
SYSTEM_INCLUDE_PATHS =-I../../include
SYSTEM_PNO_INCLUDE_PATHS =-I../../include
SYSTEM_PNO_SIM_INCLUDE_PATHS =-I../../include

# Specify any needed preprocessor symbols.
# If you set DEFINES to "ASSERTLEVEL=1", the compiler will see "-DASSERTLEVEL=1"
# (separate individual entries with spaces)
DEFINES =
PNO_DEFINES =
PNO_SIM_DEFINES =

# Specify additional compiler flags for all files
ADDITIONAL_COMPILER_FLAGS = 
ADDITIONAL_PNO_COMPILER_FLAGS =
ADDITIONAL_PNO_SIM_COMPILER_FLAGS =

# Specify additional linker flags
ADDITIONAL_LINKER_FLAGS =
ADDITIONAL_PNO_LINKER_FLAGS =
ADDITIONAL_PNO_SIM_LINKER_FLAGS =

# Tools Directory
# Normally you wouldn't want to override this since the necessary tools
# are in the PATH.  But if you experimenting with other tools, then 
# reset the directory here
# If overridden, end with a trailing '/'
TOOLS_DIR =


## --------------------------------------------------------------------------
# Resource Settings
## --------------------------------------------------------------------------

# Specify the target text encoding
# LATIN, JAPANESE, SIMPLIFIED_CHINESE
TEXTENCODING = LATIN

# Specify error levels for locale and text encoding
# NOCHECK
# STRICT
# <default>
LOCALE_CHECKING =

# Specific if encoding should be checked
# FALSE, TRUE
STRICT_ENCODING = FALSE

## --------------------------------------------------------------------------
# Output Settings
## --------------------------------------------------------------------------

# Modify if you want object and output files to be in different locations
# (However, please note that all three object directories must be different
# for the makefile engine to properly operate.)
# OUTPUT_DIR is the "main" output directory, where all linked and binary objects
# will be put.
# Initially, device and simulator builds go to the same output directories 
# because the 68K compilations steps and outputs are the same for both targets

DEBUG_DEVICE_OUTPUT_DIR := DebugDevice
RELEASE_DEVICE_OUTPUT_DIR := ReleaseDevice
DEBUG_SIMULATOR_OUTPUT_DIR := DebugSim
RELEASE_SIMULATOR_OUTPUT_DIR := ReleaseSim

# PNO code when targeting a device output directories
PNO_ARM_DEBUG_OUTPUT_DIR := DebugPNOArm
PNO_ARM_RELEASE_OUTPUT_DIR := ReleasePNOArm
# PNO code when targeting a simulator output directories
PNO_SIM_DEBUG_OUTPUT_DIR := DebugPNOSim
PNO_SIM_RELEASE_OUTPUT_DIR := ReleasePNOSim

RSC_OBJ_DIR := ResourceObjs

## --------------------------------------------------------------------------
# Makefiles
## --------------------------------------------------------------------------

## conditionally include an auto-generated.mk for dynamic definitions
-include auto-generated.mk

## include the makefile engine
include makefile-engine.mk

## conditionally include your own custom.mk for your specific overrides or definitions
## this is useful if you don't want to use the auto-generated.mk values
## for some reason
-include custom.mk
