#
# Makefile for lxs_touchscreen touch driver
#

lxs_touchscreen-objs = \
	lxs_ts.o \
	lxs_ts_fn.o \
	lxs_ts_hal.o \
	lxs_ts_hal_fw.o \
	lxs_ts_hal_prd.o \
	lxs_ts_sysfs.o \
	touch_sw82907.o
obj-$(TOUCHSCREEN_LXS) += lxs_touchscreen.o

KERNEL_SRC ?= /lib/modules/$(shell uname -r)/build
M ?= $(shell pwd)

KBUILD_OPTIONS += TOUCHSCREEN_LXS=m \
		TOUCHSCREEN_LXS_SW82907=y

KBUILD_EXTRA_SYMBOLS := $(OUT_DIR)/../sm8550-modules/qcom/opensource/display-drivers/msm/Module.symvers

modules modules_install clean:
	$(MAKE) -C $(KERNEL_SRC) M=$(M) $(KBUILD_OPTIONS) $(KBUILD_EXTRA_SYMBOLS) $(@)
