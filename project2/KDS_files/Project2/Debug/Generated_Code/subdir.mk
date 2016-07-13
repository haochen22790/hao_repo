################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Generated_Code/AS1.c \
../Generated_Code/Cpu.c \
../Generated_Code/PE_LDD.c \
../Generated_Code/RxBuf.c \
../Generated_Code/Vectors.c 

OBJS += \
./Generated_Code/AS1.o \
./Generated_Code/Cpu.o \
./Generated_Code/PE_LDD.o \
./Generated_Code/RxBuf.o \
./Generated_Code/Vectors.o 

C_DEPS += \
./Generated_Code/AS1.d \
./Generated_Code/Cpu.d \
./Generated_Code/PE_LDD.d \
./Generated_Code/RxBuf.d \
./Generated_Code/Vectors.d 


# Each subdirectory must supply rules for building sources it contributes
Generated_Code/%.o: ../Generated_Code/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"/home/hao/workspace.kds/Project2/Static_Code/PDD" -I"/home/hao/workspace.kds/Project2/Static_Code/IO_Map" -I"/home/hao/workspace.kds/Project2/Sources" -I"/home/hao/workspace.kds/Project2/Generated_Code" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


