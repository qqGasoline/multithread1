include ../Makefile.tests_common
USEMODULE += xtimer
FEATURES_REQUIRED += periph_timer
FEATURES_REQUIRED += periph_gpio
include $(RIOTBASE)/Makefile.include

