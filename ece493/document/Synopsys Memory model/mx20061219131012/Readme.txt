                   Synopsys DesignWare Memory Models
                        Tue Dec 19 13:10:31 2006


Introduction
-------------
  This readme file accompanies DesignWare Memory Model downloads from the 
  DesignWare Memory Central web site:

    http://synopsys.com/products/designware/memorycentral


Memory Models Included in this Package
--------------------------------------
  cy7c0831v_mx : v01008


Installation of your downloaded DesignWare Memory Models
--------------------------------------------------------
  Note: You must have the DWMM technology software package installed before
	you can install a DWMM memory model - for more information see

	http://synopsys.com/products/designware/memorycentral/dwmm_tfaq.html

  1. Extract the installation image:
       sl_unzip.platform mximage_name.zip
       This extracts the image to a new directory image_name/platform
       (for example, mx20020516140235/hp700).
  2. Make sure your LMC_HOME environment variable is set to the path that
     contains the DWMM technology software package (see step 3 on page 33).
  3. Move to the image_name/platform directory (which contains the
     installation image), and invoke the Admin tool (sl_admin):
       % sl_admin.csh
       After a moment, the Admin window opens, displaying the Install From
       dialog.
  4. Click Open, then click Install.
     Installation then begins. The process displays status messages to show
     its progress, and displays 'Install complete' when finished.
  5. Exit the Admin tool by selecting File > Exit.
     Note: You'll need to perform this process once for each platform you're
           installing.


Getting Support
----------------
North American customers:
  Call the hotline at 1-800-445-1888 Monday through
  Friday from 7:00 AM to 5 PM Pacific Time.

International customers:
    Call your local sales office.
