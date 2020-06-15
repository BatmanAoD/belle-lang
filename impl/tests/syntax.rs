pub use pest::Parser;

use belle::*;   // XXX TEMP

fn parse_str(prog: &str) {
    let result = BelleParser::parse(Rule::Program, prog);
    println!("{:#?}", result);
}

#[test]
fn basic() {
    parse_str(include_str!("./basic.bel"))
}
