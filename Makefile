#---------------------------------------------------------------------------------
# Clear the implicit built in rules
#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------
ifeq ($(strip $(DEVKITARM)),)
$(error "Please set DEVKITARM in your environment. export DEVKITARM=<path to>devkitARM)
endif

include $(DEVKITARM)/gba_rules

#---------------------------------------------------------------------------------
# BUILD is the directory where object files & intermediate files will be placed
# SOURCES is a list of directories containing source code
# INCLUDES is a list of directories containing header files
#---------------------------------------------------------------------------------
BUILD		:=	build
SOURCES		:=	src
INCLUDES	:=	include

export LIBGBAXX_MAJOR	:= 0
export LIBGBAXX_MINOR	:= 0
export LIBGBAXX_PATCH	:= 0

VERSION	:=	$(LIBGBAXX_MAJOR).$(LIBGBAXX_MINOR).$(LIBGBAXX_PATCH)

#---------------------------------------------------------------------------------
# options for code generation
#---------------------------------------------------------------------------------
ARCH	:=	-mthumb -mthumb-interwork

CFLAGS	:=	-Wall\
			-pedantic -pedantic-errors\
			-mcpu=arm7tdmi -mtune=arm7tdmi -march=armv4t\
 			-fomit-frame-pointer\
			-ffast-math \
			-Wno-packed-bitfield-compat \
			$(ARCH)

ifeq ($(CONFIGURATION),Debug)
CFLAGS	+=	-Og -g -D_DEBUG
else
CFLAGS	+=	-O3 -flto -DNDEBUG
endif

CFLAGS	+=	$(INCLUDE)

CXXFLAGS	:=	$(CFLAGS) -fno-rtti -fno-exceptions -std=c++2a

ASFLAGS	:=	$(ARCH)
LDFLAGS	=	$(ARCH) -Wl,-Map,$(notdir $@).map

#---------------------------------------------------------------------------------
ifneq ($(BUILD),$(notdir $(CURDIR)))

export TARGET	:=	$(CURDIR)/lib/libgba++.a

export VPATH	:=	$(foreach dir,$(DATA),$(CURDIR)/$(dir)) $(foreach dir,$(SOURCES),$(CURDIR)/$(dir))

CPPFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))

export OFILES_SRC	:=	$(CPPFILES:.cpp=.o)

export OFILES	:=	$(OFILES_SRC)

export INCLUDE	:=	$(foreach dir,$(INCLUDES),-I$(CURDIR)/$(dir))
export DEPSDIR	:=	$(CURDIR)/build

.PHONY: $(BUILD) clean docs

$(BUILD):
	@[ -d lib ] || mkdir -p lib
	@[ -d $@ ] || mkdir -p $@
	@$(MAKE) --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile

docs:
	doxygen libgba++.dox

clean:
	@echo clean ...
	@rm -fr $(BUILD) *.tar.bz2

#---------------------------------------------------------------------------------
else

DEPENDS	:=	$(OFILES:.o=.d)

#---------------------------------------------------------------------------------
$(TARGET): $(OFILES)

#---------------------------------------------------------------------------------
%.a: $(OFILES)
	@echo $@
	@rm -f $@
	@$(AR) rcs $@ $(OFILES)

-include $(DEPENDS)

endif
#---------------------------------------------------------------------------------
