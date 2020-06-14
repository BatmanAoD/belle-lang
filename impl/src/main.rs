use pest::Parser;
use pest_derive::Parser;

#[derive(Parser)]
#[grammar = "grammar.pest"]
struct BelleParser;

fn main() {
    let parse_result = BelleParser::parse(
        Rule::Program,
        "# IntVector {}\n",
    );
    println!("{:#?}", parse_result);
}
