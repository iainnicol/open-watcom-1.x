#define _NSIG       64
#define _NSIG_BPW   (sizeof( unsigned long ) * 8)
#define _NSIG_WORDS (_NSIG / _NSIG_BPW)

typedef struct {
    unsigned long sig[_NSIG_WORDS];
} sigset_t;

struct sigaction {
    union {
        void        (*sa_handler)(int);
        void        (*sa_sigaction)(int, siginfo_t *, void *);
    } _u;
    unsigned long   sa_flags;
    void            (*sa_restorer)(void);
    sigset_t        sa_mask;
};
# define sa_handler     _u.sa_handler
# define sa_sigaction   _u.sa_sigaction

union sigval {
    int         sigval_int;
    void        *sigval_ptr;
};

struct sigevent {
    int          sigev_signo;
    union sigval sigev_value;
};

struct msigevent {
    long         sigev_signo;
    union sigval sigev_value;
};
