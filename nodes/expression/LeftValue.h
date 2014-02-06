// $Id: LeftValue.h,v 1.1 2013-02-16 16:10:14 ist13500 Exp $
#ifndef __MF_NODE_EXPRESSION_LEFTVALUE_H__
#define __MF_NODE_EXPRESSION_LEFTVALUE_H__

#include <cdk/nodes/expressions/Simple.h>
#include <string>
#include "SemanticProcessor.h"

namespace mayfly {
  namespace node {
    namespace expression {

      /**
       * Class for describing syntactic tree leaves for holding lvalues.
       */
      class LeftValue: public cdk::node::expression::Simple<std::string> {
      public:
        inline LeftValue(int lineno, const char *s) :
          cdk::node::expression::Simple<std::string>(lineno, s) {
        }
        inline LeftValue(int lineno, const std::string &s) :
          cdk::node::expression::Simple<std::string>(lineno, s) {
        }
        inline LeftValue(int lineno, const std::string *s) :
          cdk::node::expression::Simple<std::string>(lineno, *s) {
        }

        /**
         * @return the name of the node's class
         */
        const char *name() const {
          return "LeftValue";
        }

        /**
         * @param sp semantic processor visitor
         * @param level syntactic tree level
         */
        virtual void accept(SemanticProcessor *sp, int level) {
          sp->processLeftValue(this, level);
        }

      };

    } // expression
  } // node
} // mayfly

#endif

// $Log: LeftValue.h,v $
// Revision 1.1  2013-02-16 16:10:14  ist13500
// This is a base mayfly version.
// This is just Compact with the names changed.
//
// Revision 1.3  2013/02/09 18:57:47  david
// New Mayfly version (this one is to be built against CDK8).
// Major code simplification. Starting transition to C++11.
//
// Revision 1.2  2011/03/09 19:56:17  david
// *** empty log message ***
//
// Revision 1.1  2011/03/07 02:27:05  david
// Added simple left value for read and assignment operations.
//
