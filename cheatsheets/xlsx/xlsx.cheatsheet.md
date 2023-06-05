# Excel formulas in German

### Excel formula translations:
https://excelhero.de/excel-funktionen-deutsch-englisch/

### common calculations
>=MITTELWERT(B:B)           # mean<br>
>=ANZAHL(B:B)               # count<br>
>=ZÄHLENWENN(B:B;"<55")     # count values under 55<br>
>=(ZÄHLENWENN(B:B;"<55")/ANZAHL(B:B))*100 # calc ratio in percent<br>

### Link to a value in another excel file:
> =[Musterfrau1.xlsx]KW29!$A$2

### Link to a value in another sheet of the same file:
> ='Musterfrau2-Sheet2'!A2

### Sum of values
> =SUMME(A6:G6)

### Count number of non-empty values
> =ZÄHLENWENN(A6:G6;"<>"&"")

### List non-empty unique values in an area (several columns!):
> =SORTIERENNACH(EINDEUTIG(FILTER(ZUSPALTE(C4:I21); ZUSPALTE(C4:I21)<>"")); ZÄHLENWENN(C4:I21; EINDEUTIG(FILTER(ZUSPALTE(C4:I21); ZUSPALTE(C4:I21)<>""))); -1)

### Find value in an area
> find value in B16 in the area 'KW30'!B$16:B33<br>
> =VERGLEICH(B16;'KW30'!B$16:B33;0)

### Find value of a string-based cell address
> find value in "KW30!D" + (value ofC16 +15)<br>
> =INDIREKT("KW30!D" & (WERT(C16) + 15))

### add values or set 0 (if error)
> =WENNFEHLER(SUMME(D16;E16); 0)
