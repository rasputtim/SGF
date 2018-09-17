// $Id: driver.cc 39 2008-08-03 10:07:15Z tb $
/** \file driver.cc Implementation of the example::Driver class. */

#include <fstream>
#include <sstream>

#include "driver.h"
#include "AirCompilerOld/scanner.h"
#include "AirCompilerOld/scanner.h"
#include "../airmanager.h"
#include "../util/debug.h"

namespace AirCompilerOld {
	/*
	Driver::Driver(class CalcContext& _calc)
    : trace_scanning(false),
      trace_parsing(false),
      calc(_calc),
	  Air(NULL)
	{
	}
	*/
	Driver::Driver(class CAirManager* _Air)
    : trace_scanning(false),
      trace_parsing(false),
      Air(_Air)
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
		Debug::debug(601) << "Driver::parse_file "<< " Error opening file: "<< filename << std::endl;
		return false;
	}
    return parse_stream(in, filename);
}

bool Driver::parse_string(const std::string &input, const std::string& sname)
{
    std::istringstream iss(input);
    return parse_stream(iss, sname);
}

void Driver::error(const class location& l,
		   const std::string& m)
{
	Debug::debug(1,__FUNCTION__) << "Driver::error:" << l << " : " << m << std::endl;
	std::cerr << "Driver::error:" << l << ": " << m << std::endl;
}

void Driver::error(const std::string& m)
{
	Debug::debug(1,__FUNCTION__) << "Driver::error: "<< m << std::endl;
	std::cerr << m << std::endl;
}
	
} // namespace example
