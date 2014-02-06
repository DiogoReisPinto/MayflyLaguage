// $Id: PFwriter.h,v 1.10 2013-05-16 17:22:21 ist169632 Exp $ -*- c++ -*-
#ifndef __MF_SEMANTICS_PFWRITER_H__
#define __MF_SEMANTICS_PFWRITER_H__

#include <string>
#include <iostream>
#include <cdk/semantics/SymbolTable.h>
#include <cdk/generators/Postfix.h>
#include "semantics/SemanticProcessor.h"
#include "semantics/MFSymbol.h"

namespace mayfly {
  namespace semantics {

    //!
    //! Traverse syntax tree and generate the corresponding assembly code.
    //!
    class PFwriter: public virtual SemanticProcessor {
      cdk::semantics::SymbolTable<MFSymbol> &_symtab;
      cdk::generator::Postfix &_pf;
      int _lbl;

    public:
      PFwriter(std::ostream &os, bool debug, cdk::semantics::SymbolTable<MFSymbol> &symtab, cdk::generator::Postfix &pf) :
          SemanticProcessor(os, debug), _symtab(symtab), _pf(pf), _lbl(0) {
      }

    public:
      ~PFwriter() {
        os().flush();
      }

    private:
      /** Method used to generate sequential labels. */
      inline std::string mklbl(int lbl) {
        std::ostringstream oss;
        if (lbl < 0)
          oss << ".L" << -lbl;
        else
          oss << "_L" << lbl;
        return oss.str();
      }

    public:
      void processNil(cdk::node::Nil * const node, int lvl) {
      }
      void processData(cdk::node::Data * const node, int lvl) {
      }
      void processComposite(cdk::node::Composite * const node, int lvl) {
      }
      void processSequence(cdk::node::Sequence * const node, int lvl);

    public:
      void processInteger(cdk::node::expression::Integer * const node, int lvl);
      void processDouble(cdk::node::expression::Double * const node, int lvl);
      void processString(cdk::node::expression::String * const node, int lvl);
      void processIdentifier(cdk::node::expression::Identifier * const node, int lvl);

    public:
      void processNEG(cdk::node::expression::NEG * const node, int lvl);

    public:
      void processADD(cdk::node::expression::ADD * const node, int lvl);
      void processSUB(cdk::node::expression::SUB * const node, int lvl);
      void processMUL(cdk::node::expression::MUL * const node, int lvl);
      void processDIV(cdk::node::expression::DIV * const node, int lvl);
      void processMOD(cdk::node::expression::MOD * const node, int lvl);
      void processLT(cdk::node::expression::LT * const node, int lvl);
      void processLE(cdk::node::expression::LE * const node, int lvl);
      void processGE(cdk::node::expression::GE * const node, int lvl);
      void processGT(cdk::node::expression::GT * const node, int lvl);
      void processNE(cdk::node::expression::NE * const node, int lvl);
      void processEQ(cdk::node::expression::EQ * const node, int lvl);

    public:
      void processLeftValue(mayfly::node::expression::LeftValue * const node, int lvl);
			void processAnd(mayfly::node::expression::And * const node, int lvl);
			void processOr(mayfly::node::expression::Or * const node, int lvl);
			void processNot(mayfly::node::expression::Not * const node, int lvl);
			void processINC(mayfly::node::expression::INC * const node, int lvl);
			void processDEC(mayfly::node::expression::DEC * const node, int lvl);
			void processMemoryIndex(mayfly::node::expression::MemoryIndex * const node, int lvl);
			void processMemoryAllocate(mayfly::node::expression::MemoryAllocate * const node, int lvl);
			void processMemoryReference(mayfly::node::expression::MemoryReference * const node, int lvl);
		
		public:
			void processPrintNode(mayfly::node::PrintNode * const node, int lvl);
			void processReadNode(mayfly::node::expression::ReadNode * const node, int lvl);
			void processWhileNode(mayfly::node::WhileNode * const node, int lvl);
			void processAssignmentNode(mayfly::node::expression::AssignmentNode * const node, int lvl);
			void processIfNode(mayfly::node::IfNode * const node, int lvl);
			void processIfElseNode(mayfly::node::IfElseNode * const node, int lvl);
			void processForNode(mayfly::node::ForNode * const node, int lvl);
			void processFunctionDeclareNode(mayfly::node::FunctionDeclareNode * const node, int lvl);
			void processFuncDefNode(mayfly::node::FuncDefNode * const node, int lvl);
			void processFunCallNode(mayfly::node::expression::FunCallNode * const node, int lvl);
			void processPrintLnNode(mayfly::node::PrintLnNode * const node, int lvl);
			void processReturnNode(mayfly::node::ReturnNode * const node, int lvl);
			void processContinueNode(mayfly::node::ContinueNode * const node, int lvl);
			void processBreakNode(mayfly::node::BreakNode * const node, int lvl);
			void processVarNode(mayfly::node::VarNode * const node, int lvl);
			void processBlockNode(mayfly::node::BlockNode * const node, int lvl);

    };

  }    // namespace semantics
} // namespace mayfly

#endif

// $Log: PFwriter.h,v $
// Revision 1.10  2013-05-16 17:22:21  ist169632
// Read works yay
//
// Revision 1.9  2013-04-29 16:46:08  ist169632
// Read and funCall are now expressions. MFParser changed accordingly.
//
// Revision 1.8  2013-04-18 17:29:30  ist169905
// *** empty log message ***
//
// Revision 1.7  2013-04-18 15:28:05  ist169632
// Added BlockNode.
// Included type in function and vars.
// Fixed some bugs
//
// Revision 1.6  2013-04-02 01:34:36  ist169632
// Added missing nodes from E0
//
// Revision 1.5  2013-03-24 20:19:32  ist169632
// fixed bugs
//
// Revision 1.4  2013-03-20 18:06:00  ist169632
// changing stuff
//
// Revision 1.3  2013-03-20 17:57:05  ist169632
// updated writers and processor
//
// Revision 1.2  2013-03-20 14:59:00  ist169632
// update writers and processor
//
// Revision 1.1  2013-02-16 16:10:14  ist13500
// This is a base mayfly version.
// This is just Compact with the names changed.
//
// Revision 1.14  2013/02/10 19:20:04  david
// Code cleanup and simplification. C++11 is now mandatory.
//
// Revision 1.13  2013/02/09 18:57:47  david
// New Mayfly version (this one is to be built against CDK8).
// Major code simplification. Starting transition to C++11.
//
// Revision 1.12  2012/04/10 19:09:47  david
// Major cleanup (comments).
// Better handling of ProgramNodes (visitors and not evaluators).
//
// Revision 1.11  2012/02/18 19:37:58  david
// Updated Mayfly to support the new semantic analysis in CDK7.
// Debug options are now integrated with semantic analysis, eliminating a long-lived
// hack in the evaluators. Renamed Symbol to MFSymbol, to emphasize
// that it is language-specific.
//
