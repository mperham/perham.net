
      ALTER TABLE DB_TABLE_PREFIXGroup
    MODIFY (
    DB_COLUMN_PREFIXgroupName
      VARCHAR2(
       128 
      )
    
    )
  
      ;
    

    UPDATE DB_TABLE_PREFIXSchema
      SET DB_COLUMN_PREFIXmajor=1,
	  DB_COLUMN_PREFIXminor=1
      WHERE DB_COLUMN_PREFIXname='Group' AND
	  DB_COLUMN_PREFIXmajor=1 AND
	  DB_COLUMN_PREFIXminor=0;
  