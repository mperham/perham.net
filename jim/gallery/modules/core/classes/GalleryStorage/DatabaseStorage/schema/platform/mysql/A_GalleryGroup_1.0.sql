
      ALTER TABLE DB_TABLE_PREFIXGroup
      MODIFY COLUMN DB_COLUMN_PREFIXgroupName
      varchar(
      
	  128
	
      )
    
      ;
    

    UPDATE DB_TABLE_PREFIXSchema
      SET DB_COLUMN_PREFIXmajor=1,
	  DB_COLUMN_PREFIXminor=1
      WHERE DB_COLUMN_PREFIXname='Group' AND
	  DB_COLUMN_PREFIXmajor=1 AND
	  DB_COLUMN_PREFIXminor=0;
  