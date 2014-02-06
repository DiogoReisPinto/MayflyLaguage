#ifndef __CONTINUENODE_H__
#define __CONTINUENODE_H__

#include <cdk/nodes/Node.h>
#include <cdk/nodes/expressions/Expression.h>

namespace mayfly {
	namespace node {
		
		/**
		* Class for describing print nodes.
		*/
		class ContinueNode: public cdk::node::Node {
			int _argument;
			
			public:
				inline ContinueNode(int lineno, int argument) :
				cdk::node::Node(lineno), _argument(argument) {
				}
				
			public:
				inline int argument() {
					return _argument;
				}
				
				const char *name() const {
					return "ContinueNode";
				}
				
				void accept(SemanticProcessor *sp, int level) {
					sp->processContinueNode(this, level);
				}
				
		};
		
	} // namespace node
} // namespace mayfly

#endif
