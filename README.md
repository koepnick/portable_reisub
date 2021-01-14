# portable_reisub
A simple example for creating an emergency external Linux reboot initiater

# Intent
I wanted to create a simple dongle-ly type device to power down my Raspberry Pis
and whatnot without simply pulling the plug or 3D printing a button enclosure for
the GPIO.

# Requirements
This project assumes that you have enabled and configured the so-called "magic" SysRq
commands. The short version requires running:

`cat /proc/sys/kernel/sysrq`

If the output is `1` then you're good to go. If it's `0` then you'll need to enable it.
If it's anything else then you *may* need to do some configuration with the bitmasked 
permissions.

For the nuclear option, use:

`echo "1" >/proc/sys/kernel/sysrq`

to temproarily enable every SysRq command. For hobbyists
that's probably fine. For server administrators, please, please RTFM and set this properly.

If you're happy with this then you can make it permanent by creating a file named
`/etc/sysctl.d/99-sysctl.conf` **or** edit `/etc/sysctl.conf` with the contents

```
kernel.sysrq=1
```

The SysRq commands go way beyond the scope of my little project. So read up. 


# Devices
This has been tested against the Arduino Pro Micro.

Note: This device has a single ATMega32U4 processor. If you do not have that chip, this
**will not** work in its current state. The 32U4 is able to present itself to a USB
host as a HID. From the point-of-view of the underlying operating system, all it sees
is a generic keyboard.

Most Arduino Unos do, in fact have both a ATMega328 and a ATMega32U4 processors, though
they're generally not advertized as such. Check out the ridiculously cool 
[HoodLoader2](https://github.com/NicoHood/HoodLoader2) project
for more details. As time permits I may integrate build files for those Unos.

# Environment
I have decided to take the plunge into [PlatformIO](https://docs.platformio.org/en/latest/core/quickstart.html)
and will be using that for building and library management.

The upside is that they integrate quite nicely into [VSCodium](https://vscodium.com/)

# Building
`make build` will attempt to pull the libraries and build the firmware

`make install` will attempt to upload the compiled firmware to the device

`make clean` will clean the build environment

# Tasks
- [ ] Document workflow required for Unos
- [ ] Add more hardware for dedicated reboot and shutdown buttons
