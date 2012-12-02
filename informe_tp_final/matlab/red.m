g='./datos/red-ga/red_ga_run_';
k='./datos/red-kh/krill-red-pesos_';
p='./datos/red-pso/red_pso_run_';

NUM_CORRIDAS = 10;
NUM_IT = 10;

PSO=zeros(NUM_CORRIDAS, NUM_IT);
GA=zeros(NUM_CORRIDAS, NUM_IT);
KH=zeros(NUM_CORRIDAS, NUM_IT);

%M=zeros(10,1000);
%Msin=zeros(100,1000);

for i=1:NUM_CORRIDAS

    part = load(strcat(p,num2str(i),'.dat'));
    part = part(1:length(part));
    PSO(i,:) = part;

    ga = load(strcat(g,num2str(i),'.dat'));
    ga = ga(1:length(ga));
    GA(i,:) = ga;

    kh = load(strcat(k,num2str(i),'.dat'));
    kh = kh(1:length(kh));
    KH(i,:) = kh;

end

%mínimos:
mejor_pso = max(PSO(:, length(PSO(1,:))))
mejor_ga = max(GA(:, length(GA(1,:))))
mejor_kh = max(KH(:, length(KH(1,:))))

%promedios:
prom_pso = mean(PSO(:, length(PSO(1,:))))
prom_ga = mean(GA(:, length(GA(1,:))))
prom_kh = mean(KH(:, length(KH(1,:))))
