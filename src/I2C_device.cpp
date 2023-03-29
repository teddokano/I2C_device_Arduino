#include "I2C_device.h"

I2C_device::I2C_device( uint8_t i2c_address, bool repeated_start_enable ) : i2c_addr( i2c_address ), rs_dis( !repeated_start_enable )
{
	//  do nothing.
	//  leave it in default state.
}

I2C_device::~I2C_device()
{
}

void I2C_device::repeated_start_enable( bool en )
{
	rs_dis	= !en;
}

bool I2C_device::ping( uint8_t addr )
{
	Wire.beginTransmission( addr );
	return !Wire.endTransmission();
}

void I2C_device::scan( void )
{
	bool  result[ 128 ];

	for ( uint8_t i = 0; i < 128; i++ )
		result[i] = I2C_device::ping(i);

	Serial.print( "\nI2C scan result\n   " );
	for ( uint8_t x = 0; x < 16; x++ ) {
		Serial.print( " x" );
		Serial.print( x, HEX );
	}
	
	for ( uint8_t i = 0; i < 128; i++ ) {
		if ( !( i % 16) ) {
			Serial.print( "\n" );
			Serial.print( i / 16, HEX );
			Serial.print( "x:" );
		}
		
		if ( result[ i ] ) {
			Serial.print( " " );
			Serial.print( i, HEX );
		}
		else {
			Serial.print( " --" );
		}
	}
	Serial.print( "\n" );			
}

uint16_t I2C_device::tx( uint8_t *data, uint16_t size, bool stop )
{
	Wire.beginTransmission( i2c_addr );
	size		= Wire.write( data, size );
	uint8_t rtn = Wire.endTransmission( stop );

	if (rtn)
		Serial.println( "i2c_tx: ERROR" );

	return size;
}

uint16_t I2C_device::rx( uint8_t *data, uint16_t size )
{
	uint16_t r_size = Wire.requestFrom( i2c_addr, size );

	if (r_size != size)
		Serial.println( "i2c_rx: received size was shorter than specified" );

	for ( uint16_t i = 0; i < size; i++ ) {
		while ( !Wire.available() )
			;
		data[ i ] = Wire.read();
	}
	return r_size;
}

uint16_t I2C_device::reg_w( uint8_t reg_adr, uint8_t *data, uint16_t size )
{
	uint8_t buffer[ size + 1 ];
	
	buffer[ 0 ]	= reg_adr;
	for ( uint16_t i = 0; i < size; i++)
		buffer[ i + 1 ]	= data[ i ];
	
	return tx( buffer, sizeof( buffer ) );
}

uint16_t I2C_device::reg_w( uint8_t reg_adr, uint8_t data )
{
	uint8_t buffer[ 2 ];
	
	buffer[ 0 ]	= reg_adr;
	buffer[ 1 ]	= data;
	
	return tx( buffer, sizeof( buffer ) );
}

uint16_t I2C_device::reg_r( uint8_t reg_adr, uint8_t *data, uint16_t size )
{
	tx( &reg_adr, 1, rs_dis );
	return rx( data, size );
}

uint8_t I2C_device::reg_r( uint8_t reg_adr )
{
	uint8_t	buffer;
	
	tx( &reg_adr, 1, rs_dis );
	rx( &buffer, 1 );
	return buffer;
}

void I2C_device::write_r8( uint8_t reg, uint8_t val )
{
	reg_w( reg, val );
}

void I2C_device::write_r16( uint8_t reg, uint16_t val )
{
	uint8_t	buff[ 2 ];
	
	buff[ 0 ]	= val >> 8;
	buff[ 1 ]	= val & 0xFF;
	
	reg_w( reg, buff, sizeof( buff ) );
}

uint8_t I2C_device::read_r8( uint8_t reg )
{
	return reg_r( reg );	
}

uint16_t I2C_device::read_r16( uint8_t reg )
{
	uint8_t	buff[ 2 ];

	reg_r( reg, buff, sizeof( buff ) );
	
	return (buff[ 0 ] << 8) | buff[ 1 ];
}

void I2C_device::bit_op8( uint8_t reg, uint8_t mask, uint8_t value )
{
	uint8_t	v	= read_r8( reg );

	v	&= mask;
	v	|= value;
	
	write_r8( reg, value );
}

void I2C_device::bit_op16( uint8_t reg, uint16_t mask, uint16_t value )
{
	uint16_t v	= read_r16( reg );

	v	&= mask;
	v	|= value;
	
	write_r16( reg, value );
}
