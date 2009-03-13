
      ALTER TABLE DB_TABLE_PREFIXPluginParameterMap
    MODIFY (
    DB_COLUMN_PREFIXparameterValue
      VARCHAR2(4000)
    
    )
  
      ;
    

    UPDATE DB_TABLE_PREFIXSchema
      SET DB_COLUMN_PREFIXmajor=1,
	  DB_COLUMN_PREFIXminor=2
      WHERE DB_COLUMN_PREFIXname='PluginParameterMap' AND
	  DB_COLUMN_PREFIXmajor=1 AND
	  DB_COLUMN_PREFIXminor=1;
  