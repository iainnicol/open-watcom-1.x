@echo off
rm -f %distroot%\archives\*.zip
rm mkzips.log
call zipit clib_a16
call zipit clib_d16
call zipit clib_o16
call zipit clib_o32
call zipit clib_w16
call zipit clib_w32
call zipit cm_clib_a16
call zipit cm_clib_a32
call zipit cm_clib_d16
call zipit cm_clib_d32
call zipit cm_clib_hdr
call zipit cm_clib_n32
call zipit cm_clib_o16
call zipit cm_clib_o32
call zipit cm_clib_w16
call zipit cm_clib_w32
call zipit cm_core_all
call zipit cm_core_dos
call zipit cm_core_doswin
call zipit cm_core_nt
call zipit cm_core_os2
call zipit cm_core_win
call zipit cm_dbg_all
call zipit cm_dbg_dos
call zipit cm_dbg_dosos2
call zipit cm_dbg_doswin
call zipit cm_dbg_misc1
call zipit cm_dbg_misc2
call zipit cm_dbg_net
call zipit cm_dbg_nt
call zipit cm_dbg_os2
call zipit cm_dbg_os2nt
call zipit cm_dbg_win
call zipit cm_ide_all
call zipit cm_ide_nt
call zipit cm_ide_os2
call zipit cm_ide_dos
call zipit cm_ide_win
call zipit cm_hlp_dos
call zipit cm_hlp_nt
call zipit cm_hlp_os2
call zipit cm_hlp_win
call zipit cm_plib_a16
call zipit cm_plib_a32
call zipit cm_plib_o32
call zipit cm_plib_w32
call zipit core_all
call zipit core_doswin
call zipit core_nt
call zipit core_os2
call zipit cpp_doswin
call zipit cpp_nt
call zipit cpp_os2
call zipit c_doswin
call zipit c_nt
call zipit c_os2
call zipit fc_doswin
call zipit fc_hlp_dos
call zipit fc_hlp_nt
call zipit fc_hlp_os2
call zipit fc_hlp_win
call zipit fc_nt
call zipit fc_os2
call zipit flib_d16
call zipit flib_d32
call zipit flib_n32
call zipit flib_o16
call zipit flib_o32
call zipit flib_w16
call zipit flib_w32
call zipit hlp_dos
call zipit hlp_nt
call zipit hlp_os2
call zipit hlp_win
call zipit plib_a16
call zipit plib_a32
call zipit plib_hdr
call zipit plib_o16
call zipit plib_o32
call zipit plib_w16
call zipit plib_w32
echo All done!
