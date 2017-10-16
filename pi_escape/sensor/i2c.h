#ifndef I2C
#define I2C

int i2c_init_adapter(int);
int i2c_write_byte_data(int, uint8_t , uint8_t );
int i2c_read_byte_data(int, uint8_t);

#endif /* I2C */