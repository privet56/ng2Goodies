# Excel formulas in German

## Docs
### Excel formulas list:
https://support.microsoft.com/en-us/office/excel-functions-alphabetical-b3944572-255d-4efb-bb96-c6d90033e188
### Excel formula translations:
https://excelhero.de/excel-funktionen-deutsch-englisch/

## Common calculations
>=MITTELWERT(B:B)           # mean<br>
>=ANZAHL(B:B)               # count<br>
>=ZÄHLENWENN(B:B;"<55")     # count values under 55<br>
>=(ZÄHLENWENN(B:B;"<55")/ANZAHL(B:B))*100 # calc ratio in percent<br>

## Link to a value in another excel file:
> =[BehandlungenProWoche.xlsx]KW29!$A$2

## Link to a value in another sheet of the same file:
> ='Sheet2'!A2

## Sum of values
> =SUMME(A6:G6)

## Count number of non-empty values
> =ZÄHLENWENN(A6:G6;"<>"&"")

## List non-empty unique values in an area (several columns!):
> =SORTIERENNACH(EINDEUTIG(FILTER(ZUSPALTE(C4:I21); ZUSPALTE(C4:I21)<>"")); ZÄHLENWENN(C4:I21; EINDEUTIG(FILTER(ZUSPALTE(C4:I21); ZUSPALTE(C4:I21)<>""))); -1)

**ATTENTION:** Excel 2016 doesn't understand FILTER

## Find value in an area
> find value in B16 in the area 'KW30'!B$16:B33<br>
> =VERGLEICH(B16;'KW30'!B$16:B33;0)

## Find value of a string-based cell address
> find value in "KW30!D" + (value-of-C16 + 15)<br>
> =INDIREKT("KW30!D" & (WERT(C16) + 15))

## Add values or set 0 (if error)
> =WENNFEHLER(SUMME(D16;E16); 0)

## Get first day (=monday) of a calendar week
$D$13 = year (eg. 2023)<br>
$C$13 = calendar week (eg. 32)<br>
put in B1:
> =MAX(DATUM($D$13;1;1);DATUM($D$13;1;1)-WOCHENTAG(DATUM($D$13;1;1);2)+($C$13)*7 + 1)<br>
> =B1+1 # = next day (=Tuesday)

# Open Office Calc (*.ods)
https://wiki.openoffice.org/wiki/Documentation/How_Tos/Calc:_Functions_listed_alphabetically

Calc has a slightly different syntax for formulas. Here the most important differences:
1. Sheet/Cell separator is not '!' but '.' Example:
    1. Excel: =INDIREKT("KW24!F16")
    1. Calc : =INDIREKT("KW24.F16")
1. Excel: IFERROR(...) is in Calc a combination of IF(ISERROR(...))<br>
    in German Calc: WENN(ISTFEHLER(...))
1. The Excel-function call VALUE(...) (ger: WERT(...)) is not needed in Calc
