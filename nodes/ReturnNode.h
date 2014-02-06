#ifndef __RETURNNODE_H__
#define __RETURNNODE_H__

#include <cdk/nodes/Node.h>
#include <cdk/nodes/expressions/Expression.h>

namespace mayfly {
	namespace node {
		
		/**
		* Class for describing print nodes.
		*/
		class ReturnNode: public cdk::node::Node {

			public:
				inline ReturnNode(int lineno) :
				cdk::node::Node(lineno) {
				}
				
			public:
				
				
				const char *name() const {
					return "ReturnNode";
				}
				
				void accept(SemanticProcessor *sp, int level) {
					sp->processReturnNode(this, level);
				}
				
		};
		
	} // namespace node
} // namespace mayfly

#endif
