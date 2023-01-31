#include <common.h>
#include <linux/types.h>
#include <stdlib.h>

/* see dps.h */
uint32_t cvi_read32(volatile uint32_t *address)
{
	return *address;
}

/* see dps.h */
void cvi_write32(uint32_t value, volatile uint32_t *address)
{
	*address = value;
}

/* see dps.h */
uint8_t cvi_uncached_read8(volatile uint8_t *address)
{
	return *address;
}

/* see dps.h */
uint16_t cvi_uncached_read16(volatile uint16_t *address)
{
	return *address;
}

/* see dps.h */
uint32_t cvi_uncached_read32(volatile uint32_t *address)
{
	return *address;
}

/* see dps.h */
void cvi_uncached_write8(uint8_t value, volatile uint8_t *address)
{
	*address = value;
}

/* see dps.h */
void cvi_uncached_write16(uint16_t value, volatile uint16_t *address)
{
	*address = value;
}

/* see dps.h */
void cvi_uncached_write32(uint32_t value, volatile uint32_t *address)
{
	*address = value;
}

/* see dps.h */
void cvi_write_phys32(uint32_t value, volatile uint32_t *location)
{
	*location = value;
}

/* see dps.h */
void cvi_buffer_copy(volatile uint8_t *dst, volatile uint8_t *src, uint32_t size)
{
	memcpy((void *)dst, (void *)src, size);
}

/* Since this is a bare-metal system, with no MMU in place, we expect that there will be no cache enabled */

void cvi_cache_invalidate(uintptr_t address, size_t size)
{
#ifdef TENSILICA
	xthal_dcache_region_invalidate(address, size);
#endif
}

void cvi_cache_flush(uintptr_t address, size_t size)
{
#ifdef TENSILICA
	xthal_dcache_region_writeback(address, size);
#endif
}

void cvi_delay_ns(uint32_t ns)
{
}
