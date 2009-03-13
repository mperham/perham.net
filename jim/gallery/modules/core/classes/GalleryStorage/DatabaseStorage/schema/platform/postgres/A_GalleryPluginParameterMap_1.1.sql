
      ALTER TABLE DB_TABLE_PREFIXPluginParameterMap
      ADD COLUMN DB_COLUMN_PREFIXparameterValueTemp
  
      TEXT
    
      ;

      UPDATE DB_TABLE_PREFIXPluginParameterMap SET
      DB_COLUMN_PREFIXparameterValueTemp
   = CAST(DB_COLUMN_PREFIXparameterValue AS 
      TEXT
    )
      ;

      ALTER TABLE DB_TABLE_PREFIXPluginParameterMap
      DROP DB_COLUMN_PREFIXparameterValue
      ;

      ALTER TABLE DB_TABLE_PREFIXPluginParameterMap
      RENAME DB_COLUMN_PREFIXparameterValueTemp
   to DB_COLUMN_PREFIXparameterValue
      ;

      

    UPDATE DB_TABLE_PREFIXSchema
      SET DB_COLUMN_PREFIXmajor=1,
	  DB_COLUMN_PREFIXminor=2
      WHERE DB_COLUMN_PREFIXname='PluginParameterMap' AND
	  DB_COLUMN_PREFIXmajor=1 AND
	  DB_COLUMN_PREFIXminor=1;
  