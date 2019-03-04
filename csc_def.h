/*****************************************************************
  CONSTANTS DEFINES for ASKCSC.DLL ( csc_def.h )

  ANSI 'C' Language.

  Copyright (C)2002-1999 by ASK SOPHIA ANTIPOLIS FRANCE
  All right reserved.

  Author : Thierry J. / Serge M. - ASK 
*****************************************************************/


/*****************************************************************
  HISTORY :
  
Ver 4.05.03.253		 03-09-10  BL   Add long frames management
Ver 4.05.03.218	Beta 03-08-06  BL   Add mono search mode
									Add CTx512x class
									Add CSC_WriteSAMNumber command
									Add CSC_TransparentCommand and CSC_TransparentCommandConfig
Ver 4.04.03.022		 03-01-22  BL
Ver 4.04.02.333 Beta 02-11-19  BL
Ver 4.04.02.332 Alpha02-11-18  BL
Ver 4.03.00.275		 02-10-02  BL	Correct CSC_SearchCardExt in askcsc.def
Ver 4.02.00.246		 02-09-04  BL	Add ISOCommandContact()
									Add sCARD_SearchExt
									Add CSC_SearchCardExt() using sCARD_SearchExt + search_mask
									Change VerifyPIN() for clear mode PIN presentation
									Add PINStatus()
									Add MIFARE_Select()
Ver 4.01.00.133-Beta 02-08-21  BL	Add first CTx512B defines : list, select, read, update, halt
Ver 4.00.02.036		 02-02-05  SM	Add Error code and new class constantes
Ver 3.01.00.329	Beta 00-11-24  JLM  Add GEN 3XX Managment
Ver	2.01.00.136		 00-05-15  JLM  Add GTML defines
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
Ver 1.05.99.119      99-03-26  THJ  Created
*****************************************************************/


#ifndef __CSC_DEF_H__
#define __CSC_DEF_H__


/* DLL Export Function return */

#define RCSC_Ok											0x8001
#define RCSC_OpenCOMError								0x8002
#define RCSC_NoAnswer									0x8003
#define RCSC_CheckSum									0x8004
#define RCSC_Fail										0x8005
#define RCSC_CardNotFound								0x8006
#define RCSC_AntennaFails								0x8007
#define RCSC_Timeout									0x8008
#define RCSC_DataWrong									0x8009
#define RCSC_Overflow									0x800A
#define RCSC_ErrorSAM									0x800B
#define RCSC_CSCNotFound								0x800C
#define RCSC_BadATR										0x800D
#define RCSC_TXError									0x800E
#define RCSC_WarningVersion								0x800F
#define RCSC_SelectSAMError								0x8010
#define RCSC_UnknownClassCommand						0x8011
#define RCSC_InputDataWrong								0x8012

/* search masks for CSC_SearchCardExt function */

#define SEARCH_MASK_CONT								0x0001
#define SEARCH_MASK_ISOB								0x0002
#define SEARCH_MASK_ISOA								0x0004
#define SEARCH_MASK_TICK								0x0008
#define SEARCH_MASK_INNO								0x0010
#define SEARCH_MASK_MIFARE								0x0020
#define SEARCH_MASK_MV4K								0x0040
#define SEARCH_MASK_MV5K								0x0080
#define SEARCH_MASK_MONO								0x0100


/* CSC Protocol value */

#define CSC_CMD_RES										0x01
#define CSC_CMD_STOP									0x02
#define CSC_CMD_EXEC									0x80

#define CSC_STA_ANS										0x01
#define CSC_STA_STOP									0x04
#define CSC_STA_RES										0x10
#define CSC_STA_ERROR									0x80


/* Function class */

#define CSC_CLA_DOWNLOAD								0x00
#define CSC_CLA_SYSTEM									0x01
#define CSC_CLA_GTML									0x02
#define CSC_CLA_CD97									0x03
#define CSC_CLA_CERTIF									0x04
#define CSC_CLA_GEN										0x05
#define CSC_CLA_CTX										0x06
#define CSC_RATP										0x07 // Reserved by Ratp for compatibility
#define CSC_CLA_MIFARE									0x10


/* DOWNLOAD Class Functions */

#define CSC_DOW_START_DOWNLOAD							0x01
#define CSC_DOW_STOP_DOWNLOAD							0x02
#define CSC_DOW_WRITE_FLASH								0x03
#define CSC_DOW_CHANGE									0x04
#define	CSC_WRITE_SAM_NUMBER							0x06


/* SYSTEM Class Functions */

#define CSC_SYS_SOFTWARE_VERSION						0x01
#define CSC_SYS_SEARCH_STOP								0x02
#define CSC_SYS_ENTER_HUNT_PHASE						0x03
#define CSC_SYS_END_TAG_COMMUNICATION					0x04
#define CSC_SYS_GET_COMMUNICATION_STATUS				0x05
#define CSC_SYS_SET_APGEN_EXTENSION						0x06
#define CSC_SYS_SET_TAG_COMMUNICATION_PARAMETERS		0x07
//#define CSC_SYS_SET_SAM_COMMUNICATION_PARAMETERS		0x08
#define CSC_SYS_SWITCH_OFF_ANTENNA						0x0E
#define CSC_SYS_SET_ANTENNA_TRANSPARENT_MODE			0x11
#define CSC_SYS_SEND_TO_ANTENNA 						0x12
#define CSC_SYS_RESET_SAM								0x13
#define CSC_SYS_SEND_TO_SAM								0x14
#define CSC_SYS_SELECT_CID								0x15
#define CSC_SYS_SELECT_DIV								0x16
#define CSC_SYS_EHP_PARAMS								0x17
//#define CSC_SYS_LOAD_DATA_SAM							0x1A
#define CSC_SYS_SELECT_SAM								0x19
#define CSC_SYS_SWITCH_SIGNALS							0x18
#define	CSC_TRANSP_COMMAND_CONFIG						0x20
#define	CSC_TRANSP_COMMAND_SEND							0x21


/* Antenna Type */

#define CSC_SYS_ANTENNA_1								0x00
#define CSC_SYS_ANTENNA_2								0x01
#define CSC_SYS_ANTENNA_3								0x02
#define CSC_SYS_ANTENNA_4								0x03
#define CSC_SYS_ANTENNA_1_2								0x81
#define CSC_SYS_ANTENNA_1_2_3							0x82
#define CSC_SYS_ANTENNA_1_2_3_4							0x83
#define CSC_SYS_ANTENNA_1_MONO							0x40
#define CSC_SYS_ANTENNA_2_MONO							0x41
#define CSC_SYS_ANTENNA_3_MONO							0x42
#define CSC_SYS_ANTENNA_4_MONO							0x43
#define CSC_SYS_ANTENNA_1_2_MONO						0xC1
#define CSC_SYS_ANTENNA_1_2_3_MONO						0xC2
#define CSC_SYS_ANTENNA_1_2_3_4_MONO					0xC3


/* communication badge */
#define CSC_SYS_TAG_NO_DATA_RECEIVED					0x00
#define CSC_SYS_TAG_DATA_RECEIVED						0x01
#define CSC_SYS_TAG_DATA_ERROR							0xFF
#define CSC_SYS_TAG_FRAMING_ERROR						0xFE
#define CSC_SYS_TAG_OVERFLOW_ERROR						0xFD
#define CSC_SYS_TAG_TIME_OUT_DATA						0xFC
#define CSC_SYS_TAG_CRC_ERROR							0xFB

#define CSC_SYS_GDW8									0x01
#define CSC_SYS_BPSK_TELEALIM							0x03


/* Search Type */
#define CSC_SEARCH_PSCL									CSC_SYS_GDW8
#define CSC_SEARCH_CLESSCARD							CSC_SYS_BPSK_TELEALIM


/* SetAPGEN Extentions */
#define CSC_SYS_ATR										0x80
#define CSC_SYS_NO_ATR									0x00


/* modes transparents */
#define CSC_SYS_MODE_TRANSPARENT_1						0x00
#define CSC_SYS_MODE_TRANSPARENT_2						0x01
#define CSC_SYS_MODE_TRANSPARENT_ETENDU 				0x02

/* SAMs */
#define CSC_SYS_SAM_CD97								0x00
#define CSC_SYS_SAM_CD96								0x01

#define CSC_SAM_105937									0x00
#define CSC_SAM_423750									0x01
#define CSC_SAM_84750									0x02


/* deconnexion */

#define CSC_SYS_DISC_REQ								0x01
#define CSC_SYS_NO_DISC_REQ								0x00

/* LED & Buzzer Parameters */

#define CSC_CPU_LED1									0x0100
#define CSC_CPU_LED2									0x0200
#define CSC_CPU_LED3									0x0400
#define CSC_ANT_BUZZER									0x0001
#define CSC_ANT_LED1									0x0002
#define CSC_ANT_LED2									0x0000

/*-------------------- CD97 Defines -------------------*/

/* Access mode */

#define CD97_ACCESS_MODE_DEFAULT						0
#define CD97_ACCESS_MODE_PROTECTED						1
#define CD97_ACCESS_MODE_STAMPED						2
#define CD97_ACCESS_MODE_PIN							3


/* CD97 Class Functions */

#define CSC_CD97_APPEND_RECORD							0x01
#define CSC_CD97_CHANGE_KEY								0x02
#define CSC_CD97_DECREASE								0x03
#define CSC_CD97_INCREASE								0x04
#define CSC_CD97_INVALIDATE								0x05
#define CSC_CD97_READ_RECORD							0x06
#define CSC_CD97_REHABILITATE							0x07
#define CSC_CD97_SELECT_FILE							0x08
#define CSC_CD97_STATUS 								0x09
#define CSC_CD97_UPDATE_RECORD							0x0A
#define CSC_CD97_VERIFY_PIN								0x0B
#define CSC_CD97_WRITE_RECORD							0x0C
#define CSC_CD97_PURCHASE								0x0D
#define CSC_CD97_GET_EP_STATUS							0x0E
#define CSC_CD97_RELOAD_EP								0x0F
#define CSC_CD97_OPEN_SECURED_SESSION					0x10
#define CSC_CD97_CLOSE_SECURED_SESSION					0x11
#define CSC_CD97_ABORT_SECURED_SESSION					0x12
#define CSC_CD97_CANCEL_PURCHASE						0x13


/* Small ID file number */

#define CD97_SID_CURENT_EF								0x00
#define CD97_SID_CURRENT_EF								0x00
#define CD97_SID_MF_ICC 								0x02
#define CD97_SID_MF_ID									0x03
#define CD97_SID_MF_AFFICHAGES							0x05

#define CD97_SID_PME_JOURNAL_CHARGEMENTS				0x14
#define CD97_SID_PME_JOURNAL_ACHATS						0x15

#define CD97_SID_RT_ENVIRONNEMENT_TITULAIRE				0x07
#define CD97_SID_RT_JOURNAL								0x08
#define CD97_SID_RT_CONTRATS							0x09
#define CD97_SID_RT_COMPTEUR_CONTRAT_1					0x0A
#define CD97_SID_RT_COMPTEUR_CONTRAT_2					0x0B
#define CD97_SID_RT_COMPTEUR_CONTRAT_3					0x0C
#define CD97_SID_RT_COMPTEUR_CONTRAT_4					0x0D
#define CD97_SID_RT_MEMOIRE_OD							0x06
#define CD97_SID_RT_EVENEMENT_SPECIAUX					0x1D
#define CD97_SID_RT_COMPORTEMENT_FIDELITE				0x1E



/* Select Mode */

#define CD97_SEL_MF										0x00
#define CD97_SEL_CURENT_EF								0x02
#define CD97_SEL_CURRENT_EF								0x02
#define CD97_SEL_PATH									0x08



#define CD97_FILE_SIZE									29

/*-------------------- GTML Defines -------------------*/

/* Access mode */

#define GTML_ACCESS_MODE_DEFAULT						0

/* Small ID file number */

#define GTML_SID_CURRENT_EF								0x00
#define GTML_SID_MF_ICC 								0x02
#define GTML_SID_MF_ID									0x03

#define GTML_SID_RT_ENVIRONMENT							0x07
#define GTML_SID_RT_EVENTS_LOG							0x08
#define GTML_SID_RT_CONTRACTS							0x09
#define GTML_SID_RT_COUNTER_1							0x0A
#define GTML_SID_RT_COUNTER_2							0x0B
#define GTML_SID_RT_COUNTER_3							0x0C
#define GTML_SID_RT_COUNTER_4							0x0D
#define GTML_SID_RT_COUNTER_5							0x0E
#define GTML_SID_RT_COUNTER_6							0x0F
#define GTML_SID_RT_COUNTER_7							0x10
#define GTML_SID_RT_COUNTER_8							0x11
#define GTML_SID_RT_COUNTER_9							0x12
#define GTML_SID_RT_ALL_COUNTERS						0x19
#define GTML_SID_RT_OD_MEMORY							0x06
#define GTML_SID_RT_SPECIAL_EVENT						0x1D



/* Select Mode */

#define GTML_SEL_MF										0x00
#define GTML_SEL_CURRENT_EF								0x02
#define GTML_SEL_PATH									0x08



/*-------------------- Generic Defines -------------------*/

/* Access mode */

#define GEN_ACCESS_MODE_DEFAULT							0
#define GEN_ACCESS_MODE_PROTECTED						1
#define GEN_ACCESS_MODE_STAMPED							2
#define GEN_ACCESS_MODE_PIN								3

/* Generic Class Functions */

#define CSC_GEN_APPEND_RECORD							0x01
#define CSC_GEN_CHANGE_PIN								0x02
#define CSC_GEN_DECREASE								0x03
#define CSC_GEN_INCREASE								0x04
#define CSC_GEN_INVALIDATE								0x05
#define CSC_GEN_READ_RECORD								0x06
#define CSC_GEN_REHABILITATE							0x07
#define CSC_GEN_SELECT_FILE								0x08
#define CSC_GEN_STATUS 									0x09
#define CSC_GEN_UPDATE_RECORD							0x0A
#define CSC_GEN_VERIFY_PIN								0x0B
#define CSC_GEN_WRITE_RECORD							0x0C
#define CSC_GEN_PURCHASE								0x0D
#define CSC_GEN_GET_EP_STATUS							0x0E
#define CSC_GEN_RELOAD_EP								0x0F
#define CSC_GEN_OPEN_SECURED_SESSION					0x10
#define CSC_GEN_CLOSE_SECURED_SESSION					0x11
#define CSC_GEN_ABORT_SECURED_SESSION					0x12
#define CSC_GEN_CANCEL_PURCHASE							0x13
#define CSC_GEN_DECREASE_MULTIPLE						0x14
#define CSC_GEN_INCREASE_MULTIPLE						0x15
#define CSC_GEN_LOCK_UNLOCK								0x16


/* Select Mode */

#define GEN_SEL_MF										0x00
#define GEN_SEL_CURENT_EF								0x02
#define GEN_SEL_CURRENT_EF								0x02
#define GEN_SEL_PATH									0x08


/* Session Type */

#define SESSION_LEVEL_PERSO								0x00
#define SESSION_LEVEL_RELOAD							0x01
#define SESSION_LEVEL_VALID								0x02

/*-------------------- CTx Defines -------------------*/
/* CTx Class Functions */
#define CSC_CTX_ACTIVE									0x01
#define CSC_CTX_READ									0x02
#define CSC_CTX_UPDATE									0x03
#define CSC_CTX_RELEASE									0x04

/*-------------------- CTx512B Defines -------------------*/

/* CTx512B Class Functions */
#define CSC_CTX_512B_LIST								0x20
#define CSC_CTX_512B_SELECT								0x21
#define CSC_CTX_512B_READ								0x22
#define CSC_CTX_512B_UPDATE								0x23
#define CSC_CTX_512B_HALT								0x24

/*-------------------- CTx512x Defines -------------------*/
/* CTx512x Class Functions */
#define CSC_CTX_512X_LIST								0x20
#define CSC_CTX_512X_SELECT								0x21
#define CSC_CTX_512X_READ								0x22
#define CSC_CTX_512X_UPDATE								0x23
#define CSC_CTX_512X_HALT								0x24
#define	CSC_CTX_512X_WRITE								0x26
#define	CSC_CTX_512X_AUTHENTICATE						0x27
#define	CSC_CTX_512X_WRITEKEY							0x28

/*----------------- Certificat Defines ----------------*/
#define CSC_CheckCertificat								0x04
#define CSC_GiveCertificat								0x05

/*----------------- SAM Defines -----------------------*/
#define SAM_SLOT_0										0x00
#define SAM_SLOT_1										0x01
#define SAM_SLOT_2										0x02
#define SAM_SLOT_3										0x03
#define SAM_SLOT_4										0x04
#define	SAM_CURRENT										0x00
#define	CONTACT_SLOT									0x04

#define SAM_PROT_HSP_INNOVATRON							0x00
#define SAM_PROT_ISO_7816								0x01


/*----------------- MIFARE Defines --------------------*/
#define CSC_INS_RC500									0x01
#define CSC_MIFARE_LOADKEY								0x06 //SUB Command
#define CSC_MIFARE_CHANGEKEY							0x03
#define CSC_MIFARE_SELECT								0x02
#define CSC_MIFARE_AUTHENTICATE							0x05
#define CSC_MIFARE_READBLOCK							0x06
#define CSC_MIFARE_READSECTOR							0x07
#define CSC_MIFARE_WRITEBLOCK							0x08
#define CSC_MIFARE_HALT									0x09
#define CSC_MIFARE_INCREMENT							0x0A
#define CSC_MIFARE_DECREMENT							0x0B
#define CSC_MIFARE_BACKUPRESTORE						0x0C

/*----------------- STOP SEARCH COMMAND ---------------*/
#define INTERROGATION									0
#define DEFINITIVELY									1


#endif /* __CSC_DEF_H__ */
