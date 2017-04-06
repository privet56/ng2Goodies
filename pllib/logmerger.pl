use strict;
use Time::localtime;	
my $tm1 = localtime;

dolog("begin...".(1900 + $tm1->year).".".(1+$tm1->mon).".".$tm1->mday." ".$tm1->hour.":".$tm1->min.":".$tm1->sec."\t----------------------------\n");

my $sToFN = "";
my @aLines = ();
my $iFilesCount=0;

for(@ARGV)
{
	if($sToFN eq "")
	{
		$sToFN = $_;
		next;
	}
	
	$iFilesCount++;

	open(FH, "<".$_);
	push(@aLines, <FH>);
	close(FH);
}
dolog("\t".(($#aLines)+1)." lines in ".$iFilesCount." files\n");

@aLines = sort logdatesort @aLines;

open(FH, ">".$sToFN);
print FH @aLines;
close(FH);

$tm1 = localtime;
dolog("end  ...".(1900 + $tm1->year).".".(1+$tm1->mon).".".$tm1->mday." ".$tm1->hour.":".$tm1->min.":".$tm1->sec."\t----------------------------\n\n");

sub logdatesort
{
	#format:
		#[11/Dec/2004:00:11:48 +100]
	#or	
		#[11/Dec/2004:00:11:48 1000]		
	#or
		#2005-01-03 03:00:47 
	my $daya="";
	my $mona="";
	my $yeaa="";
	my $houa="";
	my $mina="";
	my $seca="";
	my $oka=1;
	
	my $dayb="";
	my $monb="";
	my $yeab="";
	my $houb="";
	my $minb="";
	my $secb="";
	my $okb=1;
	
	if($a =~ m/\[(\d+)\/(\w+)\/(\d+):(\d+):(\d+):(\d+) /i)
	{
		$daya=$1;
		$mona=$2;
		$yeaa=$3;
		$houa=$4;
		$mina=$5;
		$seca=$6;
	}
	else
	{
		if($a =~ m/(\d+)-(\d+)-(\d+) (\d+):(\d+):(\d+) /i)
		{
			$daya=$3;
			$mona=$2;
			$yeaa=$1;
			$houa=$4;
			$mina=$5;
			$seca=$6;
		}
		else
		{
			$oka=0;
			dolog("logdatesort\tERROR: unknown logsyntax in line:".$a."\n");
		}
	}
	if($b =~ m/\[(\d+)\/(\w+)\/(\d+):(\d+):(\d+):(\d+) /i)
	{
		$dayb=$1;
		$monb=$2;
		$yeab=$3;
		$houb=$4;
		$minb=$5;
		$secb=$6;
	}
	else
	{
		if($b =~ m/(\d+)-(\d+)-(\d+) (\d+):(\d+):(\d+) /i)
		{
			$dayb=$3;
			$monb=$2;
			$yeab=$1;
			$houb=$4;
			$minb=$5;
			$secb=$6;
		}
		else
		{	
			$okb=0;
			dolog("logdatesort\tERROR: unknown logsyntax in line:".$b."\n");
		}
	}
	
	if(($oka == 0) and ($okb == 0))
	{
		return 0;
	}
	if($okb == 0)
	{
		return 1;
	}
	if($oka == 0)
	{
		return -1;
	}
	#year
	if($yeaa > $yeab)
	{
		return 1;
	}
	if($yeaa < $yeab)
	{
		return -1;
	}
	
	$mona = getMon($mona);
	$monb = getMon($monb);
	
	#mon
	if($mona > $monb)
	{
		return 1;
	}
	if($mona < $monb)
	{
		return -1;
	}
	#day
	if($daya > $dayb)
	{
		return -1;
	}
	if($daya < $dayb)
	{
		return 1;
	}
	#hour
	if($houa > $houb)
	{
		return 1;
	}
	if($houa < $houb)
	{
		return -1;
	}
	#min
	if($mina > $minb)
	{
		return 1;
	}
	if($mina < $minb)
	{
		return -1;
	}
	#sec
	if($seca > $secb)
	{
		return 1;
	}
	if($seca < $secb)
	{
		return -1;
	}
	return 0;
}

sub dolog
{
	my $s = shift;
	open(LOG, ">>logmerger.log");
	print LOG $s;
	close(LOG);
}

sub getMon
{
	my $s = shift;
	if($s =~ m/^\d+$/i)
	{
		return $s;
	}
	
	if($s =~ m/ja/i)
	{
		return 1;
	}
	if($s =~ m/fe/i)
	{
		return 2;
	}
	if($s =~ m/mar/i)			#maerz march
	{
		return 3;
	}
	if($s =~ m/ap/i)
	{
		return 4;
	}
	if($s =~ m/ma/i)			#mai may
	{
		return 5;
	}
	if($s =~ m/jun/i)
	{
		return 6;
	}
	if($s =~ m/jul/i)
	{
		return 7;
	}
	if($s =~ m/au/i)
	{
		return 8;
	}
	if($s =~ m/se/i)
	{
		return 9;
	}
	if($s =~ m/oc/i)
	{
		return 10;
	}
	if($s =~ m/no/i)
	{
		return 11;
	}
	if($s =~ m/de/i)
	{
		return 12;
	}
	dolog("getMon\tERROR: unknown month:".$s."\n");
	return 13;
}
