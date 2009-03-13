
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXRecoverPasswordMap (
  DB_COLUMN_PREFIXuserName
      varchar(
      
	  32
	
      )
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXauthString
      varchar(
      
	  32
	
      )
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXrequestExpires
      int(11)
    
    NOT NULL
  
    ,
  
      PRIMARY KEY (DB_COLUMN_PREFIXuserName)
    

    ) TYPE=DB_TABLE_TYPE;

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'RecoverPasswordMap',
      1,
      1
      );

  