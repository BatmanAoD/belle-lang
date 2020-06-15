use std::fs::read_to_string;

pub use pest::Parser;

use belle::*;   // XXX TEMP

fn parse_str(prog: &str) {
    let result = BelleParser::parse(Rule::Program, prog);
    println!("{:#?}", result);
}

fn parse_file(path: &str) {
    parse_str(&read_to_string(path).unwrap());
}

#[test]
fn basic() {
    parse_file("./basic.bel")
}
