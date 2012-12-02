for i in $(seq 9 1 10)
do
	../Debug/RED-KRILL.bin;
	mv "krill_run.dat" "krill-red-pesos_$i.dat";

done
