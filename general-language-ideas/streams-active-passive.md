For generators/iterators/streams/channels, characteristics are:

* async/sync
* buffered/unbuffered
* directional/bidirectional
* active/passive (push/pull)

Is this a combinatorial explosion, or do the concepts themselves subdivide
nicely?

In a hypothetical managed language, what is the minimal set of primitives to
provide maximal flexibility for hooking up sources and sinks?

Go simply has channels:
* async
* unbuffered
* bidirectional by default; syntax supports directional
* fully passive

Active: a generator/channel that "pushes" or "pulls" in a loop, *driving*
execution

Could be asymmetric: "active" pulling from a source into a buffer, but no
pushing

read from file: passive
write to file or stdin: passive
stdin: active, unless buffered?
keyboard/peripheral events: active
