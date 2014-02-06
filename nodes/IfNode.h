// $Id: IfNode.h,v 1.2 2013-05-16 15:29:09 ist169632 Exp $ -*- c++ -*-
#ifndef __MF_IFNODE_H__
#define __MF_IFNODE_H__

#include <cdk/nodes/Node.h>
#include <cdk/nodes/expressions/Expression.h>

namespace mayfly {
  namespace node {

    /**
     * Class for describing if-then nodes.
     */
    class IfNode: public cdk::node::Node {
      cdk::node::expression::Expression *_condition;
      cdk::node::Node *_block;
      int _stack;

    public:
      inline IfNode(int lineno, cdk::node::expression::Expression *condition, cdk::node::Node *block) :
          cdk::node::Node(lineno), _condition(condition), _block(block) {
      }

    public:
      inline cdk::node::expression::Expression *condition() {
        return _condition;
      }
      inline cdk::node::Node *block() {
        return _block;
      }

      inline int stack(){
 	return _stack;
      }
      
      inline int stack(int v){
	_stack += v;
	return _stack;
      }

      const char *name() const {
        return "IfNode";
      }

      void accept(SemanticProcessor *sp, int level) {
        sp->processIfNode(this, level);
      }

    };

  } // namespace node
} // namespace mayfly

#endif

// $Log: IfNode.h,v $
// Revision 1.2  2013-05-16 15:29:09  ist169632
// Hopefully passes more tests
//
// Revision 1.1  2013-02-16 16:10:13  ist13500
// This is a base mayfly version.
// This is just Compact with the names changed.
//
// Revision 1.8  2013/02/09 18:57:46  david
// New Mayfly version (this one is to be built against CDK8).
// Major code simplification. Starting transition to C++11.
//
// Revision 1.7  2012/04/10 19:09:47  david
// Major cleanup (comments).
// Better handling of ProgramNodes (visitors and not evaluators).
//
