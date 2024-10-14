################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/RadioFunctions.c \
../Core/Src/clock.c \
../Core/Src/gpio.c \
../Core/Src/main.c \
../Core/Src/nrf24.c \
../Core/Src/spi.c \
../Core/Src/stm32l4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32l4xx.c \
../Core/Src/usart.c 

OBJS += \
./Core/Src/RadioFunctions.o \
./Core/Src/clock.o \
./Core/Src/gpio.o \
./Core/Src/main.o \
./Core/Src/nrf24.o \
./Core/Src/spi.o \
./Core/Src/stm32l4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32l4xx.o \
./Core/Src/usart.o 

C_DEPS += \
./Core/Src/RadioFunctions.d \
./Core/Src/clock.d \
./Core/Src/gpio.d \
./Core/Src/main.d \
./Core/Src/nrf24.d \
./Core/Src/spi.d \
./Core/Src/stm32l4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32l4xx.d \
./Core/Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/RadioFunctions.o: ../Core/Src/RadioFunctions.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-DHSE_VALUE=8000000' '-DMSI_VALUE=4000000' '-DLSI_VALUE=32000' '-DHSE_STARTUP_TIMEOUT=100' '-DHSI_VALUE=16000000' '-DLSE_STARTUP_TIMEOUT=5000' -DDEBUG '-DLSE_VALUE=32768' '-DDATA_CACHE_ENABLE=1' '-DVDD_VALUE=3300' '-DINSTRUCTION_CACHE_ENABLE=1' '-DEXTERNALSAI2_CLOCK_VALUE=2097000' -DUSE_FULL_LL_DRIVER -DSTM32L476xx '-DEXTERNALSAI1_CLOCK_VALUE=2097000' '-DPREFETCH_ENABLE=0' -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/RadioFunctions.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/clock.o: ../Core/Src/clock.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-DHSE_VALUE=8000000' '-DMSI_VALUE=4000000' '-DLSI_VALUE=32000' '-DHSE_STARTUP_TIMEOUT=100' '-DHSI_VALUE=16000000' '-DLSE_STARTUP_TIMEOUT=5000' -DDEBUG '-DLSE_VALUE=32768' '-DDATA_CACHE_ENABLE=1' '-DVDD_VALUE=3300' '-DINSTRUCTION_CACHE_ENABLE=1' '-DEXTERNALSAI2_CLOCK_VALUE=2097000' -DUSE_FULL_LL_DRIVER -DSTM32L476xx '-DEXTERNALSAI1_CLOCK_VALUE=2097000' '-DPREFETCH_ENABLE=0' -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/clock.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/gpio.o: ../Core/Src/gpio.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-DHSE_VALUE=8000000' '-DMSI_VALUE=4000000' '-DLSI_VALUE=32000' '-DHSE_STARTUP_TIMEOUT=100' '-DHSI_VALUE=16000000' '-DLSE_STARTUP_TIMEOUT=5000' -DDEBUG '-DLSE_VALUE=32768' '-DDATA_CACHE_ENABLE=1' '-DVDD_VALUE=3300' '-DINSTRUCTION_CACHE_ENABLE=1' '-DEXTERNALSAI2_CLOCK_VALUE=2097000' -DUSE_FULL_LL_DRIVER -DSTM32L476xx '-DEXTERNALSAI1_CLOCK_VALUE=2097000' '-DPREFETCH_ENABLE=0' -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/gpio.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/main.o: ../Core/Src/main.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-DHSE_VALUE=8000000' '-DMSI_VALUE=4000000' '-DLSI_VALUE=32000' '-DHSE_STARTUP_TIMEOUT=100' '-DHSI_VALUE=16000000' '-DLSE_STARTUP_TIMEOUT=5000' -DDEBUG '-DLSE_VALUE=32768' '-DDATA_CACHE_ENABLE=1' '-DVDD_VALUE=3300' '-DINSTRUCTION_CACHE_ENABLE=1' '-DEXTERNALSAI2_CLOCK_VALUE=2097000' -DUSE_FULL_LL_DRIVER -DSTM32L476xx '-DEXTERNALSAI1_CLOCK_VALUE=2097000' '-DPREFETCH_ENABLE=0' -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/main.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/nrf24.o: ../Core/Src/nrf24.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-DHSE_VALUE=8000000' '-DMSI_VALUE=4000000' '-DLSI_VALUE=32000' '-DHSE_STARTUP_TIMEOUT=100' '-DHSI_VALUE=16000000' '-DLSE_STARTUP_TIMEOUT=5000' -DDEBUG '-DLSE_VALUE=32768' '-DDATA_CACHE_ENABLE=1' '-DVDD_VALUE=3300' '-DINSTRUCTION_CACHE_ENABLE=1' '-DEXTERNALSAI2_CLOCK_VALUE=2097000' -DUSE_FULL_LL_DRIVER -DSTM32L476xx '-DEXTERNALSAI1_CLOCK_VALUE=2097000' '-DPREFETCH_ENABLE=0' -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/nrf24.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/spi.o: ../Core/Src/spi.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-DHSE_VALUE=8000000' '-DMSI_VALUE=4000000' '-DLSI_VALUE=32000' '-DHSE_STARTUP_TIMEOUT=100' '-DHSI_VALUE=16000000' '-DLSE_STARTUP_TIMEOUT=5000' -DDEBUG '-DLSE_VALUE=32768' '-DDATA_CACHE_ENABLE=1' '-DVDD_VALUE=3300' '-DINSTRUCTION_CACHE_ENABLE=1' '-DEXTERNALSAI2_CLOCK_VALUE=2097000' -DUSE_FULL_LL_DRIVER -DSTM32L476xx '-DEXTERNALSAI1_CLOCK_VALUE=2097000' '-DPREFETCH_ENABLE=0' -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/spi.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/stm32l4xx_it.o: ../Core/Src/stm32l4xx_it.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-DHSE_VALUE=8000000' '-DMSI_VALUE=4000000' '-DLSI_VALUE=32000' '-DHSE_STARTUP_TIMEOUT=100' '-DHSI_VALUE=16000000' '-DLSE_STARTUP_TIMEOUT=5000' -DDEBUG '-DLSE_VALUE=32768' '-DDATA_CACHE_ENABLE=1' '-DVDD_VALUE=3300' '-DINSTRUCTION_CACHE_ENABLE=1' '-DEXTERNALSAI2_CLOCK_VALUE=2097000' -DUSE_FULL_LL_DRIVER -DSTM32L476xx '-DEXTERNALSAI1_CLOCK_VALUE=2097000' '-DPREFETCH_ENABLE=0' -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/stm32l4xx_it.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/syscalls.o: ../Core/Src/syscalls.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-DHSE_VALUE=8000000' '-DMSI_VALUE=4000000' '-DLSI_VALUE=32000' '-DHSE_STARTUP_TIMEOUT=100' '-DHSI_VALUE=16000000' '-DLSE_STARTUP_TIMEOUT=5000' -DDEBUG '-DLSE_VALUE=32768' '-DDATA_CACHE_ENABLE=1' '-DVDD_VALUE=3300' '-DINSTRUCTION_CACHE_ENABLE=1' '-DEXTERNALSAI2_CLOCK_VALUE=2097000' -DUSE_FULL_LL_DRIVER -DSTM32L476xx '-DEXTERNALSAI1_CLOCK_VALUE=2097000' '-DPREFETCH_ENABLE=0' -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/syscalls.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/sysmem.o: ../Core/Src/sysmem.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-DHSE_VALUE=8000000' '-DMSI_VALUE=4000000' '-DLSI_VALUE=32000' '-DHSE_STARTUP_TIMEOUT=100' '-DHSI_VALUE=16000000' '-DLSE_STARTUP_TIMEOUT=5000' -DDEBUG '-DLSE_VALUE=32768' '-DDATA_CACHE_ENABLE=1' '-DVDD_VALUE=3300' '-DINSTRUCTION_CACHE_ENABLE=1' '-DEXTERNALSAI2_CLOCK_VALUE=2097000' -DUSE_FULL_LL_DRIVER -DSTM32L476xx '-DEXTERNALSAI1_CLOCK_VALUE=2097000' '-DPREFETCH_ENABLE=0' -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/sysmem.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/system_stm32l4xx.o: ../Core/Src/system_stm32l4xx.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-DHSE_VALUE=8000000' '-DMSI_VALUE=4000000' '-DLSI_VALUE=32000' '-DHSE_STARTUP_TIMEOUT=100' '-DHSI_VALUE=16000000' '-DLSE_STARTUP_TIMEOUT=5000' -DDEBUG '-DLSE_VALUE=32768' '-DDATA_CACHE_ENABLE=1' '-DVDD_VALUE=3300' '-DINSTRUCTION_CACHE_ENABLE=1' '-DEXTERNALSAI2_CLOCK_VALUE=2097000' -DUSE_FULL_LL_DRIVER -DSTM32L476xx '-DEXTERNALSAI1_CLOCK_VALUE=2097000' '-DPREFETCH_ENABLE=0' -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/system_stm32l4xx.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/usart.o: ../Core/Src/usart.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-DHSE_VALUE=8000000' '-DMSI_VALUE=4000000' '-DLSI_VALUE=32000' '-DHSE_STARTUP_TIMEOUT=100' '-DHSI_VALUE=16000000' '-DLSE_STARTUP_TIMEOUT=5000' -DDEBUG '-DLSE_VALUE=32768' '-DDATA_CACHE_ENABLE=1' '-DVDD_VALUE=3300' '-DINSTRUCTION_CACHE_ENABLE=1' '-DEXTERNALSAI2_CLOCK_VALUE=2097000' -DUSE_FULL_LL_DRIVER -DSTM32L476xx '-DEXTERNALSAI1_CLOCK_VALUE=2097000' '-DPREFETCH_ENABLE=0' -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/usart.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

