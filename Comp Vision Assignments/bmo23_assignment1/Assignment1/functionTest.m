%test of find_bounding_box.m

restoredefaultpath;
clear all;
close all;

% Replace this path with your cs4379c-fall2021 git repository path in your system.
repo_path = 'C:\Users\brett\Documents\GitHub\cs4379c-fall2021';

s = filesep; % This gets the file separator character from the  system

addpath([repo_path s 'Code' s '00_common' s '00_detection'])
addpath([repo_path s 'Code' s '00_common' s '00_images'])
addpath([repo_path s 'Code' s '00_common' s '00_utilities'])
addpath([repo_path s 'Code' s '04_image_tranform_and_filters'])
addpath([repo_path s 'Brett Owen HW assignments'])

%bounds = find_bounding_box('walkstraight/frame0070.tif');
%present = person_present('walkstraight/frame0050.tif');
speed = person_speed('walkstraight/frame0050.tif', 'walkstraight/frame0070.tif');