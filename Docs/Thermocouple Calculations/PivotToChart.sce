clear
clc

// Read the Thermocouple Pivot Table and convert it to a chart

pivot = csvRead('Thermocouple Lookup Table.csv');
[rows columns] = size(pivot);

data = zeros(1,2);
[dataRows dataColumns] = size(data); 
loc = 0;
for i = 2:rows
    rowTemperature = pivot(i,1);
//    printf("i=%d\n",i);
    for j = 3:columns
        offset = pivot(1,j)
        temperature = rowTemperature + offset; 
        millivolt = pivot(i,j);        
        if ~isnan(millivolt) then
            loc = loc+1;
            data(loc,:) = [temperature millivolt];
//            printf("loc=%d,",loc);
        end;
//        printf("j=%d,t=%d,m=%f\n",j,temperature,millivolt);
    end;
end;

// Calculate the derivative of the temperature
der = zeros(data);

for i = 1:length(der(:,1))
    if (i > 1) then
        slope = (data(i,2)-data(i-1,2))/(data(i,1)-data(i-1,1));
        der(i,:) = [data(i,1) slope];
    else
        der(i,:) = [data(i,1) 0];
    end
end

der2 = zeros(data); 

for i = 1:length(der(:,1))
    if (i > 1) then
        slope = (der(i,2)-der(i-1,2))/(der(i,1)-der(i-1,1));
        der2(i,:) = [der(i,1) slope];
    else
        der2(i,:) = [der(i,1) 0];
    end
end

figure(1);
subplot(3,1,1);
plot(data(:,1),data(:,2));
ylabel('Thermocouple Voltage (mV)');
xlabel('Temperature (°F)');
title('Type K Thermocouple Voltage Versus Temperature');
subplot(3,1,2);
plot(der(:,1),der(:,2));
ylabel('Voltage Change / Temperature Change');
xlabel('Temperature (°F)');
subplot(3,1,3);
plot(der2(:,1),der2(:,2));
