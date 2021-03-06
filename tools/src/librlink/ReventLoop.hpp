// $Id: ReventLoop.hpp 1186 2019-07-12 17:49:59Z mueller $
// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright 2013-2018 by Walter F.J. Mueller <W.F.J.Mueller@gsi.de>
// 
// Revision History: 
// Date         Rev Version  Comment
// 2018-12-17  1085   1.2.6  use std::mutex instead of boost
// 2018-12-16  1084   1.2.5  use =delete for noncopyable instead of boost
// 2018-12-15  1083   1.2.4  AddPollHandler(): use rval ref and move
// 2018-12-14  1081   1.2.3  use std::function instead of boost
// 2018-12-07  1078   1.2.2  use std::shared_ptr instead of boost
// 2017-04-07   868   1.2.1  Dump(): add detail arg
// 2015-04-04   662   1.2    BUGFIX: fix race in Stop(), add UnStop,StopPending
// 2013-05-01   513   1.1.1  fTraceLevel now uint32_t
// 2013-02-22   491   1.1    use new RlogFile/RlogMsg interfaces
// 2013-01-11   473   1.0    Initial version
// ---------------------------------------------------------------------------


/*!
  \brief   Declaration of class \c ReventLoop.
*/

#ifndef included_Retro_ReventLoop
#define included_Retro_ReventLoop 1

#include <poll.h>

#include <cstdint>
#include <vector>
#include <memory>
#include <functional>
#include <mutex>

#include "librtools/RlogFile.hpp"

namespace Retro {

  class ReventLoop {
    public:
      typedef std::function<int(const pollfd&)> pollhdl_t;

                    ReventLoop();
      virtual      ~ReventLoop();

                    ReventLoop(const ReventLoop&) = delete; // noncopyable 
      ReventLoop&   operator=(const ReventLoop&) = delete;  // noncopyable
 
      void          AddPollHandler(pollhdl_t&& pollhdl,
                               int fd, short events=POLLIN);
      bool          TestPollHandler(int fd, short events=POLLIN);
      void          RemovePollHandler(int fd, short events, bool nothrow=false);
      void          RemovePollHandler(int fd);

      void          SetLogFile(const std::shared_ptr<RlogFile>& splog);
      void          SetTraceLevel(uint32_t level);
      uint32_t      TraceLevel() const;

      void          Stop();
      void          UnStop();
      bool          StopPending();
      virtual void  EventLoop();

      virtual void  Dump(std::ostream& os, int ind=0, const char* text=0,
                         int detail=0) const;

    protected: 

      int           DoPoll(int timeout=-1);
      void          DoCall(void);

    protected: 

      struct PollDsc {
        pollhdl_t   fHandler;
        int         fFd;
        short       fEvents;
        PollDsc(pollhdl_t hdl,int fd,short evts) :
          fHandler(hdl),fFd(fd),fEvents(evts)  {}
      };

      bool          fStopPending;
      bool          fUpdatePoll;
      std::mutex    fPollDscMutex;
      std::vector<PollDsc>   fPollDsc;
      std::vector<pollfd>    fPollFd;
      std::vector<pollhdl_t> fPollHdl;
      uint32_t      fTraceLevel;            //!< trace level
      std::shared_ptr<RlogFile>  fspLog;    //!< log file ptr
};
  
} // end namespace Retro

#include "ReventLoop.ipp"

#endif
