// ======================================================================
//
//   File:  mempro_pkg.v
//
//   Desc:  This package links the PLI/C library calls with
//          mempro verilog calls.
//
// ======================================================================

// *******************************
//   Send init_complete to MemCore
// *******************************
integer dummy_inst_handle;
initial begin
    #0 memcore_init_complete(dummy_inst_handle);
end


// *******************************
//   Predefined cycle tyep defs for
//   use with memcore_read_ext()
//   and memcore_write_ext()
// *******************************

`define CYCLEDEF_testbenchrd  'h40
`define CYCLEDEF_testbenchwt  'h41
`define CYCLEDEF_internal     'h42
`define CYCLEDEF_chktrace_wt  'h43
`define CYCLEDEF_chktrace_rd  'h44


// *******************************
//   Message level control constants
// *******************************
`define SLM_ERROR            1
`define SLM_WARNING          2
`define SLM_TIMING           4
`define SLM_XHANDLING        8
`define SLM_INFO             16
`define SLM_NO_MSGS          0
`define SLM_ALL_MSGS         31

parameter error_bit     = 0;
parameter warning_bit   = 1;
parameter timing_bit    = 2;
parameter xhandling_bit = 3;
parameter info_bit      = 4;

// *******************************
//   MemPro memory file formats
// *******************************
`define SLM_FMT_MIF          0
`define SLM_FMT_IHEX         1
`define SLM_FMT_SREC         2
`define SLM_FMT_VLOG         3

// *******************************
//   MemPro constants
// *******************************
`define SLM_MAX_STRING_LEN      256
`define SLM_MAX_STRING_SIZE     `SLM_MAX_STRING_LEN * 8
`define SLM_MAX_ADDR_WIDTH       64
`define SLM_MAX_DATA_WIDTH     2048 
`define SLM_HANDLE_INVALID       -2
`define SLM_APP_TYPE_ID_MEMPRO    1
`define SLM_MEMPRO_CORE_HANDLE    0
`define SLM_MEMPRO_USER_HANDLE    1
`define SLM_MEMPRO_MSG_WIDTH      5
`define SLM_MEMPRO_NO_CYCLE_INFO -1

// *******************************
//   Testbench status codes
// *******************************
`define SLM_TESTBENCH_WARNING  1
`define SLM_TESTBENCH_SUCCESS  0
`define SLM_TESTBENCH_FAILURE -1

// *******************************
//   MemPro function constants
// *******************************
`define SLM_MEMCORE_INSTANCE             0
`define SLM_MEMCORE_LOAD                 1
`define SLM_MEMCORE_DUMP                 2
`define SLM_MEMCORE_READ                 3
`define SLM_MEMCORE_WRITE                4
`define SLM_MEMCORE_MESSAGE_CHK          5

`define SLM_MEMCORE_UNLOAD              15
`define SLM_MEMCORE_MLOG_ENABLED        16

`define SLM_MEMCORE_REGISTER_CYCLE_TYPE 18
`define SLM_MEMCORE_CYCLE_TYPE          19
`define SLM_MEMCORE_INFO                20

`define SLM_MEMCORE_HANDLE              25
`define SLM_MEMCORE_WIDTH_INFO          26
`define SLM_MEMCORE_INIT_COMPLETE       27

`define SLM_MEMCORE_INCR_ERR_CNT        28
`define SLM_MEMCORE_INCR_WARN_CNT       29
`define SLM_MEMCORE_INCR_NOTE_CNT       30
`define SLM_MEMCORE_INIT_MSG_COUNTS     33


`define SLM_MEM_LOAD                     6
`define SLM_MEM_DUMP                     7
`define SLM_MEM_PEEK                     8
`define SLM_MEM_POKE                     9
`define SLM_MEM_TRACE                   10
`define SLM_MEM_UNTRACE                 11
`define SLM_MEM_LASTOP                  12
`define SLM_MEM_MSG_LEVEL               13
`define SLM_MEM_UNLOAD                  14

`define SLM_MEM_CREATE_DB               21
`define SLM_MEM_LOAD_DB                 22
`define SLM_MEM_BEGIN_HISTORY           23
`define SLM_MEM_END_HISTORY             24

`define SLM_MEMPRO_RESET_MSG_CNTS       31
`define SLM_MEMPRO_GET_MSG_CNTS         32



// *******************************
//   MemPro arg count constants
// *******************************
`define SLM_MEMCORE_INSTANCE_INT_CNT        7
`define SLM_MEMCORE_LOAD_INT_CNT            2
`define SLM_MEMCORE_UNLOAD_INT_CNT          2
`define SLM_MEMCORE_DUMP_INT_CNT            2
`define SLM_MEMCORE_READ_INT_CNT            3
`define SLM_MEMCORE_WRITE_INT_CNT           5
`define SLM_MEMCORE_MESSAGE_CHK_INT_CNT     3
`define SLM_MEMCORE_MLOG_ENABLED_INT_CNT    2
`define SLM_MEMCORE_REGISTER_CYCLE_TYPE_INT_CNT 4
`define SLM_MEMCORE_CYCLE_TYPE_INT_CNT      3
`define SLM_MEMCORE_INFO_INT_CNT            2
`define SLM_MEMCORE_HANDLE_INT_CNT          3
`define SLM_MEMCORE_WIDTH_INFO_INT_CNT      2
`define SLM_MEMCORE_INIT_COMPLETE_INT_CNT   2

`define SLM_MEMCORE_INCR_ERR_CNT_INT_CNT    2
`define SLM_MEMCORE_INCR_WARN_CNT_INT_CNT   2
`define SLM_MEMCORE_INCR_NOTE_CNT_INT_CNT   2
`define SLM_MEMCORE_INIT_MSG_COUNTS_INT_CNT 2

`define SLM_MEMPRO_LOAD_INT_CNT             3
`define SLM_MEMPRO_UNLOAD_INT_CNT           4
`define SLM_MEMPRO_DUMP_INT_CNT             5
`define SLM_MEMPRO_READ_INT_CNT             3
`define SLM_MEMPRO_WRITE_INT_CNT            5
`define SLM_MEMPRO_TRACE_INT_CNT            6
`define SLM_MEMPRO_UNTRACE_INT_CNT          4
`define SLM_MEMPRO_LASTOP_INT_CNT           1
`define SLM_MEMPRO_LASTOP_INT_CNT_OUT       4
`define SLM_MEMPRO_SET_MSG_LEVEL_INT_CNT    4
`define SLM_MEMPRO_ZERO_CNT                 0
`define SLM_MEMPRO_CREATE_DB_INT_CNT        1
`define SLM_MEMPRO_LOAD_DB_INT_CNT          1
`define SLM_MEMPRO_BEGIN_HISTORY_INT_CNT    1
`define SLM_MEMPRO_END_HISTORY_INT_CNT      1

`define SLM_MEMPRO_RESET_MSG_CNTS_INT_CNT   3
`define SLM_MEMPRO_GET_MSG_CNTS_INT_CNT     3
`define SLM_MEMPRO_GET_MSG_CNTS_INT_CNT_OUT 4

// *******************************
//   array indexes
// *******************************
`define INDEX_0                  (31):(0)
`define INDEX_1             (1*32+31):(1*32)
`define INDEX_2             (2*32+31):(2*32)
`define INDEX_3             (3*32+31):(3*32)
`define INDEX_4             (4*32+31):(4*32)
`define INDEX_5             (5*32+31):(5*32)
`define INDEX_6             (6*32+31):(6*32)
`define INDEX_7             (7*32+31):(7*32)

// *******************************
//   slm_post count array indexes
// *******************************
`define SLM_POST_APP_TYPE_ID_IDX   `INDEX_0
`define SLM_POST_INT_MAX_CNT_IDX   `INDEX_1
`define SLM_POST_INT_ACT_CNT_IDX   `INDEX_2
`define SLM_POST_SL_MAX_CNT_IDX    `INDEX_3
`define SLM_POST_SL_ACT_CNT_IDX    `INDEX_4
`define SLM_POST_CHAR_MAX_CNT_IDX  `INDEX_5
`define SLM_POST_CHAR_ACT_CNT_IDX  `INDEX_6
`define SLM_POST_STATUS_IDX        `INDEX_7

`define SLM_POST_CNT_ARRAY_SIZE    8

// *******************************
// cycle type catagories
// *******************************
parameter SLM_READ  = 1;
parameter SLM_WRITE = 2;
parameter SLM_OTHER = 3;


// ****************************************************************************************
//
//    MemPro Model Interface
//
// ****************************************************************************************

task memcore_instance;

    // Task arguments
    input  [31:0]                      address_width;
    input  [31:0]                      data_width;
    input  [31:0]                      four_state;
    input [(`SLM_MAX_DATA_WIDTH-1):0]  initial_state;
    input  [31:0]                      model_type;
    input  [31:0]                      msg_level;
    input  [31:0]                      user_handle;
    output [31:0]                      core_handle;

      begin : this_block
	 
	 memcore_instance_internal (address_width, 
				    data_width,    
				    four_state,    
				    initial_state, 
				    model_type,    
				    msg_level,     
				    user_handle,   
				    ".",
				    core_handle
				    );
      end
endtask  // memcore_instance

task memcore_instance_ext;

      // Task arguments
      input  [31:0]                      address_width;
      input  [31:0]                      data_width;
      input  [31:0]                      four_state;
      input [(`SLM_MAX_DATA_WIDTH-1):0]  initial_state;
      input  [31:0]                      model_type;
      input  [31:0]                      msg_level;
      input  [31:0]                      user_handle;
      input  [(`SLM_MAX_STRING_SIZE-1):0] model_alias;
      output [31:0]                      core_handle;   

      begin : this_block
	 
	 memcore_instance_internal (address_width, 
				    data_width,    
				    four_state,    
				    initial_state, 
				    model_type,    
				    msg_level,     
				    user_handle,   
				    model_alias,   
				    core_handle
				    );
      end
endtask

task memcore_instance_internal;

      // Task arguments
      input  [31:0]                       address_width;
      input  [31:0]                       data_width;
      input  [31:0]                       four_state;
      input [(`SLM_MAX_DATA_WIDTH-1):0]   initial_state;
      input  [31:0]                       model_type;
      input  [31:0]                       msg_level;
      input  [31:0]                       user_handle;
      input  [(`SLM_MAX_STRING_SIZE-1):0] model_alias;
      output [31:0]                       core_handle;

      begin : this_block

	 reg [((`SLM_POST_CNT_ARRAY_SIZE*32)-1):0]       cntArray;
	 reg [((`SLM_MEMCORE_INSTANCE_INT_CNT*32)-1):0]  intArray;
	 reg [(`SLM_MAX_DATA_WIDTH-1):0] 		 slArray;
	 reg [(`SLM_MAX_STRING_SIZE-1):0] 		 charArray; 

	 // Initialize cntArray
	 cntArray[`INDEX_0] = `SLM_APP_TYPE_ID_MEMPRO;
	 cntArray[`INDEX_1] = `SLM_MEMCORE_INSTANCE_INT_CNT;
	 cntArray[`INDEX_2] = `SLM_MEMCORE_INSTANCE_INT_CNT;
	 cntArray[`INDEX_3] = data_width;
	 cntArray[`INDEX_4] = data_width;
	 cntArray[`INDEX_5] = `SLM_MAX_STRING_SIZE;
	 cntArray[`INDEX_6] = `SLM_MAX_STRING_SIZE;

	 // Pack the intArray
	 intArray[`INDEX_0] = `SLM_MEMCORE_INSTANCE;
	 intArray[`INDEX_1] = address_width;
	 intArray[`INDEX_2] = data_width;
	 intArray[`INDEX_3] = four_state;
	 intArray[`INDEX_4] = model_type;
	 intArray[`INDEX_5] = msg_level;
	 intArray[`INDEX_6] = user_handle;

	 // Assign initial_state to slArray
	 slArray   = initial_state;

	 // Assign model_alias string to charArray
	 charArray = model_alias;

	 // Post the call
	 $slm_post_hdl( cntArray, intArray, slArray, charArray );

	 // Extract the memcore handle
	 core_handle = intArray[`INDEX_0];        

      end

endtask  // memcore_instance_internal

// ****************************************************************************************

task memcore_load;

    // Task arguments
    input  [31:0]                       core_handle;
    input  [(`SLM_MAX_STRING_SIZE-1):0] load_file; 

    begin : this_block

        reg [((`SLM_POST_CNT_ARRAY_SIZE*32)-1):0]   cntArray;
        reg [((`SLM_MEMCORE_LOAD_INT_CNT*32)-1):0]  intArray;
        reg [0:0]                                   slArray;
        reg [(`SLM_MAX_STRING_SIZE-1):0]            charArray; 

        // Initialize the count array
        cntArray[`INDEX_0] = `SLM_APP_TYPE_ID_MEMPRO;
        cntArray[`INDEX_1] = `SLM_MEMCORE_LOAD_INT_CNT;
        cntArray[`INDEX_2] = `SLM_MEMCORE_LOAD_INT_CNT;
        cntArray[`INDEX_3] = `SLM_MEMPRO_ZERO_CNT;
        cntArray[`INDEX_4] = `SLM_MEMPRO_ZERO_CNT;
        cntArray[`INDEX_5] = `SLM_MAX_STRING_SIZE;
        cntArray[`INDEX_6] = `SLM_MAX_STRING_SIZE;

        // Pack the integer array
        intArray[`INDEX_0] = `SLM_MEMCORE_LOAD;
        intArray[`INDEX_1] = core_handle;

        // Load the character array
        charArray = load_file;

        // Post the call
        $slm_post_hdl( cntArray, intArray, slArray, charArray );

    end

endtask  // memcore_load

// ****************************************************************************************

task memcore_unload;

    // Task arguments
    input  [31:0]                        core_handle;
    input  [(`SLM_MAX_ADDR_WIDTH-1):0]   low_address;
    input  [(`SLM_MAX_ADDR_WIDTH-1):0]   high_address;

    begin : this_block

        integer                                       i;
        integer                                       address_width;
        integer                                       data_width;
        reg [((`SLM_POST_CNT_ARRAY_SIZE*32)-1):0]     cntArray;
        reg [((`SLM_MEMCORE_UNLOAD_INT_CNT*32)-1):0]  intArray;
        reg [((`SLM_MAX_ADDR_WIDTH*2)-1):0]           slArray;
        reg [0:0]                                     charArray; 

        // Get the address width
        memcore_width_info_internal( core_handle, address_width, data_width );

        // Initialize the count array
        cntArray[`INDEX_0] = `SLM_APP_TYPE_ID_MEMPRO;
        cntArray[`INDEX_1] = `SLM_MEMCORE_UNLOAD_INT_CNT;
        cntArray[`INDEX_2] = `SLM_MEMCORE_UNLOAD_INT_CNT;
        cntArray[`INDEX_3] = address_width * 2;
        cntArray[`INDEX_4] = cntArray[`INDEX_3];
        cntArray[`INDEX_5] = `SLM_MEMPRO_ZERO_CNT;
        cntArray[`INDEX_6] = `SLM_MEMPRO_ZERO_CNT;

        // Pack the integer array
        intArray[`INDEX_0] = `SLM_MEMCORE_UNLOAD;
        intArray[`INDEX_1] = core_handle;

        // Load the address boundaries into slArray
        for ( i=0; i < address_width; i=i+1 )
        begin
            slArray[i]               = low_address[i];
            slArray[address_width+i] = high_address[i];
        end

        // Post the call
        $slm_post_hdl( cntArray, intArray, slArray, charArray );

    end

endtask  // memcore_unload

// ****************************************************************************************

task memcore_dump;

    // Task arguments
    input  [31:0]                        core_handle;
    input  [(`SLM_MAX_ADDR_WIDTH-1):0]   low_address;
    input  [(`SLM_MAX_ADDR_WIDTH-1):0]   high_address;
    input  [(`SLM_MAX_STRING_SIZE-1):0]  dump_file;

    begin : this_block

        integer                                     i;
        integer                                     address_width;
        integer                                     data_width;
        reg [((`SLM_POST_CNT_ARRAY_SIZE*32)-1):0]   cntArray;
        reg [((`SLM_MEMCORE_DUMP_INT_CNT*32)-1):0]  intArray;
        reg [((`SLM_MAX_ADDR_WIDTH*2)-1):0]         slArray;
        reg [(`SLM_MAX_STRING_SIZE-1):0]            charArray; 

        // Get the address width
        memcore_width_info_internal( core_handle, address_width, data_width );

        // Reset the count array for slm_mempro_dump
        cntArray[`INDEX_0] = `SLM_APP_TYPE_ID_MEMPRO;
        cntArray[`INDEX_1] = `SLM_MEMCORE_DUMP_INT_CNT;
        cntArray[`INDEX_2] = `SLM_MEMCORE_DUMP_INT_CNT;
        cntArray[`INDEX_3] = address_width * 2;
        cntArray[`INDEX_4] = cntArray[`INDEX_3];
        cntArray[`INDEX_5] = `SLM_MAX_STRING_SIZE;
        cntArray[`INDEX_6] = `SLM_MAX_STRING_SIZE;

        // Pack the integer array for slm_mempro_dump
        intArray[`INDEX_0] = `SLM_MEMCORE_DUMP;
        intArray[`INDEX_1] = core_handle;

        // Load the address boundaries into slArray
        for ( i=0; i < address_width; i=i+1 )
        begin
            slArray[i]               = low_address[i];
            slArray[address_width+i] = high_address[i];
        end

        // Assign the character array
        charArray = dump_file;

        // Post the call to slm_memcore_dump
        $slm_post_hdl( cntArray, intArray, slArray, charArray );

    end

endtask  // memcore_dump

// ****************************************************************************************

task memcore_read;

    // Task arguments
    input  [31:0]                          core_handle;
    input  [(`SLM_MAX_ADDR_WIDTH-1):0]     address;
    output [(`SLM_MAX_DATA_WIDTH-1):0]     data;

      begin : this_block
	 reg  [(`SLM_MEMPRO_MSG_WIDTH-1):0]   dummy;
	 
	 memcore_read_internal(core_handle, address, data, `SLM_MEMPRO_NO_CYCLE_INFO, dummy);
	 
      end

endtask  // memcore_read

task memcore_read_ext;

    // Task arguments
   input [31:0] 			   core_handle;
   input [(`SLM_MAX_ADDR_WIDTH-1):0] 	   address;
   output [(`SLM_MAX_DATA_WIDTH-1):0] 	   data;
   input [31:0] 			   cycle_type;
   output [(`SLM_MEMPRO_MSG_WIDTH-1):0]    message_level;

   begin : this_block
      memcore_read_internal(core_handle, address, data, cycle_type, message_level);
      
   end

endtask  // memcore_read_ext

task memcore_read_internal;

    // Task arguments
   input  [31:0]                          core_handle;
   input [(`SLM_MAX_ADDR_WIDTH-1):0] 	  address;
   output [(`SLM_MAX_DATA_WIDTH-1):0] 	  data;
   input [31:0] 			  cycle_type;
   output [(`SLM_MEMPRO_MSG_WIDTH-1):0]   message_level;

    begin : this_block

        integer                                                i;
        integer                                                address_width;
        integer                                                data_width;
        reg [((`SLM_POST_CNT_ARRAY_SIZE*32)-1):0]              cntArray;
        reg [((`SLM_MEMPRO_READ_INT_CNT*32)-1):0]              intArray;
        reg [((`SLM_MAX_ADDR_WIDTH+`SLM_MAX_DATA_WIDTH)-1):0]  slArray;
        reg [0:0]                                              charArray; 

        // Get the address and data widths
        memcore_width_info_internal( core_handle, address_width, data_width );

        // Initialize the control array 
        cntArray[`INDEX_0] = `SLM_APP_TYPE_ID_MEMPRO;
        cntArray[`INDEX_1] = `SLM_MEMCORE_READ_INT_CNT;
        cntArray[`INDEX_2] = `SLM_MEMCORE_READ_INT_CNT;
        cntArray[`INDEX_3] = address_width + data_width + `SLM_MEMPRO_MSG_WIDTH;
        cntArray[`INDEX_4] = address_width;
        cntArray[`INDEX_5] = `SLM_MEMPRO_ZERO_CNT;
        cntArray[`INDEX_6] = `SLM_MEMPRO_ZERO_CNT;

       // Pack the integer array 
       intArray[`INDEX_0] = `SLM_MEMCORE_READ;
       intArray[`INDEX_1] = core_handle;
       intArray[`INDEX_2] = cycle_type;

       // Assign the address to slArray
       slArray = address;

       // Post the call 
       $slm_post_hdl( cntArray, intArray, slArray, charArray );

       // intArray[0] == 1 if the message level has been appended else
       // and error has occurred and the message level could not be
       // returned.

       if (intArray[0]) begin

         //
         // 1. STAR 53931 - Verilog mem_read_internal task may return incorrect data 
         //  This fixes problem when msg_level bits are added to slArray contents
         // returned through C pipe. Previously the data value passed back by
         // the memcore_read_internal() task could be "extended" with the message
         // level bits. Added a filter to remove those "extra" bits. This problem
         // is only seen if the caller of the memcore_read_internal() task provides
         // a container wider than the actual data width of the memory.
         //
         data = slArray & ((1 << data_width)-1);

	 slArray       = slArray >> data_width;
	 message_level = slArray[`SLM_MEMPRO_MSG_WIDTH-1:0];
	  
       end else begin
	 message_level = 0;
         data = slArray;    // No message_level, ok to pass all data STAR 53931
	  
       end
    end

endtask  // memcore_read_internal


task memcore_read_bu;

  // Task arguments
  input                         [31:0] core_handle;
  input    [(`SLM_MAX_ADDR_WIDTH-1):0] address;
  output   [(`SLM_MAX_DATA_WIDTH-1):0] data;
  input    [(`SLM_MAX_DATA_WIDTH-1):0] bits_used;
  input                         [31:0] cycle_type;
  output [(`SLM_MEMPRO_MSG_WIDTH-1):0] message_level;

begin : this_block

  integer                                                i;
  integer                                                address_width;
  integer                                                data_width;
  integer                                                slidx;
  reg [((`SLM_POST_CNT_ARRAY_SIZE*32)-1):0]              cntArray;
  reg [((`SLM_MEMPRO_READ_INT_CNT*32)-1):0]              intArray;
  reg [((`SLM_MAX_ADDR_WIDTH+`SLM_MAX_DATA_WIDTH)-1):0]  slArray;
  reg [0:0]                                              charArray; 

  // Get the address and data widths
  memcore_width_info_internal( core_handle, address_width, data_width );

//  $display( "%0t: ===> MEMCORE_READ_BU ch=%0d a=%0h d=??? u=%0h ct=%0d",
//    $time, core_handle, address, bits_used, cycle_type );

  // Initialize the control array 
  cntArray[`INDEX_0] = `SLM_APP_TYPE_ID_MEMPRO;
  cntArray[`INDEX_1] = `SLM_MEMCORE_READ_INT_CNT;
  cntArray[`INDEX_2] = `SLM_MEMCORE_READ_INT_CNT;
  cntArray[`INDEX_3] = address_width + data_width + `SLM_MEMPRO_MSG_WIDTH;
  cntArray[`INDEX_4] = address_width + data_width;
  cntArray[`INDEX_5] = `SLM_MEMPRO_ZERO_CNT;
  cntArray[`INDEX_6] = `SLM_MEMPRO_ZERO_CNT;

  // Pack the integer array 
  intArray[`INDEX_0] = `SLM_MEMCORE_READ;
  intArray[`INDEX_1] = core_handle;
  //
  // Apr 30,'04 charliec
  // TRICK! 
  // Use bit 15 of cycle_type to convey the presence of
  // a bits used flag field in the slArray
  //
  intArray[`INDEX_2] = cycle_type + 'h8000;

  // Assign the address to slArray
  slidx = 0;
  for ( i=0; i < address_width; i=i+1 )
    begin
    slArray[slidx] = address[i];
    slidx = slidx + 1;
  end
  for ( i=0; i < data_width; i=i+1 )
    begin
    slArray[slidx] = bits_used[i];
    slidx = slidx + 1;
    end

  // Post the call 
  $slm_post_hdl( cntArray, intArray, slArray, charArray );

  // intArray[0] == 1 if the message level has been appended else
  // and error has occurred and the message level could not be
  // returned.

  if (intArray[0]) begin

    //
    // 1. STAR 53931 - Verilog mem_read_internal task may return incorrect data 
    //  This fixes problem when msg_level bits are added to slArray contents
    // returned through C pipe. Previously the data value passed back by
    // the memcore_read_internal() task could be "extended" with the message
    // level bits. Added a filter to remove those "extra" bits. This problem
    // is only seen if the caller of the memcore_read_internal() task provides
    // a container wider than the actual data width of the memory.
    //
    data = slArray & ((1 << data_width)-1);

    slArray       = slArray >> data_width;
    message_level = slArray[`SLM_MEMPRO_MSG_WIDTH-1:0];
	  
  end
  else begin
    message_level = 0;
    data = slArray;    // No message_level, ok to pass all data STAR 53931
  end

//  $display( "%0t: <=== MEMCORE_READ_BU ch=%0d a=%0h d=%0h u=%0h ct=%0d",
//    $time, core_handle, address, data, bits_used, cycle_type );

end

endtask  // memcore_read_bu


// ****************************************************************************************

//
// These two tasks "piggyback" off the memcore_write_internal task.
// They are used when a model needs to force memcore to check a read
// or write transaction at a particular address but the model DOESN'T
// want memcore to actually read or write data into/from the memcore
// databuffer. They also do not write history information. They ONLY
// call checkTrace in memcore to determine if this operation should
// cause a trace to trigger.
//
task memcore_checktrace_write;
   // Task Arguments
   input  [31:0] 			      Core_handle;
   input  [(`SLM_MAX_ADDR_WIDTH-1):0] 	      Address;
   input  [(`SLM_MAX_DATA_WIDTH-1):0] 	      Data;

   begin : this_block
      reg  [(`SLM_MEMPRO_MSG_WIDTH-1):0]   dummy;
      memcore_write_internal(Core_handle, Address, Data, `CYCLEDEF_chktrace_wt, dummy);
   end

endtask  // memcore_checktrace_write


task memcore_checktrace_read;
   // Task Arguments
   input  [31:0] 			      Core_handle;
   input  [(`SLM_MAX_ADDR_WIDTH-1):0] 	      Address;
   input  [(`SLM_MAX_DATA_WIDTH-1):0] 	      Data;

   begin : this_block
      reg  [(`SLM_MEMPRO_MSG_WIDTH-1):0]   dummy;
      memcore_write_internal(Core_handle, Address, Data, `CYCLEDEF_chktrace_rd, dummy);
   end

endtask  // memcore_checktrace_read

// ****************************************************************************************

task memcore_write;

    // Task arguments
    input  [31:0]                          core_handle;
    input  [(`SLM_MAX_ADDR_WIDTH-1):0]     address;
    input  [(`SLM_MAX_DATA_WIDTH-1):0]     data;

      begin : this_block
	 reg  [(`SLM_MEMPRO_MSG_WIDTH-1):0]   dummy;
	 
	 memcore_write_internal(core_handle, address, data, `SLM_MEMPRO_NO_CYCLE_INFO, dummy);
	 
      end

endtask  // memcore_write

task memcore_write_ext;

   // Task Arguments
   input  [31:0] 			      Core_handle;
   input  [(`SLM_MAX_ADDR_WIDTH-1):0] 	      Address;
   input  [(`SLM_MAX_DATA_WIDTH-1):0] 	      Data;
   input  [31:0] 			      cycle_type;
   output [(`SLM_MEMPRO_MSG_WIDTH-1):0]       Message_level;

   begin : this_block
      memcore_write_internal(Core_handle, Address, Data, cycle_type, Message_level);
      
   end

endtask  // memcore_write_ext



task memcore_write_internal;

   // Task arguments
   input  [31:0]                        core_handle;
   input [(`SLM_MAX_ADDR_WIDTH-1):0] 	address;
   input  [(`SLM_MAX_DATA_WIDTH-1):0] 	data;
   input [31:0] 			cycle_type;
   output [(`SLM_MEMPRO_MSG_WIDTH-1):0] message_level;

   begin : this_block

      integer                                                i;
      integer 						     address_width;
      integer 						     data_width;
      reg [((`SLM_POST_CNT_ARRAY_SIZE*32)-1):0] 	     cntArray;
      reg [((`SLM_MEMPRO_WRITE_INT_CNT*32)-1):0] 	     intArray;
      reg [((`SLM_MAX_ADDR_WIDTH+`SLM_MAX_DATA_WIDTH)-1):0]  slArray;
      reg [0:0] 					     charArray; 

      // Get the MemPro instance info
      memcore_width_info_internal( core_handle, address_width, data_width );

      // Initialize the control array 
      cntArray[`INDEX_0] = `SLM_APP_TYPE_ID_MEMPRO;
      cntArray[`INDEX_1] = `SLM_MEMCORE_WRITE_INT_CNT;
      cntArray[`INDEX_2] = `SLM_MEMCORE_WRITE_INT_CNT;
      cntArray[`INDEX_3] = address_width + data_width + `SLM_MEMPRO_MSG_WIDTH;
      cntArray[`INDEX_4] = address_width + data_width;
      cntArray[`INDEX_5] = `SLM_MEMPRO_ZERO_CNT;
      cntArray[`INDEX_6] = `SLM_MEMPRO_ZERO_CNT;

      // Pack the integer array 
      intArray[`INDEX_0] = `SLM_MEMCORE_WRITE;
      intArray[`INDEX_1] = core_handle;
      intArray[`INDEX_2] = address_width;
      intArray[`INDEX_3] = data_width;
      intArray[`INDEX_4] = cycle_type;
      

      // Pack the slArray
      for ( i=0; i < data_width; i=i+1 )
	 begin
	    slArray[i] = data[i];
	 end
      for ( i=0; i < address_width; i=i+1 )
	 begin
	    slArray[data_width+i] = address[i];
	 end

      // Post the call 
      $slm_post_hdl( cntArray, intArray, slArray, charArray );
      
      message_level = slArray[`SLM_MEMPRO_MSG_WIDTH-1:0];

   end

endtask  // memcore_write_internal


task memcore_write_bu;

   // Task arguments
   input  [31:0]                        core_handle;
   input [(`SLM_MAX_ADDR_WIDTH-1):0] 	address;
   input  [(`SLM_MAX_DATA_WIDTH-1):0] 	data;
   input  [(`SLM_MAX_DATA_WIDTH-1):0] 	bits_used;
   input [31:0] 			cycle_type;
   output [(`SLM_MEMPRO_MSG_WIDTH-1):0] message_level;

   begin : this_block

      integer                                                i;
      integer 						     address_width;
      integer 						     data_width;
      integer 						     slidx;
      reg [((`SLM_POST_CNT_ARRAY_SIZE*32)-1):0] 	     cntArray;
      reg [((`SLM_MEMPRO_WRITE_INT_CNT*32)-1):0] 	     intArray;
      reg [((`SLM_MAX_ADDR_WIDTH+`SLM_MAX_DATA_WIDTH)-1):0]  slArray;
      reg [0:0] 					     charArray; 

      // Get the MemPro instance info
      memcore_width_info_internal( core_handle, address_width, data_width );

//  $display( "%0t: MEMCORE_WRITE_BU ch=%0d a=%0h d=%0h u=%0h ct=%0d",
//    $time, core_handle, address, data, bits_used, cycle_type );

      // Initialize the control array 
      cntArray[`INDEX_0] = `SLM_APP_TYPE_ID_MEMPRO;
      cntArray[`INDEX_1] = `SLM_MEMCORE_WRITE_INT_CNT;
      cntArray[`INDEX_2] = `SLM_MEMCORE_WRITE_INT_CNT;
      cntArray[`INDEX_3] = address_width + data_width + data_width + `SLM_MEMPRO_MSG_WIDTH;
      cntArray[`INDEX_4] = address_width + data_width + data_width;
      cntArray[`INDEX_5] = `SLM_MEMPRO_ZERO_CNT;
      cntArray[`INDEX_6] = `SLM_MEMPRO_ZERO_CNT;

      // Pack the integer array 
      intArray[`INDEX_0] = `SLM_MEMCORE_WRITE;
      intArray[`INDEX_1] = core_handle;
      //
      // Apr 30,'04 charliec
      // TRICK! 
      // Use bit 15 of cycle_type to convey the presence of
      // a bits used flag field in the slArray
      //
      intArray[`INDEX_2] = address_width;
      intArray[`INDEX_3] = data_width;
      intArray[`INDEX_4] = cycle_type + 'h8000;
      

      // Pack the slArray
      slidx = 0;
      for ( i=0; i < data_width; i=i+1 )
	 begin
	 slArray[slidx] = data[i];
         slidx = slidx + 1;
	 end
      for ( i=0; i < address_width; i=i+1 )
	 begin
	 slArray[slidx] = address[i];
         slidx = slidx + 1;
	 end
      for ( i=0; i < data_width; i=i+1 )
	 begin
	 slArray[slidx] = bits_used[i];
         slidx = slidx + 1;
	 end

      // Post the call 
      $slm_post_hdl( cntArray, intArray, slArray, charArray );
      
      message_level = slArray[`SLM_MEMPRO_MSG_WIDTH-1:0];

   end

endtask  // memcore_write_bu





// ****************************************************************************************

task memcore_message_chk;

    // Task arguments
    input  [31:0] core_handle;
    input  [31:0] message_level;
    output [31:0] print_flag;

    begin : this_block

        reg [((`SLM_POST_CNT_ARRAY_SIZE*32)-1):0]          cntArray;
        reg [((`SLM_MEMCORE_MESSAGE_CHK_INT_CNT*32)-1):0]  intArray;
        reg [0:0]                                          slArray;
        reg [0:0]                                          charArray; 

        // Initialize the control array 
        cntArray[`INDEX_0] = `SLM_APP_TYPE_ID_MEMPRO;
        cntArray[`INDEX_1] = `SLM_MEMCORE_MESSAGE_CHK_INT_CNT;
        cntArray[`INDEX_2] = `SLM_MEMCORE_MESSAGE_CHK_INT_CNT;
        cntArray[`INDEX_3] = `SLM_MEMPRO_ZERO_CNT;
        cntArray[`INDEX_4] = `SLM_MEMPRO_ZERO_CNT;
        cntArray[`INDEX_5] = `SLM_MEMPRO_ZERO_CNT;
        cntArray[`INDEX_6] = `SLM_MEMPRO_ZERO_CNT;

        // Pack the integer array 
        intArray[`INDEX_0] = `SLM_MEMCORE_MESSAGE_CHK;
        intArray[`INDEX_1] = core_handle;
        intArray[`INDEX_2] = message_level;
                
        // Post the call
        $slm_post_hdl( cntArray, intArray, slArray, charArray );

        // Extract print flag
        print_flag = intArray[`INDEX_0];

    end

endtask  // memcore_message_chk


// ****************************************************************************************

task memcore_mlog_enabled;

    // Task arguments
    input  [31:0] core_handle;
    input  [(`SLM_MAX_STRING_SIZE-1):0] model_name; 
    output [31:0] enabled_flag;

    begin : this_block

        reg [((`SLM_POST_CNT_ARRAY_SIZE*32)-1):0]           cntArray;
        reg [((`SLM_MEMCORE_MLOG_ENABLED_INT_CNT*32)-1):0]  intArray;
        reg [0:0]                                           slArray;
        reg [(`SLM_MAX_STRING_SIZE-1):0]                    charArray; 

        // Initialize the control array 
        cntArray[`INDEX_0] = `SLM_APP_TYPE_ID_MEMPRO;
        cntArray[`INDEX_1] = `SLM_MEMCORE_MLOG_ENABLED_INT_CNT;
        cntArray[`INDEX_2] = `SLM_MEMCORE_MLOG_ENABLED_INT_CNT;
        cntArray[`INDEX_3] = `SLM_MEMPRO_ZERO_CNT;
        cntArray[`INDEX_4] = `SLM_MEMPRO_ZERO_CNT;
        cntArray[`INDEX_5] = `SLM_MAX_STRING_SIZE;
        cntArray[`INDEX_6] = `SLM_MAX_STRING_SIZE;

        // Pack the integer array 
        intArray[`INDEX_0] = `SLM_MEMCORE_MLOG_ENABLED;
        intArray[`INDEX_1] = core_handle;
                
        // Load the character array
        charArray = model_name;

        // Post the call
        $slm_post_hdl( cntArray, intArray, slArray, charArray );

        // Extract print flag
        enabled_flag = intArray[`INDEX_0];

    end

endtask  // memcore_mlogging_enabled


task memcore_register_cycle_type;

      // Task arguments
      input  [31:0] core_handle;
      input  [31:0] cycle_catagory; 
      input  [31:0] cycle_define; 
      input [(`SLM_MAX_STRING_SIZE-1):0] cycle_name;

    begin : this_block

       reg [((`SLM_POST_CNT_ARRAY_SIZE*32)-1):0]           cntArray;
       reg [((`SLM_MEMCORE_REGISTER_CYCLE_TYPE_INT_CNT*32)-1):0]  intArray;
       reg [0:0] 					   slArray;
       reg [(`SLM_MAX_STRING_SIZE-1):0] 		   charArray; 

       // Initialize the control array 
       cntArray[`INDEX_0] = `SLM_APP_TYPE_ID_MEMPRO;
       cntArray[`INDEX_1] = `SLM_MEMCORE_REGISTER_CYCLE_TYPE_INT_CNT;
       cntArray[`INDEX_2] = `SLM_MEMCORE_REGISTER_CYCLE_TYPE_INT_CNT;
       cntArray[`INDEX_3] = `SLM_MEMPRO_ZERO_CNT;
       cntArray[`INDEX_4] = `SLM_MEMPRO_ZERO_CNT;
       cntArray[`INDEX_5] = `SLM_MAX_STRING_SIZE;
       cntArray[`INDEX_6] = `SLM_MAX_STRING_SIZE;

        // Pack the integer array 
       intArray[`INDEX_0] = `SLM_MEMCORE_REGISTER_CYCLE_TYPE;
       intArray[`INDEX_1] = core_handle;
       intArray[`INDEX_2] = cycle_catagory;
       intArray[`INDEX_3] = cycle_define;
       
                
        // Load the character array
        charArray = cycle_name;

        // Post the call
        $slm_post_hdl( cntArray, intArray, slArray, charArray );

    end

endtask

task memcore_cycle_type;

    // Task arguments
    input  [31:0] core_handle;
    input  [31:0] cycle_define;

    begin : this_block

        reg [((`SLM_POST_CNT_ARRAY_SIZE*32)-1):0]           cntArray;
        reg [((`SLM_MEMCORE_CYCLE_TYPE_INT_CNT*32)-1):0]    intArray;
        reg [0:0]                                           slArray;
        reg [0:0]                                           charArray; 

        // Initialize the control array 
        cntArray[`INDEX_0] = `SLM_APP_TYPE_ID_MEMPRO;
        cntArray[`INDEX_1] = `SLM_MEMCORE_CYCLE_TYPE_INT_CNT;
        cntArray[`INDEX_2] = `SLM_MEMCORE_CYCLE_TYPE_INT_CNT;
        cntArray[`INDEX_3] = `SLM_MEMPRO_ZERO_CNT;
        cntArray[`INDEX_4] = `SLM_MEMPRO_ZERO_CNT;
        cntArray[`INDEX_5] = `SLM_MEMPRO_ZERO_CNT;
        cntArray[`INDEX_6] = `SLM_MEMPRO_ZERO_CNT;

        // Pack the integer array 
        intArray[`INDEX_0] = `SLM_MEMCORE_CYCLE_TYPE;
        intArray[`INDEX_1] = core_handle;
        intArray[`INDEX_2] = cycle_define;
                
        // Post the call
        $slm_post_hdl( cntArray, intArray, slArray, charArray );

    end

endtask

task memcore_info;

    // Task arguments
    input  [31:0] core_handle;
    input  [(`SLM_MAX_STRING_SIZE-1):0] memoryfile; 
    input  [(`SLM_MAX_STRING_SIZE-1):0] modelName; 
    input  [(`SLM_MAX_STRING_SIZE-1):0] specfile; 
    input  [(`SLM_MAX_STRING_SIZE-1):0] classfile; 

    begin : this_block

        reg [((`SLM_POST_CNT_ARRAY_SIZE*32)-1):0]   cntArray;
        reg [((`SLM_MEMCORE_INFO_INT_CNT*32)-1):0]  intArray;
        reg [0:0]                                   slArray;
        reg [(`SLM_MAX_STRING_SIZE*4)+2:0]          charArray; 

        // Pack the integer array 
        intArray[`INDEX_0] = `SLM_MEMCORE_INFO;
        intArray[`INDEX_1] = core_handle;

        // Initialize the control array 
        cntArray[`INDEX_0] = `SLM_APP_TYPE_ID_MEMPRO;
        cntArray[`INDEX_1] = `SLM_MEMCORE_INFO_INT_CNT;
        cntArray[`INDEX_2] = `SLM_MEMCORE_INFO_INT_CNT;
        cntArray[`INDEX_3] = `SLM_MEMPRO_ZERO_CNT;
        cntArray[`INDEX_4] = `SLM_MEMPRO_ZERO_CNT;
        cntArray[`INDEX_5] = `SLM_MAX_STRING_SIZE * 4 + 2;
        cntArray[`INDEX_6] = `SLM_MAX_STRING_SIZE * 4 + 2;

        // Load the character array
        charArray = {memoryfile, ":", modelName, ":", specfile, ":", classfile};

        // Post the call
        $slm_post_hdl( cntArray, intArray, slArray, charArray );

        // Extract print flag

    end

endtask

task memcore_handle_internal;

    // Task arguments
    input  [(`SLM_MAX_STRING_SIZE-1):0] instance_id;
    input  [31:0]                       cmd_id;
    output [31:0]                       core_handle;
    output [31:0]                       status;

    begin : this_block

        reg [((`SLM_POST_CNT_ARRAY_SIZE*32)-1):0]     cntArray;
        reg [((`SLM_MEMCORE_HANDLE_INT_CNT*32)-1):0]  intArray;
        reg [0:0]                                     slArray;
        reg [(`SLM_MAX_STRING_SIZE-1):0]              charArray; 

        // Initialize the count array
        cntArray[`INDEX_0] = `SLM_APP_TYPE_ID_MEMPRO;
        cntArray[`INDEX_1] = `SLM_MEMCORE_HANDLE_INT_CNT;
        cntArray[`INDEX_2] = `SLM_MEMCORE_HANDLE_INT_CNT;
        cntArray[`INDEX_3] = `SLM_MEMPRO_ZERO_CNT;
        cntArray[`INDEX_4] = `SLM_MEMPRO_ZERO_CNT;
        cntArray[`INDEX_5] = `SLM_MAX_STRING_SIZE;
        cntArray[`INDEX_6] = `SLM_MAX_STRING_SIZE;
 
        // Pack the integer array
        intArray[`INDEX_0] = `SLM_MEMCORE_HANDLE;
        intArray[`INDEX_1] = instance_id[31:0];
        intArray[`INDEX_2] = cmd_id;
      
        // Load the character array
        charArray = instance_id ;
 
        // Post the call
        $slm_post_hdl( cntArray, intArray, slArray, charArray );
 
        // Extract status 
        status = cntArray[`SLM_POST_STATUS_IDX];
        // Do something with the status ????

        // Extract info from intArray
        core_handle = intArray[`INDEX_0];

    end

endtask // memcore_handle_internal

task memcore_width_info_internal;

    // Task arguments
    input  [31:0]                       core_handle;
    output [31:0]                       address_width;
    output [31:0]                       data_width;

    begin : this_block

        reg [((`SLM_POST_CNT_ARRAY_SIZE*32)-1):0]         cntArray;
        reg [((`SLM_MEMCORE_WIDTH_INFO_INT_CNT*32)-1):0]  intArray;
        reg [0:0]                                         slArray;
        reg [(`SLM_MAX_STRING_SIZE-1):0]                  charArray;
        integer                                           status; 

        // Initialize the count array
        cntArray[`INDEX_0] = `SLM_APP_TYPE_ID_MEMPRO;
        cntArray[`INDEX_1] = `SLM_MEMCORE_WIDTH_INFO_INT_CNT;
        cntArray[`INDEX_2] = `SLM_MEMCORE_WIDTH_INFO_INT_CNT;
        cntArray[`INDEX_3] = `SLM_MEMPRO_ZERO_CNT;
        cntArray[`INDEX_4] = `SLM_MEMPRO_ZERO_CNT;
        cntArray[`INDEX_5] = `SLM_MEMPRO_ZERO_CNT;
        cntArray[`INDEX_6] = `SLM_MEMPRO_ZERO_CNT;
 
        // Pack the integer array
        intArray[`INDEX_0] = `SLM_MEMCORE_WIDTH_INFO;
        intArray[`INDEX_1] = core_handle;
      
        // Post the call
        $slm_post_hdl( cntArray, intArray, slArray, charArray );
 
        // Extract status 
        status = cntArray[`SLM_POST_STATUS_IDX];
        // Do something with the status ????

        // Extract info from intArray
        address_width = intArray[`INDEX_0];
        data_width    = intArray[`INDEX_1];

    end

endtask // memcore_width_info_internal

task memcore_init_complete;

    // Task arguments
    input  [31:0]                       core_handle;

    begin : this_block

        reg [((`SLM_POST_CNT_ARRAY_SIZE*32)-1):0]         cntArray;
        reg [((`SLM_MEMCORE_INIT_COMPLETE_INT_CNT*32)-1):0]  intArray;
        reg [0:0]                                         slArray;
        reg [(`SLM_MAX_STRING_SIZE-1):0]                  charArray;
        integer                                           status; 

        // Initialize the count array
        cntArray[`INDEX_0] = `SLM_APP_TYPE_ID_MEMPRO;
        cntArray[`INDEX_1] = `SLM_MEMCORE_INIT_COMPLETE_INT_CNT;
        cntArray[`INDEX_2] = `SLM_MEMCORE_INIT_COMPLETE_INT_CNT;
        cntArray[`INDEX_3] = `SLM_MEMPRO_ZERO_CNT;
        cntArray[`INDEX_4] = `SLM_MEMPRO_ZERO_CNT;
        cntArray[`INDEX_5] = `SLM_MEMPRO_ZERO_CNT;
        cntArray[`INDEX_6] = `SLM_MEMPRO_ZERO_CNT;
 
        // Pack the integer array
        intArray[`INDEX_0] = `SLM_MEMCORE_INIT_COMPLETE;
        intArray[`INDEX_1] = core_handle;
      
        // Post the call
        $slm_post_hdl( cntArray, intArray, slArray, charArray );
 
        // Extract status 
        status = cntArray[`SLM_POST_STATUS_IDX];
        // Do something with the status ????

    end

endtask // memcore_init_complete


task memcore_incr_err_cnt;

    // Task arguments
    input  [31:0]                       core_handle;

    begin : this_block

        reg [((`SLM_POST_CNT_ARRAY_SIZE*32)-1):0]         cntArray;
        reg [((`SLM_MEMCORE_INCR_ERR_CNT_INT_CNT*32)-1):0] intArray;
        reg [0:0]                                         slArray;
        reg [(`SLM_MAX_STRING_SIZE-1):0]                  charArray;
        integer                                           status; 


        // Initialize the count array
        cntArray[`INDEX_0] = `SLM_APP_TYPE_ID_MEMPRO;
        cntArray[`INDEX_1] = `SLM_MEMCORE_INCR_ERR_CNT_INT_CNT;
        cntArray[`INDEX_2] = `SLM_MEMCORE_INCR_ERR_CNT_INT_CNT;
        cntArray[`INDEX_3] = `SLM_MEMPRO_ZERO_CNT;
        cntArray[`INDEX_4] = `SLM_MEMPRO_ZERO_CNT;
        cntArray[`INDEX_5] = `SLM_MEMPRO_ZERO_CNT;
        cntArray[`INDEX_6] = `SLM_MEMPRO_ZERO_CNT;
 
        // Pack the integer array
        intArray[`INDEX_0] = `SLM_MEMCORE_INCR_ERR_CNT;
        intArray[`INDEX_1] = core_handle;
      
        // Post the call
        $slm_post_hdl( cntArray, intArray, slArray, charArray );
 
        // Extract status 
        status = cntArray[`SLM_POST_STATUS_IDX];
        // Do something with the status ????

    end

endtask // memcore_incr_err_cnt


task memcore_incr_warn_cnt;

    // Task arguments
    input  [31:0]                       core_handle;

    begin : this_block

        reg [((`SLM_POST_CNT_ARRAY_SIZE*32)-1):0]         cntArray;
        reg [((`SLM_MEMCORE_INCR_WARN_CNT_INT_CNT*32)-1):0] intArray;
        reg [0:0]                                         slArray;
        reg [(`SLM_MAX_STRING_SIZE-1):0]                  charArray;
        integer                                           status; 

        // Initialize the count array
        cntArray[`INDEX_0] = `SLM_APP_TYPE_ID_MEMPRO;
        cntArray[`INDEX_1] = `SLM_MEMCORE_INCR_WARN_CNT_INT_CNT;
        cntArray[`INDEX_2] = `SLM_MEMCORE_INCR_WARN_CNT_INT_CNT;
        cntArray[`INDEX_3] = `SLM_MEMPRO_ZERO_CNT;
        cntArray[`INDEX_4] = `SLM_MEMPRO_ZERO_CNT;
        cntArray[`INDEX_5] = `SLM_MEMPRO_ZERO_CNT;
        cntArray[`INDEX_6] = `SLM_MEMPRO_ZERO_CNT;
 
        // Pack the integer array
        intArray[`INDEX_0] = `SLM_MEMCORE_INCR_WARN_CNT;
        intArray[`INDEX_1] = core_handle;
      
        // Post the call
        $slm_post_hdl( cntArray, intArray, slArray, charArray );
 
        // Extract status 
        status = cntArray[`SLM_POST_STATUS_IDX];
        // Do something with the status ????

    end

endtask // memcore_incr_warn_cnt


task memcore_incr_note_cnt;

    // Task arguments
    input  [31:0]                       core_handle;

    begin : this_block

        reg [((`SLM_POST_CNT_ARRAY_SIZE*32)-1):0]         cntArray;
        reg [((`SLM_MEMCORE_INCR_NOTE_CNT_INT_CNT*32)-1):0] intArray;
        reg [0:0]                                         slArray;
        reg [(`SLM_MAX_STRING_SIZE-1):0]                  charArray;
        integer                                           status; 


        // Initialize the count array
        cntArray[`INDEX_0] = `SLM_APP_TYPE_ID_MEMPRO;
        cntArray[`INDEX_1] = `SLM_MEMCORE_INCR_NOTE_CNT_INT_CNT;
        cntArray[`INDEX_2] = `SLM_MEMCORE_INCR_NOTE_CNT_INT_CNT;
        cntArray[`INDEX_3] = `SLM_MEMPRO_ZERO_CNT;
        cntArray[`INDEX_4] = `SLM_MEMPRO_ZERO_CNT;
        cntArray[`INDEX_5] = `SLM_MEMPRO_ZERO_CNT;
        cntArray[`INDEX_6] = `SLM_MEMPRO_ZERO_CNT;
 
        // Pack the integer array
        intArray[`INDEX_0] = `SLM_MEMCORE_INCR_NOTE_CNT;
        intArray[`INDEX_1] = core_handle;
      
        // Post the call
        $slm_post_hdl( cntArray, intArray, slArray, charArray );
 
        // Extract status 
        status = cntArray[`SLM_POST_STATUS_IDX];
        // Do something with the status ????

    end

endtask // memcore_incr_note_cnt


task memcore_init_msg_counts;

    // Task arguments
    input  [31:0]                       core_handle;

    begin : this_block

        reg [((`SLM_POST_CNT_ARRAY_SIZE*32)-1):0]         cntArray;
        reg [((`SLM_MEMCORE_INIT_MSG_COUNTS_INT_CNT*32)-1):0] intArray;
        reg [0:0]                                         slArray;
        reg [(`SLM_MAX_STRING_SIZE-1):0]                  charArray;
        integer                                           status; 


        // Initialize the count array
        cntArray[`INDEX_0] = `SLM_APP_TYPE_ID_MEMPRO;
        cntArray[`INDEX_1] = `SLM_MEMCORE_INIT_MSG_COUNTS_INT_CNT;
        cntArray[`INDEX_2] = `SLM_MEMCORE_INIT_MSG_COUNTS_INT_CNT;
        cntArray[`INDEX_3] = `SLM_MEMPRO_ZERO_CNT;
        cntArray[`INDEX_4] = `SLM_MEMPRO_ZERO_CNT;
        cntArray[`INDEX_5] = `SLM_MEMPRO_ZERO_CNT;
        cntArray[`INDEX_6] = `SLM_MEMPRO_ZERO_CNT;
 
        // Pack the integer array
        intArray[`INDEX_0] = `SLM_MEMCORE_INIT_MSG_COUNTS;
        intArray[`INDEX_1] = core_handle;
      
        // Post the call
        $slm_post_hdl( cntArray, intArray, slArray, charArray );
 
        // Extract status 
        status = cntArray[`SLM_POST_STATUS_IDX];
        // Do something with the status ????

    end

endtask // memcore_init_msg_counts




// ****************************************************************************************
//
//    MemPro TestBench Interface
//
// ****************************************************************************************

task mem_load;

    // Task arguments
    input  [(`SLM_MAX_STRING_SIZE-1):0] instance_id;
    input  [(`SLM_MAX_STRING_SIZE-1):0] load_file; 
    output [31:0] status;

    begin : this_block

        integer                                    core_handle;
        reg [((`SLM_POST_CNT_ARRAY_SIZE*32)-1):0]  cntArray;
        reg [((`SLM_MEMPRO_LOAD_INT_CNT*32)-1):0]  intArray;
        reg [0:0]                                  slArray;
        reg [(`SLM_MAX_STRING_SIZE-1):0]           charArray; 

        // Get the mempro (core) handle
        memcore_handle_internal( instance_id, `SLM_MEM_LOAD, core_handle, status );

        if ( core_handle == `SLM_HANDLE_INVALID )
        begin
            status = `SLM_TESTBENCH_FAILURE;
        end
        else
        begin
            // Initialize the count array
            cntArray[`INDEX_0] = `SLM_APP_TYPE_ID_MEMPRO;
            cntArray[`INDEX_1] = `SLM_MEMPRO_LOAD_INT_CNT;
            cntArray[`INDEX_2] = `SLM_MEMPRO_LOAD_INT_CNT;
            cntArray[`INDEX_3] = `SLM_MEMPRO_ZERO_CNT;
            cntArray[`INDEX_4] = `SLM_MEMPRO_ZERO_CNT;
            cntArray[`INDEX_5] = `SLM_MAX_STRING_SIZE;
            cntArray[`INDEX_6] = `SLM_MAX_STRING_SIZE;
    
            // Pack the integer array
            intArray[`INDEX_0] = `SLM_MEM_LOAD;
            intArray[`INDEX_1] = core_handle;
            intArray[`INDEX_2] = `SLM_MEMPRO_CORE_HANDLE;
	       
            // Load the character array
            charArray = load_file;
    
            // Post the call
            $slm_post_hdl( cntArray, intArray, slArray, charArray );
    
            // Extract status 
            status = cntArray[`SLM_POST_STATUS_IDX];
        end
    end

endtask // mem_load

// ****************************************************************************************

task mem_unload;

    // Task arguments
    input  [(`SLM_MAX_STRING_SIZE-1):0] instance_id;
    input  [(`SLM_MAX_ADDR_WIDTH-1):0]  low_address;
    input  [(`SLM_MAX_ADDR_WIDTH-1):0]  high_address;
    output [31:0] status;

    begin : this_block

        integer                                      i;
        integer                                      core_handle;
        integer                                      address_width;
        integer                                      data_width;
        reg [((`SLM_POST_CNT_ARRAY_SIZE*32)-1):0]    cntArray;
        reg [((`SLM_MEMPRO_UNLOAD_INT_CNT*32)-1):0]  intArray;
        reg [((`SLM_MAX_ADDR_WIDTH*2)-1):0]          slArray;
        reg [0:0]                                    charArray; 

        // Get the mempro (core) handle
        memcore_handle_internal( instance_id, `SLM_MEM_UNLOAD, core_handle, status );

        if ( core_handle == `SLM_HANDLE_INVALID )
        begin
            status = `SLM_TESTBENCH_FAILURE;
        end
        else
        begin
            memcore_width_info_internal( core_handle, address_width, data_width );

            // Initialize the count array
            cntArray[`INDEX_0] = `SLM_APP_TYPE_ID_MEMPRO;
            cntArray[`INDEX_1] = `SLM_MEMPRO_UNLOAD_INT_CNT;
            cntArray[`INDEX_2] = `SLM_MEMPRO_UNLOAD_INT_CNT;
            cntArray[`INDEX_3] = address_width * 2;
            cntArray[`INDEX_4] = cntArray[`INDEX_3];
            cntArray[`INDEX_5] = `SLM_MEMPRO_ZERO_CNT;
            cntArray[`INDEX_6] = `SLM_MEMPRO_ZERO_CNT;
    
            // Pack the integer array
            intArray[`INDEX_0] = `SLM_MEM_UNLOAD;
            intArray[`INDEX_1] = core_handle;
            intArray[`INDEX_2] = `SLM_MEMPRO_CORE_HANDLE;
            intArray[`INDEX_3] = address_width;
	       
            // Load the address boundaries into slArray
            for ( i=0; i < address_width; i=i+1 )
            begin
                slArray[i]               = low_address[i];
                slArray[address_width+i] = high_address[i];
            end
    
            // Post the call
            $slm_post_hdl( cntArray, intArray, slArray, charArray );
    
            // Extract status 
            status = cntArray[`SLM_POST_STATUS_IDX];
        end
    end

endtask // mem_unload

// ****************************************************************************************

task mem_dump;

    // Task arguments
    input  [(`SLM_MAX_STRING_SIZE-1):0] instance_id;
    input  [(`SLM_MAX_ADDR_WIDTH-1):0] low_address;
    input  [(`SLM_MAX_ADDR_WIDTH-1):0] high_address;
    input  [(`SLM_MAX_STRING_SIZE-1):0] dump_file; 
    input  [31:0] format; 
    output [31:0] status;

    begin : this_block

        integer                                     i;
        integer                                     core_handle;
        integer                                     address_width;
        integer                                     data_width;
        reg [((`SLM_POST_CNT_ARRAY_SIZE*32)-1):0]   cntArray;
        reg [((`SLM_MEMPRO_DUMP_INT_CNT*32)-1):0]   intArray;
        reg [((`SLM_MAX_ADDR_WIDTH*2)-1):0]         slArray;
        reg [(`SLM_MAX_STRING_SIZE-1):0]            charArray; 

        // Get the MemPro instance info
        memcore_handle_internal( instance_id, `SLM_MEM_DUMP, core_handle, status );

        if ( core_handle == `SLM_HANDLE_INVALID )
        begin
            status = `SLM_TESTBENCH_FAILURE;
        end
        else
        begin
            memcore_width_info_internal( core_handle, address_width, data_width );
    
            // Reset the count array for slm_mempro_dump
            cntArray[`INDEX_0] = `SLM_APP_TYPE_ID_MEMPRO;
            cntArray[`INDEX_1] = `SLM_MEMPRO_DUMP_INT_CNT;
            cntArray[`INDEX_2] = `SLM_MEMPRO_DUMP_INT_CNT;
            cntArray[`INDEX_3] = address_width * 2;
            cntArray[`INDEX_4] = cntArray[`INDEX_3];
            cntArray[`INDEX_5] = (`SLM_MAX_STRING_SIZE*2);
            cntArray[`INDEX_6] = (`SLM_MAX_STRING_SIZE*2);
    
            // Pack the integer array for slm_mempro_dump
            intArray[`INDEX_0] = `SLM_MEM_DUMP;
            intArray[`INDEX_1] = core_handle;
            intArray[`INDEX_2] = `SLM_MEMPRO_CORE_HANDLE;
            intArray[`INDEX_3] = format;
            intArray[`INDEX_4] = address_width;
	       
            // Load the address boundaries into slArray
            for ( i=0; i < address_width; i=i+1 )
            begin
                slArray[i]               = low_address[i];
                slArray[address_width+i] = high_address[i];
            end
    
            // Assign the character array
	   charArray = dump_file;

            // Post the call to slm_mempro_dump
            $slm_post_hdl( cntArray, intArray, slArray, charArray );
    
            // Extract status 
            status = cntArray[`SLM_POST_STATUS_IDX];
        end
    end

endtask  // mem_dump

// ****************************************************************************************

task mem_peek; 

      // Task arguments
      input  [(`SLM_MAX_STRING_SIZE-1):0] instance_id;
      input  [(`SLM_MAX_ADDR_WIDTH-1):0] address;
      output [(`SLM_MAX_DATA_WIDTH-1):0] data;
      output [31:0] status;

      begin : this_block

	 integer                                                i;
	 integer 						core_handle;
	 integer 						address_width;
	 integer 						data_width;
	 reg [((`SLM_POST_CNT_ARRAY_SIZE*32)-1):0] 		cntArray;
	 reg [((`SLM_MEMPRO_READ_INT_CNT*32)-1):0] 		intArray;
	 reg [((`SLM_MAX_ADDR_WIDTH+`SLM_MAX_DATA_WIDTH)-1):0] 	slArray;
	 reg [0:0]					        charArray;
	 
        // Get the MemPro instance info
        memcore_handle_internal( instance_id, `SLM_MEM_PEEK, core_handle, status );
        if ( core_handle == `SLM_HANDLE_INVALID )
        begin
            status = `SLM_TESTBENCH_FAILURE;
        end
        else
        begin
           memcore_width_info_internal( core_handle, address_width, data_width );
    
	   // Initialize the control array 
	   cntArray[`INDEX_0] = `SLM_APP_TYPE_ID_MEMPRO;
	   cntArray[`INDEX_1] = `SLM_MEMPRO_READ_INT_CNT;
	   cntArray[`INDEX_2] = `SLM_MEMPRO_READ_INT_CNT;
	   cntArray[`INDEX_3] = address_width + data_width;
	   cntArray[`INDEX_4] = address_width;
	   cntArray[`INDEX_5] = `SLM_MEMPRO_ZERO_CNT;
	   cntArray[`INDEX_6] = `SLM_MEMPRO_ZERO_CNT;
    
	   // Pack the integer array 
	   intArray[`INDEX_0] = `SLM_MEM_PEEK;
	   intArray[`INDEX_1] = core_handle;
	   intArray[`INDEX_2] = `SLM_MEMPRO_CORE_HANDLE;
    
	   // Assign the address to slArray
	   slArray = address;
    
	   // Post the call 
	   $slm_post_hdl( cntArray, intArray, slArray, charArray );
	    
	   // Extract status 
	   status = cntArray[`SLM_POST_STATUS_IDX];
	    
	   data = slArray;
	    
	end
      end

endtask

// ****************************************************************************************

task mem_poke;

    // Task arguments
    input  [(`SLM_MAX_STRING_SIZE-1):0] instance_id;
    input  [(`SLM_MAX_ADDR_WIDTH-1):0] address;
    input  [(`SLM_MAX_DATA_WIDTH-1):0] data;
    output [31:0] status;

     begin : this_block

        integer                                                i;
        integer                                                core_handle;
        integer                                                address_width;
        integer                                                data_width;
        reg [((`SLM_POST_CNT_ARRAY_SIZE*32)-1):0]              cntArray;
        reg [((`SLM_MEMPRO_WRITE_INT_CNT*32)-1):0]             intArray;
        reg [((`SLM_MAX_ADDR_WIDTH+`SLM_MAX_DATA_WIDTH)-1):0]  slArray;
        reg [0:0]                                              charArray; 

        // Get the MemPro instance info
        memcore_handle_internal( instance_id, `SLM_MEM_POKE, core_handle, status );

        if ( core_handle == `SLM_HANDLE_INVALID )
        begin
            status = `SLM_TESTBENCH_FAILURE;
        end
        else
        begin
            memcore_width_info_internal( core_handle, address_width, data_width );
    
            // Initialize the control array 
            cntArray[`INDEX_0] = `SLM_APP_TYPE_ID_MEMPRO;
            cntArray[`INDEX_1] = `SLM_MEMPRO_WRITE_INT_CNT;
            cntArray[`INDEX_2] = `SLM_MEMPRO_WRITE_INT_CNT;
            cntArray[`INDEX_3] = address_width + data_width;
            cntArray[`INDEX_4] = cntArray[`INDEX_3];
            cntArray[`INDEX_5] = `SLM_MEMPRO_ZERO_CNT;
            cntArray[`INDEX_6] = `SLM_MEMPRO_ZERO_CNT;
    
            // Pack the integer array 
            intArray[`INDEX_0] = `SLM_MEM_POKE;
            intArray[`INDEX_1] = core_handle;
            intArray[`INDEX_2] = `SLM_MEMPRO_CORE_HANDLE;
            intArray[`INDEX_3] = address_width;
            intArray[`INDEX_4] = data_width;
	   
            // Load the address and data into slArray
            for ( i=0; i < data_width; i=i+1 )
            begin
                slArray[i] = data[i];
            end
            for ( i=0; i < address_width; i=i+1 )
            begin
                slArray[data_width+i] = address[i];
            end
    
            // Post the call to slm_mempro_dump
            $slm_post_hdl( cntArray, intArray, slArray, charArray );
    
            // Extract status 
            status = cntArray[`SLM_POST_STATUS_IDX];
        end
     end

endtask

// ****************************************************************************************

task mem_trace;

    // Task arguments
    input  [(`SLM_MAX_STRING_SIZE-1):0] instance_id;
    input  [(`SLM_MAX_ADDR_WIDTH-1):0] low_address;
    input  [(`SLM_MAX_ADDR_WIDTH-1):0] high_address;
    input  [(`SLM_MAX_STRING_SIZE-1):0] signal;
    output [31:0] status;

    begin : this_block

        integer                                     i;
        integer                                     core_handle;
        integer                                     address_width;
        integer                                     data_width;
        reg [((`SLM_POST_CNT_ARRAY_SIZE*32)-1):0]   cntArray;
        reg [((`SLM_MEMPRO_TRACE_INT_CNT*32)-1):0]  intArray;
        reg [((`SLM_MAX_ADDR_WIDTH*2)-1):0]         slArray;
        reg [(`SLM_MAX_STRING_SIZE-1):0]            charArray;

        // Get the MemPro instance info
        memcore_handle_internal( instance_id, `SLM_MEM_TRACE, core_handle, status );

        if ( core_handle == `SLM_HANDLE_INVALID )
        begin
            status = `SLM_TESTBENCH_FAILURE;
        end
        else
        begin
            memcore_width_info_internal( core_handle, address_width, data_width );
    
            // Initialize the control array 
            cntArray[`INDEX_0] = `SLM_APP_TYPE_ID_MEMPRO;
            cntArray[`INDEX_1] = `SLM_MEMPRO_TRACE_INT_CNT;
            cntArray[`INDEX_2] = `SLM_MEMPRO_TRACE_INT_CNT;
            cntArray[`INDEX_3] = address_width * 2;
            cntArray[`INDEX_4] = cntArray[`INDEX_3];
            cntArray[`INDEX_5] = `SLM_MAX_STRING_SIZE;
            cntArray[`INDEX_6] = `SLM_MAX_STRING_SIZE;
    
            // Pack the integer array 
            intArray[`INDEX_0] = `SLM_MEM_TRACE;
            intArray[`INDEX_1] = core_handle;
            intArray[`INDEX_2] = `SLM_MEMPRO_CORE_HANDLE;
            intArray[`INDEX_3] = address_width;
            // The following identify the length values for signal and device
            // Since we don't need device, and can't do lengths, flag them with zeroes
            intArray[`INDEX_4] = 0;
            intArray[`INDEX_5] = 0;
    
            // Load the address boundaries into slArray
            for ( i=0; i < address_width; i=i+1 )
            begin
                slArray[i]               = low_address[i];
                slArray[address_width+i] = high_address[i];
            end

            // Assign the signal name to charArray
            charArray = signal;
    
            // Post the call to slm_mempro_trace
            $slm_post_hdl( cntArray, intArray, slArray, charArray );
    
            // Extract status 
            status = cntArray[`SLM_POST_STATUS_IDX];
        end
    end

endtask

// ****************************************************************************************

task mem_untrace;

    // Task arguments
    input  [(`SLM_MAX_STRING_SIZE-1):0] instance_id;
    input  [(`SLM_MAX_ADDR_WIDTH-1):0] low_address;
    input  [(`SLM_MAX_ADDR_WIDTH-1):0] high_address;
    output [31:0] status;

    begin : this_block

        integer                                       i;
        integer                                       core_handle;
        integer                                       address_width;
        integer                                       data_width;
        reg [((`SLM_POST_CNT_ARRAY_SIZE*32)-1):0]     cntArray;
        reg [((`SLM_MEMPRO_UNTRACE_INT_CNT*32)-1):0]  intArray;
        reg [((`SLM_MAX_ADDR_WIDTH*2)-1):0]           slArray;
        reg [0:0]                                     charArray; 

        // Get the MemPro instance info
        memcore_handle_internal( instance_id, `SLM_MEM_UNTRACE, core_handle, status );
        if ( core_handle == `SLM_HANDLE_INVALID )
        begin
            status = `SLM_TESTBENCH_FAILURE;
        end
        else
        begin
            memcore_width_info_internal( core_handle, address_width, data_width );
    
            // Initialize the control array 
            cntArray[`INDEX_0] = `SLM_APP_TYPE_ID_MEMPRO;
            cntArray[`INDEX_1] = `SLM_MEMPRO_UNTRACE_INT_CNT;
            cntArray[`INDEX_2] = `SLM_MEMPRO_UNTRACE_INT_CNT;
            cntArray[`INDEX_3] = address_width * 2;
            cntArray[`INDEX_4] = cntArray[`INDEX_3];
            cntArray[`INDEX_5] = `SLM_MEMPRO_ZERO_CNT;
            cntArray[`INDEX_6] = `SLM_MEMPRO_ZERO_CNT;
    
            // Pack the integer array 
            intArray[`INDEX_0] = `SLM_MEM_UNTRACE;
            intArray[`INDEX_1] = core_handle;
            intArray[`INDEX_2] = `SLM_MEMPRO_CORE_HANDLE;
            intArray[`INDEX_3] = address_width;
    
            // Load the address boundaries into slArray
            for ( i=0; i < address_width; i=i+1 )
            begin
                slArray[i]               = low_address[i];
                slArray[address_width+i] = high_address[i];
            end

    
            // Post the call to slm_mempro_untrace_
            $slm_post_hdl( cntArray, intArray, slArray, charArray );
    
            // Extract status 
            status = cntArray[`SLM_POST_STATUS_IDX];
        end
    end

endtask

// ****************************************************************************************
//
//  parameters:
//    user_handle  - (in) handle of device for which to search for events (0 is any)
//                   (out) handle of device for the returned trace event
//                     0 - no handle because no events found
//                   'n' - user handle of device with the traced access
//    mode         - (in) determines how the event is handled
//                         31                     2    1    0
//                      +----+--   -+----+----+----+----+----+
//                      |    reserved         |keep|last|inst|
//                      +----+-   --+----+----+----+----+----+
//                     inst - use specific user inst handle to find events
//                     last - controls which end of the queue is searched first
//                            1 - find the oldest event on the queue
//                            0 - find the newest event on the queue
//                     keep - control event removal from queue
//                            0 - remove the event from the queue
//                            1 - keep (don't remove) the event on the queue
//    addr         - (out) the address at which the traced access occured
//                     Address is undefined if no event was found.
//    data         - (out) the data transferred during the traced access.
//                     Data is undefined if no event was found.
//    op           - (out) whether the traced access was a read or write
//                     0 - READ operation
//                     1 - WRITE operation
//                    -1 - event queue is empty
//    q_empty      - (out) indicates whether more events are on the queue
//                     0 - more events are on the queue
//                     1 - the trace event queue is empty
//    status       - (out) return status for this command
//                    -1 - error reading the trace event queue
//                     0 - an event was successfully obtained from the trace event queue
//                     1 - (warning) trace event queue is empty
//

`define MEMPRO_GTE_MODE_OLDEST 2
`define MEMPRO_GTE_MODE_NEWEST 0
`define MEMPRO_GTE_MODE_OLDEST_INST 3
`define MEMPRO_GTE_MODE_NEWEST_INST 1
`define MEMPRO_GTE_MODE_POLL 4
`define MEMPRO_GTE_MODE_POLL_INST 5

`define MEMPRO_GTE_MODE_LASTOP 4

`define MEMPRO_GTE_OP_READ  0
`define MEMPRO_GTE_OP_WRITE 1
`define MEMPRO_GTE_OP_PEEK  2
`define MEMPRO_GTE_OP_POKE  3

task mem_get_traced_event;

  inout  [31:0] user_handle;
  input  [31:0] mode;
  output [(`SLM_MAX_ADDR_WIDTH-1):0] addr;
  output [(`SLM_MAX_DATA_WIDTH-1):0] data;
  output [(`SLM_MAX_DATA_WIDTH-1):0] bits;  // which bits were effected by this operation
  output [31:0] op;
  output [31:0] q_empty;
  output [31:0] status;

begin : this_block

  integer                                               address_width;
  integer                                               data_width;
  integer                                               i;
  integer                                               slidx;
  reg [((`SLM_POST_CNT_ARRAY_SIZE*32)-1):0]             cntArray;
  reg [((`SLM_MEMPRO_LASTOP_INT_CNT_OUT*32)-1):0]       intArray;
  reg [(`SLM_MAX_ADDR_WIDTH+`SLM_MAX_DATA_WIDTH-1):0]   slArray;
  reg [0:0]                                             charArray; 

  // 
  // Fix for STAR 51584 - CEC 09/12/01
  // Initialize data and address values here (to help compiler
  // optimization). These values MUST be set to zero to prevent
  // Xs in the output if variables presented to this task are
  // less wide than the task argument declarations.
  addr = `SLM_MAX_ADDR_WIDTH'b0;
  data = `SLM_MAX_DATA_WIDTH'b0;

  // Initialize the control array 
  cntArray[`INDEX_0] = `SLM_APP_TYPE_ID_MEMPRO;
  cntArray[`INDEX_1] = `SLM_MEMPRO_LASTOP_INT_CNT_OUT;
  cntArray[`INDEX_2] = 3;
  cntArray[`INDEX_3] = `SLM_MAX_ADDR_WIDTH+`SLM_MAX_DATA_WIDTH;
  cntArray[`INDEX_4] = `SLM_MEMPRO_ZERO_CNT;
  cntArray[`INDEX_5] = `SLM_MEMPRO_ZERO_CNT;
  cntArray[`INDEX_6] = `SLM_MEMPRO_ZERO_CNT;

  // Pack the integer array 
  intArray[`INDEX_0] = `SLM_MEM_LASTOP;
  intArray[`INDEX_1] = user_handle;
  intArray[`INDEX_2] = mode;
       
  // Post the call to slm_mempro_lastop
  $slm_post_hdl( cntArray, intArray, slArray, charArray );

  // Extract status 
  status = cntArray[`SLM_POST_STATUS_IDX];

  // Extract info from intArray
  user_handle   = intArray[`INDEX_0];
  op            = intArray[`INDEX_1];
  address_width = intArray[`INDEX_2];
  data_width    = intArray[`INDEX_3];

  q_empty       = address_width >> 8;
  address_width = address_width & 255;

  // Extract the address
  slidx = 0;
  if (address_width > 0) 
    begin
    for ( i=0; i < address_width; i=i+1 )
      begin
      addr[i] = slArray[slidx];
      slidx = slidx + 1;
      end
    end
  else
    begin
    addr = 'b0;
    end

  // Extract the data
  if (data_width > 0) 
    begin
    for ( i=0; i < data_width; i=i+1 )
      begin
      data[i] = slArray[slidx];
      slidx = slidx + 1;
      end

  // Extract the bits used mask
    for ( i=0; i < data_width; i=i+1 )
      begin
      bits[i] = slArray[slidx];
      slidx = slidx + 1;
      end
    end
  else
    begin
    data = 'b0;
    bits = 'b0;
    end

end

endtask

// ****************************************************************************************

task mem_lastop;

    // Task arguments
    output [31:0] user_handle;
    output [(`SLM_MAX_ADDR_WIDTH-1):0] address;
    output [(`SLM_MAX_DATA_WIDTH-1):0] data;
    output [31:0] readwriteflag;
    output [31:0] status;

    begin : this_block

        integer                                               address_width;
        integer                                               data_width;
        integer                                               i;
        reg [((`SLM_POST_CNT_ARRAY_SIZE*32)-1):0]             cntArray;
        reg [((`SLM_MEMPRO_LASTOP_INT_CNT_OUT*32)-1):0]       intArray;
        reg [(`SLM_MAX_ADDR_WIDTH+`SLM_MAX_DATA_WIDTH-1):0]   slArray;
        reg [0:0]                                             charArray; 

        // 
        // Fix for STAR 51584 - CEC 09/12/01
        // Initialize data and address values here (to help compiler
        // optimization). These values MUST be set to zero to prevent
        // Xs in the output if variables presented to this task are
        // less wide than the task argument declarations.
        address = `SLM_MAX_ADDR_WIDTH'b0;
        data = `SLM_MAX_DATA_WIDTH'b0;

        // Initialize the control array 
        cntArray[`INDEX_0] = `SLM_APP_TYPE_ID_MEMPRO;
        cntArray[`INDEX_1] = `SLM_MEMPRO_LASTOP_INT_CNT_OUT;
        cntArray[`INDEX_2] = `SLM_MEMPRO_LASTOP_INT_CNT;
        cntArray[`INDEX_3] = `SLM_MAX_ADDR_WIDTH+`SLM_MAX_DATA_WIDTH;
        cntArray[`INDEX_4] = `SLM_MEMPRO_ZERO_CNT;
        cntArray[`INDEX_5] = `SLM_MEMPRO_ZERO_CNT;
        cntArray[`INDEX_6] = `SLM_MEMPRO_ZERO_CNT;

        // Pack the integer array 
        intArray[`INDEX_0] = `SLM_MEM_LASTOP;
       
        // Post the call to slm_mempro_lastop
        $slm_post_hdl( cntArray, intArray, slArray, charArray );

        // Extract status 
        status = cntArray[`SLM_POST_STATUS_IDX];

        // Extract info from intArray
        user_handle   = intArray[`INDEX_0];
        readwriteflag = intArray[`INDEX_1];
        address_width = intArray[`INDEX_2];
        data_width    = intArray[`INDEX_3];

        // Extract the address
        for ( i=0; i < address_width; i=i+1 )
        begin
            address[i] = slArray[i];
        end

        // Extract the data
        for ( i=0; i < data_width; i=i+1 )
        begin
            data[i] = slArray[address_width+i];
        end
    end

endtask

// ****************************************************************************************

task mem_msg_level;

    // Task arguments
    input  [(`SLM_MAX_STRING_SIZE-1):0] instance_id;
    input  [31:0] filter;
    output [31:0] status;

    begin : this_block
        integer                                             core_handle;
        reg [((`SLM_POST_CNT_ARRAY_SIZE*32)-1):0]           cntArray;
        reg [((`SLM_MEMPRO_SET_MSG_LEVEL_INT_CNT*32)-1):0]  intArray;
        reg [0:0]                                           slArray;
        reg [0:0]                                           charArray; 

        // Get the mempro (core) handle
        memcore_handle_internal( instance_id, `SLM_MEM_MSG_LEVEL, core_handle, status );

        if ( core_handle == `SLM_HANDLE_INVALID )
        begin
            status = `SLM_TESTBENCH_FAILURE;
        end
        else
        begin
            // Initialize the count array
	   cntArray[`INDEX_0] = `SLM_APP_TYPE_ID_MEMPRO;
	   cntArray[`INDEX_1] = `SLM_MEMPRO_SET_MSG_LEVEL_INT_CNT;
	   cntArray[`INDEX_2] = `SLM_MEMPRO_SET_MSG_LEVEL_INT_CNT;
	   cntArray[`INDEX_3] = `SLM_MEMPRO_ZERO_CNT;
	   cntArray[`INDEX_4] = `SLM_MEMPRO_ZERO_CNT;
	   cntArray[`INDEX_5] = `SLM_MEMPRO_ZERO_CNT;
	   cntArray[`INDEX_6] = `SLM_MEMPRO_ZERO_CNT;

            // Pack the integer array
            intArray[`INDEX_0] = `SLM_MEM_MSG_LEVEL;
            intArray[`INDEX_1] = core_handle;
            intArray[`INDEX_2] = `SLM_MEMPRO_CORE_HANDLE;
            intArray[`INDEX_3] = filter;
	   
	   // Post the call
	   $slm_post_hdl( cntArray, intArray, slArray, charArray );

	   // Extract status 
	   status = cntArray[`SLM_POST_STATUS_IDX];
        end
    end

endtask

task mem_create_db;
      
      input [(`SLM_MAX_STRING_SIZE-1):0] db_file_name;
      input [(`SLM_MAX_STRING_SIZE-1):0] design_comment;
      output [31:0] status;

      begin : this_block
	 reg [((`SLM_POST_CNT_ARRAY_SIZE*32)-1):0] 	     cntArray;
	 reg [((`SLM_MEMPRO_SET_MSG_LEVEL_INT_CNT*32)-1):0]  intArray;
	 reg [0:0] 					     slArray;
	 reg [(`SLM_MAX_STRING_SIZE*2-1):0] 		     charArray; 


	 // Fill up the parameter array
	 intArray[`INDEX_0] = `SLM_MEM_CREATE_DB;
	 
	 // Post the function
	 // Pack cntArray
	 cntArray[`SLM_POST_APP_TYPE_ID_IDX]  = `SLM_APP_TYPE_ID_MEMPRO;
	 cntArray[`SLM_POST_INT_MAX_CNT_IDX]  = `SLM_MEMPRO_CREATE_DB_INT_CNT;
	 cntArray[`SLM_POST_INT_ACT_CNT_IDX]  = `SLM_MEMPRO_CREATE_DB_INT_CNT;
	 cntArray[`SLM_POST_SL_MAX_CNT_IDX]   = `SLM_MEMPRO_ZERO_CNT;
	 cntArray[`SLM_POST_SL_ACT_CNT_IDX]   = `SLM_MEMPRO_ZERO_CNT;
	 cntArray[`SLM_POST_CHAR_MAX_CNT_IDX] = (`SLM_MAX_STRING_SIZE*2);
	 cntArray[`SLM_POST_CHAR_ACT_CNT_IDX] = (`SLM_MAX_STRING_SIZE*2);
	 cntArray[`SLM_POST_STATUS_IDX] = 0;

	 charArray = {db_file_name, ":", design_comment};
	 
	 $slm_post_hdl( cntArray, intArray, slArray, charArray );

	 status = cntArray[`SLM_POST_STATUS_IDX];

      end // block: this_block

endtask

task mem_load_db;
      
      input [(`SLM_MAX_STRING_SIZE-1):0] db_file_name;
      output [31:0] status;

      begin : this_block
	 reg [((`SLM_POST_CNT_ARRAY_SIZE*32)-1):0] 	     cntArray;
	 reg [((`SLM_MEMPRO_SET_MSG_LEVEL_INT_CNT*32)-1):0]  intArray;
	 reg [0:0] 					     slArray;
	 reg [(`SLM_MAX_STRING_SIZE-1):0] 		     charArray; 


	 // Fill up the parameter array
	 intArray[`INDEX_0] = `SLM_MEM_LOAD_DB;
	 
	 // Post the function
	 // Pack cntArray
	 cntArray[`SLM_POST_APP_TYPE_ID_IDX]  = `SLM_APP_TYPE_ID_MEMPRO;
	 cntArray[`SLM_POST_INT_MAX_CNT_IDX]  = `SLM_MEMPRO_LOAD_DB_INT_CNT;
	 cntArray[`SLM_POST_INT_ACT_CNT_IDX]  = `SLM_MEMPRO_LOAD_DB_INT_CNT;
	 cntArray[`SLM_POST_SL_MAX_CNT_IDX]   = `SLM_MEMPRO_ZERO_CNT;
	 cntArray[`SLM_POST_SL_ACT_CNT_IDX]   = `SLM_MEMPRO_ZERO_CNT;
	 cntArray[`SLM_POST_CHAR_MAX_CNT_IDX] = `SLM_MAX_STRING_SIZE;
	 cntArray[`SLM_POST_CHAR_ACT_CNT_IDX] = `SLM_MAX_STRING_SIZE;
	 cntArray[`SLM_POST_STATUS_IDX] = 0;

	 charArray = db_file_name;

	 $slm_post_hdl( cntArray, intArray, slArray, charArray );

	 status = cntArray[`SLM_POST_STATUS_IDX];

      end // block: this_block

endtask

task mem_begin_history;
      
      input [(`SLM_MAX_STRING_SIZE-1):0] history_file_name;
      output [31:0] status;

      begin : this_block
	 reg [((`SLM_POST_CNT_ARRAY_SIZE*32)-1):0] 	     cntArray;
	 reg [((`SLM_MEMPRO_SET_MSG_LEVEL_INT_CNT*32)-1):0]  intArray;
	 reg [0:0] 					     slArray;
	 reg [(`SLM_MAX_STRING_SIZE-1):0] 		     charArray; 


	 // Fill up the parameter array
	 intArray[`INDEX_0] = `SLM_MEM_BEGIN_HISTORY;
	 
	 // Post the function
	 // Pack cntArray
	 cntArray[`SLM_POST_APP_TYPE_ID_IDX]  = `SLM_APP_TYPE_ID_MEMPRO;
	 cntArray[`SLM_POST_INT_MAX_CNT_IDX]  = `SLM_MEMPRO_BEGIN_HISTORY_INT_CNT;
	 cntArray[`SLM_POST_INT_ACT_CNT_IDX]  = `SLM_MEMPRO_BEGIN_HISTORY_INT_CNT;
	 cntArray[`SLM_POST_SL_MAX_CNT_IDX]   = `SLM_MEMPRO_ZERO_CNT;
	 cntArray[`SLM_POST_SL_ACT_CNT_IDX]   = `SLM_MEMPRO_ZERO_CNT;
	 cntArray[`SLM_POST_CHAR_MAX_CNT_IDX] = `SLM_MAX_STRING_SIZE;
	 cntArray[`SLM_POST_CHAR_ACT_CNT_IDX] = `SLM_MAX_STRING_SIZE;
	 cntArray[`SLM_POST_STATUS_IDX] = 0;

	 charArray = history_file_name;

	 $slm_post_hdl( cntArray, intArray, slArray, charArray );

	 status = cntArray[`SLM_POST_STATUS_IDX];

      end // block: this_block

endtask

task mem_end_history;

      output [31:0] status;

      begin : this_block
	 reg [((`SLM_POST_CNT_ARRAY_SIZE*32)-1):0] 	     cntArray;
	 reg [((`SLM_MEMPRO_SET_MSG_LEVEL_INT_CNT*32)-1):0]  intArray;
	 reg [0:0] 					     slArray;
	 reg [0:0]  					     charArray; 


	 // Fill up the parameter array
	 intArray[`INDEX_0] = `SLM_MEM_END_HISTORY;
	 
	 // Post the function
	 // Pack cntArray
	 cntArray[`SLM_POST_APP_TYPE_ID_IDX]  = `SLM_APP_TYPE_ID_MEMPRO;
	 cntArray[`SLM_POST_INT_MAX_CNT_IDX]  = `SLM_MEMPRO_END_HISTORY_INT_CNT;
	 cntArray[`SLM_POST_INT_ACT_CNT_IDX]  = `SLM_MEMPRO_END_HISTORY_INT_CNT;
	 cntArray[`SLM_POST_SL_MAX_CNT_IDX]   = `SLM_MEMPRO_ZERO_CNT;
	 cntArray[`SLM_POST_SL_ACT_CNT_IDX]   = `SLM_MEMPRO_ZERO_CNT;
	 cntArray[`SLM_POST_CHAR_MAX_CNT_IDX] = `SLM_MEMPRO_ZERO_CNT;
	 cntArray[`SLM_POST_CHAR_ACT_CNT_IDX] = `SLM_MEMPRO_ZERO_CNT;
	 cntArray[`SLM_POST_STATUS_IDX] = 0;

	 $slm_post_hdl( cntArray, intArray, slArray, charArray );

	 status = cntArray[`SLM_POST_STATUS_IDX];

      end // block: this_block

endtask



task mem_reset_msg_counts;

    // Task arguments
    input  [(`SLM_MAX_STRING_SIZE-1):0] instance_id;
    output [31:0] status;

    begin : this_block

        integer                                     i;
        integer                                     core_handle;
        reg [((`SLM_POST_CNT_ARRAY_SIZE*32)-1):0]   cntArray;
        reg [((`SLM_MEMPRO_RESET_MSG_CNTS_INT_CNT*32)-1):0]   intArray;
        reg [0:0]                                   slArray;
        reg [0:0]                                   charArray;

        // Get the MemPro instance info
        memcore_handle_internal( instance_id, `SLM_MEMPRO_RESET_MSG_CNTS, core_handle, status );

        if ( core_handle == `SLM_HANDLE_INVALID )
        begin
            status = `SLM_TESTBENCH_FAILURE;
        end
        else
        begin

            // Reset the count array for slm_mempro_dump
            cntArray[`INDEX_0] = `SLM_APP_TYPE_ID_MEMPRO;
            cntArray[`INDEX_1] = `SLM_MEMPRO_RESET_MSG_CNTS_INT_CNT;
            cntArray[`INDEX_2] = `SLM_MEMPRO_RESET_MSG_CNTS_INT_CNT;
            cntArray[`INDEX_3] = 0;
            cntArray[`INDEX_4] = 0;
            cntArray[`INDEX_5] = 0;
            cntArray[`INDEX_6] = 0;

            // Pack the integer array for slm_mempro_dump
            intArray[`INDEX_0] = `SLM_MEMPRO_RESET_MSG_CNTS;
            intArray[`INDEX_1] = core_handle;
            intArray[`INDEX_2] = `SLM_MEMPRO_CORE_HANDLE;
       

            // Post the call to slm_mempro_dump
            $slm_post_hdl( cntArray, intArray, slArray, charArray );

            // Extract status
            status = cntArray[`SLM_POST_STATUS_IDX];
        end
    end

endtask  // mem_reset_msg_counts


task mem_get_msg_counts;

    // Task arguments
    input  [(`SLM_MAX_STRING_SIZE-1):0] instance_id;
    output [31:0] errorCnt;
    output [31:0] warningCnt;
    output [31:0] noteCnt;
    output [31:0] status;

    begin : this_block

        integer                                     i;
        integer                                     core_handle;
        reg [((`SLM_POST_CNT_ARRAY_SIZE*32)-1):0]   cntArray;
        reg [((`SLM_MEMPRO_GET_MSG_CNTS_INT_CNT_OUT*32)-1):0]   intArray;
        reg [0:0]                                   slArray;
        reg [0:0]                                   charArray;

        // Get the MemPro instance info
        memcore_handle_internal( instance_id, `SLM_MEMPRO_GET_MSG_CNTS, core_handle, status );

        if ( core_handle == `SLM_HANDLE_INVALID )
        begin
            status = `SLM_TESTBENCH_FAILURE;
        end
        else
        begin

            // Reset the count array for slm_mempro_dump
            cntArray[`INDEX_0] = `SLM_APP_TYPE_ID_MEMPRO;
            cntArray[`INDEX_1] = `SLM_MEMPRO_GET_MSG_CNTS_INT_CNT_OUT;
            cntArray[`INDEX_2] = `SLM_MEMPRO_GET_MSG_CNTS_INT_CNT;
            cntArray[`INDEX_3] = 0;
            cntArray[`INDEX_4] = 0;
            cntArray[`INDEX_5] = 0;
            cntArray[`INDEX_6] = 0;

            // Pack the integer array for slm_mempro_dump
            intArray[`INDEX_0] = `SLM_MEMPRO_GET_MSG_CNTS;
            intArray[`INDEX_1] = core_handle;
            intArray[`INDEX_2] = `SLM_MEMPRO_CORE_HANDLE;
            //intArray[`INDEX_2] = 0;
            intArray[`INDEX_3] = 0;
       

            // Post the call to slm_mempro_dump
            $slm_post_hdl( cntArray, intArray, slArray, charArray );
            errorCnt   = intArray[`INDEX_1];
            warningCnt = intArray[`INDEX_2];
            noteCnt    = intArray[`INDEX_3];

            // Extract status
            status = cntArray[`SLM_POST_STATUS_IDX];
        end
    end

endtask  // mem_get_msg_counts





// ****************************************************************************************

