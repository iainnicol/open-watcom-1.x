/****************************************************************************
*
*                            Open Watcom Project
*
*    Portions Copyright (c) 1983-2002 Sybase, Inc. All Rights Reserved.
*
*  ========================================================================
*
*    This file contains Original Code and/or Modifications of Original
*    Code as defined in and that are subject to the Sybase Open Watcom
*    Public License version 1.0 (the 'License'). You may not use this file
*    except in compliance with the License. BY USING THIS FILE YOU AGREE TO
*    ALL TERMS AND CONDITIONS OF THE LICENSE. A copy of the License is
*    provided with the Original Code and Modifications, and is also
*    available at www.sybase.com/developer/opensource.
*
*    The Original Code and all software distributed under the License are
*    distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
*    EXPRESS OR IMPLIED, AND SYBASE AND ALL CONTRIBUTORS HEREBY DISCLAIM
*    ALL SUCH WARRANTIES, INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF
*    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR
*    NON-INFRINGEMENT. Please see the License for the specific language
*    governing rights and limitations under the License.
*
*  ========================================================================
*
* Description:  Main file of public UNACE.
*
****************************************************************************/


#define INCL_WIN       /* Window Manager Functions     */
#define INCL_DOS
#define INCL_BASE
#include <os2.h>
#include "install.h"
#define OS2_H_INCLUDED
extern int installstate;


//--------------- include general files ------------------------------------//
#include <ctype.h>      // tolower()
#include <fcntl.h>      // open()
#include <stdio.h>      // printf() sprintf() remove()
#include <stdlib.h>     // malloc()
#include <io.h>
#include <string.h>     // str*()
#include <sys/types.h>
#include <sys/stat.h>   // S_I*  fstat()

off_t acelseek(off_t offset, int whence);
int aceread(void *buf, size_t count);
int aceopen(const char *path, int flags);
int aceclose(int fd);
char *replacestr(char *str1, char *str2, char *str3);
extern HWND mainhwnd;

//--------------- include unace specific header files ----------------------//
#include "os.h"

#include "globals.h"
#include "portable.h"
#include "uac_comm.h"
#include "uac_crc.h"
#include "uac_crt.h"
#include "uac_dcpr.h"
#include "uac_sys.h"

#ifdef CRYPT
 #include "unace_ps.h"
#endif /* CRYPT */




//--------------- BEGIN OF UNACE ROUTINES ----------------------------------//

int pipeit(char *format, ...)
{
   /* Do nothing ... perhaps pipe this somewhere in the future */
   return 0;
}

void init_unace(void)           // initializes unace
{
   buf_rd =malloc(size_rdb * sizeof(ULONG));  // Allocate buffers: increase
   buf    =malloc(size_buf);                  // sizes when possible to speed
   buf_wr =malloc(size_wrb);                  // up the program
   readbuf=malloc(size_headrdb);

   if (buf_rd ==NULL ||
       buf    ==NULL ||
       buf_wr ==NULL ||
       readbuf==NULL )
      f_err = ERR_MEM;

   make_crctable();             // initialize CRC table
   dcpr_init();                 // initialize decompression

   set_handler();               // ctrl+break etc.
}

void done_unace(void)
{
   if (buf_rd   ) free(buf_rd   );
   if (buf      ) free(buf      );
   if (buf_wr   ) free(buf_wr   );
   if (readbuf  ) free(readbuf  );
   if (dcpr_text) free(dcpr_text);
}

INT  read_header(INT print_err)         // reads any header from archive
{
   USHORT rd,
        head_size,
        crc_ok;
   LONG crc;
   UCHAR *tp=readbuf;

   acelseek(skipsize, SEEK_CUR);   // skip ADDSIZE block

   if (aceread(&head, 4)<4)
      return (0);                       // read CRC and header size

#ifdef HI_LO_BYTE_ORDER
   WORDswap(&head.HEAD_CRC);
   WORDswap(&head.HEAD_SIZE);
#endif
                                        // read size_headrdb bytes into
   head_size = head.HEAD_SIZE;          // header structure
   rd = (head_size > size_headrdb) ? size_headrdb : head_size;
   if (aceread(readbuf, rd) < rd)
      return (0);
   head_size -= rd;
   crc = getcrc(CRC_MASK, readbuf, rd);

   while (head_size)                    // skip rest of header
   {
      rd = (head_size > size_buf) ? size_buf : head_size;
      if (aceread(buf, rd) < rd)
         return (0);
      head_size -= rd;
          crc = getcrc(crc, (UCHAR*)buf, rd);
   }

   head.HEAD_TYPE =*tp++;               // generic buffer to head conversion
   head.HEAD_FLAGS=BUFP2WORD(tp);

   if (head.HEAD_FLAGS & ACE_ADDSIZE)
      skipsize = head.ADDSIZE = BUF2LONG(tp);   // get ADDSIZE
   else
      skipsize = 0;

                                                // check header CRC
   if (!(crc_ok = head.HEAD_CRC == (crc & 0xffff)) && print_err)
      pipeit("\nError: archive is broken\n");
   else
   switch (head.HEAD_TYPE)              // specific buffer to head conversion
   {
      case MAIN_BLK:
         memcpy(mhead.ACESIGN, tp, acesign_len); tp+=acesign_len;
         mhead.VER_MOD=*tp++;
         mhead.VER_CR =*tp++;
         mhead.HOST_CR=*tp++;
         mhead.VOL_NUM=*tp++;
         mhead.TIME_CR=BUFP2LONG(tp);
         mhead.RES1   =BUFP2WORD(tp);
         mhead.RES2   =BUFP2WORD(tp);
         mhead.RES    =BUFP2LONG(tp);
         mhead.AV_SIZE=*tp++;
         memcpy(mhead.AV, tp, rd-(USHORT)(tp-readbuf));
         break;
      case FILE_BLK:
         fhead.PSIZE     =BUFP2LONG(tp);
         fhead.SIZE      =BUFP2LONG(tp);
         fhead.FTIME     =BUFP2LONG(tp);
         fhead.ATTR      =BUFP2LONG(tp);
         fhead.CRC32     =BUFP2LONG(tp);
         fhead.TECH.TYPE =*tp++;
         fhead.TECH.QUAL =*tp++;
         fhead.TECH.PARM =BUFP2WORD(tp);
         fhead.RESERVED  =BUFP2WORD(tp);
         fhead.FNAME_SIZE=BUFP2WORD(tp);
         memcpy(fhead.FNAME, tp, rd-(USHORT)(tp-readbuf));
         break;
//    default: (REC_BLK and future things):
//              do nothing 'cause isn't needed for extraction
   }

   return (crc_ok);
}
                                // maximum SFX module size
#define max_sfx_size 65536      // (needed by read_arc_head)

INT read_arc_head(void)         // searches for the archive header and reads it
{
   INT  i,
        flags,
        buf_pos = 0;
   LONG arc_head_pos,
        old_fpos,
        fpos = 0;
   struct stat st;

   fstat(archan, &st);

   memset(buf, 0, size_buf);

   while (tell(archan)<st.st_size && fpos < max_sfx_size)
   {
      old_fpos = fpos;
      fpos += aceread(&buf[buf_pos], size_buf - buf_pos);

      for (i = 0; i < size_buf; i++)    // look for the acesign
      {
         if (!memcmp(acesign, &buf[i], acesign_len))
         {
                                        // seek to the probable begin
                                        // of the archive
            arc_head_pos = old_fpos + i - buf_pos -  bytes_before_acesign;
            acelseek(arc_head_pos, SEEK_SET);
            if (read_header(0))         // try to read archive header
            {
               flags = mhead.HEAD_FLAGS;
               adat.sol     = (flags & ACE_SOLID) > 0;
               adat.vol     = (flags & ACE_MULT_VOL) > 0;
               adat.vol_num = mhead.VOL_NUM;
               adat.time_cr = mhead.TIME_CR;
               return (1);
            }
         }
      }
                                        // was no archive header,
                                        // continue search
      acelseek(fpos, SEEK_SET);
      memcpy(buf, &buf[size_buf - 512], 512);
      buf_pos = 512;                    // keep 512 old bytes
   }
   return (0);
}

INT  open_archive(INT print_err)        // opens archive (or volume)
{
   CHAR av_str[80];

   archan = aceopen(aname, O_RDONLY | O_BINARY);   // open file

   if (archan == -1)
   {
      error("\nError opening file %s", aname);
      return (0);
   }
   if (!read_arc_head())                        // read archive header
   {
      error("\nInvalid archive file: %s\n", aname);
      aceclose(archan);
      return (0);
   }

   pipeit("\nProcessing archive: %s\n\n", aname);
   if (head.HEAD_FLAGS & ACE_AV)
   {
      pipeit("Authenticity Verification:");   // print the AV
      sprintf(av_str, "\ncreated on %d.%d.%d by ",
              ts_day(adat.time_cr), ts_month(adat.time_cr), ts_year(adat.time_cr));
      pipeit(av_str);
          strncpy(av_str, (CHAR*)mhead.AV, mhead.AV_SIZE);
      av_str[mhead.AV_SIZE] = 0;
      pipeit("%s\n\n", av_str);
   }
   comment_out("Main comment:");        // print main comment
   return (1);
}

void get_next_volname(void)             // get file name of next volume
{
   CHAR *cp;
   INT  num;

   if ((cp = (CHAR *) strrchr(aname, '.')) == NULL || !*(cp + 1))
      num = -1;
   else
   {
      cp++;
      num = (*(cp + 1) - '0') * 10 + *(cp + 2) - '0';
      if (!in(num, 0, 99))
         num = -1;
      if (in(*cp, '0', '9'))
         num += (*cp - '0') * 100;
   }
   num++;

   if (num < 100)
      *cp = 'C';
   else
      *cp = num / 100 + '0';
   *(cp + 1) = (num / 10) % 10 + '0';
   *(cp + 2) = num % 10 + '0';
}

INT  proc_vol(void)                     // opens volume
{
   INT  i;
   CHAR s[80];

   if (!fileexists(aname) || !f_allvol_pr)
   {
      do
      {
         sprintf(s, "Ready to process %s?", aname);
         beep();
         i = confirm(s);                  // ask whether ready or not
         f_allvol_pr = (i == 1);        // "Always" --> process all volumes
         if (i >= 2)
         {
            f_err = ERR_FOUND;
            return (0);
         }
      }
      while (!fileexists(aname));
   }

   if (!open_archive(1))                // open volume
   {
      pipeit("\nError while opening archive. File not found or archive broken.\n");
      f_err = ERR_OPEN;
      return (0);
   }

   return (1);
}

INT  proc_next_vol(void)        // opens next volume to process
{
   aceclose(archan);               // close handle
   get_next_volname();          // get file name of next volume

   if (!proc_vol())             // try to open volume, read archive header
      return 0;
   if (!read_header(1))         // read 2nd header
   {
      f_err=ERR_READ;
      return 0;
   }
   return 1;
}

INT  read_adds_blk(CHAR * buffer, INT len)      // reads part of ADD_SIZE block
{
   INT  rd = 0,
        l = len;
   LONG i;

#ifdef CRYPT
   char *cbuffer=buffer;

   if (head.HEAD_TYPE == FILE_BLK && (head.HEAD_FLAGS & ACE_PASSW))
      len = crypt_len(len);
#endif /* CRYPT */
   while (!f_err && len && skipsize)
   {
      i = (skipsize > len) ? len : skipsize;
      skipsize -= i;

      errno = 0;
      rd += aceread(buffer, i);
      if (errno)
      {
         error("\nRead error\n");
         f_err = ERR_READ;
      }

      buffer += i;
      len -= i;

      if (!skipsize)            // if block is continued on next volume
         if (head.HEAD_FLAGS & ACE_SP_AFTER && !proc_next_vol())
            break;
   }
#ifdef CRYPT
   if (head.HEAD_TYPE == FILE_BLK && (head.HEAD_FLAGS & ACE_PASSW))
      decrypt(cbuffer, rd);
#endif /* CRYPT */

   return (rd > l ? l : rd);
}

void crc_print(void)            // checks CRC, prints message
{
   if((rd_crc != fhead.CRC32) && (f_err != ERR_USER))  /* check CRC of file */
   {
           error("CRC check error!");
   }
}

void analyze_file(void)         // analyzes one file (for solid archives)
{
   pipeit("\n Analyzing");
   flush;
   while (!cancel() && (dcpr_adds_blk(buf_wr, size_wrb))) // decompress only
      ;
   crc_print();
}

void extract_file(void)         // extracts one file
{
   INT  rd;

   pipeit("\n Extracting");
   flush;                       // decompress block
   while (!cancel() && (rd = dcpr_adds_blk(buf_wr, size_wrb)))
   {
      if (write(wrhan, buf_wr, rd) != rd)       // write block
      {
         error("\nWrite error\n");
         f_err = ERR_WRITE;
      }
   }
   crc_print();
}


/* extracts or tests all files of the archive
 */
void extract_files(int nopath, int test, char *getfilename)
{
        CHAR file[PATH_MAX];
    char *tmpfile;
        extern unsigned current_file;
        extern char installdir[], installdir2[];

        while (!cancel() && read_header(1))
        {
                if (head.HEAD_TYPE == FILE_BLK)
                {
                        if(installstate == ABORTED)
                                return;
                        current_file++;
#ifdef __OS2__
                        WinSendMsg(mainhwnd, WM_USER, MPFROM2SHORT(0, 0), MPFROM2SHORT(0, 0));
#endif

                        comment_out("File comment:");   // show file comment
                        ace_fname(file, &head, nopath); // get file name

            /* We allow expansion of "userdir" to the selected directory by the user */
                        tmpfile = replacestr(file, "USERDIR", installdir2);
                        strcpy(file, tmpfile);
                        free(tmpfile);

                        if(!getfilename || (getfilename && stricmp(getfilename, file) == 0))
                        {
                         pipeit("\n%s", file);
                         flush;
                         dcpr_init_file();               // initialize decompression of file
                         if (!f_err)
                         {
                                 if (test ||
                                         (wrhan = create_dest_file(file, (INT) fhead.ATTR))<0)
                                 {
                                         if (test || adat.sol)
                                                 analyze_file();        // analyze file
                                 }
                                 else
                                 {
                                         extract_file();           // extract it
#ifdef DOS                               // set file time
                                         _dos_setftime(wrhan, (USHORT) (fhead.FTIME >> 16), (USHORT) fhead.FTIME);
#endif
                                         close(wrhan);
#ifdef __OS2__
                                         {
                                                 FILESTATUS3 fileinfo;

                                                 DosQueryPathInfo(file, FIL_STANDARD, &fileinfo, sizeof(FILESTATUS3));
                                                 *((USHORT*)&fileinfo.fdateCreation)   = (USHORT)(fhead.FTIME >> 16);
                                                 *((USHORT*)&fileinfo.ftimeCreation)   = (USHORT)fhead.FTIME;
                                                 *((USHORT*)&fileinfo.fdateLastAccess) = (USHORT)(fhead.FTIME >> 16);
                                                 *((USHORT*)&fileinfo.ftimeLastAccess) = (USHORT)fhead.FTIME;
                                                 *((USHORT*)&fileinfo.fdateLastWrite)  = (USHORT)(fhead.FTIME >> 16);
                                                 *((USHORT*)&fileinfo.ftimeLastWrite)  = (USHORT)fhead.FTIME;
                                                 DosSetPathInfo(file, FIL_STANDARD, (PVOID)&fileinfo, sizeof(FILESTATUS3), 0);
                                         }
#endif
#ifdef DOS                               // set file attributes
                                         _dos_setfileattr(file, (UINT) fhead.ATTR);
#endif
                                         if (f_err)
                                                 remove(file);
                                 }
                         }
                 }
          }
   }
}

unsigned percentage(ULONG p, ULONG d)
{
   return (unsigned)( d ? (d/2+p*100)/d : 100 );
}

int installer_unpack(CHAR * filename, int operation)              // processes the archive
{
          init_unace();                              // initialize unace
      strcpy(aname, "installer");                    // get archive name

          if(filename)
                  f_ovrall=1;

          if (open_archive(1))                       // open archive to process
      {
         if (adat.vol_num)
            pipeit("\nFirst volume of archive required!\n");
         else
            {
            if(operation == 2)
               extract_files(0, 0, filename);
            }
         aceclose(archan);
         if (f_err)
         {
            pipeit("\nError occurred\n");
            if (f_criterr)
               pipeit("Critical error on drive %c\n", f_criterr);
         }
      }

          done_unace();
          return 0;
}
