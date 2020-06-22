## "message-passing": async & non-local

Types could accept "requests"; a "request" is a function where:

* the parameter and output types are serializable
* the output is async: it is a "future" that will be populated when the type
  responds
* the receiver object:
  * is owned by the runtime (i.e. GC'd or static)
  * runs in its own green-thread
  * cannot be accessed directly (only through a "handle" - see below)

This would enable first-class language support for a message passing system. A
"handle" wrapper-type would expose a type's "requests" API, but none of the
other methods implemented by the type. "Same thread" handles would simply
invoke the request methods as normal method calls; in a multi-threaded or
distributed context, handles could use other mechanisms, such as channels or
TCP.

Since handles would have identical APIs regardless of how they send and receive
requests, this would facilitate dramatic refactorings, such as moving an object
from one node to another in a distributed system.

Additionally, request APIs could easily be versioned and published, ensuring
modularity.

Types can implement a "receiver" API *and* a "normal" synchronous-method-call
API. If a type is used as a "normal" object, the "requests" can be invoked as
synchronous methods. (When used in this way, a "handle" to the object cannot be
created, unless it "consumes" the object, transferring ownership to the
runtime.)

## Auto-generated multi-purpose API files (headers)

"API files" would be like C++ header files, but auto-generated from source code.

They would contain the following information:

 * C++ header information, i.e., everything needed to compile classes that `import`
   the class being compiled
   * type definitions
   * total size, including padding, of the object (but *not* names and explicit
     types of private data members)
   * Public function signatures
   * ...etc
 * Documentation-comments (copied from source file)
 * Pre- and post- conditions (**these should be a first-class language feature**,
   and post-conditions should facilitate autogeneration of tests (?)). Post-conditions
   would **include** separate cases for error-handling (a la Rust's `Result` type).

This would be the first step in compilation; after all API files have been generated,
piecewise compilation of the system would be trivial. It would also make partial builds
quicker: since API files are auto-generated, they could include a hash at the top
generated from the build-relevant aspects of the file (i.e., comments are not
used in the hash generation); downstream build targets would only be rebuilt if
this hash changes.

This would allow auto-detection and propagation of `mut` (or `const`), `constexpr`,
etc. It would also allow developers to have a simple and *reliable* API to look at,
which would be parsable (by autocompletion tools, etc) as well.

Note that circular `import`s (if that's allowed) would make generation of these APIs
fairly complicated; there would, for instance, need to be `mut` "placeholders" until
all source files have been examined.

## Polymorphic types

"Variadic" types--like unions, but must include a way to know which member(s) are active
 * Replaces casting! All "casts" are done via implicit function-parameter
   conversion, or by calling a "transform" method on the polymorphic type.
    * In general, polymorphic types are *not required* to support "transformation"
 * Replaces inheritance!
    * Instead of inheriting, write an "umbrella" polymorphic type
 * "Tag" is REQUIRED, but it may be any of the following:
    * Compile-time condition (a la `constexpr` function)
    * Run-time enum
    * Run-time function
 * Tags may be shared among multiple polymorphic types *nested* within an "umbrella" type
 * Built-in "universal" type a la `void*` (used, for instance, as return value
   for `Heap.Allocate`)
 * Types with run-time specification must have a finite number of distinct
   specifications (right?) and a *fixed size* (just like C/C++ unions)
 * (Potentially) useful for marshalling (define marshalled/unmarshalled version
   of data members)
    * If this is indeed useful, provide std::unmarshaller?

Method qualifiers are primarily useful for polymorphic types; for
"requests"/methods/functions not involving polymorphic types, or only
polymorphic types with compile-time specification, the compiler should be able
to determine all qualifiers (e.g. C++'s `const`). (Runtime-)polymorphic types,
however, represent an *interface*, and therefore it makes sense to add
qualifiers.

## Anonymous types

Useful with RAII; replaces "defer"

Akin to `with`

Are JS's objects essentially anonymous classes?

## "Mixins"

A la Ruby--separates the idea of *added functionality via inheritance* from the
"polymorphism" features of inheritance

Can include data members (as in traditional C++)

"Forwarding" is *explicit*

## "Sections"

Class definitions should have "sections" a la Markdown, possibly even using
`#`, `##`, etc. So far, this is somewhat similar to C++'s access-modifier sections but
with a different syntax. There are two possible ways to develop 'sections'.

### Arbitrary attributes

* Nesting (i.e. subsections) is permissible
* Attributes (e.g. access-spec, static/virtual, .... ? ):
  * The attributes bestowed by each section are *separate* from the section's
    *name* and can be *arbitrary* so long as they do not conflict with the
    attributes bestowed by supersections.
  * Members of classes 'inherit' all attributes listed by all containing
    sections; all other attributes must be specified manually (or have defaults).

### Member-type attributes

This is the idea used in the current `IntVector.class` example: `#` indicates a
class, while `##` indicates a section. Member-variables are in the `##data`
section, public methods are in the `##requests` section, the constructor is in
its own `##init` section, and private methods are in the `##aux` section.

## Enums

Support something like C++ scoped enums, but:

 * Somehow permit overlapping *subsets* (e.g. think of error codes--some apply
   to multiple situations, but not all)
 * Special "alias" subsets--otherwise multiple values w/ same name not permitted
 * If-needed support for *iterating* over enums or over subsets of enums
    * Implementation: at compile time, if iteration is requested, generate a
      zipped pair of arrays (or similar) representing where "jumps" happen and
      how far to jump (either an index or a step-size)

## "Unique" values

"Move" semantics, but only on non-shared values; object itself may be owned by
the runtime or be a value (stack) type

Unique values can turn into shared values, but not vice-versa

Some methods may require a unique value!

Relationship to mutability? (Rust: `mut` really means "uniquely referenced",
but I think this is separate from the value itself being "unique")

`drop`/`destructor`/`finalizer`: types with destructors can _only_ exist as
"unique" values. I.e., these values cannot be turned into shared values.

## Misc

Concurrency dealing w/ shared mutable data: "tags" for indicating that
mutations have occurred, use these "tags" to indicate when operations may be
scheduled (i.e. to indicate dependencies between mutations)

Error handling in finalizers/destructors: is this possible?  Require
destructors to be infallible? Provide special syntax for what to do when a
destructor error occurs within some scope? Implicitly capture destructor errors
and require a caller at some level on the stack to handle them?

When a method returns a reference to an internal value, `mut`ness should be
preserved based on the receiver. I.e., the language itself should somehow
obviate the need for things like `index[]` and `index_mut[]` being implemented
separately. This means that there needs to be a way to denote a
"possibly-`mut`" receiver and "forward" the mutability through the method and
onto the return type.
 * Option 1, less general: keyword meaning "`mut` IFF receiver is `mut`"
 * Option 2, more general: way of "naming" the CV-qualifications (to use a C++
   term) of input paramters

Compile-time evaluation (C++ `constexpr`) should be syntactically/semantically
linked with the concept of `static` data; the idea is that *the result of a
compile-time evaluation is always **data** that is embedded in the binary*. The
`static` keyword will always be associated with *data* that is *generated* (or
available as a literal) *at compile time*. (If static data is not used in the
runtime, it will not be embedded. Static data that can be easily shown with
static analysis to have no possible use regardless of feature-switches, etc.
will trigger an error.)

Assertions will be analyzed to determine whether they can simply be evaluated
at compile or link time and, if so, will trigger compile or link errors.

Explicit parameter names at *call* site (like Python but mandatory), overload
on *param names* rather than types

Generalize Ruby's blocks with Currying: callable parameters are syntactically
separate from groups of data-only parameters. E.g. a function signature could
be:

    fn my_fun(arg1: int, arg2: string){callable_arg1}(arg3: double){callable_arg2}

For short-lived valuable non-memory resources, I prefer Python's `with **** as
var:` and Ruby's `acquire(x) do |var|` to RAII, i.e., explicit rather than
implicit scopes *for* each resource. **But** I want to look into D's
`scope(end)`, which sounds very interesting. Also, I'm not sure how this can be
generalized to longer-lived resources, whereas RAII is *very*
extensible/scalable/generalizable.

Way of passing method names, a la Ruby symbols? (Compile-time only)

Way to support marshalling/unmarshalling of *classes* (not just objects)? This
would make software updates possible without recompiling *or* relinking, but
might cause huge overhead. Additionally, the "text" segment in ELF files is
apparently read-only, so the process would have to...restart itself, or
something? Would this even be worthwhile?

For (basic) signed integers, `0xFFFF...` should *always* be an invalid value.
It's tempting to say that this should also hold for signed integers.
This should also be the default initialization value.
