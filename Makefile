#---------------------------------------------------------------------------------
# devkitarm
#---------------------------------------------------------------------------------
ifeq ($(strip $(DEVKITARM)),)
	$(error "Please set DEVKITARM in your environment. export DEVKITARM=<path to>devkitARM)
endif

include $(DEVKITARM)/gba_rules
export PATH := $(DEVKITARM)/bin:$(PATH)

#---------------------------------------------------------------------------------
# version string
#---------------------------------------------------------------------------------
GBAXX_VERSION_MAJOR	:= 1
GBAXX_VERSION_MINOR	:= 0
GBAXX_VERSION_PATCH	:= 0
GBAXX_VERSION		:= $(GBAXX_VERSION_MAJOR).$(GBAXX_VERSION_MINOR).$(GBAXX_VERSION_PATCH)

#---------------------------------------------------------------------------------
# source and include folders
#---------------------------------------------------------------------------------
GBAXX_SRC_DIR     := src
GBAXX_INCLUDE_DIR := include/gba

GBAXX_CPU_FLAGS   := -mcpu=arm7tdmi -mtune=arm7tdmi -march=armv4t
GBAXX_THUMB_FLAGS := -mthumb -mthumb-interwork

#---------------------------------------------------------------------------------
# configuration compile flags
#---------------------------------------------------------------------------------
#GBAXX_CONFIGURATION_CFLAGS := -Og -D_DEBUG -g
GBAXX_CONFIGURATION_CFLAGS := -O3 -DNDEBUG

#---------------------------------------------------------------------------------
# options for code generation
#---------------------------------------------------------------------------------
GBAXX_CFLAGS   := $(GBAXX_CONFIGURATION_CFLAGS) $(GBAXX_CPU_FLAGS) $(GBAXX_THUMB_FLAGS) $(foreach dir,$(GBAXX_INCLUDE_DIR),-I$(CURDIR)/$(dir)) -Wall -fomit-frame-pointer -ffast-math
GBAXX_CXXFLAGS := $(GBAXX_CFLAGS) -fno-rtti -fno-exceptions -nostdlib -std=c++17
GBAXX_ASFLAGS  := -Wa,--warn $(GBAXX_THUMB_FLAGS)

# TODO : The rest of the Makefile