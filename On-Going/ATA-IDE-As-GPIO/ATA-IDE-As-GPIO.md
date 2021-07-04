<h1> Using PATA/IDE ports as GPIO pins</h1>

<h3>Motivation:</h3>

Some old PCs (Like the iMac G4 I've been using) don't have a parrallel port. But many have ATA/IDE interfaces for HDDS or DVD or CD-ROMs.

Thanks to <i><a href="http://ruemohr.org/~ircjunk/tutorials/elex/ata2isp/main.html">this</a></i> awesome blog post it was discovered that you can fool linux into thinking the pata port is a parralell port. 

The adress of the parallel port can be found by running <h2><b> lspci -nn</b></h2>
In this case the PATA port was labelled pata-macio. And the port register [0xff00] could be found. 

The command as root <h2><b> rmmod parport_pc </b></h2>
A new paraellel port can then be assinged to the address of the pata port using, 
<h2><b>modprobe parport_pc io=0xff00 irq=none,none,none</b></h2>

This worked on the G4 and the device at the parport was registered. 

C code to cycle through the outputs of the pata (now parallel port) data pins and set them high or low. This C code can be found in the scripts folder.

LEDs were connected to the PATA port to test the system/ a logic analyzer was also connected to check trigger recording of the data (not pictured)

<img src = "./assets/LED.PNG">
<img src = "./assets/bread.jpg">

Note the LEDs should have resistors before them but since the current the port can supply is low and they would not be on for long it was not worth it. 

Something interesting to note is the LEDS flash in a sequence on start up -- presumably during boot the kernel checks for devices and this read request gets picked up by the LEDS. 

Unfortunately this remains untested on the device... the <i>outb</i> function from the sys/io.h library is not available on powerpc linux architectures... In fact none of sys/io.h is, according to some forums this is because mac's do not allow direct hardware manipulation through io unless it is done at the kernel level. So one potential solution would be to write a kernel extension. 

Adding the outb function directly from the documentation for io was attempted but the gcc compiler was not happy with the inline assembly, and was not happy with the adresses that were being requested. 

Alternative write methods were tested, like the ioctl library, but this is a higher level library than the io library. 

Further testing needs to be done with either a kext or a non-mac based device to confirm, but it appears to be a promising direction. 

<h3> Thanks to: </h3>

https://github.com/sudipm-mukherjee/osfy/blob/master/userspace.c

https://www.howtoforge.com/tutorial/accessing-parallel-ports-on-linux/

http://www2.cs.siu.edu/~cs491-2/projects/anan2.pdf

<h3> Other useful resources:</h3>

https://www.opensourceforu.com/2015/06/using-parallel-ports-to-control-devices/

http://linuxcnc.org/docs/2.4/html/hal_parallel_port.html