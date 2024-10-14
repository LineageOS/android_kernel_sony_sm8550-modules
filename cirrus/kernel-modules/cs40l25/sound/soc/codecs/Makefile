cirrus_cs40l2x_codec-objs = cs40l2x.o
obj-$(CONFIG_SND_SOC_CS40L2X) += cirrus_cs40l2x_codec.o

KERNEL_SRC ?= /lib/modules/$(shell uname -r)/build
M ?= $(shell pwd)
CUSTOM_INCLUDE ?= -I$(shell pwd)/include/

KBUILD_OPTIONS += CONFIG_SND_SOC_CS40L2X=m \
		  ccflags-y='$(CUSTOM_INCLUDE)'

KBUILD_EXTRA_SYMBOLS := $(M)/../../../drivers/misc/Module.symvers

modules modules_install clean:
	$(MAKE) -C $(KERNEL_SRC) M=$(M) $(KBUILD_OPTIONS) $(KBUILD_EXTRA_SYMBOLS) W=1 $(@)
