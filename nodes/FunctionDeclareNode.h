#ifndef __MF_FUNCTIONDECLARENODE_H__
#define __MF_FUNCTIONDECLARENODE_H__

#include <string>
#include <cdk/nodes/Node.h>
#include <cdk/nodes/expressions/Expression.h>
#include <cdk/nodes/Sequence.h>
#include <cdk/semantics/ExpressionType.h>

namespace mayfly {
  namespace node {

    /**
     * Class for describing for nodes.
     */
    class FunctionDeclareNode: public cdk::node::Node {
			bool _publicfunc;
			ExpressionType *_type;
			std::string *_name;
			cdk::node::Sequence *_arguments;

    public:
      inline FunctionDeclareNode(int lineno, bool publicfunc, ExpressionType *type, std::string *name, cdk::node::Sequence *arguments) :
          cdk::node::Node(lineno), _publicfunc(publicfunc), _type(type), _name(name), _arguments(arguments) {
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

      const char *name() const {
        return "FunctionDeclareNode";
      }

      void accept(SemanticProcessor *sp, int level) {
        sp->processFunctionDeclareNode(this, level);
      }

    };

  } // namespace node
} // namespace mayfly

#endif 
 
 
