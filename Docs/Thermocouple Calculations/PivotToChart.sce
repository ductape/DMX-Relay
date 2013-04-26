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

[dataRows dataColumns] = size(data); 

// Calculate the derivative of the temperature
der = zeros(data);
maxDelta = 10.01;

for i = 1:length(der(:,1))
    if (i > 1) then
        slope = (data(i,2)-data(i-1,2))/(data(i,1)-data(i-1,1));
        if (1) then
            der(i,:) = [data(i,1) slope];
        elseif  (1) then
            der(i,:) = [data(i,1) der(i-1,2) - maxDelta];
        else
            der(i,:) = [data(i,1) slope];
        end
    else
        der(i,:) = [data(i,1) 0];
    end
end

// smooth the derivative
derSmooth = zeros(data);
n = 100;
for i = 1:length(der(:,1))
    if (i > n) then
        derSmooth(i,:) = [der(i,1), mean(der((i-n):i,2))];
    else
        derSmooth(i,:) = [der(i,1), mean(der(1:i,2))];
    end
end

// Calculate the second derivative of the temperature
der2 = zeros(data); 
maxDelta = 1e-4;

for i = 1:length(derSmooth(:,1))
    if (i > 1) then
        slope = (derSmooth(i,2)-derSmooth(i-1,2))/(derSmooth(i,1)-derSmooth(i-1,1));
        if (slope > maxDelta) then
            der2(i,:) = [derSmooth(i,1) maxDelta];
        elseif (slope < -maxDelta) then
            der2(i,:) = [derSmooth(i,1) -maxDelta];
        else
            der2(i,:) = [derSmooth(i,1) slope];                        
        end
    else
        der2(i,:) = [derSmooth(i,1) 0];
    end
end

// smooth the 2nd derivative
der2Smooth = zeros(data);
n = 100;
for i = 1:length(derSmooth(:,1))
    if (i > n) then
        der2Smooth(i,:) = [der2(i,1), mean(der2((i-n):i,2))];
    else
        der2Smooth(i,:) = [der2(i,1), mean(der2(1:i,2))];
    end
end

csvWrite(data,'ThermocoupleData.csv',',');

figure(1);
subplot(3,1,1);
plot(data(:,1),data(:,2));
ylabel('Thermocouple Voltage (mV)');
xlabel('Temperature (°F)');
title('Type K Thermocouple Voltage Versus Temperature');
subplot(3,1,2);
plot(derSmooth(:,1),derSmooth(:,2));
ylabel('Voltage Change / Temperature Change');
xlabel('Temperature (°F)');
subplot(3,1,3);
plot(der2Smooth(:,1),der2Smooth(:,2));

subsetSize = 32;
subset = data(1,:);
printf("subset 1: %f°F, %f, %fmV, %f°C\n", subset(1,1), subset(1,2)*128, subset(1,2), (subset(1,1)-32)*5/9);

for i = 2:subsetSize
    subset = [subset; data(round(dataRows/subsetSize*i),:)];
    printf("subset %d: %f°F, ,%f, %fmV, %f°C\n", i, subset(i,1), (subset(i,2)*128), subset(i,2), (subset(i,1)-32)*5/9);
end

subsetIndex = 2;
lowTemp = subset(1,1);
highTemp = subset(2,1);
lowVolt = subset(1,2);
highVolt = subset(2,2);
subsetExtended = zeros(data);

for i = 1:dataRows
    mV = data(i,2);
    if mV > highVolt then
        lowTemp = highTemp;
        lowVolt = highVolt;
        subsetIndex = subsetIndex + 1;
        highTemp = subset(subsetIndex, 1);
        highVolt = subset(subsetIndex,2);
    end
    temp = ((mV-lowVolt)/(highVolt-lowVolt))*(highTemp-lowTemp)+lowTemp;
    subsetExtended(i,:) = [temp mV];
end

tempError = abs(data(:,1) - subsetExtended(:,1));

figure(2);
//plot(data(:,1),data(:,2));
ylabel('Temperature Error (°F)');
xlabel('Temperature (°F)');
title('Type K Thermocouple Voltage Versus Temperature');
plot(subsetExtended(:,1),tempError);
