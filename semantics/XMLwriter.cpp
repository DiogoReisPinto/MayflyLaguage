// $Id: XMLwriter.cpp,v 1.12 2013-05-13 14:37:54 ist169632 Exp $ -*- c++ -*-
#include <string>
#include "semantics/XMLwriter.h"
#include "nodes/all.h"  // automatically generated

// just to get a shorter name
//namespace cpt = mayfly;
//
////---------------------------------------------------------------------------
//
//void cpt::semantics::XMLwriter::processData(cdk::node::Data * const node, int lvl) {
//  os() << std::string(lvl, ' ') << "<data size='" << node->size() << "'>";
//  for (size_t i = 0; i < node->size(); i++)
//    os() << ((unsigned char*)node->data())[i];
//  closeTag(node, lvl);
//}
//
//void cpt::semantics::XMLwriter::processComposite(cdk::node::Composite * const node, int lvl) {
//  os() << std::string(lvl, ' ') << "<composite size='" << node->size() << "'>" << std::endl;
//  for (size_t i = 0; i < node->size(); i++)
//    node->at(i)->accept(this, lvl + 2);
//  closeTag(node, lvl);
//}
//
////---------------------------------------------------------------------------
//
//void cpt::semantics::XMLwriter::processSequence(cdk::node::Sequence * const node, int lvl) {
//  os() << std::string(lvl, ' ') << "<sequence size='" << node->size() << "'>" << std::endl;
//  for (size_t i = 0; i < node->size(); i++)
//    node->node(i)->accept(this, lvl + 2);
//  closeTag(node, lvl);
//}
//
////---------------------------------------------------------------------------
//
//void cpt::semantics::XMLwriter::processInteger(cdk::node::expression::Integer * const node, int lvl) {
//  processSimple(node, lvl);
//}
//
//void cpt::semantics::XMLwriter::processDouble(cdk::node::expression::Double * const node, int lvl) {
//  processSimple(node, lvl);
//}
//
//void cpt::semantics::XMLwriter::processString(cdk::node::expression::String * const node, int lvl) {
//  processSimple(node, lvl);
//}
//
////---------------------------------------------------------------------------
//
//void cpt::semantics::XMLwriter::processIdentifier(cdk::node::expression::Identifier * const node, int lvl) {
//  processSimple(node, lvl);
//}
//
////---------------------------------------------------------------------------
//
//inline void cpt::semantics::XMLwriter::processUnaryExpression(cdk::node::expression::UnaryExpression * const node, int lvl) {
//  openTag(node, lvl);
//  node->argument()->accept(this, lvl + 2);
//  closeTag(node, lvl);
//}
//
//void cpt::semantics::XMLwriter::processNEG(cdk::node::expression::NEG * const node, int lvl) {
//  processUnaryExpression(node, lvl);
//}
//
////---------------------------------------------------------------------------
//
//inline void cpt::semantics::XMLwriter::processBinaryExpression(cdk::node::expression::BinaryExpression * const node, int lvl) {
//  openTag(node, lvl);
//  node->left()->accept(this, lvl + 2);
//  node->right()->accept(this, lvl + 2);
//  closeTag(node, lvl);
//}
//
//void cpt::semantics::XMLwriter::processADD(cdk::node::expression::ADD * const node, int lvl) {
//  processBinaryExpression(node, lvl);
//}
//void cpt::semantics::XMLwriter::processSUB(cdk::node::expression::SUB * const node, int lvl) {
//  processBinaryExpression(node, lvl);
//}
//void cpt::semantics::XMLwriter::processMUL(cdk::node::expression::MUL * const node, int lvl) {
//  processBinaryExpression(node, lvl);
//}
//void cpt::semantics::XMLwriter::processDIV(cdk::node::expression::DIV * const node, int lvl) {
//  processBinaryExpression(node, lvl);
//}
//void cpt::semantics::XMLwriter::processMOD(cdk::node::expression::MOD * const node, int lvl) {
//  processBinaryExpression(node, lvl);
//}
//void cpt::semantics::XMLwriter::processLT(cdk::node::expression::LT * const node, int lvl) {
//  processBinaryExpression(node, lvl);
//}
//void cpt::semantics::XMLwriter::processLE(cdk::node::expression::LE * const node, int lvl) {
//  processBinaryExpression(node, lvl);
//}
//void cpt::semantics::XMLwriter::processGE(cdk::node::expression::GE * const node, int lvl) {
//  processBinaryExpression(node, lvl);
//}
//void cpt::semantics::XMLwriter::processGT(cdk::node::expression::GT * const node, int lvl) {
//  processBinaryExpression(node, lvl);
//}
//void cpt::semantics::XMLwriter::processNE(cdk::node::expression::NE * const node, int lvl) {
//  processBinaryExpression(node, lvl);
//}
//void cpt::semantics::XMLwriter::processEQ(cdk::node::expression::EQ * const node, int lvl) {
//  processBinaryExpression(node, lvl);
//}
//
////---------------------------------------------------------------------------
//
//void cpt::semantics::XMLwriter::processLeftValue(cpt::node::expression::LeftValue * const node, int lvl) {
//  processSimple(node, lvl);
//}
//
//
//
//void cpt::semantics::XMLwriter::processINC(cpt::node::expression::INC * const node, int lvl) {
//  processUnaryExpression(node,lvl);
//}
//
//void cpt::semantics::XMLwriter::processDEC(cpt::node::expression::DEC * const node, int lvl) {
//  processUnaryExpression(node,lvl);
//}
//
//void cpt::semantics::XMLwriter::processMemoryIndex(cpt::node::expression::MemoryIndex * const node, int lvl) {
//  processUnaryExpression(node,lvl);
//}
//
//void cpt::semantics::XMLwriter::processMemoryAllocate(cpt::node::expression::MemoryAllocate * const node, int lvl) {
//  processUnaryExpression(node,lvl);
//}
//
//void cpt::semantics::XMLwriter::processMemoryReference(cpt::node::expression::MemoryReference * const node, int lvl) {
//  processUnaryExpression(node,lvl);
//}
//
//void cpt::semantics::XMLwriter::processAnd(cpt::node::expression::And * const node, int lvl) {
//    processBinaryExpression(node,lvl);
//}
//void cpt::semantics::XMLwriter::processOr(cpt::node::expression::Or * const node, int lvl) {
//    processBinaryExpression(node, lvl);
//}
//void cpt::semantics::XMLwriter::processNot(cpt::node::expression::Not * const node, int lvl) {
//    processUnaryExpression(node,lvl);
//}
//
////---------------------------------------------------------------------------
//
//
//
////---------------------------------------------------------------------------
//
//void cpt::semantics::XMLwriter::processPrintNode(cpt::node::PrintNode * const node, int lvl) {
//  openTag(node, lvl);
//  node->argument()->accept(this, lvl + 2);
//  closeTag(node, lvl);
//}
//
////---------------------------------------------------------------------------
//
//void cpt::semantics::XMLwriter::processReadNode(cpt::node::expression::ReadNode * const node, int lvl) {
//  openTag(node, lvl);
//  node->argument()->accept(this, lvl + 2);
//  closeTag(node, lvl);
//}
//
//void cpt::semantics::XMLwriter::processAssignmentNode(cpt::node::AssignmentNode * const node, int lvl) {
//  openTag(node, lvl);
//  node->lvalue()->accept(this, lvl + 2);
//  openTag("rvalue", lvl + 2);
//  node->rvalue()->accept(this, lvl + 4);
//  closeTag("rvalue", lvl + 2);
//  closeTag(node, lvl);
//}
//
////---------------------------------------------------------------------------
//
//void cpt::semantics::XMLwriter::processWhileNode(cpt::node::WhileNode * const node, int lvl) {
//  openTag(node, lvl);
//  openTag("condition", lvl + 2);
//  node->condition()->accept(this, lvl + 4);
//  closeTag("condition", lvl + 2);
//  openTag("block", lvl + 2);
//  node->block()->accept(this, lvl + 4);
//  closeTag("block", lvl + 2);
//  closeTag(node, lvl);
//}
//
////---------------------------------------------------------------------------
//
//void cpt::semantics::XMLwriter::processIfNode(cpt::node::IfNode * const node, int lvl) {
//  openTag(node, lvl);
//  openTag("condition", lvl + 2);
//  node->condition()->accept(this, lvl + 4);
//  closeTag("condition", lvl + 2);
//  openTag("then", lvl + 2);
//  node->block()->accept(this, lvl + 4);
//  closeTag("then", lvl + 2);
//  closeTag(node, lvl);
//}
//
//void cpt::semantics::XMLwriter::processIfElseNode(cpt::node::IfElseNode * const node, int lvl) {
//  openTag(node, lvl);
//  openTag("condition", lvl + 2);
//  node->condition()->accept(this, lvl + 4);
//  closeTag("condition", lvl + 2);
//  openTag("then", lvl + 2);
//  node->thenblock()->accept(this, lvl + 4);
//  closeTag("then", lvl + 2);
//  openTag("else", lvl + 2);
//  node->elseblock()->accept(this, lvl + 4);
//  closeTag("else", lvl + 2);
//  closeTag(node, lvl);
//}
//
//void cpt::semantics::XMLwriter::processForNode(cpt::node::ForNode * const node, int lvl) {
//    openTag(node,lvl);
//    openTag("variable", lvl+2);
//    node->variable()->accept(this, lvl + 4);
//    closeTag("variable", lvl + 2);
//    openTag("start condition", lvl+2);
//    node->startcondition()->accept(this, lvl + 4);
//    closeTag("start condition", lvl + 2);
//    openTag("stop condition", lvl+2);
//    node->stopcondition()->accept(this, lvl + 4);
//    closeTag("stop condition", lvl + 2);
//    openTag("For block", lvl+2);
//    node->block()->accept(this, lvl + 4);
//    closeTag("For block", lvl + 2);
//    closeTag(node,lvl);
//}
//
//
//void cpt::semantics::XMLwriter::processFunctionDeclareNode(cpt::node::FunctionDeclareNode * const node, int lvl) {
//    openTag(node,lvl);
//    if(node->publicfunc())
//      os() << std::string(lvl+2, ' ') << "Public ";
////    switch(node->type()){
////      case 0:
////	os() << std::string(lvl+2, ' ') << "Void";
////	break;
////      case 1:
////	os() << std::string(lvl+2, ' ') << "int";
////	break;
////      case 2:
////	os() << std::string(lvl+2, ' ') << "number";
////	break;
////      case 3:
////	os() << std::string(lvl+2, ' ') << "string";
////	break;
////      case 4:
////	os() << std::string(lvl+2, ' ') << "int*";
////	break;
////      case 5:
////	os() << std::string(lvl+2, ' ') << "number*";
////	break;
////      case 6:
////	os() << std::string(lvl+2, ' ') << "string*";
////	break;
////    }
//    openTag("Function Name", lvl+2);
//    node->name()->accept(this,lvl+4);
//    closeTag("Function Name", lvl+2);
//    if(node->arguments() != NULL){
//      openTag("Function arguments", lvl+2);
//      node->arguments()->accept(this,lvl+4);
//      closeTag("Function arguments", lvl+2);
//    }
//    closeTag(node,lvl);
//}
//
//void cpt::semantics::XMLwriter::processFuncDefNode(cpt::node::FuncDefNode * const node, int lvl) {
//    openTag(node,lvl);
//    if(node->publicfunc())
//      os() << std::string(lvl+2, ' ') << "Public ";
////    switch(node->type()){
////      case 0:
////	os() << std::string(lvl+2, ' ') << "Void";
////	break;
////      case 1:
////	os() << std::string(lvl+2, ' ') << "int";
////	break;
////      case 2:
////	os() << std::string(lvl+2, ' ') << "number";
////	break;
////      case 3:
////	os() << std::string(lvl+2, ' ') << "string";
////	break;
////      case 4:
////	os() << std::string(lvl+2, ' ') << "int*";
////	break;
////      case 5:
////	os() << std::string(lvl+2, ' ') << "number*";
////	break;
////      case 6:
////	os() << std::string(lvl+2, ' ') << "string*";
////	break;
////    }
//    openTag("Function Name", lvl+2);
//    node->name()->accept(this,lvl+4);
//    closeTag("Function Name", lvl+2);
//    if(node->arguments() != NULL){
//      openTag("Function arguments", lvl+2);
//      node->arguments()->accept(this,lvl+4);
//      closeTag("Function arguments", lvl+2);
//    }
//    if(node->funcreturn() != NULL){
//      openTag("Function return", lvl+2);
//      node->funcreturn()->accept(this,lvl+4);
//      closeTag("Function return", lvl+2);
//    }
//    if(node->block() != NULL){
//      openTag("Function block", lvl+2);
//      node->block()->accept(this,lvl+4);
//      closeTag("Function block", lvl+2);
//    }
//    closeTag(node,lvl);
//}
//void cpt::semantics::XMLwriter::processFunCallNode(cpt::node::expression::FunCallNode * const node, int lvl) {
//    openTag(node,lvl);
//    openTag("Function Name", lvl+2);
//    node->name()->accept(this,lvl+4);
//    closeTag("Function Name", lvl+2);
//    if(node->arguments() != NULL){
//      openTag("Function arguments", lvl+2);
//      node->arguments()->accept(this,lvl+4);
//      closeTag("Function arguments", lvl+2);
//    }
//    closeTag(node,lvl);
//}
//
//void cpt::semantics::XMLwriter::processContinueNode(cpt::node::ContinueNode * const node, int lvl) {
//    openTag(node, lvl);
//    node->argument()->accept(this, lvl + 2);
//    closeTag(node, lvl);
//}
//
//void cpt::semantics::XMLwriter::processBreakNode(cpt::node::BreakNode * const node, int lvl) {
//    openTag(node, lvl);
//    node->argument()->accept(this, lvl + 2);
//    closeTag(node, lvl);
//}
//void cpt::semantics::XMLwriter::processReturnNode(cpt::node::ReturnNode * const node, int lvl) {
//    openTag(node,lvl);
//      os() << std::string(lvl+2, ' ') << "Return";
//  closeTag(node,lvl);
//}
//void cpt::semantics::XMLwriter::processPrintLnNode(cpt::node::PrintLnNode * const node, int lvl) {
//    openTag(node, lvl);
//    node->argument()->accept(this, lvl + 2);
//    closeTag(node, lvl);
//}
//
//void cpt::semantics::XMLwriter::processVarNode(cpt::node::VarNode * const node, int lvl) {
//  openTag(node,lvl);
//  if(node->publicvar())
//      os() << std::string(lvl+2, ' ') << "Public";
//  if(node->constant())
//      os() << std::string(lvl+2, ' ') << "Constant";
//  node->varname()->accept(this, lvl + 2);
//  closeTag(node,lvl);
//}
//
//void cpt::semantics::XMLwriter::processBlockNode(cpt::node::BlockNode * const node, int lvl) {
//  openTag(node, lvl);
//  if(node->declarations() != NULL){
//    openTag("Declarations", lvl + 2);
//    node->declarations()->accept(this, lvl + 4);
//    closeTag("Declarations", lvl + 2);
//  }
//  if(node->statements() != NULL){
//    openTag("Statements", lvl + 2);
//    node->statements()->accept(this, lvl + 4);
//    closeTag("Statements", lvl + 2);
//  }
//  closeTag(node, lvl);
//}
//---------------------------------------------------------------------------
//     T H E    E N D
//---------------------------------------------------------------------------
// $Log: XMLwriter.cpp,v $
// Revision 1.12  2013-05-13 14:37:54  ist169632
// Entrega intermédia corrigida. TypeValidator corrigido
//
// Revision 1.11  2013-04-29 16:46:08  ist169632
// Read and funCall are now expressions. MFParser changed accordingly.
//
// Revision 1.10  2013-04-29 14:52:06  ist169632
// ExpressionTypes added. Changed varNode to include initialization
//
// Revision 1.9  2013-04-18 17:29:30  ist169905
// *** empty log message ***
//
// Revision 1.8  2013-04-18 15:28:05  ist169632
// Added BlockNode.
// Included type in function and vars.
// Fixed some bugs
//
// Revision 1.7  2013-04-18 02:33:56  ist169905
// fixed var node
//
// Revision 1.6  2013-04-17 12:02:53  ist169905
// *** empty log message ***
//
// Revision 1.5  2013-04-16 23:14:37  ist169905
// CORRECTION TO XMLWriter
//
// Revision 1.4  2013-04-02 01:34:36  ist169632
// Added missing nodes from E0
//
// Revision 1.3  2013-03-31 22:40:30  ist169905
// XMLWriter updated
//
// Revision 1.2  2013-03-24 20:19:32  ist169632
// fixed bugs
//
// Revision 1.1  2013-02-16 16:10:14  ist13500
// This is a base mayfly version.
// This is just Compact with the names changed.
//
// Revision 1.10  2013/02/10 19:20:04  david
// Code cleanup and simplification. C++11 is now mandatory.
//
// Revision 1.9  2013/02/09 18:57:47  david
// New Mayfly version (this one is to be built against CDK8).
// Major code simplification. Starting transition to C++11.
//
// Revision 1.8  2012/04/10 19:09:47  david
// Major cleanup (comments).
// Better handling of ProgramNodes (visitors and not evaluators).
//
