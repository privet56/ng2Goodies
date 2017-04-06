use shilib;

LogBegin(0);
Log("I do something...!");
GetCFG("hallo");
$tempfn = "c:\\temp\\SOF61.tmp";

Log("SIZE of temp: ".GetDirSize("c:\\temp"));
Log("I do something again!", 1);

Log("get extension of $tempfn: ".GetExtension($tempfn));
Log("get FileName of $tempfn: ".GetFN($tempfn));
Log("get Path of $tempfn: ".GetPath($tempfn));


@FN = GetFilesFromDir("c:\\temp", "gif");

foreach $filename (@FN)
{
	Log("found file: ".$filename);
}


ExitScript();