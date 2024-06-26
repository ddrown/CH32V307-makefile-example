# Basic CH32V307 RISCV Makefile project

Requirements:
 - xpack riscv toolchain (riscv-none-embed-)
 - minichlink-307 in path (https://github.com/ddrown/minichlink-307)

Set up udev rules for WCH link (see minichlink-307)

Make project
```
make
```

Flash to micro (will compile if needed)
```
make flash
```

# Using this in another project

Check this repo out as a submodule, in the directory `CH32V307-makefile-example`. Put your code under `./src`.

Create a `Makefile`:
```
VENDOR_DIR := ./CH32V307-makefile-example/vendor
include ./CH32V307-makefile-example/Makefile
```

For example https://github.com/ddrown/usbhs-cdc

# Licence

Unless otherwise stated files are licensed as BSD 2-Clause

Files under `vendor/` are from openwch (https://github.com/openwch/ch32v307) Licensed under Apache-2.0
Makefile is based on an example here: https://spin.atomicobject.com/2016/08/26/makefile-c-projects/
