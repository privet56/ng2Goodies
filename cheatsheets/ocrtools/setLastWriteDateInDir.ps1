# call: .\setLastWriteDateInDir.ps1 -dir c:\temp\___

param ([string]$dir)    # define & get command line param

$fileCount = 0

Get-ChildItem -Path $dir -File | 
    Foreach-Object {
        $file = Get-Item $_.FullName
        $file.LastWriteTime = (Get-Date)
        Write-Host "LastWriteTime set for ", $_.FullName
        $fileCount++
    }

Write-Host "Finished setting LastWriteTime for ", $fileCount, " files."
