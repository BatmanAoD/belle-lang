# Different syntax for different "levels" of design

I want a more "graphical" format to design the high-level
architecture of a system.

It should be based on *data flow*, not type-hierarchies.

This would be different from the syntax for actually writing
functions.

# Notes on the graphical model

* Fully monomorphized types only
  * Possibly POD only, at least for cross-node communication?
* Full textual representation
* "Actor-model" annotations; graphically, perhaps computational nodes (actors
  or even specific nodes in a distributed network) can be depicted as outlines
  around operations, and operations can be dragged from one node to another
* ...some kind of capability to mock actors
* ...some kind of capability to represent interactions outside the network
  (e.g. to external APIs)
