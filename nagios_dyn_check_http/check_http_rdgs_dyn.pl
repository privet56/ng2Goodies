#!/usr/bin/perl
# nagios: -epn

use strict;
use warnings;

use File::Basename;
use IPC::Open3;
use IO::Select;

####
# 0. precondition: perl library LWP (e.g. 'yum install perl-libwww-perl')
# 1. nagios command name = /usr/local/nagios/libexec/check_http
# 2. params = params of the command without URL (URL will be APPENDED) AND an additional LAST parameter: URL for asking for the port of the prod system (http://mchp486a.global-intra.net/prod/sss/port/)
#	http://172.30.66.110/ReportServer?%2fProd%2fSMO%2fServices_BOM				&rs:Command=GetDataSourceContents
#	http://172.30.66.110/ReportServer?%2fclusterb%2fProd%2fSMO%2fServices_BOM	&rs:Command=GetDataSourceContents
#	ntlm authenticator:
#	http://mchp486a.global-intra.net:8080/cgi-bin/get_ntlm.cgi?check4smo:GQm85mBNxC%20http://172.30.66.110:80/ReportServer?</clusterb>/Prod/SMO/Services_BOM
####

# nagios command definition should specify the perl interpreter (/usr/bin/perl)
# 'Return code of 13 is out of bounds' -> check security settings (13 = EACCESS = 'Permission denied')

local $| = 1;

my $debug = 0;

sub dbg($)
{
	if($debug != 1){ return; }
	my $s = shift(@_);
	my $filename = '/usr/local/nagios/libexec/'.basename($0, ".pl").'.log';
	open(my $fh, '>>', $filename) or die "Could not open file '$filename' $!";
	print $fh $s;
	close $fh;
}
sub get_port($)
{
	my $url = shift(@_);
	
	use LWP::UserAgent;
	 
	my $ua 	= LWP::UserAgent->new;
	my $req = HTTP::Request->new(GET => $url);
	my $resp= $ua->request($req);
	
	if ($resp->is_success)
	{
	    return trim($resp->decoded_content);
	}
    dbg("HTTP GET error code:".$resp->code." msg:".$resp->message."\n");
    return "";
}
sub get_url2check($)
{
	my $port = trim(shift(@_));
	if($port eq "9080")
	{
		return "http://172.30.66.110/ReportServer?%2fclusterb%2fProd%2fSMO%2fServices_BOM";
	}
	if($port eq "8080")
	{
		return "http://172.30.66.110/ReportServer?%2fProd%2fSMO%2fServices_BOM";
	}
	dbg("get_url2check ERR: unknown port: '".$port."'\n");
	return "";
}
sub trim
{
  my $string = shift;
  for ($string)
  {
    s/^\s+//;
    s/\s+$//;
  }
  return $string;
}
sub get_args(@)	# *NIX only
{
	my $re = "";
	foreach my $param (@_)
	{
		if(($param =~ /^\-/) or ($param =~ /^\'/))
		{
			$re .= " ".$param;
		}
		elsif($param =~ /\W/)
		{
			$re .= " '".$param."'";
		}
		else
		{
			$re .= " ".$param;
		}
	}
	return trim($re);
}
my $cmd_name= '/usr/local/nagios/libexec/check_http';
my $port 	= get_port(pop @ARGV);
my $url2check=get_url2check($port);
my $cmd_args= get_args(@ARGV) . " '" . $url2check."'";
my $cmd 	= $cmd_name ." ".$cmd_args;

dbg("cmd: '$cmd'\n");

my $stdout = `$cmd`;
my $exit_value = $? >> 8;

dbg("result:\n-----------------------\n$stdout\n-----------------------\nexit_value: $exit_value\n");

print $stdout;

exit($exit_value);
