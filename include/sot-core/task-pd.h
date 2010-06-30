/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright Projet JRL-Japan, 2007
 *+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *
 * File:      task-pd.h
 * Project:   SOT
 * Author:    Nicolas Mansard
 *
 * Version control
 * ===============
 *
 *  $Id$
 *
 * Description
 * ============
 *
 *
 * ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/



#ifndef __SOT_TASK_PD_H__
#define __SOT_TASK_PD_H__

/* --------------------------------------------------------------------- */
/* --- INCLUDE --------------------------------------------------------- */
/* --------------------------------------------------------------------- */


/* SOT */
#include <sot-core/task.h>

/* --------------------------------------------------------------------- */
/* --- API ------------------------------------------------------------- */
/* --------------------------------------------------------------------- */

#if defined (WIN32)
#  if defined (task_pd_EXPORTS)
#    define SOTTASKPD_EXPORT __declspec(dllexport)
#  else
#    define SOTTASKPD_EXPORT __declspec(dllimport)
#  endif
#else
#  define SOTTASKPD_EXPORT
#endif

/* --------------------------------------------------------------------- */
/* --- CLASS ----------------------------------------------------------- */
/* --------------------------------------------------------------------- */

namespace sot {
namespace dg = dynamicgraph;

class SOTTASKPD_EXPORT TaskPD
: public Task
{
 public:
  static const std::string CLASS_NAME;
  virtual const std::string& getClassName( void ) const { return CLASS_NAME; }

  ml::Vector previousError;
  double beta;

 public:
  TaskPD( const std::string& n );


  /* --- COMPUTATION --- */
  ml::Vector& computeErrorDot( ml::Vector& error,int time );
  VectorMultiBound& computeTaskModif( VectorMultiBound& error,int time );


  /* --- SIGNALS ------------------------------------------------------------ */
 public:
  dg::SignalTimeDependent< ml::Vector,int > errorDotSOUT;
  dg::SignalPtr< ml::Vector,int > errorDotSIN;

  /* --- PARAMS --- */
  virtual void commandLine( const std::string& cmdLine
			    ,std::istringstream& cmdArgs
			    ,std::ostream& os );


};

} // namespace sot



#endif /* #ifndef __SOT_TASK_PD_H__ */

