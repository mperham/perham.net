
      ALTER TABLE DB_TABLE_PREFIXPluginParameterMap
      ADD COLUMN DB_COLUMN_PREFIXpluginTypeTemp
  
      VARCHAR(
      
	  32
	
      )
    
      ;

      UPDATE DB_TABLE_PREFIXPluginParameterMap SET
      DB_COLUMN_PREFIXpluginTypeTemp
   = CAST(DB_COLUMN_PREFIXpluginType AS 
      VARCHAR(
      
	  32
	
      )
    )
      ;

      ALTER TABLE DB_TABLE_PREFIXPluginParameterMap
      DROP DB_COLUMN_PREFIXpluginType
      ;

      ALTER TABLE DB_TABLE_PREFIXPluginParameterMap
      RENAME DB_COLUMN_PREFIXpluginTypeTemp
   to DB_COLUMN_PREFIXpluginType
      ;

      
	ALTER TABLE DB_TABLE_PREFIXPluginParameterMap
	ALTER DB_COLUMN_PREFIXpluginType SET NOT NULL
	;
      
      ALTER TABLE DB_TABLE_PREFIXPluginParameterMap
      ADD COLUMN DB_COLUMN_PREFIXpluginIdTemp
  
      VARCHAR(
      
	  32
	
      )
    
      ;

      UPDATE DB_TABLE_PREFIXPluginParameterMap SET
      DB_COLUMN_PREFIXpluginIdTemp
   = CAST(DB_COLUMN_PREFIXpluginId AS 
      VARCHAR(
      
	  32
	
      )
    )
      ;

      ALTER TABLE DB_TABLE_PREFIXPluginParameterMap
      DROP DB_COLUMN_PREFIXpluginId
      ;

      ALTER TABLE DB_TABLE_PREFIXPluginParameterMap
      RENAME DB_COLUMN_PREFIXpluginIdTemp
   to DB_COLUMN_PREFIXpluginId
      ;

      
	ALTER TABLE DB_TABLE_PREFIXPluginParameterMap
	ALTER DB_COLUMN_PREFIXpluginId SET NOT NULL
	;
      

    UPDATE DB_TABLE_PREFIXSchema
      SET DB_COLUMN_PREFIXmajor=1,
	  DB_COLUMN_PREFIXminor=1
      WHERE DB_COLUMN_PREFIXname='PluginParameterMap' AND
	  DB_COLUMN_PREFIXmajor=1 AND
	  DB_COLUMN_PREFIXminor=0;
  