function result = person_present(newFrame);
% Replace this path with your cs4379c-fall2021 git repository path in your system.
repo_path = 'C:\Users\brett\Documents\GitHub\cs4379c-fall2021';

s = filesep; % This gets the file separator character from the  system

addpath([repo_path s 'Code' s '00_common' s '00_detection'])
addpath([repo_path s 'Code' s '00_common' s '00_images'])
addpath([repo_path s 'Code' s '00_common' s '00_utilities'])
addpath([repo_path s 'Code' s '04_image_tranform_and_filters'])
addpath([repo_path s 'Brett Owen HW assignments'])

% The data used in this lecture are the same as in the previous 
% lecture (03_elementary_image_operations)
cd([repo_path s 'Data' s '03_elementary_image_operations'])

%%

% improving accuracy by considering frames further away in time.
% code from the hint
[sequence_name, frame] = parse_frame_name(newFrame);
prevFrame = make_frame_name(sequence_name, frame-1);
nextFrame = make_frame_name(sequence_name, frame+1);

frame1 = read_gray(prevFrame);
frame0 = read_gray(newFrame);
frame2 = read_gray(nextFrame);
diff1 = abs(frame0 - frame1);
diff2 = abs(frame0 - frame2);
motion2 = min(diff1, diff2);


%%
% representing the shape as a set of pixels.
% First operation: thresholding:
threshold = 10; thresholded = (motion2 > threshold); imshow(thresholded, []);

%%

% connected component analysis
[labels, number] = bwlabel(thresholded, 4);
figure(1);

colored = label2rgb(labels, @spring, 'c', 'shuffle');
figure(2); 
imshow(colored);

% find the largest connected component
% create an array of counters, one for each connected component.
counters = zeros(1,number);
for i = 1:number
    % for each i, we count the number of pixels equal to i in the labels
    % matrix
    % first, we create a component image, that is 1 for pixels belonging to
    % the i-th connected component, and 0 everywhere else.
    component_image = (labels == i);
    
    % now, we count the non-zero pixels in the component image.
    counters(i) = sum(component_image(:));
end

% find the id of the largest component
[area, id] = max(counters);    

if area >= 1000
    result = 1;
else
    result = 0;
end
