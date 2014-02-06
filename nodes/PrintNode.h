// $Id: PrintNode.h,v 1.1 2013-02-16 16:10:13 ist13500 Exp $ -*- c++ -*-
#ifndef __MF_PRINTNODE_H__
#define __MF_PRINTNODE_H__

#include <cdk/nodes/Node.h>
#include <cdk/nodes/expressions/Expression.h>

namespace mayfly {
  namespace node {

    /**
     * Class for describing print nodes.
     */
    class PrintNode: public cdk::node::Node {
      cdk::node::expression::Expression *_argument;

    public:
      inline PrintNode(int lineno, cdk::node::expression::Expression *argument) :
          cdk::node::Node(lineno), _argument(argument) {
      }

    public:
      inline cdk::node::expression::Expression *argument() {
        return _argument;
      }

      const char *name() const {
        return "PrintNode";
      }

      void accept(SemanticProcessor *sp, int level) {
        sp->processPrintNode(this, level);
      }

    };

  } // namespace node
} // namespace mayfly

#endif

// $Log: PrintNode.h,v $
// Revision 1.1  2013-02-16 16:10:13  ist13500
// This is a base mayfly version.
// This is just Compact with the names changed.
//
// Revision 1.7  2013/02/09 18:57:46  david
// New Mayfly version (this one is to be built against CDK8).
// Major code simplification. Starting transition to C++11.
//
// Revision 1.6  2012/04/10 19:09:47  david
// Major cleanup (comments).
// Better handling of ProgramNodes (visitors and not evaluators).
//
