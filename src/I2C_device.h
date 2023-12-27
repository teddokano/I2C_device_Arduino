/** I2C device abstracting class
 *
 *	This class provides common methods for all I2C devices
 *
 *  @class   I2C_device
 *  @author  Tedd OKANO
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

	/** Create a I2C_device instance with specified address
	 *
	 * @param wire TwoWire instance
	 * @param i2c_address I2C-bus address
	 * @param repeated_start_enable repeated-START-condition enable between write and read transaction for register reading. Default: true
	 */
	I2C_device( TwoWire& wire, uint8_t i2c_address, bool repeated_start_enable = true );

    /** Destructor of I2C_device
     */
    ~I2C_device();
	
	/** repeated-START-condition enable
	 *
	 * @param en repeated-START-condition enable between write and read transaction for register reading. Default: true
	 */
	void repeated_start_enable( bool en = true );
	
	/** Ping the device
	 *
	 * @return true when ACK 
	 */
	bool ping( void );
	
	/** Send data
	 * 
	 * @param data pointer to data buffer
	 * @param size data size
	 * @param stop option: generating STOP-condition after transaction. Defailt: true
	 * @return transferred data size or error code in negative number: -1=data too long, -2=NACK for address, -3=NACK for data, -4=Other error, -5=Time out
	 */
	int tx( const uint8_t *data, uint16_t size, bool stop = true );

	/** Receive data
	 * 
	 * @param data pointer to data buffer
	 * @param size data size
	 * @return transferred data size
	 */
	int rx( uint8_t *data, uint16_t size );
	
	/** Multiple register write
	 * 
	 * @param reg register index/address/pointer
	 * @param data pointer to data buffer
	 * @param size data size
	 * @return transferred data size
	 */
	int reg_w( uint8_t reg_adr, const uint8_t *data, uint16_t size );

	/** Single register write
	 * 
	 * @param reg register index/address/pointer
	 * @param data pointer to data buffer
	 * @param size data size
	 * @return transferred data size
	 */
	int reg_w( uint8_t reg_adr, uint8_t data );

	/** Multiple register read
	 * 
	 * @param reg register index/address/pointer
	 * @param data pointer to data buffer
	 * @param size data size
	 * @return transferred data size
	 */
	int reg_r( uint8_t reg_adr, uint8_t *data, uint16_t size );

	/** Single register read
	 * 
	 * @param reg register index/address/pointer
	 * @param data pointer to data buffer
	 * @param size data size
	 * @return read data size
	 */
	uint8_t	reg_r( uint8_t reg_adr );

	/** Register write, 8 bit
	 *
	 * @param reg register index/address/pointer
	 * @return data value
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
	 *	This 16 bit access may ot be common but it's useful for sensor devices
	 *
	 * @param reg register index/address/pointer
	 * @return data value
	 */
	uint16_t read_r16( uint8_t reg );

	/** Register overwriting with bit-mask
	 *	
	 *	Register can be updated by bit level
	 *
	 * @param reg register index/address/pointer
	 * @param mask bit-mask to protect overwriting
	 * @param value value to overwrite
	 */
	void bit_op8(  uint8_t reg,  uint8_t mask,  uint8_t value );
	void bit_op16( uint8_t reg, uint16_t mask, uint16_t value );

	/** ping (class method)
	 *
	 * @param target address
	 * @return true, if ACKed
	 */
	static bool ping( uint8_t addr );
	
	/** scan (class method)
	 */
	static void scan( TwoWire& target_i2c = Wire, uint8_t stop = 128 );
		
private:
	TwoWire&	i2c;
	uint8_t		i2c_addr;
	bool		rs_dis;
};

#endif //	ARDUINO_I2C_DEVICE_H
