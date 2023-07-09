Generic possibly-async stream/iterator: `gen<...>`

Generalized `partition` over enums: take a sequence of enums, *destructure
each*, and return a tuple of streams/gens over *variants*

Note: the only way not to *consume* the input sequence is to produce a set of
*async* generators, because the iteration among all variants must be
synchronized.

Possible syntax:


```
fn partition<T: Enum>(gen<T>) -> (gen<T::*>...)
```

With TypeScript sum-type syntax:

```
fn partition<T|...>(gen<T|...>) -> (gen<T>,...)
```
...that's not terrible.

Or, instead of a return value of new iterators, what about recipient channels?
Using Go-ish syntax:

```
fn partition(src <-chan T) chan<- T::A, sinkB chan<- T::B)
```

...it's a bit awkward, and doesn't seem better than returning new channels.

As a syntactic built-in with pattern matching:

```
// given `s` of type `gen<W|X|Y|Z>`:
s-> split {
  W-> ...
  X-> ...
  Y-> ...
  Z-> ...
}
```

Or:

```
// given `s` of type `gen<W|X|Y|Z>`:

s.each match {
  X (x):
    x...each // handle this stream inline (not sure about this syntax)
    gen(x).each // ... how about this?
    let gx = gen(x) // consistent w/ this
    // ^ `gen()` is a bit weird here b/c it's not actually making a new
    // generator for each `x`.
    // ...you could require forward-declaring these, but...why?
    // If `gx` were forward-declared, you could have go channel syntax:
    gx <- x; gx.each...
    // ...that doesn't seem better.
  Y (y):
    yield y // works if the function returns `gen<Y>`
  W|Z (u):
    u...each // handle a stream `gen<W|Z>`
    yield u  // works if function returns `gen<(W|Z)>`
}
```
