%test of find_bounding_box.m

restoredefaultpath;
clear all;
close all;

% Replace this path with your cs4379c-fall2021 git repository path in your system.
repo_path = 'C:\Users\brett\Documents\GitHub\cs4379c-fall2021';

s = filesep; % This gets the file separator character from the  system

addpath([repo_path s 'Brett Owen HW assignments' s 'Assignment2'])
addpath([repo_path s 'Brett Owen HW assignments' s 'Assignment2' s 'Data'])


holes = double(imread('simple_with_holes.gif'));
threshold = 10; 
thresholded = (holes > threshold);
result = remove_holes(holes); 
figure(1); imshow(result); 