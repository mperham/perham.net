
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXPluginMap (
  DB_COLUMN_PREFIXpluginType
      VARCHAR(
      
	  32
	
      )
    
      NOT NULL
    
      ,
    DB_COLUMN_PREFIXpluginId
      VARCHAR(
      
	  32
	
      )
    
      NOT NULL
    
      ,
    DB_COLUMN_PREFIXactive
      SMALLINT
    
      NOT NULL
    
    );

  
    ALTER TABLE DB_TABLE_PREFIXPluginMap
    ADD PRIMARY KEY (DB_COLUMN_PREFIXpluginType
	,
      DB_COLUMN_PREFIXpluginId);
    

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'PluginMap',
      1,
      1
      );

  