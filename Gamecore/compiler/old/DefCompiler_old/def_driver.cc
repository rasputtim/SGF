// $Id: driver.cc 39 2008-08-03 10:07:15Z tb $
/** \file driver.cc Implementation of the example::Driver class. */

#include <fstream>
#include <sstream>

#include "def_driver.h"
#include "Defcompiler/scanner.h"
#include "Defcompiler/scanner.h"
#include "mugen/ast/astmanager.h"
#include "util/SGF_Debug.h"


namespace DefCompiler {


	Driver::Driver(class SGF::Ast::CAstManager* _Ast)
    : trace_scanning(false),
      trace_parsing(false),
      Ast(_Ast),
	  nodes(NULL),
	  cvalues(new SGF::Ast::CStack (string("cvalues")))
	{

	}

bool Driver::parse_stream(std::istream& in, const string& sname)
{
    streamname = sname;

	CScanner scanner(&in);
    scanner.set_debug(trace_scanning);
    this->lexer = &scanner;

	Parser parser(*this);
	parser.set_debug_level(trace_parsing);
    return (parser.parse() == 0);
}

bool Driver::parse_file(const string &filename)
{
    ifstream in(filename.c_str());
	if (!in.good()) {
		SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Driver::parse_file "<< " Error opening file: "<< filename << endl;
		return false;
	}
    return parse_stream(in, filename);
}

bool Driver::parse_string(const string &input, const string& sname)
{
    std::istringstream iss(input);
    return parse_stream(iss, sname);
}

void Driver::error(const class location& l, const string& m)
{
	SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Driver::error:" << l << " : " << m << endl;
	//std::cerr << "Driver::error:" << l << ": " << m << endl;
}

void Driver::error(const string& m)
{
	SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Driver::error: "<< m << endl;
	//std::cerr << "Driver::error: "<< m << endl;
}
void Driver::clear_stack ()

{
  while (!cvalues->empty ()) {
    //delete driver.cvalues->top ();
    delete cvalues->pop ();
  }
}
} // namespace example
