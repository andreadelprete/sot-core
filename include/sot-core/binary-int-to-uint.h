/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright Projet JRL-Japan, 2007
 *+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *
 * File:      BinaryIntToUint.h
 * Project:   SOT
 * Author:    Paul Evrard
 *
 * Version control
 * ===============
 *
 *  $Id$
 *
 * Description
 * ============
 *
 * Zero out the control signal when collision is detected between
 * two bodies of the controlled robot.
 *
 * !!! WARNING !!! THIS CODE IS CURRENTLY SPECIFIC TO HRP2
 *
 * ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


#ifndef __SOT_BINARY_INT_TO_UINT_HH__
#define __SOT_BINARY_INT_TO_UINT_HH__

/* --------------------------------------------------------------------- */
/* --- INCLUDE --------------------------------------------------------- */
/* --------------------------------------------------------------------- */

/* SOT */
#include <dynamic-graph/entity.h>
#include <sot-core/exception-task.h>
#include <dynamic-graph/all-signals.h>

/* --------------------------------------------------------------------- */
/* --- API ------------------------------------------------------------- */
/* --------------------------------------------------------------------- */

#if defined (WIN32) 
#  if defined (binary_int_to_uint_EXPORTS)
#    define SOTBINARYINTTOUINT_EXPORT __declspec(dllexport)
#  else  
#    define SOTBINARYINTTOUINT_EXPORT __declspec(dllimport)
#  endif 
#else
#  define SOTBINARYINTTOUINT_EXPORT
#endif

namespace sot {
namespace dg = dynamicgraph;

class BinaryIntToUint
  : public dg::Entity
{
public:
  static const std::string CLASS_NAME;
  virtual const std::string& getClassName( void ) const { return CLASS_NAME; }

  /* --- SIGNALS ------------------------------------------------------------ */
public:

  dg::SignalPtr< int,int > binaryIntSIN;
  dg::SignalTimeDependent< unsigned,int > binaryUintSOUT;

public:
  BinaryIntToUint( const std::string& name );
  virtual ~BinaryIntToUint() {}

  virtual unsigned& computeOutput( unsigned& res,int time );

  virtual void display( std::ostream& os ) const;
  void commandLine( const std::string& cmdLine,
		    std::istringstream& cmdArgs,
		    std::ostream& os );
};


} // namespace sot


#endif