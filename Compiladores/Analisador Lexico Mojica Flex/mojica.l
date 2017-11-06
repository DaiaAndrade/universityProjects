letra						[a-zA-Z]
digito						[0-9]
digitos						{digito}+
fracao_opcional				("."{digitos})?
expoente_opcional			("E"("+"|"-")?{digitos})?
letraoudigito				{letra}|{digito}
finalsublinhado				{letraoudigito}+

token_id					{letra}+({letraoudigito})*({finalsublinhado})*
token_numliteral			{digitos}+({fracao_opcional})+({expoente_opcional})*
token_reservadas			"void"|"int"|"bool"|"if"|"while"|"do"|"return"|"true"|"false"|"not"|"and"|"or"|"leq"|"skip"

%%

"{"	{ printf("abre_chave\n"); }
"}"	{ printf("fecha_chave\n"); }
"("	{ printf("abre_parentese\n"); }
")"	{ printf("fecha_parentes\n"); }
","	{ printf("virgula\n"); }
";"	{ printf("ponto_e_virgula\n"); }

":=" { printf("operador_atribuição\n"); }

"+"	{ printf("operador + \n"); }
"-"	{ printf("operador - \n"); }
"*"	{ printf("operador * \n"); }
"/"	{ printf("operador / \n"); }

{token_reservadas}	{ printf("palavra_reservada: %s\n",yytext); } 

{token_id}	{ printf("identificador: %s\n",yytext); } 
{token_numliteral} { printf("numero: %s\n",yytext); } 

" "|"\n"|"\t"|"\r" {	}

. { printf("Simbolo %s nao esperado.\n", yytext); }
%%
int yywrap();

main(){
  yylex();
}

int yywrap(){
 return 1;
}