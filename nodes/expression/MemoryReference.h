 
#ifndef __MEMORYREFERENCE_H__
#define __MEMORYREFERENCE_H__

#include <cdk/nodes/expressions/Expression.h>


namespace mayfly {
	namespace node {
		namespace expression {
			
			/**
			* Class for describing the negation operator
			*/
			class MemoryReference: public cdk::node::expression::Expression {
				cdk::node::expression::Expression *_arg;

				public:
					inline MemoryReference(int lineno, Expression *arg) :
					Expression(lineno), _arg(arg) {
					}
					
					inline cdk::node::expression::Expression *arg(){
						return _arg;
					}

					/**
					* @return the name of the node's class
					*/
					const char *name() const {
						return "MemoryReference";
					}
					
					/**
					* @param sp semantic processor visitor
					* @param level syntactic tree level
					*/
					virtual void accept(SemanticProcessor *sp, int level) {
						sp->processMemoryReference(this, level);
					}
					
			};
			
		} // expression
	} // node
} // mayfly

#endif
