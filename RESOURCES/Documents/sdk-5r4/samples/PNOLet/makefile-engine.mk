## Palm OS Generic 68K PNO Makefile Engine for Palm OS Developer Suite v1.1.0
#
# Last edit: 11/10/04
#
# This makefile engine is capable of compiling straight 68K 
# applications as well as 68K PNO applications for the Palm OS.
#
# This makefile engine assumes that the following variables are 
# set outside of this makefile by a referencing master makefile
# (see a master makefile generated by a Palm OS Developer 
# Suite wizard for detailed explanation of each variable):
#
#	SOURCES
#	RESOURCES
#	PNO_SOURCES
#	PNO_RESOURCES 
#	PNO_LIBRARY 
#	MULTIPLE_CODE_SECTIONS 
#	CREATOR_ID 
#	DB_TYPE 
#	DATABASE_RESET 
#	DATABASE_BACKUP 
#	DATABASE_HIDDEN 
#	DATABASE_PROTECT 
#	DATABASE_BUNDLE
#	DATABASE_VERSION 
#	DATABASE_NAME
#	LOCALE
#	DEBUG_OR_RELEASE 
#	TARGET_PLATFORM
#	OPTIMIZE_LEVEL 
#	WARNING_LEVEL  
#	SIM_WARNING_LEVEL  
#	PNO_WARNING_LEVEL 
#	WARNING_AS_ERROR 
#	PNO_WARNING_AS_ERROR 
#	SIM_WARNING_AS_ERROR 
#	VERBOSE
#	PNO_VERBOSE
#	SIM_VERBOSE
#	ENABLE_ASSERTIONS
#	LOCAL_INCLUDE_PATHS 
#	LOCAL_PNO_INCLUDE_PATHS 
#	LOCAL_PNO_SIM_INCLUDE_PATHS 
#	SYSTEM_INCLUDE_PATHS 
#	SYSTEM_PNO_INCLUDE_PATHS 
#	SYSTEM_PNO_SIM_INCLUDE_PATHS 
#	PRE_INCLUDE_PATHS
#	PNO_PRE_INCLUDE_PATHS
#	PNO_SIM_PRE_INCLUDE_PATHS
#	DEFINES 
#	PNO_DEFINES 
#	PNO_SIM_DEFINES 
#	UNDEFINES 
#	PNO_UNDEFINES 
#	PNO_SIM_UNDEFINES 
#	ADDITIONAL_COMPILER_FLAGS 
#	ADDITIONAL_PNO_COMPILER_FLAGS
#	ADDITIONAL_PNO_SIM_COMPILER_FLAGS
#	ADDITIONAL_LINKER_FLAGS 
#	ADDITIONAL_PNO_LINKER_FLAGS 
#	ADDITIONAL_PNO_SIM_LINKER_FLAGS 
#	ADDITIONAL_LINK_LIBRARIES 
#	ADDITIONAL_PNO_LINK_LIBRARIES 
#	ADDITIONAL_PNO_SIM_LINK_LIBRARIES
#	ADDITIONAL_LINK_LIBPATH 
#	ADDITIONAL_PNO_LINK_LIBPATH 
#	ADDITIONAL_PNO_SIM_LINK_LIBPATH 
#	PRC_TEXT_ENCODING
#	PRC_NO_LOCALE_CHECK
#	PRC_STRICT_LOCALE
#	PRC_STRICT_ENCODING
#	PRC_OVERLAY_FILTER
#	PRC_NO_WARN_SIZE
#	PRC_QUIET
#	PRCMERGE_QUIET
#	ADDITIONAL_PRC_FLAGS
#	ADDITIONAL_PRCMERGE_FLAGS
#	DEBUG_DEVICE_OUTPUT_DIR
#	RELEASE_DEVICE_OUTPUT_DIR 
#	DEBUG_SIMULATOR_OUTPUT_DIR 
#	RELEASE_SIMULATOR_OUTPUT_DIR 
#	PNO_ARM_DEBUG_OUTPUT_DIR
#	PNO_ARM_RELEASE_OUTPUT_DIR
#	PNO_SIM_DEBUG_OUTPUT_DIR 
#	PNO_SIM_RELEASE_OUTPUT_DIR 
#
# Additionally, the user of this makefile engine may obtain the 
# dynamic values for:
#	SDK_LOCATION
#	SDK_VERSION
#	TOOLS_DIR 
# by doing an optional include of a makefile segment that is 
# generated during the Palm OS Developer Suite standard make build.
# The makefile line to accomplish this is:
#	-include auto-generated.mk
# All master makefiles generated by Palm OS Developer Suite
# wizards include this line already to pick up and use these
# dynamic definitions.
#
# All variable values may be overridden by editing the make command
# for the project (Project->Properties->C/C++ Make Project->Make Builder,
# Build Command field).
#

###############################################################################
# Defaults

PRCFLAGS +=

ifeq ($(DEBUG_DEVICE_OUTPUT_DIR), )
	DEBUG_DEVICE_OUTPUT_DIR = DebugDevice
endif

ifeq ($(RELEASE_DEVICE_OUTPUT_DIR), )
	RELEASE_DEVICE_OUTPUT_DIR = ReleaseDevice
endif

ifeq ($(DEBUG_SIMULATOR_OUTPUT_DIR), )
	DEBUG_SIMULATOR_OUTPUT_DIR = DebugSim
endif

ifeq ($(RELEASE_SIMULATOR_OUTPUT_DIR), )
	RELEASE_SIMULATOR_OUTPUT_DIR = ReleaseSim
endif

ifeq ($(PNO_ARM_DEBUG_OUTPUT_DIR), )
	PNO_ARM_DEBUG_OUTPUT_DIR = DebugPNOArm
endif

ifeq ($(PNO_ARM_RELEASE_OUTPUT_DIR), )
	PNO_ARM_RELEASE_OUTPUT_DIR = ReleasePNOArm
endif

ifeq ($(PNO_SIM_DEBUG_OUTPUT_DIR), )
	PNO_SIM_DEBUG_OUTPUT_DIR = DebugPNOSim
endif

ifeq ($(PNO_SIM_RELEASE_OUTPUT_DIR), )
	PNO_SIM_RELEASE_OUTPUT_DIR = ReleasePNOSim
endif

# Locale (defaults to english)
ifeq ($(LOCALE), )
	LOCALE := enUS
endif

# PRC and Database names
ifeq ($(PRC_NAME), )
	PRC_NAME = Start.prc
endif

ifeq ($(DATABASE_NAME), )
	DATABASE_NAME = StartApp
endif

ifeq ($(ESCAPED_ARTIFACT_NAME), )
	ESCAPED_ARTIFACT_NAME = Start
endif

ifeq ($(SDK_VERSION), )
	SDK_VERSION = sdk-5r4
endif

ifeq ($(DEBUG_OR_RELEASE), Debug)
	SIM_OBJ_DIR = $(PNO_SIM_DEBUG_OUTPUT_DIR)
	ARM_OBJ_DIR = $(PNO_ARM_DEBUG_OUTPUT_DIR)
ifeq ($(TARGET_PLATFORM), Device)
	OBJ_DIR = $(DEBUG_DEVICE_OUTPUT_DIR)
	NATIVE_CODE_DIR := $(ARM_OBJ_DIR)
else
	OBJ_DIR = $(DEBUG_SIMULATOR_OUTPUT_DIR)
	NATIVE_CODE_DIR := $(SIM_OBJ_DIR)
endif
else
	SIM_OBJ_DIR = $(PNO_SIM_RELEASE_OUTPUT_DIR)
	ARM_OBJ_DIR = $(PNO_ARM_RELEASE_OUTPUT_DIR)
ifeq ($(TARGET_PLATFORM), Device)
	OBJ_DIR = $(RELEASE_DEVICE_OUTPUT_DIR)
	NATIVE_CODE_DIR := $(ARM_OBJ_DIR)
else
	OBJ_DIR = $(RELEASE_SIMULATOR_OUTPUT_DIR)
	NATIVE_CODE_DIR := $(SIM_OBJ_DIR)
endif
endif

TARGET	:= $(OBJ_DIR)/$(PRC_NAME)
LINKER_OUTPUT := $(OBJ_DIR)/$(ESCAPED_ARTIFACT_NAME)

# sdk-# assumed...
TARGET_FORMAT=PalmOS4
SDKFLAG = $(subst sdk-,-palmos,$(SDK_VERSION))
CFLAGS += $(SDKFLAG)
DEPFLAGS = -MM -MG -P -w 
ARM_DEPFLAGS = -M1

# Compiler Settings ... this is a makefile for Palm OS 68K and PNO
# so the compilers used are as follows:
# 68K compiler is m68k-palmos-gcc
# PNO compiler is pacc
# PNO "simlet" compiler is gcc

# Compiler settings... compiler + optimizations + debug
CC = m68k-palmos-gcc
AS = m68k-palmos-as
CFLAGS += -D__PALMOS__=0x05000000

ARM_CC = "$(TOOLS_DIR)pacc"
ARM_CFLAGS += -pno -nocrt -D__PALMOS__=0x05000000

SIM_CC = gcc
SIM_CFLAGS += -D__PALMOS__=0x05000000

# Optimization settings
ifeq ($(OPTIMIZE_LEVEL), FULL)
	OPTIMIZER_FLAG	= -O3
else
ifeq ($(OPTIMIZE_LEVEL), SOME)
	OPTIMIZER_FLAG	= -O1
else
ifeq ($(OPTIMIZE_LEVEL), NONE)
	OPTIMIZER_FLAG	= -O0
else
# default to FULL
	OPTIMIZER_FLAG	= -O3
endif
endif
endif
	
# Debug settings (can override optimize settings)
ifeq ($(DEBUG_OR_RELEASE), Debug)
	DEBUG_FLAG += -g
	OPTIMIZER_FLAG = -O0
endif	

CFLAGS += $(OPTIMIZER_FLAG) $(DEBUG_FLAG)
ARM_CFLAGS += $(OPTIMIZER_FLAG) $(DEBUG_FLAG)
SIM_CFLAGS += $(OPTIMIZER_FLAG) $(DEBUG_FLAG)

# Warning level for 68K compilation
ifeq ($(WARNING_LEVEL), ALL)
	CFLAGS += -Wall
else
ifeq ($(WARNING_LEVEL), NONE)
	CFLAGS += -w
endif
endif

# Warning level for PNO device target
ifeq ($(PNO_WARNING_LEVEL), ALL)
	ARM_CFLAGS += -W4
else
ifeq ($(PNO_WARNING_LEVEL), SOME)
	ARM_CFLAGS += -W2
else
ifeq ($(PNO_WARNING_LEVEL), NONE)
	ARM_CFLAGS += -W0
endif
endif
endif

# Warning level for PNO simulator target compilation
ifeq ($(SIM_WARNING_LEVEL), ALL)
	SIM_CFLAGS += -Wall 
else
ifeq ($(SIM_WARNING_LEVEL), NONE)
	SIM_CFLAGS += -w
endif
endif

# Warnings as errors for 68K builds
ifeq ($(WARNING_AS_ERROR), TRUE)
	CFLAGS += -Werror
endif

# Warnings as errors for PNO device builds
ifeq ($(PNO_WARNING_AS_ERROR), TRUE)
	ARM_CFLAGS += -Werror
endif

# Warnings as errors for PNO simulator builds
ifeq ($(SIM_WARNING_AS_ERROR), TRUE)
	SIM_CFLAGS += -Werror
endif

# Verbose output for 68K builds
ifeq ($(VERBOSE), TRUE)
	CFLAGS += -v
endif

# Verbose output for PNO device builds
ifeq ($(PNO_VERBOSE), TRUE)
	ARM_CFLAGS += -v
endif

# Verbose output for PNO simulator builds
ifeq ($(SIM_VERBOSE), TRUE)
	SIM_CFLAGS += -v
endif

# Assertion handling support
ifeq ($(ENABLE_ASSERTIONS), TRUE)
	ARM_CFLAGS += -UNDEBUG
else
	ARM_CFLAGS += -DNDEBUG=1
endif


# Skip multichar constant warnings
SIM_CFLAGS += -Wno-multichar


# Linker settings (must come after setting DEBUG_FLAG)
LD = m68k-palmos-gcc
LDFLAGS += $(DEBUG_FLAG)

ARM_LD = "$(TOOLS_DIR)pacc"
ARM_LDFLAGS = -pno -nologo -Wl,-pnolet

SIM_LD = gcc
SIM_LDFLAGS += $(DEBUG_FLAG)

# Resource flags (PalmRC)
RFLAGS +=

# Default text encoding is Latin
ifeq ($(PRC_TEXT_ENCODING), )
	PRC_TEXT_ENCODING = LATIN
endif

ifeq ($(PRC_TEXT_ENCODING), LATIN)
	RFLAGS += -target 4.0
else
ifeq ($(PRC_TEXT_ENCODING), JAPANESE)
	RFLAGS += -target 4.0J
else
ifeq ($(PRC_TEXT_ENCODING), SIMPLIFIED_CHINESE)
	RFLAGS += -target 4.0CS
endif
endif
endif

ifeq ($(PRC_NO_LOCALE_CHECK), TRUE)
	RFLAGS += -noLocaleCheck
endif

ifeq ($(PRC_STRICT_LOCALE), TRUE)
	RFLAGS += -strictLocale
endif

ifeq ($(PRC_STRICT_ENCODING), TRUE)
	RFLAGS += -strictTextEncoding
endif

ifdef PRC_OVERLAY_FILTER
	RFLAGS += -overlayFilter $(PRC_OVERLAY_FILTER)
endif

ifeq ($(PRC_NO_WARN_SIZE), TRUE)
	RFLAGS += -noWarnSize
endif

ifeq ($(PRC_QUIET), TRUE)
	RFLAGS += -quiet
endif

ifeq ($(PRCMERGE_QUIET), TRUE)
	INTERNAL_PRCMERGE_FLAGS += -quiet
	PRCFLAGS += -quiet
endif

# function for converting sources to object file names in one of output directories
define SOURCE_LIST_TO_OBJS
	$(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(foreach file, $(SOURCES), \
	$(basename $(notdir $(file))))))
endef

# function for converting sources to dependency file names in one of output directories
define SOURCE_LIST_TO_DEPS
	$(addprefix $(OBJ_DIR)/, $(addsuffix .d, $(foreach file, $(SOURCES), \
	$(basename $(notdir $(file))))))
endef

# function for converting resources into resource object files
define RESOURCE_LIST_TO_OBJS
	$(addprefix $(OBJ_DIR)/, $(addsuffix .trc, $(foreach file, $(RESOURCES), \
	$(basename $(file)))))
endef

# function for converting resources into resource dependency files
define RESOURCE_LIST_TO_DEPS
	$(addprefix $(OBJ_DIR)/, $(addsuffix .d, $(foreach file, $(RESOURCES), \
	$(basename $(file)))))
endef

# function for converting PNO sources to object file names in $(ARM_OBJ_DIR)
define SOURCE_LIST_TO_ARM_OBJS
	$(addprefix $(ARM_OBJ_DIR)/, $(addsuffix .o, $(foreach file, $(PNO_SOURCES), \
	$(basename $(notdir $(file))))))
endef

# function for converting PNO sources to dependency file names in $(ARM_OBJ_DIR)
define SOURCE_LIST_TO_ARM_DEPS
	$(addprefix $(ARM_OBJ_DIR)/, $(addsuffix .d, $(foreach file, $(PNO_SOURCES), \
	$(basename $(notdir $(file))))))
endef

# function for converting PNO sources to object file names in $(SIM_OBJ_DIR)
define SOURCE_LIST_TO_SIM_OBJS
	$(addprefix $(SIM_OBJ_DIR)/, $(addsuffix .o, $(foreach file, $(PNO_SOURCES), \
	$(basename $(notdir $(file))))))
endef

# function for converting PNO sources to dependency file names in $(SIM_OBJ_DIR)
define SOURCE_LIST_TO_SIM_DEPS
	$(addprefix $(SIM_OBJ_DIR)/, $(addsuffix .d, $(foreach file, $(PNO_SOURCES), \
	$(basename $(notdir $(file))))))
endef

OBJS = $(SOURCE_LIST_TO_OBJS)
SOURCE_PATHS += $(sort $(foreach file, $(SOURCES), $(dir $(file))))
RESOURCE_OBJS = $(RESOURCE_LIST_TO_OBJS)
RESOURCE_PATHS += $(sort $(foreach file, $(RESOURCES), $(dir $(file))))
ARM_OBJS = $(SOURCE_LIST_TO_ARM_OBJS)
SIM_OBJS = $(SOURCE_LIST_TO_SIM_OBJS)

DEPS = $(SOURCE_LIST_TO_DEPS) $(RESOURCE_LIST_TO_DEPS)
ifeq ($(TARGET_PLATFORM), Device)
	DEPS += $(SOURCE_LIST_TO_ARM_DEPS)
else
	DEPS += $(SOURCE_LIST_TO_SIM_DEPS)
endif


PNO_SOURCE_PATHS += $(sort $(foreach file, $(PNO_SOURCES), $(dir $(file))))
ifeq ($(TARGET_PLATFORM), Device)
# PNO BINARIES always go into "main" object directory so they are at the
# same location as all the other resource files
PNO_BINARIES = $(addprefix $(OBJ_DIR)/, $(addsuffix .bin, $(PNO_RESOURCES)))
PNO_FULLPATHS = $(PNO_BINARIES)
else
PNO_BINARIES=
PNO_FULLPATHS=
endif


VPATH :=
VPATH += $(addprefix :, $(subst  ,:, $(filter-out $($(subst, :, ,$(VPATH))), $(SOURCE_PATHS) $(RESOURCE_PATHS) $(PNO_SOURCE_PATHS))))

SYSTEM_INCLUDES = $(SYSTEM_INCLUDE_PATHS)
INCLUDES = $(LOCAL_INCLUDE_PATHS) $(foreach path, $(SOURCE_PATHS), $(addprefix -I, $(path))) $(SYSTEM_INCLUDES) $(PRE_INCLUDE_PATHS)
CPP_INCLUDES = -I"$(TOOLS_DIR)include/stlport"

PNO_SYSTEM_INCLUDES = $(SYSTEM_PNO_INCLUDE_PATHS) -I"$(SDK_LOCATION)include" -I"$(SDK_LOCATION)include/Core/System"
PNO_INCLUDES = $(LOCAL_PNO_INCLUDE_PATHS) $(foreach path, $(SOURCE_PATHS), $(addprefix -I, $(path))) $(PNO_SYSTEM_INCLUDES) $(PNO_PRE_INCLUDE_PATHS)

PNO_SIM_SYSTEM_INCLUDES = $(SYSTEM_PNO_SIM_INCLUDE_PATHS) -I"$(SDK_LOCATION)include" -I"$(SDK_LOCATION)include/Core/System"
PNO_SIM_INCLUDES = $(LOCAL_PNO_SIM_INCLUDE_PATHS) $(foreach path, $(SOURCE_PATHS), $(addprefix -I, $(path))) $(PNO_SIM_SYSTEM_INCLUDES) $(PNO_SIM_PRE_INCLUDE_PATHS)

# Now add additional settings specified by user
LDFLAGS += $(ADDITIONAL_LINK_LIBRARIES)
LDFLAGS += $(ADDITIONAL_LINKER_FLAGS)
LDFLAGS += $(foreach libpath, $(ADDITIONAL_LINK_LIBPATH), $(addprefix -L, $(libpath)))
CFLAGS += $(foreach define, $(DEFINES), $(addprefix -D, $(define)))
CFLAGS += $(foreach define, $(UNDEFINES), $(addprefix -U, $(define)))
CFLAGS += $(ADDITIONAL_COMPILER_FLAGS)

SIM_LDFLAGS += $(ADDITIONAL_PNO_SIM_LINK_LIBRARIES)
SIM_LDFLAGS += $(ADDITIONAL_PNO_SIM_LINKER_FLAGS)
SIM_LDFLAGS += $(foreach libpath, $(ADDITIONAL_PNO_SIM_LINK_LIBPATH), $(addprefix -L, $(libpath)))
SIM_CFLAGS += $(foreach define, $(PNO_SIM_DEFINES), $(addprefix -D, $(define)))
SIM_CFLAGS += $(foreach define, $(PNO_SIM_UNDEFINES), $(addprefix -U, $(define)))
SIM_CFLAGS += $(ADDITIONAL_PNO_SIM_COMPILER_FLAGS)

ARM_LDFLAGS += $(ADDITIONAL_PNO_LINK_LIBRARIES) "$(TOOLS_DIR)misclibs/PNOEntryGlue.o"
ARM_LDFLAGS += $(ADDITIONAL_PNO_LINKER_FLAGS)
ARM_LDFLAGS += $(foreach libpath, $(ADDITIONAL_PNO_LINK_LIBPATH), $(addprefix -libpath , $(libpath)))
ARM_CFLAGS += $(foreach define, $(PNO_DEFINES), $(addprefix -D, $(define)))
ARM_CFLAGS += $(foreach define, $(PNO_UNDEFINES), $(addprefix -U, $(define)))
ARM_CFLAGS += $(ADDITIONAL_PNO_COMPILER_FLAGS)

RFLAGS += $(ADDITIONAL_PRC_FLAGS)
PRCFLAGS += $(ADDITIONAL_PRCMERGE_FLAGS)

ifeq ($(CREATOR_ID), )
	CREATOR_ID = STRT
endif

ifeq ($(DB_TYPE), )
	DB_TYPE = appl
endif

ifeq ($(DATABASE_VERSION), )
	DATABASE_VERSION = 1
endif

PRCFLAGS += -dbVersion $(DATABASE_VERSION) $(DATABASE_PROTECT) $(DATABASE_HIDDEN) $(DATABASE_BACKUP) $(DATABASE_RESET) $(DATABASE_BUNDLE)

###############################################################################
# Make target determination

ifeq ($(TARGET_PLATFORM), Device)
	PROJECT_MAKE_TARGET = device
else
	PROJECT_MAKE_TARGET = simulator
endif


###############################################################################
# Dependency includes

-include $(DEPS)


###############################################################################
# Defaults

#	Eclipse requires an all target to get the work done
all: $(PROJECT_MAKE_TARGET)
	@echo Build complete
	
#	This rule is only valid for projects created as application projects.
#	Don't invoke this make target directly; instead change the value of
#	TARGET_PLATFORM to Device in the main makefile
device: $(OBJ_DIR) $(ARM_OBJ_DIR) $(TARGET)

#	This rule is only valid for projects created as application projects.
#	Don't invoke this make target directly; instead change the value of
#	TARGET_PLATFORM to Simulator in the main makefile
simulator: $(OBJ_DIR) $(SIM_OBJ_DIR) $(OBJ_DIR)/$(PNO_LIBRARY) $(TARGET)


# rule to create the object file directories if needed
$(OBJ_DIR):
	@[ -d $(OBJ_DIR) ] || mkdir $(OBJ_DIR) > /dev/null 2>&1

$(ARM_OBJ_DIR): 
ifneq ($(PNO_SOURCES), )
	@[ -d $(ARM_OBJ_DIR) ] || mkdir $(ARM_OBJ_DIR) > /dev/null 2>&1
endif
	
$(SIM_OBJ_DIR):
ifneq ($(PNO_SOURCES), )
	@[ -d $(SIM_OBJ_DIR) ] || mkdir $(SIM_OBJ_DIR) > /dev/null 2>&1
endif


# main/68K C/C++ sources
$(OBJ_DIR)/%.o : %.c 
	@echo
	$(CC) -c $< $(INCLUDES) $(CFLAGS) -o $@
	echo -n $(@:%.o=%.d) $(dir $@) > $(@:%.o=%.d) && \
	$(CC) -c $< $(DEPFLAGS) $(INCLUDES) $(CFLAGS) >> $(@:%.o=%.d) && \
	echo -e \\n$(@:%.o=%.d) $@ : makefile makefile-engine.mk auto-generated.mk >> $(@:%.o=%.d)
	
$(OBJ_DIR)/%.o : %.cpp 
	@echo
	$(CC) -c $< $(INCLUDES) $(CPP_INCLUDES) $(CFLAGS) -o $@
	echo -n $(@:%.o=%.d) $(dir $@) > $(@:%.o=%.d) && \
	$(CC) -c $< $(DEPFLAGS) $(INCLUDES) $(CPP_INCLUDES) $(CFLAGS) >> $(@:%.o=%.d) && \
	echo -e \\n$(@:%.o=%.d) $@ : makefile makefile-engine.mk auto-generated.mk >> $(@:%.o=%.d)
	
$(OBJ_DIR)/%.o : %.cp 
	@echo
	$(CC) -c $< $(INCLUDES) $(CPP_INCLUDES) $(CFLAGS) -o $@
	echo -n $(@:%.o=%.d) $(dir $@) > $(@:%.o=%.d) && \
	$(CC) -c $< $(DEPFLAGS) $(INCLUDES) $(CPP_INCLUDES) $(CFLAGS) >> $(@:%.o=%.d) && \
	echo -e \\n$(@:%.o=%.d) $@ : makefile makefile-engine.mk auto-generated.mk >> $(@:%.o=%.d)
	
$(OBJ_DIR)/%.o : %.cc 
	@echo
	$(CC) -c $< $(INCLUDES) $(CPP_INCLUDES) $(CFLAGS) -o $@
	echo -n $(@:%.o=%.d) $(dir $@) > $(@:%.o=%.d) && \
	$(CC) -c $< $(DEPFLAGS) $(INCLUDES) $(CPP_INCLUDES) $(CFLAGS) >> $(@:%.o=%.d) && \
	echo -e \\n$(@:%.o=%.d) $@ : makefile makefile-engine.mk auto-generated.mk >> $(@:%.o=%.d)
	
$(OBJ_DIR)/%.o : %.C 
	@echo
	$(CC) -c $< $(INCLUDES) $(CFLAGS) -o $@
	echo -n $(@:%.o=%.d) $(dir $@) > $(@:%.o=%.d) && \
	$(CC) -c $< $(DEPFLAGS) $(INCLUDES) $(CFLAGS) >> $(@:%.o=%.d) && \
	echo -e \\n$(@:%.o=%.d) $@ : makefile makefile-engine.mk auto-generated.mk >> $(@:%.o=%.d)
	
$(OBJ_DIR)/%.o : %.CC 
	@echo
	$(CC) -c $< $(INCLUDES) $(CPP_INCLUDES) $(CFLAGS) -o $@
	echo -n $(@:%.o=%.d) $(dir $@) > $(@:%.o=%.d) && \
	$(CC) -c $< $(DEPFLAGS) $(INCLUDES) $(CPP_INCLUDES) $(CFLAGS) >> $(@:%.o=%.d) && \
	echo -e \\n$(@:%.o=%.d) $@ : makefile makefile-engine.mk auto-generated.mk >> $(@:%.o=%.d)
	
$(OBJ_DIR)/%.o : %.CPP 
	@echo
	$(CC) -c $< $(INCLUDES) $(CPP_INCLUDES) $(CFLAGS) -o $@
	echo -n $(@:%.o=%.d) $(dir $@) > $(@:%.o=%.d) && \
	$(CC) -c $< $(DEPFLAGS) $(INCLUDES) $(CPP_INCLUDES) $(CFLAGS) >> $(@:%.o=%.d) && \
	echo -e \\n$(@:%.o=%.d) $@ : makefile makefile-engine.mk auto-generated.mk >> $(@:%.o=%.d)
	

# ARM C/C++ sources
$(ARM_OBJ_DIR)/%.o : %.c 
	@echo
	$(ARM_CC) -c $< $(PNO_INCLUDES) $(ARM_CFLAGS) -o $@
	echo -n $(@:%.o=%.d) $@ : ' ' > $(@:%.o=%.d) && \
	$(ARM_CC) $< $(ARM_DEPFLAGS) $(PNO_INCLUDES) $(ARM_CFLAGS) | /usr/bin/sed 's/^.*: //' | /usr/bin/sed 's/ /\\\ /g' | /usr/bin/tr '\r\n' ' ' >> $(@:%.o=%.d) && \
	echo -e \\n\\n$(@:%.o=%.d) $@ : makefile makefile-engine.mk auto-generated.mk >> $(@:%.o=%.d)
	
$(ARM_OBJ_DIR)/%.o : %.cpp 
	@echo
	$(ARM_CC) -c $< $(PNO_INCLUDES) $(ARM_CFLAGS) -o $@
	echo -n $(@:%.o=%.d) $@ : ' ' > $(@:%.o=%.d) && \
	$(ARM_CC) $< $(ARM_DEPFLAGS) $(PNO_INCLUDES) $(ARM_CFLAGS) | /usr/bin/sed 's/^.*: //' | /usr/bin/sed 's/ /\\\ /g' | /usr/bin/tr '\r\n' ' ' >> $(@:%.o=%.d) && \
	echo -e \\n\\n$(@:%.o=%.d) $@ : makefile makefile-engine.mk auto-generated.mk >> $(@:%.o=%.d)
	
$(ARM_OBJ_DIR)/%.o : %.cp 
	@echo
	$(ARM_CC) -c $< $(PNO_INCLUDES) $(ARM_CFLAGS) -o $@
	echo -n $(@:%.o=%.d) $@ : ' ' > $(@:%.o=%.d) && \
	$(ARM_CC) $< $(ARM_DEPFLAGS) $(PNO_INCLUDES) $(ARM_CFLAGS) | /usr/bin/sed 's/^.*: //' | /usr/bin/sed 's/ /\\\ /g' | /usr/bin/tr '\r\n' ' ' >> $(@:%.o=%.d) && \
	echo -e \\n\\n$(@:%.o=%.d) $@ : makefile makefile-engine.mk auto-generated.mk >> $(@:%.o=%.d)
	
$(ARM_OBJ_DIR)/%.o : %.cc 
	@echo
	$(ARM_CC) -c $< $(PNO_INCLUDES) $(ARM_CFLAGS) -o $@
	echo -n $(@:%.o=%.d) $@ : ' ' > $(@:%.o=%.d) && \
	$(ARM_CC) $< $(ARM_DEPFLAGS) $(PNO_INCLUDES) $(ARM_CFLAGS) | /usr/bin/sed 's/^.*: //' | /usr/bin/sed 's/ /\\\ /g' | /usr/bin/tr '\r\n' ' ' >> $(@:%.o=%.d) && \
	echo -e \\n\\n$(@:%.o=%.d) $@ : makefile makefile-engine.mk auto-generated.mk >> $(@:%.o=%.d)
	
$(ARM_OBJ_DIR)/%.o : %.C 
	@echo
	$(ARM_CC) -c $< $(PNO_INCLUDES) $(ARM_CFLAGS) -o $@
	echo -n $(@:%.o=%.d) $@ : ' ' > $(@:%.o=%.d) && \
	$(ARM_CC) $< $(ARM_DEPFLAGS) $(PNO_INCLUDES) $(ARM_CFLAGS) | /usr/bin/sed 's/^.*: //' | /usr/bin/sed 's/ /\\\ /g' | /usr/bin/tr '\r\n' ' ' >> $(@:%.o=%.d) && \
	echo -e \\n\\n$(@:%.o=%.d) $@ : makefile makefile-engine.mk auto-generated.mk >> $(@:%.o=%.d)
	
$(ARM_OBJ_DIR)/%.o : %.CC 
	@echo
	$(ARM_CC) -c $< $(PNO_INCLUDES) $(ARM_CFLAGS) -o $@
	echo -n $(@:%.o=%.d) $@ : ' ' > $(@:%.o=%.d) && \
	$(ARM_CC) $< $(ARM_DEPFLAGS) $(PNO_INCLUDES) $(ARM_CFLAGS) | /usr/bin/sed 's/^.*: //' | /usr/bin/sed 's/ /\\\ /g' | /usr/bin/tr '\r\n' ' ' >> $(@:%.o=%.d) && \
	echo -e \\n\\n$(@:%.o=%.d) $@ : makefile makefile-engine.mk auto-generated.mk >> $(@:%.o=%.d)
	
$(ARM_OBJ_DIR)/%.o : %.CPP 
	@echo
	$(ARM_CC) -c $< $(PNO_INCLUDES) $(ARM_CFLAGS) -o $@
	echo -n $(@:%.o=%.d) $@ : ' ' > $(@:%.o=%.d) && \
	$(ARM_CC) $< $(ARM_DEPFLAGS) $(PNO_INCLUDES) $(ARM_CFLAGS) | /usr/bin/sed 's/^.*: //' | /usr/bin/sed 's/ /\\\ /g' | /usr/bin/tr '\r\n' ' ' >> $(@:%.o=%.d) && \
	echo -e \\n\\n$(@:%.o=%.d) $@ : makefile makefile-engine.mk auto-generated.mk >> $(@:%.o=%.d)
	

# Simulator C/C++ sources - use host gcc
$(SIM_OBJ_DIR)/%.o : %.c 
	@echo
	$(SIM_CC) -c $< $(PNO_SIM_INCLUDES) $(SIM_CFLAGS) -o $@
	echo -n $(@:%.o=%.d) $(dir $@) > $(@:%.o=%.d) && \
	$(SIM_CC) -c $< $(DEPFLAGS) $(PNO_SIM_INCLUDES) $(SIM_CFLAGS) >> $(@:%.o=%.d) && \
	echo -e \\n$(@:%.o=%.d) $@ : makefile makefile-engine.mk auto-generated.mk >> $(@:%.o=%.d)
	
$(SIM_OBJ_DIR)/%.o : %.cpp 
	@echo
	$(SIM_CC) -c $< $(PNO_SIM_INCLUDES) $(SIM_CFLAGS) -o $@
	echo -n $(@:%.o=%.d) $(dir $@) > $(@:%.o=%.d) && \
	$(SIM_CC) -c $< $(DEPFLAGS) $(PNO_SIM_INCLUDES) $(SIM_CFLAGS) >> $(@:%.o=%.d) && \
	echo -e \\n$(@:%.o=%.d) $@ : makefile makefile-engine.mk auto-generated.mk >> $(@:%.o=%.d)
	
$(SIM_OBJ_DIR)/%.o : %.cp 
	@echo
	$(SIM_CC) -c $< $(PNO_SIM_INCLUDES) $(SIM_CFLAGS) -o $@
	echo -n $(@:%.o=%.d) $(dir $@) > $(@:%.o=%.d) && \
	$(SIM_CC) -c $< $(DEPFLAGS) $(PNO_SIM_INCLUDES) $(SIM_CFLAGS) >> $(@:%.o=%.d) && \
	echo -e \\n$(@:%.o=%.d) $@ : makefile makefile-engine.mk auto-generated.mk >> $(@:%.o=%.d)
	
$(SIM_OBJ_DIR)/%.o : %.cc 
	@echo
	$(SIM_CC) -c $< $(PNO_SIM_INCLUDES) $(SIM_CFLAGS) -o $@
	echo -n $(@:%.o=%.d) $(dir $@) > $(@:%.o=%.d) && \
	$(SIM_CC) -c $< $(DEPFLAGS) $(PNO_SIM_INCLUDES) $(SIM_CFLAGS) >> $(@:%.o=%.d) && \
	echo -e \\n$(@:%.o=%.d) $@ : makefile makefile-engine.mk auto-generated.mk >> $(@:%.o=%.d)
	
$(SIM_OBJ_DIR)/%.o : %.C 
	@echo
	$(SIM_CC) -c $< $(PNO_SIM_INCLUDES) $(SIM_CFLAGS) -o $@
	echo -n $(@:%.o=%.d) $(dir $@) > $(@:%.o=%.d) && \
	$(SIM_CC) -c $< $(DEPFLAGS) $(PNO_SIM_INCLUDES) $(SIM_CFLAGS) >> $(@:%.o=%.d) && \
	echo -e \\n$(@:%.o=%.d) $@ : makefile makefile-engine.mk auto-generated.mk >> $(@:%.o=%.d)
	
$(SIM_OBJ_DIR)/%.o : %.CC 
	@echo
	$(SIM_CC) -c $< $(PNO_SIM_INCLUDES) $(SIM_CFLAGS) -o $@
	echo -n $(@:%.o=%.d) $(dir $@) > $(@:%.o=%.d) && \
	$(SIM_CC) -c $< $(DEPFLAGS) $(PNO_SIM_INCLUDES) $(SIM_CFLAGS) >> $(@:%.o=%.d) && \
	echo -e \\n$(@:%.o=%.d) $@ : makefile makefile-engine.mk auto-generated.mk >> $(@:%.o=%.d)
	
$(SIM_OBJ_DIR)/%.o : %.CPP 
	@echo
	$(SIM_CC) -c $< $(PNO_SIM_INCLUDES) $(SIM_CFLAGS) -o $@
	echo -n $(@:%.o=%.d) $(dir $@) > $(@:%.o=%.d) && \
	$(SIM_CC) -c $< $(DEPFLAGS) $(PNO_SIM_INCLUDES) $(SIM_CFLAGS) >> $(@:%.o=%.d) && \
	echo -e \\n$(@:%.o=%.d) $@ : makefile makefile-engine.mk auto-generated.mk >> $(@:%.o=%.d)
	

# XRD sources
$(OBJ_DIR)/%.trc : %.xrd 
	@echo
	"$(TOOLS_DIR)PalmRC" -p $(TARGET_FORMAT) $(RFLAGS) -locale $(LOCALE) $< -o $@
	echo -n $(@:%.trc=%.d) $@ : ' ' > $(@:%.trc=%.d) && \
	"$(TOOLS_DIR)PalmRC" -quiet -p $(TARGET_FORMAT) -makedeps $(@:%.trc=%.d).tmp $(RFLAGS) -locale $(LOCALE) $< && \
	/usr/bin/cygpath -m -f $(@:%.trc=%.d).tmp | /usr/bin/sed 's/ /\\\ /g' | /usr/bin/tr '\r\n' ' ' >> $(@:%.trc=%.d) && \
	rm -rf $(@:%.trc=%.d).tmp && \
	echo -e \\n\\n$(@:%.trc=%.d) $@ : makefile makefile-engine.mk auto-generated.mk >> $(@:%.trc=%.d)

$(OBJ_DIR)/%.trc : %.XRD 
	@echo
	"$(TOOLS_DIR)PalmRC" -p $(TARGET_FORMAT) $(RFLAGS) -locale $(LOCALE) $< -o $@
	echo -n $(@:%.trc=%.d) $@ : ' ' > $(@:%.trc=%.d) && \
	"$(TOOLS_DIR)PalmRC" -quiet -p $(TARGET_FORMAT) -makedeps $(@:%.trc=%.d).tmp $(RFLAGS) -locale $(LOCALE) $< && \
	/usr/bin/cygpath -m -f $(@:%.trc=%.d).tmp | /usr/bin/sed 's/ /\\\ /g' | /usr/bin/tr '\r\n' ' ' >> $(@:%.trc=%.d) && \
	rm -rf $(@:%.trc=%.d).tmp && \
	echo -e \\n\\n$(@:%.trc=%.d) $@ : makefile makefile-engine.mk auto-generated.mk >> $(@:%.trc=%.d)


$(OBJ_DIR)/%.bin.elf : $(ARM_OBJS)
	@echo
	@echo "...Generating PNO ELF file: $@..."
	$(ARM_LD) $(ARM_LDFLAGS) -Wl,-first -Wl,"$(ARM_OBJ_DIR)/$($*_MAIN_OBJ)(.i.$($*_PNO_ENTRY))" -Wl,-entry -Wl,$($*_PNO_ENTRY) -o $@ $(addprefix $(ARM_OBJ_DIR)/, $($*))

$(OBJ_DIR)/%.bin : $(OBJ_DIR)/%.bin.elf
	@echo
	@echo "...Generating PNO binary: $@..."
	"$(TOOLS_DIR)pelf2bin" -rsrc $($*_RSRC_ID) -directory $(OBJ_DIR) -code ARMC -data ARMD $<


# multi-section sources
ifeq ($(MULTIPLE_CODE_SECTIONS), TRUE)
SEGMENT_BASE = multiple_code_sections
$(SEGMENT_BASE).o : $(SEGMENT_BASE).s

$(SEGMENT_BASE).s $(SEGMENT_BASE).ld : Sections.def  makefile makefile-engine.mk
	@echo
	m68k-palmos-multigen -b $(SEGMENT_BASE) Sections.def

MULTISEGMENT_LINKER_INPUT = $(SEGMENT_BASE).o $(SEGMENT_BASE).ld
MULTISEGMENT_BUILD_INPUT = Sections.def
else
MULTISEGMENT_LINKER_INPUT =
MULTISEGMENT_BUILD_INPUT =
endif

$(LINKER_OUTPUT) : $(OBJS) $(MULTISEGMENT_LINKER_INPUT)
	@echo
	@echo "...Linking 68K portion..."
	$(LD) -o $(OBJ_DIR)/$(ESCAPED_ARTIFACT_NAME) $(OBJS) $(MULTISEGMENT_LINKER_INPUT) $(LDFLAGS)

$(TARGET): $(LINKER_OUTPUT) $(RESOURCE_OBJS) $(PNO_BINARIES) 
	@echo
	@echo "...Creating PRC: $(TARGET)..."
	build-prc -o $(OBJ_DIR)/buildprc_temp.prc -c '$(CREATOR_ID)' -n $(DATABASE_NAME) $(MULTISEGMENT_BUILD_INPUT) $(LINKER_OUTPUT)
	@echo
	"$(TOOLS_DIR)PRCMerge" $(INTERNAL_PRCMERGE_FLAGS) -omit pref $(OBJ_DIR)/buildprc_temp.prc -o $(OBJ_DIR)/prcmerge_temp.prc
	@echo
	"$(TOOLS_DIR)PRCMerge" -dbType '$(DB_TYPE)' -dbCreator '$(CREATOR_ID)' -n $(DATABASE_NAME) $(PRCFLAGS) -o $(TARGET) $(RESOURCE_OBJS) $(OBJ_DIR)/prcmerge_temp.prc $(PNO_FULLPATHS)
	rm -rf $(OBJ_DIR)/buildprc_temp.prc $(OBJ_DIR)/prcmerge_temp.prc

$(OBJ_DIR)/$(PNO_LIBRARY) : $(SIM_OBJS)
	@echo
	@echo "...Linking DLL for Palm OS Simulator target..."
	$(SIM_LD) --entry 0 -shared -mno-cygwin -mwindows -nostdlib -o $(OBJ_DIR)/$(PNO_LIBRARY) $(SIM_OBJS) $(SIM_LDFLAGS)


# Prevents deletion of .bin.elf files that are considered by make as 'intermediate' files
.SECONDARY:

FORCE:

# Eclipse requires a clean command
# just delete everything in OBJ_DIR and any section files
clean :: FORCE
	-rm -rf $(NATIVE_CODE_DIR)/* $(OBJ_DIR)/* *-sections.*

