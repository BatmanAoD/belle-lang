- Parser generators seem like the right approach. Grammar should be defined in a spec file. 
- Spec files should define both tokenization and actual AST rules.
  - PEG does this, but arguably not in a "thoughtful" way.
  - For the purpose of writing a programming language, a token is any expansion that doesn't have anywhere that permits inserting comments or arbitrary whitespace. 
- PEG's/Pest's concept of auto-inserting comments and whitespace outside of tokens makes a lot of sense. 
- "labeled contexts" - not fully context-free, but only as much as necessary to parse things like heredocs 
  - probably not more powerful than Pest's stack? 

Links:

* https://matklad.github.io/2018/06/06/modern-parser-generator.html
* https://github.com/tree-sitter/tree-sitter
* https://www.eyalkalderon.com/nom-error-recovery/
* https://github.com/lalrpop/lalrpop
