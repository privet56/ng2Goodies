#!/usr/bin/perl

use strict;
use warnings;

use File::Basename;
use IPC::Open3;
use IO::Select;

####
# 0. precondition: perl library LWP (e.g. 'yum install perl-libwww-perl')
# 1. script name = command name (e.g. check_http)
# 2. params = params of the command without port (port will be APPENDED) AND an additional LAST parameter: URL for asking for the port
#	http://mchp486a.global-intra.net:8080/prod/sss/port/		#prod-rc
#	http://mchp486a.global-intra.net/prod/sss/port/				#prod
#	http://mchp484a.global-intra.net/prod/sss/port/				stage
# 3. command has to be found in PATH (if not working, then script will be changed: prepend ./)
####

local $| = 1;

my $debug = 0;

sub get_port($)
{
	my $url = shift(@_);
	
	use LWP::UserAgent;
	 
	my $ua 	= LWP::UserAgent->new;
	my $req = HTTP::Request->new(GET => $url);
	my $resp= $ua->request($req);
	
	if ($resp->is_success)
	{
	    return $resp->decoded_content;
	}
    if($debug == 1) { print "HTTP GET error code:", $resp->code, " msg:", $resp->message, "\n"; }
    return "";
}

my $cmd_name= basename($0, ".pl");
my $port 	= get_port(pop @ARGV);
my $cmd_args= join(" ", @ARGV) . " " . $port;
my $cmd 	= $cmd_name ." ".$cmd_args;

if($debug == 1) { print "cmd: '$cmd'\n"; }

my $stdout = `$cmd`;
my $exit_value = $? >> 8;

if($debug == 1) { print "result:\n-----------------------\n$stdout\n-----------------------\nexit_value: $exit_value\n"; }

print $stdout;

exit($exit_value);
