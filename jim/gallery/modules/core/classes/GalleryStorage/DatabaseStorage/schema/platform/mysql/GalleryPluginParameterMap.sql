
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXPluginParameterMap (
  DB_COLUMN_PREFIXpluginType
      varchar(
      
	  32
	
      )
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXpluginId
      varchar(
      
	  32
	
      )
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXitemId
      int(11)
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXparameterName
      varchar(
      
	  128
	
      )
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXparameterValue
      text
    
    NOT NULL
  
    ,
  
      UNIQUE KEY (DB_COLUMN_PREFIXpluginType
	,
      DB_COLUMN_PREFIXpluginId
	,
      DB_COLUMN_PREFIXitemId
	,
      DB_COLUMN_PREFIXparameterName)
    
    ,
  
    INDEX DB_TABLE_PREFIXPluginParameterMap_12808 (DB_COLUMN_PREFIXpluginType
      ,
    DB_COLUMN_PREFIXpluginId
      ,
    DB_COLUMN_PREFIXitemId)
    
      ,
    
    INDEX DB_TABLE_PREFIXPluginParameterMap_80596 (DB_COLUMN_PREFIXpluginType)
    

    ) TYPE=DB_TABLE_TYPE;

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'PluginParameterMap',
      1,
      2
      );

  