#!/bin/bash

# the script for cleaning all of
# temp files before committing
# your contribution.

ROOT=..
RM="rm -rf"
CP=cp
MV=mv

devices="nrf52 stm32f0xx"
toolchains="arm gcc iar"

# for arm toolchain
for device in $devices
do
	$CP $ROOT/ports/cmsis/device/$device/build/arm/totoro.uvprojx ./
	$RM $ROOT/ports/cmsis/device/$device/build/arm/*
	$MV ./totoro.uvprojx $ROOT/ports/cmsis/device/$device/build/arm
done

# for gcc toolchain
for device in $devices
do
	$RM $ROOT/ports/cmsis/device/$device/build/gcc/out
done
