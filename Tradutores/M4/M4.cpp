// constantes para os tipos de token
const int IF=1
const int EXPR=2
const int THEN=3
const int REPEAT=4
const int LISTA=5
const int UNTIL=6
const int WHILE=7
const int DO=8
const int ID=8
const int EQUAL=8

//variável global que armazena o token lido
int tok;

//Obtém o próximo token do analisador léxico
void advance() {
    tok = getToken();
}

//Consome o token passado como parâmetro e avança para o próximo //token da entrada
void consume(int t) {
    if (tok == t)
        advance();
    else
        error();
}

void Comando() {
    switch (tok) {
        case IF:
            Condicional();
            break;
        case REPEAT:
        case WHILE:
            Iterativo();
            break;
        case ID:
            Atribuicao();
            break;
        default:
            error();
    }
}

void Condicional() {
    consume(IF);
    consume(EXPR);
    consume(THEN);
    Comando();
}

void Iterativo() {
    switch (tok) {
        case REPEAT:
            consume(REPEAT);
            consume(LISTA);
            consume(UNTIL);
            consume(EXPR);
            break;
        case WHILE:
            consume(WHILE);
            consume(EXPR);
            consume(DO);
            Comando();
        default:
            error();
    }
}

void Atribuicao() {
    consume(ID);
    consume(EQUAL);
    consume(EXPR);
}