#define _NSIG       128
#define _NSIG_BPW   (sizeof( unsigned long ) * 8)
#define _NSIG_WORDS (_NSIG / _NSIG_BPW)

typedef struct {
    unsigned long sig[_NSIG_WORDS];
} sigset_t;

typedef unsigned long old_sigset_t;     /* at least 32 bits */

struct sigaction {
    unsigned int    sa_flags;
    void            (*sa_handler)(int);
    sigset_t        sa_mask;
};
