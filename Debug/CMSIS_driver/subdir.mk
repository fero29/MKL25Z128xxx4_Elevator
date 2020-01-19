################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CMSIS_driver/fsl_i2c_cmsis.c \
../CMSIS_driver/fsl_lpsci_cmsis.c \
../CMSIS_driver/fsl_spi_cmsis.c \
../CMSIS_driver/fsl_uart_cmsis.c 

OBJS += \
./CMSIS_driver/fsl_i2c_cmsis.o \
./CMSIS_driver/fsl_lpsci_cmsis.o \
./CMSIS_driver/fsl_spi_cmsis.o \
./CMSIS_driver/fsl_uart_cmsis.o 

C_DEPS += \
./CMSIS_driver/fsl_i2c_cmsis.d \
./CMSIS_driver/fsl_lpsci_cmsis.d \
./CMSIS_driver/fsl_spi_cmsis.d \
./CMSIS_driver/fsl_uart_cmsis.d 


# Each subdirectory must supply rules for building sources it contributes
CMSIS_driver/%.o: ../CMSIS_driver/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__NEWLIB__ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DSDK_OS_BAREMETAL -DFSL_RTOS_BM -DSDK_DEBUGCONSOLE=0 -DSDK_OS_FREE_RTOS -DFSL_RTOS_FREE_RTOS -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\ferom\Documents\MCUXpressoIDE_11.1.0_3209\workspace\MKL25Z128xxx4_Elevator\board" -I"C:\Users\ferom\Documents\MCUXpressoIDE_11.1.0_3209\workspace\MKL25Z128xxx4_Elevator\source" -I"C:\Users\ferom\Documents\MCUXpressoIDE_11.1.0_3209\workspace\MKL25Z128xxx4_Elevator" -I"C:\Users\ferom\Documents\MCUXpressoIDE_11.1.0_3209\workspace\MKL25Z128xxx4_Elevator\freertos" -I"C:\Users\ferom\Documents\MCUXpressoIDE_11.1.0_3209\workspace\MKL25Z128xxx4_Elevator\drivers" -I"C:\Users\ferom\Documents\MCUXpressoIDE_11.1.0_3209\workspace\MKL25Z128xxx4_Elevator\CMSIS" -I"C:\Users\ferom\Documents\MCUXpressoIDE_11.1.0_3209\workspace\MKL25Z128xxx4_Elevator\utilities" -I"C:\Users\ferom\Documents\MCUXpressoIDE_11.1.0_3209\workspace\MKL25Z128xxx4_Elevator\CMSIS_driver" -I"C:\Users\ferom\Documents\MCUXpressoIDE_11.1.0_3209\workspace\MKL25Z128xxx4_Elevator\startup" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__NEWLIB__ -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


