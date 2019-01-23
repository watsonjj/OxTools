#!/bin/bash

parallel_draw() {
	cd ~/Software/OxTools/build/bin
	output_dir=~/Software/outputs/simulation/
	output_name="simulation_$1_photon"
	output_path=${output_dir}${output_name}.ox.root
	./fit_pulse_spectrum -f $output_path -b fPulseArea -c ~/Software/outputs/simulation/simulation_1_photon.ox.root -T both
}
export -f parallel_draw
parallel_low() {
	cd ~/Software/OxTools/build/bin
	output_dir=~/Software/outputs/simulation/
	output_name="simulation_$1_photon"
	output_path=${output_dir}${output_name}.ox.root
	./fit_pulse_spectrum -f $output_path -b fPulseArea -T low -R calib
}
export -f parallel_low
parallel_high() {
	cd ~/Software/OxTools/build/bin
	output_dir=~/Software/outputs/simulation/
	output_name="simulation_$1_photon"
	output_path=${output_dir}${output_name}.ox.root
	./fit_pulse_spectrum -f $output_path -b fPulseArea -c ~/Software/outputs/simulation/simulation_1_photon.ox.root -T high -R calib
}
export -f parallel_high


#parallel --bar parallel_draw ::: 1 2 3 4 5 6 7 8 9 10 20 30 40 50 60 70 80 90 100
parallel --bar parallel_low ::: 1 2 3 4 5 6 7 8 9 10
parallel --bar parallel_high ::: 20 30 40 50 60 70 80 90 100