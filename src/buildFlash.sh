#!/bin/sh
arm-linux-gnueabi-gcc ./main.c startup_gcc.c -ggdb -mthumb -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -Os -ffunction-sections -fdata-sections -MD -std=c99 -Wall -pedantic -DPART_LM4F120H5QR -c -I/home/itchy8me/Deployment/stellaris_launchpad/StellarisWare-EK-LM4F120XL-9453  -DTARGET_IS_BLIZZARD_RA1
arm-none-eabi-ld -T ./main.ld --entry ResetISR -o a.out ./startup_gcc.o ./main.o --gc-sections
arm-none-eabi-objcopy -O binary a.out main.bin
~/Deployment/stellaris_launchpad/stellaris_launchpad-lm4f120xl/lm4tools/lm4tools-master/lm4flash/lm4flash ./main.bin