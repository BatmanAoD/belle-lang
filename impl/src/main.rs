use pest::Parser;
use pest_derive::Parser;

#[derive(Parser)]
#[grammar = "grammar.pest"]
struct BelleParser;

fn main() {
    let successful_parse = BelleParser::parse(Rule::Program, "# IntVector {}\n");
    println!("{:?}", successful_parse);
}
