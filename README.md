The Belle programming language
------------------------------

This language is intended as a low-level language with capabilities similar to
those of C++, but adhering to a more semantically meaningful design philosophy.

The plan is to create it in two stages, much as C++ itself was designed in
stages:

 * First, it will be merely a code-generator for C++;
 * Eventually, it may have its own native compiler(s).

Design goals:

 * support the low-level control of memory management and stack/heap allocation
 * Easier to read
 * Less typing
 * Better "default" behavior, generated code, etc
 * True "message-passing"
 * First-class support for managing synchronous or asynchronous control-flow

The name
--------

My daughter's name is Annabelle, so the language is named after her. There are a number of secondary considerations:

 * I wanted a one-syllable easy-to-remember name
 * I wanted a name that was not already associated with a popular technology, especially another
   programming language.
 * I like the semantic association of "beauty," since I would like to create a "beautiful" language
   (in some intuitive sense--Ruby and Python are "beautiful" to me, while C++ and Perl are not).
 * I like the phonetic association with Bell Labs.
 * From *Go To* by Steve Lohr:
 
       > Belle was the first computer to attain the level of a chess master
