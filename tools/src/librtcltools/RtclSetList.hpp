// $Id: RtclSetList.hpp 1186 2019-07-12 17:49:59Z mueller $
// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright 2013-2018 by Walter F.J. Mueller <W.F.J.Mueller@gsi.de>
// 
// Revision History: 
// Date         Rev Version  Comment
// 2018-12-16  1084   1.2.3  use =delete for noncopyable instead of boost
// 2018-12-15  1083   1.2.2  Add(): use rval ref and move semantics
// 2018-12-14  1081   1.2.1  use std::function instead of boost
// 2018-12-01  1076   1.2    use unique_ptr
// 2015-01-08   631   1.1    add Clear()
// 2013-02-12   487   1.0    Initial version
// ---------------------------------------------------------------------------

/*!
  \brief   Declaration of class \c RtclSetList.
*/

#ifndef included_Retro_RtclSetList
#define included_Retro_RtclSetList 1

#include "tcl.h"

#include <cstdint>
#include <string>
#include <map>
#include <memory>
#include <functional>

#include "RtclSet.hpp"
#include "librtcltools/RtclArgs.hpp"

namespace Retro {

  class RtclSetList {
    public:
      typedef std::unique_ptr<RtclSetBase> set_uptr_t;

                    RtclSetList();
      virtual      ~RtclSetList();

                    RtclSetList(const RtclSetList&) = delete;   // noncopyable 
      RtclSetList&  operator=(const RtclSetList&) = delete;     // noncopyable

      void          Add(const std::string& name, set_uptr_t&& upset);

      template <class TP>
      void          Add(const std::string& name, 
                        std::function<void(TP)>&& set);

      void          Clear();
      int           M_set(RtclArgs& args);

    protected: 
      typedef std::map<std::string, set_uptr_t> map_t;

      map_t         fMap;
  };
  
} // end namespace Retro

#include "RtclSetList.ipp"

#endif
