# Wind River Workbench generated Makefile.
# Do not edit!!!
#
# The file ".wrmakefile" is the template used by the Wind River Workbench to
# generate the makefiles of this project. Add user-specific build targets and
# make rules only(!) in this project's ".wrmakefile" file. These will then be
# automatically dumped into the makefiles.

WIND_HOME := $(subst \,/,$(WIND_HOME))
WIND_BASE := $(subst \,/,$(WIND_BASE))
WIND_USR := $(subst \,/,$(WIND_USR))
WRVX_COMPBASE := $(subst \,/,$(WRVX_COMPBASE))

all : pre_build main_all post_build

_clean ::
	@echo "make: removing targets and objects of `pwd`"

TRACE=0
TRACEON=$(TRACE:0=@)
TRACE_FLAG=$(TRACEON:1=)

JOBS?=1
TARGET_JOBS?=$(JOBS)

MAKEFILE := Makefile

FLEXIBLE_BUILD := 1

BUILD_SPEC = VSB_zfas-alt-soc-gen5_smp_CBEV_REL_X27X_03_maj_ARMARCH7diab_C++2003
DEBUG_MODE = 1
ifeq ($(DEBUG_MODE),1)
MODE_DIR := Debug
else
MODE_DIR := NonDebug
endif
OBJ_DIR := .
WS_ROOT_DIR := C:/WindRiver/workspace
PRJ_ROOT_DIR := $(WS_ROOT_DIR)/module2



#Global Build Macros
PROJECT_TYPE = RTP
DEFINES = 
DO_STRIP = 0
EXPAND_DBG = 0


#BuildSpec specific Build Macros
VX_CPU_FAMILY = arm
CPU = ARMARCH7
TOOL_FAMILY = diab
TOOL_VERSION = diab_5_9_4_0
_CC_VERSION = diab_5_9_4_6
TOOL = diab
CC_ARCH_SPEC = -tARMV7MV:rtp7
LIBPATH = 
LIBS = -lstlstd
VSB_DIR = $(PRJ_ROOT_DIR)/../VSB_zfas-alt-soc-gen5_smp_CBEV_REL_X27X_03_maj
VSB_CONFIG_FILE = $(VSB_DIR)/h/config/vsbConfig.h

IDE_INCLUDES = -I$(VSB_DIR)/share/h -I$(VSB_DIR)/usr/h/public -I$(VSB_DIR)/usr/h 

IDE_LIBRARIES = 

IDE_DEFINES = -D_VX_CPU=_VX_$(CPU) -D_VX_TOOL_FAMILY=$(TOOL_FAMILY) -D_VX_TOOL=$(TOOL) -D_VSB_CONFIG_FILE=\"$(VSB_DIR)/h/config/vsbConfig.h\" -DARMEL  



#BuildTool flags
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
DEBUGFLAGS_C++-Compiler = -g
DEBUGFLAGS_Linker = 
DEBUGFLAGS_Librarian = 
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_C-Compiler =  -XO
DEBUGFLAGS_C++-Compiler =  -XO
DEBUGFLAGS_Linker = 
DEBUGFLAGS_Librarian = 
DEBUGFLAGS_Assembler =  -XO
endif


#Project Targets
PROJECT_TARGETS = check_objdirs \
	 module2/$(MODE_DIR)/module2.vxe


#Rules

# module2
ifeq ($(DEBUG_MODE),1)
module2/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -g
module2/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -g
module2/$(MODE_DIR)/% : DEBUGFLAGS_Linker = 
module2/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
module2/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -g
else
module2/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler =  -XO
module2/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler =  -XO
module2/$(MODE_DIR)/% : DEBUGFLAGS_Linker = 
module2/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
module2/$(MODE_DIR)/% : DEBUGFLAGS_Assembler =  -XO
endif
module2/$(MODE_DIR)/% : IDE_INCLUDES = -I$(VSB_DIR)/share/h -I$(VSB_DIR)/usr/h/public -I$(VSB_DIR)/usr/h 
module2/$(MODE_DIR)/% : IDE_LIBRARIES = 
module2/$(MODE_DIR)/% : IDE_DEFINES = -D_VX_CPU=_VX_$(CPU) -D_VX_TOOL_FAMILY=$(TOOL_FAMILY) -D_VX_TOOL=$(TOOL) -D_VSB_CONFIG_FILE=\"$(VSB_DIR)/h/config/vsbConfig.h\" -DARMEL  
module2/$(MODE_DIR)/% : PROJECT_TYPE = RTP
module2/$(MODE_DIR)/% : DEFINES = 
module2/$(MODE_DIR)/% : DO_STRIP = 0
module2/$(MODE_DIR)/% : EXPAND_DBG = 0
module2/$(MODE_DIR)/% : VX_CPU_FAMILY = arm
module2/$(MODE_DIR)/% : CPU = ARMARCH7
module2/$(MODE_DIR)/% : TOOL_FAMILY = diab
module2/$(MODE_DIR)/% : TOOL_VERSION = diab_5_9_4_0
module2/$(MODE_DIR)/% : _CC_VERSION = diab_5_9_4_6
module2/$(MODE_DIR)/% : TOOL = diab
module2/$(MODE_DIR)/% : CC_ARCH_SPEC = -tARMV7MV:rtp7
module2/$(MODE_DIR)/% : LIBPATH = 
module2/$(MODE_DIR)/% : LIBS = -lstlstd
module2/$(MODE_DIR)/% : VSB_DIR = $(PRJ_ROOT_DIR)/../VSB_zfas-alt-soc-gen5_smp_CBEV_REL_X27X_03_maj
module2/$(MODE_DIR)/% : VSB_CONFIG_FILE = $(VSB_DIR)/h/config/vsbConfig.h
module2/$(MODE_DIR)/% : OBJ_DIR := module2/$(MODE_DIR)

module2/$(MODE_DIR)/Objects/module2/moduleTwoCommunication.o : $(PRJ_ROOT_DIR)/moduleTwoCommunication.c $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(WIND_HOME)/compilers/diab-5.9.4.6/WIN32/bin/dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -Y I,+C:/WindRiver/workspace/VSB_zfas-alt-soc-gen5_smp_CBEV_REL_X27X_03_maj/usr/h/public/c++03:C:/WindRiver/workspace/VSB_zfas-alt-soc-gen5_smp_CBEV_REL_X27X_03_maj/usr/h/public:$(WIND_HOME)/compilers/diab-5.9.4.6/WIN32/bin/../../include/diab -Xansi -WDVSB_DIR=$(VSB_DIR)  -W:c++:.CPP  -Xfp-fast -Xforce-declarations -ei4171,4188,4191,4223,4513,5152,5457,2273,5387,5388,1546   -Xmake-dependency=0xd $(IDE_DEFINES) $(DEFINES) $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<"


module2/$(MODE_DIR)/Objects/module2/moduleTwoFileSending.o : $(PRJ_ROOT_DIR)/moduleTwoFileSending.c $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(WIND_HOME)/compilers/diab-5.9.4.6/WIN32/bin/dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -Y I,+C:/WindRiver/workspace/VSB_zfas-alt-soc-gen5_smp_CBEV_REL_X27X_03_maj/usr/h/public/c++03:C:/WindRiver/workspace/VSB_zfas-alt-soc-gen5_smp_CBEV_REL_X27X_03_maj/usr/h/public:$(WIND_HOME)/compilers/diab-5.9.4.6/WIN32/bin/../../include/diab -Xansi -WDVSB_DIR=$(VSB_DIR)  -W:c++:.CPP  -Xfp-fast -Xforce-declarations -ei4171,4188,4191,4223,4513,5152,5457,2273,5387,5388,1546   -Xmake-dependency=0xd $(IDE_DEFINES) $(DEFINES) $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<"


module2/$(MODE_DIR)/Objects/module2/moduleTwoHandleRoutines.o : $(PRJ_ROOT_DIR)/moduleTwoHandleRoutines.c $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(WIND_HOME)/compilers/diab-5.9.4.6/WIN32/bin/dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -Y I,+C:/WindRiver/workspace/VSB_zfas-alt-soc-gen5_smp_CBEV_REL_X27X_03_maj/usr/h/public/c++03:C:/WindRiver/workspace/VSB_zfas-alt-soc-gen5_smp_CBEV_REL_X27X_03_maj/usr/h/public:$(WIND_HOME)/compilers/diab-5.9.4.6/WIN32/bin/../../include/diab -Xansi -WDVSB_DIR=$(VSB_DIR)  -W:c++:.CPP  -Xfp-fast -Xforce-declarations -ei4171,4188,4191,4223,4513,5152,5457,2273,5387,5388,1546   -Xmake-dependency=0xd $(IDE_DEFINES) $(DEFINES) $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<"


module2/$(MODE_DIR)/Objects/module2/moduleTwoRTP.o : $(PRJ_ROOT_DIR)/moduleTwoRTP.c $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(WIND_HOME)/compilers/diab-5.9.4.6/WIN32/bin/dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -Y I,+C:/WindRiver/workspace/VSB_zfas-alt-soc-gen5_smp_CBEV_REL_X27X_03_maj/usr/h/public/c++03:C:/WindRiver/workspace/VSB_zfas-alt-soc-gen5_smp_CBEV_REL_X27X_03_maj/usr/h/public:$(WIND_HOME)/compilers/diab-5.9.4.6/WIN32/bin/../../include/diab -Xansi -WDVSB_DIR=$(VSB_DIR)  -W:c++:.CPP  -Xfp-fast -Xforce-declarations -ei4171,4188,4191,4223,4513,5152,5457,2273,5387,5388,1546   -Xmake-dependency=0xd $(IDE_DEFINES) $(DEFINES) $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<"


module2/$(MODE_DIR)/Objects/module2/moduleTwoServer.o : $(PRJ_ROOT_DIR)/moduleTwoServer.c $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(WIND_HOME)/compilers/diab-5.9.4.6/WIN32/bin/dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -Y I,+C:/WindRiver/workspace/VSB_zfas-alt-soc-gen5_smp_CBEV_REL_X27X_03_maj/usr/h/public/c++03:C:/WindRiver/workspace/VSB_zfas-alt-soc-gen5_smp_CBEV_REL_X27X_03_maj/usr/h/public:$(WIND_HOME)/compilers/diab-5.9.4.6/WIN32/bin/../../include/diab -Xansi -WDVSB_DIR=$(VSB_DIR)  -W:c++:.CPP  -Xfp-fast -Xforce-declarations -ei4171,4188,4191,4223,4513,5152,5457,2273,5387,5388,1546   -Xmake-dependency=0xd $(IDE_DEFINES) $(DEFINES) $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -o "$@" -c "$<"


OBJECTS_module2 = module2/$(MODE_DIR)/Objects/module2/moduleTwoCommunication.o \
	 module2/$(MODE_DIR)/Objects/module2/moduleTwoFileSending.o \
	 module2/$(MODE_DIR)/Objects/module2/moduleTwoHandleRoutines.o \
	 module2/$(MODE_DIR)/Objects/module2/moduleTwoRTP.o \
	 module2/$(MODE_DIR)/Objects/module2/moduleTwoServer.o

ifeq ($(TARGET_JOBS),1)
module2/$(MODE_DIR)/module2.vxe : $(OBJECTS_module2) | check_objdirs
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(WIND_HOME)/compilers/diab-5.9.4.6/WIN32/bin/dplus $(DEBUGFLAGS_Linker) $(CC_ARCH_SPEC) -Y I,+C:/WindRiver/workspace/VSB_zfas-alt-soc-gen5_smp_CBEV_REL_X27X_03_maj/usr/h/public/c++03:C:/WindRiver/workspace/VSB_zfas-alt-soc-gen5_smp_CBEV_REL_X27X_03_maj/usr/h/public:$(WIND_HOME)/compilers/diab-5.9.4.6/WIN32/bin/../../include/diab -Xansi -WDVSB_DIR=$(VSB_DIR)  -W:c++:.CPP  -Xfp-fast -Xforce-declarations -ei4171,4188,4191,4223,4513,5152,5457,2273,5387,5388,1546   -Xmake-dependency=0xd -Wl,-Bt=0x80000000 -o "$@" $(OBJECTS_module2) $(ADDED_OBJECTS) $(LIBPATH) -L$(VSB_DIR)/usr/lib/common $(ADDED_LIBPATH)  $(LIBS) $(IDE_LIBRARIES) $(ADDED_LIBS)  && if [ "$(DO_STRIP)" = "1" ]; then mv -f "$@" "$@.unstripped" && striparm -g -o "$@" "$@.unstripped";fi && if [ "$(EXPAND_DBG)" = "1" ]; then plink "$@";fi

else
module2/$(MODE_DIR)/module2.vxe : module2/$(MODE_DIR)/module2.vxe_jobs

endif
module2/$(MODE_DIR)/module2_compile_file : $(FILE) ;

_clean :: module2/$(MODE_DIR)/module2_clean

module2/$(MODE_DIR)/module2_clean : 
	$(TRACE_FLAG)if [ -d "module2" ]; then cd "module2"; rm -rf $(MODE_DIR); fi

force : 

TARGET_JOBS_RULE?=echo "Update the makefile template via File > Import > Build Settings : Update makefile template";exit 1
%_jobs : 
	$(TRACE_FLAG)$(TARGET_JOBS_RULE)

DEP_FILES := module2/$(MODE_DIR)/Objects/module2/moduleTwoCommunication.d module2/$(MODE_DIR)/Objects/module2/moduleTwoFileSending.d module2/$(MODE_DIR)/Objects/module2/moduleTwoHandleRoutines.d \
	 module2/$(MODE_DIR)/Objects/module2/moduleTwoRTP.d module2/$(MODE_DIR)/Objects/module2/moduleTwoServer.d
-include $(DEP_FILES)

OBJ_DIRS := module2/$(MODE_DIR)/Objects/module2
check_objdirs : 
	$(TRACE_FLAG)echo "Creating object dirs";\
	for dir in $(OBJ_DIRS); do\
		if [ ! -d "$$dir" ]; then mkdir -p "$$dir"; fi;\
	done


-include $(PRJ_ROOT_DIR)/*.makefile

-include *.makefile

TARGET_JOBS_RULE=$(MAKE) -f $(MAKEFILE) --jobs $(TARGET_JOBS) $(MFLAGS) $* TARGET_JOBS=1
ifeq ($(JOBS),1)
main_all : external_build $(PROJECT_TARGETS)
	@echo "make: built targets of `pwd`"
else
main_all : external_build 
	@$(MAKE) -f $(MAKEFILE) --jobs $(JOBS) $(MFLAGS) $(PROJECT_TARGETS) TARGET_JOBS=1 &&\
	echo "make: built targets of `pwd`"
endif 

# entry point for extending the build
external_build ::
	@echo ""

# main entry point for pre processing prior to the build
pre_build :: $(PRE_BUILD_STEP) generate_sources
	@echo ""

# entry point for generating sources prior to the build
generate_sources ::
	@echo ""

# main entry point for post processing after the build
post_build :: $(POST_BUILD_STEP) deploy_output
	@echo ""

# entry point for deploying output after the build
deploy_output ::
	@echo ""

clean :: external_clean $(CLEAN_STEP) _clean

# entry point for extending the build clean
external_clean ::
	@echo ""
