// ADS1118 Data Parsing Tool

clear

headerRow = 1;
hexTokens = ['0','x'];

data = csvRead('ads1118_SPI_01.csv',',',[],'string');
header = data(headerRow,:);
misoColumn = find(header=="MISO");
mosiColumn = find(header=="MOSI");

hex = data(headerRow+1,mosiColumn);
disp(hex);
decimal = hex2dec(tokens(hex,hexTokens));
disp(decimal);
