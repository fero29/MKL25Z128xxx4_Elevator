################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../source/Commands.cpp \
../source/Control.cpp \
../source/MKL25Z128xxx4_Elevator.cpp \
../source/Mytimer.cpp \
../source/Myuart.cpp \
../source/cpp_config.cpp 

C_SRCS += \
../source/mtb.c \
../source/semihost_hardfault.c 

OBJS += \
./source/Commands.o \
./source/Control.o \
./source/MKL25Z128xxx4_Elevator.o \
./source/Mytimer.o \
./source/Myuart.o \
./source/cpp_config.o \
./source/mtb.o \
./source/semihost_hardfault.o 

CPP_DEPS += \
./source/Commands.d \
./source/Control.d \
./source/MKL25Z128xxx4_Elevator.d \
./source/Mytimer.d \
./source/Myuart.d \
./source/cpp_config.d 

C_DEPS += \
./source/mtb.d \
./source/semihost_hardfault.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DSDK_OS_BAREMETAL -DFSL_RTOS_BM -DSDK_DEBUGCONSOLE=0 -DSDK_OS_FREE_RTOS -DFSL_RTOS_FREE_RTOS -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__NEWLIB__ -I"C:\Users\ferom\Documents\MCUXpressoIDE_11.1.0_3209\workspace\MKL25Z128xxx4_Elevator\board" -I"C:\Users\ferom\Documents\MCUXpressoIDE_11.1.0_3209\workspace\MKL25Z128xxx4_Elevator\source" -I"C:\Users\ferom\Documents\MCUXpressoIDE_11.1.0_3209\workspace\MKL25Z128xxx4_Elevator" -I"C:\Users\ferom\Documents\MCUXpressoIDE_11.1.0_3209\workspace\MKL25Z128xxx4_Elevator\freertos" -I"C:\Users\ferom\Documents\MCUXpressoIDE_11.1.0_3209\workspace\MKL25Z128xxx4_Elevator\drivers" -I"C:\Users\ferom\Documents\MCUXpressoIDE_11.1.0_3209\workspace\MKL25Z128xxx4_Elevator\CMSIS" -I"C:\Users\ferom\Documents\MCUXpressoIDE_11.1.0_3209\workspace\MKL25Z128xxx4_Elevator\utilities" -I"C:\Users\ferom\Documents\MCUXpressoIDE_11.1.0_3209\workspace\MKL25Z128xxx4_Elevator\CMSIS_driver" -I"C:\Users\ferom\Documents\MCUXpressoIDE_11.1.0_3209\workspace\MKL25Z128xxx4_Elevator\startup" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fno-rtti -fno-exceptions -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__NEWLIB__ -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__NEWLIB__ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DSDK_OS_BAREMETAL -DFSL_RTOS_BM -DSDK_DEBUGCONSOLE=0 -DSDK_OS_FREE_RTOS -DFSL_RTOS_FREE_RTOS -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\ferom\Documents\MCUXpressoIDE_11.1.0_3209\workspace\MKL25Z128xxx4_Elevator\board" -I"C:\Users\ferom\Documents\MCUXpressoIDE_11.1.0_3209\workspace\MKL25Z128xxx4_Elevator\source" -I"C:\Users\ferom\Documents\MCUXpressoIDE_11.1.0_3209\workspace\MKL25Z128xxx4_Elevator" -I"C:\Users\ferom\Documents\MCUXpressoIDE_11.1.0_3209\workspace\MKL25Z128xxx4_Elevator\freertos" -I"C:\Users\ferom\Documents\MCUXpressoIDE_11.1.0_3209\workspace\MKL25Z128xxx4_Elevator\drivers" -I"C:\Users\ferom\Documents\MCUXpressoIDE_11.1.0_3209\workspace\MKL25Z128xxx4_Elevator\CMSIS" -I"C:\Users\ferom\Documents\MCUXpressoIDE_11.1.0_3209\workspace\MKL25Z128xxx4_Elevator\utilities" -I"C:\Users\ferom\Documents\MCUXpressoIDE_11.1.0_3209\workspace\MKL25Z128xxx4_Elevator\CMSIS_driver" -I"C:\Users\ferom\Documents\MCUXpressoIDE_11.1.0_3209\workspace\MKL25Z128xxx4_Elevator\startup" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__NEWLIB__ -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


