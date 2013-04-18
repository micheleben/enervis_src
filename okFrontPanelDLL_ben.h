///------------------------------------------------------------------------
// okFrontPanelDLL.h
//
// This is the header file for C/C++ compilation of the FrontPanel DLL
// import library.  This file must be included within any C/C++ source
// which references the FrontPanel DLL methods.
//
//------------------------------------------------------------------------
// Copyright (c) 2005-2010 Opal Kelly Incorporated
// $Rev: 1032 $ $Date: 2012-01-03 15:42:21 -0800 (Tue, 03 Jan 2012) $
//------------------------------------------------------------------------

#ifndef __okFrontPanelDLL_h__
#define __okFrontPanelDLL_h__

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the FRONTPANELDLL_EXPORTS
// symbol defined on the command line.  This symbol should not be defined on any project
// that uses this DLL.
#if defined(_WIN32)
	#define okDLLEXPORT
	#define DLL_ENTRY   __stdcall
#elif defined(__linux__) || defined(__APPLE__) || defined(__QNX__)
	#define okDLLEXPORT
	#define DLL_ENTRY
#endif



typedef void (* DLL_EP)(void);

#ifdef __cplusplus
#include <string>
extern "C" {
#endif // __cplusplus


typedef void* okPLL22150_HANDLE;

typedef void* okPLL22393_HANDLE;

typedef void* okFrontPanel_HANDLE;

typedef int Bool;

#define MAX_SERIALNUMBER_LENGTH      10       // 10 characters + Does NOT include termination NULL.
#define MAX_DEVICEID_LENGTH          32       // 32 characters + Does NOT include termination NULL.
#define MAX_BOARDMODELSTRING_LENGTH  64       // 64 characters including termination NULL.

#ifndef TRUE
	#define TRUE    1
	#define FALSE   0
#endif

typedef enum {
	ok_ClkSrc22150_Ref=0,
	ok_ClkSrc22150_Div1ByN=1,
	ok_ClkSrc22150_Div1By2=2,
	ok_ClkSrc22150_Div1By3=3,
	ok_ClkSrc22150_Div2ByN=4,
	ok_ClkSrc22150_Div2By2=5,
	ok_ClkSrc22150_Div2By4=6
} ok_ClockSource_22150;


typedef enum {
	ok_ClkSrc22393_Ref=0,
	ok_ClkSrc22393_PLL0_0=2,
	ok_ClkSrc22393_PLL0_180=3,
	ok_ClkSrc22393_PLL1_0=4,
	ok_ClkSrc22393_PLL1_180=5,
	ok_ClkSrc22393_PLL2_0=6,
	ok_ClkSrc22393_PLL2_180=7
} ok_ClockSource_22393;


typedef enum {
	ok_DivSrc_Ref = 0, 
	ok_DivSrc_VCO = 1
} ok_DividerSource;


typedef enum {
	ok_brdUnknown = 0,
	ok_brdXEM3001v1 = 1,
	ok_brdXEM3001v2 = 2,
	ok_brdXEM3010 = 3,
	ok_brdXEM3005 = 4,
	ok_brdXEM3001CL = 5,
	ok_brdXEM3020 = 6,
	ok_brdXEM3050 = 7,
	ok_brdXEM9002 = 8,
	ok_brdXEM3001RB = 9,
	ok_brdXEM5010 = 10,
	ok_brdXEM6110LX45 = 11,
	ok_brdXEM6110LX150 = 15,
	ok_brdXEM6001 = 12,
	ok_brdXEM6010LX45 = 13,
	ok_brdXEM6010LX150 = 14,
	ok_brdXEM6006LX9 = 16,
	ok_brdXEM6006LX16 = 17,
	ok_brdXEM6006LX25 = 18,
	ok_brdXEM5010LX110 = 19
} ok_BoardModel;


typedef enum {
	ok_NoError                    = 0,
	ok_Failed                     = -1,
	ok_Timeout                    = -2,
	ok_DoneNotHigh                = -3,
	ok_TransferError              = -4,
	ok_CommunicationError         = -5,
	ok_InvalidBitstream           = -6,
	ok_FileError                  = -7,
	ok_DeviceNotOpen              = -8,
	ok_InvalidEndpoint            = -9,
	ok_InvalidBlockSize           = -10,
	ok_I2CRestrictedAddress       = -11,
	ok_I2CBitError                = -12,
	ok_I2CNack                    = -13,
	ok_I2CUnknownStatus           = -14,
	ok_UnsupportedFeature         = -15,
	ok_FIFOUnderflow              = -16,
	ok_FIFOOverflow               = -17,
	ok_DataAlignmentError         = -18
} ok_ErrorCode;

//
// Define the LoadLib and FreeLib methods for the IMPORT side.
//
#ifndef FRONTPANELDLL_EXPORTS

    Bool okFrontPanelDLL_LoadLib(const char *libname);

    void okFrontPanelDLL_FreeLib(void);
#endif

//
// General
//

okDLLEXPORT void DLL_ENTRY okFrontPanelDLL_GetVersion(char *date, char *time);

//
// okPLL22393
//

okDLLEXPORT okPLL22393_HANDLE DLL_ENTRY okPLL22393_Construct();

okDLLEXPORT void DLL_ENTRY okPLL22393_Destruct(okPLL22393_HANDLE pll);

okDLLEXPORT void DLL_ENTRY okPLL22393_SetCrystalLoad(okPLL22393_HANDLE pll, double capload);

okDLLEXPORT void DLL_ENTRY okPLL22393_SetReference(okPLL22393_HANDLE pll, double freq);

okDLLEXPORT double DLL_ENTRY okPLL22393_GetReference(okPLL22393_HANDLE pll);

okDLLEXPORT Bool DLL_ENTRY okPLL22393_SetPLLParameters(okPLL22393_HANDLE pll, int n, int p, int q, Bool enable);
okDLLEXPORT Bool DLL_ENTRY okPLL22393_SetPLLLF(okPLL22393_HANDLE pll, int n, int lf);

okDLLEXPORT Bool DLL_ENTRY okPLL22393_SetOutputDivider(okPLL22393_HANDLE pll, int n, int div);
/*!
 \brief

 \param pll
 \param n
 \param clksrc
 \return Bool
*/
okDLLEXPORT Bool DLL_ENTRY okPLL22393_SetOutputSource(okPLL22393_HANDLE pll, int n, ok_ClockSource_22393 clksrc);
/*!
 \brief

 \param pll
 \param n
 \param enable
*/
okDLLEXPORT void DLL_ENTRY okPLL22393_SetOutputEnable(okPLL22393_HANDLE pll, int n, Bool enable);
/*!
 \brief

 \param pll
 \param n
 \return int
*/
okDLLEXPORT int DLL_ENTRY okPLL22393_GetPLLP(okPLL22393_HANDLE pll, int n);
/*!
 \brief

 \param pll
 \param n
 \return int
*/
okDLLEXPORT int DLL_ENTRY okPLL22393_GetPLLQ(okPLL22393_HANDLE pll, int n);
/*!
 \brief

 \param pll
 \param n
 \return double
*/
okDLLEXPORT double DLL_ENTRY okPLL22393_GetPLLFrequency(okPLL22393_HANDLE pll, int n);
/*!
 \brief

 \param pll
 \param n
 \return int
*/
okDLLEXPORT int DLL_ENTRY okPLL22393_GetOutputDivider(okPLL22393_HANDLE pll, int n);
/*!
 \brief

 \param pll
 \param n
 \return ok_ClockSource_22393
*/
okDLLEXPORT ok_ClockSource_22393 DLL_ENTRY okPLL22393_GetOutputSource(okPLL22393_HANDLE pll, int n);
/*!
 \brief

 \param pll
 \param n
 \return double
*/
okDLLEXPORT double DLL_ENTRY okPLL22393_GetOutputFrequency(okPLL22393_HANDLE pll, int n);
/*!
 \brief

 \param pll
 \param n
 \return Bool
*/
okDLLEXPORT Bool DLL_ENTRY okPLL22393_IsOutputEnabled(okPLL22393_HANDLE pll, int n);
/*!
 \brief

 \param pll
 \param n
 \return Bool
*/
okDLLEXPORT Bool DLL_ENTRY okPLL22393_IsPLLEnabled(okPLL22393_HANDLE pll, int n);
/*!
 \brief

 \param pll
 \param buf
*/
okDLLEXPORT void DLL_ENTRY okPLL22393_InitFromProgrammingInfo(okPLL22393_HANDLE pll, unsigned char *buf);
/*!
 \brief

 \param pll
 \param buf
*/
okDLLEXPORT void DLL_ENTRY okPLL22393_GetProgrammingInfo(okPLL22393_HANDLE pll, unsigned char *buf);


//
// okPLL22150
//
/*!
 \brief

 \return okPLL22150_HANDLE
*/
okDLLEXPORT okPLL22150_HANDLE DLL_ENTRY okPLL22150_Construct();
/*!
 \brief

 \param pll
*/
okDLLEXPORT void DLL_ENTRY okPLL22150_Destruct(okPLL22150_HANDLE pll);
/*!
 \brief

 \param pll
 \param capload
*/
okDLLEXPORT void DLL_ENTRY okPLL22150_SetCrystalLoad(okPLL22150_HANDLE pll, double capload);
/*!
 \brief

 \param pll
 \param freq
 \param extosc
*/
okDLLEXPORT void DLL_ENTRY okPLL22150_SetReference(okPLL22150_HANDLE pll, double freq, Bool extosc);
/*!
 \brief

 \param pll
 \return double
*/
okDLLEXPORT double DLL_ENTRY okPLL22150_GetReference(okPLL22150_HANDLE pll);
/*!
 \brief

 \param pll
 \param p
 \param q
 \return Bool
*/
okDLLEXPORT Bool DLL_ENTRY okPLL22150_SetVCOParameters(okPLL22150_HANDLE pll, int p, int q);
/*!
 \brief

 \param pll
 \return int
*/
okDLLEXPORT int DLL_ENTRY okPLL22150_GetVCOP(okPLL22150_HANDLE pll);
/*!
 \brief

 \param pll
 \return int
*/
okDLLEXPORT int DLL_ENTRY okPLL22150_GetVCOQ(okPLL22150_HANDLE pll);
/*!
 \brief

 \param pll
 \return double
*/
okDLLEXPORT double DLL_ENTRY okPLL22150_GetVCOFrequency(okPLL22150_HANDLE pll);
/*!
 \brief

 \param pll
 \param divsrc
 \param n
*/
okDLLEXPORT void DLL_ENTRY okPLL22150_SetDiv1(okPLL22150_HANDLE pll, ok_DividerSource divsrc, int n);
/*!
 \brief

 \param pll
 \param divsrc
 \param n
*/
okDLLEXPORT void DLL_ENTRY okPLL22150_SetDiv2(okPLL22150_HANDLE pll, ok_DividerSource divsrc, int n);
/*!
 \brief

 \param pll
 \return ok_DividerSource
*/
okDLLEXPORT ok_DividerSource DLL_ENTRY okPLL22150_GetDiv1Source(okPLL22150_HANDLE pll);
/*!
 \brief

 \param pll
 \return ok_DividerSource
*/
okDLLEXPORT ok_DividerSource DLL_ENTRY okPLL22150_GetDiv2Source(okPLL22150_HANDLE pll);
/*!
 \brief

 \param pll
 \return int
*/
okDLLEXPORT int DLL_ENTRY okPLL22150_GetDiv1Divider(okPLL22150_HANDLE pll);
/*!
 \brief

 \param pll
 \return int
*/
okDLLEXPORT int DLL_ENTRY okPLL22150_GetDiv2Divider(okPLL22150_HANDLE pll);
/*!
 \brief

 \param pll
 \param output
 \param clksrc
*/
okDLLEXPORT void DLL_ENTRY okPLL22150_SetOutputSource(okPLL22150_HANDLE pll, int output, ok_ClockSource_22150 clksrc);
/*!
 \brief

 \param pll
 \param output
 \param enable
*/
okDLLEXPORT void DLL_ENTRY okPLL22150_SetOutputEnable(okPLL22150_HANDLE pll, int output, Bool enable);
/*!
 \brief

 \param pll
 \param output
 \return ok_ClockSource_22150
*/
okDLLEXPORT ok_ClockSource_22150 DLL_ENTRY okPLL22150_GetOutputSource(okPLL22150_HANDLE pll, int output);
/*!
 \brief

 \param pll
 \param output
 \return double
*/
okDLLEXPORT double DLL_ENTRY okPLL22150_GetOutputFrequency(okPLL22150_HANDLE pll, int output);
/*!
 \brief

 \param pll
 \param output
 \return Bool
*/
okDLLEXPORT Bool DLL_ENTRY okPLL22150_IsOutputEnabled(okPLL22150_HANDLE pll, int output);
/*!
 \brief

 \param pll
 \param buf
*/
okDLLEXPORT void DLL_ENTRY okPLL22150_InitFromProgrammingInfo(okPLL22150_HANDLE pll, unsigned char *buf);
/*!
 \brief

 \param pll
 \param buf
*/
okDLLEXPORT void DLL_ENTRY okPLL22150_GetProgrammingInfo(okPLL22150_HANDLE pll, unsigned char *buf);


//
// okFrontPanel
//
/*!
 \brief

 \return okFrontPanel_HANDLE
*/
okDLLEXPORT okFrontPanel_HANDLE DLL_ENTRY okFrontPanel_Construct();
/*!
 \brief

 \param hnd
*/
okDLLEXPORT void DLL_ENTRY okFrontPanel_Destruct(okFrontPanel_HANDLE hnd);
/*!
 \brief

 \param hnd
 \param addr
 \param length
 \param data
 \return ok_ErrorCode
*/
okDLLEXPORT ok_ErrorCode DLL_ENTRY okFrontPanel_WriteI2C(okFrontPanel_HANDLE hnd, const int addr, int length, unsigned char *data);
/*!
 \brief

 \param hnd
 \param addr
 \param length
 \param data
 \return ok_ErrorCode
*/
okDLLEXPORT ok_ErrorCode DLL_ENTRY okFrontPanel_ReadI2C(okFrontPanel_HANDLE hnd, const int addr, int length, unsigned char *data);
/*!
 \brief

 \param hnd
 \return int
*/
okDLLEXPORT int DLL_ENTRY okFrontPanel_GetHostInterfaceWidth(okFrontPanel_HANDLE hnd);
/*!
 \brief

 \param hnd
 \return Bool
*/
okDLLEXPORT Bool DLL_ENTRY okFrontPanel_IsHighSpeed(okFrontPanel_HANDLE hnd);
/*!
 \brief

 \param hnd
 \return ok_BoardModel
*/
okDLLEXPORT ok_BoardModel DLL_ENTRY okFrontPanel_GetBoardModel(okFrontPanel_HANDLE hnd);
/*!
 \brief

 \param hnd
 \param m
 \param buf
*/
okDLLEXPORT void DLL_ENTRY okFrontPanel_GetBoardModelString(okFrontPanel_HANDLE hnd, ok_BoardModel m, char *buf);
/*!
 \brief

 \param hnd
 \return int
*/
okDLLEXPORT int DLL_ENTRY okFrontPanel_GetDeviceCount(okFrontPanel_HANDLE hnd);
/*!
 \brief

 \param hnd
 \param num
 \return ok_BoardModel
*/
okDLLEXPORT ok_BoardModel DLL_ENTRY okFrontPanel_GetDeviceListModel(okFrontPanel_HANDLE hnd, int num);
/*!
 \brief

 \param hnd
 \param num
 \param buf
*/
okDLLEXPORT void DLL_ENTRY okFrontPanel_GetDeviceListSerial(okFrontPanel_HANDLE hnd, int num, char *buf);
/*!
 \brief

 \param hnd
 \param serial
 \return ok_ErrorCode
*/
okDLLEXPORT ok_ErrorCode DLL_ENTRY okFrontPanel_OpenBySerial(okFrontPanel_HANDLE hnd, const char *serial);
/*!
 \brief

 \param hnd
 \return Bool
*/
okDLLEXPORT Bool DLL_ENTRY okFrontPanel_IsOpen(okFrontPanel_HANDLE hnd);
/*!
 \brief

 \param hnd
 \param enable
*/
okDLLEXPORT void DLL_ENTRY okFrontPanel_EnableAsynchronousTransfers(okFrontPanel_HANDLE hnd, Bool enable);
/*!
 \brief

 \param hnd
 \param interval
 \return ok_ErrorCode
*/
okDLLEXPORT ok_ErrorCode DLL_ENTRY okFrontPanel_SetBTPipePollingInterval(okFrontPanel_HANDLE hnd, int interval);
/*!
 \brief

 \param hnd
 \param timeout
*/
okDLLEXPORT void DLL_ENTRY okFrontPanel_SetTimeout(okFrontPanel_HANDLE hnd, int timeout);
/*!
 \brief

 \param hnd
 \return int
*/
okDLLEXPORT int DLL_ENTRY okFrontPanel_GetDeviceMajorVersion(okFrontPanel_HANDLE hnd);
/*!
 \brief

 \param hnd
 \return int
*/
okDLLEXPORT int DLL_ENTRY okFrontPanel_GetDeviceMinorVersion(okFrontPanel_HANDLE hnd);
/*!
 \brief

 \param hnd
 \return ok_ErrorCode
*/
okDLLEXPORT ok_ErrorCode DLL_ENTRY okFrontPanel_ResetFPGA(okFrontPanel_HANDLE hnd);
/*!
 \brief

 \param hnd
 \param buf
*/
okDLLEXPORT void DLL_ENTRY okFrontPanel_GetSerialNumber(okFrontPanel_HANDLE hnd, char *buf);
/*!
 \brief

 \param hnd
 \param buf
*/
okDLLEXPORT void DLL_ENTRY okFrontPanel_GetDeviceID(okFrontPanel_HANDLE hnd, char *buf);
/*!
 \brief

 \param hnd
 \param strID
*/
okDLLEXPORT void DLL_ENTRY okFrontPanel_SetDeviceID(okFrontPanel_HANDLE hnd, const char *strID);
/*!
 \brief

 \param hnd
 \param strFilename
 \return ok_ErrorCode
*/
okDLLEXPORT ok_ErrorCode DLL_ENTRY okFrontPanel_ConfigureFPGA(okFrontPanel_HANDLE hnd, const char *strFilename);
/*!
 \brief

 \param hnd
 \param data
 \param length
 \return ok_ErrorCode
*/
okDLLEXPORT ok_ErrorCode DLL_ENTRY okFrontPanel_ConfigureFPGAFromMemory(okFrontPanel_HANDLE hnd, unsigned char *data, unsigned long length);
/*!
 \brief

 \param hnd
 \param pll
 \return ok_ErrorCode
*/
okDLLEXPORT ok_ErrorCode DLL_ENTRY okFrontPanel_GetPLL22150Configuration(okFrontPanel_HANDLE hnd, okPLL22150_HANDLE pll);
/*!
 \brief

 \param hnd
 \param pll
 \return ok_ErrorCode
*/
okDLLEXPORT ok_ErrorCode DLL_ENTRY okFrontPanel_SetPLL22150Configuration(okFrontPanel_HANDLE hnd, okPLL22150_HANDLE pll);
/*!
 \brief

 \param hnd
 \param pll
 \return ok_ErrorCode
*/
okDLLEXPORT ok_ErrorCode DLL_ENTRY okFrontPanel_GetEepromPLL22150Configuration(okFrontPanel_HANDLE hnd, okPLL22150_HANDLE pll);
/*!
 \brief

 \param hnd
 \param pll
 \return ok_ErrorCode
*/
okDLLEXPORT ok_ErrorCode DLL_ENTRY okFrontPanel_SetEepromPLL22150Configuration(okFrontPanel_HANDLE hnd, okPLL22150_HANDLE pll);
/*!
 \brief

 \param hnd
 \param pll
 \return ok_ErrorCode
*/
okDLLEXPORT ok_ErrorCode DLL_ENTRY okFrontPanel_GetPLL22393Configuration(okFrontPanel_HANDLE hnd, okPLL22393_HANDLE pll);
/*!
 \brief

 \param hnd
 \param pll
 \return ok_ErrorCode
*/
okDLLEXPORT ok_ErrorCode DLL_ENTRY okFrontPanel_SetPLL22393Configuration(okFrontPanel_HANDLE hnd, okPLL22393_HANDLE pll);
/*!
 \brief

 \param hnd
 \param pll
 \return ok_ErrorCode
*/
okDLLEXPORT ok_ErrorCode DLL_ENTRY okFrontPanel_GetEepromPLL22393Configuration(okFrontPanel_HANDLE hnd, okPLL22393_HANDLE pll);
/*!
 \brief

 \param hnd
 \param pll
 \return ok_ErrorCode
*/
okDLLEXPORT ok_ErrorCode DLL_ENTRY okFrontPanel_SetEepromPLL22393Configuration(okFrontPanel_HANDLE hnd, okPLL22393_HANDLE pll);
/*!
 \brief

 \param hnd
 \return ok_ErrorCode
*/
okDLLEXPORT ok_ErrorCode DLL_ENTRY okFrontPanel_LoadDefaultPLLConfiguration(okFrontPanel_HANDLE hnd);
/*!
 \brief

 \param hnd
 \return Bool
*/
okDLLEXPORT Bool DLL_ENTRY okFrontPanel_IsFrontPanelEnabled(okFrontPanel_HANDLE hnd);
/*!
 \brief

 \param hnd
 \return Bool
*/
okDLLEXPORT Bool DLL_ENTRY okFrontPanel_IsFrontPanel3Supported(okFrontPanel_HANDLE hnd);
/*!
 \brief

 \param hnd
*/
okDLLEXPORT void DLL_ENTRY okFrontPanel_UpdateWireIns(okFrontPanel_HANDLE hnd);
/*!
 \brief

 \param hnd
 \param ep
 \param val
 \param mask
 \return ok_ErrorCode
*/
okDLLEXPORT ok_ErrorCode DLL_ENTRY okFrontPanel_SetWireInValue(okFrontPanel_HANDLE hnd, int ep, unsigned long val, unsigned long mask);
/*!
 \brief

 \param hnd
*/
okDLLEXPORT void DLL_ENTRY okFrontPanel_UpdateWireOuts(okFrontPanel_HANDLE hnd);
/*!
 \brief

 \param hnd
 \param epAddr
 \return unsigned long
*/
okDLLEXPORT unsigned long DLL_ENTRY okFrontPanel_GetWireOutValue(okFrontPanel_HANDLE hnd, int epAddr);
/*!
 \brief

 \param hnd
 \param epAddr
 \param bit
 \return ok_ErrorCode
*/
okDLLEXPORT ok_ErrorCode DLL_ENTRY okFrontPanel_ActivateTriggerIn(okFrontPanel_HANDLE hnd, int epAddr, int bit);
/*!
 \brief

 \param hnd
*/
okDLLEXPORT void DLL_ENTRY okFrontPanel_UpdateTriggerOuts(okFrontPanel_HANDLE hnd);
/*!
 \brief

 \param hnd
 \param epAddr
 \param mask
 \return Bool
*/
okDLLEXPORT Bool DLL_ENTRY okFrontPanel_IsTriggered(okFrontPanel_HANDLE hnd, int epAddr, unsigned long mask);
/*!
 \brief

 \param hnd
 \return long
*/
okDLLEXPORT long DLL_ENTRY okFrontPanel_GetLastTransferLength(okFrontPanel_HANDLE hnd);
/*!
 \brief

 \param hnd
 \param epAddr
 \param length
 \param data
 \return long
*/
okDLLEXPORT long DLL_ENTRY okFrontPanel_WriteToPipeIn(okFrontPanel_HANDLE hnd, int epAddr, long length, unsigned char *data);
/*!
 \brief

 \param hnd
 \param epAddr
 \param length
 \param data
 \return long
*/
okDLLEXPORT long DLL_ENTRY okFrontPanel_ReadFromPipeOut(okFrontPanel_HANDLE hnd, int epAddr, long length, unsigned char *data);
/*!
 \brief

 \param hnd
 \param epAddr
 \param blockSize
 \param length
 \param data
 \return long
*/
okDLLEXPORT long DLL_ENTRY okFrontPanel_WriteToBlockPipeIn(okFrontPanel_HANDLE hnd, int epAddr, int blockSize, long length, unsigned char *data);
/*!
 \brief

 \param hnd
 \param epAddr
 \param blockSize
 \param length
 \param data
 \return long
*/
okDLLEXPORT long DLL_ENTRY okFrontPanel_ReadFromBlockPipeOut(okFrontPanel_HANDLE hnd, int epAddr, int blockSize, long length, unsigned char *data);


#ifdef __cplusplus
#if !defined(FRONTPANELDLL_EXPORTS)
//------------------------------------------------------------------------
// okCPLL22150 C++ wrapper class
//------------------------------------------------------------------------
/*!
 \brief

*/
class okCPLL22150
{
public:
    okPLL22150_HANDLE h; /*!< TODO */
    /*!
     \brief

    */
    enum ClockSource {
			ClkSrc_Ref=0,
			ClkSrc_Div1ByN=1,
			ClkSrc_Div1By2=2,
			ClkSrc_Div1By3=3,
            ClkSrc_Div2ByN=4,
			ClkSrc_Div2By2=5,
			ClkSrc_Div2By4=6 };

    /*!
     \brief

    */
    enum DividerSource {
			DivSrc_Ref = 0, 
			DivSrc_VCO = 1 };
private:
    /*!
     \brief

     \param x
     \return bool
    */
    bool to_bool(Bool x);
    /*!
     \brief

     \param x
     \return Bool
    */
    Bool from_bool(bool x);
public:
	okCPLL22150();
    /*!
     \brief

     \param capload
    */
    void SetCrystalLoad(double capload);
    /*!
     \brief

     \param freq
     \/*!
     \ \brief
     \
     \ \return DividerSource
     \
     \param extosc
    */
    void SetReference(double freq, bool extosc);
    /*!
     \brief

     \return double
    */
    double GetReference();
    /*!
     \brief

     \param p
     \param q
     \return bool
    */
    bool SetVCOParameters(int p, int q);
    /*!
     \brief

     \return int
    */
    int GetVCOP();
    /*!
     \brief

     \return int
    */
    int GetVCOQ();
    /*!
     \brief

     \return double
    */
    double GetVCOFrequency();
    /*!
     \brief

     \param divsrc
     \param n
    */
    void SetDiv1(DividerSource divsrc, int n);
    /*!
     \brief

     \param divsrc
     \param n
    */
    void SetDiv2(DividerSource divsrc, int n);
    /*!
     \brief

     \return DividerSource
    */
    DividerSource GetDiv1Source();
    /*!
     \brief

     \return DividerSource
    */
    DividerSource GetDiv2Source();
    /*!
     \brief

     \return int
    */
    int GetDiv1Divider();
    /*!
     \brief

     \return int
    */
    int GetDiv2Divider();
    /*!
     \brief

     \param output
     \param clksrc
    */
    void SetOutputSource(int output, ClockSource clksrc);
    /*!
     \brief

     \param output
     \param enable
    */
    void SetOutputEnable(int output, bool enable);
    /*!
     \brief

     \param output
     \return ClockSource
    */
    ClockSource GetOutputSource(int output);
    /*!
     \brief

     \param output
     \return double
    */
    double GetOutputFrequency(int output);
    /*!
     \brief

     \param output
     \return bool
    */
    bool IsOutputEnabled(int output);
    /*!
     \brief

     \param buf
    */
    void InitFromProgrammingInfo(unsigned char *buf);
    /*!
     \brief

     \param buf
    */
    void GetProgrammingInfo(unsigned char *buf);
};

//------------------------------------------------------------------------
// okCPLL22150 C++ wrapper class
//------------------------------------------------------------------------
/*!
 \brief

*/
class okCPLL22393
{
public:
    okPLL22393_HANDLE h; /*!< TODO */
    /*!
     \brief

    */
    enum ClockSource {
			ClkSrc_Ref=0,
			ClkSrc_PLL0_0=2,
			ClkSrc_PLL0_180=3,
			ClkSrc_PLL1_0=4,
			ClkSrc_PLL1_180=5,
			ClkSrc_PLL2_0=6,
			ClkSrc_PLL2_180=7 };
private:
    /*!
     \brief

     \param x
     \return bool
    */
    bool to_bool(Bool x);
    /*!
     \brief

     \param x
     \return Bool
    */
    Bool from_bool(bool x);
public:
	okCPLL22393();
    /*!
     \brief

     \param capload
    */
    /*!
     \brief

     \param n
     \param div
     \return bool
    */
    void SetCrystalLoad(double capload);
    /*!
     \brief

     \param freq
    */
    void SetReference(double freq);
    /*!
     \brief

     \return double
    */
    double GetReference();
    /*!
     \brief

     \param n
     \param p
     \param q
     \param enable
     \return bool
    */
    bool SetPLLParameters(int n, int p, int q, bool enable=true);
    /*!
     \brief

     \param n
     \param lf
     \return bool
    */
    bool SetPLLLF(int n, int lf);
    /*!
     \brief

     \param n
     \param div
     \return bool
    */
    bool SetOutputDivider(int n, int div);
    /*!
     \brief

     \param n
     \param clksrc
     \return bool
    */
    bool SetOutputSource(int n, ClockSource clksrc);
    /*!
     \brief

     \param n
     \param enable
    */
    void SetOutputEnable(int n, bool enable);
    /*!
     \brief

     \param n
     \return int
    */
    int GetPLLP(int n);
    /*!
     \brief

     \param n
     \return int
    */
    int GetPLLQ(int n);
    /*!
     \brief

     \param n
     \return double
    */
    double GetPLLFrequency(int n);
    /*!
     \brief

     \param n
     \return int
    */
    int GetOutputDivider(int n);
    /*!
     \brief

     \param n
     \return ClockSource
    */
    ClockSource GetOutputSource(int n);
    /*!
     \brief

     \param n
     \return double
    */
    double GetOutputFrequency(int n);
    /*!
     \brief

     \param n
     \return bool
    */
    bool IsOutputEnabled(int n);
    /*!
     \brief

     \param n
     \return bool
    */
    bool IsPLLEnabled(int n);
    /*!
     \brief

     \param buf
    */
    void InitFromProgrammingInfo(unsigned char *buf);
    /*!
     \brief

     \param buf
    */
    void GetProgrammingInfo(unsigned char *buf);
};

//------------------------------------------------------------------------
// okCFrontPanel C++ wrapper class
//------------------------------------------------------------------------
/*!
 \brief

*/
class okCFrontPanel
{
public:
    okFrontPanel_HANDLE h; /*!< TODO */
    /*!
     \brief

    */
    enum BoardModel {
		brdUnknown=0,
		brdXEM3001v1=1,
		brdXEM3001v2=2,
		brdXEM3010=3,
		brdXEM3005=4,
		brdXEM3001CL=5,
		brdXEM3020=6,
		brdXEM3050=7,
		brdXEM9002=8,
		brdXEM3001RB=9,
		brdXEM5010=10,
		brdXEM6110LX45=11,
		brdXEM6110LX150=15,
		brdXEM6001=12,
		brdXEM6010LX45=13,
		brdXEM6010LX150=14,
		brdXEM6006LX9=16,
		brdXEM6006LX16=17,
		brdXEM6006LX25=18,
		brdXEM5010LX110=19
	};
    /*!
     \brief

    */
    enum ErrorCode {
		NoError                    = 0,
		Failed                     = -1,
		Timeout                    = -2,
		DoneNotHigh                = -3,
		TransferError              = -4,
		CommunicationError         = -5,
		InvalidBitstream           = -6,
		FileError                  = -7,
		DeviceNotOpen              = -8,
		InvalidEndpoint            = -9,
		InvalidBlockSize           = -10,
		I2CRestrictedAddress       = -11,
		I2CBitError                = -12,
		I2CNack                    = -13,
		I2CUnknownStatus           = -14,
		UnsupportedFeature         = -15
	};
private:
    /*!
     \brief

     \param x
     \return bool
    */
    bool to_bool(Bool x);
    /*!
     \brief

     \param x
     \return Bool
    */
    Bool from_bool(bool x);
public:
	okCFrontPanel();
    /*!
     \brief

    */
    ~okCFrontPanel();
    /*!
     \brief

     \return int
    */
    /*!
     \brief

     \return int
    */
    int GetHostInterfaceWidth();
    /*!
     \brief

     \return BoardModel
    */
    BoardModel GetBoardModel();
    /*!
     \brief

     \param m
     \return std::string
    */
    std::string GetBoardModelString(BoardModel m);
    /*!
     \brief

     \return int
    */
    int GetDeviceCount();
    /*!
     \brief

     \param num
     \return BoardModel
    */
    BoardModel GetDeviceListModel(int num);
    /*!
     \brief

     \param num
     \return std::string
    */
    std::string GetDeviceListSerial(int num);
    /*!
     \brief

     \param enable
    */
    void EnableAsynchronousTransfers(bool enable);
    /*!
     \brief

     \param str
     \return ErrorCode
    */
    ErrorCode OpenBySerial(std::string str = "");
    /*!
     \brief

     \return bool
    */
    bool IsOpen();
    /*!
     \brief

     \return int
    */
    int GetDeviceMajorVersion();
    /*!
     \brief

     \return int
    */
    int GetDeviceMinorVersion();
    /*!
     \brief

     \return std::string
    */
    std::string GetSerialNumber();
    /*!
     \brief

     \return std::string
    */
    std::string GetDeviceID();
    /*!
     \brief

     \param str
    */
    void SetDeviceID(const std::string str);
    /*!
     \brief

     \param interval
     \return ErrorCode
    */
    ErrorCode SetBTPipePollingInterval(int interval);
    /*!
     \brief

     \param timeout
    */
    void SetTimeout(int timeout);
    /*!
     \brief

     \return ErrorCode
    */
    ErrorCode ResetFPGA();
    /*!
     \brief

     \param data
     \param length
     \param (callback)(int
     \param int
     \param )
     \param arg
     \return ErrorCode
    */
    ErrorCode ConfigureFPGAFromMemory(unsigned char *data, const unsigned long length,
				void(*callback)(int, int, void *) = NULL, void *arg = NULL);
    /*!
     \brief

     \param strFilename
     \param (callback)(int
     \param int
     \param )
     \param arg
     \return ErrorCode
    */
    ErrorCode ConfigureFPGA(const std::string strFilename,
				void (*callback)(int, int, void *) = NULL, void *arg = NULL);
    /*!
     \brief

     \param addr
     \param length
     \param data
     \return ErrorCode
    */
    ErrorCode WriteI2C(const int addr, int length, unsigned char *data);
    /*!
     \brief

     \param addr
     \param length
     \param data
     \return ErrorCode
    */
    ErrorCode ReadI2C(const int addr, int length, unsigned char *data);
    /*!
     \brief

     \param pll
     \return ErrorCode
    */
    ErrorCode GetPLL22150Configuration(okCPLL22150& pll);
    /*!
     \brief

     \param pll
     \return ErrorCode
    */
    ErrorCode SetPLL22150Configuration(okCPLL22150& pll);
    /*!
     \brief

     \param pll
     \return ErrorCode
    */
    ErrorCode GetEepromPLL22150Configuration(okCPLL22150& pll);
    /*!
     \brief

     \param pll
     \return ErrorCode
    */
    ErrorCode SetEepromPLL22150Configuration(okCPLL22150& pll);
    /*!
     \brief

     \param pll
     \return ErrorCode
    */
    ErrorCode GetPLL22393Configuration(okCPLL22393& pll);
    /*!
     \brief

     \param pll
     \return ErrorCode
    */
    ErrorCode SetPLL22393Configuration(okCPLL22393& pll);
    /*!
     \brief

     \param pll
     \return ErrorCode
    */
    ErrorCode GetEepromPLL22393Configuration(okCPLL22393& pll);
    /*!
     \brief

     \param pll
     \return ErrorCode
    */
    ErrorCode SetEepromPLL22393Configuration(okCPLL22393& pll);
    /*!
     \brief

     \return ErrorCode
    */
    ErrorCode LoadDefaultPLLConfiguration();
    /*!
     \brief

     \return bool
    */
    bool IsHighSpeed();
    /*!
     \brief

     \return bool
    */
    bool IsFrontPanelEnabled();
    /*!
     \brief

     \return bool
    */
    bool IsFrontPanel3Supported();
    /*!
     \brief

    */
    void UpdateWireIns();
    /*!
     \brief

     \param ep
     \param val
     \param mask
     \return ErrorCode
    */
    ErrorCode SetWireInValue(int ep, unsigned long val, unsigned long mask = 0xffffffff);
    /*!
     \brief

    */
    void UpdateWireOuts();
    /*!
     \brief

     \param epAddr
     \return unsigned long
    */
    unsigned long GetWireOutValue(int epAddr);
    /*!
     \brief

     \param epAddr
     \param bit
     \return ErrorCode
    */
    ErrorCode ActivateTriggerIn(int epAddr, int bit);
    /*!
     \brief

    */
    void UpdateTriggerOuts();
    /*!
     \brief

     \param epAddr
     \param mask
     \return bool
    */
    bool IsTriggered(int epAddr, unsigned long mask);
    /*!
     \brief

     \return long
    */
    long GetLastTransferLength();
    /*!
     \brief

     \param epAddr
     \param length
     \param data
     \return long
    */
    long WriteToPipeIn(int epAddr, long length, unsigned char *data);
    /*!
     \brief

     \param epAddr
     \param length
     \param data
     \return long
    */
    long ReadFromPipeOut(int epAddr, long length, unsigned char *data);
    /*!
     \brief

     \param epAddr
     \param blockSize
     \param length
     \param data
     \return long
    */
    long WriteToBlockPipeIn(int epAddr, int blockSize, long length, unsigned char *data);
    /*!
     \brief

     \param epAddr
     \param blockSize
     \param length
     \param data
     \return long
    */
    long ReadFromBlockPipeOut(int epAddr, int blockSize, long length, unsigned char *data);
};
#endif // !defined(FRONTPANELDLL_EXPORTS)

}
#endif // __cplusplus
//this is the extern definition
extern okCFrontPanel *gDev; /*!< TODO */
#endif // __okFrontPanelDLL_h__
