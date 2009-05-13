.model small
.data
    for _arg, <1,2,3,4,5,6,7,8,9,0>
        db _arg
        if _arg eq 3 or _arg eq 5
        .err
        endif
    endm
    irp _arg, <1,2,3,4,5,6,7,8,9,0>
        dw _arg
    endm
    forc _arg, <1234567890>
        dd _arg
    endm
end
