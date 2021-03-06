# $Id: 211bsd_tm_rm05_boot.tcl 1139 2019-04-27 14:00:38Z mueller $
#
# Setup file for creating a 211bsd RM05 system from a TM11 dist kit
#
# Usage:
#   
# console_starter -d DL0 &
# console_starter -d DL1 &
# create_disk --typ=rm05 --bad 211bsd_rm05.dsk
# ti_w11 -xxx @211bsd_tm_boot.tcl        ( -xxx depends on sim or fpga connect)
#

# setup w11 cpu
rutil::dohook "preinithook"
puts [rlw]

# setup tt,lp (211bsd uses parity -> use 7 bit mode)
rw11::setup_tt "cpu0" dlrxrlim 5 to7bit 1
rw11::setup_lp 

# mount disks
cpu0rpa0 set type rm05
cpu0rpa1 set type rm05

cpu0rpa0 att 211bsd_rm05.dsk

# mount tapes
cpu0tma0 att 211bsd_tm.tap?wpro

# and boot
rutil::dohook "preboothook"
cpu0 boot tma0
