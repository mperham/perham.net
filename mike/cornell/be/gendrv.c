/*
 * Generic static PCI driver framework for BeOS DR8.  The driver API
 * is subject to change so use at your own risk!
 *
 * Note that drivers are written in C, not C++.
 *
 * Created 3/30/97 by Mike Perham (mperham@cs.cornell.edu)
 */

#include <device/KernelExport.h>
#include <device/Driver.h>

/*
 * As an example, we are an Intel EtherExpress driver
 * 		VENDOR_ID = Intel
 *		DEVICE_ID = EtherExpress 10/100
 *
 * See http://www.halcyon.com/scripts/jboemler/pci/pcicode
 * for a thorough PCI magic number list.
 */

#define VENDOR_ID	0x8086
#define DEVICE_ID	0x1227

device_entry devices[] = {
	{"/dev/ether", open_drv, close_drv, control_drv, 
			read_drv, write_drv},
	0
};

/*
 * init_driver()
 *
 * Used for generic initialization of the entire driver
 * (Semaphores, global data, etc).  Device-specific
 * initialization should wait until the actual device
 * open routine.
 */

long init_driver(void)
{
	return B_NO_ERROR;
}

/*
 * uninit_driver()
 *
 * Cleans up what init_driver did.  Should return
 * B_NO_ERROR since the driver is about to be unloaded.
 */

long uninit_driver(void)
{
	return B_NO_ERROR;
}

/*
 * open_dev()
 *
 * Finds the device, initializes it and returns.
 * WARNING ----------------------------------
 * I'm not sure what will happen if there are 
 * two of the same device in the same Box.
 */

long open_dev(device_info *devInfo, ulong flags)
{
	pci_info pinfo;
	long more_info;
	long offset = 52;

	for (i=0;i<PCI_DEV_MAX;i++) {
		if (get_nth_pci_info(i, &pinfo) == B_NO_ERROR) {
			if (pinfo.vendor_id == VENDOR_ID) &&
			   (pinfo.device_id == DEVICE_ID) {
			   	/*
			   	 * This is our device!
			   	 * As an example, read 4 bytes from the configuration
			   	 * area on the card.
			   	 */
			   	more_info = read_pci_config(pinfo.bus, pinfo.device, 
			   			pinfo.function, offset, sizeof(long));
			   	return B_NO_ERROR;
			}
		}
	}
	return B_ERROR;
}

/*
 * close_dev()
 *
 * Closes the device and does device-specific cleanup.
 */

long close_dev(device_info *devInfo)
{
	return B_NO_ERROR;
}

/*
 * read_dev()
 *
 * Reads data from the device, up to numBytes, into buffer.
 */

long read_dev(device_info *devInfo, void *buffer, 
				ulong numBytes, ulong position)
{
	ASSERT(amountRead <= numBytes);
	return amountRead;
}

/*
 * write_dev()
 *
 * Write numBytes of data from buffer to the device
 */

long write_dev(device_info *devInfo, void *buffer,
				ulong numBytes, ulong position)
{
	ASSERT(amountWritten <= numBytes);
	return amountWritten;
}

/*
 * control_dev()
 *
 * Used to configure and otherwise control the device.
 */

long control_dev(device_info *devInfo, ulong op, void *data)
{
	switch (op) {
		case B_GET_SIZE:
			break;
		case B_SET_SIZE:
			break;
		case B_SET_BLOCKING_IO:
			break;
		case B_SET_NONBLOCKING_IO:
			break;
		case B_GET_READ_STATUS:
			break;
		case B_GET_WRITE_STATUS:
			break;
		/*
		 * These next two are disk-specific
		 */
		case B_GET_GEOMETRY:
			break;
		case B_FORMAT:
			break;
		/*
		 * User defined config ops
		 */
		case ...:
			break;
		/*
		 * Bad op code
		 */
		default:
			return B_ERROR;
	}
	return B_NO_ERROR;
}
