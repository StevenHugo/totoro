# Totoro

* elegant thread-scheduler designed for the embedded system.

## Features

* round-robin schedule at same priority level
* simple semaphore implemented
* entry level and well easy learning

## How to install totoro

### Clone totoro

* git clone https://github.com/gilarus/totoro.git

### Clone totoro with submodules

* git clone --recursive https://github.com/gilarus/totoro.git

### Build totoro for your deivces

#### GCC

(un-avaiable now)

* $ cd ports/cmsis/device/XXX/build/gcc
* $ make

#### KEIL

* start your keil instance
* then just open project file under ports/cmsis/device/XXX/build/arm directory

## Before committing your patches

### Clean built files generated by compiler(keil, iar, gcc)

* cd scripts
* ./clean.sh

## Mirrors

* [https://soloing.org/pub/totoro](https://soloing.org/pub/totoro)
* [https://opensir.org/totoro](https://opensir.org/totoro)

## Credits && References

* [Semaphore](http://pubs.opengroup.org/onlinepubs/7908799/xsh/semaphore.h.html)
* [Atomthreads](https://atomthreads.com/)
* [Chapter 22: Pointers to Pointers](https://www.eskimo.com/~scs/cclass/int/sx8.html)