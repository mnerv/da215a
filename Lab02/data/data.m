%  data.m
%
%  Created by Pratchaya Khansomboon on 2020-11-29.
%  Copyright © 2020 Pratchaya Khansomboon. All rights reserved.

clc
clear
close all
format short

data01 = csvread('./TRC02.CSV', 1); % skips header

figure("Name", "9 NOP")
plot(data01(:,1), data01(:,2), ".")
title("Delay 1 micros 9 NOP")
xlabel("Time (S)")
ylabel("Voltage (V)")