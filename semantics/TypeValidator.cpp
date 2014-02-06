#include <string>
#include "semantics/TypeValidator.h"

#include <cdk/semantics/ExpressionType.h>

#include <cdk/nodes/Composite.h>
#include <cdk/nodes/Sequence.h>

#include <cdk/nodes/expressions/Expression.h>
#include <cdk/nodes/expressions/Integer.h>
#include <cdk/nodes/expressions/Double.h>
#include <cdk/nodes/expressions/String.h>
#include <cdk/nodes/expressions/Identifier.h>
#include <cdk/nodes/expressions/NEG.h>
#include <cdk/nodes/expressions/ADD.h>
#include <cdk/nodes/expressions/SUB.h>
#include <cdk/nodes/expressions/MUL.h>
#include <cdk/nodes/expressions/DIV.h>
#include <cdk/nodes/expressions/MOD.h>
#include <cdk/nodes/expressions/LT.h>
#include <cdk/nodes/expressions/GT.h>
#include <cdk/nodes/expressions/GE.h>
#include <cdk/nodes/expressions/LE.h>
#include <cdk/nodes/expressions/NE.h>
#include <cdk/nodes/expressions/EQ.h>

#include "nodes/IfNode.h"
#include "nodes/BreakNode.h"
#include "nodes/FunctionDeclareNode.h"
#include "nodes/PrintLnNode.h"
#include "nodes/expression/ReadNode.h"
#include "nodes/expression/And.h"
#include "nodes/expression/INC.h"
#include "nodes/expression/MemoryIndex.h"
#include "nodes/expression/Not.h"
#include "nodes/expression/Or.h"
#include "nodes/expression/MemoryAllocate.h"
#include "nodes/expression/MemoryReference.h"
#include "nodes/expression/LeftValue.h"
#include "nodes/expression/FunCallNode.h"
#include "nodes/expression/DEC.h"
#include "nodes/PrintNode.h"
#include "nodes/expression/AssignmentNode.h"
#include "nodes/ContinueNode.h"
#include "nodes/IfElseNode.h"
#include "nodes/VarNode.h"
#include "nodes/FuncDefNode.h"
#include "nodes/WhileNode.h"
#include "nodes/BlockNode.h"
#include "nodes/ReturnNode.h"
#include "nodes/ForNode.h"

TypeValidator::~TypeValidator(){}

void TypeValidator::processComposite(cdk::node::Composite * const node, int lvl){
     for (size_t i = 0; i < node->size(); i++)
     node->at(i)->accept(this, lvl+2);
}

void TypeValidator::processSequence(cdk::node::Sequence * const node, int lvl){
     for (size_t i = 0; i < node->size(); i++) {
     cdk::node::Node *n = node->node(i);
     if (n == NULL) break;
     n->accept(this, lvl+2);
     }
}

template<typename T> void TypeValidator::processSimple(cdk::node::expression::Simple<T> * const node, int lvl) {throw 42;}

void TypeValidator::processInteger(cdk::node::expression::Integer * const node, int lvl){
     node->type(new ExpressionType(4, ExpressionType::TYPE_INT));
}

void TypeValidator::processDouble(cdk::node::expression::Double * const node, int lvl){
     node->type(new ExpressionType(8, ExpressionType::TYPE_DOUBLE));
}

void TypeValidator::processString(cdk::node::expression::String * const node, int lvl){
     node->type(new ExpressionType(4, ExpressionType::TYPE_STRING));
}

void TypeValidator::processIdentifier(cdk::node::expression::Identifier * const node, int lvl){
  const char* id = node->value().c_str();
  MFSymbol *s = _symtab.find(id);
  if(!s)
    throw std::string(id) + " undeclared";
  
  node->type(s->type());
}

void TypeValidator::processIntAndNumUnaryExpression(cdk::node::expression::UnaryExpression *const node, int lvl){
  node->argument()->accept(this, lvl+2);
  if(node->argument()->type()->name() != ExpressionType::TYPE_INT && ExpressionType::TYPE_DOUBLE)
    throw std::string("integer or number expression expected");

  node->type(node->argument()->type());
}

void TypeValidator::processIntAndPointerUnaryExpression(cdk::node::expression::UnaryExpression *const node, int lvl){
  node->argument()->accept(this, lvl+2);
  if(node->argument()->type()->name() != ExpressionType::TYPE_INT && ExpressionType::TYPE_POINTER)
    throw std::string("integer or pointer expression expected");

  node->type(node->argument()->type());
}

void TypeValidator::processAdditiveExpression(cdk::node::expression::BinaryExpression *const node, int lvl) {
  node->left()->accept(this, lvl+2);
  if (node->left()->type()->name() != ExpressionType::TYPE_INT && ExpressionType::TYPE_DOUBLE && ExpressionType::TYPE_POINTER)
    throw std::string("integer, number or pointer expression expected in binary operator (left)");

  node->right()->accept(this, lvl+2);
  if (node->right()->type()->name() != ExpressionType::TYPE_INT && ExpressionType::TYPE_DOUBLE)
    throw std::string("integer or number expression expected in binary operator (right)");

  if (node->left()->type()->name() != node->right()->type()->name())
    throw std::string("types do not match");
  else if(node->left()->type()->name() == node->right()->type()->name())
    node->type(node->left()->type());
  else if(node->left()->type()->name() == ExpressionType::TYPE_POINTER && node->right()->type()->name() == ExpressionType::TYPE_INT)
    node->type(node->left()->type());
}

void TypeValidator::processIntAndNumExpression(cdk::node::expression::BinaryExpression *const node, int lvl) {
  node->left()->accept(this, lvl+2);
  if (node->left()->type()->name() != ExpressionType::TYPE_INT && ExpressionType::TYPE_DOUBLE)
    throw std::string("integer or number expression expected in binary operator (left)");

  node->right()->accept(this, lvl+2);
  if (node->right()->type()->name() != ExpressionType::TYPE_INT && ExpressionType::TYPE_DOUBLE)
    throw std::string("integer or number expression expected in binary operator (right)");

  if (node->left()->type()->name() != node->right()->type()->name())
    throw std::string("types do not match");
  
    node->type(node->left()->type());
}

void TypeValidator::processIntOnlyExpression(cdk::node::expression::BinaryExpression *const node, int lvl){
    //if(node->type()->name() == ExpressionType::TYPE_UNSPEC){
        node->left()->accept(this, lvl+2);
        if (node->left()->type()->name() != ExpressionType::TYPE_INT)
            throw std::string("integer expression expected in binary operator (left)");
     
        node->right()->accept(this, lvl+2);
        if (node->right()->type()->name() != ExpressionType::TYPE_INT)
            throw std::string("integer expression expected in binary operator (right)");
     
        node->type(node->left()->type());
    //}
}

void TypeValidator::processIntAndPointerExpression(cdk::node::expression::BinaryExpression *const node, int lvl) {
  node->left()->accept(this, lvl+2);
  if (node->left()->type()->name() != ExpressionType::TYPE_INT && ExpressionType::TYPE_POINTER)
    throw std::string("integer or pointer expression expected in binary operator (left)");

  node->right()->accept(this, lvl+2);
  if (node->right()->type()->name() != ExpressionType::TYPE_INT && ExpressionType::TYPE_POINTER)
    throw std::string("integer or pointer expression expected in binary operator (right)");

  if (node->left()->type()->name() != node->right()->type()->name())
    throw std::string("types do not match");

  node->type(node->left()->type());
}

void TypeValidator::processScalarLogicalExpression(cdk::node::expression::BinaryExpression *const node, int lvl) {
  node->left()->accept(this, lvl+2);
  if (node->left()->type()->name() != ExpressionType::TYPE_INT && ExpressionType::TYPE_DOUBLE)
    throw std::string("integer or number expression expected in binary operator (left)");

  node->right()->accept(this, lvl+2);
  if (node->right()->type()->name() != ExpressionType::TYPE_INT && ExpressionType::TYPE_DOUBLE)
    throw std::string("integer or number expression expected in binary operator (right)");

  if (node->left()->type()->name() != node->right()->type()->name())
    throw std::string("types do not match");

  node->type(new ExpressionType(4, ExpressionType::TYPE_BOOLEAN));
}

void TypeValidator::processBooleanLogicalExpression(cdk::node::expression::BinaryExpression *const node, int lvl) {
  node->left()->accept(this, lvl+2);
  if (node->left()->type()->name() != ExpressionType::TYPE_BOOLEAN)
    throw std::string("boolean expression expected in binary expression");

  node->right()->accept(this, lvl+2);
  if (node->right()->type()->name() != ExpressionType::TYPE_BOOLEAN)
    throw std::string("boolean expression expected in binary expression");

  node->type(new ExpressionType(4, ExpressionType::TYPE_BOOLEAN));
}

void TypeValidator::processGeneralLogicalExpression(cdk::node::expression::BinaryExpression *const node, int lvl) {
  node->left()->accept(this, lvl+2);
  node->right()->accept(this, lvl+2);
  node->type(new ExpressionType(4, ExpressionType::TYPE_BOOLEAN));
}

void TypeValidator::processNEG(cdk::node::expression::NEG *const node, int lvl) {
  node->argument()->accept(this, lvl);
  if (node->argument()->type()->name() == ExpressionType::TYPE_INT)
    node->type(node->argument()->type());
  else throw std::string("integer expression expected");
}

void TypeValidator::processUnaryExpression(cdk::node::expression::UnaryExpression * const node, int lvl) {throw 42;}
void TypeValidator::processNot(mayfly::node::expression::Not * const node, int lvl){processIntAndNumUnaryExpression(node, lvl);}
void TypeValidator::processINC(mayfly::node::expression::INC * const node, int lvl){processIntAndPointerUnaryExpression(node, lvl);}
void TypeValidator::processDEC(mayfly::node::expression::DEC * const node, int lvl){processIntAndPointerUnaryExpression(node, lvl);}
void TypeValidator::processMemoryAllocate(mayfly::node::expression::MemoryAllocate * const node, int lvl){
  node->argument()->accept(this, lvl);
  if (node->argument()->type()->name() == ExpressionType::TYPE_INT)
    node->type(node->argument()->type());
  else throw std::string("integer expression expected");
}

void TypeValidator::processBinaryExpression(cdk::node::expression::BinaryExpression * const node, int lvl) {throw 42;}
void TypeValidator::processADD(cdk::node::expression::ADD * const node, int lvl){ processAdditiveExpression(node, lvl);}
void TypeValidator::processSUB(cdk::node::expression::SUB * const node, int lvl){ processAdditiveExpression(node, lvl);}
void TypeValidator::processMUL(cdk::node::expression::MUL * const node, int lvl){ processIntAndNumExpression(node, lvl);}
void TypeValidator::processDIV(cdk::node::expression::DIV * const node, int lvl){ processIntAndNumExpression(node, lvl);}
void TypeValidator::processMOD(cdk::node::expression::MOD * const node, int lvl){ processIntOnlyExpression(node, lvl);}
void TypeValidator::processLT(cdk::node::expression::LT * const node, int lvl){ processScalarLogicalExpression(node, lvl);}
void TypeValidator::processLE(cdk::node::expression::LE * const node, int lvl){ processScalarLogicalExpression(node, lvl);}
void TypeValidator::processGE(cdk::node::expression::GE * const node, int lvl){ processScalarLogicalExpression(node, lvl);}
void TypeValidator::processGT(cdk::node::expression::GT * const node, int lvl){ processScalarLogicalExpression(node, lvl);}
void TypeValidator::processNE(cdk::node::expression::NE * const node, int lvl){ processGeneralLogicalExpression(node, lvl);}
void TypeValidator::processEQ(cdk::node::expression::EQ * const node, int lvl){ processGeneralLogicalExpression(node, lvl);}
void TypeValidator::processAnd(mayfly::node::expression::And * const node, int lvl){ processBooleanLogicalExpression(node, lvl);}
void TypeValidator::processOr(mayfly::node::expression::Or * const node, int lvl){ processBooleanLogicalExpression(node, lvl);}

void TypeValidator::processLeftValue(mayfly::node::expression::LeftValue * const node, int lvl){
	const char *id = node->value().c_str();
	MFSymbol *s = _symtab.find(id);
	if(!s)
		throw std::string(id) + " undeclared";
	node->type(s->type());
}


void TypeValidator::processMemoryIndex(mayfly::node::expression::MemoryIndex * const node, int lvl){
	try{
		node->index()->accept(this, lvl);
		if(node->index()->type()->name() != ExpressionType::TYPE_INT)
			throw std::string("index must be of type int");
	}
	catch(std::string s) {throw s;}
}



void TypeValidator::processReadNode(mayfly::node::expression::ReadNode * const node, int lvl){
	try{
		node->argument()->accept(this, lvl);
		if(node->argument()->type()->name() != ExpressionType::TYPE_INT && ExpressionType::TYPE_DOUBLE)
			throw std::string("int or number expression expected in 'read'");
	}
	catch(std::string s) {throw s;}
}

void TypeValidator::processWhileNode(mayfly::node::WhileNode * const node, int lvl){
	try{
		node->condition()->accept(this, lvl);
		if(node->condition()->type()->name() != ExpressionType::TYPE_BOOLEAN)
			throw std::string("boolean expression expected in 'while' cycle test");
	}
	catch(std::string s) {throw s;}
}

void TypeValidator::processAssignmentNode(mayfly::node::expression::AssignmentNode * const node, int lvl){
try {
    node->lvalue()->accept(this, lvl+4);
    node->rvalue()->accept(this, lvl+4);
    if (node->lvalue()->type()->name() != node->rvalue()->type()->name())
      throw std::string("wrong types in assignment");
    }
  catch (std::string s) { throw s; }
}
	
void TypeValidator::processIfNode(mayfly::node::IfNode * const node, int lvl){
	try{
		node->condition()->accept(this, lvl);
		if(node->condition()->type()->name() != ExpressionType::TYPE_BOOLEAN)
			throw std::string("boolean expression expected in 'if' statement");
	}
	catch(std::string s) {throw s;}
}	
void TypeValidator::processIfElseNode(mayfly::node::IfElseNode * const node, int lvl){
	try{
		node->condition()->accept(this, lvl);
		if(node->condition()->type()->name() != ExpressionType::TYPE_BOOLEAN)
			throw std::string("boolean expression expected in 'if' statement");
	}
	catch(std::string s) {throw s;}
}
void TypeValidator::processForNode(mayfly::node::ForNode * const node, int lvl){
	try{
		node->variable()->accept(this, lvl);
		node->startcondition()->accept(this, lvl);
		node->stopcondition()->accept(this, lvl);
		if(node->variable()->type()->name() !=(node->startcondition()->type()->name() != node->stopcondition()->type()->name()))
			throw std::string("start or stop condition types do not match with variable type");
		if(node->step()){
			node->step()->accept(this, lvl);
			if(node->variable()->type()->name() != node->step()->type()->name())
				throw std::string("step expression type does not match with variable type");
		}
	}
	catch(std::string s) {throw s;}
}

void TypeValidator::processFunCallNode(mayfly::node::expression::FunCallNode * const node, int lvl){
	if(node->arguments()){
		try{
			node->arguments()->accept(this, lvl);
		}
		catch(std::string s) {throw s;}
	}
	MFSymbol *s = _symtab.find(*node->name());
	node->type(s->type());
}

void TypeValidator::processContinueNode(mayfly::node::ContinueNode * const node, int lvl){}

void TypeValidator::processBreakNode(mayfly::node::BreakNode * const node, int lvl){}

void TypeValidator::processVarNode(mayfly::node::VarNode * const node, int lvl){
	try{
		const std::string *id = node->varname();
		MFSymbol *s = _symtab.find(*id);
		if(!_symtab.findLocal(*id, s))
			_symtab.insert(*id, new MFSymbol(node->type(), *id, 0, _global));
		if(node->init()){
			node->init()->accept(this, lvl);
			if(node->type()->name() != node->init()->type()->name())
				throw std::string("Wrong type for initializer");
		}
	}
	catch(std::string s) {throw s;}
}
			
void TypeValidator::processBlockNode(mayfly::node::BlockNode * const node, int lvl){
	if(node->declarations())
		node->declarations()->accept(this, lvl);
	if(node->statements())
		node->statements()->accept(this, lvl);
}

void TypeValidator::processMemoryReference(mayfly::node::expression::MemoryReference * const node, int lvl){}
void TypeValidator::processPrintNode(mayfly::node::PrintNode * const node, int lvl){
	node->argument()->accept(this, lvl);
}
void TypeValidator::processFunctionDeclareNode(mayfly::node::FunctionDeclareNode * const node, int lvl){
	//const std::string *id = node->name();
	//std::cout << *id << node->type()->name();
	//_symtab.insert(*id, new MFSymbol(node->type(), *id, 0, _global));
}

void TypeValidator::processFuncDefNode(mayfly::node::FuncDefNode * const node, int lvl){
	
}

void TypeValidator::processPrintLnNode(mayfly::node::PrintLnNode * const node, int lvl){
	node->argument()->accept(this, lvl);
}
void TypeValidator::processReturnNode(mayfly::node::ReturnNode * const node, int lvl){}
