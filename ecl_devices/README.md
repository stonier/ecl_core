## Overview

Devices provide a c++ interface (usually on top of a lower level api
such as posix) for input-output manipulation.

It's pretty hard to find a library that treats devices in anything but
an ad-hoc way. There is no consistent interface. This attempts to bring
that to the subset of devices that control systems use. It also allows
hooking of streams to each and any of the devices. Also of interest,
there are a few very theoretical approaches to writing c++ devices
(sources, sinks, seekable, etc ..). The ecl's first version too was
along these lines, but ultimately for control systems, being practical
wins over syntactic correctness.

The devices here are kept as consistent and practical as possible
without sacrificing speed.

## Compiling & Linking

Include the following at the top of any translation unit:



```cplusplus
#include <ecl/devices.hpp>

// Device Classes
using ecl::OFile;
using ecl::SharedFile;
using ecl::Serial;
using ecl::OConsole; // Also IConsole, EConsole, but dont use directly, use console streams instead.
using ecl::String;   // Dont use directly, use StringStream instead.
using ecl::SocketClient; // Simple and does ipv4 only.
using ecl::SocketServer; // Simple and does ipv4 only.
```



If outside ros, you will also need to link against *ecl_devices*.

## Tutorials

- [Introduction to Ecl Devices](#introduction-to-ecl-devices)

## Examples

- `src/examples/serial_timeout.cpp` : shows off the low latency
  timeout code \[posix only\].

These are in [ecl_core_apps](https://index.ros.org/p/ecl_core_apps).

- `src/benchmarks/files.cpp`
- `src/demos/socket_client.cpp`
- `src/demos/socket_server.cpp`
- `src/utils/hex.cpp` : simple utility for reading/writing hex across
  the serial cable.
- `src/utils/serial.cpp` : simple serial testing utility.

## Introduction to Ecl Devices

- **Description:** Introduces the general framework for ecl devices.
- **Keywords:** ecl devices
- **Tutorial Level:** INTERMEDIATE
- **Next Tutorial:**
  [Serial Devices](#serial-devices)

### Device Usage

#### Open/Close

All devices have both RAII and non-RAII setup methods. In practice, this
means you either bundle all configuration into the constructor, or you
utilise the `open()` method to do configuration yourself. Usually RAII
is the more ideal approach, but sometimes its inconvenient so the latter
method is also available. For example, the serial class:



```cplusplus
Serial serial_raii("/dev/ttyS0",BaudRate_115200,DataBits_8,StopBits_1,NoParity); // RAII

Serial serial_nonraii;
serial_nonraii.open("/dev/ttyS0",BaudRate_115200,DataBits_8,StopBits_1,NoParity); // non-RAII
```



Cleanup is always done in the destructor, though if you need to manually
open/close a device frequently, a `close()` method is also provided.

#### Read/Write

Some class are output devices (only write), others are input devices
(only read) and some can do both. The read and write modes will
sometimes be configurable, (e.g. timeout or non-blocking for serial
reads), however the actual read and write operations will always be the
same.



```cplusplus
int n;
char buffer[256];
n = source.read(buffer,256);
n = sink.write("dude\n",5);
```



#### Exceptions

Exceptions (enabled by default) will be thrown in most functions for
errors which are not likely to be used in a fast control loop.
Constructors, open and close, configure methods etc. Others, such as
read and write calls will throw exceptions only in debug mode.

When exceptions are not enabled, or running in release mode, error flags
can be checked in the return values for most of these functions. Refer
to [ecl_exceptions](https://index.ros.org/p/ecl_exceptions) for more
information.

#### Concepts

Essentially, a device class can be written in any way you please.
However, if you wish to connect it to higher level components, in
particular, streams, you must ensure you class satisfies certain device
concepts. Refer to [ecl_concepts](https://index.ros.org/p/ecl_concepts)
for more information.

### Devices

#### OFile

- *IO*: write
- *Seekable*: no
- *Sync/Async*: synchronous

This is the logger class. Since its primary purpose is to serve logging,
the option to make it seekable was dropped to keep it nice and simple.

#### Serial

- *IO*: read/write
- *Seekable*: no
- *Sync/Async*: synchronous

The most important thing to note with the serial class is that it really
doesn't implement much of the underlying api. Rather it wraps a
configuration appropriate for control and keeps it as simple as
possible. Of the possible read modes, it utilises only a timeout mode
and a non-blocking mode. The other modes generally do not work very well
at the speed that control loops need to run.

#### String

- *IO*: read/write
- *Seekable*: no
- *Sync/Async*: synchronous

This is a virtual device used for storing and converting strings
(similar to Converters, but more general). It is not intended for direct
use, but as a mechanism for the stringstream class which functions very
similarly to the c++ stringstream classes.

#### Sockets

- *IO*: read/write
- *Seekable*: no
- *Sync/Async*: synchronous

These are a very simple/rough implementation of ipv4. It isn't designed
to be an industrial strength tool - just something for simple cross
platform connections to enable quick and simple remote debugging program
builds (or similar).

## Tutorials

- [Introduction to Ecl Devices](#introduction-to-ecl-devices):
  Introduces the general framework for ecl devices.
- [Serial Devices](#serial-devices):
  How to use the serial class for RS232/485 connections.

## Serial Devices

- **Note:** This tutorial assumes that you have completed the previous
  tutorials:
  [Introduction to Ecl Devices](#introduction-to-ecl-devices).
- **Description:** How to use the serial class for RS232/485
  connections.
- **Keywords:** ecl serial
- **Tutorial Level:** INTERMEDIATE

TODO!!!
