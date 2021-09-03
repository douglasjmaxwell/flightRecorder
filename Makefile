CC=g++
CFLAGS = -std=c++11 -I. -I/usr/include/i2c -I../bmp388 -I../imu
LFLAGS = -lm -lwiringPi -li2c
DEPS = ../imu/IMU.h ../bmp388/BMP388.h
OBJ = flightRecorder.o ../imu/IMU.o ../bmp388/BMP388.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

flightRecorder: $(OBJ)
	$(CC) -o $@ $^ $(LFLAGS)
clean:
	rm *.o
