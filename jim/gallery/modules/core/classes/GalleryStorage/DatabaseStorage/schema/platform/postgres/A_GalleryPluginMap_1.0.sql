
      ALTER TABLE DB_TABLE_PREFIXPluginMap
      ADD COLUMN DB_COLUMN_PREFIXpluginTypeTemp
  
      VARCHAR(
      
	  32
	
      )
    
      ;

      UPDATE DB_TABLE_PREFIXPluginMap SET
      DB_COLUMN_PREFIXpluginTypeTemp
   = CAST(DB_COLUMN_PREFIXpluginType AS 
      VARCHAR(
      
	  32
	
      )
    )
      ;

      ALTER TABLE DB_TABLE_PREFIXPluginMap
      DROP DB_COLUMN_PREFIXpluginType
      ;

      ALTER TABLE DB_TABLE_PREFIXPluginMap
      RENAME DB_COLUMN_PREFIXpluginTypeTemp
   to DB_COLUMN_PREFIXpluginType
      ;

      
	ALTER TABLE DB_TABLE_PREFIXPluginMap
	ALTER DB_COLUMN_PREFIXpluginType SET NOT NULL
	;
      
      ALTER TABLE DB_TABLE_PREFIXPluginMap
      ADD COLUMN DB_COLUMN_PREFIXpluginIdTemp
  
      VARCHAR(
      
	  32
	
      )
    
      ;

      UPDATE DB_TABLE_PREFIXPluginMap SET
      DB_COLUMN_PREFIXpluginIdTemp
   = CAST(DB_COLUMN_PREFIXpluginId AS 
      VARCHAR(
      
	  32
	
      )
    )
      ;

      ALTER TABLE DB_TABLE_PREFIXPluginMap
      DROP DB_COLUMN_PREFIXpluginId
      ;

      ALTER TABLE DB_TABLE_PREFIXPluginMap
      RENAME DB_COLUMN_PREFIXpluginIdTemp
   to DB_COLUMN_PREFIXpluginId
      ;

      
	ALTER TABLE DB_TABLE_PREFIXPluginMap
	ALTER DB_COLUMN_PREFIXpluginId SET NOT NULL
	;
      

    UPDATE DB_TABLE_PREFIXSchema
      SET DB_COLUMN_PREFIXmajor=1,
	  DB_COLUMN_PREFIXminor=1
      WHERE DB_COLUMN_PREFIXname='PluginMap' AND
	  DB_COLUMN_PREFIXmajor=1 AND
	  DB_COLUMN_PREFIXminor=0;
  