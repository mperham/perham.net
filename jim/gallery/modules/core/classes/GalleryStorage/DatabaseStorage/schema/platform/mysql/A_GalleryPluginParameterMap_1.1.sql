
      ALTER TABLE DB_TABLE_PREFIXPluginParameterMap
      MODIFY COLUMN DB_COLUMN_PREFIXparameterValue
      text
    
      ;
    

    UPDATE DB_TABLE_PREFIXSchema
      SET DB_COLUMN_PREFIXmajor=1,
	  DB_COLUMN_PREFIXminor=2
      WHERE DB_COLUMN_PREFIXname='PluginParameterMap' AND
	  DB_COLUMN_PREFIXmajor=1 AND
	  DB_COLUMN_PREFIXminor=1;
  