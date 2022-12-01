obj-y += lpm_handler.o padcfg.o
ifneq ($(SOC),$(filter $(SOC), j7200))
obj-y += rtc.o gtc.o
endif
obj-$(CONFIG_LPM_INCLUDE_OSAL) += osal/
