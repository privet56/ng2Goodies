set PATH=c:\programs\gs9.25;c:\programs\gs9.25\bin;%PATH%

gswin64.exe -q -sDEVICE=png16m -dBATCH -dNOPAUSE -r300 -sOutputFile=RAP-for-Java-Developers-Slides_page%%03d_page.png "RAP for Java Developers-Slides.pdf"

pause
