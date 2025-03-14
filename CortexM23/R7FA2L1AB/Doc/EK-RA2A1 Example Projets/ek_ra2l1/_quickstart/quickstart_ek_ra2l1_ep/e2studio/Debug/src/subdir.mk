################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/common_init.c \
../src/hal_entry.c \
../src/menu_kis.c \
../src/menu_main.c \
../src/menu_ns.c \
../src/r_console_if.c 

C_DEPS += \
./src/common_init.d \
./src/hal_entry.d \
./src/menu_kis.d \
./src/menu_main.d \
./src/menu_ns.d \
./src/r_console_if.d 

OBJS += \
./src/common_init.o \
./src/hal_entry.o \
./src/menu_kis.o \
./src/menu_main.o \
./src/menu_ns.o \
./src/r_console_if.o 

SREC += \
quickstart_ek_ra2l1_ep.srec 

MAP += \
quickstart_ek_ra2l1_ep.map 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	$(file > $@.in,-mcpu=cortex-m23 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -g -D_RENESAS_RA_ -D_RA_CORE=CM23 -D_RA_ORDINAL=1 -I"D:/kod/git/project_arm/CortexM23/R7FA2L1AB/Doc/EK-RA2A1 Example Projets/ek_ra2l1/_quickstart/quickstart_ek_ra2l1_ep/e2studio/src" -I"D:/kod/git/project_arm/CortexM23/R7FA2L1AB/Doc/EK-RA2A1 Example Projets/ek_ra2l1/_quickstart/quickstart_ek_ra2l1_ep/e2studio/ra/fsp/inc" -I"D:/kod/git/project_arm/CortexM23/R7FA2L1AB/Doc/EK-RA2A1 Example Projets/ek_ra2l1/_quickstart/quickstart_ek_ra2l1_ep/e2studio/ra/fsp/inc/api" -I"D:/kod/git/project_arm/CortexM23/R7FA2L1AB/Doc/EK-RA2A1 Example Projets/ek_ra2l1/_quickstart/quickstart_ek_ra2l1_ep/e2studio/ra/fsp/inc/instances" -I"D:/kod/git/project_arm/CortexM23/R7FA2L1AB/Doc/EK-RA2A1 Example Projets/ek_ra2l1/_quickstart/quickstart_ek_ra2l1_ep/e2studio/ra_gen" -I"D:/kod/git/project_arm/CortexM23/R7FA2L1AB/Doc/EK-RA2A1 Example Projets/ek_ra2l1/_quickstart/quickstart_ek_ra2l1_ep/e2studio/ra_cfg/fsp_cfg/bsp" -I"D:/kod/git/project_arm/CortexM23/R7FA2L1AB/Doc/EK-RA2A1 Example Projets/ek_ra2l1/_quickstart/quickstart_ek_ra2l1_ep/e2studio/ra_cfg/fsp_cfg" -I"." -I"D:/kod/git/project_arm/CortexM23/R7FA2L1AB/Doc/EK-RA2A1 Example Projets/ek_ra2l1/_quickstart/quickstart_ek_ra2l1_ep/e2studio/ra/arm/CMSIS_6/CMSIS/Core/Include" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" -x c "$<")
	@echo Building file: $< && arm-none-eabi-gcc @"$@.in"

