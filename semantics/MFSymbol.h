// $Id: MFSymbol.h,v 1.4 2013-05-18 16:16:44 ist169632 Exp $ -*- c++ -*-
#ifndef __MF_SEMANTICS_SYMBOL_H__
#define __MF_SEMANTICS_SYMBOL_H__

#include <string>
#include <semantics/ExpressionType.h>

class MFSymbol {
  ExpressionType * _type;
  std::string _name;
  int _offset;
  bool _global;

public:
  inline MFSymbol(ExpressionType *type, const std::string &name, int offset, bool global) :
    _type(type), _name(name), _offset(offset), _global(global) {
  }

  inline MFSymbol(ExpressionType *type, const char *name, int offset, bool global) :
    _type(type), _name(name), _offset(offset), _global(global) {
  }

  virtual ~MFSymbol() {
  }

	inline bool global(){
		return _global;
	}

  inline ExpressionType *type() const {
    return _type;
  }
  inline const std::string &name() const {
    return _name;
  }
  inline int offset() const {
    return _offset;
  }
  inline int offset(int v) {
    return _offset = v;
  }
};

#endif

// $Log: MFSymbol.h,v $
// Revision 1.4  2013-05-18 16:16:44  ist169632
// Fixed global variables
//
// Revision 1.3  2013-05-14 12:23:36  ist169632
// *** empty log message ***
//
// Revision 1.2  2013-05-13 14:37:54  ist169632
// Entrega intermédia corrigida. TypeValidator corrigido
//
// Revision 1.1  2013-02-16 16:10:14  ist13500
// This is a base mayfly version.
// This is just Compact with the names changed.
//
// Revision 1.3  2013/02/09 18:57:47  david
// New Mayfly version (this one is to be built against CDK8).
// Major code simplification. Starting transition to C++11.
//
// Revision 1.2  2012/04/10 19:09:47  david
// Major cleanup (comments).
// Better handling of ProgramNodes (visitors and not evaluators).
//
// Revision 1.1  2012/02/18 19:37:58  david
// Updated Mayfly to support the new semantic analysis in CDK7.
// Debug options are now integrated with semantic analysis, eliminating a long-lived
// hack in the evaluators. Renamed Symbol to MFSymbol, to emphasize
// that it is language-specific.
//
