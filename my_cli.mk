MY_CLI_VERSION = 1.0
MY_CLI_SITE = $(TOPDIR)/package/my_cli
MY_CLI_SITE_METHOD = local

define MY_CLI_BUILD_CMDS
    $(TARGET_CC) $(TARGET_CFLAGS) -o $(@D)/my_cli $(@D)/my_cli.c
endef

define MY_CLI_INSTALL_TARGET_CMDS
    $(INSTALL) -D -m 0755 $(@D)/my_cli $(TARGET_DIR)/usr/bin/my_cli
endef

$(eval $(generic-package))

