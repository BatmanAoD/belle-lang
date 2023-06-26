# "Context & Capabilities"

Rust blog post: https://tmandry.gitlab.io/blog/posts/2021-12-21-context-capabilities/

This feels to me like a prime example of what "objects" in the Erlang sense of
"object-oriented" are *for*. When initialized, an object must register the
implicit "context" to be used when any invocations are sent to it. This context
should be static throughout the lifetime of the object.

Note that since this is the Actor/Erlang-like "indepednent living cells" model,
the "context" will often be a "directory" of other objects (by "handle", i.e.
address).

# Some implications & extrapolations

* Contexts only provide "capabilities", which are effectively "handles" to
  actors that provide particular functionality.
* Contexts are immutable. To change an actor's context, a new instantiation
  must occur. In general, the interfaces provided via capabilities should also
  be...limited. "Immutable" is probably not necessarily the right term here.
  * ...would it be possible to build an effects system around contexts?
* Some "standard" capabilities (context items) are provided by the runtime/OS:
  `stdout`, `stdin`, various clocks
* Instantiating an actor should always take optional arguments for overriding
  the defaults for context values.
  * These should probably *not* be limited by the set of capabilities actually
    currently used by the actor. If the actor does not use a context-item now,
    it may in the future.
* In general, a new actor should inherit context implicitly from its "parent",
  the actor instantiating it.
  * The top-level context is the `main` method, with any capabilities that are
    inherent to the OS/runtime
* There could be special syntax (probably `with`) for declaring a scoped
  override for context items, to be applied to all actors instantiated within
  that scope.
