#ifndef __MF_FUNCDEFNODE_H__
#define __MF_FUNCDEFNODE_H__

#include <string>
#include <cdk/nodes/Node.h>
#include <cdk/nodes/expressions/Expression.h>
#include <cdk/nodes/expressions/Identifier.h>
#include <cdk/nodes/Sequence.h>
#include <cdk/semantics/ExpressionType.h>

namespace mayfly {
  namespace node {

    /**
     * Class for describing for nodes.
     */
    class FuncDefNode: public cdk::node::Node {
			bool _publicfunc;
			ExpressionType *_type;
			std::string* _name;
			cdk::node::Sequence *_arguments;
			cdk::node::expression::Expression *_funcreturn;
			cdk::node::Node *_block;
			int _stack;

    public:
      inline FuncDefNode(int lineno, bool publicfunc, ExpressionType *type, std::string *name, cdk::node::Sequence *arguments, cdk::node::expression::Expression *funcreturn, cdk::node::Node *block) :
          cdk::node::Node(lineno), _publicfunc(publicfunc), _type(type), _name(name), _arguments(arguments), _funcreturn(funcreturn), _block(block) {
      }

    public:
	inline bool publicfunc() {
		return _publicfunc;
	}
	
	inline ExpressionType *type(){
		return _type;
	}

      inline std::string *name() {
        return _name;
      }
      inline cdk::node::Sequence *arguments() {
        return _arguments;
      }
      inline cdk::node::expression::Expression *funcreturn() {
        return _funcreturn;
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
        return "FuncDefNode";
      }

      void accept(SemanticProcessor *sp, int level) {
        sp->processFuncDefNode(this, level);
      }

    };

  } // namespace node
} // namespace mayfly

#endif 
 
