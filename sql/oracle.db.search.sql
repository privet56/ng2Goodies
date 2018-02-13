declare
 l_count number := 0;
 l_str varchar2(20) := '%Z0008SHC%';
begin
 for rec in (select table_name, column_name
             from user_tab_columns
             where data_type in ( 'VARCHAR2' , 'VARCHAR', 'CHAR' ) ) loop
  execute immediate 'select count(*) from '||rec.table_name||
                ' where '||rec.column_name||' like '''||l_str||'''' into l_count;
  if l_count > 0 then
   dbms_output.put_line('table:'''||rec.table_name||''' '||CHR(9)||' col:'''||rec.column_name||''' '||CHR(9)||' hitcount:'||l_count||' '||CHR(9)||' searchstring:'''||l_str||'''');
  end if;
 end loop;
end;
