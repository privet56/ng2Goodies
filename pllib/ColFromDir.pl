#!/usr/bin/perl -w

use strict;
use FindBin;
use File::Copy;
use File::Path;

my $m_sourcepath = "";
my $m_targetfile = "";
my $m_targetdir = "";
my $m_addtorelativepath = "";
my $m_coltitle = "";
my $m_aliasprefix = "";
my $m_kapitelpictopen = "";
my $m_kapitelpictclosed = "";
my $m_docitempictopen = "";
my $m_docitempictclosed = "";
my $m_worditempictopen = "";
my $m_worditempictclosed = "";
my $m_pdfitempictopen = "";
my $m_pdfitempictclosed = "";
my $m_excelitempictopen = "";
my $m_excelitempictclosed = "";
my $m_colpictopen = "";
my $m_colpictclosed = "";
my $m_debug = 0;

GetCFG();

AddLog("ColFromDir wird ausgeführt ".localtime(time)."\n\n");

my $m_destpath = $m_targetdir."\\".ReplaceSZ($m_targetfile)."_Files";
AddLog("Zielverzeichnis fuer Dateien wird geleert...\n\n");
rmtree ($m_destpath);

my $basepath = $m_sourcepath;
my $tofilepath = $m_targetdir."\\".$m_targetfile;
my $alias = "000000";
my $m_itempictopen = "";
my $m_itempictclosed = "";

my @m_folders = ();
my @m_files = ();
my $m_filescount = 0;
my $m_folderscount = 0;

Main();

sub Main
{
	if (open __COL, ">$tofilepath")
	{
		AddLog("Erstelle Collection...\n");
		
		print __COL "<shiip>\n";
		print __COL "<COL imgc=\"misc\\$m_colpictclosed\" imgo=\"misc\\$m_colpictopen\" alias=\"$m_aliasprefix$alias\">\n";
		print __COL "<TITLE>$m_coltitle<\/TITLE>\n";
		DoFolder($basepath, -1, "");
		print __COL "<\/COL>\n";
		print __COL "</shiip>\n";
		close __COL;
		
		AddLog("Collection erstellt.\n\n");
	}
	
	CreateBatch();

	# Links korrigieren:
	@m_folders = ();
	@m_files = ();
	$m_filescount = 0;
	$m_folderscount = 0;
	
	GetFolder($m_sourcepath);

	AddLog("Korrigiere Links...\n\n");
	CorrectLinks($m_targetdir."\\".ReplaceSZ($m_targetfile)."_Files");
	AddLog("Korrektur der Links beendet.\n\n");
	
	AddLog("Korrigiere Datum der neu erstellten Dateien...\n");
	CorrectDates($m_sourcepath, $m_targetdir."\\".ReplaceSZ($m_targetfile)."_Files");
	AddLog("Korrektur der Daten beendet.\n\n");
	
	# HTMLs-Ordner löschen
	rmtree($FindBin::Bin."\\HTMLs");
	
}

sub DoFolder
{
	my $basepath = $_[0]; # base path to start with
	my $bfirst = $_[1]; # indicates if the COL-tag has to be generated (=0). if =-1, no item is being generated
	
	my $title = "__";
	my @files = ();
	my $prepath = $_[2]; # relative path chain to generate a relative doc src
	my $file = "";
	my $docpath = "";
	my $sub = 0;
	my $titlefilestring = "";
	my $doctype = "";
			
	if ($title eq "__")
	{
		$title = $basepath;
		$title =~ s/.*\\([^\\]*$)/$1/;
	}

	if ($bfirst == 0)
	{
		if (uc(substr($title,5,length($title)-5)) eq "SUB")
		{
			$sub = 1;
		}
		else
		{
			$alias++;
			print __COL "<ITEM imgc=\"misc\\$m_kapitelpictclosed\" imgo=\"misc\\$m_kapitelpictopen\" alias=\"$m_aliasprefix$alias\">\n";
		}
	}
	elsif ($bfirst > 0)
	{
		if (uc(substr($title,5,length($title)-5)) eq "SUB")
		{
			$sub = 1;
		}
		else
		{
			$alias++;
			print __COL "<ITEM imgc=\"misc\\$m_kapitelpictclosed\" imgo=\"misc\\$m_kapitelpictopen\" alias=\"$m_aliasprefix$alias\">\n";		
		}
	}
	
	if ($bfirst >= 0)
	{
		$title=substr($title,5,length($title)-5); # Die ersten Zeichen abschneiden ("001- " etc.)
		if ($sub == 0)
		{
			# Prüfen, ob File mit Titel vorhanden
			if (open(TITLEFILE, "<".$basepath."\.txt"))
			{
				$titlefilestring="";
				while(! eof(TITLEFILE))
				{
					$titlefilestring = $titlefilestring.getc(TITLEFILE);
				}
				
				# Wagenrücklauf und Zeilenvorschub ersetzen
				$titlefilestring =~ s/\r|\n//isg;
				
				$title = $titlefilestring;
			}
			print __COL "<TITLE>".$title."</TITLE>\n";
		}
	}

	# proceed the folder hierarchy and documents
	if (opendir __TEMP, $basepath)
 	{
		@files = readdir __TEMP;
		foreach $file (@files)
		{
			if ($file ne "." and $file ne "..")
			{
				if (open __F, "<".$basepath."\\".$file) # file
				{
					if(CheckFileType(GetFileType($file)))
					{
						SetPict(GetFileType($file));
						
						$alias++;
						print __COL "<ITEM imgc=\"misc\\$m_itempictclosed\" imgo=\"misc\\$m_itempictopen\" alias=\"$m_aliasprefix$alias\">\n"  if ($sub == 1);
						$title = $file;
						$title =~ s/&sect;/§/is;
						
						# Pfad anlegen und File kopieren
						$docpath = RelPath($basepath);
						mkpath ($m_destpath."\\".ReplaceSZ($docpath));
						copy ($basepath."\\".$file, $m_destpath."\\".ReplaceSZ($docpath)."\\Gen.".ReplaceSZ($file));					
						
						# Nummer am Anfang abschneiden
						$title =~ s/^[0-9]+ *- *(.*)/$1/;
						$title = CutEnd($title);

						# Prüfen, ob File mit Titel vorhanden
						if (open(TITLEFILE, "<".$basepath."\\".$file."\.txt"))
						{
							$titlefilestring = "";
							while(! eof(TITLEFILE))
							{
								$titlefilestring = $titlefilestring.getc(TITLEFILE);
							}

							# Wagenrücklauf und Zeilenvorschub ersetzen
							$titlefilestring =~ s/\r|\n//isg;

							$title = $titlefilestring;
						}
						
						print __COL "\t<TITLE>".$title."</TITLE>\n" if ($sub == 1);

						# generate doc
						$docpath = ReplaceSZ($m_targetfile)."_Files"."\\".ReplaceSZ($docpath)."\\Gen.".ReplaceSZ($file);
						if ($m_addtorelativepath ne "")
						{
							$docpath = $m_addtorelativepath."\\".$docpath;
						}
						$doctype = GetDocType($basepath."\\".$file);
						print __COL "\t<DOC type=\"$doctype\" language=\"D\" src=\"$docpath\" \/>\n";
						print __COL "</ITEM>\n" if ($sub == 1);
					}
					elsif (! ($file =~ /\.txt$/is))
					{
						#Pfad anlegen und File kopieren
						$docpath = RelPath($basepath);
						mkpath ($m_destpath."\\".ReplaceSZ($docpath));
						copy ($basepath."\\".$file, $m_destpath."\\".ReplaceSZ($docpath)."\\".$file);
					}
										
				}
				else # subfolder
				{
					
				
					if ($prepath eq "")
					{
						DoFolder($basepath."\\".$file, $bfirst + 1, $file);
					}
					else
					{
						DoFolder($basepath."\\".$file, $bfirst + 1, $prepath."\\$file");
					}
				}
			}
		}

		closedir __TEMP;
	}

	if ($bfirst == 0)
	{
		if ($sub == 0)
		{
			print __COL "</ITEM>\n";
		}
	}
	elsif ($bfirst > 0)
	{
		if ($sub == 0)
		{
			print __COL "</ITEM>\n";
		}
	}
	
}

sub GetDocType
{
	my $originalpath = shift;
	
	my $filetype = "";
	my $meta = "";
	my $doctype = "";
	
	# Dateinamenerweiterung bekommen
	$filetype = uc($1) if($originalpath =~ /.*\.(.*)/);
	
	# Nach Dateinamenerweiterung unterscheiden
	
	if($filetype eq "HTM" || $filetype eq "HTML")
	{
		# Meta aus Originalfile holen
		$meta = uc(GetMetaContent($originalpath, "Kategorie"));
	}
	elsif($filetype eq "DOC" || $filetype eq "XLS")
	{
		# Meta aus vom WordMakro erzeugtem HTML-File holen
		$meta = uc(GetMetaContent($FindBin::Bin."\\HTMLs".substr($originalpath, length($m_sourcepath)), "Kategorie"));
	}
	elsif($filetype eq "")
	{
		# Fehler
		AddLog("Fehler: GetDocType: Konnte FileType nicht bekommen. Datei: $originalpath\n\n");
	}
	
	
	# Nach Meta unterscheiden
	
	if($meta eq "VERTRäGE" || $meta eq "VERTRAG" || $meta eq "VERTRÄGE")
	{
		$doctype = "v";
	}
	elsif($meta eq "MUSTER")
	{
		$doctype = "m";
	}
	elsif($meta eq "CHECKLISTEN" || $meta eq "CHECKLISTE")
	{
		$doctype = "c";
	}
	elsif($meta eq "TABELLE" || $meta eq "TABELLEN")
	{
		$doctype = "t";
	}
	elsif($meta eq "MUSTERBRIEFE" || $meta eq "MUSTERBRIEF")
	{
		$doctype = "b";
	}
	else
	{
		$doctype = "Standard";
	}
	
	return($doctype);
}

sub GetMetaContent
{
	my $file = shift;
	my $metaname = shift;
	
	# Holt aus dem übergebenen Dateinamen den Content des übergebenen Metas
	
	my $metacontent = "";
	my @filelines = "";
	my $filestring = "";
	
	if(open(FILE, "<".$file))
	{
		# File einlesen
		@filelines = <FILE>;
		$filestring = "";
		foreach(@filelines)
		{
			$filestring = $filestring.$_;
		}
		
		# Meta suchen
		if($filestring =~ /<\s*meta\s*name=\"Kategorie\"\s*content=\"(.*?)\"/igs)
		{
			$metacontent = $1 
		}
		else
		{
			$metacontent = "ERROR";
			AddLog("Fehler: GetMetaContent: Konnte Meta '$metaname' nicht finden. Datei: $file\n");
		}
	}
	else
	{
		$metacontent = "ERROR";
		AddLog("Fehler: GetMetaContent: Konnte Datei nicht öffnen. Datei: $file\n");
	}
	
	return($metacontent);
}

sub CutEnd 
{
	# Schneidet die Dateiendung ab

	my $string = shift;
	my $i = 0;
	
	for ($i = (length($string)-1); $i >= 0; $i--)
	{
		if (substr($string, $i, 1) eq ".")
		{
			last;
		}
	}

	if ($i >= 0)
	{
		$string = substr($string, 0, $i);
	}
	
	return ($string);
}

sub CreateBatch
{
	my $mypath = $FindBin::Bin;
	for (my $i = 0; $i <= length($mypath); $i++)
	{
		if (substr($mypath, $i, 1) eq "\/")
		{
			$mypath = substr($mypath, 0, $i)."\\".substr($mypath, $i + 1, length($mypath) - ($i + 1));
		}
	}
		
	open(BATCH, ">$FindBin::Bin\/IPView.bat");
	
	print BATCH "$mypath\\IPView\\IPView.exe $m_targetdir\\$m_targetfile";
	
	close(BATCH);
}

sub RelPath
{
	my $path = shift;
	my $relpath = "";
	
	$path = $path."\\";
	
	if (length($path) >= length($m_sourcepath))
	{
		$relpath = substr($path, length($m_sourcepath) + 1, length($path) - length($m_sourcepath));
	}

	$relpath = substr($relpath, 0, length($relpath) - 1);
	
	return($relpath);
}

sub SchneidAb
{
	#Schneidet Leerzeichen am Ende ab
	my $string = shift;
	
	while (substr($string, length($string) - 1, 1) eq " ")
	{
		$string = substr($string, 0, length($string) - 1);
	}
	
	return $string;
}

sub CutBS
{
	# Schneidet Backslashes am Ende ab
	my $string = shift;
	
	while (substr($string, length($string) - 1, 1) eq "\\")
	{
		$string = substr($string, 0, length($string) - 1);
	}
	
	return($string);
}

sub GetFileType
{
	my $filename = shift;

	# Gibt die Dateiendung zurück
	
	$filename =~ /.*\.(.*)/;
	
	return (uc($1));	
}

sub CheckFileType
{
	# Prüft, ob Datei verarbeitet werden soll
	
	my $filetype = shift;
	
	if ((uc($filetype) eq "HTM") || (uc($filetype) eq "HTML") || (uc($filetype) eq "DOC") || (uc($filetype) eq "PDF") || (uc($filetype) eq "RTF") || (uc($filetype) eq "XLS"))
	{
		return(1);
	}
	else
	{
		return(0);
	}
}

sub SetPict
{
	my $filetype = shift;
	
	$m_itempictopen = "";
	$m_itempictclosed = "";

	if (uc($filetype) eq "DOC")
	{
		$m_itempictopen = $m_worditempictopen;
		$m_itempictclosed = $m_worditempictclosed;
	}
	elsif (uc($filetype) eq "PDF")
	{
		$m_itempictopen = $m_pdfitempictopen;
		$m_itempictclosed = $m_pdfitempictclosed;
	}
	elsif (uc($filetype) eq "XLS")
	{
		$m_itempictopen = $m_excelitempictopen;
		$m_itempictclosed = $m_excelitempictclosed;
	}
	
	if ($m_itempictopen eq "")
	{
		$m_itempictopen = $m_docitempictopen;
	}

	if ($m_itempictclosed eq "")
	{
		$m_itempictclosed = $m_docitempictclosed;
	}
}

sub ReplaceSZ
{
	my $strString = shift;
	
	my $strNewString = $strString;
	
	$strNewString =~ s/ /_/g;
	$strNewString =~ s/é/e/g;
	$strNewString =~ s/è/e/g;
	$strNewString =~ s/ê/e/g;
	$strNewString =~ s/É/E/g;
	$strNewString =~ s/È/E/g;
	$strNewString =~ s/Ê/E/g;
	$strNewString =~ s/á/a/g;
	$strNewString =~ s/à/a/g;
	$strNewString =~ s/â/a/g;
	$strNewString =~ s/Á/A/g;
	$strNewString =~ s/À/A/g;
	$strNewString =~ s/Â/A/g;
	$strNewString =~ s/í/i/g;
	$strNewString =~ s/ì/i/g;
	$strNewString =~ s/î/i/g;
	$strNewString =~ s/Í/I/g;
	$strNewString =~ s/Ì/I/g;
	$strNewString =~ s/Î/I/g;
	$strNewString =~ s/ô/o/g;
	$strNewString =~ s/Ô/O/g;
	$strNewString =~ s/ç/c/g;
	$strNewString =~ s/Ç/C/g;
	$strNewString =~ s/ß/ss/g;
	$strNewString =~ s/ú/u/g;
	$strNewString =~ s/ù/u/g;
	$strNewString =~ s/û/u/g;
	$strNewString =~ s/Ú/U/g;
	$strNewString =~ s/Ù/U/g;
	$strNewString =~ s/Û/U/g;
	$strNewString =~ s/Œ/OE/g;
	$strNewString =~ s/æ/ae/g;
	$strNewString =~ s/Æ/AE/g;
	$strNewString =~ s/œ/oe/g;
	$strNewString =~ s/'/-/g;
	$strNewString =~ s/ä/ae/g;
	$strNewString =~ s/Ä/Ae/g;
	$strNewString =~ s/ü/ue/g;
	$strNewString =~ s/Ü/Ue/g;
	$strNewString =~ s/ö/oe/g;
	$strNewString =~ s/Ö/Oe/g;
	$strNewString =~ s/,/-/g;
	$strNewString =~ s/«//g;
	$strNewString =~ s/»//g;
	$strNewString =~ s/"//g;
	
	return ($strNewString);
}

sub CorrectLinks
{
	my $path = shift;
	
	my @tempfiles = ();
	my $file = "";
	my $filestring = "";
	my $searchstring = "";
	my $replacestring = "";
	my $element = "";
	my $pos = -1;
	
	if (opendir FOLDER, $path)
	{
		@tempfiles = readdir FOLDER;
		
		foreach $file (@tempfiles)
		{
			if ($file ne "." and $file ne "..")
			{
				
				#Prüfen, ob Datei oder Verzeichnis
				if (open FILE, "<".$path."\\".$file)
				{
					if ((uc(GetFileType($file)) eq "HTM") || (uc(GetFileType($file)) eq "HTML"))
					{
						AddLog("Korrigiere Links in Datei $path\\$file...\n");
						$filestring = ReadFile($path."\\".$file);
						
						$filestring = ReplaceSZinHTML($filestring);
						
						foreach $element (@m_files)
						{							
							$searchstring = $element;
							$replacestring = "Gen.".ReplaceSZinHTML(ReplaceSZ($searchstring));
							$searchstring = ReplaceSZinHTML($searchstring);
							$filestring =~ s/(<a[^>]+?href\s*?=\s*?"[^"]*?)$searchstring(.*?".*?>)/$1$replacestring$2/isg;
						}
						
						foreach $element (@m_folders)
						{
							$searchstring = $element;
							$replacestring = ReplaceSZinHTML(ReplaceSZ($searchstring));
							$searchstring = ReplaceSZinHTML($searchstring);
							$filestring =~ s/(<a[^>]+?href\s*?=\s*?"[^"]*?)$searchstring(.*?".*?>)/$1$replacestring$2/isg;
						}
						
						close FILE;
						
						AddLog("Korrektur der Datei beendet.\n\n");
						
						if (open FILE, ">".$path."\\".$file)
						{
							print FILE $filestring;
						}
					}
					close FILE;
				}
				else
				{
					CorrectLinks($path."\\".$file);
				}
			}

		}
	}

}

sub ReadFile
{
	# Liest eine Datei Zeichen für Zeichen aus und gibt einen
	# String zurück, die ganze Datei enthält
	my $file = shift;
	my $filestring = "";
	my @zeilen = ();
	
	if (open FILE, "<".$file)
	{
		@zeilen = <FILE>;
		
		foreach(@zeilen)
		{
			$filestring = $filestring.$_;
		}
		
		#while (! eof(FILE))
		#{
		#	$filestring = $filestring.getc(FILE);
		#}
		
		close FILE;
	}
	
	return($filestring);
}

sub GetFolder
{
	my $path = shift;
	my @tempfiles = ();
	my $file = "";
	
	if (opendir FOLDER, $path)
	{
		@tempfiles = readdir FOLDER;
		
		foreach $file (@tempfiles)
		{
			if ($file ne "." and $file ne "..")
			{
				
				#Prüfen, ob Datei oder Verzeichnis
				if (open FILE, "<".$path."\\".$file)
				{
					close FILE;
					$m_files[$m_filescount] = $file;
					$m_filescount++;
				}
				else
				{
					$m_folders[$m_folderscount] = $file;
					$m_folderscount++;
					GetFolder($path."\\".$file);
				}
			}

		}
	}
}

sub ReplaceSZinHTML
{
	# Ersetzt Sonderzeichen HTML-gerecht.
	
	my $string = shift;
	
	$string =~ s/Á/&Aacute;/g;
	$string =~ s/À/&Agrave;/g;
	$string =~ s/Â/&Acirc;/g;
	$string =~ s/á/&aacute;/g;
	$string =~ s/à/&agrave;/g;
	$string =~ s/â/&acirc;/g;
	$string =~ s/É/&Eacute;/g;
	$string =~ s/È/&Egrave;/g;
	$string =~ s/Ê/&Ecirc;/g;
	$string =~ s/é/&eacute;/g;
	$string =~ s/è/&egrave;/g;
	$string =~ s/ê/&ecirc;/g;
	$string =~ s/Í/&Iacute;/g;
	$string =~ s/Ì/&Igrave;/g;
	$string =~ s/Î/&Icirc;/g;
	$string =~ s/í/&iacute;/g;
	$string =~ s/ì/&igrave;/g;
	$string =~ s/î/&icirc;/g;
	$string =~ s/Ô/&Ocirc;/g;
	$string =~ s/ô/&ocirc;/g;
	$string =~ s/Ú/&Uacute;/g;
	$string =~ s/Ù/&Ugrave;/g;
	$string =~ s/Û/&Ucirc;/g;
	$string =~ s/ú/&uacute;/g;
	$string =~ s/ù/&ucirc;/g;
	$string =~ s/û/&ugrave;/g;
	$string =~ s/Ä/&Auml;/g;
	$string =~ s/ä/&auml;/g;
	$string =~ s/Ö/&Ouml;/g;
	$string =~ s/ö/&ouml;/g;
	$string =~ s/Ü/&Uuml;/g;
	$string =~ s/ü/&uuml;/g;
	$string =~ s/ß/&szlig;/g;
	$string =~ s/Ç/&Ccedil;/g;
	$string =~ s/ç/&ccedil;/g;
	$string =~ s/Æ/&AElig;/g;
	$string =~ s/æ/&aelig;/g;
	$string =~ s/«/&laquo;/g;
	$string =~ s/»/&raquo;/g;
	
	return $string;
}

sub CorrectDates
{
	my $oldpath = shift;
	my $newpath = shift;
	
	my @oldfiles = ();
	my @newfiles = ();
	
	# Zwei Listen mit Äquivalenten Dateien erstellen:
	# $oldfiles[0] => $newfiles[0]
	GetEqualFiles($oldpath, $oldpath, \@oldfiles, \@newfiles);
	
	# Datum setzen
	for(my $i = 0; $i <= $#oldfiles; $i++)
	{
		SetFileDate($newpath."\\".$newfiles[$i], GetFileDate($oldpath."\\".$oldfiles[$i]));
	}
}

sub SetFileDate
{
	my $file = shift;
	my $date = shift;
	
	unless($date < 0)
	{
		# Datum setzen
		AddLog("FEHLER: SetFileDate: Konnte Datum in Datei '$file' nicht setzen!\n") unless utime($date, $date, $file)
	}
}

sub GetFileDate
{
	my $file = shift;
	
	my @stats = ();
	my $date = 0;
	
	(@stats = stat($file)) ? ($date = $stats[9]) : ($date = -1);
	
	AddLog("FEHLER: GetFileDate: Konnte Datum von Datei '$file' nicht bekommen!\n") if($date < 0);
	
	return ($date);
}

sub GetEqualFiles
{
	my $oldpath = shift;
	my $recpath = shift; # Pfad, der zur Rekursion benutzt wird, denn $oldpath muss erhalten bleiben
	my $oldfilesp = shift;
	my $newfilesp = shift;
	
	my @tempfiles = ();
	my $file = "";
	my $relpath = "";
	
	opendir (FOLDER, $recpath) || AddLog("FEHLER: GetEqualFiles: recpath konnte nicht geöffnet werden!");
	@tempfiles = readdir FOLDER;

	foreach $file (@tempfiles)
	{
		if ($file ne "." and $file ne "..")
		{
			#Prüfen, ob Datei oder Verzeichnis
			if (open FILE, "<".$recpath."\\".$file)
			{
				if ($file =~ /\.htm$|\.html$/i)
				{
					# Dateiname mit Pfad relativ zu $oldpath speichern
					$relpath = GetRelPath($oldpath, $recpath)."\\".$file;
					push(@{$oldfilesp}, $relpath);
					
					# Neuen Dateinamen erzeugen und speichern
					($relpath =~ s/(.*)/Gen\.$1/i) unless ($relpath =~ s/(.*)\\(.*)/$1\\Gen\.$2/i);
					push(@{$newfilesp}, ReplaceSZ($relpath));
				}
				close FILE;
			}
			else
			{
				GetEqualFiles($oldpath, $recpath."\\".$file, $oldfilesp, $newfilesp);
			}
		}

	}
}

sub GetRelPath
{
	my $targetpath = shift;
	my $abspath = shift;
	
	# Erwartet absoluten Zielpfad und absoluten Pfad als Übergabeparamter
	# Gibt zurück den absoluten Pfad vom Zielpfad aus zu dem absoluten Pfad
	
	my $targetdrive = "";
	my $absdrive = "";
	my $newpath = "";
	my @targetdirs = ();
	my @absdirs = ();
	my @newdirs = ();
	my $dirsanz = 0;
	my $difpos = 0;
	my $i = 0;
	
	# Prüfen, ob Pfade in gleichem Laufwerk, ansonsten absoluten Pfad beibehalten
	$targetdrive = $1 if ($targetpath =~ /(^[A-Z]:)/i) || ($targetpath =~ /^\\\\(.*?)\\/i);
	$absdrive = $1 if ($abspath =~ /(^[A-Z]:)/i) || ($abspath =~ /^\\\\(.*?)\\/i);
	
	if (uc($targetdrive) ne uc($absdrive))
	{
		$newpath = $abspath;
	}
	else
	{
		@targetdirs = split(/\\/, $targetpath);
		@absdirs = split(/\\/, $abspath);
		
		# Feststellen, bis wohin die Ordner noch übereinstimmen
		(@targetdirs < @absdirs) ? ($dirsanz = @targetdirs) : ($dirsanz = @absdirs);
		
		for ($i = 0; $i < $dirsanz; $i++)
		{
			last if (uc($targetdirs[$i]) ne uc($absdirs[$i]));
		}
		
		$difpos = $i;
		
		# Vom Zielpfad bis zu dieser Stelle gelangen
		for ($i = @targetdirs - 1; $i >= $difpos; $i--)
		{
			push(@newdirs, "..");	
		}

		# Restliche Pfade anhängen
		for ($i = $difpos; $i < @absdirs; $i++)
		{
			push(@newdirs, $absdirs[$i]);
		}
		
		$newpath = join("\\", @newdirs);
	}
	
	return($newpath);
}

sub AddLog
{
	my $logstring = shift;
	
	if($m_debug == 1)
	{	
		open(LOG, ">>".$FindBin::Bin."\/ColFromDir.log");

		print LOG "$logstring";

		close(LOG);
	}
	
	print "$logstring";
}

sub GetAbsPath
{
	my $abspath = shift;
	my $relpath = shift;
		
	# Erwartet zwei Pfade als Parameter:
	# einen absoluten und einen relativen von diesem ersten Pfad aus gesehen
	# Gibt zurück den absoluten Pfad zu dem übergebenen relativen.
	
	my @absdirs = ();
	my @reldirs = ();
	my @newdirs = ();
	my $newpath = "";
	
	# Wenn $relpath kein absoluter Pfad ist
	unless ($relpath =~ /^\\\\|^[A-Z]:/i)
	{
		$relpath =~ s/^\\(.*)/$1/g; # Führende Backslashes abschneiden

		@absdirs = split(/\\/, $abspath);
		@reldirs = split(/\\/, $relpath);
		@newdirs =  @absdirs;
		
		# Die relativen Pfade an absoluten anhängen
		# bzw. löschen, wenn ".."
		foreach(@reldirs)
		{
			$_ eq ".." ? pop(@newdirs) : push(@newdirs, $_);
		}
		
		$newpath = join("\\", @newdirs);
	}
	else
	{
		$newpath = $relpath;
	}
	
	return($newpath);
}

sub GetCFG
{
	
	my $string = "";
	my $char = "";
	my $vorne = "";
	my $hinten = "";
	my $pos = 0;
	my $binpath = "";
	
	$binpath = $FindBin::Bin;
	$binpath =~ s/\//\\/g;	
	
	open(CFG, $FindBin::Bin."\/ColFromDir.cfg") || die "Konfigurationsdatei 'ColFromDir.cfg' nicht gefunden!";
	
	while (! eof(CFG))
	{
		$char = getc(CFG);
		$string = $string.$char;
		if (($char eq "\n") || (eof(CFG)))
		{
			if ($char eq "\n")
			{
				$string = substr($string, 0, length($string) - 1);
			}
			$pos = index($string, "=");
			if ($pos > 0)
			{
				$vorne = substr($string, 0, $pos);
				$hinten = substr($string, $pos + 1, length($string)-($pos + 1));
				
				if (uc($vorne) eq "SOURCEPATH")
				{
					$m_sourcepath = SchneidAb($hinten);
					$m_sourcepath = GetAbsPath($binpath, $m_sourcepath);
				}
				elsif (uc($vorne) eq "ALIASPREFIX")
				{
					$m_aliasprefix = SchneidAb($hinten);
				}
				elsif (uc($vorne) eq "TARGETFILE")
				{
					$m_targetfile = SchneidAb($hinten);
				}
				elsif (uc($vorne) eq "KAPITELPICTOPEN")
				{
					$m_kapitelpictopen = SchneidAb($hinten);
				}
				elsif (uc($vorne) eq "KAPITELPICTCLOSED")
				{
					$m_kapitelpictclosed = SchneidAb($hinten);
				}
				elsif (uc($vorne) eq "DOCITEMPICTOPEN")
				{
					$m_docitempictopen = SchneidAb($hinten);
				}
				elsif (uc($vorne) eq "DOCITEMPICTCLOSED")
				{
					$m_docitempictclosed = SchneidAb($hinten);
				}
				elsif (uc($vorne) eq "ADDTORELATIVEPATH")
				{
					$m_addtorelativepath = SchneidAb($hinten);
				}				
				elsif (uc($vorne) eq "TARGETDIR")
				{
					$m_targetdir = SchneidAb($hinten);
					$m_targetdir = GetAbsPath($binpath, $m_targetdir);
				}
				elsif (uc($vorne) eq "WORDITEMPICTOPEN")
				{
					$m_worditempictopen = SchneidAb($hinten);
				}
				elsif (uc($vorne) eq "WORDITEMPICTCLOSED")
				{
					$m_worditempictclosed = SchneidAb($hinten);
				}
				elsif (uc($vorne) eq "PDFITEMPICTOPEN")
				{
					$m_pdfitempictopen = SchneidAb($hinten);
				}
				elsif (uc($vorne) eq "PDFITEMPICTCLOSED")
				{
					$m_pdfitempictclosed = SchneidAb($hinten);
				}				
				elsif (uc($vorne) eq "EXCELITEMPICTOPEN")
				{
					$m_excelitempictopen = SchneidAb($hinten);
				}
				elsif (uc($vorne) eq "EXCELITEMPICTCLOSED")
				{
					$m_excelitempictclosed = SchneidAb($hinten);
				}
				elsif (uc($vorne) eq "COLTITLE")
				{
					$m_coltitle = SchneidAb($hinten);
				}
				elsif (uc($vorne) eq "COLPICTOPEN")
				{
					$m_colpictopen = SchneidAb($hinten);
				}
				elsif (uc($vorne) eq "COLPICTCLOSED")
				{
					$m_colpictclosed = SchneidAb($hinten);
				}
				elsif (uc($vorne) eq "DEBUG")
				{
					$m_debug = SchneidAb($hinten);
				}
				
			}
			
			$string = "";	
		}
	}
	
	close(CFG);
	
	# Backslashes am Ende abschneiden
	$m_sourcepath = CutBS($m_sourcepath);
	$m_addtorelativepath = CutBS($m_addtorelativepath);
	$m_targetdir = CutBS($m_targetdir);
	
	# Prüfen, ob alle wichtigen Paramter gesetzt:
	
	if ($m_sourcepath eq "")
	{
		die "FEHLER: Es wurde kein Quellpfad angegeben.";
	}
	elsif ($m_targetfile eq "")
	{
		die "FEHLER: Es wurde keine Zieldatei angegeben.";
	}
	elsif ($m_targetdir eq "")
	{
		die "FEHLER: Es wurde kein Zielpfad angegeben.";
	}
}