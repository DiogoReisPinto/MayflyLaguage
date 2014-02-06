 
#ifndef __MEMORYALLOCATE_H__
#define __MEMORYALLOCATE_H__

#include <cdk/nodes/expressions/UnaryExpression.h>


namespace mayfly {
	namespace node {
		namespace expression {
			
			/**
			* Class for describing the negation operator
			*/
			class MemoryAllocate: public cdk::node::expression::UnaryExpression {
				public:
					inline MemoryAllocate(int lineno, Expression *arg) :
					UnaryExpression(lineno, arg) {
					}
					
					/**
					* @return the name of the node's class
					*/
					const char *name() const {
						return "MemoryAllocate";
					}
					
					/**
					* @param sp semantic processor visitor
					* @param level syntactic tree level
					*/
					virtual void accept(SemanticProcessor *sp, int level) {
						sp->processMemoryAllocate(this, level);
					}
					
			};
			
		} // expression
	} // node
} // mayfly

#endif
