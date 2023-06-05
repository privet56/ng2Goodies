# Excel formulas in German

### common calculations
>=MITTELWERT(B:B)           # mean<br>
>=ANZAHL(B:B)               # count<br>
>=ZÄHLENWENN(B:B;"<55")     # count values under 55
>=(ZÄHLENWENN(B:B;"<55")/ANZAHL(B:B))*100 # calc ratio in percent<br>

### Link to a value in another excel file:
> =[Musterfrau1.xlsx]KW29!$A$2

### Link to a value in another sheet of the same file:
='Musterfrau2-Sheet2'!A2

### Sum of values
> =SUMME(A6:G6)

### Count number of non-empty values
> =ZÄHLENWENN(A6:G6;"<>"&"")

### List non-empty unique values in an area (several columns!):
> =SORTIERENNACH(EINDEUTIG(FILTER(ZUSPALTE(C4:I21); ZUSPALTE(C4:I21)<>"")); ZÄHLENWENN(C4:I21; EINDEUTIG(FILTER(ZUSPALTE(C4:I21); ZUSPALTE(C4:I21)<>""))); -1)

