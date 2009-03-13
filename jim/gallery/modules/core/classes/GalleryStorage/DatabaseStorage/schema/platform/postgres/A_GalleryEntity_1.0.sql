
      ALTER TABLE DB_TABLE_PREFIXEntity
      ADD COLUMN DB_COLUMN_PREFIXonLoadHandlers
      VARCHAR(
      
	  128
	
      )
    
      ;
    

    UPDATE DB_TABLE_PREFIXSchema
      SET DB_COLUMN_PREFIXmajor=1,
	  DB_COLUMN_PREFIXminor=1
      WHERE DB_COLUMN_PREFIXname='Entity' AND
	  DB_COLUMN_PREFIXmajor=1 AND
	  DB_COLUMN_PREFIXminor=0;
  