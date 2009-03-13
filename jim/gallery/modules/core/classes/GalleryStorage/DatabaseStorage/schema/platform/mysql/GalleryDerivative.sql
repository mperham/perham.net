
    -- This file was automatically generated from an XSL template, which is
    -- why it looks so ugly.  Editing it by hand would be a bad idea.
    --

    CREATE TABLE DB_TABLE_PREFIXDerivative (
  DB_COLUMN_PREFIXid
      int(11)
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXderivativeSourceId
      int(11)
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXderivativeOperations
      varchar(
      
	  255
	
      )
    
      ,
    DB_COLUMN_PREFIXderivativeOrder
      int(11)
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXderivativeSize
      int(11)
    
      ,
    DB_COLUMN_PREFIXderivativeType
      int(11)
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXmimeType
      varchar(
      
	  128
	
      )
    
    NOT NULL
  
      ,
    DB_COLUMN_PREFIXpostFilterOperations
      varchar(
      
	  255
	
      )
    
      ,
    DB_COLUMN_PREFIXisBroken
      int(1)
    
    ,
  
      PRIMARY KEY (DB_COLUMN_PREFIXid)
    
    ,
  
    INDEX DB_TABLE_PREFIXDerivative_85338 (DB_COLUMN_PREFIXderivativeSourceId)
    
      ,
    
    INDEX DB_TABLE_PREFIXDerivative_25243 (DB_COLUMN_PREFIXderivativeOrder)
    
      ,
    
    INDEX DB_TABLE_PREFIXDerivative_97216 (DB_COLUMN_PREFIXderivativeType)
    

    ) TYPE=DB_TABLE_TYPE;

    INSERT INTO DB_TABLE_PREFIXSchema (
      DB_COLUMN_PREFIXname,
      DB_COLUMN_PREFIXmajor,
      DB_COLUMN_PREFIXminor
      ) VALUES (
      'Derivative',
      1,
      1
      );

  