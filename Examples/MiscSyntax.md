## Pointers and ownership

`*, &, $` for pointer ownership:
-- raw: like C++/C
-- owning: like `unique_ptr` (can release, etc…for C++ multi-proc interface)
-- shared: allocate block w/ vector of owner addresses, notify (??)

## Arrays

[MyClass]#elems  -- local, elems elements
&[MyClass]#elems   -- heap (could use * or $)

[] access, as usual…
..way to get “raw pointer” from array?
...allow ptr arithmetic?
array.method, e.g. for reduce op
(way to specify whether op is commutative/associative for parallelization/optimization)

## Method ("request") naming

! for destructive methods?

## Meta section

`##Meta` section is for static methods and Python-like "metaclass" stuff; e.g. for
redefining Type.New

## Keywords

 * consider "redefines" keyword for overriding things (since overriding has
   inheritance connotations

## Request forwarding

 * EXPLICIT for mixins! Each request name is _forwarded_ to the mixin and
   optionally renamed
 * known "sets" of requests which can be forwarded all together:
   * all from mixin (syntax?)
   * equality (named, somehow...)
   * inequality
   * comparison (both equality and inequality)
   * arithmetic

## Allocation/initialization

Explicit allocation syntax:

    obj_name{(ctor_arg1, arg2...) <-* :AllocFunc}

AllocFunc must return a variadic type that supports `obj_name`; in general,
standard heap allocation will be use, which will return a special variadic type
that must be determined at compile time but supports all types (i.e.
essentially `void*`). (The standard ":Heap.Allocate" might just be turned into
a `new` statement for now.)

`obj_name{(ctor_arg1, arg2...)}` will initialize on the stack.

[elem1, elem2, elem3] is the "literal array/tuple" syntax, a la
`std::initializer_list`. This avoids the "uniform init/std::init-list"
confusion.

## Copying/assignment

`<-deep` for deep copy--or maybe `<-deep|` to prevent dependence on whitespace?

any use for `:=`?

## Preconditions/postconditions

:=> and <=: should represent something like preconditions/postconditions, or
possibly even event signals.
