param ([string]$fn)    # define & get command line param
Get-Content $fn -tail 2000 -wait
