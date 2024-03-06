### Development Plan

1. Write a Jack Tokenizer
2. Write a basic compilation engine that handles all the features,
   except for expressions, and array-oriented statements.
3. Extend the compilation engine to handle expressions.
4. Extend the compilation engine to handle array-oriented statements.

### Token Types

Keyword:

- `class`
- `constructor`
- `function`
- `method`
- `field`
- `static`
- `var`
- `int`
- `char`
- `boolean`
- `void`
- `true`
- `false`
  ...

Symbol:

- `{` or `}`
- `(` or `)`
  etc...

Identifier:

- String of letters, digits, and underscores that does not start with a digit.

Integer Constant:

- A sequence of digits from 0 to 9.

String Constant:

- A sequence of characters not including double quote or newline.

## Compiler Logic

Stage 1: Symbol Table

- Add to each identifier: name, type, kind, and running index.
- The symbol table is basically a list of hash tables, one for each scope.
  - Each reflects a single scope nested within the next one in the list
  - Compilers look for symbol in the first table in the list, if it fails, it moves to the next table and looks for it (inner scopes outward)
- We have different types:
  - static: class level
  - field: class level
  - local: subroutine level
  - argument: subroutine level
- A list of hash tables, each representing a single scope, nested within the next one on the list.
- We need to define if the identifier is being defined (var declaration) or used.

### Repos

https://github.com/timiscoding/JackCompiler/blob/master/SymbolTable.js
