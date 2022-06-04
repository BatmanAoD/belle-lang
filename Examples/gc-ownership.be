fn max(&mut g: [Numeric] + Index) -> Numeric {
}

[T] - indexable
{T} - generically iterable...?
K->V - map- or function-like (input K, get V)
() - tuple-like

any - dynamic type
T? - nullable

Default: impl can decide whether values are copied or not, but values aren't mutable

mut -> like &mut
auto -> like RC or ARC<Mutex ...> (impl must detect whether it escapes the current thread)

fn add7(g: Numeric) -> Numeric {
}

fn add7(mut g: Numeric) 
