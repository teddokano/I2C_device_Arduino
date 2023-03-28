/** I2C device abstracting class
 *
 *	This class provides common methods for all I2C devices
 *
 *  @class   I2C_device
 *  @author  Tedd OKANO
 *  @version 0.1
 *  @date    29-Mar-2023
 *
 *  Released under the MIT license License
 */

#ifndef ARDUINO_I2C_DEVICE_H
#define ARDUINO_I2C_DEVICE_H

#include <Arduino.h>
#include <stdint.h>
#include <Wire.h>

class I2C_device
{
public:
	/** Create a I2C_device instance with specified address
     *
	 * @param i2c_address I2C-bus address
	 * @param repeated_start_enable repeated-START-condition enable between write and read transaction for register reading. Default: true
     */
	I2C_device( uint8_t i2c_address, bool repeated_start_enable = true );

    /** Destructor of I2C_device
     */
    ~I2C_device();
	
	/** repeated-START-condition enable
	 *
	 * @param en repeated-START-condition enable between write and read transaction for register reading. Default: true
	 */
	void repeated_start_enable( bool en = true );
	
	/** Send data
	 * 
	 * @param data pointer to data buffer
	 * @param size data size
	 * @param stop option: generating STOP-condition after transaction. Defailt: true
	 * @return transferred data size
	 */
	uint16_t tx( uint8_t *data, uint16_t size, bool stop = true );

	/** Receive data
	 * 
	 * @param data pointer to data buffer
	 * @param size data size
	 * @return transferred data size
	 */
	uint16_t rx( uint8_t *data, uint16_t size );
	
	/** Multiple register write
	 * 
	 * @param reg register index/address/pointer
	 * @param data pointer to data buffer
	 * @param size data size
	 * @return transferred data size
	 */
	uint16_t reg_w( uint8_t reg_adr, uint8_t *data, uint16_t size );

	/** Single register write
	 * 
	 * @param reg register index/address/pointer
	 * @param data pointer to data buffer
	 * @param size data size
	 * @return transferred data size
	 */
	uint16_t reg_w( uint8_t reg_adr, uint8_t data );

	/** Multiple register read
	 * 
	 * @param reg register index/address/pointer
	 * @param data pointer to data buffer
	 * @param size data size
	 * @return transferred data size
	 */
	uint16_t reg_r( uint8_t reg_adr, uint8_t *data, uint16_t size );

	/** Single register read
	 * 
	 * @param reg register index/address/pointer
	 * @return read data
	 */
	uint8_t	reg_r( uint8_t reg_adr );

	/** Register write, 8 bit
	 *
	 * @param reg register index/address/pointer
	 * @param val data value
	 */
	void write_r8( uint8_t reg, uint8_t val );

	/** Register write, 16 bit
	 * 
	 *	This 16 bit access may ot be common but it's useful for sensor devices
	 *
	 * @param reg register index/address/pointer
	 * @param val data value
	 */
	void write_r16( uint8_t reg, uint16_t val );

	/** Register read, 8 bit
	 *
	 * @param reg register index/address/pointer
	 * @return data value
	 */
	uint8_t read_r8( uint8_t reg );

	/** Register read, 16 bit
	 *	
	 *This 16 bit access may ot be common but it's useful for sensor devices
	 *
	 * @param reg register index/address/pointer
	 * @return data value
	 */
	uint16_t read_r16( uint8_t reg );

	/** ping (class method)
	 *
	 * @param target address
	 * @return true, if ACKed
	 */
	static bool ping( uint8_t addr );
	
	/** scan (class method)
	 */
	static void scan( void );
		
private:
	uint8_t	i2c_addr;
	bool	rs_dis;
};

#endif //	ARDUINO_I2C_DEVICE_H
