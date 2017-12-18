# version specify
VERSION := 0
SUBVERSION := 13
PATCHVERSION := .5
TOTORO_VERSION := $(VERSION).$(SUBVERSION)$(PATCHVERSION)

# compiler variables
TOOLS_PREFIX = arm-none-eabi-
CC      := $(TOOLS_PREFIX)gcc
AS      := $(TOOLS_PREFIX)as
LD      := $(TOOLS_PREFIX)ld
CPP     := $(TOOLS_PREFIX)cpp
OBJCOPY := $(TOOLS_PREFIX)objcopy

# Kernel source tree
KERNEL_SOURCE = arch drivers include kernel scripts test

# phony targets
.PHONY: all clean backup help info tags cscope

all:
	@echo 'Fix me'

backup:
	tar -zcvf totoro-$(TOTORO_VERSION).tar.gz $(KERNEL_SOURCE)

help:
	@echo 'totoro making decision'
	@echo 'make [option]'
	@echo 'options:'
	@echo '  help            display this'
	@echo '  backup          back up this project'
	@echo '                  generate totoro-x.x.x.tar.gz at parent directory'
	@echo '  info            display the infos of:'
	@echo '                    arch to be build for'
	@echo '                    cross toolchain to build with'
	@echo '                    totoro kernel version to be build'
	@echo '  md5             calculate md5 checksum'
	@echo '  clean           clean working space'

info:
	@echo Building architecture: $(ARCH)
	@echo Building toochain: $(TOOLS_PREFIX)
	@echo Totoro version: $(TOTORO_VERSION)

md5:
	@make backup
	md5sum totoro-$(TOTORO_VERSION).tar.gz

tags:
	touch cscope.files cscope.files.sorted tags; > cscope.files; > tags
	for n in $(KERNEL_SOURCE); do find $$n | grep "\.c$$\|\.h$$" >> cscope.files; done
	sort cscope.files > cscope.files.sorted; mv cscope.files.sorted cscope.files
	ctags -f tags -L cscope.files

cscope:
	cscope -b

clean:
	rm -rf cscope.files cscope.out tags
