## Overview

Signals and slots provide a means for intra-process communication. The
classes here let you have a many-to-many relationship (unlike most event
callback techniques), and also templatise the data transfer to allow the
coder to customise the event data that is communicated from signal to
slot. It also implements a few conditional (event) related classes.

- [Background](#background) - non-essential
  historical notes.
- [Comparisons](#comparisons) - ecl_sigslots
  vs nodelets vs ecto.

## Features

- *Lightweight* - implements only the necessary features for practical
  usage.
- *Fully typesafe* - signal-slot pairs *must* have the same type, loaded
  functions must also agree.
- *Convenient slot loading* - global/static and member functions can be
  loaded with the same api.
- *Naming* - can use posix style names to identify and perform
  convenient connections/disconnections.
- *Thread safe* - slots can disconnect/self-destruct without worrying
  about segfaulting across threads.

## Definitions

### Signals

Anywhere that triggers an event requiring a callback to be executed can
be implemented with a signal. These can be placed anywhere in your code
and can be connected to one or many slots.

### Slots

Anywhere that a callback function is required can be implemented with a
slot. These can be placed anywhere in your code and are initialised with
either a static (global) function, or a member function. Once
initialised, they can be hooked up to a signal.

### Message Data

The signal-slot pairs developed here only ever accept one template
argument representing the data to be transmitted from signal to slot. It
would be easy to extend this to more (aka SigSlot/Boost) but I have yet
to find a need for it - if you wish multiple arguments, simply wrap up
your data in a single struct/class. Conceptually, this makes the code
more readable anyway.

The data class itself could be as simple as an error id or as
complicated as the current state in a fsm. Note that both signal and
slot must use the same type.

## Compiling & Linking

Include the following at the top of any translation unit:



```cplusplus
#include <ecl/sigslots.hpp>

// The types
using ecl::Signal;
using ecl::Slots;
```



You will also need to link to *ecl_sigslots*.

## Tutorials

- [Introduction to Sigslots](#introduction-to-sigslots) -
  creating, connecting and triggering signals and slots.
- [Relaying Signals](#relaying-signals) -
  relaying data from one signaller to the next.
- [Debugging Sigslots](#debugging-sigslots) -
  tools to help debug sigslots problems.

## Examples

- [src/examples/sigslots.cpp](http://ros.org/doc/groovy/api/ecl_sigslots/html/examples_2sigslots_8cpp_source.html)
- [src/examples/sigslots_manager.cpp](http://ros.org/doc/groovy/api/ecl_sigslots/html/sigslots__manager_8cpp_source.html)

## Background

The ideas for this signal/slots implementation come from a few sources.

- Qt
- [Sigslot](http://sigslot.sourceforge.net/)
- [Boost Signals](http://www.boost.org/doc/libs/1_48_0/doc/html/signals.html)

Qt was the original signal/slots implementation, but it needs a
pre-processor to compile the code. Sigslot and Boost on the other hand
are pure ISO C++, but both have some disadvantages. The boost
implementation is fairly heavy and a little cumbersome, although its now
morphing into version 2 with even more functionality (I haven't yet
road tested a comparison between the two). Sigslot was the precursor, is
more lightweight, but has some oddities - it isn't fully typesafed,
can't handle global/static function loading.

None of these are thread-safe and it can be somewhat inconvenient
manually connecting signal-slot pairs when they are buried far from each
other (e.g. deep in parallel heirarchies of c++ objects).

This motivated this library - what was needed was an abstract way of
connecting pairs with an engine in the background to do the hard work -
ultimately leaving the programmer free from any tedious details. To do
this, the sigslots library uniquely names connections (i.e. topic name
in ros-speak), via a string. Signals and slots can connect to the topic
simply by referring to a string. This was originally motivated by the
way many posix ipc structures connect (e.g. semaphores and shared
memory), but later also merged very neatly with the way ros topics
connect (in particular nodelets). Adding mutex's for thread safety so
that sigslot destruction would occur safely was the next step.

## Comparisons

### Comparison

- ecl_sigslots
- [nodelets](https://index.ros.org/p/nodelet)
- [ecto](http://plasmodic.org/)

All three do *intra-process communications* and are a means of doing
zero-cost transfer of data between threads in a process.

### Sigslots and Nodelets

We were using ecl sigslots before ros came out, and then when ros came
out, it gave us a fast means of doing quick communication between ros
library packages that had been bundled together into a ros application
package.

When [nodelets](https://index.ros.org/p/nodelet) came out, with a very
similar syntax (connections via topics identified by strings), we could
almost immediately drop out alot of our sigslots for nodelets.

The nodelets impose extra structure though, and sigslots can be
convenient still in some cases.

#### Non Ros Programs

Ecl packages have no dependency on any ros libraries, they just utilise
the ros build environment. Similarly, we often do this to create non-ros
programs, especially cross-compiled embedded programs. The very low
overhead of ecl_sigslots is advantageous in
this regard - much lower than boost, qt or a ros.

#### Hiding Communications from Ros

Sometimes its convenient to hook up sigslots in a single multi-threaded
package where you don't want to expose extra topics needlessly.

#### Comms in a Single Application

Also, ecl sigslots don't impose the const'ness of the data being
transferred (in most cases const imposition is a good thing - a library
should never use non-const data references because they then can't
control/guarantee behaviour for the users of their library). However
inside a single multi-threaded application where control is guaranteed,
this can be ok, and it provides a convenient way to pass references to
shared data around the application. If you can find another way to do
this though, it is to be encouraged - you need to take special care to
avoid multi-threaded bugs.

### Ectos

(I haven't used this yet, so the information below may be slightly
innacurate - will update once we've road tested it).

This is a new project at willow for intra-process communications that
adds a framework for scheduling and synchronisation. This avoids the
completely asynchronous nature of sigslots and ros comms which should be
very beneficial in alot of control applications.

### Errata

Disregarding the other sigslot style implementations for the reasons
discussed [here](#background).

## Introduction to Sigslots

- **Description:** Creating, connecting and triggering signals and
  slots.
- **Keywords:** ecl sigslots
- **Tutorial Level:** INTERMEDIATE
- **Next Tutorial:**
  [Relaying Signals](#relaying-signals)
  [Debugging Sigslots](#debugging-sigslots)

### Slot Loading

Loading of slots can be done directly to free or member functions
through the constructors. Below is a simple example for various types of
loading.



```cplusplus
void f(const int& i) {}
class A {
public:
    void f(const int& i) {}
};
// ...
A a;
Slot<const int&> slot0(f);
Slot<const int&> slot1(&A::f,a);
```



### Connecting



```cplusplus
Signal<const int&> signal;
Slot<const int&> slot(f);
signal.connect("Dudes");
slot.connect("Dudes");
```



Signals and slots have no limit to the number of connections they may
make.

### Emitting

Every time a signal emits, the connected slots are consecutively run
with the data that is emitted.



```cplusplus
signal.emit(3); // Pass the '3' to all the slot functions.
```



Every emit, the slots are consecutively run - this means that your slots
should by nature be short and concise! Otherwise you'll get serious
bottlenecks. This is always a good habit to get into for slots otherwise
you'll frequently run into problems. If you have a heavy callback,
consider spinning that callback off into a thread. That way the thread
response will still be quick (cost of a thread creation) and you can
still manage heavy workloads.

### Design Considerations

- Keep your slot callbacks concise\...failing that, reference them or
  spin the work off into a thread!
- For data slots use const references, saves a copy and prevents your
  original class losing control of its variables.
- Slots w/ member functions should be member variables of the same
  class, this guarantees the function is always valid.
- The sigslots manager may become a bottleneck if you are
  creating/connecting/disconnecting a large number of slots.

<!-- -->

- If you do need a sigslot implementation that can handle massive
  numbers of sigslots, fast connection and disconnection, then you
  probably need to look at the old ecl signals or boost/qt. At the
  moment, we can't foresee a need for that in control systems, but if
  needed, this library can be extended.

## Relaying Signals

- **Note:** This tutorial assumes that you have completed the previous
  tutorials:
  [Introduction to Sigslots](#introduction-to-sigslots).
- **Description:** Relaying data from one signaller to the next.
- **Keywords:** ecl relaying signals
- **Tutorial Level:** INTERMEDIATE
- **Next Tutorial:**
  [Debugging Sigslots](#debugging-sigslots)

### Relaying

A signal can relay another signal, effectively posing temporarily as a
slot.



```cplusplus
Signal<> signal;
Signal<> signal_relay;
Slot<> slot(f);
signal.connect("First_Topic");
signal_relay.connectAsSlot("First_Topic");
signal_relay.connect("Second_Topic");
slot.connect("Second_Topic");
signal.emit();
```

## Debugging Sigslots

- **Note:** This tutorial assumes that you have completed the previous
  tutorials:
  [Introduction to Sigslots](#introduction-to-sigslots),
  [Relaying Signals](#relaying-signals).
- **Description:** Tools to help debug sigslots problems.
- **Keywords:** ecl sigslots
- **Tutorial Level:** INTERMEDIATE

Often you may wish to see what is actually connected. This can be done
by calling the `SigSlotsManager<T>::printStatistics()` function.
Note that there is a manager for each templatised family of sigslots
(i.e. `SigSlotsManager<>`, `SigSlotsManager<int>`). Some example
code:



```cplusplus
A a;
Signal<> sig_void;

Slot<> slot_void0(g);
Slot<> slot_void1(&A::g,a);

sig_void.connect("void_test");
slot_void0.connect("void_test");
slot_void1.connect("void_test");

sig_void.emit();
ecl::SigSlotsManager<>::printStatistics();
```



would output:



```cplusplus
  Topics
    Name: void_test
    # Subscribers: 2
    # Publishers : 1
```

## Tutorials

- [Debugging Sigslots](#debugging-sigslots):
  Tools to help debug sigslots problems.
- [Introduction to Sigslots](#introduction-to-sigslots):
  Creating, connecting and triggering signals and slots.
- [Relaying Signals](#relaying-signals):
  Relaying data from one signaller to the next.
