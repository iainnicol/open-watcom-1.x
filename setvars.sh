# Do not use directly; copy and modify as appropriate

#export P4PORT=perforce.openwatcom.org:3488
#export P4USER=YourName
#export P4PASSWD=YourPassword
#export P4CLIENT=YourClient

export OWROOT=`cd \`dirname -- $0\` && pwd`
source $OWROOT/cmnvars.sh

# Adjust to match the host platform
export BOOTSTRAP_OS=linux
export BOOTSTRAP_CPU=386
