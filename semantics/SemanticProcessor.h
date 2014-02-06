// $Id: SemanticProcessor.h,v 1.11 2013-05-16 17:22:21 ist169632 Exp $ -*- c++ -*-
#ifndef __MF_SEMANTICS_SEMANTICPROCESSOR_H__
#define __MF_SEMANTICS_SEMANTICPROCESSOR_H__

#include <string>
#include <iostream>

/* include node forward declarations */
#define __NODE_DECLARATIONS_ONLY__
#include "nodes/all.h"  // automatically generated
#undef __NODE_DECLARATIONS_ONLY__

//!
//! Print nodes as XML elements to the output stream.
//!
class SemanticProcessor {
  //! The output stream
  std::ostream &_os;

	protected:
		//! Debug flag
		bool _debug;

	protected:
		SemanticProcessor(std::ostream &o = std::cout, bool debug = false) :
				_os(o), _debug(debug) {
		}
		inline std::ostream &os() {
			return _os;
		}

	public:
		virtual ~SemanticProcessor() {
		}

	public:
		// CDK nodes (general)
		virtual void processNil(cdk::node::Nil * const node, int lvl) = 0;
		virtual void processData(cdk::node::Data * const node, int lvl) = 0;
		virtual void processComposite(cdk::node::Composite * const node, int lvl) = 0;
		virtual void processSequence(cdk::node::Sequence * const node, int lvl) = 0;

	public:
		virtual void processInteger(cdk::node::expression::Integer * const node, int lvl) = 0;
		virtual void processDouble(cdk::node::expression::Double * const node, int lvl) = 0;
		virtual void processString(cdk::node::expression::String * const node, int lvl) = 0;
		virtual void processIdentifier(cdk::node::expression::Identifier * const node, int lvl) = 0;

	public:
		virtual void processNEG(cdk::node::expression::NEG * const node, int lvl) = 0;

	public:
		virtual void processADD(cdk::node::expression::ADD * const node, int lvl) = 0;
		virtual void processSUB(cdk::node::expression::SUB * const node, int lvl) = 0;
		virtual void processMUL(cdk::node::expression::MUL * const node, int lvl) = 0;
		virtual void processDIV(cdk::node::expression::DIV * const node, int lvl) = 0;
		virtual void processMOD(cdk::node::expression::MOD * const node, int lvl) = 0;
		virtual void processLT(cdk::node::expression::LT * const node, int lvl) = 0;
		virtual void processLE(cdk::node::expression::LE * const node, int lvl) = 0;
		virtual void processGE(cdk::node::expression::GE * const node, int lvl) = 0;
		virtual void processGT(cdk::node::expression::GT * const node, int lvl) = 0;
		virtual void processNE(cdk::node::expression::NE * const node, int lvl) = 0;
		virtual void processEQ(cdk::node::expression::EQ * const node, int lvl) = 0;

	public:
      		virtual void processLeftValue(mayfly::node::expression::LeftValue * const node, int lvl) = 0;
		virtual	void processAnd(mayfly::node::expression::And * const node, int lvl) = 0;
		virtual	void processOr(mayfly::node::expression::Or * const node, int lvl) = 0;
		virtual	void processNot(mayfly::node::expression::Not * const node, int lvl) = 0;
		virtual	void processINC(mayfly::node::expression::INC * const node, int lvl) = 0;
		virtual	void processDEC(mayfly::node::expression::DEC * const node, int lvl) = 0;
		virtual	void processMemoryIndex(mayfly::node::expression::MemoryIndex * const node, int lvl) = 0;
		virtual	void processMemoryAllocate(mayfly::node::expression::MemoryAllocate * const node, int lvl) = 0;
		virtual	void processMemoryReference(mayfly::node::expression::MemoryReference * const node, int lvl) = 0;
		
	public:
		virtual	void processPrintNode(mayfly::node::PrintNode * const node, int lvl) = 0;
		virtual	void processReadNode(mayfly::node::expression::ReadNode * const node, int lvl) = 0;
		virtual	void processWhileNode(mayfly::node::WhileNode * const node, int lvl) = 0;
		virtual	void processAssignmentNode(mayfly::node::expression::AssignmentNode * const node, int lvl) = 0;
		virtual	void processIfNode(mayfly::node::IfNode * const node, int lvl) = 0;
		virtual	void processIfElseNode(mayfly::node::IfElseNode * const node, int lvl) = 0;
		virtual	void processForNode(mayfly::node::ForNode * const node, int lvl) = 0;
		virtual	void processFunctionDeclareNode(mayfly::node::FunctionDeclareNode * const node, int lvl) = 0;
		virtual	void processFuncDefNode(mayfly::node::FuncDefNode * const node, int lvl) = 0;
		virtual	void processFunCallNode(mayfly::node::expression::FunCallNode * const node, int lvl) = 0;
		virtual	void processPrintLnNode(mayfly::node::PrintLnNode * const node, int lvl) = 0;
		virtual	void processReturnNode(mayfly::node::ReturnNode * const node, int lvl) = 0;
		virtual	void processContinueNode(mayfly::node::ContinueNode * const node, int lvl) = 0;
		virtual	void processBreakNode(mayfly::node::BreakNode * const node, int lvl) = 0;
		virtual	void processVarNode(mayfly::node::VarNode * const node, int lvl) = 0;
		virtual void processBlockNode(mayfly::node::BlockNode * const node, int lvl) = 0;
	};

#endif

// $Log: SemanticProcessor.h,v $
// Revision 1.11  2013-05-16 17:22:21  ist169632
// Read works yay
//
// Revision 1.10  2013-04-29 16:46:08  ist169632
// Read and funCall are now expressions. MFParser changed accordingly.
//
// Revision 1.9  2013-04-18 17:29:30  ist169905
// *** empty log message ***
//
// Revision 1.8  2013-04-18 15:28:05  ist169632
// Added BlockNode.
// Included type in function and vars.
// Fixed some bugs
//
// Revision 1.7  2013-04-02 01:34:36  ist169632
// Added missing nodes from E0
//
// Revision 1.6  2013-03-23 20:38:52  ist169632
// *** empty log message ***
//
// Revision 1.5  2013-03-20 18:06:00  ist169632
// changing stuff
//
// Revision 1.4  2013-03-20 17:57:05  ist169632
// updated writers and processor
//
// Revision 1.3  2013-03-20 14:59:00  ist169632
// update writers and processor
//
// Revision 1.1  2013-02-16 16:10:14  ist13500
// This is a base mayfly version.
// This is just Compact with the names changed.
//
// Revision 1.12  2013/02/10 19:20:04  david
// Code cleanup and simplification. C++11 is now mandatory.
//
// Revision 1.11  2013/02/09 18:57:47  david
// New Mayfly version (this one is to be built against CDK8).
// Major code simplification. Starting transition to C++11.
//
// Revision 1.10  2012/04/10 19:09:47  david
// Major cleanup (comments).
// Better handling of ProgramNodes (visitors and not evaluators).
//
// Revision 1.9  2012/02/18 19:37:58  david
// Updated Mayfly to support the new semantic analysis in CDK7.
// Debug options are now integrated with semantic analysis, eliminating a long-lived
// hack in the evaluators. Renamed Symbol to MFSymbol, to emphasize
// that it is language-specific.
//
