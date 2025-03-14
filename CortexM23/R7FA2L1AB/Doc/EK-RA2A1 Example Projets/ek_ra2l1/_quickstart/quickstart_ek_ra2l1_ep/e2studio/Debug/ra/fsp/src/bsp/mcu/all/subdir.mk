################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ra/fsp/src/bsp/mcu/all/bsp_clocks.c \
../ra/fsp/src/bsp/mcu/all/bsp_common.c \
../ra/fsp/src/bsp/mcu/all/bsp_delay.c \
../ra/fsp/src/bsp/mcu/all/bsp_group_irq.c \
../ra/fsp/src/bsp/mcu/all/bsp_guard.c \
../ra/fsp/src/bsp/mcu/all/bsp_io.c \
../ra/fsp/src/bsp/mcu/all/bsp_irq.c \
../ra/fsp/src/bsp/mcu/all/bsp_macl.c \
../ra/fsp/src/bsp/mcu/all/bsp_register_protection.c \
../ra/fsp/src/bsp/mcu/all/bsp_rom_registers.c \
../ra/fsp/src/bsp/mcu/all/bsp_sbrk.c \
../ra/fsp/src/bsp/mcu/all/bsp_sdram.c \
../ra/fsp/src/bsp/mcu/all/bsp_security.c 

C_DEPS += \
./ra/fsp/src/bsp/mcu/all/bsp_clocks.d \
./ra/fsp/src/bsp/mcu/all/bsp_common.d \
./ra/fsp/src/bsp/mcu/all/bsp_delay.d \
./ra/fsp/src/bsp/mcu/all/bsp_group_irq.d \
./ra/fsp/src/bsp/mcu/all/bsp_guard.d \
./ra/fsp/src/bsp/mcu/all/bsp_io.d \
./ra/fsp/src/bsp/mcu/all/bsp_irq.d \
./ra/fsp/src/bsp/mcu/all/bsp_macl.d \
./ra/fsp/src/bsp/mcu/all/bsp_register_protection.d \
./ra/fsp/src/bsp/mcu/all/bsp_rom_registers.d \
./ra/fsp/src/bsp/mcu/all/bsp_sbrk.d \
./ra/fsp/src/bsp/mcu/all/bsp_sdram.d \
./ra/fsp/src/bsp/mcu/all/bsp_security.d 

OBJS += \
./ra/fsp/src/bsp/mcu/all/bsp_clocks.o \
./ra/fsp/src/bsp/mcu/all/bsp_common.o \
./ra/fsp/src/bsp/mcu/all/bsp_delay.o \
./ra/fsp/src/bsp/mcu/all/bsp_group_irq.o \
./ra/fsp/src/bsp/mcu/all/bsp_guard.o \
./ra/fsp/src/bsp/mcu/all/bsp_io.o \
./ra/fsp/src/bsp/mcu/all/bsp_irq.o \
./ra/fsp/src/bsp/mcu/all/bsp_macl.o \
./ra/fsp/src/bsp/mcu/all/bsp_register_protection.o \
./ra/fsp/src/bsp/mcu/all/bsp_rom_registers.o \
./ra/fsp/src/bsp/mcu/all/bsp_sbrk.o \
./ra/fsp/src/bsp/mcu/all/bsp_sdram.o \
./ra/fsp/src/bsp/mcu/all/bsp_security.o 

SREC += \
quickstart_ek_ra2l1_ep.srec 

MAP += \
quickstart_ek_ra2l1_ep.map 


# Each subdirectory must supply rules for building sources it contributes
ra/fsp/src/bsp/mcu/all/%.o: ../ra/fsp/src/bsp/mcu/all/%.c
	$(file > $@.in,-mcpu=cortex-m23 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -g -D_RENESAS_RA_ -D_RA_CORE=CM23 -D_RA_ORDINAL=1 -I"D:/kod/git/project_arm/CortexM23/R7FA2L1AB/Doc/EK-RA2A1 Example Projets/ek_ra2l1/_quickstart/quickstart_ek_ra2l1_ep/e2studio/src" -I"D:/kod/git/project_arm/CortexM23/R7FA2L1AB/Doc/EK-RA2A1 Example Projets/ek_ra2l1/_quickstart/quickstart_ek_ra2l1_ep/e2studio/ra/fsp/inc" -I"D:/kod/git/project_arm/CortexM23/R7FA2L1AB/Doc/EK-RA2A1 Example Projets/ek_ra2l1/_quickstart/quickstart_ek_ra2l1_ep/e2studio/ra/fsp/inc/api" -I"D:/kod/git/project_arm/CortexM23/R7FA2L1AB/Doc/EK-RA2A1 Example Projets/ek_ra2l1/_quickstart/quickstart_ek_ra2l1_ep/e2studio/ra/fsp/inc/instances" -I"D:/kod/git/project_arm/CortexM23/R7FA2L1AB/Doc/EK-RA2A1 Example Projets/ek_ra2l1/_quickstart/quickstart_ek_ra2l1_ep/e2studio/ra_gen" -I"D:/kod/git/project_arm/CortexM23/R7FA2L1AB/Doc/EK-RA2A1 Example Projets/ek_ra2l1/_quickstart/quickstart_ek_ra2l1_ep/e2studio/ra_cfg/fsp_cfg/bsp" -I"D:/kod/git/project_arm/CortexM23/R7FA2L1AB/Doc/EK-RA2A1 Example Projets/ek_ra2l1/_quickstart/quickstart_ek_ra2l1_ep/e2studio/ra_cfg/fsp_cfg" -I"." -I"D:/kod/git/project_arm/CortexM23/R7FA2L1AB/Doc/EK-RA2A1 Example Projets/ek_ra2l1/_quickstart/quickstart_ek_ra2l1_ep/e2studio/ra/arm/CMSIS_6/CMSIS/Core/Include" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" -x c "$<")
	@echo Building file: $< && arm-none-eabi-gcc @"$@.in"

