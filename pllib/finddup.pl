#!/usr/bin/perl -w

# find duplicated files in a directory by only checking the file Sizes (//TODO: checking/hash content)
# call: ./finddup.pl /home/h/Downloads/tmp > /home/h/Downloads/tmp/sameSizes.log

use strict;
use warnings;

my $dir = $ARGV[0];
my %fileSize2Name = ();
my $sameSizes = 0;

opendir(DH, $dir);
my @files = readdir(DH);
closedir(DH);

@files = sort @files;                                   # sort alphabetically

foreach(@files)
{
    my $fn = $_;
    my $absFn = $dir . "/" . $fn;
    if (-f $absFn)                                      # = is a file
    {
        my $fileSize = -s $absFn;                       # = getFileSize, similar to stat
        if (exists($fileSize2Name{$fileSize})) {
            print "$fn <sameSize> $fileSize2Name{$fileSize}\n";
            $sameSizes = $sameSizes + 1;
        }
        else
        {
            $fileSize2Name{$fileSize} = $fn;
        }
    }
}

my $fileSize2Names = (keys %fileSize2Name);
print "FINISH. checked $fileSize2Names files. sameSizes = $sameSizes\n";
