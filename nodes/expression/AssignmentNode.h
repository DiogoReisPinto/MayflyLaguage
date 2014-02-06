// $Id: AssignmentNode.h,v 1.1 2013-05-16 17:23:21 ist169632 Exp $ -*- c++ -*-
#ifndef __MF_ASSIGNMENTNODE_H__
#define __MF_ASSIGNMENTNODE_H__

#include <cdk/nodes/Node.h>
#include <cdk/nodes/expressions/Expression.h>
#include "nodes/expression/LeftValue.h"

namespace mayfly {
  namespace node {
    namespace expression{
    /**
     * Class for describing assignment nodes.
     */
      class AssignmentNode: public cdk::node::expression::Expression {
        mayfly::node::expression::LeftValue *_lvalue;
        cdk::node::expression::Expression *_rvalue;

      public:
        inline AssignmentNode(int lineno, mayfly::node::expression::LeftValue *lvalue, cdk::node::expression::Expression *rvalue) :
            Expression(lineno), _lvalue(lvalue), _rvalue(rvalue) {
        }

      public:
        inline mayfly::node::expression::LeftValue *lvalue() {
          return _lvalue;
        }
        inline cdk::node::expression::Expression *rvalue() {
          return _rvalue;
        }

        const char *name() const {
          return "AssignmentNode";
        }

        void accept(SemanticProcessor *sp, int level) {
          sp->processAssignmentNode(this, level);
        }

      };
    }
  }// namespace node
} // namespace mayfly

#endif

// $Log: AssignmentNode.h,v $
// Revision 1.1  2013-05-16 17:23:21  ist169632
// Assignment nodes changed places
//
// Revision 1.1  2013-02-16 16:10:13  ist13500
// This is a base mayfly version.
// This is just Compact with the names changed.
//
// Revision 1.9  2013/02/09 18:57:46  david
// New Mayfly version (this one is to be built against CDK8).
// Major code simplification. Starting transition to C++11.
//
// Revision 1.8  2012/04/10 19:09:47  david
// Major cleanup (comments).
// Better handling of ProgramNodes (visitors and not evaluators).
//
