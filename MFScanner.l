%option c++ yyclass="MFScanner" outfile="MFScanner.cpp"
%option stack noyywrap yylineno 8bit debug
%{ 
/* $Id: MFScanner.l,v 1.14 2013/02/11 20:56:27 david Exp $ */
#include <string>
#include <cdk/nodes/Node.h>
#include <cdk/nodes/Sequence.h>
#include <cdk/nodes/expressions/Expression.h>
#include "MFScanner.h"

// ensure that relevant includes are made before including the following
#include "MFParser.tab.h"

// this is terrible...
#define yyerror LexerError

std::string str;
%}

%x X_COMMENTLINE X_COMMENT X_STRING X_STRNOTIMPORTANT
%%
	{set_debug(0);}

">>"	  yy_push_state(X_COMMENTLINE);
<X_COMMENTLINE>\n	yy_pop_state();
<X_COMMENTLINE>.	;
"=<"		yy_push_state(X_COMMENT);
<X_COMMENT>"=<"	yy_push_state(X_COMMENT);
<X_COMMENT>"=>"	yy_pop_state();
<X_COMMENT>.|\n	;

">="      return tGE;
"<="      return tLE; 
"=="      return tEQ; 
"<>"      return tNE; 
"void" 		return tVOID;
"integer"	return tINT;
"number"	return tNUMBER;
"string"	return tSTR;
"public"	return tPUBLIC;
"const"		return tCONST;
"do"		return tDO;
"while"   return tWHILE; 
"if"      return tIF; 
"then"		return tTHEN;
"else"    return tELSE; 
"for"		return tFOR;
"in"		return tIN;
"step"		return tSTEP;
"upto"		return tUPTO;
"downto"	return tDOWNTO;
"continue"	return tCONTINUE;
"break"		return tBREAK;
"return"	return tRETURN;
"!"   return tPRINT;
"!!"		return tPRINTLN;
"++"		return tINC;
"--"		return tDEC; 
  

[A-Za-z_][A-Za-z0-9_]*  { yylval.s = new std::string(yytext); return tIDENTIFIER;}
\"              	{yy_push_state(X_STRING); yylval.s = new std::string(); }

<X_STRING>\\\"  	{yytext[yyleng - 1] = 0; *yylval.s += yytext+1; }
<X_STRING>\"    	{yy_pop_state(); return tSTRING;}
<X_STRING>\\[0]*[aA]	;
<X_STRING>\\[0]*[dD]	;
<X_STRING>\\20		;
<X_STRING>\\[0]*9	;
<X_STRING>\\t		;
<X_STRING>\\[0-9a-fA-F][1-9a-fA-F] { yytext++; *yylval.s += strtol(yytext, NULL, 16);}	
<X_STRING>\\[a-fA-F0-9]	     { yytext++; *yylval.s += strtol(yytext, NULL, 16);}
<X_STRING>'\0'		yyerror("NULL or \0 inside string");
<X_STRING>.     	{*yylval.s += yytext ;}
<X_STRING>\\n		;
[1-9][0-9]*               	{errno = 0; yylval.i = strtol(yytext, nullptr, 10); if(errno==ERANGE) yyerror("OVERFLOW!"); else return tINTEGER; }
0				{yylval.i = strtol(yytext, nullptr, 10); return tZERO;}
0[0-7]+				{errno = 0; yylval.i = strtol(yytext, nullptr, 8); if(errno==ERANGE) yyerror("OVERFLOW!"); else return tOCTAL;}
0[xX][0-9a-fA-F]+		{errno = 0; yylval.i = strtol(yytext, nullptr,16 ); if(errno==ERANGE) yyerror("OVERFLOW!"); else return tHEXA;}
[0-9]+"."[0-9]*e[0-9]+		{yylval.d = strtod(yytext, nullptr); return tNUMBERLIT;}
[0-9]+"."[0-9]*([eE][+-]*[0-9]+)+	{yylval.d = strtod(yytext, nullptr); return tNUMBERLIT;}
[@,:\[\]&()<>=~|+*/%;{}-]       return *yytext;

[ \t\n]+  ; /* ignore whitespace */

.   yyerror("Unknown character");
%%
/**
 * Very, very dirty hack: flex is a mess generating C++.
 */
int MFScanner::yywrap() { return 1;}

//---------------------------------------------------------------------------
//     T H E    E N D
//---------------------------------------------------------------------------
// $Log: MFScanner.l,v $
// Revision 1.14  2013/02/11 20:56:27  david
// Minor cleanup.
//
// Revision 1.13  2013/02/09 18:57:46  david
// New Mayfly version (this one is to be built against CDK8).
// Major code simplification. Starting transition to C++11.
//
// Revision 1.12  2012/04/10 19:09:46  david
// Major cleanup (comments).
// Better handling of ProgramNodes (visitors and not evaluators).
// 
