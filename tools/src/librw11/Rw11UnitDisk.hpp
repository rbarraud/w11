// $Id: Rw11UnitDisk.hpp 1186 2019-07-12 17:49:59Z mueller $
// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright 2013-2017 by Walter F.J. Mueller <W.F.J.Mueller@gsi.de>
// 
// Revision History: 
// Date         Rev Version  Comment
// 2017-04-07   868   1.0.3  Dump(): add detail arg
// 2015-03-21   659   1.0.2  add fEnabled, Enabled()
// 2015-02-18   647   1.0.1  add Nwrd2Nblk()
// 2013-04-19   507   1.0    Initial version
// 2013-02-19   490   0.1    First draft
// ---------------------------------------------------------------------------


/*!
  \brief   Declaration of class Rw11UnitDisk.
*/

#ifndef included_Retro_Rw11UnitDisk
#define included_Retro_Rw11UnitDisk 1

#include "Rw11VirtDisk.hpp"

#include "Rw11UnitVirt.hpp"

namespace Retro {

  class Rw11UnitDisk : public Rw11UnitVirt<Rw11VirtDisk> {
    public:
                    Rw11UnitDisk(Rw11Cntl* pcntl, size_t index);
                   ~Rw11UnitDisk();

      virtual void  SetType(const std::string& type);

      const std::string& Type() const;
      virtual bool  Enabled() const;
      size_t        NCylinder() const;
      size_t        NHead() const;
      size_t        NSector() const;
      size_t        BlockSize() const;
      size_t        NBlock() const;

      uint32_t      Chs2Lba(uint16_t cy, uint16_t hd, uint16_t se);
      void          Lba2Chs(uint32_t lba, uint16_t& cy, uint16_t& hd, 
                            uint16_t& se);
      uint32_t      Nwrd2Nblk(uint32_t nwrd);

      void          SetWProt(bool wprot);
      bool          WProt() const;

      bool          VirtRead(size_t lba, size_t nblk, uint8_t* data, 
                             RerrMsg& emsg);
      bool          VirtWrite(size_t lba, size_t nblk, const uint8_t* data, 
                              RerrMsg& emsg);

      virtual void  Dump(std::ostream& os, int ind=0, const char* text=0,
                         int detail=0) const;

    protected:
      std::string   fType;                  //!< drive type
      bool          fEnabled;               //!< unit enabled
      size_t        fNCyl;                  //!< # cylinder
      size_t        fNHead;                 //!< # heads (aka surfaces)
      size_t        fNSect;                 //!< # sectors
      size_t        fBlksize;               //!< block size (in bytes)
      size_t        fNBlock;                //!< # blocks
      bool          fWProt;                 //!< unit write protected
  };
  
} // end namespace Retro

#include "Rw11UnitDisk.ipp"

#endif
