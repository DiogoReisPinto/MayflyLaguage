#ifndef __VARNODE_H__
#define __VARNODE_H__

#include <string>

#include <cdk/nodes/Node.h>
#include <cdk/nodes/expressions/Expression.h>
#include <cdk/semantics/ExpressionType.h>
#include "nodes/expression/LeftValue.h"

namespace mayfly {
	namespace node {
		
		/**
		* Class for describing print nodes.
		*/
		class VarNode: public cdk::node::Node {
			bool _publicvar;
			bool _constant;
			ExpressionType *_type;
			std::string *_varname;
			cdk::node::expression::Expression *_init;
			int _stack;
			
			public:
				inline VarNode(int lineno, bool publicvar, bool constant, ExpressionType *type, std::string *varname, cdk::node::expression::Expression *init) :
				cdk::node::Node(lineno), _publicvar(publicvar), _constant(constant), _type(type), _varname(varname), _init(init) {
				}
				
			public:
				inline bool publicvar() {
				  return _publicvar;
				}
				
				inline bool constant() {
				  return _constant;
				}

				inline ExpressionType *type(){
				  return _type;
				}
			  
				inline std::string *varname() {
					return _varname;
				}

				inline cdk::node::expression::Expression *init(){
					return _init;
				}
				
				const char *name() const {
					return "VarNode";
				}
				
				void accept(SemanticProcessor *sp, int level) {
					sp->processVarNode(this, level);
				}
				
		};
		
	} // namespace node
} // namespace mayfly

#endif 
