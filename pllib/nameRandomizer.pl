#!/usr/bin/perl

#call this script with: ./nameRandomizer.pl docx

use File::Basename;
# 'rename' does not always work across file systems the recommended alternative is the move function of the File::Copy module:
use File::Copy qw(move);

my $curDir = './';
my $ext   = $ARGV[0];
my @files = glob($curDir . '*.' . $ext);

my $handled = 0;

foreach ( @files ) {
    my $fn = basename($_);
    my $random_number = int(rand(100));
    my $new_fn = $random_number . '.' . $fn;
    
	move $curDir.$fn , $curDir.$new_fn;
	
	$handled = $handled + 1;
}

print "renamed files:$handled\n";
