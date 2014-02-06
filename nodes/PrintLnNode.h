#ifndef __MF_PRINTLNNODE_H__
#define __MF_PRINTLNNODE_H__

#include <cdk/nodes/Node.h>
#include <cdk/nodes/expressions/Expression.h>

namespace mayfly {
  namespace node {

    /**
     * Class for describing println nodes.
     */
    class PrintLnNode: public cdk::node::Node {
      cdk::node::expression::Expression *_argument;

    public:
      inline PrintLnNode(int lineno, cdk::node::expression::Expression *argument) :
          cdk::node::Node(lineno), _argument(argument) {
      }

    public:
      inline cdk::node::expression::Expression *argument() {
        return _argument;
      }

      const char *name() const {
        return "PrintLnNode";
      }

      void accept(SemanticProcessor *sp, int level) {
        sp->processPrintLnNode(this, level);
      }

    };

  } // namespace node
} // namespace mayfly

#endif 
