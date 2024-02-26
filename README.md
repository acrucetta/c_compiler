
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
-  `(` or `)`
etc...

Identifier:
- String of letters, digits, and underscores that does not start with a digit.

Integer Constant:
- A sequence of digits from 0 to 9.

String Constant:
- A sequence of characters not including double quote or newline.



