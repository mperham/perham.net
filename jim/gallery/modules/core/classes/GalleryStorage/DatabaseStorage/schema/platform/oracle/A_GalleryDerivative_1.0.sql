
      ALTER TABLE DB_TABLE_PREFIXDerivative
      ADD (
	DB_COLUMN_PREFIXisBroken
      NUMBER(1)
    
      )
    
      ;
    

    UPDATE DB_TABLE_PREFIXSchema
      SET DB_COLUMN_PREFIXmajor=1,
	  DB_COLUMN_PREFIXminor=1
      WHERE DB_COLUMN_PREFIXname='Derivative' AND
	  DB_COLUMN_PREFIXmajor=1 AND
	  DB_COLUMN_PREFIXminor=0;
  