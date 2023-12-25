#include "ina3221.h"
typedef struct
{
    float _INA3221_shuntresistor_1;
    float _INA3221_shuntresistor_2;
    float _INA3221_shuntresistor_3;
      
    float _Shunt_Resistor_Ch1;
    float _Shunt_Resistor_Ch2;
    float _Shunt_Resistor_Ch3;
		
		char rx[2];
		char tx[2];
}INA3221_DATA;
INA3221_DATA INAA;

extern I2C_HandleTypeDef hi2c2;

void INA3221ConfWriteRegister(uint8_t reg, uint16_t value)
{
			
//			char rx[2];
//			char tx[2];
    INAA.tx[0]=((value >> 8) & 0xFF);
		INAA.tx[1]=(value & 0xFF);
		HAL_I2C_Mem_Write(&hi2c2,INA_ID,reg,I2C_MEMADD_SIZE_8BIT,(uint8_t*)&INAA.tx,2,0x10000);  
}

uint16_t INA3221ConfReadRegister(uint8_t reg)
{
	  HAL_I2C_Mem_Read(&hi2c2,INA_ID,reg,I2C_MEMADD_SIZE_8BIT,(uint8_t*)&INAA.rx,2,0x10000);
    return (int)INAA.rx[0]<<8|(int)INAA.rx[1];
}

/**************************************************************************/
/*! 
    @brief Set shunt resistor values (default 0.1 Ohm)
*/
/**************************************************************************/
void INA3221ConfSetShuntValues (float shuntresistor_1, float shuntresistor_2, float shuntresistor_3)
{
    INAA._INA3221_shuntresistor_1 = shuntresistor_1;
    INAA._INA3221_shuntresistor_2 = shuntresistor_2;
    INAA._INA3221_shuntresistor_3 = shuntresistor_3; 
}
/**************************************************************************/
/*! 
    @brief  Get Manufacturer ID -> INA3221_REG_MANUFACTURER_ID_VALUE (0x5449)
*/
/**************************************************************************/
uint16_t INA3221ConfGetManufacturerID(void)
{
    return INA3221ConfReadRegister(INA3221_REG_MANUFACTURER_ID);
}

/**************************************************************************/
/*! 
    @brief  Get Die ID -> INA3221_REG_DIE_ID_VALUE (0x3220)
*/
/**************************************************************************/
uint16_t INA3221ConfGetDieID(void)
{
    return INA3221ConfReadRegister(INA3221_REG_DIE_ID);
}

/**************************************************************************/
/*! 
    @brief  Check connection
    Return: 1 - Connection OK 
            0 - no Connection
*/
/**************************************************************************/
uint8_t INA3221ConfCheckConnection(void)
{
    return ((INA3221ConfGetManufacturerID() == INA3221_REG_MANUFACTURER_ID_VALUE) && (INA3221ConfGetDieID() == INA3221_REG_DIE_ID_VALUE));
}

/**************************************************************************/
/*! 
    @brief  Get raw register value from shunt voltage register 
    Return: Raw Register Value 
*/
/**************************************************************************/
int16_t INA3221ConfGetRawShuntVoltage(uint8_t channel)
{
    switch(channel){
        case 1: return ((int16_t)INA3221ConfReadRegister(INA3221_REG_SHUNTVOLTAGE_1)>>3); 
        case 2: return ((int16_t)INA3221ConfReadRegister(INA3221_REG_SHUNTVOLTAGE_2)>>3); 
        case 3: return ((int16_t)INA3221ConfReadRegister(INA3221_REG_SHUNTVOLTAGE_3)>>3); 
        default: return 0;
    }
}

/**************************************************************************/
/*! 
    @brief  Get voltage from Shunt voltage register (Convert raw value to voltage) 
    Return: Voltage from Shunt voltage register 
*/
/**************************************************************************/
float INA3221ConfGetShuntVoltage(uint8_t channel)
{
    return ((float)INA3221ConfGetRawShuntVoltage(channel)*INA3221_SHUNT_VOLTAGE_LSB);
}

/**************************************************************************/
/*! 
    @brief  Get current from Shunt voltage register (Convert voltage value to current) 
    Return: Current through shunt resistor
*/
/**************************************************************************/
float INA3221ConfGetCurrent(uint8_t channel)
{
    float voltage = INA3221ConfGetShuntVoltage(channel);

    switch(channel){
        case 1: return (voltage / INAA._INA3221_shuntresistor_1); 
        case 2: return (voltage / INAA._INA3221_shuntresistor_2);
        case 3: return (voltage / INAA._INA3221_shuntresistor_3); 
        default: return 0.0;
    }
}

/**************************************************************************/
/*! 
    @brief  Get raw register value from bus voltage register 
    Return: Raw Register Value 
*/
/**************************************************************************/
int16_t INA3221ConfGetRawBusVoltage(uint8_t channel)
{
    switch(channel){
        case 1: return ((int16_t)INA3221ConfReadRegister(INA3221_REG_BUSVOLTAGE_1)>>3);
        case 2: return ((int16_t)INA3221ConfReadRegister(INA3221_REG_BUSVOLTAGE_2)>>3);
        case 3: return ((int16_t)INA3221ConfReadRegister(INA3221_REG_BUSVOLTAGE_3)>>3);
        default: return 0;
    }
}

/**************************************************************************/
/*! 
    @brief  Get voltage from bus voltage register (Convert raw value to voltage) 
    Return: Voltage from Bus voltage register  
*/
/**************************************************************************/
float INA3221ConfGetBusVoltage(uint8_t channel)
{
    return ((float)INA3221ConfGetRawBusVoltage(channel)*INA3221_BUS_VOLTAGE_LSB);
}

/**************************************************************************/
/*! 
    @brief  Get raw register value from critical alert limit register 
    Return: Raw Register Value 
*/
/**************************************************************************/
int16_t INA3221ConfGetRawCriticalAlertLimit(uint8_t channel)
{
    switch(channel){
        case 1: return ((int16_t)INA3221ConfReadRegister(INA3221_REG_CRITICAL_1)>>3);
        case 2: return ((int16_t)INA3221ConfReadRegister(INA3221_REG_CRITICAL_2)>>3);
        case 3: return ((int16_t)INA3221ConfReadRegister(INA3221_REG_CRITICAL_3)>>3);
        default: return 0;
    }
}

/**************************************************************************/
/*! 
    @brief  Get current setpoint from the critical alert limit register (Convert raw value to current) 
    Return: Current setpoint for critical alert limit
*/
/**************************************************************************/
float INA3221ConfGetCurrentCriticalAlertLimit(uint8_t channel)
{
    float voltage=((float)INA3221ConfGetRawCriticalAlertLimit(channel))*INA3221_SHUNT_VOLTAGE_LSB; 
    switch(channel){
        case 1: return (voltage / INAA._INA3221_shuntresistor_1);
        case 2: return (voltage / INAA._INA3221_shuntresistor_2);
        case 3: return (voltage / INAA._INA3221_shuntresistor_3);
        default: return 0;
    }
}

/**************************************************************************/
/*! 
    @brief  Set raw register value to critical alert limit register 
*/
/**************************************************************************/
void INA3221ConfSetRawCriticalAlertLimit(uint8_t channel, uint16_t value)
{
    value = value << 3;
    switch(channel){
        case 1: INA3221ConfWriteRegister(INA3221_REG_CRITICAL_1,value); break;
        case 2: INA3221ConfWriteRegister(INA3221_REG_CRITICAL_2,value); break;
        case 3: INA3221ConfWriteRegister(INA3221_REG_CRITICAL_3,value); break;
    }
}

/**************************************************************************/
/*! 
    @brief  Set current value to critical alert register 
*/
/**************************************************************************/
void INA3221ConfSetCurrentCriticalAlertLimit(uint8_t channel, float current )
{
    float value;
    switch(channel){
        case 1: value = INAA._INA3221_shuntresistor_1; break;
        case 2: value = INAA._INA3221_shuntresistor_2; break;
        case 3: value = INAA._INA3221_shuntresistor_3; break;
    }
    
    value = ((value*current) / (INA3221_SHUNT_VOLTAGE_LSB));
    INA3221ConfSetRawCriticalAlertLimit(channel, (uint16_t)value);
}

/**************************************************************************/
/*! 
    @brief  Get raw register value from warning alert limit register 
    Return: Raw Register Value 
*/
/**************************************************************************/
int16_t INA3221ConfGetRawWarningAlertLimit(uint8_t channel)
{
    switch(channel){
        case 1: return ((int16_t)INA3221ConfReadRegister(INA3221_REG_WARNING_1)>>3); 
        case 2: return ((int16_t)INA3221ConfReadRegister(INA3221_REG_WARNING_2)>>3); 
        case 3: return ((int16_t)INA3221ConfReadRegister(INA3221_REG_WARNING_3)>>3); 
        default: return 0;
    }
}

/**************************************************************************/
/*! 
    @brief  Get current setpoint from the warning alert limit register (Convert raw value to current) 
    Return: Current setpoint for warning alert limit
*/
/**************************************************************************/
float INA3221ConfGetCurrentWarningAlertLimit(uint8_t channel)
{
    float voltage =((float)INA3221ConfGetRawWarningAlertLimit(channel))*INA3221_SHUNT_VOLTAGE_LSB; 
    switch(channel){
        case 1: return (voltage / INAA._INA3221_shuntresistor_1); 
        case 2: return (voltage / INAA._INA3221_shuntresistor_2); 
        case 3: return (voltage / INAA._INA3221_shuntresistor_3);
        default: return 0;
    }
}

/**************************************************************************/
/*! 
    @brief  Set raw register value to warning alert limit register 
*/
/**************************************************************************/
void INA3221ConfSetRawWarningAlertLimit(uint8_t channel, int16_t value)
{
    value = value << 3;
    switch(channel){
        case 1: INA3221ConfWriteRegister(INA3221_REG_WARNING_1,value); break;
        case 2: INA3221ConfWriteRegister(INA3221_REG_WARNING_2,value); break;
        case 3: INA3221ConfWriteRegister(INA3221_REG_WARNING_3,value); break;
    }
}

/**************************************************************************/
/*! 
    @brief  Set current value to warning alert register 
*/
/**************************************************************************/
void INA3221ConfSetCurrentWarningAlertLimit(uint8_t channel, float current )
{
    float value;
    switch(channel){
        case 1: value = INAA._INA3221_shuntresistor_1; break;
        case 2: value = INAA._INA3221_shuntresistor_2; break;
        case 3: value = INAA._INA3221_shuntresistor_3; break;
    }
    
    value = ((value*current) / (INA3221_SHUNT_VOLTAGE_LSB));
    INA3221ConfSetRawWarningAlertLimit(channel, (int16_t)value);
}

/**************************************************************************/
/*! 
    @brief  Get raw register value from shunt voltage sum register 
    Return: Raw Register Value 
*/
/**************************************************************************/
int16_t INA3221ConfGetRawShuntVoltageSum(void)
{
    return ((int16_t)INA3221ConfReadRegister(INA3221_REG_SUM_SHUNTVOLTAGE)>>1);
}

/**************************************************************************/
/*! 
    @brief  Get voltage value from shunt voltage sum register (Convert raw value to voltage)
    Return: Voltage form shunt voltage sum register
*/
/**************************************************************************/
float INA3221ConfGetShuntVoltageSum(void)
{
    return ((float)INA3221ConfGetRawShuntVoltageSum() * INA3221_SHUNT_VOLTAGE_LSB);
}

/**************************************************************************/
/*! 
    @brief  Get raw register value from shunt voltage sum limit register 
    Return: Raw Register Value 
*/
/**************************************************************************/
int16_t INA3221ConfGetRawShuntVoltageSumLimit(void)
{
    return ((int16_t)INA3221ConfReadRegister(INA3221_REG_SUM_LIMIT)>>1);
}

/**************************************************************************/
/*! 
    @brief  Get voltage value from shunt voltage sum limit register (Convert raw value to voltage)
    Return: Voltage setpoint for shunt voltage sum limit register
*/
/**************************************************************************/
float INA3221ConfGetShuntVoltageSumLimit(void)
{
    return ((float)INA3221ConfGetRawShuntVoltageSumLimit() * INA3221_SHUNT_VOLTAGE_LSB);
}

/**************************************************************************/
/*! 
    @brief  Set raw register value to shunt voltage sum limit register 
*/
/**************************************************************************/
void INA3221ConfSetRawShuntVoltageSumLimit(uint16_t value )
{
        value = value << 1;
        INA3221ConfWriteRegister(INA3221_REG_SUM_LIMIT,value);
}

/**************************************************************************/
/*! 
    @brief  Set voltage value to shunt voltage sum limit register 
*/
/**************************************************************************/
void INA3221ConfSetShuntVoltageSumLimit(float value)
{
    value = value / INA3221_SHUNT_VOLTAGE_LSB ;
    INA3221ConfSetRawShuntVoltageSumLimit((uint16_t)value);
}

/**************************************************************************/
/*! 
    @brief  Get raw register value from power valid upper limit register 
    Return: Raw Register Value 
*/
/**************************************************************************/
int16_t INA3221ConfGetRawPowerValidUpperLimit(void)
{
    return ((int16_t)INA3221ConfReadRegister(INA3221_REG_POWERVALID_UPPER_LIMIT)>>3);
}

/**************************************************************************/
/*! 
    @brief  Get voltage value from power valid upper limit register (Convert raw value to voltage)
    Return: Voltage setpoint for power vaild upper limit register
*/
/**************************************************************************/
float INA3221ConfGetPowerValidUpperLimitVoltage(void)
{
    return ((float)INA3221ConfGetRawPowerValidUpperLimit() * INA3221_BUS_VOLTAGE_LSB);
}

/**************************************************************************/
/*! 
    @brief  Set raw register value to power valid upper limit register 
*/
/**************************************************************************/
void INA3221ConfSetRawPowerValidUpperLimit(uint16_t value )
{
        value = value << 3;
        INA3221ConfWriteRegister(INA3221_REG_POWERVALID_UPPER_LIMIT,value);
}

/**************************************************************************/
/*! 
    @brief  Set voltage value to power valid upper limit register 
*/
/**************************************************************************/
void INA3221ConfSetPowerValidUpperLimitVoltage(float value)
{
    value = value / INA3221_BUS_VOLTAGE_LSB ;
    INA3221ConfSetRawPowerValidUpperLimit((uint16_t)value);
}

/**************************************************************************/
/*! 
    @brief  Get raw register value from power valid lower limit register 
    Return: Raw Register Value 
*/
/**************************************************************************/
int16_t INA3221ConfGetRawPowerValidLowerLimit(void)
{
    return ((int16_t)INA3221ConfReadRegister(INA3221_REG_POWERVALID_LOWER_LIMIT)>>3);
}

/**************************************************************************/
/*! 
    @brief  Get voltage value from power valid lower limit register (Convert raw value to voltage)
    Return: Voltage setpoint for power vaild lower limit register
*/
/**************************************************************************/
float INA3221ConfGetPowerValidLowerLimitVoltage(void)
{
    return ((float)INA3221ConfGetRawPowerValidLowerLimit() * INA3221_BUS_VOLTAGE_LSB);
}

/**************************************************************************/
/*! 
    @brief  Set raw register value to power valid lower limit register 
*/
/**************************************************************************/
void INA3221ConfSetRawPowerValidLowerLimit(uint16_t value )
{
        value = value << 3;
        INA3221ConfWriteRegister(INA3221_REG_POWERVALID_LOWER_LIMIT,value);
}

/**************************************************************************/
/*! 
    @brief  Set voltage value to power valid lower limit register 
*/
/**************************************************************************/
void INA3221ConfSetPowerValidLowerLimitVoltage(float value)
{
    value = value / INA3221_BUS_VOLTAGE_LSB ;
    INA3221ConfSetRawPowerValidLowerLimit((uint16_t)value);
}

/**************************************************************************/
/*! 
    @brief  Get raw content of configuration register 
    Return: Raw Register Value 
*/
/**************************************************************************/
uint16_t INA3221ConfGetConfiguration(void)
{
    return (uint16_t)INA3221ConfReadRegister(INA3221_REG_CONFIG);
}

/**************************************************************************/
/*! 
    @brief  Set raw register value to configuration register 
*/
/**************************************************************************/
void INA3221ConfSetConfiguration(uint16_t value)
{
    INA3221ConfWriteRegister(INA3221_REG_CONFIG , value);
}

/**************************************************************************/
/*! 
    @brief  Set mode bits in configuration register to: 
    INA3221_MODE_POWER_DOWN                 
    INA3221_MODE_SHUNT_SINGLE               
    INA3221_MODE_BUS_SINGLE                 
    INA3221_MODE_SHUNT_BUS_SINGLE           
    INA3221_MODE_SHUNT_CONTINUOUS           
    INA3221_MODE_BUS_CONTINUOUS             
    INA3221_MODE_SHUNT_BUS_CONTINUOUS        
*/
/**************************************************************************/
void INA3221ConfSetMode(uint16_t mode)
{   
    uint16_t mode_reg = INA3221ConfGetConfiguration();
    mode_reg &= 0xFFF8;
    mode_reg |= mode;
    
    INA3221ConfSetConfiguration(mode_reg);
}

/**************************************************************************/
/*! 
    @brief  Set conversion time bits for shunt voltage measurement in configuration register to: 
    INA3221_140_US                      
    INA3221_204_US                      
    INA3221_332_US                        
    INA3221_588_US                         
    INA3221_1_1_MS                         
    INA3221_2_116_MS                        
    INA3221_4_156_MS                        
    INA3221_8_244_MS      
*/
/**************************************************************************/
void INA3221ConfSetShuntConversionTime(uint16_t shunt_conversion_time)
{   
    uint16_t mode_reg = INA3221ConfGetConfiguration();
    mode_reg &= 0xFFC7;
    mode_reg |= shunt_conversion_time<<3;
    
    INA3221ConfSetConfiguration(mode_reg);
}

/**************************************************************************/
/*! 
    @brief  Set conversion time bits for bus voltage measurement in configuration register to: 
    INA3221_140_US                      
    INA3221_204_US                      
    INA3221_332_US                        
    INA3221_588_US                         
    INA3221_1_1_MS                         
    INA3221_2_116_MS                        
    INA3221_4_156_MS                        
    INA3221_8_244_MS      
*/
/**************************************************************************/
void INA3221ConfSetBusConversionTime(uint16_t bus_conversion_time)
{   
    uint16_t mode_reg = INA3221ConfGetConfiguration();
    mode_reg &= 0xFE3F;
    mode_reg |= bus_conversion_time<<6;
    
    INA3221ConfSetConfiguration(mode_reg);
}

/**************************************************************************/
/*! 
    @brief  Set averaging mode in configuration register to:
    INA3221_AVERAGE_1                     
    INA3221_AVERAGE_4                       
    INA3221_AVERAGE_16                      
    INA3221_AVERAGE_64                      
    INA3221_AVERAGE_128                     
    INA3221_AVERAGE_256                     
    INA3221_AVERAGE_512                     
    INA3221_AVERAGE_1024                   
*/
/**************************************************************************/
void INA3221ConfSetAveragingMode(uint16_t averaging_mode)
{   
    uint16_t mode_reg = INA3221ConfGetConfiguration();
    mode_reg &= 0xF1FF;
    mode_reg |= (averaging_mode<<9);
    
    INA3221ConfSetConfiguration(mode_reg);
}

/**************************************************************************/
/*! 
    @brief  Enable measurement for single channel
    INA3221_CONFIG_CH1            
    INA3221_CONFIG_CH2                   
    INA3221_CONFIG_CH3 
*/
/**************************************************************************/
void INA3221ConfEnableChannel(uint16_t channel)
{   
    uint16_t mode_reg = INA3221ConfGetConfiguration();
    switch(channel){
        case 1: mode_reg |= INA3221_CONFIG_CH1; break;
        case 2: mode_reg |= INA3221_CONFIG_CH2; break;
        case 3: mode_reg |= INA3221_CONFIG_CH3; break;
    }
    
    INA3221ConfSetConfiguration(mode_reg);
}

/**************************************************************************/
/*! 
    @brief  Disable measurement for single channel
    INA3221_CONFIG_CH1            
    INA3221_CONFIG_CH2                   
    INA3221_CONFIG_CH3 
*/
/**************************************************************************/
void INA3221ConfDisableChannel(uint16_t channel)
{   
    uint16_t mode_reg = INA3221ConfGetConfiguration();
    switch(channel){
        case 1: mode_reg &= (~INA3221_CONFIG_CH1); break;
        case 2: mode_reg &= (~INA3221_CONFIG_CH2); break;
        case 3: mode_reg &= (~INA3221_CONFIG_CH3); break;
    }
    
    INA3221ConfSetConfiguration(mode_reg);
}

/**************************************************************************/
/*! 
    @brief  Generate a system reset that is the same as a power-on reset (POR).
            This bit resets all registers to default values and self-clears.
*/
/**************************************************************************/
void INA3221ConfRest(void)
{   
    uint16_t mode_reg = INA3221ConfGetConfiguration();
    mode_reg &= 0xEFFF;
    mode_reg |= INA3221_CONFIG_RST;
    
    INA3221ConfSetConfiguration(mode_reg);
}

/**************************************************************************/
/*! 
    @brief  Get raw register value from mask register 
    Return: Raw Register Value 
*/
/**************************************************************************/
uint16_t INA3221ConfGetMask(void)
{
    return (uint16_t)INA3221ConfReadRegister(INA3221_REG_MASK);
}

/**************************************************************************/
/*! 
    @brief  Set raw register value to mask register 
*/
/**************************************************************************/
void INA3221ConfSetMask(uint16_t value)
{
    INA3221ConfWriteRegister (INA3221_REG_MASK , value);
}

/**************************************************************************/
/*! 
    @brief  Check if conversion has finished  
    Return: 1 after all conversions are complete else 0
*/
/**************************************************************************/
uint8_t INA3221ConfConversionReady(void)
{
    uint16_t mask = INA3221ConfGetMask();
    mask &= INA3221_REG_MASK_CVRF;
     
    return  (uint8_t)mask;
}

/**************************************************************************/
/*! 
    @brief  Get Timing-control-alert flag indicator 
*/
/**************************************************************************/
uint8_t INA3221ConfGetTimingAlertFlag(void)
{
    uint16_t mask = INA3221ConfGetMask();
    mask &= INA3221_REG_MASK_TCF;
    mask = mask >>1;
     
    return  (uint8_t)mask;
}

/**************************************************************************/
/*! 
    @brief  Get Power-valid-alert flag indicator
*/
/**************************************************************************/
uint8_t INA3221ConfGetPowerVaildAlertFlag(void)
{
    uint16_t mask = INA3221ConfGetMask();
    mask &= INA3221_REG_MASK_PVF;
    mask = mask >>2;
     
    return  (uint8_t)mask;
}

/**************************************************************************/
/*! 
    @brief  Get Warning-alert flag indicator for one channel
*/
/**************************************************************************/
uint8_t INA3221ConfGetWarningAlertFlag(uint8_t channel)
{
    uint16_t mask = INA3221ConfGetMask();
    
    switch(channel){
        case 1: mask &= INA3221_REG_MASK_WF_1; mask= mask >> 5; break;
        case 2: mask &= INA3221_REG_MASK_WF_2; mask= mask >> 4; break;
        case 3: mask &= INA3221_REG_MASK_WF_3; mask= mask >> 3; break;
    }
     
    return  (uint8_t)mask;
}

/**************************************************************************/
/*! 
    @brief  Get Summation-alert flag indicator 
*/
/**************************************************************************/
uint8_t INA3221ConfGetSummationAlertFlag(void)
{
    uint16_t mask = INA3221ConfGetMask();
    mask &= INA3221_REG_MASK_SF ;
    mask = mask >>6;
     
    return  (uint8_t)mask;
}

/**************************************************************************/
/*! 
    @brief  Get Critical-alert flag indicator for one channel
*/
/**************************************************************************/
uint8_t INA3221ConfGetCriticalAlertFlag(uint8_t channel)
{
    uint16_t mask = INA3221ConfGetMask();
    
    switch(channel){
        case 1: mask &= INA3221_REG_MASK_CF_1; mask= mask >> 9; break;
        case 2: mask &= INA3221_REG_MASK_CF_2; mask= mask >> 8; break;
        case 3: mask &= INA3221_REG_MASK_CF_3; mask= mask >> 7; break;
    }
     
    return  (uint8_t)mask;
}

/**************************************************************************/
/*! 
    @brief  Get Critical alert latch enable bit 
    Return: 0 = Transparent (default)
            1 = Latch enabled
*/
/**************************************************************************/
uint8_t INA3221ConfGetCriticalAlertLachEnable(void)
{
    uint16_t mask = INA3221ConfGetMask();
    mask &= INA3221_REG_MASK_CEN ;
    mask = mask >>10;
     
    return  (uint8_t)mask;
}

/**************************************************************************/
/*! 
    @brief  Set Critical alert latch enable bit 
*/
/**************************************************************************/
void INA3221ConfSetCriticalAlertLachEnable(uint8_t value)
{
    uint16_t mask = INA3221ConfGetMask();
    mask &= (~INA3221_REG_MASK_CEN);
    mask |= (value << 10);
         
    INA3221ConfSetMask(mask);
}

/**************************************************************************/
/*! 
    @brief  Get warning alert latch enable bit 
    Return: 0 = Transparent (default)
            1 = Latch enabled
*/
/**************************************************************************/
uint8_t INA3221ConfGetWarningAlertLachEnable(void)
{
    uint16_t mask = INA3221ConfGetMask();
    mask &= INA3221_REG_MASK_WEN ;
    mask = mask >>11;
     
    return  (uint8_t)mask;
}

/**************************************************************************/
/*! 
    @brief  Set warning alert latch enable bit 
*/
/**************************************************************************/
void INA3221ConfSetWarningAlertLachEnable(uint8_t value)
{
    uint16_t mask = INA3221ConfGetMask();
    mask &= (~INA3221_REG_MASK_WEN);
    mask |= (value << 11);
         
    INA3221ConfSetMask(mask);
}

/**************************************************************************/
/*! 
    @brief  Enable channel for summation 
*/
/**************************************************************************/
void INA3221ConfEnableChannelSummation(uint16_t channel)
{   
    uint16_t mask = INA3221ConfGetMask();
    switch(channel){
        case 1: mask |= INA3221_REG_MASK_SCC_1; break;
        case 2: mask |= INA3221_REG_MASK_SCC_2; break;
        case 3: mask |= INA3221_REG_MASK_SCC_3; break;
    }
    
    INA3221ConfSetMask(mask);
}

/**************************************************************************/
/*! 
    @brief  Disable channel for summation 
 
*/
/**************************************************************************/
void INA3221ConfDisableChannelSummation(uint16_t channel)
{   
    uint16_t mask = INA3221ConfGetMask();
    switch(channel){
        case 1: mask &= (~INA3221_REG_MASK_SCC_1 ); break;
        case 2: mask &= (~INA3221_REG_MASK_SCC_2 ); break;
        case 3: mask &= (~INA3221_REG_MASK_SCC_3); break;
    }
    
    INA3221ConfSetMask(mask);
}


void INA3221_INIT(uint16_t mode_init,float shuntresistor_1_init, float shuntresistor_2_init, float shuntresistor_3_init,
														float value_low_init,float value_high_init, uint16_t shunt_conversion_time_init,  
														uint16_t bus_conversion_time_init, uint16_t averaging_mode_init)
{
		INA3221ConfRest();
    INA3221ConfSetMode(mode_init);
		INA3221ConfSetShuntValues(shuntresistor_1_init, shuntresistor_2_init, shuntresistor_3_init);
    INA3221ConfSetPowerValidLowerLimitVoltage(value_low_init);
    INA3221ConfSetPowerValidUpperLimitVoltage(value_high_init);
    INA3221ConfSetShuntConversionTime(shunt_conversion_time_init);                          
    INA3221ConfSetBusConversionTime(bus_conversion_time_init);                            
    INA3221ConfSetAveragingMode(averaging_mode_init);
	
    for(int i = 1;i<4;i++)
    {
        INA3221ConfEnableChannel(i); 
        INA3221ConfEnableChannelSummation(i);
    }
}