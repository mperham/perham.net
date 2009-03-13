
      ALTER TABLE DB_TABLE_PREFIXItem
      ADD COLUMN DB_COLUMN_PREFIXoriginationTimestamp
      int(11)
    
      ;
    

    UPDATE DB_TABLE_PREFIXSchema
      SET DB_COLUMN_PREFIXmajor=1,
	  DB_COLUMN_PREFIXminor=1
      WHERE DB_COLUMN_PREFIXname='Item' AND
	  DB_COLUMN_PREFIXmajor=1 AND
	  DB_COLUMN_PREFIXminor=0;
  