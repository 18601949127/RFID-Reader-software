/*****************************************************************
  HEADER INCLUDE FILE for ASKCSC.DLL 

  Copyright (C)1999-2002 by ASK SOPHIA ANTIPOLIS FRANCE
  All right reserved.

  Author : Thierry J. / Jean-Luc M. / Serge M. - ASK
*****************************************************************/


/*****************************************************************
  HISTORY :
  
Ver 4.05.03.253		 03-09-10  BL   Add long frames management
Ver 4.05.03.218	Beta 03-08-06  BL   Add mono search mode
									Add CTx512x class
									Add CSC_WriteSAMNumber command
									Add CSC_TransparentCommand and CSC_TransparentCommandConfig
Ver 4.04.03.022		 03-01-22  BL
Ver 4.04.02.333 Beta 02-11-19  BL	Pass RFU param to CSC in iCTX_512B_List
Ver 4.04.02.332 Alpha02-11-18  BL   Wait delay=25ms in CSC_ResetCSC()
									Add global variables for CSC_SendReseive timeout param
									Add CSC_SetTimings modifying those variables
Ver 4.03.00.275		 02-10-02  BL	Correct CSC_SearchCardExt in askcsc.def
Ver 4.02.00.246		 02-09-04  BL	Add ISOCommandContact()
									Add sCARD_SearchExt
									Add CSC_SearchCardExt() using sCARD_SearchExt + search_mask
									Change VerifyPIN() for clear mode PIN presentation
									Add PINStatus()
									Add MIFARE_Select()
Ver 4.01.00.133-Beta 02-08-21  BL	Add first CTx512B functions : list, select, read, update, halt
Ver 4.00.02.036		 02-02-05  SM   Add MIFARE, RS485, Speed commands
Ver 3.11.01.260		 01-09-17  SM	No modif
Ver 3.10.01.087		 01-03-28  CCV  harmonisation des commandes CTS (prevision CTM)
Ver 3.10.01.064		 01-03-05  CCV  Add CTS functions and modify CSC_SearchCard()
Ver 3.01.00.329	Beta 00-11-24  JLM  Add GEN 3XX Managment
Ver	2.01.00.132		 00-05-11  JLM  Check the reader version for GTML 
									compatibility
Ver	2.01.00.126		 00-05-05  JLM  Remove GTML_ChangeKey function
Ver 2.01.00.116      00-04-25  THJ  Add GTML class
Ver 1.93.00.061      00-03-01  THJ  Error CSC_ResetSAM ( vBuf[6] )
Ver 1.92.00.032      00-02-01  THJ  Error CSC_ISOCommand ( vBuf[4] )
Ver 1.91.99.322      99-11-12  THJ  Send ATR from ISSUER coupler
Ver 1.90.99.301      99-10-22  THJ  Correct Increase and Decrease Bug
Ver 1.80.99.257      99-09-09  THJ	Modify CSC_CardStopSearch
Ver 1.60.99.242      99-08-25  THJ	Special search
Ver 1.50.99.227      99-08-10  THJ	Parallel communication
Ver 1.07.99.142      99-05-18  THJ  First Commercial Version
Ver 1.06.99.130      99-05-06  THJ  Add the DEBUG LOG
Ver 1.05.99.119      99-03-26  THJ  Created
*****************************************************************/

#ifndef __ASKCSC_H__
#define __ASKCSC_H__


#include "csc_def.h"  // Constants defines CSC module


#ifdef __cplusplus
extern "C" {
#endif


// sCARD_Status Structure 
// for CD97_... or GTML_... functions
typedef struct sCARD_StatusTag
{
BYTE Code;		// Status Code
BYTE Byte1;		// First detail byte
BYTE Byte2;		// Last detail byte
}sCARD_Status;


typedef struct sCARD_SessionTag
{
BYTE NbApp;		// Number of Application
SHORT Path[128];// Path of the Applications
BYTE Data[29];	// Data record
}sCARD_Session;

typedef struct sCARD_SecurParamTag
{
BYTE  AccMode;	// Acces Mode
BYTE  SID;		// Short ID
WORD  LID;		// Long ID
BYTE  NKEY;		// Number of Key (SAM)
BYTE  RFU;		// Reserved for the KVC
}sCARD_SecurParam;


typedef struct sCARD_SearchTag
{
BYTE  CONT;		// Contact Mode
BYTE  ISOB;		// ISO B Protocol Mode
BYTE  ISOA;		// ISO A Protocol Mode
BYTE  TICK;		// Ticket Mode
BYTE  INNO;		// Innovatron Protocol Mode
}sCARD_Search;


typedef struct sCARD_SearchExtTag
{
BYTE  CONT;		// Contact Mode
BYTE  ISOB;		// ISO B Protocol Mode
BYTE  ISOA;		// ISO A Protocol Mode
BYTE  TICK;		// Ticket Mode
BYTE  INNO;		// Innovatron Protocol Mode
BYTE  MIFARE;	// Mifare Mode
BYTE  MV4k;		// MV4k protocol mode
BYTE  MV5k;		// MV5k protocol mode
BYTE  MONO;		// mono-search mode
}sCARD_SearchExt;


//-- for ascendent compatibility --------------------------------
// sCARD_Status Structure 
// for CD97_...  function
#define sCD97_Status sCARD_Status
#define sCD97_Session sCARD_Session



#ifndef __ASKCSC_IN__

/****************************************************************/
DWORD CSC_GetUSBNumDevices (DWORD *NumDevices);
/****************************************************************
Get number of CSC USB devices

OUTPUTS
	NumDevices return the number of USB devices

RETURNS
	RCSC_Ok
	RCSC_Fail
*****************************************************************/

/****************************************************************/
DWORD CSC_GetPCSCNumDevices (DWORD *NumDevices);
/****************************************************************
Get number of CSC PCSC devices

OUTPUTS
	NumDevices return the number of CSC PCSC devices

RETURNS
	RCSC_Ok
	RCSC_Fail
*****************************************************************/

/****************************************************************/
DWORD CSC_GetPCSCDeviceName (DWORD DeviceNumber,char *sName);
/****************************************************************
Get the name of DeviceNumber PCSC ASK reader

INPUTS
	DeviceNumber 

OUTPUTS
	sName 

RETURNS
	RCSC_Ok
	RCSC_Fail
*****************************************************************/

/****************************************************************/
DWORD WINAPI CSC_Open(LPSTR ComName);
/*****************************************************************
Open the PC communication port

INPUTS
  ComName     : Communication port Name (ex: "COM1", "LPT1" or "USB1") 

RETURNS
	RCSC_Ok
	RCSC_OpenCOMError
*****************************************************************/


/****************************************************************/
void WINAPI CSC_Close(void);
/*****************************************************************
Close the PC communication port
*****************************************************************/


/****************************************************************/
DWORD WINAPI CSC_ResetCSC(void);
/*****************************************************************
Initialize the CSC module

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_DataWrong
	RCSC_Timeout
	RCSC_Fail
	RCSC_Ok
****************************************************************/


/****************************************************************/
DWORD WINAPI CSC_DownloadStartCSC(void);
/*****************************************************************
Initialize the CSC Download transfert

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_DataWrong
	RCSC_Timeout
	RCSC_Fail
	RCSC_Ok
*****************************************************************/

/****************************************************************/
DWORD WINAPI CSC_DownloadStopCSC(void);
/*****************************************************************
Conclude the CSC download transfert

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_DataWrong
	RCSC_Timeout
	RCSC_Fail
	RCSC_Ok
*****************************************************************/

/****************************************************************/
DWORD WINAPI CSC_DesactiveCRC(BYTE Type, LPSTR Version);
/*****************************************************************
Desactive the Compute and Set of the CRC 

INPUTS
	Type     : 0xFF (desactive)/ else (activate)

OUTPUTS
	Version	: The text CSC version

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_Timeout
	RCSC_Ok
*****************************************************************/


/****************************************************************/
DWORD WINAPI CSC_VersionCSC(LPSTR Version);
/*****************************************************************
Return the CSC version

OUTPUTS
  Version	: The text CSC version

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_Timeout
	RCSC_Ok
*****************************************************************/


/****************************************************************/
DWORD WINAPI CSC_VersionDLL(LPSTR Version);
/*****************************************************************
Return the DLL version

OUTPUTS
  Version	: The text DLL version

RETURNS
  The DLL version : release
*****************************************************************/


/****************************************************************/
DWORD WINAPI CSC_SendReceive(DWORD Timeout,BYTE* BufIN,
							 DWORD LnIN,BYTE* BufOUT,LPDWORD LnOUT);
/*****************************************************************
Send a command frame to the CSC, and waits for the answer

INPUTS
	Timeout	: The command timeout value in milliseconds
	BufIN	: Command frame to send to the CSC
			  the frame is : <CMD><LEN><CLASS><IDENT><DATA><CRC>
	LnIN	: The frame size
	

OUTPUT
	BufOUT	: Contains the CSC answer frame
			  The frame is : <STA><LEN><CLASS><IDENT><DATA><CRC>
	LnOUT	: The answer frame size

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_DataWrong
	RCSC_CheckSum
	RCSC_NoAnswer
	RCSC_Timeout
	RCSC_Ok
*****************************************************************/


/****************************************************************/
DWORD WINAPI CSC_AddCRC(BYTE* Buf,LPDWORD Len);
/*****************************************************************
Compute and Set the CRC at the end of the buffer and change the
Len value

INPUTS
	Buf 	: Buffer without CRC
	Len 	: The buffer size
	
OUTPUT
	Len 	: The new buffer size

RETURNS
	RCSC_Overflow
	RCSC_Fail
	RCSC_Ok
*****************************************************************/


/****************************************************************/
DWORD WINAPI CSC_GetCommand(BYTE Command,BYTE* BufOUT,LPDWORD LnOUT);
/*****************************************************************
Return the CSC module command frame

INPUTS
	Command	: The command name (CSC_SYS_SOFTWARE_VERSION,...)
	
OUTPUT
	BufOUT 	: Command frame
	LnOUT	: The bufOUT size

RETURNS
	RCSC_Fail
	RCSC_Ok
*****************************************************************/

/****************************************************************/
DWORD WINAPI CSC_SearchCard(sCARD_Search Search,
							BYTE Forget,BYTE TimeOut,
							LPBYTE COM,LPDWORD lpcbATR,BYTE* lpATR);
/*****************************************************************
Starts the search for a card. This function must be called once
to set the CSC module in a search mode;

INPUTS
	Search		: Contain the type of tag to be find.
					- CONT : Contact Mode
					- ISOB : ISO B Protocol Mode
					- ISOA : ISO A Protocol Mode
					- TICK : Ticket Mode
					- INNO : Innovatron Protocol Mode

 	Forget		: Parameter to forget the last tag serial number.
	TimeOut		: Time Out of the command (x10ms).

OUTPUTS
	COM			: type of tag to be found
	lpcbATR		: is its length
	lpATR		: is the ISO ATR sent by the card

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_DataWrong
	RCSC_CheckSum
	RCSC_NoAnswer
	RCSC_Ok
*****************************************************************/

/****************************************************************/
DWORD WINAPI CSC_SearchCardExt(sCARD_SearchExt* search,DWORD search_mask,
							BYTE Forget,BYTE TimeOut,
							LPBYTE COM,LPDWORD lpcbATR,BYTE* lpATR);
/*****************************************************************
Starts the search for a card. This function must be called once
to set the CSC module in a search mode.
The mask specifies the relevant information stored in the sCARD_SearchExt structure

INPUTS
	Search		: Contain the type of tag to be found.
					- CONT : Contact Mode
					- ISOB : ISO B Protocol Mode
					- ISOA : ISO A Protocol Mode
					- TICK : Ticket Mode
					- INNO : Innovatron Protocol Mode
					- MIFARE : Mifare Mode
					- MV4k : MV4k protocol mode
					- MV5k : MV5k protocol mode
					- MONO : mono-search mode
	search_mask	: mask sepcifying the types of cards searched
 	Forget		: Parameter to forget the last tag serial number.
	TimeOut		: Time Out of the command (x10ms).

OUTPUTS
	COM			: type of tag to be found
	lpcbATR		: is its length
	lpATR		: is the ISO ATR sent by the card

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_DataWrong
	RCSC_CheckSum
	RCSC_NoAnswer
	RCSC_Ok
*****************************************************************/



/****************************************************************/
DWORD WINAPI CSC_CardConfig(BYTE SearchType);
/*****************************************************************
Configure the CSC in PSCL or contactless card mode

INPUTS
  SearchType	:
			- PSCL mode			: CSC_SEARCH_PSCL					
			- Contact less Card : CSC_SEARCH_CLESSCARD			

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_Timeout
	RCSC_Fail
	RCSC_Ok
*****************************************************************/


/****************************************************************/
DWORD WINAPI CSC_CardStartSearch(void);
/*****************************************************************
Starts the search for a card. This function must be called once
to set the CSC module in a search mode;
Then the CSC_CardFound may be called repeatedly to see if a card
was detected.

CSC_CardConfig function must be called before.

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_Timeout
	RCSC_Ok
*****************************************************************/


/****************************************************************/
DWORD WINAPI CSC_CardStopSearch(void);
/*****************************************************************
Stops the search for a card
This function must be called to stop a search running, when no
card has been found


RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_Timeout
	RCSC_Fail
	RCSC_Ok
*****************************************************************/


/****************************************************************/
DWORD WINAPI CSC_CardFound(BYTE* lpATR,LPDWORD lpcbATR);
/*****************************************************************
Look if a card was found.
The function CSC_CardStartSearch must have been called previously
to start the search


OUTPUTS
	lpATR	: is the ISO ATR sent by the card
	lpcbATR	: is its length


RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_Timeout
	RCSC_Fail
	RCSC_BadATR
	RCSC_Ok
*****************************************************************/


/****************************************************************/
DWORD WINAPI CSC_CardEnd(void);
/*****************************************************************
End the communication with the card


RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_DataWrong
	RCSC_CheckSum
	RCSC_NoAnswer
	RCSC_Ok
*****************************************************************/


/****************************************************************/
DWORD WINAPI CSC_AntennaOFF(void);
/*****************************************************************
Stop the antenna


RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_DataWrong
	RCSC_CheckSum
	RCSC_NoAnswer
	RCSC_Ok
*****************************************************************/


/****************************************************************/
DWORD WINAPI CSC_ISOCommand(BYTE* BufIN,DWORD LnIN,BYTE* BufOUT,
												LPDWORD lpLnOUT);
/*****************************************************************
Sends an ISO command, and returns the answer.


INPUTS
	BufIN	: the ISO Command to send to the card
	LnIN	: ISO command length
	
OUTPUT
	BufOUT	: Contains the answer
	lpLnOUT	: The answer size

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_Timeout
	RCSC_Fail
	RCSC_Ok
*****************************************************************/


/****************************************************************/
DWORD WINAPI CSC_TransparentCommandConfig(BYTE ISO,
										  BYTE addCRC,
										  BYTE checkCRC,
										  BYTE field,
										  BYTE* configISO,
										  BYTE* configAddCRC,
										  BYTE* configCheckCRC,
										  BYTE* configField);
/*****************************************************************
Configures the settings of "CSC_TransparentCommand"


INPUTS
	ISO :		0x00 : for getting the current config
				0x01 : for selecting ISOB
				0x02 : for selecting ISOA
	addCRC :	0x01 : the CRC will be computed and added to the frame
				else : nothing to add, the frame is sent directly
	checkCRC :	0x01 : the CRC of the frame received needs to be checked
				else : nothing to check
	field :		0x01 : the field will be switched ON when sending the frame
				else : no modification of the field
	
OUTPUT
	configISO :	0x01 : ISOB selected
				0x02 : ISOA selected
				0xFF : wrong protocol asked
	configAddCRC :		current configuration (same values as input)
	configCheckCRC :	current configuration (same values as input)
	configField :		current configuration (same values as input)

  
RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_Fail
	RCSC_DataWrong
	RCSC_NoAnswer
	RCSC_UnknowClassCommand
	RCSC_Ok
*****************************************************************/



/****************************************************************/
DWORD WINAPI CSC_TransparentCommand(BYTE* bufIn, DWORD lnIn,
									BYTE* status, DWORD* lnOut, BYTE* bufOut);
/*****************************************************************
sends and receives a transparent command, as previously configured with the
	CSC_TransparentCommandsConfig function



INPUTS
	bufIn	: data to send
	lnIn	: length of the data to send
	
OUTPUT
	bufOut	: data received
	lnOut	: length of the data received
	status	: status :	0x01 : CRC checked successfully (if asked)
						0xFF : wrong CRC (if asked to be checked)
						0x00 : CRC not checked

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_Fail
	RCSC_DataWrong
	RCSC_NoAnswer
	RCSC_UnknowClassCommand
	RCSC_Ok
*****************************************************************/


/****************************************************************/
DWORD WINAPI CSC_WriteSAMNumber(BYTE N_SAM, BYTE* status);
/*****************************************************************
writes the default SAM number in EEPROM for memory

INPUTS
	N_SAM : SAM number
	
OUTPUT
	status	: status : 0 = failure / 1 = success

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_Fail
	RCSC_DataWrong
	RCSC_NoAnswer
	RCSC_UnknowClassCommand
	RCSC_Ok
*****************************************************************/


/****************************************************************/
DWORD WINAPI CSC_ISOCommandContact(BYTE* BufIN,DWORD LnIN,
								   BYTE Case,
								   BYTE* BufOUT,DWORD* lpLnOUT);
/*****************************************************************
Sends an ISO command in contact mode, with the choice of the case :
IN, OUT, IN and OUT

INPUTS
	BufIN	: the ISO Command to send to the card
	LnIN	: ISO command length
	Case	: APDU case :	01 : IN
							02 : OUT
							03 : IN and OUT
	
OUTPUT
	BufOUT	: Contains the answer
	lpLnOUT	: The answer size

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_Fail
	RCSC_DataWrong
	RCSC_NoAnswer
	RCSC_UnknowClassCommand
	RCSC_Ok
*****************************************************************/



/****************************************************************/
DWORD WINAPI CSC_SelectSAM(BYTE N_SAM,BYTE Type);
/*****************************************************************
select the specified SAM.


OUTPUT
	N_SAM				Number of SAM to select.
	Type				Protocole used
RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_ErrorSAM
	RCSC_Ok
*****************************************************************/

/****************************************************************/
DWORD WINAPI CSC_ResetSAM(BYTE* lpATR,LPDWORD lpcbATR);
/*****************************************************************
Reset the SAM, and returns the ATR.


OUTPUT
	lpATR						Contains the ATR of the SAM
	lpcbATR						The ATR length

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_ErrorSAM
	RCSC_Ok
*****************************************************************/


/****************************************************************/
DWORD WINAPI CSC_ISOCommandSAM(BYTE* BufIN,DWORD LnIN,BYTE* BufOUT,
													LPDWORD lpLnOUT);
/*****************************************************************
Sends an ISO command to the SAM, and returns the answer.


INPUTS
	BufIN	: The ISO Command to send to the SAM
	LnIN	: ISO command length
	
OUTPUT
	BufOUT	: Contains the answer
	lpLnOUT	: The answer size

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_ErrorSAM
	RCSC_Ok
*****************************************************************/


/****************************************************************/
DWORD WINAPI CSC_SearchCSC(void);
/*****************************************************************
Search the CSC module, Open the PC communication port and the
CSC is reseted.

RETURNS
	RCSC_Ok
	RCSC_CSCNotFound
*****************************************************************/


/****************************************************************/
DWORD WINAPI CSC_Switch_Led_Buz(WORD Param);
/*****************************************************************
Switch ON or OFF LEDs and Buzzer

INPUTS
	Param : 
			- Bit0 :Antanna's LED1 (on if=1)
			- Bit1 :Antenna's LED2 (on if=1)
			- Bit2 :Antenna's Buzzer (on if=1)
			- Bit9 :CPU's LED1 (on if=1)
			- Bit10:CPU's LED2 (on if=1)
			- Bit11:CPU's LED3 (on if=1)
RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_ErrorSAM
	RCSC_Ok
*****************************************************************/


/****************************************************************/
DWORD WINAPI CD97_AppendRecord(BYTE AccMode,BYTE SID,LPBYTE Rec,
								BYTE RecSize,sCARD_Status* Status);
/*****************************************************************
Add a record to a circular EF


INPUTS
	AccMode	 : Card Access Mode ( CD97_ACCESS_MODE_DEFAULT, ...)
	SID		 : Small ID Number ( CD97_SID_RT_JOURNAL, ...)
	Rec      : Data to write
	RecSize  : The size of data to write

OUTPUT
	Status	 : Contains the card execution return status

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_Ok
*****************************************************************/


/****************************************************************/
DWORD WINAPI CD97_ChangeKey(BYTE KeyIndex,BYTE NewVersion,
											sCARD_Status* Status);
/*****************************************************************
Change the key / Personnalization


INPUTS
	KeyIndex   : Index of the key ( 01 - 03 )
	NewVersion : New version of the key ( <> 0 )

OUTPUT
	Status	   : Contains the card execution return status

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_Ok
*****************************************************************/


/****************************************************************/
DWORD WINAPI CD97_ChangePIN(LPBYTE OldPIN,LPBYTE NewPIN,
											sCARD_Status* Status);
/*****************************************************************
Change the PIN code


INPUTS
	OldPIN		 : Old PIN Code ( 4 characters )
	NewPIN		 : New PIN Code ( 4 characters )

OUTPUT
	Status		 : Contains the card execution return status

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_Ok
*****************************************************************/


/****************************************************************/
DWORD WINAPI CD97_Decrease(BYTE AccMode,BYTE SID,DWORD Value,
						   LPDWORD NewValue,sCARD_Status* Status);
/*****************************************************************
Decrease a counter file value

INPUTS
	AccMode		 : Card Access Mode ( CD97_ACCESS_MODE_DEFAULT, ...)
	SID			 : Small ID Number ( CD97_SID_RT_JOURNAL, ...)
	Value		 : Value decreased

OUTPUT
	NewValue	 : Counter new value ( Out of sessions Mode )
	Status		 : Contains the card execution return status

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_Ok
*****************************************************************/


/****************************************************************/
DWORD WINAPI CD97_Increase(BYTE AccMode,BYTE SID,DWORD Value,
						   LPDWORD NewValue,sCARD_Status* Status);
/*****************************************************************
Increase a counter file value

INPUTS
	AccMode		 : Card Access Mode ( CD97_ACCESS_MODE_DEFAULT, ...)
	SID			 : Small ID Number ( CD97_SID_RT_JOURNAL, ...)
	Value		 : Value increased

OUTPUT
	NewValue	 : Counter new value ( Out of sessions Mode )
	Status		 : Contains the card execution return status

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_Ok
*****************************************************************/


/****************************************************************/
DWORD WINAPI CD97_Invalidate(BYTE AccMode,sCARD_Status* Status);
/*****************************************************************
Invalidate the current DF

INPUTS
	AccMode		 : Card Access Mode ( CD97_ACCESS_MODE_DEFAULT, ...)

OUTPUT
	Status		 : Contains the card execution return status

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_Ok
*****************************************************************/


/****************************************************************/
DWORD WINAPI CD97_Rehabilitate(BYTE AccMode,sCARD_Status* Status);
/*****************************************************************
Rehabilitate the current DF

INPUTS
	AccMode		 : Card Access Mode ( CD97_ACCESS_MODE_DEFAULT, ...)

OUTPUT
	Status		 : Contains the card execution return status

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_Ok
*****************************************************************/


/****************************************************************/
DWORD WINAPI CD97_ReadRecord(BYTE AccMode,BYTE SID,BYTE NuRec,
							 BYTE DataLen,LPBYTE Data,sCARD_Status* Status);
/*****************************************************************
Read a record from linear or circular file

INPUTS
	AccMode		 : Card Access Mode ( CD97_ACCESS_MODE_DEFAULT, ...)
	SID			 : Small ID Number ( CD97_SID_RT_JOURNAL, ...)
	NuRec		 : Record number
	DataLen      : Number of bytes to be read ( record length )

OUTPUT
	Data		 : Data read
	Status		 : Contains the card execution return status

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_Ok
*****************************************************************/


/****************************************************************/
DWORD WINAPI CD97_SelectFile(BYTE SelectMode,LPBYTE IdPath,
							 BYTE IdPathLen,LPBYTE FCI,
							 sCARD_Status* Status);
/*****************************************************************
EF or DF select file

INPUTS
	SelectMode : Select Mode :
									CD97_SEL_MF	( Select the Master file )
									CD97_SEL_CURENT_EF ( Select the curent EF ID )
									CD97_SEL_PATH ( the path from MF ( exclude ) )

	IdPath     : ID number or path from MF ( exclude )
	IdPathLen  : IdPath length

OUTPUT
	FCI		   : File Control Information ( Length = 23 characters )
	Status	   : Contains the card execution return status

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_Ok
*****************************************************************/

/****************************************************************/
DWORD WINAPI CD97_StatusFile(BYTE SelectMode,LPBYTE IdPath,
										BYTE IdPathLen,LPBYTE FCI,
											sCARD_Status* Status);
/*****************************************************************
Same as iCD97_SelectFile but only give the file status without
select the file

INPUTS
	SelectMode : Select Mode :
									CD97_SEL_MF	( Select the Master file )
									CD97_SEL_CURENT_EF ( Select the curent EF ID )
									CD97_SEL_PATH ( the path from MF ( exclude ) )

	IdPath     : ID number or path from MF ( exclude )
	IdPathLen  : IdPath length

OUTPUT
	FCI		   : File Control Information ( Length = 23 characters )
	Status	   : Contains the card execution return status

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_Ok
*****************************************************************/

/****************************************************************/
DWORD WINAPI CD97_UpdateRecord(BYTE AccMode,BYTE SID,BYTE NuRec,
										BYTE DataLen,LPBYTE Data,
											sCARD_Status* Status);
/*****************************************************************
Erase and write a record to a EF

INPUTS
	AccMode	 : Card Access Mode ( CD97_ACCESS_MODE_DEFAULT, ...)
	SID		 : SID Number ( CD97_SID_RT_JOURNAL, ...)
	NuRec	 : Record number
	Data     : Data to write
	DataLen  : The size of data to write


OUTPUT
	Status	 : Contains the card execution return status

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_Ok
*****************************************************************/

/****************************************************************/
DWORD WINAPI CD97_WriteRecord(BYTE AccMode,BYTE SID,BYTE NuRec,
										BYTE DataLen,LPBYTE Data,
											sCARD_Status* Status);
/*****************************************************************
Write a record to a EF

INPUTS
	AccMode	 : Card Access Mode ( CD97_ACCESS_MODE_DEFAULT, ...)
	SID		 : SID Number ( CD97_SID_RT_JOURNAL, ...)
	NuRec	 : Record number
	Data     : Data to write
	DataLen  : The size of data to write


OUTPUT
	Status	 : Contains the card execution return status

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_Ok
*****************************************************************/

/****************************************************************/
DWORD WINAPI CD97_VerifyPIN(LPBYTE PIN,sCARD_Status* Status);
/*****************************************************************
PIN verification

INPUTS
	PIN		 : PIN code ( 4 characters )

OUTPUT
	Status	 : Contains the card execution return status

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_Ok
*****************************************************************/

/****************************************************************/
DWORD WINAPI CD97_Purchase(BYTE Type,LPBYTE DataLog,LPBYTE Disp,
											sCARD_Status* Status);
/*****************************************************************
Purchase with the Electronic Purse ( EP )

INPUTS
	Type	 : Purchase Type :
						- Purchase without display ( 0x00 )
						- Purchase with display    ( 0x01 )
	DataLog  : EP Log record ( 7 bytes )
	Disp	 : Display Message


OUTPUT
	Status	 : Contains the card execution return status

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_Ok
*****************************************************************/

/****************************************************************/
DWORD WINAPI CD97_GetEPStatus(BYTE Type,LPDWORD EP,LPBYTE Log,
											sCARD_Status* Status);
/*****************************************************************
Purchase with the Electronic Purse ( EP )

INPUTS
	Type	 : Transaction Type :
						- Loading Transaction   (0x00)
						- Purchase Transaction  (0x01)
						- Purchase cancellation (0x02)

OUTPUT
	EP		 : Electronic Purse Value

	Log      : if Type = Loading Transaction (0x00)
						 Log = Loading Log Record ( 22 characters )
						 if Type = 0x01 or 0x02
						 Log = Payement Log Record ( 19 characters )

	Status	 : Contains the card execution return status

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_Ok
*****************************************************************/

/****************************************************************/
DWORD WINAPI CD97_ReloadEP(LPBYTE ChargLog1,LPBYTE ChargLog2,
											sCARD_Status* Status);
/*****************************************************************
Reload Electronic Purse

INPUTS
	ChargLog1 : Loading Log record ( 5 characters )
								 ( Date, Money batch, Equipment type )

	ChargLog2 : Loading Log record, offset [0x08..0x13]
								 ( 5 characters ) ( Amount, Time )

OUTPUT
	Status	  : Contains the card execution return status

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_Ok
*****************************************************************/

/****************************************************************/
DWORD WINAPI CD97_OpenSession(BYTE Type,BYTE SID,BYTE NRec,
					sCARD_Session* Session,sCARD_Status* Status);
/*****************************************************************
Open the secured session

INPUTS
	Type    : Operation Type
					- Personnalization (0x00)
					- Reloading        (0x01)
					- Validation       (0x02)
	SID		: SID Number ( CD97_SID_RT_JOURNAL, ...)
	NRec	: Record number

OUTPUT
	Session : Contains the application data return value
	Status	: Contains the card execution return status

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_Ok
*****************************************************************/

/****************************************************************/
DWORD WINAPI CD97_CloseSession(LPBYTE Result,LPDWORD cbResult,
											sCARD_Status* Status);
/*****************************************************************
Close the secured session


OUTPUT
	Result	 : Order result
	cbResult : The Result length
	Status	 : Contains the card execution return status

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_Ok
*****************************************************************/

/****************************************************************/
DWORD WINAPI CD97_CancelPurchase(BYTE Type,LPBYTE DataLog,
								LPBYTE Disp,sCARD_Status* Status);
/*****************************************************************
Cancel Purchase with the Electronic Purse ( EP )

INPUTS
	Type	 : Purchase Type :
					- Purchase without display ( 0x00 )
					- Purchase with display    ( 0x01 )
	DataLog  : EP Log record ( 7 bytes )
	Disp	 : Display Message


OUTPUT
	Status	 : Contains the card execution return status

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_Ok
*****************************************************************/

/****************************************************************/
DWORD WINAPI GTML_AppendRecord(BYTE AccMode,BYTE SID,LPBYTE Rec,
								BYTE RecSize,sCARD_Status* Status);
/*****************************************************************
Add a record to a circular EF


INPUTS
	AccMode	 : Card Access Mode
	SID		 : Short ID Number
	Rec      : Data to write
	RecSize  : The size of data to write

OUTPUT
	Status	 : Contains the card execution return status

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_Ok
*****************************************************************/

/****************************************************************/
DWORD WINAPI GTML_ChangePIN(LPBYTE OldPIN,LPBYTE NewPIN,
											sCARD_Status* Status);
/*****************************************************************
Change the PIN code


INPUTS
	OldPIN		 : Old PIN Code ( 4 characters )
	NewPIN		 : New PIN Code ( 4 characters )

OUTPUT
	Status		 : Contains the card execution return status

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_Ok
*****************************************************************/

/****************************************************************/
DWORD WINAPI GTML_Decrease(BYTE AccMode,BYTE SID,DWORD Value,
							LPDWORD NewValue,sCARD_Status* Status);
/*****************************************************************
Decrease a counter file value

INPUTS
	AccMode		 : Card Access Mode
	SID			 : Small ID Number
	Value		 : Value decreased

OUTPUT
	NewValue	 : Counter new value ( Out of sessions Mode )
	Status		 : Contains the card execution return status

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_Ok
*****************************************************************/

/****************************************************************/
DWORD WINAPI GTML_Increase(BYTE AccMode,BYTE SID,DWORD Value,
							LPDWORD NewValue,sCARD_Status* Status);
/*****************************************************************
Increase a counter file value

INPUTS
	AccMode		 : Card Access Mode
	SID			 : Small ID Number
	Value		 : Value increased

OUTPUT
	NewValue	 : Counter new value ( Out of sessions Mode )
	Status		 : Contains the card execution return status

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_Ok
*****************************************************************/

/****************************************************************/
DWORD WINAPI GTML_Invalidate(BYTE AccMode,sCARD_Status* Status);
/*****************************************************************
Invalidate the current DF

INPUTS
	AccMode		 : Card Access Mode

OUTPUT
	Status		 : Contains the card execution return status

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_Ok
*****************************************************************/

/****************************************************************/
DWORD WINAPI GTML_Rehabilitate(BYTE AccMode,sCARD_Status* Status);
/*****************************************************************
Rehabilitate the current DF

INPUTS
	AccMode		 : Card Access Mode

OUTPUT
	Status		 : Contains the card execution return status

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_Ok
*****************************************************************/

/****************************************************************/
DWORD WINAPI GTML_ReadRecord(BYTE AccMode,BYTE SID,BYTE NuRec,
					BYTE DataLen,LPBYTE Data,sCARD_Status* Status);
/*****************************************************************
Read a record from linear or circular file

INPUTS
	AccMode	 : Card Access Mode
	SID		 : Small ID Number
	NuRec	 : Record number
	DataLen  : Number of bytes to be read ( record length )

OUTPUT
	Data	 : Data read
	Status	 : Contains the card execution return status

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_Ok
*****************************************************************/

/****************************************************************/
DWORD WINAPI GTML_SelectFile(BYTE SelectMode,LPBYTE IdPath,
										BYTE IdPathLen,LPBYTE FCI,
											sCARD_Status* Status);
/*****************************************************************
EF or DF select file

INPUTS
	SelectMode : Select Mode :
						CD97_SEL_MF	( Select the Master file )
						CD97_SEL_CURENT_EF ( Select the curent EF ID )
						CD97_SEL_PATH ( the path from MF ( exclude ) )

	IdPath     : ID number or path from MF ( exclude )
	IdPathLen  : IdPath length

OUTPUT
	FCI		   : File Control Information ( Length = 23 characters )
	Status	   : Contains the card execution return status

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_Ok
*****************************************************************/

/****************************************************************/
DWORD WINAPI GTML_UpdateRecord(BYTE AccMode,BYTE SID,BYTE NuRec,
										BYTE DataLen,LPBYTE Data,
											sCARD_Status* Status);
/*****************************************************************
Erase and write a record to a EF

INPUTS
	AccMode	: Card Access Mode
	SID		: SID Number
	NuRec	: Record number
	Data    : Data to write
	DataLen : The size of data to write


OUTPUT
	Status	: Contains the card execution return status

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_Ok
*****************************************************************/

/****************************************************************/
DWORD WINAPI GTML_WriteRecord(BYTE AccMode,BYTE SID,BYTE NuRec,
										BYTE DataLen,LPBYTE Data,
											sCARD_Status* Status);
/*****************************************************************
Write a record to a EF

INPUTS
	AccMode	: Card Access Mode
	SID		: SID Number
	NuRec	: Record number
	Data    : Data to write
	DataLen : The size of data to write


OUTPUT
	Status	: Contains the card execution return status

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_Ok
*****************************************************************/

/****************************************************************/
DWORD WINAPI GTML_VerifyPIN(LPBYTE PIN,sCARD_Status* Status);
/*****************************************************************
PIN verification

INPUTS
	PIN		 : PIN code ( 4 characters )

OUTPUT
	Status	 : Contains the card execution return status

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_Ok
*****************************************************************/

/****************************************************************/
DWORD WINAPI GTML_OpenSession(BYTE Type,BYTE SID,BYTE NRec,
					sCARD_Session* Session,sCARD_Status* Status);
/*****************************************************************
Open the secured session

INPUTS
	Type    : Operation Type
					- Personnalization (0x00)
					- Reloading        (0x01)
					- Validation       (0x02)
	SID		: SID Number
	NRec	: Record number

OUTPUT
	Session : Contains the application data return value
	Status	: Contains the card execution return status

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_Ok
*****************************************************************/

/****************************************************************/
DWORD WINAPI GTML_CloseSession(LPBYTE Result,LPDWORD cbResult,
											sCARD_Status* Status);
/*****************************************************************
Close the secured session


OUTPUT
	Result	 : Order result
	cbResult : The Result length
	Status	 : Contains the card execution return status

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_Ok
*****************************************************************/

//** Generic *****************************************************

/****************************************************************/
DWORD WINAPI AppendRecord(sCARD_SecurParam Secur,
						  LPBYTE Rec,BYTE RecSize,
						  sCARD_Status* Status);
/*****************************************************************
Add a record to a circular EF


INPUTS
	SecurParam	: Contain the parameters for the secury
					- AccMode :	Card Access Mode ( GEN_ACCESS_MODE_DEFAULT, ...)
					- SID	  : Short ID Number ( ex. : CD97_SID_RT_JOURNAL, ...)
					- LID	  : Long ID
					- NKEY	  : Number of Key which use in the SAM (in future KIF)
					- RUF	  : Reserved for KVC
	  
	Rec			: Data to write
	RecSize		: The size of data to write

OUTPUT
	Status		: Contains the card execution return status

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_Ok
*****************************************************************/



/****************************************************************/
DWORD WINAPI ChangePIN(sCARD_SecurParam SecurParam,
					   LPBYTE OldPIN,LPBYTE NewPIN,
					   sCARD_Status* Status);
/*****************************************************************
Change the PIN code


INPUTS
	SecurParam	: Contain the parameters for the secury
						- NKEY	  : Number of Key which use in the SAM (in future KIF)
						- RUF	  : Reserved for KVC
	OldPIN		: Old PIN Code ( 4 characters )
	NewPIN		: New PIN Code ( 4 characters )

OUTPUT
	Status		: Contains the card execution return status

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_Ok
*****************************************************************/


/****************************************************************/
DWORD WINAPI VerifyPIN(sCARD_SecurParam Secur,
						LPBYTE PIN,
						sCARD_Status* Status);
/*****************************************************************
PIN verification

INPUTS
	SecurParam	: Contain the parameters for the security
						- NKEY	  : Number of Key which use in the SAM (in future KIF)
							if NKEY=0, presentation in clear mode
						- RUF	  : Reserved for KVC
	PIN			: PIN code ( 4 characters )

OUTPUT
	Status		: Contains the card execution return status

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_Ok
*****************************************************************/

/****************************************************************/
DWORD WINAPI PINStatus(sCARD_Status* Status);
/*****************************************************************
checks the PIN status

INPUTS
	void

OUTPUT
	Status		: Contains the card execution return status

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_Fail
	RCSC_DataWrong
	RCSC_NoAnswer
	RCSC_UnknowClassCommand
	RCSC_Ok
*****************************************************************/


/****************************************************************/
DWORD WINAPI Increase(sCARD_SecurParam SecurParam,
					  BYTE ICount,DWORD Value,
					  LPDWORD NewValue,sCARD_Status* Status);
/*****************************************************************
Increase a counter file value

INPUTS
	SecurParam	: Contain the parameters for the secury
					- AccMode :	Card Access Mode ( GEN_ACCESS_MODE_DEFAULT, ...)
					- SID	  : Short ID Number ( ex. : CD97_SID_RT_JOURNAL, ...)
					- LID	  : Long ID
					- NKEY	  : Number of Key which use in the SAM (in future KIF)
					- RUF	  : Reserved for KVC
	Icount		: Index of the counter
	Value		: Value increased

OUTPUT
	NewValue	: Counter new value ( Out of sessions Mode )
	Status		: Contains the card execution return status

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_Ok
*****************************************************************/


/****************************************************************/
DWORD WINAPI Decrease(sCARD_SecurParam SecurParam,
					  BYTE ICount,DWORD Value,
					  LPDWORD NewValue,sCARD_Status* Status);
/*****************************************************************
Decrease a counter file value

INPUTS
	SecurParam	: Contain the parameters for the secury
					- AccMode :	Card Access Mode ( GEN_ACCESS_MODE_DEFAULT, ...)
					- SID	  : Short ID Number ( ex. : CD97_SID_RT_JOURNAL, ...)
					- LID	  : Long ID
					- NKEY	  : Number of Key which use in the SAM (in future KIF)
					- RUF	  : Reserved for KVC
	Value		: Value to decreased

OUTPUT
	NewValue	: Counter new value ( Out of sessions Mode )
	Status		: Contains the card execution return status

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_Ok
*****************************************************************/



/****************************************************************/
DWORD WINAPI Invalidate(sCARD_SecurParam SecurParam,
						sCARD_Status* Status);
/*****************************************************************
Invalidate the current DF

INPUTS
	SecurParam	: Contain the parameters for the secury
					- AccMode :	Card Access Mode ( GEN_ACCESS_MODE_DEFAULT, ...)
					- LID	  : Long ID
					- NKEY	  : Number of Key which use in the SAM (in future KIF)
					- RUF	  : Reserved for KVC
OUTPUT
	Status		: Contains the card execution return status

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_Ok
*****************************************************************/


/****************************************************************/
DWORD WINAPI Rehabilitate(sCARD_SecurParam SecurParam,
						  sCARD_Status* Status);
/*****************************************************************
Rehabilitate the current DF

INPUTS
	SecurParam	: Contain the parameters for the secury
					- AccMode :	Card Access Mode ( GEN_ACCESS_MODE_DEFAULT, ...)
					- LID	  : Long ID
					- NKEY	  : Number of Key which use in the SAM (in future KIF)
					- RUF	  : Reserved for KVC

OUTPUT
	Status		: Contains the card execution return status

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_Ok
*****************************************************************/


/****************************************************************/
DWORD WINAPI ReadRecord(sCARD_SecurParam Secur,
						BYTE NuRec,BYTE DataLen,
						LPBYTE Data,sCARD_Status* Status);
/*****************************************************************
Read a record from linear or circular file

INPUTS
	SecurParam	: Contain the parameters for the secury
					- AccMode :	Card Access Mode ( GEN_ACCESS_MODE_DEFAULT, ...)
					- SID	  : Short ID Number ( ex. : CD97_SID_RT_JOURNAL, ...)
					- LID	  : Long ID
					- NKEY	  : Number of Key which use in the SAM (in future KIF)
					- RUF	  : Reserved for KVC
	NuRec		: Record number
	DataLen		: Number of bytes to be read ( record length )

OUTPUT
	Data		: Data read
	Status		: Contains the card execution return status

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_Ok
*****************************************************************/


/****************************************************************/
DWORD WINAPI SelectFile(BYTE SelectMode,LPBYTE IdPath,
						BYTE IdPathLen,LPBYTE FCI,
						sCARD_Status* Status);
/*****************************************************************
EF or DF select file

INPUTS
	SelectMode : Select Mode :
					GEN_SEL_MF	( Select the Master file )
					GEN_SEL_CURENT_EF ( Select the curent EF ID )
					GEN_SEL_PATH ( the path from MF ( exclude ) )

	IdPath     : ID number or path from MF ( exclude )
	IdPathLen  : IdPath length

OUTPUT
	FCI		   : File Control Information ( Length = 23 characters )
	Status	   : Contains the card execution return status

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_Ok
*****************************************************************/

/****************************************************************/
DWORD WINAPI StatusFile(BYTE SelectMode,LPBYTE IdPath,
						BYTE IdPathLen,LPBYTE FCI,
						sCARD_Status* Status);
/*****************************************************************
Same as SelectFile but only give the file status without
select the file

INPUTS
	SelectMode : Select Mode :
					GEN_SEL_MF	( Select the Master file )
					GEN_SEL_CURENT_EF ( Select the curent EF ID )
					GEN_SEL_PATH ( the path from MF ( exclude ) )

	IdPath     : ID number or path from MF ( exclude )
	IdPathLen  : IdPath length

OUTPUT
	FCI		   : File Control Information ( Length = 23 characters )
	Status	   : Contains the card execution return status

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_Ok
*****************************************************************/

/****************************************************************/
DWORD WINAPI UpdateRecord(sCARD_SecurParam Secur,
						  BYTE NuRec,BYTE DataLen,
						  LPBYTE Data,sCARD_Status* Status);
/*****************************************************************
Erase and write a record to a EF

INPUTS
	SecurParam	: Contain the parameters for the secury
					- AccMode :	Card Access Mode ( GEN_ACCESS_MODE_DEFAULT, ...)
					- SID	  : Short ID Number ( ex. : CD97_SID_RT_JOURNAL, ...)
					- LID	  : Long ID
					- NKEY	  : Number of Key which use in the SAM (in future KIF)
					- RUF	  : Reserved for KVC
	NuRec		: Record number
	Data		: Data to write
	DataLen		: The size of data to write


OUTPUT
	Status		: Contains the card execution return status

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_Ok
*****************************************************************/


/****************************************************************/
DWORD WINAPI WriteRecord(sCARD_SecurParam Secur,
						 BYTE NuRec,BYTE DataLen,LPBYTE Data,
						 sCARD_Status* Status);
/*****************************************************************
Write a record to a EF

INPUTS
	SecurParam	: Contain the parameters for the secury
					- AccMode :	Card Access Mode ( GEN_ACCESS_MODE_DEFAULT, ...)
					- SID	  : Short ID Number ( ex. : CD97_SID_RT_JOURNAL, ...)
					- LID	  : Long ID
					- NKEY	  : Number of Key which use in the SAM (in future KIF)
					- RUF	  : Reserved for KVC
	NuRec		: Record number
	DataLen		: The size of data to write
	Data		: Data to write


OUTPUT
	Status		: Contains the card execution return status

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_Ok
*****************************************************************/


/****************************************************************/
DWORD WINAPI GetEPStatus_CD97(sCARD_SecurParam Secur,BYTE Type,
							  LPDWORD EP,LPBYTE Log,sCARD_Status* Status);
/*****************************************************************
Purchase with the Electronic Purse ( EP )

INPUTS
	SecurParam	: Contain the parameters for the secury
					- NKEY	  : Number of Key which use in the SAM (in future KIF)
					- RUF	  : Reserved for KVC

  Type			: Transaction Type :
					- Loading Transaction   (0x00)
					- Purchase Transaction  (0x01)
					- Purchase cancellation (0x02)

OUTPUT
	EP			: Electronic Purse Value

	Log			: if Type = Loading Transaction (0x00)
							 Log = Loading Log Record ( 22 characters )
							 if Type = 0x01 or 0x02
							 Log = Payement Log Record ( 19 characters )

	Status		: Contains the card execution return status

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_Ok
*****************************************************************/

/****************************************************************/
DWORD WINAPI Purchase_CD97(BYTE Type,LPBYTE DataLog,LPBYTE Disp,
											sCARD_Status* Status);
/*****************************************************************
Purchase with the Electronic Purse ( EP )

INPUTS
	Type	 : Purchase Type :
						- Purchase without display ( 0x00 )
						- Purchase with display    ( 0x01 )
	DataLog  : EP Log record ( 7 bytes )
	Disp	 : Display Message


OUTPUT
	Status	 : Contains the card execution return status

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_Ok
*****************************************************************/


/****************************************************************/
DWORD WINAPI CancelPurchase_CD97(BYTE Type,LPBYTE DataLog,
								LPBYTE Disp,sCARD_Status* Status);
/*****************************************************************
Cancel Purchase with the Electronic Purse ( EP )

INPUTS
	Type	 : Purchase Type :
					- Purchase without display ( 0x00 )
					- Purchase with display    ( 0x01 )
	DataLog  : EP Log record ( 7 bytes )
	Disp	 : Display Message


OUTPUT
	Status	 : Contains the card execution return status

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_Ok
*****************************************************************/

/****************************************************************/
DWORD WINAPI ReloadEP_CD97(LPBYTE ChargLog1,LPBYTE ChargLog2,
											sCARD_Status* Status);
/*****************************************************************
Reload Electronic Purse

INPUTS
	ChargLog1 : Loading Log record ( 5 characters )
								 ( Date, Money batch, Equipment type )

	ChargLog2 : Loading Log record, offset [0x08..0x13]
								 ( 5 characters ) ( Amount, Time )

OUTPUT
	Status	  : Contains the card execution return status

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_Ok
*****************************************************************/

/****************************************************************/
DWORD WINAPI OpenSession(BYTE Type,
						 sCARD_SecurParam Secur,
						 BYTE NRec,
						 sCARD_Session* Session,
						 sCARD_Status* Status);
/*****************************************************************
Open the secured session

INPUTS
	Type		: Operation Type
					- Personnalization (0x00)
					- Reloading        (0x01)
					- Validation       (0x02)
	SecurParam	: Contain the parameters for the secury
					- SID	  : Short ID Number ( ex. : CD97_SID_RT_JOURNAL, ...)
					- NKEY	  : Number of Key which use in the SAM (in future KIF)
					- RUF	  : Reserved for KVC
	NRec		: Record number

OUTPUT
	Session		: Contains the application data return value
	Status		: Contains the card execution return status

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_Ok
*****************************************************************/
/****************************************************************/
DWORD WINAPI OpenSessionExt(BYTE Type,
							sCARD_SecurParam Secur,
							BYTE NRec,BYTE* KVC,
							sCARD_Session* Session,
							sCARD_Status* Status);
/*****************************************************************
Open the secured session

INPUTS
	Type		: Operation Type
					- Personnalization (0x00)
					- Reloading        (0x01)
					- Validation       (0x02)
	SecurParam	: Contain the parameters for the security
					- SID	  : Short ID Number ( ex. : CD97_SID_RT_JOURNAL, ...)
					- NKEY	  : Number of Key which use in the SAM (in future KIF)
					- RUF	  : Reserved for KVC
	NRec		: Record number

OUTPUT
	Session		: Contains the application data return value
	Status		: Contains the card execution return status

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_Ok
*****************************************************************/

/****************************************************************/
DWORD WINAPI CloseSession(LPBYTE Result,LPDWORD cbResult,
											sCARD_Status* Status);
/*****************************************************************
Close the secured session


OUTPUT
	Result	 : Order result
	cbResult : The Result length
	Status	 : Contains the card execution return status

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_Ok
*****************************************************************/


/****************************************************************/
DWORD WINAPI Lock_Unlock(BYTE Type,
						 sCARD_Status* Status);
/*****************************************************************
Lock or unlock the card

INPUTS
	Type		: Operation Type
					- Lock the card (0x00)
					- Unlock the card (0x01)

OUTPUT
	Status		: Contains the card execution return status

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_Ok
*****************************************************************/

/****************************************************************/
DWORD WINAPI MultiIncrease( sCARD_SecurParam Secur,
							BYTE NumberCpt,LPBYTE Data,
							LPBYTE NewData,
							sCARD_Status* Status);
/*****************************************************************
Increase a counter file value

INPUTS
	SecurParam	: Contain the parameters for the security
					- AccMode :	Card Access Mode ( GEN_ACCESS_MODE_DEFAULT, ...)
					- SID	  : Short ID Number ( ex. : CD97_SID_RT_JOURNAL, ...)
					- LID	  : Long ID
					- NKEY	  : Number of Key which use in the SAM (in future KIF)
					- RUF	  : Reserved for KVC
	NumberCpt	: Number of counters to increase
	Data		: Values to increase (Lng=NumberCpt*4).
				  NumberCpt*Bloc :
						- Byte1		: Number of counter
						- Byte2-4	: Value to increase

OUTPUT
	NewData		: New value of the counters (Lng=NumberCpt*4).
				  NumberCpt*Bloc :
						- Byte1		: Number of counter
						- Byte2-4	: Value to increase
	Status		: Contains the card execution return status

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_Ok
*****************************************************************/


/****************************************************************/
DWORD WINAPI MultiDecrease( sCARD_SecurParam Secur,
							BYTE NumberCpt,LPBYTE Data,
							LPBYTE NewData,
							sCARD_Status* Status);
/*****************************************************************
Decrease several counters file value

INPUTS
	SecurParam	: Contain the parameters for the security
					- AccMode :	Card Access Mode ( GEN_ACCESS_MODE_DEFAULT, ...)
					- SID	  : Short ID Number ( ex. : CD97_SID_RT_JOURNAL, ...)
					- LID	  : Long ID
					- NKEY	  : Number of Key which use in the SAM (in future KIF)
					- RUF	  : Reserved for KVC
	NumberCpt	: Number of counters to decrease
	Data		: Values to decrease (Lng=NumberCpt*4).
				  NumberCpt*Bloc :
						- Byte1		: Number of counter
						- Byte2-4	: Value to decrease

OUTPUT
	NewData		: New value of the counters (Lng=NumberCpt*4).
				  NumberCpt*Bloc :
						- Byte1		: Number of counter
						- Byte2-4	: Value to decrease
	Status		: Contains the card execution return status

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_Ok
*****************************************************************/




/****************************************************************/
DWORD WINAPI CTx_Active (LPBYTE Data,BYTE* Status);
/*****************************************************************
Active CTx ticket

INPUTS
	Nothing
OUTPUTS
	Data	: Data read
	Status	: Contains the CTS execution return status


RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_UnknowClassCommand
	RCSC_Ok
*****************************************************************/

/****************************************************************/
DWORD WINAPI CTx_Read (	BYTE ADD, BYTE NB, LPBYTE Data,BYTE* Status);
/*****************************************************************
Read CTx ticket

INPUTS
	ADD		: adress of the first read (0 ... 31)
	NB		: Number of bytes to be read (from 1 up to 32)

OUTPUT
	Data	: Data read
	Status	: Contains the card execution return status

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_Ok
*****************************************************************/


/****************************************************************/
DWORD WINAPI CTx_Update (BYTE ADD, BYTE NB,
							LPBYTE DataToWrite,LPBYTE DataInCTS,
							LPBYTE Data, BYTE* Status);
/*****************************************************************
Update CTx ticket

INPUTS
	ADD			: adress of the first byte to write (0 ... 31)
	NB			: Number of bytes to be written (from 1 up to 32)
	Data		: Data to write
	DataInCTS	: Data already read and store in CTS application
OUTPUT
	Data	: Data read
	Status	: Contains the card execution return status

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_Ok
*****************************************************************/


/****************************************************************/
DWORD WINAPI CTx_Release (BYTE Param, BYTE* Status);
/*****************************************************************
Release CTx ticket

INPUTS
	Param
OUTPUTS
	Status	: Contains the CTx execution return status


RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_UnknowClassCommand
	RCSC_Ok
*****************************************************************/


/****************************************************************/
DWORD WINAPI CheckCertificate (BYTE KeyType, BYTE Param,
									BYTE LngBuffer, LPBYTE Buffer,
									BYTE LngCertificat, LPBYTE Certificat,
									BYTE *Status );
/*****************************************************************
Check Certificate

INPUTS
	KeyType
	Param	(RFU)
	LngBuffer
	Buffer
	LngCertificat
	Certificat
OUTPUTS
	Status	: Contains the CTS execution return status


RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_UnknowClassCommand
	RCSC_Ok
*****************************************************************/

/****************************************************************/
DWORD WINAPI GiveCertificate (BYTE KeyType, BYTE Param,
									BYTE LngBuffer, LPBYTE Buffer,
									BYTE LngCertificat, LPBYTE Certificat,
									BYTE *Status );
/*****************************************************************
Give Certificate

INPUTS
	KeyType
	Param	(RFU)
	LngBuffer
	Buffer
	LngCertificat
OUTPUTS
	Status	: Contains the CTS execution return status
	Certificat


RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_NoAnswer
	RCSC_UnknowClassCommand
	RCSC_Ok
*****************************************************************/



/*****************************************************************/
DWORD WINAPI CSC_ChangeRS485Address(BYTE CSCAddress485);
/*****************************************************************
Change the mode of protocol to CSC RS485 and set the Address value 

INPUTS
	CSCAddress485 : Address of the CSC on the RS485 Bus
	
OUTPUT

RETURNS
	RCSC_InputDataWrong		Bad Address Value go back to mode RS232
	RCSC_Ok					Good value
*****************************************************************/



/****************************************************************/
DWORD WINAPI CSC_ChangeDLLSpeed(DWORD DLLSpeed);
/*****************************************************************
Change the PC communication port baud rate and the CSC baud rate

INPUTS
  DLLSpeed :	New baud rate
  
OUTPUTS
  Status

RETURNS
	RCSC_Ok					Good execution
	RCSC_OpenCOMError		Fail in opening com port
	RCSC_InputDataWrong		Speed out of limit 9600-MAX_BAUDRATE
*****************************************************************/


/****************************************************************/
DWORD WINAPI CSC_SetTimings(DWORD func_timeout,DWORD search_timeout,
							DWORD RFU);
/*****************************************************************
Change the global timings values

INPUTS
  func_timeout		: timeout in CSC_SendReceive for DLL functions
  search_timeout	: timeout in CSC_SendReceive in CSC_SearchCard
						and CSC_SearchCardExt
  RFU				: RFU
  
OUTPUTS
  void

RETURNS
	RCSC_Ok					Good execution
*****************************************************************/


/*****************************************************************/
DWORD WINAPI CSC_ChangeCSCSpeed(DWORD RS232Speed, 
								DWORD RS485Speed, DWORD TTLSpeed, BYTE *Status);
/*****************************************************************
Send the Change Speed Command that change the CSC divisor for baud rate 
in EEPROM. This command will take effect only after a reset of the CSC.

INPUTS
  RS232Speed	:	Baud Rate choosen for the RS232 link (see microswitch configuration)
  RS485Speed	:	Baud Rate choosen for the RS485 link (see microswitch configuration)
  TTLSpeed		:	Baud Rate choosen for the serial TTL link (see microswitch configuration)
  
OUTPUTS
  Status :		Status of the operation (see CSC Interface documentation)

RETURNS
	RCSC_Ok					
	RCSC_OpenCOMError		
	RCSC_Timout				
	RCSC_Fail				
	RCSC_DataWrong		
	RCSC_Checksum		
*****************************************************************/


/*****************************************************************/
DWORD WINAPI CSC_SelectCID(BYTE CID, BYTE *Status);
/*****************************************************************
Update the global buffer for the SendReceive command.

INPUTS
	CID :		Index from 1 to 15 of the ISO14443 Card communication channel
OUTPUTS
	Status :	Status of operation 1 = Ok, 0 = Nok (Bad CID value)
RETURNS
	RCSC_Ok					
	RCSC_OpenCOMError		
	RCSC_Timout				
	RCSC_Fail				
	RCSC_DataWrong		
	RCSC_Checksum		
	RCSC_InputDataWrong
  
*****************************************************************/


/*****************************************************************/
DWORD WINAPI CSC_SelectDIV(BYTE Slot, BYTE Prot, BYTE *DIV, BYTE *Status);
/*****************************************************************
Update the global buffer for the SendReceive command.

INPUTS
  Slot :	Slot of the SAM
  Prot :	0 for Innovatron, 1 for ISO7816
  DIV :		4 bytes serial number used for alg diversification
OUTPUTS
	Status :	Status of operation 1 = Ok, 0 = Nok (Bad CID value)
RETURNS
	RCSC_Ok					
	RCSC_OpenCOMError		
	RCSC_Timout				
	RCSC_Fail				
	RCSC_DataWrong		
	RCSC_Checksum		
	RCSC_InputDataWrong
  
*****************************************************************/


/*****************************************************************/
DWORD WINAPI CSC_EHP_PARAMS(BYTE MaxNbCard, BYTE Req, BYTE NbSlot, BYTE AFI, BYTE AutoSelDiv);
/*****************************************************************
Update the global buffer for the SendReceive command.

INPUTS
	Slot :	Slot of the SAM
	Prot :	0 for Innovatron, 1 for ISO7816
	DIV  :	4 bytes serial number used for alg diversification
OUTPUTS
	None 
RETURNS
	RCSC_Ok					
	RCSC_OpenCOMError		
	RCSC_Timout				
	RCSC_Fail				
	RCSC_DataWrong		
	RCSC_Checksum		
	RCSC_InputDataWrong
  
*****************************************************************/


/*****************************************************************/
DWORD WINAPI MIFARE_LoadReaderKeyIndex(BYTE KeyIndex, LPBYTE KeyVal, BYTE *Status);
/*****************************************************************
Load a MIFARE Key in one of the 32 locations of the Reader in EEPROM
that will be used by their Index for the Cryptographic operation by 
the Crypto Module.

INPUTS
  KeyIndex :	Index from 0 to 31 of the key to load in the Reader
  KeyVal :		Value of the key (6 bytes LSB First)
  
OUTPUTS
  Status :		Status of the operation (see CSC Interface documentation)

RETURNS
	RCSC_Ok					
	RCSC_OpenCOMError		
	RCSC_Timout				
	RCSC_Fail				
	RCSC_DataWrong		
	RCSC_Checksum		
*****************************************************************/


/*****************************************************************/
DWORD WINAPI MIFARE_ChangeKey(BYTE InitialKeyAorB, BYTE NumSector, 
							  BYTE InitialKeyIndex, BYTE FinalKeyAorB, 
							  LPBYTE NewKeyA, LPBYTE NewAccessBits, 
							  LPBYTE NewKeyB, LPBYTE MifareType, 
							  LPBYTE SerialNumber, BYTE *Status);
/*****************************************************************
Change a MIFARE Key in the card : 
* Realise the authentication of the sector with the key indexed by the initialKey specified
* Change the trailer block by a write operation with control made on the Access bits
* And then realise the finale authentication of the sector with the new keys

INPUTS
	InitialKeyAorB	:	Choice of the key needed for authentication before key change operation
	NumSector		:	Sector on which the ChangeKey operation need to be performed
	InitialKeyIndex :	Index from 0 to 31 of the Reader key used for initial authentication
	FinalKeyAorB	:	Choice of the key needed for authentication after key change operation  
	NewKeyA			:	(6 Bytes) New value for the A Key (Be Carefull it must be coded MSB first)
	NewAccessBits	:	(4 Bytes) New value for Access bits area
	NewKeyB			:	(6 Bytes) New value for the B Key (Be Carefull it must be coded MSB first) 
  
OUTPUTS
	Status			:	Status of the operation (see CSC Interface documentation)
	MifareType		:	Type of the card authenticated (08 for Mifare Classic) 
	SerialNumber	:	(4 Bytes) Serial Number of the card authenticated 

RETURNS
	RCSC_Ok					
	RCSC_OpenCOMError		
	RCSC_Timout				
	RCSC_Fail				
	RCSC_DataWrong		
	RCSC_Checksum		
*****************************************************************/

/*****************************************************************/
DWORD WINAPI MIFARE_Select(BYTE* SerialNumber,
						   BYTE  SerialNumberLn,
						   BYTE* Status,
						   BYTE* SerialNumberOut);
/*****************************************************************
Selects a MIFARE card with its unique ID. Enables to detect a card in case of collision.

INPUTS
	SerialNumber	:	Buffer containing the serial Number of teh card to select
	SerialNumberLn	:	Length of the serial number
  
OUTPUTS
	Status			:	Status of the operation (see CSC Interface documentation)
	SerialNumberOut	:	Buffer containing the serial Number of the card selected

RETURNS
	RCSC_Ok					
	RCSC_OpenCOMError		
	RCSC_Timout				
	RCSC_Fail				
	RCSC_DataWrong		
	RCSC_Checksum		
*****************************************************************/

/*****************************************************************/
DWORD WINAPI MIFARE_Authenticate(BYTE NumSector, BYTE KeyAorB, 
							  BYTE KeyIndex, LPBYTE MifareType, 
							  LPBYTE SerialNumber, BYTE *Status);
/*****************************************************************
Change a MIFARE Key in the card : 
* Realise the authentication of the sector with the key indexed by the initialKey specified
* Change the trailer block by a write operation with control made on the Access bits
* And then realise the finale authentication of the sector with the new keys

INPUTS
	NumSector		:	Sector to authenticate
	KeyAorB			:	Choice of the key needed for authentication  
	KeyIndex		:	Index from 0 to 31 of the Reader key used for authentication
  
OUTPUTS
	MifareType		:	Type of the card authenticated (08 for Mifare Classic) 
	SerialNumber	:	(4 Bytes) Serial Number of the card authenticated 
	Status			:	Status of the operation (see CSC Interface documentation)

RETURNS
	RCSC_Ok					
	RCSC_OpenCOMError		
	RCSC_Timout				
	RCSC_Fail				
	RCSC_DataWrong		
	RCSC_Checksum		
*****************************************************************/


/*****************************************************************/
DWORD WINAPI MIFARE_Halt(void);
/*****************************************************************
Disable a MIFARE card to forbid authenticated operation.

INPUTS
	None  
OUTPUTS
	None 

RETURNS
	RCSC_Ok					
	RCSC_OpenCOMError		
	RCSC_Timout				
	RCSC_Fail				
	RCSC_DataWrong		
	RCSC_Checksum		
*****************************************************************/


/*****************************************************************/
DWORD WINAPI MIFARE_ReadBlock(BYTE NumBlock, 
							  LPBYTE DataRead, BYTE *Status);
/*****************************************************************
Read a block in a MIFARE card : for this operation, the sector need to
be previously authenticated by an authenticate or read_sector command

INPUTS
	NumBlock		:	Block number from 0 to 63 
  
OUTPUTS
	Status			:	Status of the operation (see CSC Interface documentation)
	DataRead		:	(16 bytes) DataRead in the card  or  
						(5 Bytes ) Mifare Type and serial Number in case 
									of bad transmission error

RETURNS
	RCSC_Ok					
	RCSC_OpenCOMError		
	RCSC_Timout				
	RCSC_Fail				
	RCSC_DataWrong		
	RCSC_Checksum		
*****************************************************************/


/*****************************************************************/
DWORD WINAPI MIFARE_ReadSector(BYTE NumSector, BYTE KeyAorB, 
							  BYTE KeyIndex, LPBYTE MifareType, 
							  LPBYTE SerialNumber, LPBYTE DataRead, 
							  BYTE *Status);
/*****************************************************************
Read a block in a MIFARE card : for this operation, the sector is authenticated and read
the authentication can be used for other following operation 
like increment, decrement, writeblock, .../...

INPUTS
	NumSector		:	Sector to authenticate and read
	KeyAorB			:	Choice of the key needed for authentication  
	KeyIndex		:	Index from 0 to 31 of the Reader key used for authentication
  
OUTPUTS
	Status			:	Status of the operation (see CSC Interface documentation)
	MifareType		:	Type of the card authenticated (08 for Mifare Classic) 
	SerialNumber	:	(4 Bytes) Serial Number of the card authenticated 
	DataRead		:	(64 bytes) data read in the sector specified

RETURNS
	RCSC_Ok					
	RCSC_OpenCOMError		
	RCSC_Timout				
	RCSC_Fail				
	RCSC_DataWrong		
	RCSC_Checksum		
*****************************************************************/


/*****************************************************************/
DWORD WINAPI MIFARE_WriteBlock(BYTE NumBlock, LPBYTE DataToWrite, 
							  LPBYTE DataVerif, BYTE *Status);
/*****************************************************************
Write a block in a MIFARE card : for this operation, the sector need to
be previously authenticated by an authenticate or read_sector command

INPUTS
	NumBlock		:	Block number from 0 to 63 
	DataToWrite		:	(16 bytes) Data to write in the block (the whole block is written) 
  
OUTPUTS
	Status			:	Status of the operation (see CSC Interface documentation)
	DataVerif		:	(16 bytes) DataRead in the card  or  
						(5 Bytes ) Mifare Type and serial Number in case 
									of bad transmission error

RETURNS
	RCSC_Ok					
	RCSC_OpenCOMError		
	RCSC_Timout				
	RCSC_Fail				
	RCSC_DataWrong		
	RCSC_Checksum		
*****************************************************************/


/*****************************************************************/
DWORD WINAPI MIFARE_DecrementValue(BYTE NumBlock, LPBYTE Substract, 
							  LPBYTE Verif, BYTE *Status);
/*****************************************************************
Decrement a Value block in a MIFARE card : for this operation, the sector need to
be previously authenticated by an authenticate or read_sector command

INPUTS
	NumBlock		:	Block number from 0 to 63 (must be previously configured as a value block)
	Substract		:	(4 bytes) value to substract to the counter 
  
OUTPUTS
	Status			:	Status of the operation (see CSC Interface documentation)
	Verif			:	(4 bytes) Counter value read in the card after the operation
						(5 Bytes ) Mifare Type and serial Number in case 
									of bad transmission error

RETURNS
	RCSC_Ok					
	RCSC_OpenCOMError		
	RCSC_Timout				
	RCSC_Fail				
	RCSC_DataWrong		
	RCSC_Checksum		
*****************************************************************/


/*****************************************************************/
DWORD WINAPI MIFARE_IncrementValue(BYTE NumBlock, LPBYTE Addition, 
							  LPBYTE Verif, BYTE *Status);
/*****************************************************************
Increment a Value block in a MIFARE card : For this operation, the sector need to
be previously authenticated by an authenticate or read_sector command

INPUTS
	NumBlock		:	Block number from 0 to 63 (must be previously configured as a value block)
	Addition		:	(4 bytes) value to Add to the counter 
  
OUTPUTS
	Status			:	Status of the operation (see CSC Interface documentation)
	Verif			:	(4 bytes) Counter value read in the card after the operation
						(5 Bytes ) Mifare Type and serial Number in case 
									of bad transmission error

RETURNS
	RCSC_Ok					
	RCSC_OpenCOMError		
	RCSC_Timout				
	RCSC_Fail				
	RCSC_DataWrong		
	RCSC_Checksum		
*****************************************************************/


/*****************************************************************/
DWORD WINAPI MIFARE_BackUpRestoreValue(BYTE Origine, BYTE Destination, BYTE *Status);
/*****************************************************************
Perform a copy of a value block to an other value block location 
in a given sector of a MIFARE card : For this operation, the sector need to
be previously authenticated by an authenticate or read_sector command
The two blocks must be in the same sector

INPUTS
	Origine			:	Block number from 0 to 63 (must be previously configured as a value block)
	Destination		:	Block number from 0 to 63 (must be previously configured as a value block)
  
OUTPUTS
	Status			:	Status of the operation (see CSC Interface documentation)

RETURNS
	RCSC_Ok					
	RCSC_OpenCOMError		
	RCSC_Timout				
	RCSC_Fail				
	RCSC_DataWrong		
	RCSC_Checksum		
*****************************************************************/


/****************************************************************/
DWORD WINAPI CTx512B_List(BYTE RFU, BYTE* nbTickets,BYTE* serialNumbers,
						  BYTE* status);
/*****************************************************************
LIST CTX512B tickets
Performs anticollision and answers serial numbers of all the chips
present in the antenna field

INPUTS
	RFU				: 0x00, RFU
OUTPUTS
	nbTickets		: number of tickets in the antenna field
	serialNumbers	: list of the serial numbers retrieved
					(2 LSB serial number bytes for each ticket)
	status			: CTX512B execution status returned


RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_Fail
	RCSC_DataWrong
	RCSC_NoAnswer
	RCSC_UnknowClassCommand
	RCSC_Ok
*****************************************************************/


/****************************************************************/
DWORD WINAPI CTx512B_Select(BYTE* serialNumber,BYTE* serialNumberRead,
							BYTE* status);
/*****************************************************************
SELECT CTX512B
Selects a ticket with its serial number

INPUT
	serialNumber : pointer to the buffer containing the serial
					number (2 bytes)

OUTPUTS
	serialNumberRead	: pointer to serial number read (2 bytes)
						(sould be equal to serialNumber)
	status				: CTX512B execution status returned


RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_Fail
	RCSC_DataWrong
	RCSC_NoAnswer
	RCSC_UnknowClassCommand
	RCSC_Ok
*****************************************************************/


/****************************************************************/
DWORD WINAPI CTx512B_Read (BYTE ADD,BYTE NB,BYTE* dataRead,BYTE* status);
/*****************************************************************
READ CTX512B
Reads a number of bytes (NB) from a given address (ADD)

INPUTS
	ADD		: adress of the first byte (0 ... 63)
	NB		: Number of bytes to be read (from 1 up to 64)

OUTPUT
	dataRead	: pointer to data read
	status		: CTX512B execution status returned

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_Fail
	RCSC_DataWrong
	RCSC_NoAnswer
	RCSC_UnknowClassCommand
	RCSC_Ok
*****************************************************************/


/****************************************************************/
DWORD WINAPI CTx512B_Update(BYTE ADD, BYTE NB,BYTE* dataToWrite,
							BYTE* dataRead, BYTE* status);
/*****************************************************************
UPDATE CTX512B
deletion if necessary, update then checking (reading bytes written)

INPUTS
	ADD			: adress of the first byte to write (0 ... 63)
	NB			: Number of bytes to write (from 1 up to 64)
	dataToWrite	: Data to write
	dataInTicket: Data already read and stored in the CTx512B

OUTPUT
	dataRead	: Data read
	status		: CTX512B execution status returned

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_Fail
	RCSC_DataWrong
	RCSC_NoAnswer
	RCSC_UnknowClassCommand
	RCSC_Ok
*****************************************************************/


/****************************************************************/
DWORD WINAPI CTx512B_Halt (BYTE param, BYTE* status);
/*****************************************************************
HALT CTX512B

INPUTS
	param	0x00 : desactivates ticket using 'desactivate' instruction
			(others RFU)
OUTPUTS
	status	: CTX512B execution status returned


RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_Fail
	RCSC_DataWrong
	RCSC_NoAnswer
	RCSC_UnknowClassCommand
	RCSC_Ok
*****************************************************************/


/****************************************************************/
DWORD WINAPI CTx512x_List(BYTE	RFU, BYTE* nbTickets,
						  BYTE* serialNumbers, BYTE* status);
/*****************************************************************
LIST CTX512X tickets
Performs anticollision and answers serial numbers of all the chips
present in the antenna field

INPUTS
	RFU				: 0x00, RFU
OUTPUTS
	nbTickets		: number of tickets in the antenna field
	serialNumbers	: list of the serial numbers retrieved
					(2 LSB serial number bytes for each ticket)
	status			: CTX512X execution status returned


RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_Fail
	RCSC_DataWrong
	RCSC_NoAnswer
	RCSC_UnknowClassCommand
	RCSC_Ok
*****************************************************************/


/****************************************************************/
DWORD WINAPI CTx512x_Select(BYTE* serialNumber,
							BYTE* serialNumberRead, BYTE* status);
/*****************************************************************
SELECT CTX512X
Selects a ticket with its serial number

INPUT
	serialNumber : pointer to the buffer containing the serial
					number (2 bytes)

OUTPUTS
	serialNumberRead	: pointer to serial number read (2 bytes)
						(sould be equal to serialNumber)
	status				: CTX512X execution status returned


RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_Fail
	RCSC_DataWrong
	RCSC_NoAnswer
	RCSC_UnknowClassCommand
	RCSC_Ok
*****************************************************************/


/****************************************************************/
DWORD WINAPI CTx512x_Read (BYTE ADD, BYTE NB, BYTE* dataRead,
						   BYTE* status);
/*****************************************************************
READ CTX512X
Reads a number of bytes (NB) from a given address (ADD)

INPUTS
	ADD		: adress of the first byte (0 ... 63)
	NB		: Number of bytes to be read (from 1 up to 64)

OUTPUT
	dataRead	: pointer to data read
	status		: CTX512X execution status returned

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_Fail
	RCSC_DataWrong
	RCSC_NoAnswer
	RCSC_UnknowClassCommand
	RCSC_Ok
*****************************************************************/


/****************************************************************/
DWORD WINAPI CTx512x_Update(BYTE ADD, BYTE NB, BYTE* dataToWrite,
							  BYTE* dataRead, BYTE* status);
/*****************************************************************
UPDATE CTX512X
deletion if necessary, update then checking (reading bytes written)

INPUTS
	ADD			: adress of the first byte to write (0 ... 63)
	NB			: Number of bytes to write (from 1 up to 64)
	dataToWrite	: Data to write

OUTPUT
	dataRead	: Data read
	status		: CTX512X execution status returned

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_Fail
	RCSC_DataWrong
	RCSC_NoAnswer
	RCSC_UnknowClassCommand
	RCSC_Ok
*****************************************************************/


/****************************************************************/
DWORD WINAPI CTx512x_Halt (BYTE param, BYTE* status);
/*****************************************************************
HALT CTX512X

INPUTS
	param	0x00 : desactivates ticket using 'desactivate' instruction
			(others RFU)
OUTPUTS
	status	: CTX512X execution status returned


RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_Fail
	RCSC_DataWrong
	RCSC_NoAnswer
	RCSC_UnknowClassCommand
	RCSC_Ok
*****************************************************************/


/****************************************************************/
DWORD WINAPI CTx512x_Write(BYTE ADD, BYTE NB, BYTE* dataToWrite,
							  BYTE* dataRead, BYTE* status);
/*****************************************************************
WRITE CTX512X
deletion if necessary, update then checking (reading bytes written)

INPUTS
	ADD			: adress of the first byte to write (0 ... 63)
	NB			: Number of bytes to write (from 1 up to 64)
	dataToWrite	: Data to write

OUTPUT
	dataRead	: Data read (former existing data computed with the
						logical OR with the written data)
	status		: CTX512X execution status returned

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_Fail
	RCSC_DataWrong
	RCSC_NoAnswer
	RCSC_UnknowClassCommand
	RCSC_Ok
*****************************************************************/


/****************************************************************/
DWORD WINAPI CTx512x_Authenticate(BYTE ADD,
								BYTE kif_kref,
								BYTE kvc_zero,
								BYTE* status,
								BYTE* dataSAMLength,
								BYTE* dataSAM);
/*****************************************************************
Authenticate CTX512X

Authentication of a CTM512B area

INPUTS
	ADD			: address of the area to authenticate
	kif_kref	: specifies the KIF or the key reference
					(if key reference used, kvc_zero must be set to 0x00)
	kvc_zero	: specifies the KVC if the KIF has been specified in kif_kref
					(if the KIF has not been specified in kif_kref, must be set to 0x00)

OUTPUT
	status		: CTX512X execution status returned
	dataSAMLength : length of the data returned in dataSAM
	dataSAM		: buffer containing the SAM status returned when
					an error occurs, i.e. when status = $06

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_Fail
	RCSC_DataWrong
	RCSC_NoAnswer
	RCSC_UnknowClassCommand
	RCSC_Ok
*****************************************************************/



/****************************************************************/
DWORD WINAPI CTx512x_WriteKey( BYTE kif_kref,
							BYTE kvc_zero,
							BYTE* status,
							BYTE* dataSAMLength,
							BYTE* dataSAM);
/*****************************************************************
WriteKey CTM512B

Compute and write the key in the CTM512B

INPUTS
	kif_kref	: specifies the KIF or the key reference
					(if key reference used, kvc_zero must be set to 0x00)
	kvc_zero	: specifies the KVC if the KIF has been specified in kif_kref
					(if the KIF has not been specified in kif_kref, must be set to 0x00)

OUTPUT
	status		: CTX512X execution status returned
	dataSAMLength : length of the data returned in dataSAM
	dataSAM		: buffer containing the SAM status returned when
					an error occurs, i.e. when status = $06

RETURNS
	RCSC_OpenCOMError
	RCSC_TXError
	RCSC_Fail
	RCSC_DataWrong
	RCSC_NoAnswer
	RCSC_UnknowClassCommand
	RCSC_Ok
*****************************************************************/



#endif /* __ASKCSC_IN__ */


#ifdef __cplusplus
}
#endif


#endif /* __ASKCSC_H__ */
