// $Id: PFwriter.cpp,v 1.23 2013-05-19 23:46:08 ist169632 Exp $ -*- c++ -*-
#include <string>
#include <iostream>
#include <sstream>
#include "semantics/PFwriter.h"
#include "semantics/TypeValidator.h"
#include "semantics/StackCounter.h"
#include "nodes/all.h"  // all.h is automatically generated

// just to get a shorter name
namespace cpt = mayfly;
int offset = 0;
bool global = true;
std::vector<int> breaklbls;
std::vector<int> continuelbls;
std::vector<std::string> externs;
bool arguments;
std::string current_func;
//---------------------------------------------------------------------------
//     THIS IS THE VISITOR'S DEFINITION
//---------------------------------------------------------------------------

void cpt::semantics::PFwriter::processSequence(cdk::node::Sequence * const node, int lvl) {
  for (size_t i = 0; i < node->size(); i++) {
    node->node(i)->accept(this, lvl);
  }
}

//---------------------------------------------------------------------------

void cpt::semantics::PFwriter::processInteger(cdk::node::expression::Integer * const node, int lvl) {
  if(!global)
		_pf.INT(node->value()); // push an integer
	else
		_pf.CONST(node->value());
}

void cpt::semantics::PFwriter::processDouble(cdk::node::expression::Double * const node, int lvl) {
  if(!global)
		_pf.DOUBLE(node->value());
	else
		_pf.CONST(node->value());
}
void cpt::semantics::PFwriter::processString(cdk::node::expression::String * const node, int lvl) {
  int lbl1;

  _pf.RODATA();
  _pf.ALIGN();
  _pf.LABEL(mklbl(lbl1 = ++_lbl));
  _pf.STR(node->value()); // output string characters
	if(!global){
  	_pf.TEXT();
  	_pf.ADDR(mklbl(lbl1));
	}else{
		_pf.DATA();
		_pf.ID(mklbl(lbl1));
	}
}

//---------------------------------------------------------------------------

void cpt::semantics::PFwriter::processIdentifier(cdk::node::expression::Identifier * const node, int lvl) {
const std::string id = node->value();
MFSymbol *symbol = _symtab.find(id);
  if (symbol != NULL) {
    if(!symbol->global()){
      _pf.LOCAL(symbol->offset());
	      if(symbol->type()->name() == ExpressionType::TYPE_DOUBLE) 
		  _pf.DLOAD();
	      else 
		  _pf.LOAD();
    }
    else{
    _pf.ADDRV(id);
		}
	}
}

//---------------------------------------------------------------------------

void cpt::semantics::PFwriter::processNEG(cdk::node::expression::NEG * const node, int lvl) {
  node->argument()->accept(this, lvl); // determine the value
  _pf.NEG(); // 2-complement
}

//---------------------------------------------------------------------------

void cpt::semantics::PFwriter::processADD(cdk::node::expression::ADD * const node, int lvl) {
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.ADD();
}
void cpt::semantics::PFwriter::processSUB(cdk::node::expression::SUB * const node, int lvl) {
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.SUB();
}
void cpt::semantics::PFwriter::processMUL(cdk::node::expression::MUL * const node, int lvl) {
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.MUL();
}
void cpt::semantics::PFwriter::processDIV(cdk::node::expression::DIV * const node, int lvl) {
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.DIV();
}
void cpt::semantics::PFwriter::processMOD(cdk::node::expression::MOD * const node, int lvl) {
  try{
        TypeValidator v(os(), _symtab, global);
        node->accept(&v, lvl);
  } catch(std::string s) {std::cerr << s << std::endl;}

  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.MOD();
}
void cpt::semantics::PFwriter::processLT(cdk::node::expression::LT * const node, int lvl) {
  try{
	TypeValidator v(os(), _symtab, global);
	node->accept(&v, lvl);
  } catch(std::string s) {std::cerr << s << std::endl;}
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.LT();
}
void cpt::semantics::PFwriter::processLE(cdk::node::expression::LE * const node, int lvl) {
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.LE();
}
void cpt::semantics::PFwriter::processGE(cdk::node::expression::GE * const node, int lvl) {
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.GE();
}
void cpt::semantics::PFwriter::processGT(cdk::node::expression::GT * const node, int lvl) {
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.GT();
}
void cpt::semantics::PFwriter::processNE(cdk::node::expression::NE * const node, int lvl) {
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.NE();
}
void cpt::semantics::PFwriter::processEQ(cdk::node::expression::EQ * const node, int lvl) {
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.EQ();
}

//---------------------------------------------------------------------------

void cpt::semantics::PFwriter::processLeftValue(cpt::node::expression::LeftValue * const node, int lvl) {
  const std::string id = node->value();
  MFSymbol *s = _symtab.find(id);
  if (s != NULL) {
    if(!s->global())
      _pf.LOCAL(_symtab.find(id)->offset());
    else
      _pf.ADDR(id);
  }
}

void cpt::semantics::PFwriter::processAnd(cpt::node::expression::And * const node, int lvl) {
  int lbl1;

	node->left()->accept(this, lvl);
	_pf.JZ(mklbl(lbl1 = ++_lbl));
  node->right()->accept(this, lvl);
  _pf.AND();
	_pf.LABEL(mklbl(lbl1));
}

void cpt::semantics::PFwriter::processOr(cpt::node::expression::Or * const node, int lvl) {
  int lbl1;

	node->left()->accept(this, lvl);
	_pf.JNZ(mklbl(lbl1 = ++_lbl));
  node->right()->accept(this, lvl);
  _pf.OR();
	_pf.LABEL(mklbl(lbl1));
}

void cpt::semantics::PFwriter::processNot(cpt::node::expression::Not * const node, int lvl) {
  node->argument()->accept(this, lvl);
  _pf.NOT();
}

void cpt::semantics::PFwriter::processINC(cpt::node::expression::INC * const node, int lvl) {
  node->argument()->accept(this, lvl);
  _pf.INT(1);
  _pf.ADD();
  const std::string id = ((cdk::node::expression::Identifier*)node->argument())->value();
  MFSymbol *s = _symtab.find(id);
  if(!s->global())
    _pf.LOCA(s->offset());
  else
    _pf.ADDRA(id);
}

void cpt::semantics::PFwriter::processDEC(cpt::node::expression::DEC * const node, int lvl) {
  node->argument()->accept(this, lvl);
  _pf.INT(1);
  _pf.SUB();
  const std::string id = ((cdk::node::expression::Identifier*)node->argument())->value();
  MFSymbol *s = _symtab.find(id);
  if(!s->global())
    _pf.LOCA(s->offset());
  else
    _pf.ADDRA(id);
}

void cpt::semantics::PFwriter::processMemoryIndex(cpt::node::expression::MemoryIndex * const node, int lvl) {
  const std::string &id = ((cdk::node::expression::Identifier*)node->arg())->value();
  if(_symtab.find(id)){
	_pf.ADDR(id);
	node->index()->accept(this, lvl);
	if(node->arg()->type()->name() == ExpressionType::TYPE_INT){
		_pf.INT(4);
		_pf.MUL();
		_pf.ADD();
		_pf.LOAD();
	}
	if(node->arg()->type()->name() == ExpressionType::TYPE_DOUBLE){
		_pf.INT(8);
		_pf.MUL();
		_pf.ADD();
		_pf.DLOAD();
	}
  } 
}
void cpt::semantics::PFwriter::processMemoryAllocate(cpt::node::expression::MemoryAllocate * const node, int lvl) {
  node->argument()->accept(this, lvl);
  _pf.ALLOC();
}

void cpt::semantics::PFwriter::processMemoryReference(cpt::node::expression::MemoryReference * const node, int lvl) {
  const std::string &id = ((cdk::node::expression::Identifier*)node->arg())->value();
  if(_symtab.find(id))
	_pf.ADDR(id);
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

void cpt::semantics::PFwriter::processPrintNode(cpt::node::PrintNode * const node, int lvl) {
	try{
		TypeValidator v(os(), _symtab, global);
		node->accept(&v, lvl);
	}catch (std::string s) {std::cerr << s << std::endl;}

	node->argument()->accept(this, lvl);
 	
	if(node->argument()->type()->name() == ExpressionType::TYPE_INT){
		_pf.CALL("printi");
	}
	else if(node->argument()->type()->name() == ExpressionType::TYPE_DOUBLE){
		_pf.CALL("printd");
	}
	else if(node->argument()->type()->name() == ExpressionType::TYPE_STRING){
		_pf.CALL("prints");
	}
 	else {_pf.CALL("printi");}
	_pf.TRASH(4);
}

//---------------------------------------------------------------------------

void cpt::semantics::PFwriter::processReadNode(cpt::node::expression::ReadNode * const node, int lvl) {
  try{
		TypeValidator v(os(), _symtab, global);
		node->argument()->accept(&v, lvl);
	} catch(std::string s) {std::cerr << s << std::endl;}

	if(node->argument()->type()->name() == ExpressionType::TYPE_INT)
		_pf.CALL("readi");
	else
		_pf.CALL("readd");
  _pf.PUSH();
  node->argument()->accept(this, lvl);
  _pf.STORE();
}

//---------------------------------------------------------------------------

void cpt::semantics::PFwriter::processWhileNode(cpt::node::WhileNode * const node, int lvl) {
  int lbl1, lbl2;
	breaklbls.push_back(lbl2 = ++_lbl);
  continuelbls.push_back(lbl1 = ++_lbl);
 
	_pf.LABEL(mklbl(lbl1));
  node->block()->accept(this, lvl + 2);
 	node->condition()->accept(this, lvl);
	_pf.JNZ(mklbl(lbl1));
	_pf.LABEL(mklbl(lbl2));

	breaklbls.pop_back();
	continuelbls.pop_back();
}

//---------------------------------------------------------------------------

void cpt::semantics::PFwriter::processAssignmentNode(cpt::node::expression::AssignmentNode * const node, int lvl) {
  
  const std::string &id = node->lvalue()->value();
  

  node->rvalue()->accept(this, lvl); // determine the new value
	_pf.DUP();
  node->lvalue()->accept(this, lvl); // where to store the value
  _pf.STORE(); // store the value at address
}

//---------------------------------------------------------------------------

void cpt::semantics::PFwriter::processIfNode(cpt::node::IfNode * const node, int lvl) {
  int lbl1;
  node->condition()->accept(this, lvl);
  _pf.JZ(mklbl(lbl1 = ++_lbl));
  node->block()->accept(this, lvl + 2);
  _pf.LABEL(mklbl(lbl1));
}

//---------------------------------------------------------------------------

void cpt::semantics::PFwriter::processIfElseNode(cpt::node::IfElseNode * const node, int lvl) {
  int lbl1, lbl2;
  node->condition()->accept(this, lvl);
  _pf.JZ(mklbl(lbl1 = ++_lbl));
  node->thenblock()->accept(this, lvl + 2);
  _pf.JMP(mklbl(lbl2 = ++_lbl));
  _pf.LABEL(mklbl(lbl1));
  node->elseblock()->accept(this, lvl + 2);
  _pf.LABEL(mklbl(lbl1 = lbl2));
}

void cpt::semantics::PFwriter::processForNode(cpt::node::ForNode * const node, int lvl) {
  int lbl1, lbl2, lbl3; //cond, inc, end
	breaklbls.push_back(lbl3 = ++_lbl);
	continuelbls.push_back(lbl2 = ++_lbl);
	
  node->startcondition()->accept(this, lvl);
	node->variable()->accept(this, lvl);
	_pf.STORE();
	_pf.LABEL(mklbl(lbl1 = ++_lbl));
	node->variable()->accept(this, lvl);
	_pf.LOAD();
	node->startcondition()->accept(this,lvl);
	if(node->upto())
		_pf.GE();
	else
		_pf.LE();
	_pf.JZ(mklbl(lbl3));
	node->variable()->accept(this, lvl);
	_pf.LOAD();
	node->stopcondition()->accept(this, lvl);
	if(node->upto())
		_pf.LE();
	else
		_pf.GE();
	_pf.JZ(mklbl(lbl3));
	node->block()->accept(this, lvl);
	_pf.LABEL(mklbl(lbl2));
	node->variable()->accept(this, lvl);
	_pf.LOAD();
	if(node->step())
		node->step()->accept(this ,lvl);
	else
		_pf.INT(1);
	if(node->upto())
		_pf.ADD();
	else
		_pf.SUB();
	node->variable()->accept(this, lvl);
	_pf.STORE();
	_pf.JMP(mklbl(lbl1));
	_pf.LABEL(mklbl(lbl3));

	breaklbls.pop_back();
  continuelbls.pop_back();  
}

void cpt::semantics::PFwriter::processFunctionDeclareNode(cpt::node::FunctionDeclareNode * const node, int lvl) {
	std::string name = *node->name();
	if(name == "_main")
		name = "mayfly";
	_symtab.insert(name, new MFSymbol(node->type(), name, 0, global));
	externs.push_back(name);
}

void cpt::semantics::PFwriter::processFuncDefNode(cpt::node::FuncDefNode * const node, int lvl) {
	global = false;
	offset = 0;
  std::string name = *node->name();
	
	if(name == "mayfly")
		name = "_main";
	else if(name == "_main")
		name = "mayfly";
	
	current_func = name;
	
  mayfly::semantic::StackCounter * s = new mayfly::semantic::StackCounter();

 	MFSymbol *symbol = NULL; 
	 
	node->accept(s, lvl);
	if(s->stack() != 0 && !_symtab.find(name)){
		_symtab.insert(name, new MFSymbol(node->type(), name, -s->stack(), global));
		symbol = _symtab.find(name);
	}
	else if(s->stack() !=0 && _symtab.find(name)){
		_symtab.replace(name, new MFSymbol(node->type(), name, -s->stack(), global));
		symbol = _symtab.find(name);
	}
	
	arguments = true;
	offset = 8;
	if(node->arguments())
		node->arguments()->accept(this, lvl);
	arguments = false;
	offset = 0;

  _pf.TEXT();
  _pf.ALIGN();
  _pf.GLOBAL(name, _pf.FUNC());
  _pf.LABEL(name);
	_pf.TEXT();
  _pf.ENTER(s->stack());
	if(node->funcreturn()){
		node->funcreturn()->accept(this, lvl);
		_pf.LOCA(symbol->offset());
	}
	_symtab.push();
		
  node->block()->accept(this, lvl);

  // end the main function
 	if(symbol != NULL || node->funcreturn())
		_pf.LOCV(symbol->offset());
	else
		_pf.INT(0);
	_pf.POP();
  _pf.LEAVE();
  _pf.RET();

  // these are just a few library function imports
	if(name == "_main"){
  	_pf.EXTERN("readi");
		_pf.EXTERN("readd");
  	_pf.EXTERN("printi");
		_pf.EXTERN("printd");
  	_pf.EXTERN("prints");
  	_pf.EXTERN("println");
	}

	for(unsigned int i = 0; i < externs.size(); i++){
		if(externs[i] == name || externs[i] == "")
			externs[i] = "";
		else if(name == "_main")
			_pf.EXTERN(externs[i]);
	}

	_symtab.pop(); 
  global = true;
}

void cpt::semantics::PFwriter::processFunCallNode(cpt::node::expression::FunCallNode * const node, int lvl) {
	if(node->arguments())
		for(int i = node->arguments()->size(); i > 0; i--){
			node->arguments()->node(i-1)->accept(this, lvl);
			
		}
		
	std::string id = *node->name();
	if(id == "_main")
		id = "mayfly";
	_pf.CALL(id);
	_pf.PUSH();
}

void cpt::semantics::PFwriter::processContinueNode(cpt::node::ContinueNode * const node, int lvl) {
	_pf.JMP(mklbl(continuelbls[continuelbls.size() - node->argument() - 1]));
}

void cpt::semantics::PFwriter::processBreakNode(cpt::node::BreakNode * const node, int lvl) {
	_pf.JMP(mklbl(breaklbls[breaklbls.size() - node->argument() - 1]));
}

void cpt::semantics::PFwriter::processReturnNode(cpt::node::ReturnNode * const node, int lvl) {
	MFSymbol *s = _symtab.find(current_func);
	if(s != NULL){
		_pf.LOCV(s->offset());
		_pf.POP();
	}
	_pf.LEAVE();
	_pf.RET();
}

void cpt::semantics::PFwriter::processPrintLnNode(cpt::node::PrintLnNode * const node, int lvl) {
	try{
		TypeValidator v(os(), _symtab, global);
		node->accept(&v, lvl);
	}catch (std::string s) {std::cerr << s << std::endl;}

	node->argument()->accept(this, lvl);
 	
	if(node->argument()->type()->name() == ExpressionType::TYPE_INT){
		_pf.CALL("printi");
	}
	else if(node->argument()->type()->name() == ExpressionType::TYPE_DOUBLE){
		_pf.CALL("printd");
	}
	else if(node->argument()->type()->name() == ExpressionType::TYPE_STRING){
		_pf.CALL("prints");
	}
 	else {_pf.CALL("printi");}
	_pf.TRASH(4);
	_pf.CALL("println");
}
void cpt::semantics::PFwriter::processVarNode(cpt::node::VarNode * const node, int lvl) {
  try{
	TypeValidator v(os(), _symtab, global);
	node->accept(&v, lvl);
	std::string *id = node->varname();
	MFSymbol *s = _symtab.find(*id);
	if(!global && !arguments){
		if(node->type()->name() == ExpressionType::TYPE_INT && !node->init()){
			_pf.INT(0);
			_pf.LOCA(s->offset(offset -= 4));
		}
		if(node->type()->name() == ExpressionType::TYPE_DOUBLE && !node->init()){
			_pf.DOUBLE(0);
			_pf.LOCA(s->offset(offset -= 8));
		}
		if((node->type()->name() == ExpressionType::TYPE_INT) && node->init()){
			node->init()->accept(this, lvl);
			_pf.LOCA(s->offset(offset -= 4));
		}
		if(node->type()->name() == ExpressionType::TYPE_DOUBLE && node->init()){
			node->init()->accept(this, lvl);
			_pf.LOCA(s->offset(offset -= 8));
		}
	}
	else if(arguments){
		s->offset(offset);
		offset += node->type()->size();
	}
	else{
		_pf.DATA();
		_pf.ALIGN();
		_pf.LABEL(*id);
		if(node->init())
			node->init()->accept(this, lvl);
		else 
			_pf.CONST(0);
		}
	} catch(std::string s){
	std::cerr << "FATAL: " << node->lineno() << ": " << s << std::endl;
	return;
  }
}

void cpt::semantics::PFwriter::processBlockNode(cpt::node::BlockNode * const node, int lvl) {
  if(node->declarations())
	node->declarations()->accept(this, lvl);
	if(node->statements())
	node->statements()->accept(this, lvl);
}
//---------------------------------------------------------------------------
//     T H E    E N D
//---------------------------------------------------------------------------
// $Log: PFwriter.cpp,v $
// Revision 1.23  2013-05-19 23:46:08  ist169632
// Externs are working now
//
// Revision 1.15  2013-05-18 14:14:11  ist169632
// Fixed some bugs
//
// Revision 1.14  2013-05-17 02:08:14  ist169632
// FuncDef now recognizes names to change from mayfly to _main and from _main to mayfly
//
// Revision 1.12  2013-05-16 20:57:17  ist169632
// StackCounter added
//
// Revision 1.7  2013-05-13 14:37:54  ist169632
// Entrega intermédia corrigida. TypeValidator corrigido
//
// Revision 1.6  2013-04-29 16:46:08  ist169632
// Read and funCall are now expressions. MFParser changed accordingly.
//
// Revision 1.5  2013-04-18 17:29:30  ist169905
// *** empty log message ***
//
// Revision 1.4  2013-04-18 15:28:05  ist169632
// Added BlockNode.
// Included type in function and vars.
// Fixed some bugs
//
// Revision 1.3  2013-04-02 01:34:36  ist169632
// Added missing nodes from E0
//
// Revision 1.2  2013-03-24 20:19:32  ist169632
// fixed bugs
//
// Revision 1.1  2013-02-16 16:10:14  ist13500
// This is a base mayfly version.
// This is just Compact with the names changed.
//
// Revision 1.14  2013/02/10 19:20:04  david
// Code cleanup and simplification. C++11 is now mandatory.
//
// Revision 1.13  2013/02/09 18:57:47  david
// New Mayfly version (this one is to be built against CDK8).
// Major code simplification. Starting transition to C++11.
//
// Revision 1.12  2012/04/10 19:10:45  david
// Minor comment cleanup.
//
// Revision 1.11  2012/04/10 19:09:47  david
// Major cleanup (comments).
// Better handling of ProgramNodes (visitors and not evaluators).
//
// Revision 1.10  2012/02/18 19:37:58  david
// Updated Mayfly to support the new semantic analysis in CDK7.
// Debug options are now integrated with semantic analysis, eliminating a long-lived
// hack in the evaluators. Renamed Symbol to MFSymbol, to emphasize
// that it is language-specific.
//
