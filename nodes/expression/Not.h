#ifndef __NOT_H__
#define __NOT_H__

#include <cdk/nodes/expressions/UnaryExpression.h>


namespace mayfly {
	namespace node {
		namespace expression {
			
			/**
			* Class for describing the negation operator
			*/
			class Not: public cdk::node::expression::UnaryExpression {
				public:
					inline Not(int lineno, Expression *arg) :
					UnaryExpression(lineno, arg) {
					}
					
					/**
					* @return the name of the node's class
					*/
					const char *name() const {
						return "Not";
					}
					
					/**
					* @param sp semantic processor visitor
					* @param level syntactic tree level
					*/
					virtual void accept(SemanticProcessor *sp, int level) {
						sp->processNot(this, level);
					}
					
			};
			
		} // expression
	} // node
} // mayfly

#endif
