//use std::fs::read_to_string;
//use std::path::Path;

//pub use pest::{Parser, iterators::Pairs};
//use pest::error::Error as PestError;
use pest_derive::Parser;

#[derive(Parser)]
#[grammar = "grammar.pest"]
pub struct BelleParser;

/*
 * XXX `pest` creates objects w/ lifetimes tied to the input data. So how can an "owned" type be
 * created?
type ParseOutput = Pairs<Rule>;
type ParseResult = Result<ParseOutput, PestError<Rule>>;

fn parse_str(prog: &str) -> ParseResult {
    BelleParser::parse(Rule::Program, prog)
}

fn parse_file<P: AsRef<Path>>(file: P) -> ParseResult {
    // XXX error handling
    parse_str(read_to_string(file).unwrap())
}
*/
