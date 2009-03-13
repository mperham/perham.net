
      ALTER TABLE DB_TABLE_PREFIXGroup
      ADD COLUMN DB_COLUMN_PREFIXgroupNameTemp
  
      VARCHAR(
      
	  128
	
      )
    
      ;

      UPDATE DB_TABLE_PREFIXGroup SET
      DB_COLUMN_PREFIXgroupNameTemp
   = CAST(DB_COLUMN_PREFIXgroupName AS 
      VARCHAR(
      
	  128
	
      )
    )
      ;

      ALTER TABLE DB_TABLE_PREFIXGroup
      DROP DB_COLUMN_PREFIXgroupName
      ;

      ALTER TABLE DB_TABLE_PREFIXGroup
      RENAME DB_COLUMN_PREFIXgroupNameTemp
   to DB_COLUMN_PREFIXgroupName
      ;

      

    UPDATE DB_TABLE_PREFIXSchema
      SET DB_COLUMN_PREFIXmajor=1,
	  DB_COLUMN_PREFIXminor=1
      WHERE DB_COLUMN_PREFIXname='Group' AND
	  DB_COLUMN_PREFIXmajor=1 AND
	  DB_COLUMN_PREFIXminor=0;
  