use belle::{BelleParser, Parser, Rule};

fn main() {
    let parse_result = BelleParser::parse(
        Rule::Program,
        "# IntVector {}\n",
    );
    println!("{:#?}", parse_result);
}
