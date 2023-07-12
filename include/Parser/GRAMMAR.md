[//]: # (TODO update)

**Program**

program -> translation_unit_decl

translation_unit_decl -> decl...

**Declaration**

decl -> func_decl (, translation_unit_decl (using only in compiler infrastructure, not in real programs!))

func_decl -> ('extern') 'func' id '(' (id ':' id)... ')' '{' stmt... '}'

**Statement**

stmt -> var_decl_stmt, assignment_stmt, expr_stmt

var_decl_stmt -> 'var' id (':' id) '=' rvalue_expr 
               | 'var' id ':' id

assignment_stmt -> lvalue_expr '=' rvalue_expr 

expr_stmt -> expr

**Expression**

expr -> paren_expr (only in grammar), const_expr, unary_expr, binary_expr, array_expr, var_using_expr, func_call_expr

paren_expr -> '(' expr ')'

lvalue_expr -> var_using_expr

rvalue_expr -> const_expr, unary_expr, binary_expr, array_expr, var_using_expr, func_call_expr

const_expr -> num, str

unary_expr -> unary_op expr

unary_op -> '-'

binary_expr -> expr binary_op expr

binary_op -> '+', '-', '*', '/'

array_expr -> '[' expr (, expr)... ']'

var_using_expr -> id

func_call_expr -> id '(' (expr...) ')'

expr -> unary_expr binary_expr_rhs, array_expr

unary_expr -> (unary_op) primary_expr

binary_expr_rhs -> binary_op unary_expr

primary_expr -> const_expr, var_using_expr, func_call_expr, paren_expr
