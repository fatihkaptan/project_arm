################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ra_gen/common_data.c \
../ra_gen/hal_data.c \
../ra_gen/main.c \
../ra_gen/pin_data.c \
../ra_gen/vector_data.c 

C_DEPS += \
./ra_gen/common_data.d \
./ra_gen/hal_data.d \
./ra_gen/main.d \
./ra_gen/pin_data.d \
./ra_gen/vector_data.d 

OBJS += \
./ra_gen/common_data.o \
./ra_gen/hal_data.o \
./ra_gen/main.o \
./ra_gen/pin_data.o \
./ra_gen/vector_data.o 

SREC += \
quickstart_ek_ra2l1_ep.srec 

MAP += \
quickstart_ek_ra2l1_ep.map 


# Each subdirectory must supply rules for building sources it contributes
ra_gen/%.o: ../ra_gen/%.c
	$(file > $@.in,-mcpu=cortex-m23 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -g -D_RENESAS_RA_ -D_RA_CORE=CM23 -D_RA_ORDINAL=1 -I"D:/kod/git/project_arm/CortexM23/R7FA2L1AB/Doc/EK-RA2A1 Example Projets/ek_ra2l1/_quickstart/quickstart_ek_ra2l1_ep/e2studio/src" -I"D:/kod/git/project_arm/CortexM23/R7FA2L1AB/Doc/EK-RA2A1 Example Projets/ek_ra2l1/_quickstart/quickstart_ek_ra2l1_ep/e2studio/ra/fsp/inc" -I"D:/kod/git/project_arm/CortexM23/R7FA2L1AB/Doc/EK-RA2A1 Example Projets/ek_ra2l1/_quickstart/quickstart_ek_ra2l1_ep/e2studio/ra/fsp/inc/api" -I"D:/kod/git/project_arm/CortexM23/R7FA2L1AB/Doc/EK-RA2A1 Example Projets/ek_ra2l1/_quickstart/quickstart_ek_ra2l1_ep/e2studio/ra/fsp/inc/instances" -I"D:/kod/git/project_arm/CortexM23/R7FA2L1AB/Doc/EK-RA2A1 Example Projets/ek_ra2l1/_quickstart/quickstart_ek_ra2l1_ep/e2studio/ra_gen" -I"D:/kod/git/project_arm/CortexM23/R7FA2L1AB/Doc/EK-RA2A1 Example Projets/ek_ra2l1/_quickstart/quickstart_ek_ra2l1_ep/e2studio/ra_cfg/fsp_cfg/bsp" -I"D:/kod/git/project_arm/CortexM23/R7FA2L1AB/Doc/EK-RA2A1 Example Projets/ek_ra2l1/_quickstart/quickstart_ek_ra2l1_ep/e2studio/ra_cfg/fsp_cfg" -I"." -I"D:/kod/git/project_arm/CortexM23/R7FA2L1AB/Doc/EK-RA2A1 Example Projets/ek_ra2l1/_quickstart/quickstart_ek_ra2l1_ep/e2studio/ra/arm/CMSIS_6/CMSIS/Core/Include" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" -x c "$<")
	@echo Building file: $< && arm-none-eabi-gcc @"$@.in"

