# Grammar of GSLanguage

Program - one file.

## **Program**
    program ::= translation_unit_decl

    translation_unit_decl ::= decls

## **Declarations**

    decls ::= decl decls 
            | empty

    decl ::= module_decl 
           | import_decl 
           | func_decl

    module_decl ::= 'module' id '{' decls '}'

    import_decl ::= 'import' id

    func_decl ::= qualifiers 'func' id '(' params ')' '{' stmts '}'

    qualifiers ::= qualifier qualifiers 
                 | empty

    qualifier ::= 'extern'

    params ::= param 
             | param ',' params 
             | empty

    param ::= id ':' id

[//]: # (TODO: Add compound assignment statement)
[//]: # (TODO: Add else branch in if statement)
[//]: # (TODO: Replace 'range_expr' to 'expr' in for statement)
[//]: # (TODO: Add simplified match arm in match statement)
[//]: # (TODO: Add underscore '_' to valid pattern in match statement)
## **Statements**

    stmts ::= stmt stmts 
            | empty

    stmt ::= var_decl_stmt 
           | assignment_stmt 
           | if_stmt 
           | for_stmt 
           | while_stmt 
           | match_stmt 
           | return_stmt 
           | expr_stmt

    var_decl_stmt ::= 'var' id ':' id '=' rvalue_expr 
                    | 'var' id '=' rvalue_expr
                    | 'var' id ':' id

    assignment_stmt ::= lvalue_expr '=' rvalue_expr

    if_stmt ::= 'if' expr '{' stmts '}'

    for_stmt ::= 'for' id 'in' range_expr '{' stmts '}'

    while_stmt ::= 'while' expr '{' stmts '}'

    match_stmt ::= 'match' expr '{' match_arms '}'

    match_arms ::= match_arm match_arms 
                 | emtpy

    match_arm ::= expr '=>' '{' stmts '}'

    return_stmt ::= 'return' expr

    expr_stmt ::= expr

[//]: # (TODO: Rewrite expression)
## **Expression**

    exprs ::= expr exprs 
            | empty

    expr ::= literal_expr
           | array_expr
           | range_expr
           | unary_expr
           | binary_expr
           | index_expr
           | cast_expr
           | var_using_expr
           | func_call_expr 
           | paren_expr

    lvalue_expr ::= index_expr 
                  | var_using_expr 
                  | paren_expr

    rvalue_expr ::= literal_expr 
                  | array_expr 
                  | range_expr 
                  | unary_expr 
                  | binary_expr 
                  | index_expr 
                  | cast_expr 
                  | var_using_expr 
                  | func_call_expr 
                  | paren_expr

    primary_expr ::= literal_expr 
                   | array_expr 
                   | range_expr 
                   | index_expr 
                   | var_using_expr 
                   | func_call_expr 
                   | paren_expr

    literal_expr ::= symbol 
                   | num 
                   | str

    array_expr ::= '[' array_values ']'

    array_values ::= expr 
                   | expr ',' array_values 
                   | empty

    range_expr ::= expr '..' expr

    unary_expr ::= unary_op primary_expr
    
    unary_op ::= '-' 
               | '!'

    binary_expr ::= cast_expr binary_op cast_expr

    binary_op ::= '+' 
                | '-' 
                | '*' 
                | '/' 
                | '%' 
                | '^' 
                | '&' 
                | '|' 
                | '>' 
                | '<' 
                | '!' 
                | '='
                | '++'
                | '--'
                | '**'
                | '&&'
                | '||'
                | '>>'
                | '<<'
                | '>='
                | '<='
                | '=='
                | '!='
                | '+='
                | '-='
                | '*='
                | '/='
                | '%='
                | '^='
                | '&='
                | '|='

    index_expr ::= expr '[' expr ']'

    cast_expr ::= unary_expr 'as' id

    var_using_expr ::= id

    func_call_expr ::= id '(' args ')'

    args ::= expr
           | expr ',' args 
           | empty

    paren_expr ::= '(' expr ')'

## **Lexical**

    id ::= id_start [id_continue]*

    symbol ::= ''' any_symbol '''

    num ::= '0'..'9' ['0'..'9']*

    str ::= '"' all_symbols '"'