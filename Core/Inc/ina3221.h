#include "main.h"
#ifndef INA3221_H
#define INA3221_H  

#ifdef __cplusplus
extern "C" {
#endif




		#define INA3221_SHUNT_VOLTAGE_LSB               0.00004   // 40 uV per LSB
		#define INA3221_BUS_VOLTAGE_LSB                 0.008     // 8 mV per LSB
/*=========================================================================
    I2C ADDRESS/BITS
-----------------------------------------------------------------------*/
    #define INA_ID                          				(0x80)    // 1000000 
/*=========================================================================*/

/*=========================================================================
    Configuration Register (RW) - See table 5 spec
---------------------------------------------------------------------*/
    #define INA3221_CONFIG_RST                      (0x8000)  // Reset Bit
    
    #define INA3221_CONFIG_CH1                      (0x4000)  // Enable Channel 1
    #define INA3221_CONFIG_CH2                      (0x2000)  // Enable Channel 2
    #define INA3221_CONFIG_CH3                      (0x1000)  // Enable Channel 3
    
    #define INA3221_CONFIG_AVG2                     (0x0800)  // Averaging mode Bit 2 
    #define INA3221_CONFIG_AVG1                     (0x0400)  // Averaging mode Bit 1 
    #define INA3221_CONFIG_AVG0                     (0x0200)  // Averaging mode Bit 0 

    #define INA3221_CONFIG_VBUS_CT2                 (0x0100)  // Bus-voltage conversion time bit 0
    #define INA3221_CONFIG_VBUS_CT1                 (0x0080)  // Bus-voltage conversion time bit 0
    #define INA3221_CONFIG_VBUS_CT0                 (0x0040)  // Bus-voltage conversion time bit 0

    #define INA3221_CONFIG_VSH_CT2                  (0x0020)  // Shunt-voltage conversion time bit 2
    #define INA3221_CONFIG_VSH_CT1                  (0x0010)  // Shunt-voltage conversion time bit 1
    #define INA3221_CONFIG_VSH_CT0                  (0x0008)  // Shunt-voltage conversion time bit 0
    
    #define INA3221_CONFIG_MODE_3                   (0x0004)  // Operating Mode bit 2
    #define INA3221_CONFIG_MODE_2                   (0x0002)  // Operating Mode bit 1
    #define INA3221_CONFIG_MODE_1                   (0x0001)  // Operating Mode bit 0
    
    #define INA3221_MODE_POWER_DOWN                 (0x0000)  // Power-down
    #define INA3221_MODE_SHUNT_SINGLE               (0x0001)  // Shunt voltage, single-shot (triggered)
    #define INA3221_MODE_BUS_SINGLE                 (0x0002)  // Bus voltage, single-shot (triggered)
    #define INA3221_MODE_SHUNT_BUS_SINGLE           (0x0003)  // Shunt and bus, single-shot (triggered)
    #define INA3221_MODE_SHUNT_CONTINUOUS           (0x0005)  // Shunt voltage, continuous
    #define INA3221_MODE_BUS_CONTINUOUS             (0x0006)  // Bus voltage, continuous
    #define INA3221_MODE_SHUNT_BUS_CONTINUOUS       (0x0007)  // Shunt and bus, continuous
    
    #define INA3221_140_US                          (0x0000)  // Conversion time 140 us
    #define INA3221_204_US                          (0x0001)  // Conversion time 204 us
    #define INA3221_332_US                          (0x0002)  // Conversion time 332 us
    #define INA3221_588_US                          (0x0003)  // Conversion time 588 us
    #define INA3221_1_1_MS                          (0x0004)  // Conversion time 1.1 ms
    #define INA3221_2_116_MS                        (0x0005)  // Conversion time 2.116 ms
    #define INA3221_4_156_MS                        (0x0006)  // Conversion time 4.156 ms
    #define INA3221_8_244_MS                        (0x0007)  // Conversion time 8.244 ms
    
    #define INA3221_AVERAGE_1                       (0x0000)  // Averaging mode 1
    #define INA3221_AVERAGE_4                       (0x0001)  // Averaging mode 4
    #define INA3221_AVERAGE_16                      (0x0002)  // Averaging mode 16
    #define INA3221_AVERAGE_64                      (0x0003)  // Averaging mode 64
    #define INA3221_AVERAGE_128                     (0x0004)  // Averaging mode 128
    #define INA3221_AVERAGE_256                     (0x0005)  // Averaging mode 256
    #define INA3221_AVERAGE_512                     (0x0006)  // Averaging mode 512
    #define INA3221_AVERAGE_1024                    (0x0007)  // Averaging mode 1024
/*=========================================================================    
    Mask/ Enable Register (RW) - See table 20 spec
---------------------------------------------------------------------*/

    #define INA3221_REG_MASK_SCC_1                  (0x4000)  // Enable Channel 1 for Summation
    #define INA3221_REG_MASK_SCC_2                  (0x2000)  // Enable Channel 2 for Summation
    #define INA3221_REG_MASK_SCC_3                  (0x1000)  // Enable Channel 3 for Summation
    
    #define INA3221_REG_MASK_WEN                    (0x0800)  // Warning-alert latch enable
    #define INA3221_REG_MASK_CEN                    (0x0400)  // Critical-alert latch enable
    
    #define INA3221_REG_MASK_CF_1                   (0x0200)  // Critical-alert flag indicator for Channel 1
    #define INA3221_REG_MASK_CF_2                   (0x0100)  // Critical-alert flag indicator for Channel 2
    #define INA3221_REG_MASK_CF_3                   (0x0080)  // Critical-alert flag indicator for Channel 3
    
    #define INA3221_REG_MASK_SF                     (0x0040)  // Summation-alert flag indicator

    #define INA3221_REG_MASK_WF_1                   (0x0020)  // Warning-alert flag indicator for Channel 1
    #define INA3221_REG_MASK_WF_2                   (0x0010)  // Warning-alert flag indicator for Channel 2
    #define INA3221_REG_MASK_WF_3                   (0x0008)  // Warning-alert flag indicator for Channel 3

    #define INA3221_REG_MASK_PVF                    (0x0004)  // Power-vaild-alert flag indicator
    #define INA3221_REG_MASK_TCF                    (0x0002)  // Timing-control-alert flag indicator
    #define INA3221_REG_MASK_CVRF                   (0x0001)  // Conversion-ready flag
/*=========================================================================    
    Manufacturer ID (R) - See table 23 spec
---------------------------------------------------------------------*/
    #define INA3221_REG_MANUFACTURER_ID_VALUE       (0x5449)  // Manufacturer ID bits
/*=========================================================================    
    Die ID (R) - See table 24 spec
---------------------------------------------------------------------*/
    #define INA3221_REG_DIE_ID_VALUE                (0x3220)  // Die ID bits
/*=========================================================================*/
    #define INA3221_REG_CONFIG                      (0x00)  // Configuration Register (RW)
    #define INA3221_REG_SHUNTVOLTAGE_1              (0x01)  // Channel-1 Shunt Voltage (R)
    #define INA3221_REG_BUSVOLTAGE_1                (0x02)  // Channel-1 Bus Voltage (R)
    #define INA3221_REG_SHUNTVOLTAGE_2              (0x03)  // Channel-2 Shunt Voltage (R)
    #define INA3221_REG_BUSVOLTAGE_2                (0x04)  // Channel-2 Bus Voltage (R)
    #define INA3221_REG_SHUNTVOLTAGE_3              (0x05)  // Channel-3 Shunt Voltage (R)
    #define INA3221_REG_BUSVOLTAGE_3                (0x06)  // Channel-3 Bus Voltage (R)
    #define INA3221_REG_CRITICAL_1                  (0x07)  // Channel-1 Critical Alert Limit (RW)
    #define INA3221_REG_WARNING_1                   (0x08)  // Channel-1 Warning-Alert Limit (RW) 
    #define INA3221_REG_CRITICAL_2                  (0x09)  // Channel-2 Critical Alert Limit (RW)
    #define INA3221_REG_WARNING_2                   (0x0A)  // Channel-2 Warning-Alert Limit (RW) 
    #define INA3221_REG_CRITICAL_3                  (0x0B)  // Channel-3 Critical Alert Limit (RW)
    #define INA3221_REG_WARNING_3                   (0x0C)  // Channel-3 Warning-Alert Limit (RW)  
    #define INA3221_REG_SUM_SHUNTVOLTAGE            (0x0D)  // Shunt Voltage Sum (R)
    #define INA3221_REG_SUM_LIMIT                   (0x0E)  // Shunt Voltage Sum Limit (RW)
    #define INA3221_REG_MASK                        (0x0F)  // Mask/ Enable (RW)
    #define INA3221_REG_POWERVALID_UPPER_LIMIT      (0x10)  // Power-Valid Upper Limit (RW)
    #define INA3221_REG_POWERVALID_LOWER_LIMIT      (0x11)  // Power-Valid Lower Limit (RW)
    #define INA3221_REG_MANUFACTURER_ID             (0xFE)  // Manufacturer ID (R)
    #define INA3221_REG_DIE_ID                      (0xFF)  // Die ID (R)

    #define SHUNT_RESISTOR_VALUE  (0.1)   // default shunt resistor value of 0.1 Ohm
		void INA3221_INIT(uint16_t mode_init,float shuntresistor_1_init, float shuntresistor_2_init, float shuntresistor_3_init,
														float value_low_init,float value_high_init, uint16_t shunt_conversion_time_init,  
														uint16_t bus_conversion_time_init, uint16_t averaging_mode_init);
    void INA3221ConfSetShuntValues (float shuntresistor_1, float shuntresistor_2, float shuntresistor_3);  
    void INA3221ConfSetI2CAdr(uint8_t);                                                                    
    void INA3221ConfWriteRegister (uint8_t reg, uint16_t value);                                          
    uint16_t INA3221ConfReadRegister(uint8_t reg);                                                        
    uint16_t INA3221ConfGetManufacturerID(void);                                                        
    uint16_t INA3221ConfGetDieID(void);                                                                 
    uint8_t INA3221ConfCheckConnection(void);                                                           
    int16_t INA3221ConfGetRawShuntVoltage(uint8_t channel);                                             
    float INA3221ConfGetShuntVoltage(uint8_t channel);                                                  
    float INA3221ConfGetCurrent(uint8_t channel);                                                         
    int16_t INA3221ConfGetRawBusVoltage(uint8_t channel);                                                
    float INA3221ConfGetBusVoltage(uint8_t channel);                                                     
    int16_t INA3221ConfGetRawCriticalAlertLimit(uint8_t channel);                                         
    float INA3221ConfGetCurrentCriticalAlertLimit(uint8_t channel);                                      
    void INA3221ConfSetRawCriticalAlertLimit(uint8_t channel, uint16_t value);                         
    void INA3221ConfSetCurrentCriticalAlertLimit(uint8_t channel, float current );                    
    int16_t INA3221ConfGetRawWarningAlertLimit(uint8_t channel);                                          
    float INA3221ConfGetCurrentWarningAlertLimit(uint8_t channel);                                       
    void INA3221ConfSetRawWarningAlertLimit(uint8_t channel, int16_t value);                            
    void INA3221ConfSetCurrentWarningAlertLimit(uint8_t channel, float current );                        
    int16_t INA3221ConfGetRawShuntVoltageSum(void);                                                       
    float INA3221ConfGetShuntVoltageSum(void);                                                          
    int16_t INA3221ConfGetRawShuntVoltageSumLimit(void);                                                  
    float INA3221ConfGetShuntVoltageSumLimit(void);                                                       
    void INA3221ConfSetRawShuntVoltageSumLimit(uint16_t value );                                          
    void INA3221ConfSetShuntVoltageSumLimit(float value);                                                  
    int16_t INA3221ConfGetRawPowerValidUpperLimit(void);                                                   
    float INA3221ConfGetPowerValidUpperLimitVoltage(void);                                                 
    void INA3221ConfSetRawPowerValidUpperLimit(uint16_t value );                                           
    void INA3221ConfSetPowerValidUpperLimitVoltage(float value);                                           
    int16_t INA3221ConfGetRawPowerValidLowerLimit(void);                                                   
    float INA3221ConfGetPowerValidLowerLimitVoltage(void);                                                 
    void INA3221ConfSetRawPowerValidLowerLimit(uint16_t value );                                           
    void INA3221ConfSetPowerValidLowerLimitVoltage(float value);                                           
    uint16_t INA3221ConfGetConfiguration(void);                                                            
    void INA3221ConfSetConfiguration(uint16_t value);                                                      
    void INA3221ConfSetMode(uint16_t mode);                                                                
    void INA3221ConfSetShuntConversionTime(uint16_t shunt_conversion_time);                                
    void INA3221ConfSetBusConversionTime(uint16_t bus_conversion_time);                                    
    void INA3221ConfSetAveragingMode(uint16_t averaging_mode);                                             
    void INA3221ConfEnableChannel(uint16_t channel);                                                       
    void INA3221ConfDisableChannel(uint16_t channel);                                                      
    void INA3221ConfRest(void);                                                                            
    uint16_t INA3221ConfGetMask(void);                                                                     
    void INA3221ConfSetMask(uint16_t value);                                                               
    uint8_t INA3221ConfConversionReady(void);                                                              
    uint8_t INA3221ConfGetTimingAlertFlag(void);                                                           
    uint8_t INA3221ConfGetPowerVaildAlertFlag(void);                                                       
    uint8_t INA3221ConfGetWarningAlertFlag(uint8_t channel);                                               
    uint8_t INA3221ConfGetSummationAlertFlag(void);                                                        
    uint8_t INA3221ConfGetCriticalAlertFlag(uint8_t channel);                                              
    uint8_t INA3221ConfGetCriticalAlertLachEnable(void);                                                   
    void INA3221ConfSetCriticalAlertLachEnable(uint8_t value);                                                
    uint8_t INA3221ConfGetWarningAlertLachEnable(void);                                                    
    void INA3221ConfSetWarningAlertLachEnable(uint8_t value);                                              
    void INA3221ConfEnableChannelSummation(uint16_t channel);                                              
    void INA3221ConfDisableChannelSummation(uint16_t channel); 

#endif