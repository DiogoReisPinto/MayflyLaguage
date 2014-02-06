#ifndef __MF_BLOCKNODE_H__
#define __MF_BLOCKNODE_H__

#include <cdk/nodes/Node.h>
#include <cdk/nodes/Sequence.h>

namespace mayfly{
	namespace node{
	
		class BlockNode: public cdk::node::Node{
			cdk::node::Sequence *_declarations;
			cdk::node::Sequence *_statements;

		public:
			inline BlockNode(int lineno, cdk::node::Sequence *declarations, cdk::node::Sequence *statements): 
				cdk::node::Node(lineno), _declarations(declarations), _statements(statements) {}

		public:
			inline cdk::node::Sequence *declarations(){
				return _declarations;
			}

			inline cdk::node::Sequence *statements(){
				return _statements;
			}

			const char *name() const{
				return "BlockNode";
			}

			void accept(SemanticProcessor *sp, int lvl){
				sp->processBlockNode(this, lvl);
			}

		};
	}
}

#endif
