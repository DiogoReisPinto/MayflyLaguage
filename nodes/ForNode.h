#ifndef __MF_FORNODE_H__
#define __MF_FORNODE_H__

#include <cdk/nodes/Node.h>
#include <cdk/nodes/expressions/Expression.h>
#include <cdk/nodes/Sequence.h>
#include "nodes/expression/LeftValue.h"

namespace mayfly {
  namespace node {

    /**
     * Class for describing for nodes.
     */
    class ForNode: public cdk::node::Node {
      mayfly::node::expression::LeftValue *_variable;
      cdk::node::expression::Expression *_startcondition;
      bool _upto;
      cdk::node::expression::Expression *_stopcondition;
      cdk::node::expression::Expression *_step;
      cdk::node::Node *_block;
      int _stack;

    public:
      inline ForNode(int lineno, mayfly::node::expression::LeftValue *variable, cdk::node::expression::Expression *startcondition, bool upto, cdk::node::expression::Expression *stopcondition, cdk::node::expression::Expression *step, cdk::node::Node *block) :
          cdk::node::Node(lineno), _variable(variable),  _startcondition(startcondition), _upto(upto), _stopcondition(stopcondition), _step(step), _block(block) {
      }

    public:
      inline cdk::node::expression::Expression *startcondition() {
        return _startcondition;
      }
      inline cdk::node::expression::Expression *step() {
        return _step;
      } 
      inline cdk::node::expression::Expression *stopcondition() {
        return _stopcondition;
      }
      inline cdk::node::Node *block() {
        return _block;
      }
      inline mayfly::node::expression::LeftValue *variable() {
        return _variable;
      }
      inline bool upto(){
	return _upto;
      }

      inline int stack(){
    	return _stack;
      }

      inline int stack(int v){
	_stack += v;
	return _stack;
      }

      const char *name() const {
        return "ForNode";
      }

      void accept(SemanticProcessor *sp, int level) {
        sp->processForNode(this, level);
      }

    };

  } // namespace node
} // namespace mayfly

#endif 
