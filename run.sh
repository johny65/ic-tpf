for i in $(seq 1 1 100)
do
	#./pso.bin;
	#mv "fmejor.dat" "pso_run_$i.dat";
	
	#./GA.bin;
	#mv "fmejor.dat" "ga_run_$i.dat";
	
	./krill.bin;
	mv "krill_run.dat" "krill_run_$i.dat";

	#./red-ga.bin;
	#mv "fmejor.dat" "red_ga_run_$i.dat";
	
	#./RED-PSO.bin;
	#mv "fmejor" "red_pso_run_$i.dat";
done
