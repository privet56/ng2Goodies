create or replace PROCEDURE PC_UPSERT_MTA_PMT_ADD_DATA AS 

 -- cursor version begin
  c_limit PLS_INTEGER := 1000;
  CURSOR cur
  is
    select * from VW_RL_MTA_PMT;
-- cursor version end
-- bulk&cursor version begin
  TYPE t_VW_RL_MTA_PMT is table of VW_RL_MTA_PMT%ROWTYPE INDEX BY PLS_INTEGER;
  v_VW_RL_MTA_PMT t_VW_RL_MTA_PMT;
 -- bulk&cursor version end

BEGIN

  -- fill mta table is_visible & pointdate from the view VW_RL_MTA_PMT which calculates it

  -- this would be the cursor version
  open cur;
  -- dbms_output.put_line('A:');
  loop
    fetch cur
    bulk collect into v_VW_RL_MTA_PMT
    limit c_limit;
    
    forall idx in 1 .. v_VW_RL_MTA_PMT.count
      update MTA set is_visible = v_VW_RL_MTA_PMT(idx).is_visible, pointdate = v_VW_RL_MTA_PMT(idx).pointdate where MTA.MTA_ID = v_VW_RL_MTA_PMT(idx).MTA_ID;
    
    exit when v_VW_RL_MTA_PMT.count = 0;
  end loop;

  -- this would be the bulk-version: (fast but uses more memory)
  -- TODO: remove unneeded cols from VW after ensuring that these are used nowhere, and so save memory in the below bulk operation
  -- TODO(optional): use cursor with limit of loaded rows
  -- select * bulk collect into v_VW_RL_MTA_PMT from VW_RL_MTA_PMT;
  -- forall idx in 1 .. v_VW_RL_MTA_PMT.count
  --  update MTA set is_visible = v_VW_RL_MTA_PMT(idx).is_visible, pointdate = v_VW_RL_MTA_PMT(idx).pointdate where MTA.MTA_ID = v_VW_RL_MTA_PMT(idx).MTA_ID;

  -- this would be the non-bulk-version: (slow but uses less memory)
  --for vwrlmtapmt IN (select mta_id, is_visible, POINTDATE from VW_RL_MTA_PMT) loop
  --  update MTA set is_visible = vwrlmtapmt.is_visible, pointdate = vwrlmtapmt.pointdate where MTA.MTA_ID = vwrlmtapmt.MTA_ID;
  -- end loop;

END PC_UPSERT_MTA_PMT_ADD_DATA;
