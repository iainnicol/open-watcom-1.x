# get uppercased module name
/^LIBRARY/ { ModuleName = toupper( $2 ); next }

# skip uninteresting lines
/^ *(EXPORTS|;)/ { next }

# NB: Calling conventions essentially do not exist on non-x86 platforms,
# we simply strip the decoration unless 'cpu' equals 386.

# process fastcall symbols "@symbol@size"
/^@[A-Za-z0-9_]+@[0-9]+/ {
  split( $1, parts, "@" ) # split the import name on the at signs
  if( cpu == "386" )
    printf( "++'__imp_%s'.'%s'.'%s'.'%s'\n", $1, ModuleName, $1, parts[2] )
  else
    printf( "++'__imp%s'.'%s'.'%s'\n", parts[1], ModuleName, parts[2] )
  next
}

# process stdcall symbols using "symbol@size" format
/^[A-Za-z0-9_]+@[0-9]+/ {
  split( $1, parts, "@" ) # split the import name on the at sign
  if( cpu == "386" )
    printf( "++'__imp__%s'.'%s'.'_%s'.'%s'\n", $1, ModuleName, $1, parts[1] )
  else
    printf( "++'__imp_%s'.'%s'.'%s'\n", parts[1], ModuleName, parts[1] )
  next
}

# process cdecl symbols using plain "symbol" format
/^[A-Za-z0-9_]+/ {
  split( $1, parts, "@" ) # split the import name on the at sign
  if( cpu == "386" )
    printf( "++'__imp__%s'.'%s'.'_%s'.'%s'\n", $1, ModuleName, $1, $1 )
  else
    printf( "++'__imp_%s'.'%s'.'%s'\n", $1, ModuleName, $1 )
  next
}
