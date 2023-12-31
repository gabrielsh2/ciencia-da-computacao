%class Lexer
%unicode

%%

[0-9]+         { return new Token(Token.INT, yytext()); }
[a-zA-Z][a-zA-Z0-9]* { return new Token(Token.IDENTIFIER, yytext()); }
.              { /* Ignorar caracteres desconhecidos */ }

%%

public static void main(String[] args) throws Exception {
    Lexer lexer = new Lexer(System.in);
    Token token;
    
    while ((token = lexer.yylex()) != null) {
        System.out.println("Tipo: " + token.getType() + ", Valor: " + token.getValue());
    }
}