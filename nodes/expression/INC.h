 
#ifndef __INC_H__
#define __INC_H__

#include <cdk/nodes/expressions/UnaryExpression.h>


namespace mayfly {
	namespace node {
		namespace expression {
			
			/**
			* Class for describing the negation operator
			*/
			class INC: public cdk::node::expression::UnaryExpression {
				public:
					inline INC(int lineno, Expression *arg) :
					UnaryExpression(lineno, arg) {
					}
					
					/**
					* @return the name of the node's class
					*/
					const char *name() const {
						return "INC";
					}
					
					/**
					* @param sp semantic processor visitor
					* @param level syntactic tree level
					*/
					virtual void accept(SemanticProcessor *sp, int level) {
						sp->processINC(this, level);
					}
					
			};
			
		} // expression
	} // node
} // mayfly

#endif
