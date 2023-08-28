DSLs for different "layers" of the application

Should be largely "modular"/"composable"/"pluggable" in the sense that one
layer does not impose many requirements on another

General open question for layers with "thick" implementations (esp. data-flow
layer): how much control should "power-users" be given to tweak/modify/control
the details in the "implementation details" list?

### Node & Data-flow layer

The "BEAM layer"

Ideally, this is graph-like; see [dataflow_graph.md]

DSL Domain:
* Node requirements & constraints
  * e.g. "pure computation", "scalable," "persistent", "[x] hardware access",
    "collocated"
  * node supervisor relationship & behavior
* Data flow: types from data-definition layer
  * streams vs items
  * events & responses

Implementation details:
* Secure inter-node communication (TLS for networking, etc)
* Deploying, starting, & monitoring nodes
* Scaling "pure" nodes
* _how_ data is sent (e.g. if nodes are collocated, implementation may "send"
  by passing a pointer)

questions:
* what about closures/callbacks/lambdas? Seem useful at this layer
* should this layer also handle business logic? very diagrammatic
* is it helpful to model mutability at this layer, or is it preferable for
  everything to be POD messages?

### Data-definition layer

POD types

Can be an existing format: JSON, YAML, Typical, Protobuf... even `repr(C)`

Just needs stable representation over wire and on-disk

Can have associated functions, _if_ the functions be represented in a "common"
way on all nodes (e.g. if all nodes are using Rust at a "lower" layer,
associated functions should be in Rust; or if nodes can run WASM, associated
functions can be WASM)

...similarly: should have codegen or another "idiomatic" representation for use
in all other layers

### Computation layer

The "Fortran"/"R"/"Julia" layer

Generally more "math-y" where possible, but in the sense of arithmetic, not
functional programming or category theory

Designed for "number crunching" but more generally anything compute-bound

Memory-layout aware: needs to be close to data, and perform transformations in
a performant way; some compute DSLs may present as "pure" functions but be
compiled to mutate/reuse memory, others may give direct mutation control to
users

_no_ explicit persistence or I/O (layer is connected only to the "data-flow"
layer, via "inputs"/"outputs")

Error-handling must be exposed to the data-flow layer as "error" messages. Some
ways this could manifest in the DSL itself are:
* preconditions/postconditions, but main logic must be provably "pure"
* checked exceptions
* `Result` types

Easiest & most flexible is probably a combination of pre/post-conditions, plus
checked exceptions for specific operations that are hardware-trappable, such as
div-by-0. In particular, where possible, prove that illegal operations are
impossible based on pre/post conditions (and consequently, that preconditions
for a function imply that using with certain args is a new "illegal operation"
for the caller); but when that can't be proven, require a checked exception
annotation

#### special cases

GPU shaders, QPU programs, LLM models...

#### Implementation note

Part of the desire here is for the datalayer implementation and computation
layer implementation to be "smart enough" to work together to minimize copies &
permit parallelized access to shared data, _safely_. In particular, the
programmer should be able to specify how a large data structure should be
"split up" for processing, what processing steps must occur, and what nodes or
opertions must occur on them; but should _not_ be given direct access to the
memory itself. The dataflow layer operates on "values" only, not on references,
and the computation layer DSL may be "pure", but the compiler(s) could
recognize that the data does not actually need to be copied or "sent" anywhere
if all computational nodes are on the same hardware, and could freely
distribute pointers as long as it can guarantee that no two nodes have access
to the same "window" of the data.

### ...everything else?

Everything else should probably just be a "node" compatible with the dataflow
layer, written in an existing general-purpose language.

Not covered:
* I/O (graphics, printing, keyboard input, etc)
* APIs (...and interacting with legacy APIs)
* business logic (lots of `if`s) - _maybe_ belong at dataflow level?
* ...?
