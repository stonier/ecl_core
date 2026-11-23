## Compiling & Linking

Include the following at the top of any translation unit:



```cplusplus
#include <ecl/ipc.hpp>

using ecl::Semaphore;
using ecl::SharedMemory;
```



If outside of ros, you will also need to link to `ecl_ipc`.

## Cross Platform Support

Currently there is only the posix structures. There is win32 code lying
around from an earlier version of the ecl, but since we're not using
windows these days, it is largely untested against more recent updates.
When we have a need, it will be reintroduced.

## Tutorials

- [Semaphores](#semaphores) -
  inter-process locks for use with shared memory.
- [Shared Memory](#shared-memory) -
  fast, typesafe, interprocess communication.

## Semaphores

- **Description:** Locks for multiple processes (use with shared
  memory).
- **Keywords:** ecl semaphores
- **Tutorial Level:** INTERMEDIATE
- **Next Tutorial:**
  [Shared Memory](#shared-memory)

There are many ways to implement semaphores (especially the counting
semaphores on posix), but I've kept it relatively simple here with the
task at hand being just to provide a lock that can be used when
accessing shared memory. Its usage is very similar to thread mutexes
with the only difference being the instantiation via a string identifier
(similar to the case for shared memory). Note, on windows semaphores are
usually referred to as mutexes (confusing!).



```cplusplus
//...First process
Semaphore semaphore("test_sem");
semaphore.lock();
// ... access shared memory here
semaphore.unlock();

//...Second process
Semaphore semaphore("test_sem");
semaphore.lock();
// ... access shared memory here
semaphore.unlock();
```



If another semaphore (doesn't have to be the same object, just a
semaphore instantiated from the same name) tries to lock an already
locked semaphore, it will wait until the first semaphore releases the
lock. Be wary of deadlocks.

## Shared Memory

- **Note:** This tutorial assumes that you have completed the previous
  tutorials:
  [Semaphores](#semaphores).
- **Description:** Simplified api-like interface to shared memory
  storage.
- **Keywords:** ecl shared memory
- **Tutorial Level:** INTERMEDIATE

### Overview

Used in conjunction with semaphores, shared memory sections provide the
fastest way for processes to directly communicate with each other.
Usually you reserve a block and then cast in and out of the direct
memory addresses allocated within the reserved memory. However, this is
not typesafe and error-prone, so the shared memory wrapper here instead
allocates a block that is implicitly tied to a data structure. The
following steps provide an easy, convenient way to access the reserved
memory block through a typesafe and well-structured api.

- Formulate a data structure of fixed size.
- Create a wrapper class that includes a semaphore, shared memory
  object, a read/write interface and pointer to the data.
- Instantiate the shared memory using with the data structure as a
  template argument.
- Point to the data section stored in the shared memory.
- Initialise the data section (if its the first accessor).
- Establish the read/write interface which will internally use
  semaphores to access the shared memory.



```cplusplus
struct DataStructure {
    int i;
};

class Data {
public:
    void readInteger(int i);
    void writeInteger(int j);

private:
    void initialise();

    SharedMemory< DataStructure > sm;
    Semaphore semaphore;
    DataStructure *data;
};

inline Data::Data() : sm("sm_test"), semaphore("sem_test"), data(NULL) {
    data = sm.data();
    initialise();
}

inline Data::readInteger(int i) {
    semaphore.lock();
    i = data->i;
    semaphore.unlock();
}
inline Data::writeInteger(int i) {
    semaphore.lock();
    data->i = i;
    semaphore.unlock();
}
```



### Important Usage Notes

#### No Variable Length Data Structures

Ensure you do not use variable length types (such as stl containers)
inside the data structure because the shared memory section allocates
memory based on the initial size of the data structure.

#### Who Initialises the Shared Memory Block

Initialisation and closure can be a little complicated. With
initialisation, you want to ensure that only the first accessor
initialises the memory to desired defaults, but there is no way of
guaranteeing via the shared memory class that you're the first
accessor - in some cases you could be accessing an already reserved
block. One way of getting around this is to set a magic number in the
data structure and see if that reads rubbish when you initialise. If it
does - then appropriately initialise all you data structure variables
and set your magic number accordingly - subsequent accesses from
different processes should find the correct magic number and not
initialise.

#### Closing the Shared Memory Block

With regards to closure, there is also no guarantee that you can
actually clean up the memory block. If everything runs fine and closes
without error, then it will be fine, but if your program crashes in some
unforeseen way and not all of the operating system signals are set up
(usually too much detail to bother with), then the memory block will
remain on the system. Often its easier to get some external script to
clean the memory sections.

## Tutorials

- [Semaphores](#semaphores): Locks for
  multiple processes (use with shared memory).
- [Shared Memory](#shared-memory):
  Simplified api-like interface to shared memory storage.
