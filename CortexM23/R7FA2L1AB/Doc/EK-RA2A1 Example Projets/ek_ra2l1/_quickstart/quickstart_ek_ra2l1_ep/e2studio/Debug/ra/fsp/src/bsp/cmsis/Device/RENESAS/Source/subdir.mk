################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ra/fsp/src/bsp/cmsis/Device/RENESAS/Source/startup.c \
../ra/fsp/src/bsp/cmsis/Device/RENESAS/Source/system.c 

C_DEPS += \
./ra/fsp/src/bsp/cmsis/Device/RENESAS/Source/startup.d \
./ra/fsp/src/bsp/cmsis/Device/RENESAS/Source/system.d 

OBJS += \
./ra/fsp/src/bsp/cmsis/Device/RENESAS/Source/startup.o \
./ra/fsp/src/bsp/cmsis/Device/RENESAS/Source/system.o 

SREC += \
quickstart_ek_ra2l1_ep.srec 

MAP += \
quickstart_ek_ra2l1_ep.map 


# Each subdirectory must supply rules for building sources it contributes
ra/fsp/src/bsp/cmsis/Device/RENESAS/Source/%.o: ../ra/fsp/src/bsp/cmsis/Device/RENESAS/Source/%.c
	$(file > $@.in,-mcpu=cortex-m23 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -g -D_RENESAS_RA_ -D_RA_CORE=CM23 -D_RA_ORDINAL=1 -I"D:/kod/git/project_arm/CortexM23/R7FA2L1AB/Doc/EK-RA2A1 Example Projets/ek_ra2l1/_quickstart/quickstart_ek_ra2l1_ep/e2studio/src" -I"D:/kod/git/project_arm/CortexM23/R7FA2L1AB/Doc/EK-RA2A1 Example Projets/ek_ra2l1/_quickstart/quickstart_ek_ra2l1_ep/e2studio/ra/fsp/inc" -I"D:/kod/git/project_arm/CortexM23/R7FA2L1AB/Doc/EK-RA2A1 Example Projets/ek_ra2l1/_quickstart/quickstart_ek_ra2l1_ep/e2studio/ra/fsp/inc/api" -I"D:/kod/git/project_arm/CortexM23/R7FA2L1AB/Doc/EK-RA2A1 Example Projets/ek_ra2l1/_quickstart/quickstart_ek_ra2l1_ep/e2studio/ra/fsp/inc/instances" -I"D:/kod/git/project_arm/CortexM23/R7FA2L1AB/Doc/EK-RA2A1 Example Projets/ek_ra2l1/_quickstart/quickstart_ek_ra2l1_ep/e2studio/ra_gen" -I"D:/kod/git/project_arm/CortexM23/R7FA2L1AB/Doc/EK-RA2A1 Example Projets/ek_ra2l1/_quickstart/quickstart_ek_ra2l1_ep/e2studio/ra_cfg/fsp_cfg/bsp" -I"D:/kod/git/project_arm/CortexM23/R7FA2L1AB/Doc/EK-RA2A1 Example Projets/ek_ra2l1/_quickstart/quickstart_ek_ra2l1_ep/e2studio/ra_cfg/fsp_cfg" -I"." -I"D:/kod/git/project_arm/CortexM23/R7FA2L1AB/Doc/EK-RA2A1 Example Projets/ek_ra2l1/_quickstart/quickstart_ek_ra2l1_ep/e2studio/ra/arm/CMSIS_6/CMSIS/Core/Include" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" -x c "$<")
	@echo Building file: $< && arm-none-eabi-gcc @"$@.in"

