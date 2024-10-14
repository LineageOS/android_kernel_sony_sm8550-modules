# Makefile for use with Android's kernel/build system

KBUILD_OPTIONS += SONY_CAMERA_ROOT=$(KERNEL_SRC)/$(M)
KBUILD_OPTIONS += KERNEL_ROOT=$(KERNEL_SRC)
KBUILD_OPTIONS += CAMERA_KERNEL_ROOT=$(KERNEL_SRC)/../sm8550-modules/qcom/opensource/camera-kernel
KBUILD_OPTIONS += MODNAME=sony_camera
KBUILD_OPTIONS += KBUILD_EXTRA_SYMBOLS=$(OUT_DIR)/../sm8550-modules/qcom/opensource/camera-kernel/Module.symvers

all: modules

modules dtbs:
	$(MAKE) -C $(KERNEL_SRC) M=$(M) modules $(KBUILD_OPTIONS)

modules_install:
	$(MAKE) M=$(M) -C $(KERNEL_SRC) modules_install

clean:
	$(MAKE) -C $(KERNEL_SRC) M=$(M) clean
