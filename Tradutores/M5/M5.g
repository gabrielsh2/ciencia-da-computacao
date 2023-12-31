grammar M5.g;

options {
	language=Java;
}

@header {
    import java.util.HashMap;
}

@members {
    HashMap<String, Double> memory = new HashMap<>();
}

prog
    :
    stat+ EOF
    ;

stat
    :
    comandos
    ; 

comandos
    :
    (comando ';')+
    ;

comando
    : 
    atribuicao
    | iteracao
    | teste 
    ;

iteracao
    :
	WHILE rel DO comandos
    ;

atribuicao
    :
    VAR ':=' expr 
    { memory.put($VAR.text, new Double($expr.v)); } 
    { System.out.println("Variável " + $VAR.text + " = " + $expr.v + " inserida na memória"); }
    ;

teste
    :
	(IF rel THEN comandos) alternativa 
	;
	
alternativa
    :	
	(ELSE comandos)
	|
	;

expr returns [ double v ]
    :
    ( INT { $v = Double.parseDouble($INT.text); } {System.out.println("Lido valor constante: " + $v);}
    | VAR { $v = memory.getOrDefault($VAR.text, 0.0); } {System.out.println("Lido da memória de variáveis: " + $v);} )
    ( '+' {System.out.println("Lido: + ");} e = expr {$v += $e.v;} {System.out.println("Resultado da soma: " + $v);}
    | '-' {System.out.println("Lido: - ");} e = expr {$v -= $e.v;} {System.out.println("Resultado da subtração: " + $v);}
    | '*' {System.out.println("Lido: * ");} e = expr {$v *= $e.v;} {System.out.println("Resultado da multiplicação: " + $v);}
    | '/' {System.out.println("Lido: / ");} e = expr {$v /= $e.v;} {System.out.println("Resultado da divisão: " + $v);}
    |
    )
    | '(' e = expr {$v = $e.v;} ')'
    ;

rel returns [ boolean t ]
    : 
    ( e = expr ) 
    ( '='  {System.out.println("Lido expr rel: = " );} d = expr {$t = $e.v == $d.v;} {System.out.println("Resultado expr rel " + $e.v + " = "  + $d.v + " : " + $t);} 
    | '<>' {System.out.println("Lido expr rel: <> ");} d = expr {$t = $e.v != $d.v;} {System.out.println("Resultado expr rel " + $e.v + " <> " + $d.v + " : " + $t);} 
    | '<'  {System.out.println("Lido expr rel: < " );} d = expr {$t = $e.v <  $d.v;} {System.out.println("Resultado expr rel " + $e.v + " < "  + $d.v + " : " + $t);}
    | '>'  {System.out.println("Lido expr rel: > " );} d = expr {$t = $e.v >  $d.v;} {System.out.println("Resultado expr rel " + $e.v + " > "  + $d.v + " : " + $t);} 
    | '<=' {System.out.println("Lido expr rel: <= ");} d = expr {$t = $e.v <= $d.v;} {System.out.println("Resultado expr rel " + $e.v + " <= " + $d.v + " : " + $t);}
    | '>=' {System.out.println("Lido expr rel: >= ");} d = expr {$t = $e.v >= $d.v;} {System.out.println("Resultado expr rel " + $e.v + " >= " + $d.v + " : " + $t);}
    )   
    ;

DO   : 'do';
ELSE : 'else';
IF   : 'if';
WHILE: 'while';
THEN : 'then';
END  : 'end';

INT  : ('0'..'9')+ ;
VAR  : ('a'..'z')+ ;

WS   : (' '|'\n'|'\r'|'\t')+ {skip();} ;