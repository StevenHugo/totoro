# Totoro

Tiny kernel for ARMs.

## Features

* round-robin schedule at same priority level
* simple semaphore implemented
* entry level and well easy learning

## How to install totoro

### Clone totoro

```bash
git clone https://github.com/gilarus/totoro.git
```

### Build totoro for your devices

#### GCC

(un-avaiable now)

```bash
$ cd ports/cmsis/device/XXX/build/gcc
$ make
```

#### KEIL

* start your keil instance
* then just open project file under ports/cmsis/device/XXX/build/arm directory

## Mirror

* [https://io-lab.net/totoro](https://io-lab.net/totoro)

## Credits && References

* [Semaphore](http://pubs.opengroup.org/onlinepubs/7908799/xsh/semaphore.h.html)
* [Atomthreads](https://atomthreads.com/)
* [Chapter 22: Pointers to Pointers](https://www.eskimo.com/~scs/cclass/int/sx8.html)
