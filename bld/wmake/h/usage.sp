::
:: help page
:: For a page break, leave a line undefined.
::
:segment ENGLISH
Usage  :  wmake [options]* [macro=text]* [target]*
Options:  ('-' may be substituted for '/', and '#' for '=')
/a make all targs (ignoring time stamp)  /b block/ignore all implicit rules
/c do not check existence of files made  /d debug mode (echo progress of work)
/e erase files after error (no prompt)   /h do not print program header
/i ignore command return status          /k continue after an error
:segment HIDDEN
::	until we know this works properly for '::' rules
/j set time stamp of files made to the latest time stamp of their dependents
:endsegment
/m do not read MAKEINIT file             /ms Microsoft NMAKE mode
/n print commands without executing      /o take advantage of circular path  
/q query mode (commands not executed)    
/p print the dependency tree, macro definitions, and extension information
/r ignore built-in definitions           /s silent mode (do not print commands)
/t touch files (commands not executed)   /u UNIX compatibility mode
/v verbose listing of inline files       /z do not erase files (no prompt)
/l logfile	append output to logfile
/f filename	process filename instead of MAKEFILE ('/f -' means stdin)
macro=text	overrides the definition of 'macro' with the value 'text'
target		specifies a target to make (default is first target)
:elsesegment JAPANESE
�g�p���@:  wmake [options]* [macro=text]* [target]*
�I�v�V����:  ('/'��'-'��,'='��'#'�ő�p���鎖���ł��܂�)
/a �S���ޯĂ��쐬���܂�(��ѥ����߂𖳎�)  /b ���ׂĂ̈Ö�ٰق𖳎����܂�
/c ���ꂽ̧�ق�����ǂ����������܂���   /d ���ޯ�ޥӰ��(�����ߒ����o�͂��܂�)
/e �װ���N�������A̧�ق������܂�(�m�F���܂���)
/h ��۸��ѥͯ�ނ��o�͂��܂���		  /u UNIX�݊�Ӱ��
/i ����ނ��Ԃ��ð���𖳎����܂�           /k �װ���N���Ă����s���܂�
:segment HIDDEN
:: until we know this works properly for '::' rules
/j ̧�ق���ѥ����߂��ˑ���̒��ōŐV����ѥ����߂ɐݒ肵�܂�
:endsegment
/m MAKEINIT ̧�ق�ǂ݂܂���              /ms microsoft nmake mode
/n ���s�����ɁA����ނ�\�����܂�          /o �z���߽�𗘗p���܂�                    
/q �₢����Ӱ��(����ނ����s���܂���)
/p �ˑ��K���Aϸۂ̒�`�A�g����̫Ұ��݂Ȃǂ��o�͂��܂�
/r ��̫�Ē�`�𖳎����܂�                 /s ����ĥӰ��(����ނ�\�����܂���)
/t ̧�ق���ѥ����߂��X�V���܂�(����ނ����s���܂���)
/v verbose listing of inline file
/z ̧�ق������܂���(�m�F���܂���)
/l logfile    ۸ޥ̧�قɏo�͂�ǉ����܂�
/f filename    MAKEFILE�̑���̧��filename���������܂�('/f -'�͕W�����͂ł�)
macro=text    'macro' �̒l�� 'text' �ōĒ�`���܂�
target        �쐬���������ޯĂ��w�肵�܂�(��̫�Ă͈�Ԗڂ����ޯĂł�)
:endsegment
:segment IS_RC
.
:endsegment
