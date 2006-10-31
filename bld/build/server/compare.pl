#!/usr/bin/perl -w
############################################################################
#
#                            Open Watcom Project
#
#  Copyright (c) 2004-2006 The Open Watcom Contributors. All Rights Reserved.
#
#  ========================================================================
#
#    This file contains Original Code and/or Modifications of Original
#    Code as defined in and that are subject to the Sybase Open Watcom
#    Public License version 1.0 (the 'License'). You may not use this file
#    except in compliance with the License. BY USING THIS FILE YOU AGREE TO
#    ALL TERMS AND CONDITIONS OF THE LICENSE. A copy of the License is
#    provided with the Original Code and Modifications, and is also
#    available at www.sybase.com/developer/opensource.
#
#    The Original Code and all software distributed under the License are
#    distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
#    EXPRESS OR IMPLIED, AND SYBASE AND ALL CONTRIBUTORS HEREBY DISCLAIM
#    ALL SUCH WARRANTIES, INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF
#    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR
#    NON-INFRINGEMENT. Please see the License for the specific language
#    governing rights and limitations under the License.
#
#  ========================================================================
#
#  Description: This program compares an old and new summary log to find
#               errors that have been removed and errors that have been
#               added.
#
###########################################################################
#use strict;

# Read the next two line record from the summary file.
sub read_record
{
    my($file) = $_[0];
    my($record, $line);
    while (<$file>) {
        chomp;
        s/#.*//;
        if (/^\s*$/) { next; }
        $record = $_;
        $line = <$file>;
        chomp($line);
        $record = $record . "|" . $line;
        return $record;
    }
    return "EOF";
}

# Display a combined record as two lines.
sub print_record
{
    my($record) = $_[0];
    my(@fields) = split /\|/, $record;
    print "$fields[0]\n$fields[1]\n\n";
}

#############
# Main Script
#############

if ($#ARGV != 1) {
    print "Usage: compare old_summary new_summary\n";
    exit 1;
}

# Read both the old and new summaries into memory.
open(OLDFILE, "$ARGV[0]") || die "Unable to open input file: $ARGV[0]";
while (($record = read_record(OLDFILE)) ne "EOF") {
    push @old_records, $record;
}
close(OLDFILE);

open(NEWFILE, "$ARGV[1]") || die "Unable to open output file: $ARGV[1]";
while (($record = read_record(NEWFILE)) ne "EOF") {
    push @new_records, $record;
}
close(NEWFILE);

# Now compare the summaries. This runs in O(n^2) where n is the # of records.
#############################################################################

$something_added   = "no";
$something_removed = "no";
$first_added       = "yes";
$first_removed     = "yes";

$something_added = "no";
foreach $record (@new_records) {
    $found = "no";
    foreach $candidate (@old_records) {
        if ($record eq $candidate) { $found = "yes"; }
    }
    if ($found eq "no") {
        if ($first_added eq "yes") {
            print "Messages Added\n";
            print "--------------\n\n";
            $first_added = "no";
        }   
        print_record($record);
        $something_added = "yes";
    }
}

# If there are new errors, don't bother computing removed messages. Some
# messages might appear to vanish because certain compilations failed to
# finish. Only trust the removal list if there are no additional errors.
#
if ($something_added eq "no") {
    foreach $record (@old_records) {
        $found = "no";
        foreach $candidate (@new_records) {
            if ($record eq $candidate) { $found = "yes"; }
        }
        if ($found eq "no") {
            if ($first_removed eq "yes") {
                print "Messages Removed\n";
                print "----------------\n\n";
                $first_removed = "no";
            }   
            print_record($record);
            $something_removed = "yes";
        }
    }
}

$exit_status = 1;  # Assume failure.

# This is what we like to see.
if ($something_added eq "no" && $something_removed eq "no") {
    print "Build Successful\n\n";
    $exit_status = 0;
}

exit $exit_status

