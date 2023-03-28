#include "test_LM75B.h"

/* LM75B class ******************************************/

test_LM75B::test_LM75B( uint8_t i2c_address ) : I2C_device( i2c_address )
{
	//  do nothing.
	//  leave it in default state.
}

test_LM75B::~test_LM75B()
{
}

float test_LM75B::read()
{
	return read_r16( Temp ) / 256.0;
}

void test_LM75B::thresholds( float v0, float v1 )
{
	float higher	= (v0 < v1) ? v1 : v0;
	float lower		= (v0 < v1) ? v0 : v1;
	
	write_r16( Tos,   ((uint16_t)(higher * 256.0)) & 0xFF80 );
	write_r16( Thyst, ((uint16_t)(lower  * 256.0)) & 0xFF80 );
}

void test_LM75B::os_mode( mode flag )
{
	uint8_t	v;
	
	v	 = read_r8( Conf );
	v	&= ~0x02;
	v	|= flag << 1;
	
	write_r8( Conf, v );
}

