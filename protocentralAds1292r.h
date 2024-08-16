//////////////////////////////////////////////////////////////////////////////////////////
//
//   Arduino Library for ADS1292R Shield/Breakout
//
//   Copyright (c) 2017 ProtoCentral
//
//   This software is licensed under the MIT License(http://opensource.org/licenses/MIT).
//
//   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
//   NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
//   IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
//   WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
//   SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
//   Requires g4p_control graphing library for processing.  Built on V4.1
//   Downloaded from Processing IDE Sketch->Import Library->Add Library->G4P Install
//
/////////////////////////////////////////////////////////////////////////////////////////
#ifndef ads1292r_h
#define ads1292r_h

#include "Arduino.h"

#define CONFIG_SPI_MASTER_DUMMY   0xFF

// Register Read Commands
#define RREG  0x20;		//Read n nnnn registers starting at address r rrrr
                      //first byte 001r rrrr (2xh)(2) - second byte 000n nnnn(2)
#define WREG  0x40;	  //Write n nnnn registers starting at address r rrrr
                      //first byte 010r rrrr (2xh)(2) - second byte 000n nnnn(2)
#define START	0x08		//Start/restart (synchronize) conversions
#define STOP	0x0A		//Stop conversion
#define RDATAC 0x10		//Enable Read Data Continuous mode.

//This mode is the default mode at power-up.
#define SDATAC 0x11		//Stop Read Data Continuously mode
#define RDATA	0x12		//Read data by command; supports multiple read back.

//register address
#define ADS1292_REG_ID			  0x00
#define ADS1292_REG_CONFIG1		0x01
#define ADS1292_REG_CONFIG2		0x02
#define ADS1292_REG_LOFF		  0x03
#define ADS1292_REG_CH1SET		0x04
#define ADS1292_REG_CH2SET		0x05
#define ADS1292_REG_RLDSENS		0x06
#define ADS1292_REG_LOFFSENS  0x07
#define ADS1292_REG_LOFFSTAT  0x08
#define ADS1292_REG_RESP1	    0x09
#define ADS1292_REG_RESP2	    0x0A

//Packet format
#define  CES_CMDIF_PKT_START_1   0x0A
#define  CES_CMDIF_PKT_START_2   0xFA
#define  CES_CMDIF_TYPE_DATA     0x02
#define  CES_CMDIF_PKT_STOP_1    0x00
#define  CES_CMDIF_PKT_STOP_2    0x0B

typedef struct Record{
  volatile signed long sDaqVals[8];
  boolean leadoffDetected = true;
  signed long sresultTempResp;
}ads1292OutputValues;

class ads1292r
{
  public:
    boolean getAds1292EcgAndRespirationSamples(const int dataReady,const int chipSelect,ads1292OutputValues *ecgRespirationValues);
    static void ads1292Init(const int chipSelect,const int pwdnPin,const int startPin);
    static void ads1292Reset(const int pwdnPin);

  private:
	  static void ads1292RegWrite (unsigned char READ_WRITE_ADDRESS, unsigned char DATA,const int chipSelect);
    static void ads1292SPICommandData(unsigned char dataIn,const int chipSelect);
    static void ads1292DisableStart(const int startPin);
    static void ads1292EnableStart(const int startPin);
    static void ads1292HardStop (const int startPin);
    static void ads1292StartDataConvCommand (const int chipSelect);
    static void ads1292SoftStop (const int chipSelect);
    static void ads1292StartReadDataContinuous (const int chipSelect);
    static void ads1292StopReadDataContinuous (const int chipSelect);
    static char* ads1292ReadData(const int chipSelect);
};

#endif
