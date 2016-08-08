################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/CB_test.c \
../Sources/DMA_memory.c \
../Sources/Events.c \
../Sources/LED.c \
../Sources/SPI.c \
../Sources/circBuf.c \
../Sources/log.c \
../Sources/main.c \
../Sources/memory.c \
../Sources/nRF24L01.c \
../Sources/timer.c \
../Sources/uart.c 

OBJS += \
./Sources/CB_test.o \
./Sources/DMA_memory.o \
./Sources/Events.o \
./Sources/LED.o \
./Sources/SPI.o \
./Sources/circBuf.o \
./Sources/log.o \
./Sources/main.o \
./Sources/memory.o \
./Sources/nRF24L01.o \
./Sources/timer.o \
./Sources/uart.o 

C_DEPS += \
./Sources/CB_test.d \
./Sources/DMA_memory.d \
./Sources/Events.d \
./Sources/LED.d \
./Sources/SPI.d \
./Sources/circBuf.d \
./Sources/log.d \
./Sources/main.d \
./Sources/memory.d \
./Sources/nRF24L01.d \
./Sources/timer.d \
./Sources/uart.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/%.o: ../Sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"C:/Users/hchen2/Documents/KineticDesignStudioDocs/Project3/Static_Code/PDD" -I"C:/Users/hchen2/Documents/KineticDesignStudioDocs/Project3/Static_Code/IO_Map" -I"C:/Users/hchen2/Documents/KineticDesignStudioDocs/Project3/Sources" -I"C:/Users/hchen2/Documents/KineticDesignStudioDocs/Project3/Generated_Code" -std=c99 -O0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/main.o: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"C:/Users/hchen2/Documents/KineticDesignStudioDocs/Project3/Static_Code/PDD" -I"C:/Users/hchen2/Documents/KineticDesignStudioDocs/Project3/Static_Code/IO_Map" -I"C:/Users/hchen2/Documents/KineticDesignStudioDocs/Project3/Sources" -I"C:/Users/hchen2/Documents/KineticDesignStudioDocs/Project3/Generated_Code" -I/home/hao/hao_repo/project1/cross_compile -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"Sources/main.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


