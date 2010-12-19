/*
 * Copyright 2010,
 * François Bleibel,
 * Olivier Stasse,
 *
 * CNRS/AIST
 *
 * This file is part of sot-core.
 * sot-core is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 * sot-core is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.  You should
 * have received a copy of the GNU Lesser General Public License along
 * with sot-core.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <dynamic-graph/interpreter.h>
#include <sot-core/debug.h>
#include <sot-core/factory.h>
#include <sot-core/additional-functions.h>
#include <sot-core/signal-cast.h>
#include <dynamic-graph/signal.h>
#include <sot-core/flags.h>
using namespace std;
using namespace sot;
using namespace dynamicgraph;

/* \brief Constructor. At creation, overloads (deregisters-then registers
 * again) the 'new' function in the g_shell
 */
AdditionalFunctions::AdditionalFunctions() {
}

AdditionalFunctions::~AdditionalFunctions() {
}

void AdditionalFunctions::
cmdFlagSet( const std::string& cmdLine, istringstream& cmdArg, std::ostream& os )
{
  if( cmdLine == "help" )
    {
      os << "  - set <obj1.sig1(flag type)> {#&|}START:END"
	 << "\t\tSet or reset the flag value." <<endl;
      return;
    }

  try {
    Signal<Flags,int> &sig1
      = dynamic_cast< Signal<Flags,int>& >( g_pool.getSignal(cmdArg) );

    dgDEBUG(25) << "set..."<<endl;
    Flags fl; try { fl = sig1.accessCopy(); } catch(...) {}
    cmdArg >> std::ws >> fl;
    dgDEBUG(15) << "Fl=" << fl <<std::endl;
    sig1 = fl;

  } catch( ExceptionAbstract & err ) { throw;  }
  catch( ... ) {
    DG_THROW ExceptionFactory( ExceptionFactory::SYNTAX_ERROR,
				   "setflag: sig should be of flag type. ",
				   "(while calling setflag).");
  }

}

namespace {
	AdditionalFunctions functions;
	ShellFunctionRegisterer regFun18
   ( "setflag",boost::bind(AdditionalFunctions::cmdFlagSet,_1,_2,_3) );
}