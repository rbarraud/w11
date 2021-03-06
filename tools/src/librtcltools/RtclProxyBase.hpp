// $Id: RtclProxyBase.hpp 1186 2019-07-12 17:49:59Z mueller $
// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright 2011-2013 by Walter F.J. Mueller <W.F.J.Mueller@gsi.de>
// 
// Revision History: 
// Date         Rev Version  Comment
// 2013-02-09   485   1.4.2  add CommandName()
// 2013-02-05   483   1.4.1  ClassCmdConfig: use RtclArgs
// 2013-02-02   480   1.4    factor out RtclCmdBase base class
// 2013-02-01   479   1.3    add DispatchCmd(), support $unknown method
// 2011-07-31   401   1.2    add ctor(type,interp,name) for direct usage
// 2011-04-23   380   1.1    use boost/function instead of RmethDsc
//                           use boost::noncopyable (instead of private dcl's)
// 2011-02-20   363   1.0    Initial version
// 2011-02-11   360   0.1    First draft
// ---------------------------------------------------------------------------

/*!
  \brief   Declaration of class RtclProxyBase.
*/

#ifndef included_Retro_RtclProxyBase
#define included_Retro_RtclProxyBase 1

#include "tcl.h"

#include <string>
#include <map>

#include "RtclCmdBase.hpp"

#include "RtclArgs.hpp"

namespace Retro {

  class RtclProxyBase : public RtclCmdBase {
    public:

      explicit      RtclProxyBase(const std::string& type = std::string());
                    RtclProxyBase(const std::string& type, Tcl_Interp* interp,
                                  const char* name);
      virtual      ~RtclProxyBase();

      virtual int   ClassCmdConfig(RtclArgs& args);

      const std::string& Type() const;
      Tcl_Command        Token() const;
      std::string   CommandName() const;

    protected:
      void          SetType(const std::string& type);

      void          CreateObjectCmd(Tcl_Interp* interp, const char* name);

      int           TclObjectCmd(Tcl_Interp* interp, int objc, 
                                 Tcl_Obj* const objv[]);

      static int    ThunkTclObjectCmd(ClientData cdata, Tcl_Interp* interp, 
                                      int objc, Tcl_Obj* const objv[]);
      static void   ThunkTclCmdDeleteProc(ClientData cdata);
      static void   ThunkTclExitProc(ClientData cdata);
    
    protected:
      std::string   fType;                  //!< proxied type name
      Tcl_Interp*   fInterp;                //!< tcl interpreter
      Tcl_Command   fCmdToken;              //!< cmd token for object command
  };
  
} // end namespace Retro

#include "RtclProxyBase.ipp"

#endif
