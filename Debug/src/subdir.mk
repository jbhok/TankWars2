################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/TankWars2.cpp \
../src/tank.cpp \
../src/tankbullet.cpp \
../src/turret.cpp \
../src/turretbullet.cpp 

OBJS += \
./src/TankWars2.o \
./src/tank.o \
./src/tankbullet.o \
./src/turret.o \
./src/turretbullet.o 

CPP_DEPS += \
./src/TankWars2.d \
./src/tank.d \
./src/tankbullet.d \
./src/turret.d \
./src/turretbullet.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


