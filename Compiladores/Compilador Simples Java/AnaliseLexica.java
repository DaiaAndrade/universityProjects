import java.io.*;

enum TokenType{ NUM, SOMA, SUB, MULT, DIV, APar, FPar, EOF}

class Token{
    char lexema;
    TokenType token;
    int num;

    Token (int l, TokenType t){
        num=l;
        token = t;
    }
    Token (char l, TokenType t){
        lexema=l;
        token = t;
    }
}

class AnaliseLexica {

    BufferedReader arquivo;

    AnaliseLexica(String a) throws Exception {
        this.arquivo = new BufferedReader(new FileReader(a));
    }

    Token getNextToken() throws Exception{
        Token token;
        int eof = -1;
        char currchar;
        int currchar1;
        int n = 0;

        do{
            currchar1 =  arquivo.read();
            currchar = (char) currchar1;
        } while (currchar == '\n' || currchar == ' ' || currchar =='\t' || currchar == '\r');

        if(currchar1 != eof && currchar1 !=10){
            if (currchar >= '0' && currchar <= '9'){
                do {
                    //0=48, 1=19, 2=50, 3=51, 4=52, 5=53, 6=54, 7=55, 8=56, 9=57
                    n = n * 10;
                    n = n + (currchar1 - '0');
                    arquivo.mark(1);
                    currchar1 = arquivo.read();
                    currchar = (char) currchar1;
                } while (currchar >= '0' && currchar <= '9');

                arquivo.reset();
                return (new Token(n, TokenType.NUM));

            }else{
                switch (currchar){
                    case '(':
                        return (new Token (currchar,TokenType.APar));
                    case ')':
                        return (new Token (currchar,TokenType.FPar));
                    case '+':
                        return (new Token (currchar,TokenType.SOMA));
                    case '-':
                        //System.out.println("reconheceu SUB");
                        return (new Token (currchar,TokenType.SUB));
                    case '*':
                        return (new Token (currchar,TokenType.MULT));
                    case '/':
                        //System.out.println("reconheceu DIV");
                        return (new Token (currchar,TokenType.DIV));
                    default:
                        throw (new Exception("Caractere inválido: " + ((int) currchar)));
                }
            }
        }

        arquivo.close();

        return (new Token(currchar,TokenType.EOF));

    }
}
