#!/usr/bin/perl -w

# find duplicated files in a directory by only checking the fileSize or checkSum of the file
# call: ./finddup.pl /home/h/Downloads/tmp 1 _ > /home/h/Downloads/tmp/sameSizes.log 2>&1

# 1. param: dir to check
# 2. param: 0 or 1 = useCheckSum off/on
# 3. param: \S+ = duplicate to be renamed, use this prefix

use strict;
use warnings;

use 5.010; # so i can use 'state'

use Digest::MD5 qw(md5_hex);
use IO::File;

my $dir                 = $ARGV[0];
my $useCheckSum         = ($#ARGV > 0) ? ($ARGV[1] == '1') : 0;
my $renameDupPrefix     = ($#ARGV > 1) ?  $ARGV[2] : 0;
my %fileKey2Name        = ();
my $sameKeys            = 0;
my $fileKey2Names       = 0;

opendir(DH, $dir) or die "!open $dir";
my @files = readdir(DH); # read in the list of the files at once, because we will change the dir content in our script
closedir(DH);

@files = sort @files;                                   # sort alphabetically

_log("START. dir: $dir , useCheckSum: $useCheckSum , renameDupPrefix: $renameDupPrefix");

foreach(@files)
{
    my $fn = $_;
    my $absFn = $dir . "/" . $fn;
    if (-f $absFn)                                      # = is a file
    {
        my $fileSize = -s $absFn;                       # = getFileSize, similar to stat
        my $key = $fileSize;
        $fileKey2Names = (keys %fileKey2Name);
        if ($useCheckSum)
        {
            my $checkSum = getCheckSum($absFn);
            $key = $checkSum;
        }
        
        if ($useCheckSum and (($fileKey2Names % 10) == 0))
        {
            _log(".");
        }
        
        if (exists($fileKey2Name{$key}))
        {
            _log("$fn <sameKey $key> $fileKey2Name{$key}");
            $sameKeys++;
            
            if ($renameDupPrefix) {
                my $newFn = $dir . '/' . $renameDupPrefix . $fn;
                _log("renamed to: ".$newFn);
                rename $absFn, $newFn;
            }
        }
        else
        {
            $fileKey2Name{$key} = $fn;
        }
    }
}

$fileKey2Names = (keys %fileKey2Name);
_log("FINISH. checked $fileKey2Names files. sameSizes = $sameKeys");

sub getCheckSum
{
    my $absFn = $_[0];
    open (my $FH, $absFn) or die "!open $absFn";
    binmode ($FH);
    my $checkSum = Digest::MD5->new->addfile($FH)->hexdigest;
    close ($FH);
    return $checkSum;
}

sub _log
{
    my $s = $_[0];
    my $slen = length($s);
    
    state $startWithNewLine = 0;
    
    my $prefix  = ($startWithNewLine == 1) ? "\n" : "";
    my $postfix = ($slen < 2) ? "" : "\n";

    if ($slen < 2)
    {
        $postfix = "";
        $prefix  = "";
        $startWithNewLine = 1;
    }
    else
    {
        $startWithNewLine = 0;    
    }

    print STDERR $prefix.$s.$postfix;
}
