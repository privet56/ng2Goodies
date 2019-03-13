set PATH=c:\Program Files (x86)\Tesseract-OCR;%PATH%

rem > one pic:
rem tesseract --tessdata-dir ./tessdata inputpicname.png outputpdffilename PDF
rem > pic-list from text file: (one fn per line, as per created with 'dir /b > pics.txt')
tesseract --tessdata-dir ./tessdata ./pics.txt outputpdffilename PDF

pause
