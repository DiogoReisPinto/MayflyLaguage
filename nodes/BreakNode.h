#ifndef __BREAKNODE_H__
#define __BREAKNODE_H__

#include <cdk/nodes/Node.h>
#include <cdk/nodes/expressions/Expression.h>

namespace mayfly {
	namespace node {
		
		/**
		* Class for describing print nodes.
		*/
		class BreakNode: public cdk::node::Node {
			int _argument;
			
			public:
				inline BreakNode(int lineno, int argument) :
				cdk::node::Node(lineno), _argument(argument) {
				}
				
			public:
				inline int argument() {
					return _argument;
				}
				
				const char *name() const {
					return "BreakNode";
				}
				
				void accept(SemanticProcessor *sp, int level) {
					sp->processBreakNode(this, level);
				}
				
		};
		
	} // namespace node
} // namespace mayfly

#endif
