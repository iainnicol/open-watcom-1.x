:segment ENGLISH
Usage:   wdisasm [options] obj_file [options]
:segment qnx
Options:
:elsesegment
Options:			( /option is also supported )
:endsegment
	-l[=list_file]      	generate listing file
        -s[=source_file]	include source lines
        -c=code_name        	additional code segment name
        -i=char             	initial character of internal labels
        -a[u]               	generate Intel/Unix .ASM format
        -b                  	alternate form of based modes
        -e                  	generate list of externs
        -p                  	generate list of publics
        -r                  	registers in upper case
        -u                  	instruction names in upper case
	-m			leave C++ names mangled
:segment HIDDEN
	-w		        decode Weitek macros if present
:endsegment
:elsesegment JAPANESE
�g�p���@: wdisasm [options] obj_file [options]
:segment qnx
�I�v�V����:
:elsesegment
�I�v�V����:			( /��߼�� �ł��w��\)
:endsegment
	-l[=list_file]		���X�g�t�@�C���̐���
	-s[=source_file]	�\�[�X�s�̑}��
	-c=code_name		�R�[�h�Z�O�����g���̒ǉ�
	-i=char			�������x�����Ŏg�p����C�j�V���������̎w��
	-a[u]			Intel/Unix ��.ASM �t�H�[�}�b�g�ł̐���
	-b			�x�[�X�E���[�h�̑�փt�H�[���ł̐���
	-e			�G�N�X�^�[�i���E���X�g�̐���
	-p			�p�u���b�N�E���X�g�̐���
	-r			���W�X�^���ɑ啶�����g�p
	-u			�j���j�b�N�ɑ啶�����g�p
	-m			�v���v���Z�X���C++ ���̕ێ�
:segment HIDDEN
	-w			Weitek�}�N���̃f�R�[�h
:endsegment
:endsegment
