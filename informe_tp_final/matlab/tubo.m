g='./datos/tubo-ga/ga_run_';
k='./datos/tubo-kh/krill_run_';
p='./datos/tubo-pso/pso_run_';

NUM_CORRIDAS = 10;
NUM_IT = 1000;

PSO=zeros(NUM_CORRIDAS, NUM_IT);
GA=zeros(NUM_CORRIDAS, NUM_IT);
KH=zeros(NUM_CORRIDAS, NUM_IT);

%M=zeros(10,1000);
%Msin=zeros(100,1000);

for i=1:NUM_CORRIDAS

    part = load(strcat(p,num2str(i),'.dat'));
    part = part(1:length(part)-1);
    PSO(i,:) = part;

    %tienen 1002 no sé por qué ¬¬
    ga = -1*load(strcat(g,num2str(i),'.dat'));
    ga = ga(2:length(ga)-1);
    GA(i,:) = ga;

    kh = -1*load(strcat(k,num2str(i),'.dat'));
    kh = kh(1:length(kh)-1);
    KH(i,:) = kh;

end

%mínimos:
mejor_pso = min(PSO(:, length(PSO(1,:))))
mejor_ga = min(GA(:, length(GA(1,:))))
mejor_kh = min(KH(:, length(KH(1,:))))

%promedios:
prom_pso = mean(PSO(:, length(PSO(1,:))))
prom_ga = mean(GA(:, length(GA(1,:))))
prom_kh = mean(KH(:, length(KH(1,:))))
