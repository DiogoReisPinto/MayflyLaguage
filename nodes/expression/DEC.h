 
#ifndef __DEC_H__
#define __DEC_H__

#include <cdk/nodes/expressions/UnaryExpression.h>


namespace mayfly {
	namespace node {
		namespace expression {
			
			/**
			* Class for describing the negation operator
			*/
			class DEC: public cdk::node::expression::UnaryExpression {
				public:
					inline DEC(int lineno, Expression *arg) :
					UnaryExpression(lineno, arg) {
					}
					
					/**
					* @return the name of the node's class
					*/
					const char *name() const {
						return "DEC";
					}
					
					/**
					* @param sp semantic processor visitor
					* @param level syntactic tree level
					*/
					virtual void accept(SemanticProcessor *sp, int level) {
						sp->processDEC(this, level);
					}
					
			};
			
		} // expression
	} // node
} // mayfly

#endif
