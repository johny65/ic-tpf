clear all;
clc;
% 
% s='/media/Facultad/Inteligencia Computacional/tpf-ic/RED-KRILL/datos/krill-red-pesos_';
% g='./datos/red-ga/red_ga_run_';
% p='./datos/red-pso/red_pso_run_';
% 
% 
% M=zeros(10,10);
% GA=zeros(10,10);
% PSO=zeros(10,10);
% for i=1:10
%      M(i,:)=load(strcat(s,num2str(i),'.dat')); 
%      GA(i,:)=load(strcat(g,num2str(i),'.dat'));
%      PSO(i,:)=load(strcat(p,num2str(i),'.dat'))
% end
% 
% %Busco el mejor indice 
% mejor_k=1
% mejor_g=1;
% mejor_p=1;
% for i=1:10
%     if(M(i,10)>M(mejor_k,10))
%         mejor_k=i;
%     end
%     
%     if(GA(i,10)>GA(mejor_g,10))
%         mejor_g=i;
%     end
%     
%     if(PSO(i,10)>PSO(mejor_p,10))
%         mejor_p=i;
%     end
% end
% 
% plot(M(mejor_k,:));
% hold all;
% plot(GA(mejor_g,:));
% hold all;
% plot(PSO(mejor_p,:));
% 
% legend('KH','GA','PSO');
% xlabel('iteraciones');
% ylabel('% de acierto');
% 
% figure(2);

kacm='./datos/krill-ackley-cm/krill_run_';
kas='./datos/krill-ackley-sin/krill_run_';
g='./datos/ga-ackley/ga_run_';
p='./datos/pso-ackley/pso_run_';

M=zeros(100,1000);
Msin=zeros(100,1000);
GA=zeros(100,1000);
PSO=zeros(100,1000);
pkcm=0; pksm=0; pgen=0; ppso=0;
nkcm=0; nksm=0; ngen=0; npso=0;
for i=1:100
     kcm=-1*load(strcat(kacm,num2str(i),'.dat')); pkcm=pkcm+kcm(length(kcm));  if(length(kcm)<1000) kcm=[kcm; nan*zeros(1000-length(kcm),1)]; end;
     ksm=-1*load(strcat(kas,num2str(i),'.dat'));  pksm=pksm+ksm(length(ksm)); nksm=nksm+length(ksm); if(length(ksm)<1000) ksm=[ksm; nan*zeros(1000-length(ksm),1)]; end;
     gen=-1*load(strcat(g,num2str(i),'.dat'));    pgen=pgen+gen(length(gen)); ngen=ngen+length(gen); if(length(gen)<1000) gen=[gen; nan*zeros(1000-length(gen),1)]; end;
     part=load(strcat(p,num2str(i),'.dat'));   ppso=ppso+part(length(part)); npso=npso+length(part); if(length(part)<1000) part=[part; nan*zeros(1000-length(part),1)]; end;
     M(i,:)=kcm;
     Msin(i,:)=ksm;
     GA(i,:)=gen;
     PSO(i,:)=part;
end


%Promedios
pkcm=pkcm/100;
pksm=pksm/100;
pgen=pgen/100;
ppso=ppso/100;


[vkcm,ikcm]=min(M); [v2,i2]=min(vkcm); mckcm=ikcm(i2); i2
[vksm,iksm]=min(Msin); [v2,i2]=min(vksm); mcksm=iksm(i2); i2
[vgen,igen]=min(GA); [v2,i2]=min(vgen); mcgen=igen(i2);  i2
[vpso,ipso]=min(PSO); [v2,i2]=min(vpso); mcpso=ipso(i2); i2

disp('Minimo de krill con genetico');
min(M(mckcm,:))
disp('Minimo de krill sin genetico');
min(Msin(mcksm,:))
disp('Minimo de Genetico');
min(GA(mcgen,:))
disp('Minimo de PSO');
min(PSO(mcpso,:))

plot(M(mckcm,:),'r');
hold all;
plot(Msin(mcksm,:),'g');
hold all;
plot(GA(mcgen,:),'b');
hold all;
plot(PSO(mcpso,:),'k');
legend('KH-cg','KH-sg','GA','PSO');



% 
% disp('MAx de krill con genetico');
% max(M(mckcm,:))
% disp('Max de krill sin genetico');
% max(Msin(mcksm,:))
% disp('Ma de Genetico');
% max(GA(mcgen,:))
% disp('Minimo de PSO');
% max(PSO(mcpso,:))

%Saco la mejor iteracion de cada uno
% mejor_kcm=1; valor_kcm=1000;
% mejor_ksm=1; valor_ksm=1000;
% mejor_gen=1; valor_gen=1000;
% mejor_pso=1; valor_pso=1000;
% for i=1:100
%     if(M(i,find(M(i,:),1,'last'))<valor_kcm)
%         mejor_kcm=i;
%         valor_kcm=M(i,find(M(i,:),1,'last'));
%     end
%     if(Msin(i,find(Msin(i,:),1,'last'))<valor_ksm)
%         mejor_ksm=i;
%         valor_ksm=Msin(i,find(Msin(i,:),1,'last'));
%     end
%     if(GA(i,find(GA(i,:),1,'last'))<valor_gen)
%         mejor_gen=i;
%         valor_gen=GA(i,find(GA(i,:),1,'last'));
%     end
%     if(PSO(i,find(PSO(i,:),1,'last'))<valor_gen)
%         mejor_pso=i;
%         valor_pso=PSO(i,find(PSO(i,:),1,'last'));
%     end
%     
%     
%         
% end



%Saco la peor iteracion de cada uno
% peor_kcm=zeros(1,100);
% peor_ksm=zeros(1,100);
% peor_gen=zeros(1,100);
% peor_pso=zeros(1,100);
% for i=1:100
%     peor_kcm(i)=M(i,find(M(i,:),1,'last'));
%     peor_ksm(i)=Msin(i,find(Msin(i,:),1,'last'));
%     peor_gen(i)=GA(i,find(GA(i,:),1,'last'));
%     peor_pso(i)=PSO(i,find(PSO(i,:),1,'last'));
% end
% 
% 
% max(peor_kcm)
% max(peor_ksm)
% max(peor_gen)
% max(peor_pso)
% 



