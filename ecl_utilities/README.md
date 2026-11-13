## Tutorials

- [Function Objects](#function-objects) -
  passing functions around as typed class objects.
- [Parameters](#parameters) -
  avoiding a profusion of get/set.
- [Reference Wrappers](#reference-wrappers) -
  when you want to pass a reference, but are only permitted to pass a
  copy.
- [Singleton](#singleton) - the
  classic singleton design pattern.

## Function Objects

- **Description:** Passing functions around as typed class objects.
- **Keywords:** ecl function objects
- **Tutorial Level:** INTERMEDIATE

### Introduction

Resolving c++ function passing (as arguments to other functions) is
complicated by the differences between global/static and member
functions as well as by the awkward syntax. Here we attempt to provide a
standardised approach to using them.

### Definition

One way of standardising the approach is to utilise the idea of a
function object (also known as functor). A function object is simply an
object that characterises a function. In c++, this has three advantages:

- Function code can be inlined (instead of repeated pointer calls) when
  used repetitively in a loop.
- The function object can maintain state, something which pure function
  callbacks cannot do.
- The syntax is much cleaner and more flexible.

An example of a unary function object is given below:



```cplusplus
class Sum {
    int val;
public:
    Sum(int i) :val(i) { }
    int operator()(int i) { return val+=i; }        // unary function
};
```



We also make a terminology distinction here when distinguishing between
*free* and *member* functions. Free functions are defined to be global
or static functions.

### Compiling & Linking

Include some or all of the following at the top of any translation unit
that requires compilation of class that uses parameters.



```cplusplus
#include <ecl/utilities.hpp>

// The classes
using ecl::NullaryFunction;
using ecl::UnaryFunction;
using ecl::BinaryFunction;
using ecl::NullaryFreeFunction;
using ecl::UnaryFreeFunction;
using ecl::BoundUnaryFreeFunction;
using ecl::NullaryMemberFunction;
using ecl::BoundNullaryMemberFunction;
using ecl::UnaryMemberFunction;
using ecl::PartiallyBoundUnaryMemberFunction;
using ecl::BoundUnaryMemberFunction;
using ecl::NullaryFunctionCopy;
using ecl::NullaryFunctionReference;
using ecl::UnaryFunctionCopy;
using ecl::UnaryFunctionReference;

// Overloaded utility functions
using ecl::generateFunctionObject;
```



Since it is a template class, no linking is required if you are only
using this class.

### Usage

Many of the higher level classes in the ecl utilise function objects,
e.g. [ecl_threads](https://index.ros.org/p/ecl_threads),
[ecl_sigslots](https://index.ros.org/p/ecl_sigslots). These classes
expect certain concepts to be fulfilled when accepting function objects
as arguments and also make use of some of the convenience classes/tools
in the above list.

#### Concepts

Classes that accept function objects generally utilise a template
parameter and require the function object to fulfill the requirements of
a concept. For example, threads require function objects to satisfy the
nullary function concept. The current list of concepts for function
objects include:

- `NullaryFunction`

Documentation for the concepts can be found in the
[ecl_concepts](https://index.ros.org/p/ecl_concepts) package.

#### Creating Your Own Function Objects

When constructing your own function object classes to be used with
higher level ecl components, they must conform to the requirements of
their target concept. For example, a suitable thread class function
object:



```cplusplus
class ThreadFunction {
public:
    typedef void result_type;
    void operator()() {
        // thread worker function
    }
};
ThreadFunction thread_function;
Thread thread(thread_function); // Alternatively Thread thread = Thread(ThreadFunction());
```



#### Wrapping Free/Member Functions

Wrapping functions can be done via construction calls to many of the
classes listed above, however to make it easier, there is the overloaded
`ecl::generateFunctionObject` method.

A good example of its usage is with the ecl Thread class where a nullary
function object is required for construction.



```cplusplus
int f(int i) {}
class A {
    void f() {}
    void g(int i) {}
};
// ...
A a;
Thread thread0(generateFunctionObject(f, 3));         // Bind the first argument to a global function
Thread thread1(generateFunctionObject(&A::f, a));     // Bind an object instance with the nullary function
Thread thread2(generateFunctionObject(&A::g, a, 2));  // Bind object instance, first argument to a unary member function
```



For member functions, in the above code we bound the instance with the
member function. Alternatively, you can leave it free so that the
following two lines of code produce the same result:



```cplusplus
generateFunctionObject(&A::f, a)(); // This case produces and calls a nullary function
generateFunctionObject(&A::f)(a);   // This case produces and calls a unary function
```



#### Case Scenario : Threads

Threads uses the tools here, an example of thread function loading is
shown below.



```cplusplus
A a;                             // Just an ordinary class with nullary member f().
NullaryFunction function_object; // Conforms to the concept above.
Thread thread_f1(f);
Thread thread_f2(&A::f,a);
Thread thread_f3(generateFunctionObject(f));
Thread thread_f4(generateFunctionObject(g,1));
Thread thread_f5(generateFunctionObject(&A::f,a));
Thread thread_f6(generateFunctionObject(&A::g,a,2));
Thread thread_f7(function_object);
Thread thread_f8 = NullaryFunction();
Thread thread_f8(ref(function_object));
```



### Limitations

We only utilise at most one argument to any free/member function. In
practice a limit has to be drawn somewhere and I find you can always
bundle however many arguments you wish into an appropriately defined
structure, so either none or one is always sufficient for all purposes.

## Parameters

- **Description:** Avoiding a profusion of get/set.
- **Keywords:** ecl parameters
- **Tutorial Level:** INTERMEDIATE

### Introduction

Parameter types substitute the basic types for a more convenient
templatised structure when used within a class. Ideally the only way any
member variable should be modified is via member functions of the class
itself. When you start allowing member variables to be extracted and
modified outside a class, you inevitably lose control of the class (and
in practice this happens by lazy/tired programmers more often than not)
and bugs start creeping in.

The usual way to implement this is with get and set methods providing
access. However, this can get somewhat verbose for simple classes:



```cplusplus
class A {
public:
    A() {};

    int getCounter() const { return m_counter; }
    void setCounter (const int& counter) { m_counter = counter; }

private:
    int m_counter;
};
```



This can be simplified with the use of templates and the () operator
resulting in the Parameter class defined here.

### Compiling & Linking

Include the following at the top of any translation unit that requires
compilation of class that uses parameters.



```cplusplus
#include <ecl/utilities.hpp>

using ecl::Parameter;
```



Since it is a template class, no linking is required if you are only
using this class.

### Usage

#### Parameters

The parameter implementation of a class A (compare with the set/get
implementation described earlier) looks like:



```cplusplus
class A {
public:
    A() {};

    Parameter<int> counter;
};
```



Here access to the variable is done very similarly (but without the
verbosity of set/get).



```cplusplus
int main() {
    A a;
    a.counter(1); // <-- Sets the variable
    cout << a.counter(); << endl; // <-- Gets the variable
}
```



Note that even though `Parameter<int>` is defined publicly, the
contents are still privately allocated, but here they are tucked away in
Parameter's internal implementation.

#### Convenience

There are also convenience methods if the above usage is undesirable.



```cplusplus
a.counter = 1;
int a_copy = a.counter;
```



The difference between these and public variables is that these can
never be set outside of the class. The reason - regualar public
variables can be hooked by a pointer/reference and then passed off to
another function where the variable can be modified\...well outside of
the control of the original class. In this case here, the only hooks
that can be made to the variable are const pointers or const references.
Thus, even though the notation is the same, these parameter variables
are protected by their constness.

## Reference Wrappers

- **Description:** When you want to pass a reference, but are only
  permitted to pass a copy.
- **Keywords:** ecl reference wrappers
- **Tutorial Level:** INTERMEDIATE

### Introduction

There are situations where you may wish to overload a function with both
non-referenced and referenced arguments. Unfortunately, this is not
directly possible with c++, it usually results in an ambiguity.



```cplusplus
class A {
public:
    template <typename T>
    void f(T i) { cout << "Not a reference input" << endl; }

    template <typename T>
    void f(T &i) { cout << "A reference input" << endl; }
}
```



One way to resolve this is to create a wrapper with a pointer to the
object inside it (we call this a reference wrapper) and pass it to the
function as you would normally pass a copy. Once accepted, the function
can use some metaprogramming logic to determine the fate of the accepted
copy or reference wrapper.

### Compiling & Linking

Include the following at the top of any translation unit:



```cplusplus
#include <ecl/utilities.hpp>

using ecl::ReferenceWrapper
using ecl::ref
using ecl::cref
using ecl::addressOf
```



If outside ros, you will also need to link to *ecl_utilities*.

### Usage

#### ReferenceWrapper

The easiest way to generate a reference wrapper is via the convenience
functions ref/cref. For example, below illustrates a referenced function
object passed to a thread.



```cplusplus
Thread thread(ref(function_object));
```



The cref call creates a constant reference, useful when your api will
only accept a constant.

Accessing a reference wrapper is straight forward:



```cplusplus
A a;
ReferenceWrapper<A> wrapper = ref(a);

A &a_ref = wrapper.reference();
A *a_ptr = wrapper.pointer();
```



It can also be directly passed off as the type it wraps.

#### Traits

Testing for reference wrapper objects can be done via the
is_reference_wrapper trait.



```cplusplus
bool result = is_reference_wrapper<int>::value
```



This is most useful when used as a template argument metafunction.

## Singleton

- **Description:** The classic singleton design pattern.
- **Keywords:** ecl singleton
- **Tutorial Level:** INTERMEDIATE

### Overview

Singletons are a means of ensuring a single, unique copy of an object
can ever exist. There are various ways of implementing singletons, the
[wikipedia](http://en.wikipedia.org/wiki/Singleton_pattern) has a
surprisingly good article on singletons and provides a snippet that
utilises the curiously recurring template pattern which is used as the
derivation for this form of the singleton.

### Compiling & Linking

Include the following at the top of any translation unit that:



```cplusplus
#include <ecl/utilities.hpp>

using ecl::Singleton;
```



### Usage

#### Inheriting

This singleton is intended to be inherited by a deriving class - this
saves the work of actually reinventing the singleton mechanisms whenever
you wish to use a singleton.



```cplusplus
class TestObject : public ecl::Singleton<TestObject>
{
friend class ecl::Singleton<TestObject>;

public:
    int value() { return data; }

protected:
    TestObject() : data(32) {}

private:
    int data;
};
```



#### Calling

If you use a macro as shown below, the instance can be conveniently and
readably accessed,



```cplusplus
#define Test TestObject::instance()

...

cout << Test.value() << endl;
```

## Tutorials

- [Function Objects](#function-objects):
  Passing functions around as typed class objects.
- [Parameters](#parameters):
  Avoiding a profusion of get/set.
- [Reference Wrappers](#reference-wrappers):
  When you want to pass a reference, but are only permitted to pass a
  copy.
- [Singleton](#singleton): The
  classic singleton design pattern.
