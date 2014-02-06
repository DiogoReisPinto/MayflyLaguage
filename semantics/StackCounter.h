#ifndef __MF_SEMANTICS_STACKCOUNTER_H__
#define __MF_SEMANTICS_STACKCOUNTER_H__

#include "semantics/SemanticProcessor.h"
#include <semantics/ExpressionType.h>
#include <string>
#include <iostream>
#include <stack>
#include "nodes/all.h"

namespace mayfly{
  namespace semantic{

    class StackCounter: public virtual SemanticProcessor{
      int _stack;
      
    public:
      StackCounter() : _stack(0){}
    
    public:
      inline int stack(){
        return _stack;
      }
     
    public: 
      inline ~StackCounter(){}
      
    public:
      
          void processNode(cdk::node::Node * const node, int lvl) {}
          void processNil(cdk::node::Nil * const node, int lvl) {}
          void processData(cdk::node::Data * const node, int lvl){}
          void processComposite(cdk::node::Composite * const node, int lvl){}
          void processSequence(cdk::node::Sequence * const node, int lvl){
	    for (size_t i = 0; i < node->size(); i++) {
	      cdk::node::Node *n = node->node(i);
	      if (n == NULL) break;
	      n->accept(this, lvl);
	    }
	    
	  }
    
          template<typename T> void processSimple(cdk::node::expression::Simple<T> * const node, int lvl){}
    
          void processInteger(cdk::node::expression::Integer * const node, int lvl){}
          void processDouble(cdk::node::expression::Double * const node, int lvl){}
          void processString(cdk::node::expression::String * const node, int lvl){}
          void processIdentifier(cdk::node::expression::Identifier * const node, int lvl){}
          void processIntAndNumUnaryExpression(cdk::node::expression::UnaryExpression *const node, int lvl){}
          void processIntAndPointerUnaryExpression(cdk::node::expression::UnaryExpression *const node, int lvl){}
          void processAdditiveExpression(cdk::node::expression::BinaryExpression *const node, int lvl){}
          void processIntAndNumExpression(cdk::node::expression::BinaryExpression *const node, int lvl){}
          void processIntAndPointerExpression(cdk::node::expression::BinaryExpression *const node, int lvl){}
          void processScalarLogicalExpression(cdk::node::expression::BinaryExpression *const node, int lvl){}
          void processBooleanLogicalExpression(cdk::node::expression::BinaryExpression *const node, int lvl){}
          void processGeneralLogicalExpression(cdk::node::expression::BinaryExpression *const node, int lvl){}
          void processUnaryExpression(cdk::node::expression::UnaryExpression * const node, int lvl){}
          void processNEG(cdk::node::expression::NEG * const node, int lvl){}
          void processBinaryExpression(cdk::node::expression::BinaryExpression * const node, int lvl){}
          void processADD(cdk::node::expression::ADD * const node, int lvl){}
          void processSUB(cdk::node::expression::SUB * const node, int lvl){}
          void processMUL(cdk::node::expression::MUL * const node, int lvl){}
          void processDIV(cdk::node::expression::DIV * const node, int lvl){}
          void processMOD(cdk::node::expression::MOD * const node, int lvl){}
          void processLT(cdk::node::expression::LT * const node, int lvl){}
          void processLE(cdk::node::expression::LE * const node, int lvl){}
          void processGE(cdk::node::expression::GE * const node, int lvl){}
          void processGT(cdk::node::expression::GT * const node, int lvl){}
          void processNE(cdk::node::expression::NE * const node, int lvl){}
          void processEQ(cdk::node::expression::EQ * const node, int lvl){}
    
          void processLeftValue(mayfly::node::expression::LeftValue * const node, int lvl){}
          void processAnd(mayfly::node::expression::And * const node, int lvl){}
          void processOr(mayfly::node::expression::Or * const node, int lvl){}
          void processNot(mayfly::node::expression::Not * const node, int lvl){}
          void processINC(mayfly::node::expression::INC * const node, int lvl){}
          void processDEC(mayfly::node::expression::DEC * const node, int lvl){}
          void processMemoryIndex(mayfly::node::expression::MemoryIndex * const node, int lvl){}
          void processMemoryAllocate(mayfly::node::expression::MemoryAllocate * const node, int lvl){}
          void processMemoryReference(mayfly::node::expression::MemoryReference * const node, int lvl){}
          void processPrintNode(mayfly::node::PrintNode * const node, int lvl){}
          void processReadNode(mayfly::node::expression::ReadNode * const node, int lvl){}
          void processWhileNode(mayfly::node::WhileNode * const node, int lvl){
	    node->block()->accept(this, lvl);
	  }
          void processAssignmentNode(mayfly::node::expression::AssignmentNode * const node, int lvl){}
          void processIfNode(mayfly::node::IfNode * const node, int lvl){
	    node->block()->accept(this, lvl);
	  }
          void processIfElseNode(mayfly::node::IfElseNode * const node, int lvl){
	    node->thenblock()->accept(this,lvl);
	    node->elseblock()->accept(this, lvl);
	  }
	  void processForNode(mayfly::node::ForNode * const node, int lvl){
	    node->block()->accept(this, lvl);
	  }
          void processFunctionDeclareNode(mayfly::node::FunctionDeclareNode * const node, int lvl){}
	  void processFuncDefNode(mayfly::node::FuncDefNode * const node, int lvl){
	    this->_stack += node->type()->size();
	    node->block()->accept(this, lvl);
	   
		  
	  }
          void processFunCallNode(mayfly::node::expression::FunCallNode * const node, int lvl){}
          void processPrintLnNode(mayfly::node::PrintLnNode * const node, int lvl){}
          void processReturnNode(mayfly::node::ReturnNode * const node, int lvl){}
          void processContinueNode(mayfly::node::ContinueNode * const node, int lvl){}
          void processBreakNode(mayfly::node::BreakNode * const node, int lvl){}
          void processVarNode(mayfly::node::VarNode * const node, int lvl){
	    if(node->type()->name() == ExpressionType::TYPE_INT)
	      this->_stack += 4;
	    if(node->type()->name() == ExpressionType::TYPE_DOUBLE)
	      this->_stack += 8;
	    if(node->type()->name() == ExpressionType::TYPE_POINTER)
	      this->_stack += 4;
	    if(node->type()->name() == ExpressionType::TYPE_STRING)
	      this->_stack += 4;
	  }
          void processBlockNode(mayfly::node::BlockNode * const node, int lvl){
	    if(node->declarations())
		node->declarations()->accept(this ,lvl);
	    if(node->statements())
		node->statements()->accept(this, lvl);
	    
	  }
    };
  }
} 

#endif
