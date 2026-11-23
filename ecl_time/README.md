## Ecl Time vs Rostime

Many of the classes/methods in this package have many characteristics in
common with the [rostime](https://index.ros.org/p/rostime) package - in
fact they are almost identical. It was made before ros came about and is
kept in the ecl for both legacy reasons and because it is still
sometimes useful outside a ros runtime environment (particularly when
cross-compiling).

## Compiling & Linking

Include the following at the top of any translation unit:



```cplusplus
#include <ecl/time.hpp>

// The time classes
using ecl::Duration;
using ecl::MicroSleep;
using ecl::MilliSleep;
using ecl::NanoSleep;
using ecl::Sleep;
using ecl::Snooze;
using ecl::CpuWatch; // posix only
using ecl::StopWatch;
using ecl::TimeData;
using ecl::TimeStamp;
```



If outside ros, you will also need to link to *ecl_time*.

## Tutorials

- [Timestamps and Durations](#timestamps-and-durations)
  : timestamping and performing arithmetic on timestamps/durations.
- [Sleep](#sleep) : classes that put
  the thread to sleep for fixed or periodic intervals.
- [Stopwatch](#stopwatch) : devices
  to record the passing of time.
- [Benchmarking](#benchmarking) :
  tools to assist benchmarking programs.

## Cross Platform Support

### Posix RT Timers

Posix timers record times as a pair : (seconds,nanoseconds), so they
have a very fine resolution, but it needs to remembered that the system
latency will still affect their results. For example, sleeping for 1
nanosecond wont work as you expect, since the system latency will
usually mean the command has to wait for the scheduler to grant it a
slice of the action (usually a wait of around 1ms on a linux desktop).
This latency is usually configured by the scheduler being used by the
kernel.

Returning to the pair, the first unit, seconds is usually of a system
defined type. This allows it to be extendable to a larger type in the
future if the system time requires a larger value. The latter is
measured with the long variable, which is more than sufficient to cater
for 1x10\^9 units.

### MacOSX Timers

MacOSX timers are mostly posix, however they are missing the extensions
provided by the librt library, e.g. `clock_gettime` and
`clock_nanosleep`. The real downside of this is that it is not
possible to use absolute time with the macosx posix timers (i.e.
periodic timers will drift).

There are another set of mac specific timers that will let you do this,
but it has not yet been implemented.

### Windows Timers

Not yet implemented.

## Timestamps and Durations

- **Description:** Timestamping and performing arithmetic on
  timestamps/durations.
- **Keywords:** ecl timestamps durations
- **Tutorial Level:** INTERMEDIATE

### Timestamps

On a posix system, the timestamp class can be used to capture the
current time. It does this using the `MONOTONIC_CLOCK` which
calculates the time since the cpu was turned on. It has the advantage in
that you are guaranteed that the clock will never jump backwards to
correct for drift which is imperative for control systems running high
frequency loops.

It can be also used just to store a time/duration in a convenient
structure.

### Initialising



```cplusplus
TimeStamp time_system;           // Automatically captures system time since Epoch.
TimeStamp time_double(3.21)      // Initialise with a decimalised time (slow).
TimeStamp time_pair(3,210000000) // Initialise with a (s,ns) pair (fast for posix rt systems).
```



These operations can also be performed to set the timestamp after
construction:



```cplusplus
time_system.stamp();         // Automatically captures system time since Epoch.
time_double.stamp(3.21)      // Initialise with a decimalised time (slow).
time_pair.stamp(3,210000000) // Initialise with a (s,ns) pair (fast for posix rt systems).
```



All the usual comparison (==,!=,<=,>=,<,>) and mathematical
(+,-,+=,-=) operations can also be used.



```cplusplus
if ( time_system > time_double ) {
    time_system -= time_double;
}
```



Streaming:



```cplusplus
TimeStamp timestamp; // captures current time
std::cout << timestamp << std::endl; // 1682346.235653090
```



/!\\ **Caution**: The only thing to be wary of with timestamps is to
remember that they must always be positive. This was a design decision
that keeps the timestamp class as light as possible. If negativity was
introduced, an extra sign bit would be required, and in almost all
timestamp operations, this is not necessary.

**Exceptions**: The timestamp class will throw exceptions (in debug mode
only) whenever a timestamp method is used that would create a negative
timestamp.

### Durations

Durations are intended to intuitively represent the passage of time.
Although is is conceptually different from a timestamp, the
functionality under the hood is currently identical. Subsequently, the
`ecl::TimeStamp` class is currently typedef'd to the
`ecl::Duration` class.

This might change at some point in the future if we require negativity
(as mentioned above).

## Sleep

- **Description:** Classes that put the thread to sleep for fixed or
  periodic intervals.
- **Keywords:** sleep
- **Tutorial Level:** INTERMEDIATE

### Sleep

Some simple sleep classes. They can be used directly or preconfigured.



```cplusplus
Duration duration(1,300000000);
Sleep sleep;
MilliSleep sleep_ms;
MicroSleep sleep_us;
NanoSleep sleep_ns;

// Direct sleep commands
sleep(duration);
sleep(3);
sleep_ms(3500);
sleep_us(500000);
sleep_ns(500000000);

// Preconfigured (i.e. use last configured command)
MilliSleep pc_sleep_ms(duration);
sleep_ms(); // uses the last configuration
pc_sleep_ms(); // uses the constructor configuration
```



### Snooze

Snooze is a periodic sleeper, useful in control loops where you want to
exactly control the time taken by each loop. Using a regular sleep
function to do this can cause some time drift problems (refer to the
snooze class documentation for more detail). The snooze class gets
around this by setting its periodic timestamps off the absolute clock
time rather than calculating relative time splits.



```cplusplus
Snooze snooze(Duration(0,20000000); // 20ms snooze
// Some preliminaries
snooze.initialise(); // make sure the snoozer is sync'ed with the current time.
while (1) {
    // do some work
    snooze();
}
```



Note, this can be problematic if the periodic timestamps get behind the
current time. To remedy this, by default the class validates the
timestamp at each check and syncs it with the current time if it starts
to lag behind (can easily be caused by the system scheduler knocking it
out of whack in favour of another process). This can be manually turned
off in the constructor if you're confident of the timing processes and
this will marginally reduce the snoozer's latency.

## Stopwatch

- **Description:** Devices to record the passing of time.
- **Keywords:** ecl stopwatch
- **Tutorial Level:** INTERMEDIATE
- **Next Tutorial:**
  [Benchmarking](#benchmarking)

### StopWatch

This is a fairly intuitive class and uses the `TimeStamp` class under
the hood for recording times.

Note that the stopwatch starts automatically, just use `restart()` if
you wish to reset and start again.



```cplusplus
StopWatch stopwatch;
TimeStamp time;
time = stopwatch.split()
cout << time << endl;
time = stopwatch.elapsed()
cout << time << endl;
stopwatch.restart();
```

## Benchmarking

- **Note:** This tutorial assumes that you have completed the previous
  tutorials: [Stopwatch](#stopwatch).
- **Description:** Tools to assist benchmarking programs.
- **Tutorial Level:** INTERMEDIATE

### CpuWatch

/!\\ Requires : `librt`

This is a variation of the stopwatch for systems with `librt`. The
time measured by the cpu watch is not system time, rather the time spent
by the process actually exeucting on the cpu. This is very useful for
*benchmarking programs*. Usage is exactly the same as for the
[stopwatch](#stopwatch) class.

### TimeData

It is useful when used with the `TimeData` class - this class helps
store timings from a `CpuWatch` and then analysing them with some
statistical methods.



```cplusplus
CpuWatch cpuwatch;
TimeData timings;
ecl::Duration duration;
for ( unsigned int i = 0; i < 100; ++i ) {
    cpuwatch.restart();
    // do some work here
    duration = cpuwatch.split();
    timings.push_back(duration);
}
std::cout << "Average : " << timings.average() << std::endl;
std::cout << "Variance: " << timings.variance() << std::endl;
```

## Tutorials

- [Benchmarking](#benchmarking):
  Tools to assist benchmarking programs.
- [Sleep](#sleep): Classes that put
  the thread to sleep for fixed or periodic intervals.
- [Stopwatch](#stopwatch): Devices to
  record the passing of time.
- [Timestamps and Durations](#timestamps-and-durations):
  Timestamping and performing arithmetic on timestamps/durations.
