 
#ifndef __MEMORYINDEX_H__
#define __MEMORYINDEX_H__

#include <cdk/nodes/expressions/UnaryExpression.h>
#include <cdk/nodes/expressions/Expression.h>

namespace mayfly {
	namespace node {
		namespace expression {
			
			
			
			class MemoryIndex: public cdk::node::expression::Expression {
				cdk::node::expression::Expression *_arg;
				cdk::node::expression::Expression *_index;

				public:
					inline MemoryIndex(int lineno, cdk::node::expression::Expression *arg, cdk::node::expression::Expression *index) :
					Expression(lineno), _arg(arg), _index(index) {
					}
					
					cdk::node::expression::Expression *arg(){
						return _arg;
					}

					cdk::node::expression::Expression *index(){
						return _index;
					}
					/**
					* @return the name of the node's class
					*/
					const char *name() const {
						return "MemoryIndex";
					}
					
					/**
					* @param sp semantic processor visitor
					* @param level syntactic tree level
					*/
					virtual void accept(SemanticProcessor *sp, int level) {
						sp->processMemoryIndex(this, level);
					}
					
			};
			
		} // expression
	} // node
} // mayfly

#endif
