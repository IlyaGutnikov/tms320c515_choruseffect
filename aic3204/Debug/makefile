################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := E:/ti_ccs5/ccsv5/tools/compiler/c5500_4.4.1

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"./main.obj" \
"./aic3204_tone_stereo_out.obj" \
"./aic3204_tone_headphone.obj" \
"./aic3204_test.obj" \
"./aic3204_loop_stereo_in2.obj" \
"./aic3204_loop_stereo_in1.obj" \
"./aic3204_loop_mic_in.obj" \
"../C5515.cmd" \
-l"evm5515bsl.lib" \
-l"rts55x_eh.lib" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: aic3204.out

# Tool invocations
aic3204.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: C5500 Linker'
	"E:/ti_ccs5/ccsv5/tools/compiler/c5500_4.4.1/bin/cl55" -g --diag_warning=225 --ptrdiff_size=32 --memory_model=large -z -m"aic3204.map" --warn_sections -i"E:/ti_ccs5/ccsv5/tools/compiler/c5500_4.4.1/lib" -i"E:/ti_ccs5/ccsv5/tools/compiler/c5500_4.4.1/include" -i"../../../lib" -i"E:/evm5515_v1/lib" --reread_libs --xml_link_info="aic3204_linkInfo.xml" --rom_model -o "aic3204.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C5500_EXECUTABLE_OUTPUTS__QUOTED) "aic3204.out"
	-$(RM) "aic3204_loop_mic_in.pp" "aic3204_loop_stereo_in1.pp" "aic3204_loop_stereo_in2.pp" "aic3204_test.pp" "aic3204_tone_headphone.pp" "aic3204_tone_stereo_out.pp" "main.pp" 
	-$(RM) "aic3204_loop_mic_in.obj" "aic3204_loop_stereo_in1.obj" "aic3204_loop_stereo_in2.obj" "aic3204_test.obj" "aic3204_tone_headphone.obj" "aic3204_tone_stereo_out.obj" "main.obj" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

