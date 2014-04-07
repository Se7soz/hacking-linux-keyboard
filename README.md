hacking-linux-keyboard
======================

A Linux kernel module that simulates key presses without pressing any keys, in this module i press the left key whenever the user presses any key, so that he writes from right to left instead of writing from left to right.


Features

    Report key presses and releases to the linux input module
    Sniffing linux keyboard strokes

Video demo:

    http://se7so.blogspot.com/2012/12/hacking-linux-keyboard.html
    
Compile & Run:

    1. Build
	    make
    2. Load
	    sudo insmod kbd.ko
	 3. Unload
	    sudo rmmod kbd
