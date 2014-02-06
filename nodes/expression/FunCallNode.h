#ifndef __MF_FUNCALLNODE_H__
#define __MF_FUNCALLNODE_H__

#include <string>
#include <cdk/nodes/Node.h>
#include <cdk/nodes/expressions/Expression.h>
#include <cdk/nodes/expressions/Identifier.h>

namespace mayfly {
  namespace node {
    namespace expression{
    /**
     * Class for describing for nodes.
     */
    class FunCallNode: public cdk::node::expression::Expression {
			std::string *_name;
			cdk::node::Sequence *_arguments;

    public:
      inline FunCallNode(int lineno, std::string *name, cdk::node::Sequence *arguments) :
          Expression(lineno), _name(name), _arguments(arguments) {
      }

    public:
      inline std::string *name() {
        return _name;
      }
      inline cdk::node::Sequence *arguments() {
        return _arguments;
      }

      const char *name() const {
        return "FunCallNode";
      }

      void accept(SemanticProcessor *sp, int level) {
        sp->processFunCallNode(this, level);
      }

    };
   }
  } // namespace node
} // namespace mayfly

#endif 
 
 
 
