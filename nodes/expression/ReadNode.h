// $Id: ReadNode.h,v 1.3 2013-05-16 17:22:21 ist169632 Exp $ -*- c++ -*-
#ifndef __MF_READNODE_H__
#define __MF_READNODE_H__

#include <cdk/nodes/Node.h>
#include <cdk/nodes/expressions/Expression.h>

namespace mayfly {
  namespace node {
    namespace expression{

    /**
     * Class for describing read nodes.
     */
    class ReadNode: public cdk::node::expression::Expression {
      mayfly::node::expression::LeftValue *_argument;

    public:
      inline ReadNode(int lineno, mayfly::node::expression::LeftValue *argument) :
          Expression(lineno), _argument(argument) {
      }

    public:
      inline mayfly::node::expression::LeftValue *argument() {
        return _argument;
      }

      const char *name() const {
        return "ReadNode";
      }

      void accept(SemanticProcessor *sp, int level) {
        sp->processReadNode(this, level);
      }

    };
   }
  }// namespace node
} // namespace mayfly

#endif

// $Log: ReadNode.h,v $
// Revision 1.3  2013-05-16 17:22:21  ist169632
// Read works yay
//
// Revision 1.2  2013-05-15 15:12:53  ist169632
// *** empty log message ***
//
// Revision 1.1  2013-02-16 16:10:14  ist13500
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
