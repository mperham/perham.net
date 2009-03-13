
      ALTER TABLE DB_TABLE_PREFIXPluginMap
      MODIFY COLUMN DB_COLUMN_PREFIXpluginType
      varchar(
      
	  32
	
      )
    
    NOT NULL
  
      ,
    
      MODIFY COLUMN DB_COLUMN_PREFIXpluginId
      varchar(
      
	  32
	
      )
    
    NOT NULL
  
      ;
    

    UPDATE DB_TABLE_PREFIXSchema
      SET DB_COLUMN_PREFIXmajor=1,
	  DB_COLUMN_PREFIXminor=1
      WHERE DB_COLUMN_PREFIXname='PluginMap' AND
	  DB_COLUMN_PREFIXmajor=1 AND
	  DB_COLUMN_PREFIXminor=0;
  