## ESTree [Back](../JavaScript.md)

REF: https://github.com/estree/estree/blob/master/es5.md

This document specifies the core ESTree AST node types that support the ES5 grammar.

### Node objects

ESTree AST nodes are represented as `Node` objects, which may have any prototype inheritance but which implement the following interface:

```ts
interface Node {
    type: string;
    loc: SourceLocation | null;
}
```

The `type` field is a string representing the AST variant type. Each subtype of `Node` is documented below with the specific string of its `type` field. You can use this field to determine which interface a node implements.

The `loc` field represents the source location information of the node. If the node contains no information about the source location, the field is `null`; otherwise it is an object consisting of a start position (the position of the first character of the parsed source region) and an end position (the position of the first character after the parsed source region):

```ts
interface SourceLocation {
    source: string | null;
    start: Position;
    end: Position;
}
```

Each `Position` object consists of a `line` number (1-indexed) and a `column` number (0-indexed):

```ts
interface Position {
    line: number; // >= 1
    column: number; // >= 0
}
```

### Identifier

```ts
interface Identifier <: Expression, Pattern {
    type: "Identifier";
    name: string;
}
```

An identifier. Note that an identifier may be an expression or a destructuring pattern.

### Literal

```ts
interface Literal <: Expression {
    type: "Literal";
    value: string | boolean | null | number | RegExp;
}
```

A literal token. Note that a literal can be an expression.

#### RegExpLiteral

```ts
interface RegExpLiteral <: Literal {
  regex: {
    pattern: string;
    flags: string;
  };
}
```

The `regex` property allows regexes to be represented in environments that don’t
support certain flags such as `y` or `u`. In environments that don't support
these flags `value` will be `null` as the regex can't be represented natively.

### Programs

```ts
interface Program <: Node {
    type: "Program";
    body: [ Directive | Statement ];
}
```

A complete program source tree.

### Functions

```ts
interface Function <: Node {
    id: Identifier | null;
    params: [ Pattern ];
    body: FunctionBody;
}
```

A function [declaration](#functiondeclaration) or [expression](#functionexpression).

### Statements

```ts
interface Statement <: Node { }
```

Any statement.

#### ExpressionStatement

```ts
interface ExpressionStatement <: Statement {
    type: "ExpressionStatement";
    expression: Expression;
}
```

An expression statement, i.e., a statement consisting of a single expression.

#### Directive

```ts
interface Directive <: Node {
    type: "ExpressionStatement";
    expression: Literal;
    directive: string;
}
```

A directive from the directive prologue of a script or function.
The `directive` property is the raw string source of the directive without quotes.

#### BlockStatement

```ts
interface BlockStatement <: Statement {
    type: "BlockStatement";
    body: [ Statement ];
}
```

A block statement, i.e., a sequence of statements surrounded by braces.

#### FunctionBody

```ts
interface FunctionBody <: BlockStatement {
    body: [ Directive | Statement ];
}
```

The body of a function, which is a block statement that may begin with directives.

#### EmptyStatement

```ts
interface EmptyStatement <: Statement {
    type: "EmptyStatement";
}
```

An empty statement, i.e., a solitary semicolon.

#### DebuggerStatement

```ts
interface DebuggerStatement <: Statement {
    type: "DebuggerStatement";
}
```

A `debugger` statement.

#### WithStatement

```ts
interface WithStatement <: Statement {
    type: "WithStatement";
    object: Expression;
    body: Statement;
}
```

A `with` statement.

#### Control flow

##### ReturnStatement

```ts
interface ReturnStatement <: Statement {
    type: "ReturnStatement";
    argument: Expression | null;
}
```

A `return` statement.

##### LabeledStatement

```ts
interface LabeledStatement <: Statement {
    type: "LabeledStatement";
    label: Identifier;
    body: Statement;
}
```

A labeled statement, i.e., a statement prefixed by a `break`/`continue` label.

##### BreakStatement

```ts
interface BreakStatement <: Statement {
    type: "BreakStatement";
    label: Identifier | null;
}
```

A `break` statement.

##### ContinueStatement

```ts
interface ContinueStatement <: Statement {
    type: "ContinueStatement";
    label: Identifier | null;
}
```

A `continue` statement.

#### Choice

##### IfStatement

```ts
interface IfStatement <: Statement {
    type: "IfStatement";
    test: Expression;
    consequent: Statement;
    alternate: Statement | null;
}
```

An `if` statement.

##### SwitchStatement

```ts
interface SwitchStatement <: Statement {
    type: "SwitchStatement";
    discriminant: Expression;
    cases: [ SwitchCase ];
}
```

A `switch` statement.

###### SwitchCase

```ts
interface SwitchCase <: Node {
    type: "SwitchCase";
    test: Expression | null;
    consequent: [ Statement ];
}
```

A `case` (if `test` is an `Expression`) or `default` (if `test === null`) clause in the body of a `switch` statement.

#### Exceptions

##### ThrowStatement

```ts
interface ThrowStatement <: Statement {
    type: "ThrowStatement";
    argument: Expression;
}
```

A `throw` statement.

##### TryStatement

```ts
interface TryStatement <: Statement {
    type: "TryStatement";
    block: BlockStatement;
    handler: CatchClause | null;
    finalizer: BlockStatement | null;
}
```

A `try` statement. If `handler` is `null` then `finalizer` must be a `BlockStatement`.

###### CatchClause

```ts
interface CatchClause <: Node {
    type: "CatchClause";
    param: Pattern;
    body: BlockStatement;
}
```

A `catch` clause following a `try` block.

#### Loops

##### WhileStatement

```ts
interface WhileStatement <: Statement {
    type: "WhileStatement";
    test: Expression;
    body: Statement;
}
```

A `while` statement.

##### DoWhileStatement

```ts
interface DoWhileStatement <: Statement {
    type: "DoWhileStatement";
    body: Statement;
    test: Expression;
}
```

A `do`/`while` statement.

##### ForStatement

```ts
interface ForStatement <: Statement {
    type: "ForStatement";
    init: VariableDeclaration | Expression | null;
    test: Expression | null;
    update: Expression | null;
    body: Statement;
}
```

A `for` statement.

##### ForInStatement

```ts
interface ForInStatement <: Statement {
    type: "ForInStatement";
    left: VariableDeclaration |  Pattern;
    right: Expression;
    body: Statement;
}
```

A `for`/`in` statement.

### Declarations

```ts
interface Declaration <: Statement { }
```

Any declaration node. Note that declarations are considered statements; this is because declarations can appear in any statement context.

#### FunctionDeclaration

```ts
interface FunctionDeclaration <: Function, Declaration {
    type: "FunctionDeclaration";
    id: Identifier;
}
```

A function declaration. Note that unlike in the parent interface `Function`, the `id` cannot be `null`.

#### VariableDeclaration

```ts
interface VariableDeclaration <: Declaration {
    type: "VariableDeclaration";
    declarations: [ VariableDeclarator ];
    kind: "var";
}
```

A variable declaration.

##### VariableDeclarator

```ts
interface VariableDeclarator <: Node {
    type: "VariableDeclarator";
    id: Pattern;
    init: Expression | null;
}
```

A variable declarator.

### Expressions

```ts
interface Expression <: Node { }
```

Any expression node. Since the left-hand side of an assignment may be any expression in general, an expression can also be a pattern.

#### ThisExpression

```ts
interface ThisExpression <: Expression {
    type: "ThisExpression";
}
```

A `this` expression.

#### ArrayExpression

```ts
interface ArrayExpression <: Expression {
    type: "ArrayExpression";
    elements: [ Expression | null ];
}
```

An array expression. An element might be `null` if it represents a hole in a sparse array. E.g. `[1,,2]`.

#### ObjectExpression

```ts
interface ObjectExpression <: Expression {
    type: "ObjectExpression";
    properties: [ Property ];
}
```

An object expression.

##### Property

```ts
interface Property <: Node {
    type: "Property";
    key: Literal | Identifier;
    value: Expression;
    kind: "init" | "get" | "set";
}
```

A literal property in an object expression can have either a string or number as its `value`. Ordinary property initializers have a `kind` value `"init"`; getters and setters have the kind values `"get"` and `"set"`, respectively.

#### FunctionExpression

```ts
interface FunctionExpression <: Function, Expression {
    type: "FunctionExpression";
}
```

A `function` expression.

#### Unary operations

##### UnaryExpression

```ts
interface UnaryExpression <: Expression {
    type: "UnaryExpression";
    operator: UnaryOperator;
    prefix: boolean;
    argument: Expression;
}
```

A unary operator expression.

###### UnaryOperator

```ts
enum UnaryOperator {
    "-" | "+" | "!" | "~" | "typeof" | "void" | "delete"
}
```

A unary operator token.

##### UpdateExpression

```ts
interface UpdateExpression <: Expression {
    type: "UpdateExpression";
    operator: UpdateOperator;
    argument: Expression;
    prefix: boolean;
}
```

An update (increment or decrement) operator expression.

###### UpdateOperator

```ts
enum UpdateOperator {
    "++" | "--"
}
```

An update (increment or decrement) operator token.

#### Binary operations

##### BinaryExpression

```ts
interface BinaryExpression <: Expression {
    type: "BinaryExpression";
    operator: BinaryOperator;
    left: Expression;
    right: Expression;
}
```

A binary operator expression.

###### BinaryOperator

```ts
enum BinaryOperator {
    "==" | "!=" | "===" | "!=="
         | "<" | "<=" | ">" | ">="
         | "<<" | ">>" | ">>>"
         | "+" | "-" | "*" | "/" | "%"
         | "|" | "^" | "&" | "in"
         | "instanceof"
}
```

A binary operator token.

##### AssignmentExpression

```ts
interface AssignmentExpression <: Expression {
    type: "AssignmentExpression";
    operator: AssignmentOperator;
    left: Pattern | Expression;
    right: Expression;
}
```

An assignment operator expression.

###### AssignmentOperator

```ts
enum AssignmentOperator {
    "=" | "+=" | "-=" | "*=" | "/=" | "%="
        | "<<=" | ">>=" | ">>>="
        | "|=" | "^=" | "&="
}
```

An assignment operator token.

##### LogicalExpression

```ts
interface LogicalExpression <: Expression {
    type: "LogicalExpression";
    operator: LogicalOperator;
    left: Expression;
    right: Expression;
}
```

A logical operator expression.

###### LogicalOperator

```ts
enum LogicalOperator {
    "||" | "&&"
}
```

A logical operator token.

##### MemberExpression

```ts
interface MemberExpression <: Expression, Pattern {
    type: "MemberExpression";
    object: Expression;
    property: Expression;
    computed: boolean;
}
```

A member expression. If `computed` is `true`, the node corresponds to a computed (`a[b]`) member expression and `property` is an `Expression`. If `computed` is `false`, the node corresponds to a static (`a.b`) member expression and `property` is an `Identifier`.

#### ConditionalExpression

```ts
interface ConditionalExpression <: Expression {
    type: "ConditionalExpression";
    test: Expression;
    alternate: Expression;
    consequent: Expression;
}
```

A conditional expression, i.e., a ternary `?`/`:` expression.

#### CallExpression

```ts
interface CallExpression <: Expression {
    type: "CallExpression";
    callee: Expression;
    arguments: [ Expression ];
}
```

A function or method call expression.

#### NewExpression

```ts
interface NewExpression <: Expression {
    type: "NewExpression";
    callee: Expression;
    arguments: [ Expression ];
}
```

A `new` expression.

#### SequenceExpression

```ts
interface SequenceExpression <: Expression {
    type: "SequenceExpression";
    expressions: [ Expression ];
}
```

A sequence expression, i.e., a comma-separated sequence of expressions.

### Patterns

Destructuring binding and assignment are not part of ES5, but all binding positions accept `Pattern` to allow for destructuring in ES6. Nevertheless, for ES5, the only `Pattern` subtype is [`Identifier`](#identifier).

```ts
interface Pattern <: Node { }
```
