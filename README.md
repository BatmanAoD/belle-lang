# The Belle programming language

If I ever create a language, I will call it "Belle".

I had originally thought I would try to create a low-level language with capabilities
similar to those of C++, but adhering to a more semantically meaningful design philosophy.
However, I believe that Rust satisfies this niche quite well, and that the next
area of language design that needs to be improved is in higher-level languages.

## Design goals

### Known goals

Currently... none. This repo is primarily for writing down any language design ideas
that I have.

### Possible goals

 * support the low-level control of memory management and stack/heap allocation
 * "don't pay for what you don't use" (a la Rust, C++)
 * Easier to read
 * Less typing
 * Better "default" behavior, generated code, etc
 * True "message-passing"
 * First-class support for managing synchronous or asynchronous control-flow
 * Re-evaluation of what "object oriented" means and what aspects are useful
 * Support for some functional-programming paradigms
 * Interactivity: not yet well-defined (see [The Legacy of
   GOAL](http://art-of-optimization.blogspot.com/2014/06/the-legacy-of-goal.html))
   * Quick compile times (at least for debug builds)
   * Built-in marshalling of *executable* code? This would be difficult or impossible
     in a multi-architecture system without JIT, which is probably contrary to low-level
     control goal
   * "Interactive" way to take a slow/dynamic program and incrementally monomorphize/optimize it?
 * Guarantees about functionality of debug vs release builds (may inhibit optimizations,
   but that might be a good thing)
   * Perhaps there would be an "intermediate" optimization level between debug and release
     that would perform all potentially functionality-changing optimizations (e.g.
     in C/C++, removing `#ifdef _DEBUG/NDEBUG` code and removing code paths with undefined
     behavior). Then the fully-optimized code should logically behave exactly the same
     way the intermediate build behaves.
 * Review [Jonathan Blow's presentation about his desires for a new programming language
   ](https://www.youtube.com/watch?v=TH9VCN6UkyQ)

## The name

My daughter's name is Annabelle, so the language is named after her. There are a number of secondary considerations:

 * I wanted a one-syllable easy-to-remember name
 * I wanted a name that was not already associated with a popular technology, especially another
   programming language.
 * I like the semantic association of "beauty," since I would like to create a "beautiful" language
   (in some intuitive sense--Ruby and Python are "beautiful" to me, while C++ and Perl are not).
 * I like the phonetic association with Bell Labs.
 * From *Go To* by Steve Lohr:
 
       > Belle was the first computer to attain the level of a chess master
