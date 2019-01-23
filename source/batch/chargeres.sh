#!/bin/bash

cd ~/Software/OxTools/build/bin


echo [RUNNING]
#./create_charge_resolution -f ~/Software/outputs/readhess/chargeres_*.ox.root -s Charge_Resolution-All > ~/Software/outputs/readhess/charge_resolution/scores.txt
#./create_charge_resolution -f ~/Software/outputs/readhess/chargeres_*.ox.root -s Charge_Resolution-All_40pe -m 40
#./create_charge_resolution -f ~/Software/outputs/readhess/chargeres_s3_*.ox.root -s Charge_Resolution-Nei_Scheme3
#./create_charge_resolution -f ~/Software/outputs/readhess/chargeres_s3_*.ox.root -s Charge_Resolution-Nei_Scheme3_40pe -m 40
#./create_charge_resolution -f ~/Software/outputs/readhess/chargeres_s4_*.ox.root -s Charge_Resolution-Nei_Scheme4
#./create_charge_resolution -f ~/Software/outputs/readhess/chargeres_s4_*.ox.root -s Charge_Resolution-Nei_Scheme4_40pe -m 40
#./create_charge_resolution -f ~/Software/outputs/readhess/chargeres_s5_*.ox.root -s Charge_Resolution-Nei_Scheme5
#./create_charge_resolution -f ~/Software/outputs/readhess/chargeres_s5_*.ox.root -s Charge_Resolution-Nei_Scheme5_40pe -m 40
#./create_charge_resolution -f ~/Software/outputs/readhess/chargeres_s9_*.ox.root -s Charge_Resolution-Nei_Scheme9
#./create_charge_resolution -f ~/Software/outputs/readhess/chargeres_s9_*.ox.root -s Charge_Resolution-Nei_Scheme9_40pe -m 40

#./create_charge_resolution -f ~/Software/outputs/readhess/chargeres_s5_r2_c2_rc4_m1.ox.root ~/Software/outputs/readhess/chargeres_s3_r1_c1_rc1_m0.ox.root -s Charge_Resolution-low_bestvsworst
#./create_charge_resolution -f ~/Software/outputs/readhess/chargeres_s5_r2_c2_rc4_m1.ox.root ~/Software/outputs/readhess/chargeres_s3_r1_c1_rc1_m0.ox.root -s Charge_Resolution-low_bestvsworst_40pe -m 40
#
#./create_charge_resolution -f ~/Software/outputs/readhess/chargeres_s5_r2_c2_rc4_m1.ox.root ~/Software/outputs/readhess/chargeres_s3_r2_c2_rc4_m1.ox.root -s Charge_Resolution-best_lowvshigh
#./create_charge_resolution -f ~/Software/outputs/readhess/chargeres_s5_r2_c2_rc4_m1.ox.root ~/Software/outputs/readhess/chargeres_s3_r2_c2_rc4_m1.ox.root -s Charge_Resolution-best_lowvshigh_40pe -m 40
#
#./create_charge_resolution -f ~/Software/outputs/readhess/chargeres_s3_r1_c1_rc1_m0.ox.root ~/Software/outputs/readhess/chargeres_s9_r2_c2_rc4_m1.ox.root -s Charge_Resolution-worst_lowvshigh
#./create_charge_resolution -f ~/Software/outputs/readhess/chargeres_s3_r1_c1_rc1_m0.ox.root ~/Software/outputs/readhess/chargeres_s9_r2_c2_rc4_m1.ox.root -s Charge_Resolution-worst_lowvshigh_40pe -m 40
#
#./create_charge_resolution -f ~/Software/outputs/readhess/chargeres_*_r2_c2_rc4_m1.ox.root -s Charge_Resolution-All_40pe_largeneighbours -m 40
#
#./create_charge_resolution -f ~/Software/outputs/readhess/chargeres_*.ox.root -s Charge_Resolution-All_20pe_lowscores -m 20
#
#./create_charge_resolution -f ~/Software/outputs/readhess/chargeres_s3_r2_c2_rc4_m1.ox.root ~/Software/outputs/readhess/chargeres_s5_r2_c2_rc4_m1.ox.root ~/Software/outputs/readhess/chargeres_s7_r2_c2_rc4_m1.ox.root -s Charge_Resolution-All_combined
#./create_charge_resolution -f ~/Software/outputs/readhess/chargeres_s3_r2_c2_rc4_m1.ox.root ~/Software/outputs/readhess/chargeres_s5_r2_c2_rc4_m1.ox.root ~/Software/outputs/readhess/chargeres_s7_r2_c2_rc4_m1.ox.root -s Charge_Resolution-All_combined_40pe -m 40
#
#./create_charge_resolution -f ~/Software/outputs/readhess/chargeres_s3_r2_c2_rc4_m1.ox.root ~/Software/outputs/readhess/chargeres_s5_r2_c2_rc4_m1.ox.root ~/Software/outputs/readhess/chargeres_s7_r2_c2_rc4_m1.ox.root ~/Software/outputs/readhess/chargeres_s7_r2_c2_rc4_m1_gt2.ox.root -s Charge_Resolution-All_combined_gt2_40pe -m 40

./create_charge_resolution -f ~/Software/outputs/readhess/meudon/chargeres_M_*.ox.root -s Charge_Resolution-All > ~/Software/outputs/readhess/charge_resolution/meudon/scores.txt