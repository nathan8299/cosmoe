# Tracker makefile
# Based on the makefile template

NAME= Deskbar

DEBUGGER= FALSE

ROOT_DIR = ..

#	the build tools are now in the top level directory
BIN_DIR = $(ROOT_DIR)/../bin/

SHARED_INCLUDE_PATHS = shared
TRACKER_INCLUDE_PATHS = tracker
LOCAL_INCLUDE_PATHS = $(ROOT_DIR)/$(SHARED_INCLUDE_PATHS) $(ROOT_DIR)/$(TRACKER_INCLUDE_PATHS)
SYSTEM_INCLUDE_PATHS = .
BERES = $(BIN_DIR)/beres

LIBPATHS = $(ROOT_DIR)/tracker/obj

WARNINGS = \
	-W -Wall \
	-Wno-multichar \
	-Woverloaded-virtual \
	-Wreturn-type \
	-Wnon-virtual-dtor \
	-Wno-ctor-dtor-privacy

ifeq ($(DEBUGGER), TRUE)
	OPTIMIZER := -O0
	DEBUG += -g
else
	OPTIMIZER := -O3
endif
DEPENDENCIES = .x86_dependencies


# @src->@ 

ORIGIN := ../../../../apps/OpenTracker/

sources_src := \
	BarApp.cpp				\
	BarMenuBar.cpp			\
	BarMenuTitle.cpp		\
	BarView.cpp				\
	BarWindow.cpp			\
	BeMenu.cpp				\
	DeskBarUtils.cpp		\
	ExpandoMenuBar.cpp		\
	ShowHideMenuItem.cpp	\
	StatusView.cpp			\
	StatusViewShelf.cpp		\
	TeamMenu.cpp			\
	TeamMenuItem.cpp		\
	TimeView.cpp			\
	WindowMenu.cpp			\
	WindowMenuItem.cpp		\
	ResourceSet.cpp \
	Switcher.cpp \
#

resources_rsrc := \
	Deskbar.rsrc \
	icon-freelogo.rsrc \
#

resources_rdef := \
	icons.rdef \
#

# @<-src@ 

SRCS := \
	$(sources_src) \
#

RDEFS := \
	$(resources_rdef) \
#

RAW_RSRCS := \
	$(resources_rsrc) \
#


# list the libraries your binary needs to link against
# (lbe, ltracker, etc.)
LIBS= cosmoe tracker

#	set the directory where object files and binaries will be created
OBJ_DIR		:= obj

# 	specify that the binary should be created in the object directory
TARGET		:= "$(OBJ_DIR)/$(NAME)"

MIMESET		:= mimeset
XRES		:= xres

CFLAGS := $(DEBUG) $(OPTIMIZER) $(WARNINGS) \
	-DDB_ADDONS -DOPEN_TRACKER=1 \
	-D_INCLUDES_CLASS_DEVICE_MAP=1 \
	-D_SUPPORTS_RESOURCES=1 \
	-D_SUPPORTS_FEATURE_SCRIPTING=1 \
#

LDFLAGS	:= $(DEBUG)

#	set the compiler and compiler flags
CC	:= gcc
LD	:= gcc
LDFLAGS += -Xlinker -soname=_APP_


# psuedo-function for converting a list of source files in SRCS variable
# to a corresponding list of object files in $(OBJ_DIR)/xxx.o
# The "function" strips off the src file suffix (.ccp or .c or whatever)
# and then strips of the directory name, leaving just the root file name.
# It then appends the .o suffix and prepends the $(OBJ_DIR)/ path
define SRCS_LIST_TO_OBJS
	$(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(foreach file, $(SRCS), \
	$(basename $(notdir $(file))))))
endef

define RDEFS_LIST_TO_RSRCS
	$(addprefix $(OBJ_DIR)/, $(addsuffix .rsrc, $(foreach file, $(RDEFS), \
	$(basename $(notdir $(file))))))
endef

OBJS = $(SRCS_LIST_TO_OBJS)
RSRCS = $(RDEFS_LIST_TO_RSRCS)

# create a unique list of paths to our sourcefiles
SRC_PATHS += $(sort $(foreach file, $(SRCS), $(dir $(file))))

# add source paths to VPATH if not already present
VPATH :=
VPATH += $(addprefix :, $(subst  ,:, $(filter-out $($(subst, :, ,$(VPATH))), $(SRC_PATHS))))

#	SETTING: build the local and system include paths
LOC_INCLUDES = $(foreach path, $(SRC_PATHS) $(LOCAL_INCLUDE_PATHS), $(addprefix -I, $(path)))
SYS_INCLUDES = `cat ../../../../cosmoe.specs` 
SYS_INCLUDES += $(foreach path, $(SYSTEM_INCLUDE_PATHS), $(addprefix -I, $(path)))

INCLUDES = $(LOC_INCLUDES) $(SYS_INCLUDES)

# SETTING: add the -L prefix to all library paths to search
LINK_PATHS = $(foreach path, $(SRC_PATHS) $(LIBPATHS), \
	$(addprefix -L, $(path)))

#	SETTING: specify the additional libraries to link against
#	if the libraries have a .so or .a prefix, or if they are _APP_ or _KERNEL_
#	simply add them to the list
LINK_LIBS += $(filter %.so %.a _APP_ _KERNEL_, $(LIBS))
#	if the libraries do not have suffixes and are not _APP_ or _KERNEL_
#	prepend -l to each name: be becomes -lbe
LINK_LIBS += $(foreach lib, $(filter-out %.so %.a _APP_ _KERNEL_, $(LIBS)), $(addprefix -l, $(lib)))

# add to the linker flags 
LDFLAGS += $(LINK_PATHS)  $(LINK_LIBS)

#	SETTING: add the defines to the compiler flags
CFLAGS += $(foreach define, $(DEFINES), $(addprefix -D, $(define)))

#	SETTING: add the additional compiler flags
CFLAGS += $(COMPILER_FLAGS)

#	SETTING: add the additional linker flags
LDFLAGS += $(LINKER_FLAGS)


#	define the actual work to be done	
default deskbar all: $(TARGET)

$(TARGET):	$(OBJ_DIR) $(OBJS) $(RAW_RSRCS) $(RSRCS)
		$(LD) -o $@ $(OBJS) $(LDFLAGS)
		#$(XRES) -o "$(TARGET)" $(RAW_RSRCS) $(RSRCS)
		#$(MIMESET) -f $@

install:	$(TARGET)
		copyattr -d $(TARGET) /system

#	rule to create the object file directory if needed
$(OBJ_DIR)::
	@[ -d $(OBJ_DIR) ] || mkdir $(OBJ_DIR) > /dev/null 2>&1

$(OBJ_DIR)/%.o : %.c
	$(CC) -c $< $(INCLUDES) $(CFLAGS) -o $@
$(OBJ_DIR)/%.o : %.cpp
	$(CC) -c $< $(INCLUDES) $(CFLAGS) -o $@
$(OBJ_DIR)/%.rsrc : %.rdef
	$(BERES) -o $@ $<

#	empty rule. Things that depend on this rule will always get triggered
FORCE:

#	The generic clean command. Delete everything in the object folder.
clean :: FORCE
	-rm -rf $(OBJ_DIR)/*

#	remove just the application from the object folder
rmapp ::
	-rm -f "$(TARGET)"

# dependency generation

DEPFLAG = -MM
SEDSCRIPT = sed -e's%^\(.*\.o\)%$$(OBJ_DIR)/\1%'

deps :: FORCE
	echo "# auto-generated by make deps; do not edit" > $(DEPENDENCIES)
	$(CC) $(INCLUDES) $(CFLAGS) $(DEPFLAG) $(SRCS) | $(SEDSCRIPT) >> $(DEPENDENCIES)

maintainerdeps :: FORCE
	p4 edit $(DEPENDENCIES)
	echo "# auto-generated by make deps; do not edit" > $(DEPENDENCIES)
	$(CC) $(INCLUDES) $(CFLAGS) $(DEPFLAG) $(SRCS) | $(SEDSCRIPT) >> $(DEPENDENCIES)
	echo "Change: new" > /tmp/tmp.deps
	echo "Status: new" >> /tmp/tmp.deps
	echo "Description:" >> /tmp/tmp.deps
	echo "	Auto-generated dependencies" >> /tmp/tmp.deps
	echo "Files:" >> /tmp/tmp.deps
	echo "	//depot/deskbar/"$(DEPENDENCIES) >> /tmp/tmp.deps
	cat /tmp/tmp.deps | p4 submit -i

cleandeps :: FORCE
	-rm -f $(DEPENDENCIES)

-include $(DEPENDENCIES)


