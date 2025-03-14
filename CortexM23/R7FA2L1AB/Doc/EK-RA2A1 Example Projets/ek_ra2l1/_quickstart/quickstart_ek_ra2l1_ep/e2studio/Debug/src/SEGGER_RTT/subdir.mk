################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/SEGGER_RTT/SEGGER_RTT.c \
../src/SEGGER_RTT/SEGGER_RTT_printf.c 

C_DEPS += \
./src/SEGGER_RTT/SEGGER_RTT.d \
./src/SEGGER_RTT/SEGGER_RTT_printf.d 

OBJS += \
./src/SEGGER_RTT/SEGGER_RTT.o \
./src/SEGGER_RTT/SEGGER_RTT_printf.o 

SREC += \
quickstart_ek_ra2l1_ep.srec 

MAP += \
quickstart_ek_ra2l1_ep.map 


# Each subdirectory must supply rules for building sources it contributes
src/SEGGER_RTT/%.o: ../src/SEGGER_RTT/%.c
	$(file > $@.in,-mcpu=cortex-m23 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -g -D_RENESAS_RA_ -D_RA_CORE=CM23 -D_RA_ORDINAL=1 -I"D:/kod/git/project_arm/CortexM23/R7FA2L1AB/Doc/EK-RA2A1 Example Projets/ek_ra2l1/_quickstart/quickstart_ek_ra2l1_ep/e2studio/src" -I"D:/kod/git/project_arm/CortexM23/R7FA2L1AB/Doc/EK-RA2A1 Example Projets/ek_ra2l1/_quickstart/quickstart_ek_ra2l1_ep/e2studio/ra/fsp/inc" -I"D:/kod/git/project_arm/CortexM23/R7FA2L1AB/Doc/EK-RA2A1 Example Projets/ek_ra2l1/_quickstart/quickstart_ek_ra2l1_ep/e2studio/ra/fsp/inc/api" -I"D:/kod/git/project_arm/CortexM23/R7FA2L1AB/Doc/EK-RA2A1 Example Projets/ek_ra2l1/_quickstart/quickstart_ek_ra2l1_ep/e2studio/ra/fsp/inc/instances" -I"D:/kod/git/project_arm/CortexM23/R7FA2L1AB/Doc/EK-RA2A1 Example Projets/ek_ra2l1/_quickstart/quickstart_ek_ra2l1_ep/e2studio/ra_gen" -I"D:/kod/git/project_arm/CortexM23/R7FA2L1AB/Doc/EK-RA2A1 Example Projets/ek_ra2l1/_quickstart/quickstart_ek_ra2l1_ep/e2studio/ra_cfg/fsp_cfg/bsp" -I"D:/kod/git/project_arm/CortexM23/R7FA2L1AB/Doc/EK-RA2A1 Example Projets/ek_ra2l1/_quickstart/quickstart_ek_ra2l1_ep/e2studio/ra_cfg/fsp_cfg" -I"." -I"D:/kod/git/project_arm/CortexM23/R7FA2L1AB/Doc/EK-RA2A1 Example Projets/ek_ra2l1/_quickstart/quickstart_ek_ra2l1_ep/e2studio/ra/arm/CMSIS_6/CMSIS/Core/Include" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" -x c "$<")
	@echo Building file: $< && arm-none-eabi-gcc @"$@.in"

