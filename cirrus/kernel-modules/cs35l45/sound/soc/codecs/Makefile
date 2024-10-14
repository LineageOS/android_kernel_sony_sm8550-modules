cirrus_wm_adsp-objs = wm_adsp.o
obj-$(CONFIG_SND_SOC_WM_ADSP) += cirrus_wm_adsp.o

cirrus_cs35l45-objs = cs35l45.o cs35l45-tables.o
ifneq ($(filter m y,$(CONFIG_SND_SOC_CS35L45_SPI)),)
   cirrus_cs35l45-objs += cs35l45-spi.o
else
   cirrus_cs35l45-objs += cs35l45-i2c.o
endif
obj-$(CONFIG_SND_SOC_CS35L45) += cirrus_cs35l45.o

KERNEL_SRC ?= /lib/modules/$(shell uname -r)/build
M ?= $(shell pwd)
CUSTOM_INCLUDE ?= -I$(shell pwd)/include/

KBUILD_OPTIONS += CONFIG_SND_SOC_WM_ADSP=m \
		  CONFIG_SND_SOC_CS35L45=m \
		  ccflags-y='$(CUSTOM_INCLUDE)'

modules modules_install clean:
	$(MAKE) -C $(KERNEL_SRC) M=$(M) $(KBUILD_OPTIONS) W=1 $(@)
