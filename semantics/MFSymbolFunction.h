
#ifndef __MF_SEMANTICS_SYMBOL_FUNCTION_H__
#define __MF_SEMANTICS_SYMBOL_FUNCTION_H__

#include <string>
#include <semantics/MFSymbol.h>
#include <cdk/nodes/Sequence.h>
#include <semantics/ExpressionType.h>

//class MFSymbolFunction : public MFSymbol{ 
//  ExpressionType *_type;
//  std::string _name;
//  int _value;
//  cdk::node::Sequence* _args;
//  bool _declared;
//
//public:
//  inline MFSymbolFunction(ExpressionType *type, const std::string &name, int value, cdk::node::Sequence* args, bool declared) :
//    MFSymbol(type,name,value), _args(args), _declared(declared) {
//  }
//
//  inline MFSymbolFunction(ExpressionType *type, const char *name, int value, cdk::node::Sequence* args, bool declared) :
//     MFSymbol(type, name, value), _args(args), _declared(declared) {
//  }
//
//  virtual ~MFSymbolFunction() {
//  }
//
//  inline ExpressionType *type() const {
//    return _type;
//  }
//  inline const std::string &name() const {
//    return _name;
//  }
//  inline int value() const {
//    return _value;
//  }
//  inline int value(int v) {
//    return _value = v;
//  }
//  
//  inline bool declared() {
//    return _declared;
//  }
//  
//  inline cdk::node::Sequence* args() {
//    return _args;
//  }
//   
//  
//};

#endif

