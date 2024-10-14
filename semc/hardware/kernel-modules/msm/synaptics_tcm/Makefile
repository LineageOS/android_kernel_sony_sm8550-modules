synaptics_tcm_ts-objs := \
	synaptics_tcm_core/ \
	synaptics_tcm_device/ \
	synaptics_tcm_core/ \
	synaptics_tcm_device/ \
	synaptics_tcm_diagnostics/ \
	synaptics_tcm_i2c/ \
	synaptics_tcm_recovery/ \
	synaptics_tcm_reflash/ \
	synaptics_tcm_testing/ \
	synaptics_tcm_touch/
obj-m += synaptics_tcm_ts.o

KERNEL_SRC ?= /lib/modules/$(shell uname -r)/build
M ?= $(shell pwd)
CUSTOM_INCLUDE ?= -I$(shell pwd)/include/

all:
	$(MAKE) -C $(KERNEL_SRC) M=$(M) modules $(KBUILD_OPTIONS)

modules_install:
	$(MAKE) INSTALL_MOD_STRIP=1 M=$(M) -C $(KERNEL_SRC) modules_install

clean:
	$(MAKE) -C $(KERNEL_SRC) M=$(M) clean $(KBUILD_OPTIONS)
