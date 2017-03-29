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

ARTIFACT_NAME =HardBall

EMPTY =
SPACE =$(EMPTY) $(EMPTY)
ESCAPED_ARTIFACT_NAME = $(subst $(SPACE),\ ,$(ARTIFACT_NAME))
PRC_NAME = $(ESCAPED_ARTIFACT_NAME).prc
LIB_NAME = $(ESCAPED_ARTIFACT_NAME).a

## --------------------------------------------------------------------------
# Sources and Resources
# List all the sources (.c/.cpp) and resources (.xrd) in your project
# Use project relative path names with forward slashes (src/code.cpp).
# Please do not use spaces in directory names.
# A note about XRD resource files:  If you have existing .rsrc or .rcp files, 
# refer to the documentation for the GenerateXRD tool to convert them into 
# XRD files for use with all Palm OS SDKs.
## --------------------------------------------------------------------------

# TODO: List all sources and resources

SOURCES = Src/HardBall.c
RESOURCES = Rsc/HardBallBoard.xrd Rsc/HardBallHighScores.xrd Rsc/HardBallMisc.xrd Rsc/HardBallNewHighScore.xrd Rsc/HardBallPrefs.xrd 
SLIB_DEF_FILE =

## --------------------------------------------------------------------------
# Specify if this application has multiple sections
# If TRUE, then Sections.def file must be part of the project
## --------------------------------------------------------------------------

MULTIPLE_CODE_SECTIONS = FALSE

## --------------------------------------------------------------------------
# Review Database information
# Register Creator ID at: http://dev.palmos.com/creatorid/
## --------------------------------------------------------------------------

CREATOR_ID = hbal
DB_TYPE = appl

# to enable reset on install, use -r
DATABASE_RESET = 
# to enable backup, use -b
DATABASE_BACKUP = -b
# to make the app hidden, use -h
DATABASE_HIDDEN =
# to prevent copy, use -p
DATABASE_PROTECT =
# to bundle the application with its databases on beaming, use -dbFlagBundle
DATABASE_BUNDLE = 

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
# Use Device as a target for emulator builds.  For 68K projects, this
# option doesn't really affect the build; 68K code is built for both
# device and simulator targets
#
TARGET_PLATFORM=Device

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

# Additional paths to look for #include "header"
# (Source file directories are automatically included)
# Please note that both local and system include paths should 
# either use "cygwin" syntax or if in Windows syntax the should
# be quoted.  ie: ../MyLibrary/headers or "C:\Source\MyLibrary\headers"
# Additionally, you must explicly specify the "-I" prior to each
# path included in this variable.  Spaces are used to separate
# each path from each other.
LOCAL_INCLUDE_PATHS = -IRsc


# Additional paths to look for #include <header>
# (Palm OS SDK directories are automatically included)
# Additionally, you must explicly specify the "-I" prior to each
# path included in this variable.  Spaces are used to separate
# each path from each other.
SYSTEM_INCLUDE_PATHS =

# Specify any needed preprocessor symbols.
# If you set DEFINES to "ASSERTLEVEL=1", the compiler will see "-DASSERTLEVEL=1"
# (separate individual entries with spaces)
DEFINES =

# Specify additional compiler flags for all files
ADDITIONAL_COMPILER_FLAGS = 

# Specify additional linker flags
ADDITIONAL_LINKER_FLAGS =

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

DEBUG_DEVICE_OUTPUT_DIR := Debug
RELEASE_DEVICE_OUTPUT_DIR := Release
DEBUG_SIMULATOR_OUTPUT_DIR := Debug
RELEASE_SIMULATOR_OUTPUT_DIR := Release

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
