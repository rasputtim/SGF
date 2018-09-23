// $Id: driver.cc 39 2008-08-03 10:07:15Z tb $
/** \file driver.cc Implementation of the example::Driver class. */

#include <fstream>
#include <sstream>

#include "def_driver.h"
#include "DefCompiler/defScanner.h"
#include "mugen/ast/astManager.h"
#include "util/SGF_Debug.h"

namespace DefCompiler {


	Driver::Driver(SGF::Ast::CAstManager* _Ast)
    : trace_scanning(false),
      trace_parsing(false),
      Ast(_Ast),
	  nodes(NULL),
	  cvalues(new SGF::Ast::CStack (std::string("cvalues")))
	{

	}

bool Driver::parse_stream(std::istream& in, const std::string& sname)
{
    streamname = sname;

	CScanner scanner(&in);
    scanner.set_debug(trace_scanning);
    this->lexer = &scanner;

	Parser parser(*this);
	parser.set_debug_level(trace_parsing);
    return (parser.parse() == 0);
}

bool Driver::parse_file(const std::string &filename)
{
    std::ifstream in(filename.c_str());
	if (!in.good()) {
		SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Driver::parse_file "<< " Error opening file: "<< filename << std::endl;
		return false;
	}
    return parse_stream(in, filename);
}

bool Driver::parse_string(const std::string &input, const std::string& sname)
{
    std::istringstream iss(input);
    return parse_stream(iss, sname);
}

void Driver::error(const class location& l, const std::string& m)
{
	SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Driver::error:" << l << " : " << m << std::endl;
	//std::cerr << "Driver::error:" << l << ": " << m << std::endl;
}

void Driver::error(const std::string& m)
{
	SGF::Debug::debug(SGF::Debug::compilers,__FUNCTION__) << "Driver::error: "<< m << std::endl;
	//std::cerr << "Driver::error: "<< m << std::endl;
}
void Driver::clear_stack ()

{
  while (!cvalues->empty ()) {
    //delete driver.cvalues->top ();
    delete cvalues->pop ();
  }
}
} // namespace example
