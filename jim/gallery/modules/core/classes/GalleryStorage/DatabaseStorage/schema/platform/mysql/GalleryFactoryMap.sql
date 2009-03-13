
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXFactoryMap (
  DB_COLUMN_PREFIXclassType
      varchar(
      
	  128
	
      )
    
      ,
    DB_COLUMN_PREFIXclassName
      varchar(
      
	  128
	
      )
    
      ,
    DB_COLUMN_PREFIXimplId
      varchar(
      
	  128
	
      )
    
      ,
    DB_COLUMN_PREFIXimplPath
      varchar(
      
	  128
	
      )
    
      ,
    DB_COLUMN_PREFIXimplModuleId
      varchar(
      
	  128
	
      )
    
      ,
    DB_COLUMN_PREFIXhints
      varchar(
      
	  255
	
      )
    
      ,
    DB_COLUMN_PREFIXorderWeight
      varchar(
      
	  255
	
      )
    

    ) TYPE=DB_TABLE_TYPE;

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'FactoryMap',
      1,
      0
      );

  