#ifndef __OR_H__
#define __OR_H__

#include <cdk/nodes/expressions/BinaryExpression.h>


namespace mayfly {
	namespace node {
		namespace expression {
			
			/**
			* Class for describing the sum ('+') operator
			*/
			class Or: public cdk::node::expression::BinaryExpression {
				public:
					/**
					* @param lineno source code line number for this nodes
					* @param left first operand
					* @param right second operand
					*/
					inline Or(int lineno, Expression *left, Expression *right) :
					BinaryExpression(lineno, left, right) {
					}
					
					/**
					* @return the name of the node's class
					*/
					const char *name() const {
						return "Or";
					}
					
					/**
					* @param sp semantic processor visitor
					* @param level syntactic tree level
					*/
					virtual void accept(SemanticProcessor *sp, int level) {
						sp->processOr(this, level);
					}
					
			};
			
		} // expression
	} // node
} // mayfly

#endif
