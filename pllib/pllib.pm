#descriptiondescriptiondescriptiondescriptiondescriptiondescriptiondescriptiondescriptiondescription
#a. I should be in "C:\Perl\lib\pllib.pm"
#b. list of the functions:
#1.:    LogBegin(DelOldLog);            begins logging with date if DelOldLog == 1 --> old logfile will be deleted
#2.:    ExitScript();                   ends logging and exits
#3.:    Log(strToLog, MeToo);           appends string "strToLog" to the LOG-File. If MeToo == 1 -> prints "strToLog" to the standard output too
#4.:    GetToday(bForUser);             get date. if(bForUser==0) -> form = "2002.09.19 15:51:41" else -> form = "020919"
#5.:    EntryAlreadyThere(FileName, String);    return 1 if "String" in "FileName" found (do not use Regular expression in "String"!)
#6.:    GetCFG(entry, [CFG-FileName]);      returns value of "entry" from the CFG-File (the same filename + ".cfg" in the same dir, if not specified)
#7.:    AppendToFile(FileName, String);     appends to "FileName" the string "String". returns 1, if successfully
#8.:    NotYetInArray(@Array, String);      returns 0 if "String" already in "@Array", else 1
#9.:    IsFile(FileName);               returns 1 if "FileName" is a valid file
#10.:   GetFN(PathWithFileName, bWithExt);  returns FileName with Extension if bWithExt != 0, else without extension
#11.:   GetDirSize(Path);               returns size of the directory "Path" in Bytes
#12.:   GetFileString(FileName);        returns the content of "FileName"
#13.:   GetExtension(FileName);         returns the extension of "FileName"
#14.:   GetPath(FileNameWithPath);      returns the path-part of "FileNameWithPath"
#15.:   GetFilesFromDir([Path], [Ext1], [Ext2]);returns an array with all files in this directory (with all subdirs) with extensions Ext1 or Ext2 (if specified), if Ext1 and Ext2 are nothing --> returns ALL files in the dir
#16.:   AllTrim(String);                returns a string without leading/trailing whitespaces
#17.:   Maximum(Zahl, Zahl);            returns the higher number
#18.:   Minimum(Zahl, Zahl);            returns the lower number

    #an argument in [...] means, you can leave it empty or ""

#descriptiondescriptiondescriptiondescriptiondescriptiondescriptiondescriptiondescriptiondescription

#usesusesusesusesusesusesusesusesusesusesusesusesusesusesusesusesusesusesusesusesusesusesusesuses
use HTTP::Date;     #to have date-functions
use Time::localtime;    
use Time::gmtime;
use strict;     #force programmer to build code in the right way!
use File::stat;
#usesusesusesusesusesusesusesusesusesusesusesusesusesusesusesusesusesusesusesusesusesusesusesuses

#functionsfunctionsfunctionsfunctionsfunctionsfunctionsfunctionsfunctionsfunctionsfunctionsfunctions
sub LogBegin
{
    my $DelOldLog = $_[0];
    
    my $logFN = $0;         #log-filename
    $logFN =~ s/\.pl/.log/si;
    $logFN = ">".$logFN;
    if($DelOldLog != 1)
    {
        $logFN = ">".$logFN;    #create append-string
    }
    open M_LOG, $logFN;     #open for creating or appending
    print M_LOG "SCRIPT BEGIN ".GetToday(1)."\t------------\n";
    close M_LOG;
}

sub Log
{
    my $logFN = $0;             #log-filename
    $logFN =~ s/\.pl/.log/si;
    my $str = $_[0];
    my $MeToo = $_[1];
    open M_LOG, ">>$logFN";     #open for appending
    print M_LOG "\t".$str."\n";
    close M_LOG;
    
    if($MeToo == 1)
    {
        print "\t".$str."\n";
    }
}

sub ExitScript
{
    my $logFN = $0;             #log-filename
    $logFN =~ s/\.pl/.log/si;
    open M_LOG, ">>$logFN";     #open for appending
    print M_LOG "SCRIPT END ".GetToday(1)."\t\t------------\n\n";
    close M_LOG;
    exit(0);
}

sub GetToday
{
    my $bForUser = $_[0];
    my $tm = localtime;
                            #else for building date like 2002.12.23
    my $jahr = ($tm->year) + 1900;  
    my $monat = ($tm->mon) + 1;
    if((length $monat) == 1)
    {
        $monat = "0".$monat;
    }
    my $tag = $tm->mday;
    if((length $tag) == 1)
    {
        $tag = "0".$tag;
    }   
    my $heute = $jahr.".".$monat.".".$tag;
    if($bForUser ne "1")            #for user
    {
        $heute =~ s/^20//si;
        $heute =~ s/\.//sgi;
        $heute =~ s/\.//sgi;
        return $heute;
    }
    my $hour = $tm->hour;
    if((length $hour) == 1)
    {
        $hour = "0".$hour;
    }       
    my $min = $tm->min;
    if((length $min) == 1)
    {
        $min = "0".$min;
    }       
    my $sec = $tm->sec;
    if((length $sec) == 1)
    {
        $sec = "0".$sec;
    }       
    $heute = $heute." $hour:$min:$sec";
    return $heute;
}

sub EntryAlreadyThere
{
    my $FN = $_[0];
    my $Str = $_[1];
    
    $Str =~ s/\[/\\\[/sgi;
    $Str =~ s/\-/\\\-/sgi;

    if(($FN eq "") or ($Str eq ""))
    {
        Log("\tERROR 1 in function EntryAlreadyThere (FN = \"$FN\"; Str = \"$Str\"), no parameter\n");
        return 0;
    }
    
    if(not(open(_FN, ("<$FN"))))        #open for reading
    {
        Log("\tERROR 2 in function EntryAlreadyThere, could not open $FN\n");
        return 0;   
    }
    my $FS = join "", <_FN>;        #read the whole file in a string
    close _FN;
    if($FS =~ m/$Str/si)
    {
        return 1;
    }
    
    return 0;
}

sub GetCFG
{
    my $entry = $_[0];
    my $cfg = $_[1];
    
    if($cfg eq "")
    {
        $cfg = $0;              #log-filename
        $cfg =~ s/\.pl/.cfg/si;
    }
    
    if($entry eq "")
    {
        Log("\tERROR 1 in function GetCFG, no parameter\n");
        return;
    }
    
    if(not(open(_CFG, ("<$cfg"))))      #open for reading
    {
        Log("\tERROR 2 in function GetCFG \"$cfg\" not found");
        return;
    }
    
    while(<_CFG>)
    {
        my $zeile = $_;
        if($zeile = m/^$entry=(.*?)$/si)
        {
            close _CFG;
            return $1;
        }
    }
    close _CFG;
    
    return "";
}

sub AppendToFile
{
    my $FN = $_[0];
    my $Str = $_[1];
    if(($FN eq "") or ($Str eq ""))
    {
        Log("\tERROR 1 in function AppendToFile (FN = \"$FN\"; Str = \"$Str\"), no parameter\n");
        return 0;
    }
    if(not(open(_FN, (">>$FN"))))       #open for appending
    {
        Log("\tERROR 2 in function AppendToFile, could not open $FN\n");
        return 0;   
    }

    print _FN $Str;
    close _FN;
    return 1;
}

sub NotYetInArray
{
    my @Array = $_[0];
    my $Key = $_[1];
    
    my $element = "";
    
    foreach $element (@Array)
    {
        if($element eq $Key)
        {
            return 0;
        }
    }
    
    return 1;
}

sub IsFile
{
    my $FN = $_[0];
    if(open(FILE, ("<$FN")))        #open for reading
    {
        close FILE;
        return 1;
    }
    return 0;
}

sub GetFN
{
    my $FN = $_[0];             #this is the absolute path to the file  
    my $bWithExt = $_[1];
    $FN =~ s/\//\\/sgi;
    $FN =~ s/.*\\(.*?)$/\1/sgi;
    if($bWithExt != 0)          #return filename with extension
    {   
        return $FN;
    }
    if($FN =~ m/(.*)\.(.*?)$/si)
    {
        return $1;
    }
    return $FN;
}

sub GetDirSize
{
    my $dirpath = $_[0];

    my $size = 0;
    my @erg = `dir \"$dirpath\" /S`;    #show EACH FILE and subdir! #"
    my $ergline = "";
    
    my $blastimportantline = 0;
    my $linezaehler=0;
    my $ergline = "";
    
    foreach $ergline (@erg)
    {       
        if($ergline =~ m/Anzahl der angezeigten Dateien:/si)
        {
            $blastimportantline = 1;
        }
    
        if(($ergline =~ m/(\d+) Datei\(en\)(.*?)Bytes$/si) and ($blastimportantline == 1))
        {
            my $sizeang = $2;
            $sizeang =~ s/\s//sgi;
            $sizeang =~ s/\.//sgi;
            $size = $size + $sizeang;   
            $blastimportantline = 0;
        }
        
        $linezaehler++;
    }
    
    return $size;
}

sub GetFileString
{
    my $FN = $_[0];             #this is the absolute path to the file
    if(open FN, "<$FN")         #open for reading
    {
        my $FS = join "", <FN>;     #read the whole file in a string
        close FN;
        return $FS;
    }
}

sub GetExtension
{
    my $FN = $_[0];             #this is the absolute path to the file
    
    $FN =~ s/\//\\/sgi;
    $FN =~ s/.*\\(.*?)$/\1/sgi;
    
    if($FN =~ m/\.(.*?)$/si)
    {
        return $1;
    }
}

sub GetPath
{
    my $FN = $_[0];             #this is the absolute path to the file  
    $FN =~ s/\//\\/sgi;
    $FN =~ s/(.*)\\.*?$/\1/sgi;
    return $FN;
}

sub GetFilesFromDir
{
    my $VerzToHandle = $_[0];               #this is the absolute path to the file  
    my $Ext1 = $_[1];
    my $Ext2 = $_[2];
    

    if($VerzToHandle eq "")             #if(no parameter) --> work in the current dir
    {
        use Cwd;
        $VerzToHandle = cwd;
    }
    else
    {
        $VerzToHandle =~ s/\//\\/sgi;
        my $davor = $ENV{'PWD'};        #= get current dir
        $davor =~ s/\//\\/sgi;
        #if(current dir != dir want to have) --> change in this dir
        if(($davor ne $VerzToHandle) and ($davor ne ("\"".$VerzToHandle."\"")))
        {
            chdir $VerzToHandle;
            #was this operation successfully?
            my $danach = `chdir`;
            chomp $danach;
            $danach =~ s/\//\\/sgi;

            if($davor eq $danach)
            {
                Log("GetFilesFromDir error\n");
                return;
            }
        }
        else    #= if(currentdir == dir want to have)  --> OK, do nothing more..!
        {
            $VerzToHandle = $davor;
        }
    }
    #part two ... #####################################################################
    my @MySearchFiles = ();
    @MySearchFiles = qw(.) unless @MySearchFiles;
    use File::Find;
    find (\&fill_array, @MySearchFiles);                     #begin reading all the files, dirs and subdirs in the dir $VerzToHandle
    
    my $files_zaehler=0;
    my @FNs;
    sub fill_array                              #reads each file (in subdirs too)
    {   
        my $name = "$File::Find::name";
        $name =~ s/^\.\///g;                        #deletes "./" from the beginning
        $name = lc $name;
        if(($Ext1 eq "") and ($Ext2 eq ""))
        {
            $name =~ s/\//\\/sgi;
            if(not($name =~ m/:\\/si))
            {
                $name = $VerzToHandle."\\".$name;
            }
            chomp $name;
            $FNs[$files_zaehler] = $name;               #save filename to a global array
            $files_zaehler++;       
        }
        elsif(($name =~ m/\.$Ext1$/si) and ($Ext1 ne ""))
        {
            $name =~ s/\//\\/sgi;
            if(not($name =~ m/:\\/si))
            {
                $name = $VerzToHandle."\\".$name;
            }
            chomp $name;
            $FNs[$files_zaehler] = $name;               #save filename to a global array
            $files_zaehler++;
        }
        elsif(($name =~ m/\.$Ext2$/si) and ($Ext2 ne ""))
        {
            $name =~ s/\//\\/sgi;
            if(not($name =~ m/:\\/si))
            {
                $name = $VerzToHandle."\\".$name;
            }
            chomp $name;
            $FNs[$files_zaehler] = $name;               #save filename to a global array
            $files_zaehler++;
        }
    }
    
    return @FNs;
}

sub AllTrim
{
    my $STR = $_[0];                #input string
    
    $STR =~ s/^(\s+|)(.*?)(\s+|)$/$2/si;
    
    return $STR;                    #return trimmed string
}

sub Maximum
{
    if(int($_[0]) > int($_[1]))
    {
        return $_[0];
    }
    
    return $_[1];
}

sub Minimum
{
    if(int($_[0]) < int($_[1]))
    {
        return $_[0];
    }
    
    return $_[1];
}

#functionsfunctionsfunctionsfunctionsfunctionsfunctionsfunctionsfunctionsfunctionsfunctionsfunctions

return 1;