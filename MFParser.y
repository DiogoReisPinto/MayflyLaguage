%{
/* $Id: MFParser.y,v 1.18 2013/02/12 17:43:58 david Exp $ */
#include <cstdlib>  // needed for getenv
#include <iostream>
#include <string>
#include "YYParser.h"
#include "nodes/all.h"

#define LINE scanner()->lineno()


// The rules below will be included in the function yyparse, the main
// parsing function. The macro below will cause the function to become
// a method instead. This is very fragile, but works with byacc.
// The class is mayfly::YYParser, a cdk::Parser subclass using
// Flex and BYACC.
#define yyparse mayfly::YYParser::yyparse

%}

%union {
  int                                i;	/* integer value */
  double			     d;
  std::string                       *s;	/* symbol name or string literal */
  bool				    boolean;	
  cdk::node::Node                   *node;	/* node pointer */
  cdk::node::Sequence               *sequence;
  cdk::node::expression::Expression *expression; /* expression nodes */
  mayfly::node::expression::LeftValue *leftvalue;
  ExpressionType			*sem;
};

%token <i> tINTEGER tZERO tOCTAL tHEXA 
%token <d> tNUMBERLIT
%token <s> tIDENTIFIER tSTRING
%token tWHILE tIF tPRINT tREAD tPROGRAM tEND tVOID tINT tNUMBER tSTR tPUBLIC tCONST tDO tTHEN tIN tSTEP tFOR tUPTO tDOWNTO tCONTINUE tBREAK tRETURN tPRINTLN
%nonassoc tIFX tFUNCX tINDEX tREF tALLOC
%nonassoc tELSE

%right '='
%left '|'
%left '&'
%nonassoc '~'
%left tGE tLE tEQ tNE '>' '<'
%left '+' '-'
%left '*' '/' '%'
%nonassoc tUMINUS tINC tDEC tPOSITION tPOINTER tUPLUS 
%nonassoc '[' ']' '{'

%type <sem> type 
%type <s> strconcat
%type <node> file declaration variable function statement condstatement iterstatement body block 
%type <sequence> declarations variables statements funcvars
%type <expression> expr literal intliteral step funcall
%type <leftvalue> lvalue

%%

file	: declarations   {_compiler->ast($1);   }
	;

declarations: declaration		{$$ = new cdk::node::Sequence(LINE, $1);}
	    | declarations declaration  {$$ = new cdk::node::Sequence(LINE, $2, $1);}		
	    ;

declaration: variables ';'	{$$ = $1;}
	   | function		{$$ = $1;}
	   ;

variables: variable 			{$$ = new cdk::node::Sequence(LINE, $1);}
	 | variables ',' variable	{$$ = new cdk::node::Sequence(LINE, $3, $1);}
	 ;

variable: type tIDENTIFIER 		{$$ = new mayfly::node::VarNode(LINE, false, false, $1, new std::string(*$2), NULL);}
	| tPUBLIC type tIDENTIFIER 		{$$ = new mayfly::node::VarNode(LINE, true, false, $2, new std::string(*$3), NULL);}
	| tCONST type tIDENTIFIER		{$$ = new mayfly::node::VarNode(LINE, false, true, $2, new std::string(*$3), NULL);}
	| tPUBLIC tCONST type tIDENTIFIER	{$$ = new mayfly::node::VarNode(LINE, true, true, $3, new std::string(*$4), NULL);}
	| type tIDENTIFIER '=' expr		{$$ = new mayfly::node::VarNode(LINE, true, false, $1, new std::string(*$2), $4);}
	| tPUBLIC type tIDENTIFIER '=' expr	{$$ = new mayfly::node::VarNode(LINE, true, false, $2, new std::string(*$3), $5);}
	| tCONST type tIDENTIFIER '=' expr	{$$ = new mayfly::node::VarNode(LINE, false, true, $2, new std::string(*$3), $5);}
	| tPUBLIC tCONST type tIDENTIFIER '=' expr	{$$ = new mayfly::node::VarNode(LINE, true, false, $3, new std::string(*$4), $6);}	
	;



function: type tIDENTIFIER '(' ')' %prec tFUNCX					{$$ = new mayfly::node::FunctionDeclareNode(LINE, false, $1, new std::string(*$2), NULL);}
	| type tIDENTIFIER '(' variables ')' %prec tFUNCX				{$$ = new mayfly::node::FunctionDeclareNode(LINE, false, $1, new std::string(*$2), $4);}
	| type tIDENTIFIER '(' ')' body					{$$ = new mayfly::node::FuncDefNode(LINE, false, $1, new std::string(*$2), NULL, NULL, $5);}
	| type tIDENTIFIER '(' ')' '=' literal body			{$$ = new mayfly::node::FuncDefNode(LINE, false, $1, new std::string(*$2), NULL, $6, $7);}
	| tVOID tIDENTIFIER '(' ')' %prec tFUNCX					{$$ = new mayfly::node::FunctionDeclareNode(LINE, false, new ExpressionType(0, ExpressionType::TYPE_VOID), new std::string(*$2), NULL);}
	| tVOID tIDENTIFIER '(' ')' body				{$$ = new mayfly::node::FuncDefNode(LINE, false, new ExpressionType(0, ExpressionType::TYPE_VOID), new std::string(*$2), NULL, NULL, $5);}
	| type tIDENTIFIER '(' variables ')' body			{$$ = new mayfly::node::FuncDefNode(LINE, false, $1, new std::string(*$2), $4, NULL, $6);}
	| type tIDENTIFIER '(' variables ')' '=' literal body		{$$ = new mayfly::node::FuncDefNode(LINE, false, $1, new std::string(*$2), $4, $7, $8);}
	| tVOID	tIDENTIFIER '(' variables ')' %prec tFUNCX				{$$ = new mayfly::node::FunctionDeclareNode(LINE, false, new ExpressionType(0, ExpressionType::TYPE_VOID), new std::string(*$2), $4);}
	| tVOID tIDENTIFIER '(' variables ')' body			{$$ = new mayfly::node::FuncDefNode(LINE, false, new ExpressionType(0, ExpressionType::TYPE_VOID), new std::string(*$2), $4, NULL, $6);}
	| tPUBLIC type tIDENTIFIER '(' ')' %prec tFUNCX					{$$ = new mayfly::node::FunctionDeclareNode(LINE, true, $2, new std::string(*$3), NULL);}
	| tPUBLIC type tIDENTIFIER '(' variables ')' %prec tFUNCX				{$$ = new mayfly::node::FunctionDeclareNode(LINE, true, $2, new std::string(*$3), $5);}
	| tPUBLIC type tIDENTIFIER '(' ')' body					{$$ = new mayfly::node::FuncDefNode(LINE, true, $2, new std::string(*$3), NULL, NULL, $6);}
	| tPUBLIC type tIDENTIFIER '(' ')' '=' literal body			{$$ = new mayfly::node::FuncDefNode(LINE, true, $2, new std::string(*$3), NULL, $7, $8);}
	| tPUBLIC tVOID tIDENTIFIER '(' ')' %prec tFUNCX					{$$ = new mayfly::node::FunctionDeclareNode(LINE, true, new ExpressionType(0, ExpressionType::TYPE_VOID), new std::string(*$3), NULL);}
	| tPUBLIC tVOID tIDENTIFIER '(' ')' body				{$$ = new mayfly::node::FuncDefNode(LINE, true, new ExpressionType(0, ExpressionType::TYPE_VOID), new std::string(*$3), NULL, NULL, $6);}
	| tPUBLIC type tIDENTIFIER '(' variables ')' body			{$$ = new mayfly::node::FuncDefNode(LINE, true, $2, new std::string(*$3), $5, NULL, $7);}
	| tPUBLIC type tIDENTIFIER '(' variables ')' '=' literal body		{$$ = new mayfly::node::FuncDefNode(LINE, true, $2, new std::string(*$3), $5, $8, $9);}
	| tPUBLIC tVOID	tIDENTIFIER '(' variables ')' %prec tFUNCX				{$$ = new mayfly::node::FunctionDeclareNode(LINE, true, new ExpressionType(0, ExpressionType::TYPE_VOID), new std::string(*$3), $5);}
	| tPUBLIC tVOID tIDENTIFIER '(' variables ')' body			{$$ = new mayfly::node::FuncDefNode(LINE, true, new ExpressionType(0, ExpressionType::TYPE_VOID), new std::string(*$3), $5, NULL, $7);}
	;
	
funcall: tIDENTIFIER '(' ')'						{$$ = new mayfly::node::expression::FunCallNode(LINE, new std::string(*$1), NULL);}
 	| tIDENTIFIER '(' funcvars ')'					{$$ = new mayfly::node::expression::FunCallNode(LINE, new std::string(*$1), $3);}
	;

funcvars: expr		{$$ = new cdk::node::Sequence(LINE, $1);}
	| funcvars ',' expr	{$$ = new cdk::node::Sequence(LINE, $3, $1);}
	;

type: tINT		{$$ = new ExpressionType(4, ExpressionType::TYPE_INT);}
    | tNUMBER		{$$ = new ExpressionType(8, ExpressionType::TYPE_DOUBLE);}
    | tSTR		{$$ = new ExpressionType(4, ExpressionType::TYPE_STRING);}
    | type '*'		{$$ = new ExpressionType(4, ExpressionType::TYPE_POINTER);}
    ;

body: block		{$$ = $1;}
    ;

block: '{' '}'				{$$ = new mayfly::node::BlockNode(LINE, NULL, NULL);}
     | '{' declarations '}'		{$$ = new mayfly::node::BlockNode(LINE, $2, NULL);}
     | '{' statements '}'		{$$ = new mayfly::node::BlockNode(LINE, NULL, $2); }
     | '{' declarations statements '}'  {$$ = new mayfly::node::BlockNode(LINE, $2, $3);}
     ;

literal: strconcat		{$$ = new cdk::node::expression::String(LINE, $1);}
       | intliteral	{$$ = $1;}
       | tNUMBERLIT	{$$ = new cdk::node::expression::Double(LINE, $1);}
       ;

strconcat: tSTRING		{$$ = new std::string(*$1);}
         | strconcat tSTRING  {$$ = new std::string(*$1 + *$2);}
         ;

intliteral: tINTEGER	{$$ = new cdk::node::expression::Integer(LINE, $1);}
	  | tOCTAL	{$$ = new cdk::node::expression::Integer(LINE, $1);}
	  | tHEXA	{$$ = new cdk::node::expression::Integer(LINE, $1);}
	  | tZERO	{$$ = new cdk::node::expression::Integer(LINE, $1);}
	  ;

statements: statement			{$$ = new cdk::node::Sequence(LINE, $1);}
	  | statements statement	{$$ = new cdk::node::Sequence(LINE, $2, $1);}
	  ;

statement: expr ';'			{$$ = $1;}
	  | expr tPRINT			{$$ = new mayfly::node::PrintNode(LINE, $1);}
	  | expr tPRINTLN		{$$ = new mayfly::node::PrintLnNode(LINE, $1);}
	  | tBREAK ';'			{$$ = new mayfly::node::BreakNode(LINE, 0);}
	  | tCONTINUE ';' 		{$$ = new mayfly::node::ContinueNode(LINE, 0);}
	  | tBREAK tINTEGER ';' 	{$$ = new mayfly::node::BreakNode(LINE, $2);}
	  | tCONTINUE tINTEGER ';'	{$$ = new mayfly::node::ContinueNode(LINE, $2);}
	  | tRETURN			{$$ = new mayfly::node::ReturnNode(LINE);}
	  | condstatement		{$$ = $1;}
	  | iterstatement		{$$ = $1;}
	  | block			{$$ = $1;}
	  ;
	  
condstatement: tIF expr tTHEN statement	%prec tIFX 	{$$ = new mayfly::node::IfNode(LINE, $2, $4);}
	     | tIF expr tTHEN statement tELSE statement	{$$ = new mayfly::node::IfElseNode(LINE, $2, $4, $6);}
	     ;

iterstatement: tFOR tIDENTIFIER tIN expr tUPTO expr step tDO statement		{$$ = new mayfly::node::ForNode(LINE, new mayfly::node::expression::LeftValue(LINE, $2), $4, true, $6, $7, $9);}
	     | tFOR tIDENTIFIER tIN expr tDOWNTO expr step tDO statement		{$$ = new mayfly::node::ForNode(LINE, new mayfly::node::expression::LeftValue(LINE, $2), $4, false, $6, $7, $9);}
	     | tDO statement tWHILE expr ';'					{$$ = new mayfly::node::WhileNode(LINE, $4, $2);}
	     ;

step: tSTEP expr 	{$$ = $2;}
    | 			{$$ = NULL;}
    ;

expr : literal			{ $$ = $1;}
     | tIDENTIFIER		{ $$ = new cdk::node::expression::Identifier(LINE, $1);}
     | funcall			{ $$ = $1;}
     | '+' expr %prec tUPLUS	{ $$ = $2;}
     | '-' expr %prec tUMINUS  { $$ = new cdk::node::expression::NEG(LINE, $2); }
     | expr '+' expr	         { $$ = new cdk::node::expression::ADD(LINE, $1, $3); }
     | expr tINC		 { $$ = new mayfly::node::expression::INC(LINE, $1);}
     | expr tDEC		 { $$ = new mayfly::node::expression::DEC(LINE, $1);}
     | tINC expr		 { $$ = new mayfly::node::expression::INC(LINE, $2);}
     | tDEC expr		 { $$ = new mayfly::node::expression::DEC(LINE, $2);}
     | expr '-' expr	         { $$ = new cdk::node::expression::SUB(LINE, $1, $3); }
     | expr '*' expr	         { $$ = new cdk::node::expression::MUL(LINE, $1, $3); }
     | expr '/' expr	         { $$ = new cdk::node::expression::DIV(LINE, $1, $3); }
     | expr '%' expr	         { $$ = new cdk::node::expression::MOD(LINE, $1, $3); }
     | expr '<' expr	         { $$ = new cdk::node::expression::LT(LINE, $1, $3); }
     | expr '>' expr	         { $$ = new cdk::node::expression::GT(LINE, $1, $3); }
     | expr tGE expr	         { $$ = new cdk::node::expression::GE(LINE, $1, $3); }
     | expr tLE expr           { $$ = new cdk::node::expression::LE(LINE, $1, $3); }
     | expr tNE expr	         { $$ = new cdk::node::expression::NE(LINE, $1, $3); }
     | expr tEQ expr	         { $$ = new cdk::node::expression::EQ(LINE, $1, $3); }
     | '(' expr ')'            { $$ = $2; }
     | expr '&' expr		{ $$ = new mayfly::node::expression::And(LINE, $1, $3);}
     | expr '|' expr		{ $$ = new mayfly::node::expression::Or(LINE, $1, $3);}
     | '~' expr			{ $$ = new mayfly::node::expression::Not(LINE, $2);}
     | '#' expr %prec tALLOC  	{ $$ = new mayfly::node::expression::MemoryAllocate(LINE, $2);}
     | '*' expr %prec tINDEX	{ $$ = new mayfly::node::expression::MemoryIndex(LINE, $2, new cdk::node::expression::Integer(LINE, 0));}
     | expr '[' expr ']'	{ $$ = new mayfly::node::expression::MemoryIndex(LINE, $1, $3);}
     | '&' expr %prec tREF	{ $$ = new mayfly::node::expression::MemoryReference(LINE, $2);}
     | lvalue '=' '@'		{ $$ = new mayfly::node::expression::ReadNode(LINE, $1);}
     | lvalue '=' expr		{ $$ = new mayfly::node::expression::AssignmentNode(LINE, $1, $3);}
     ;

lvalue: tIDENTIFIER		{ $$ = new mayfly::node::expression::LeftValue(LINE, $1);}


%%
// $Log: MFParser.y,v $
// Revision 1.18  2013/02/12 17:43:58  david
// Further code simplification (evaluators).
//
// Revision 1.17  2013/02/11 20:56:27  david
// Minor cleanup.
//
// Revision 1.16  2013/02/10 19:20:04  david
// Code cleanup and simplification. C++11 is now mandatory.
//
// Revision 1.15  2013/02/09 18:57:46  david
// New Mayfly version (this one is to be built against CDK8).
// Major code simplification. Starting transition to C++11.
// 
// Revision 1.14  2012/04/10 19:09:46  david
// Major cleanup (comments).
// Better handling of ProgramNodes (visitors and not evaluators).
// 
// Revision 1.13  2012/02/18 19:37:58  david
// Updated Mayfly to support the new semantic analysis in CDK7.
// Debug options are now integrated with semantic analysis, eliminating a long-lived
// hack in the evaluators. Renamed Symbol to MFSymbol, to emphasize
// that it is language-specific.
// 
