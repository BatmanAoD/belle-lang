pub use pest::Parser;

use belle::*;   // XXX TEMP

fn parse_str(prog: &str) {
    if let Err(e) = BelleParser::parse(Rule::Program, prog) {
        eprintln!("{}", e);
        assert!(false, "Failed to parse");
    }
}

#[test]
fn basic() {
    parse_str(include_str!("./basic.bel"))
}
