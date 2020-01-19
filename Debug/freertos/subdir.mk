################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../freertos/croutine.c \
../freertos/event_groups.c \
../freertos/fsl_tickless_lptmr.c \
../freertos/fsl_tickless_systick.c \
../freertos/heap_4.c \
../freertos/list.c \
../freertos/port.c \
../freertos/queue.c \
../freertos/tasks.c \
../freertos/timers.c 

OBJS += \
./freertos/croutine.o \
./freertos/event_groups.o \
./freertos/fsl_tickless_lptmr.o \
./freertos/fsl_tickless_systick.o \
./freertos/heap_4.o \
./freertos/list.o \
./freertos/port.o \
./freertos/queue.o \
./freertos/tasks.o \
./freertos/timers.o 

C_DEPS += \
./freertos/croutine.d \
./freertos/event_groups.d \
./freertos/fsl_tickless_lptmr.d \
./freertos/fsl_tickless_systick.d \
./freertos/heap_4.d \
./freertos/list.d \
./freertos/port.d \
./freertos/queue.d \
./freertos/tasks.d \
./freertos/timers.d 


# Each subdirectory must supply rules for building sources it contributes
freertos/%.o: ../freertos/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__NEWLIB__ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DSDK_OS_BAREMETAL -DFSL_RTOS_BM -DSDK_DEBUGCONSOLE=0 -DSDK_OS_FREE_RTOS -DFSL_RTOS_FREE_RTOS -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\ferom\Documents\MCUXpressoIDE_11.1.0_3209\workspace\MKL25Z128xxx4_Elevator\board" -I"C:\Users\ferom\Documents\MCUXpressoIDE_11.1.0_3209\workspace\MKL25Z128xxx4_Elevator\source" -I"C:\Users\ferom\Documents\MCUXpressoIDE_11.1.0_3209\workspace\MKL25Z128xxx4_Elevator" -I"C:\Users\ferom\Documents\MCUXpressoIDE_11.1.0_3209\workspace\MKL25Z128xxx4_Elevator\freertos" -I"C:\Users\ferom\Documents\MCUXpressoIDE_11.1.0_3209\workspace\MKL25Z128xxx4_Elevator\drivers" -I"C:\Users\ferom\Documents\MCUXpressoIDE_11.1.0_3209\workspace\MKL25Z128xxx4_Elevator\CMSIS" -I"C:\Users\ferom\Documents\MCUXpressoIDE_11.1.0_3209\workspace\MKL25Z128xxx4_Elevator\utilities" -I"C:\Users\ferom\Documents\MCUXpressoIDE_11.1.0_3209\workspace\MKL25Z128xxx4_Elevator\CMSIS_driver" -I"C:\Users\ferom\Documents\MCUXpressoIDE_11.1.0_3209\workspace\MKL25Z128xxx4_Elevator\startup" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__NEWLIB__ -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


