/*
 * SPI flash interface
 *
 * Copyright (C) 2008 Atmel Corporation
 * Copyright (C) 2010 Reinhard Meyer, EMK Elektronik
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <spi.h>

static int spi_flash_read_write(struct spi_slave *spi,
		const u8 *cmd, size_t cmd_len,
		const u8 *data_out, u8 *data_in,
		size_t data_len, unsigned long flags)
{
	int ret;

	debug("%s cmd 0x%x cmd_len %ld, data_len %ld\n", __func__, cmd[0], cmd_len, data_len);

	if (data_len == 0)
		ret = spi_xfer(spi, cmd_len * 8, cmd, NULL, SPI_XFER_ONCE);
	else
		ret = spi_xfer(spi, cmd_len * 8, cmd, NULL, SPI_XFER_BEGIN);

	if (ret) {
		debug("SF: Failed to send command (%zu bytes): %d\n",
		      cmd_len, ret);
	} else if (data_len != 0) {
		ret = spi_xfer(spi, data_len * 8, data_out, data_in,
					flags | SPI_XFER_END);
		if (ret)
			debug("SF: Failed to transfer %zu bytes of data: %d\n",
			      data_len, ret);
	}

	return ret;
}

int spi_flash_cmd_read(struct spi_slave *spi, const u8 *cmd,
		size_t cmd_len, void *data, size_t data_len, unsigned long flags)
{
	return spi_flash_read_write(spi, cmd, cmd_len, NULL, data, data_len, flags);
}

int spi_flash_cmd(struct spi_slave *spi, u8 cmd, void *response, size_t len)
{
	return spi_flash_cmd_read(spi, &cmd, 1, response, len, SPI_XFER_CMD_DATA);
}

int spi_flash_xfer_data(struct spi_slave *spi, const u8 *data_out,
			u8 *data_in, size_t data_len, unsigned long flags)
{
	int ret;

	ret = spi_xfer(spi, data_len * 8, data_out, data_in, flags | SPI_XFER_END);
	return ret;
}

int spi_flash_cmd_write(struct spi_slave *spi, const u8 *cmd, size_t cmd_len,
		const void *data, size_t data_len, unsigned long flags)
{
	return spi_flash_read_write(spi, cmd, cmd_len, data, NULL, data_len, flags);
}
