
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXPluginParameterMap (
  DB_COLUMN_PREFIXpluginType
      VARCHAR2(
       32 
      )
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXpluginId
      VARCHAR2(
       32 
      )
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXitemId
      INTEGER
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXparameterName
      VARCHAR2(
       128 
      )
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXparameterValue
      VARCHAR2(4000)
    
    );

  
    CREATE INDEX DB_TABLE_PREFIXPluginParameterMap_12808
    ON DB_TABLE_PREFIXPluginParameterMap
    (DB_COLUMN_PREFIXpluginType
	,
      DB_COLUMN_PREFIXpluginId
	,
      DB_COLUMN_PREFIXitemId);
  
    CREATE INDEX DB_TABLE_PREFIXPluginParameterMap_80596
    ON DB_TABLE_PREFIXPluginParameterMap
    (DB_COLUMN_PREFIXpluginType);
  
    ALTER TABLE DB_TABLE_PREFIXPluginParameterMap
      ADD UNIQUE (DB_COLUMN_PREFIXpluginType
	,
      DB_COLUMN_PREFIXpluginId
	,
      DB_COLUMN_PREFIXitemId
	,
      DB_COLUMN_PREFIXparameterName)
  ;
  

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'PluginParameterMap',
      1,
      2
      );

  