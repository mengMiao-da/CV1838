#include <stdlib.h>
#include <common.h>
#include <command.h>
#include <cvi_reboot.h>

__weak void software_root_reset(void)
{
}

static int do_cvi_reboot(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	software_root_reset();
	return CMD_RET_SUCCESS;
}

U_BOOT_CMD(
	cvi_reboot,	2,	0,	do_cvi_reboot,
	"bootloader control block command",
	"cvi_bcb <interface> <dev> <varname>\n"
);

