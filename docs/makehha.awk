/<H. ID=\"(.*)\"> (.*) <\/H.>/ {
    newlevel = $0
    gsub( /<H/, "", newlevel )
    gsub( / ID=\"(.*)\" (.*) <\/H.>/, "", newlevel )
    file = $0
    gsub( /<H. ID=\"/, "", file )
    gsub( /\"> (.*) <\/H.>/, "", file )
    title = $0
    gsub( /<H. ID=\"(.*)\"> /, "", title )
    gsub( / <\/H.>/, "", title )
    gsub( /\&nbsp\;/, "", title )
    print "HLP_" toupper( file ) " = " file ".htm"
}
