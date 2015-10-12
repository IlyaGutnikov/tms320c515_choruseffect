################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
led_test.obj: ../led_test.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"E:/ti_ccs5/ccsv5/tools/compiler/c5500_4.4.1/bin/cl55" -g --include_path="E:/ti_ccs5/ccsv5/tools/compiler/c5500_4.4.1/include" --include_path="../../../include" --diag_warning=225 --ptrdiff_size=32 --memory_model=large --preproc_with_compile --preproc_dependency="led_test.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"E:/ti_ccs5/ccsv5/tools/compiler/c5500_4.4.1/bin/cl55" -g --include_path="E:/ti_ccs5/ccsv5/tools/compiler/c5500_4.4.1/include" --include_path="../../../include" --diag_warning=225 --ptrdiff_size=32 --memory_model=large --preproc_with_compile --preproc_dependency="main.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


