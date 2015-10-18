Auto-generated multi-purpose API files (headers)
------------------------------------------------

"API files" would be like C++ header files, but auto-generated fro source code.

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
piecewise compilation of the system would be trivial.

This would allow auto-detection and propagation of `mut` (or `const`), `constexpr`,
etc. It would also allow developers to have a simple and *reliable* API to look at,
which would be parsable (by autocompletion tools, etc) as well.

Note that circular `import`s (if that's allowed) would make generation of these APIs
fairly complicated; there would, for instance, need to be `mut` "placeholders" until
all source files have been examined.

Polymorphic types
-----------------

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

"Mixins"
--------

A la Ruby--separates the idea of *added functionality via inheritance* from the
"polymorphism" features of inheritance

Can include data members (as in traditional C++)

"Forwarding" is *explicit*

Misc
----

Explicit parameter names at *call* site (like Python but mandatory), overload on *param names* rather than types

Way of passing method names, a la Ruby symbols? (Compile-time only)

“message-oriented”--consider how to make this “truly” OO a la Alan Kays

Way to support marshalling/unmarshalling of *classes* (not just objects)? This
would make software updates possible without recompiling *or* relinking, but
might cause huge overhead. Additionally, the "text" segment in ELF files is
apparently read-only, so the process would have to...restart itself, or
something? Would this even be worthwhile?
